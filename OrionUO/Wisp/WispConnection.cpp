//----------------------------------------------------------------------------------
#include "WispConnection.h"

namespace WISP_NETWORK
{
//----------------------------------------------------------------------------------
CConnection::CConnection(int af, int type, int protocol)
: m_DataReady(0), m_Connected(false), m_Port(0), m_Af(af), m_Type(type),
m_Protocol(protocol)
{
	WSADATA wsaData = { 0 };

	if (!WSAStartup(MAKEWORD(2, 2), &wsaData))
		m_Socket = socket(af, type, protocol);
	else
		m_Socket = INVALID_SOCKET;

	m_MessageParser = new CPacketMessage();
}
//----------------------------------------------------------------------------------
CConnection::~CConnection()
{
	Disconnect();

	if (m_MessageParser != NULL)
	{
		delete m_MessageParser;
		m_MessageParser = NULL;
	}
}
//----------------------------------------------------------------------------------
bool CConnection::Connect(const string &address, const int &port)
{
	if (m_Connected)
		return false;
	else if (m_Socket == INVALID_SOCKET)
	{
		m_Socket = socket(m_Af, m_Type, m_Protocol);

		if (m_Socket == INVALID_SOCKET)
			return false;
	}

	sockaddr_in caddr;
	memset(&caddr, 0, sizeof(sockaddr_in));
	caddr.sin_family = AF_INET;

	struct hostent *he;

	int rt = inet_addr(address.c_str());

	if (rt != -1)
		caddr.sin_addr.s_addr = rt;
	else
	{
		he = gethostbyname(address.c_str());

		if (he == NULL)
			return false;

		memcpy(&caddr.sin_addr, he->h_addr, he->h_length);
	}

	caddr.sin_port = htons(port);

	if (connect(m_Socket, (struct sockaddr*)&caddr, sizeof(caddr)) == -1)
		return false;

	m_Port = port;
	m_Connected = true;
	WSASetLastError(0);
	m_MessageParser->Clear();

	return true;
}
//----------------------------------------------------------------------------------
void CConnection::Disconnect()
{
	if (m_Connected && m_Socket != INVALID_SOCKET)
	{
		closesocket(m_Socket);

		m_Socket = INVALID_SOCKET;
		m_Connected = false;
		m_DataReady = 0;
		m_Port = 0;
		m_MessageParser->Clear();
	}
}
//----------------------------------------------------------------------------------
bool CConnection::ReadyRead()
{
	if (!m_Connected || m_Socket == INVALID_SOCKET)
		return false;

	fd_set rfds;
	struct timeval tv = { 0, 0 };
	FD_ZERO(&rfds);
	FD_SET(m_Socket, &rfds);

	m_DataReady = select(m_Socket, &rfds, NULL, NULL, &tv);

	if (m_DataReady == SOCKET_ERROR)
		Disconnect();

	return (m_DataReady != 0);
}
//----------------------------------------------------------------------------------
void CConnection::Read(const int &maxSize)
{
	if (m_DataReady == SOCKET_ERROR)
		Disconnect();
	else if (m_Connected && m_Socket != INVALID_SOCKET)
	{
		UCHAR_LIST data(maxSize);
		int size = recv(m_Socket, (char*)&data[0], maxSize, 0);

		if (size > 0)
		{
			data.resize(size);

			data = Decompression(data);

			m_MessageParser->Append(data);
		}
	}
}
//----------------------------------------------------------------------------------
int CConnection::Send(puchar data, const int &size)
{
	if (!m_Connected || m_Socket == INVALID_SOCKET)
		return 0;

	return send(m_Socket, (char*)data, size, 0);
}
//----------------------------------------------------------------------------------
int CConnection::Send(const UCHAR_LIST &data)
{
	if (data.size())
		return Send((puchar)&data[0], data.size());
	
	return 0;
}
//----------------------------------------------------------------------------------
}; //namespace
//----------------------------------------------------------------------------------
