/***********************************************************************************
**
** GameItem.cpp
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#include "GameItem.h"
#include "ObjectOnCursor.h"
#include "../OrionUO.h"
#include "../TargetGump.h"
#include "../SelectedObject.h"
#include "../Managers/ConfigManager.h"
#include "../Managers/MapManager.h"
#include "../Managers/AnimationManager.h"
#include "../Managers/GumpManager.h"
#include "../Screen stages/GameScreen.h"
#include "../Gumps/GumpMinimap.h"
//----------------------------------------------------------------------------------
CGameItem::CGameItem(const uint &serial)
: CGameObject(serial), m_Layer(0), m_AnimID(0), m_ImageID(0), m_UsedLayer(0),
m_Opened(false), m_Dragged(false), ShopItem(NULL)
{
}
//----------------------------------------------------------------------------------
CGameItem::~CGameItem()
{
	if (m_Graphic >= 0x4000 && m_Items != NULL)
	{
		CMulti *multi = (CMulti*)m_Items;
		m_Items = NULL;
		delete multi;
	}

	if (ShopItem != NULL)
	{
		delete ShopItem;
		ShopItem = NULL;
	}
	
	if (m_Opened)
	{
		g_GumpManager.CloseGump(m_Serial, 0, GT_CONTAINER);
		g_GumpManager.CloseGump(m_Serial, 0, GT_SPELLBOOK);
		g_GumpManager.CloseGump(m_Serial, 0, GT_MAP);

		CGump *gump = g_GumpManager.GetGump(m_Serial, 0, GT_BULLETIN_BOARD);
		if (gump != NULL)
			g_GumpManager.RemoveGump(gump);

		m_Opened = false;
	}

	if (m_Dragged)
	{
		g_GumpManager.CloseGump(m_Serial, 0, GT_DRAG);

		m_Dragged = false;
	}
}
//----------------------------------------------------------------------------------
/*!
������� ������ �� ������� � ���� (�� �������)
@param [__in] obj ������ �� ������ �� �������
@return 
*/
void CGameItem::Paste(CObjectOnCursor *obj)
{
	if (obj == NULL)
		return;

	m_Items = NULL;
	m_Next = NULL;
	m_Prev = NULL;
	
	m_Serial = obj->Serial;
	m_Graphic = obj->Graphic;
	m_Color = obj->Color;
	m_X = obj->X;
	m_Y = obj->Y;
	m_Z = obj->Z;
	m_Count = obj->Count;
	m_Layer = obj->Layer;
	m_Flags = obj->Flags;
	m_NPC = obj->NPC;
	m_ImageID = obj->ImageID;
	m_Container = obj->Container;
	m_UsedLayer = obj->UsedLayer;
	m_Opened = false;
	m_AnimID = obj->AnimID;
	m_MapIndex = obj->MapIndex;
	m_Dragged = false;
	m_Clicked = false;

	m_Name = obj->Name;
	OnGraphicChange();
}
//----------------------------------------------------------------------------------
/*!
������� ��������� �������� �������
@param [__in_opt] direction ����������� �������� (��� ������)
@return 
*/
void CGameItem::OnGraphicChange(int direction)
{
	if (m_Graphic < 0x4000)
	{
		if (IsCorpse())
		{
			m_AnimIndex = 99;

			for (CORPSE_LIST_MAP::iterator i = g_CorpseSerialList.begin(); i != g_CorpseSerialList.end(); i++)
			{
				if (i->first == m_Serial)
				{
					g_CorpseSerialList.erase(i);
					m_AnimIndex = 0;
					break;
				}
			}

			if (direction & 0x80)
			{
				m_UsedLayer = 1;
				direction &= 0x7F;
			}
			else
				m_UsedLayer = 0;

			m_Layer = direction;

			m_RenderQueueIndex = 6;
		}
		else
		{
			m_TiledataPtr = &g_Orion.m_StaticData[m_Graphic / 32].Tiles[m_Graphic % 32];
			STATIC_TILES &tile = *m_TiledataPtr;

			if (ToLowerA(tile.Name) == "nodraw")
				m_Graphic = 1;

			if (IsWearable() || m_Graphic == 0x0A28)
			{
				m_ImageID = tile.AnimID + 0xC350;
				m_AnimID = tile.AnimID;
				
				g_Orion.ExecuteGump(tile.AnimID + MALE_GUMP_OFFSET);
				g_Orion.ExecuteGump(tile.AnimID + FEMALE_GUMP_OFFSET);

				m_UsedLayer = tile.Quality;
			}
			else if (m_Layer == OL_MOUNT)
			{
				m_AnimID = tile.AnimID;
				m_UsedLayer = tile.Quality;
			}

			if (IsBackground())
				m_RenderQueueIndex = 3 - (int)IsSurface();
			else if (IsSurface())
				m_RenderQueueIndex = 4;
			else if (IsAnimated())
				m_RenderQueueIndex = 6;
			else
				m_RenderQueueIndex = 5;

			m_RenderQueueIndex++;

			g_Orion.ExecuteStaticArt(m_Graphic);
		}
	}
	else if (m_Items == NULL)
		LoadMulti();
}
//----------------------------------------------------------------------------------
void CGameItem::Draw(const int &x, const int &y)
{
	if (m_Container == 0xFFFFFFFF && m_Graphic < 0x4000 && m_Graphic != 1)
	{
#if UO_DEBUG_INFO!=0
		g_RenderedObjectsCountInGameWindow++;
#endif

		ushort objGraphic = m_Graphic;
		ushort objColor = m_Color;

		if (Hidden())
			objColor = 0x038A;

		if (IsCorpse()) //������
			g_AnimationManager.DrawCorpse(this, x, y, m_Z);
		else
		{
			bool doubleDraw = false;
			bool selMode = false;
			objGraphic = GetDrawGraphic(doubleDraw);

			if (!Locked() && g_SelectedObject.Object() == this)
			{
				objColor = 0x0035;
				selMode = true;
			}

			if (doubleDraw)
			{
				g_Orion.DrawStaticArt(objGraphic, objColor, x - 2, y - 5, m_Z, selMode);
				g_Orion.DrawStaticArt(objGraphic, objColor, x + 3, y, m_Z, selMode);
			}
			else
				g_Orion.DrawStaticArtAnimated(objGraphic, objColor, x, y, m_Z, selMode);

			if (IsLightSource() && g_GameScreen.UseLight)
				g_GameScreen.AddLight(this, this, x, y - (m_Z * 4));
		}

		if (!g_ConfigManager.DisableNewTargetSystem && g_NewTargetSystem.Serial == m_Serial && !Locked())
		{
			WISP_GEOMETRY::CSize size = g_Orion.GetArtDimension(objGraphic + 0x4000);

			if (size.Width >= 80)
			{
				g_NewTargetSystem.GumpTop = 0x756D;
				g_NewTargetSystem.GumpBottom = 0x756A;
			}
			else if (size.Width >= 40)
			{
				g_NewTargetSystem.GumpTop = 0x756E;
				g_NewTargetSystem.GumpBottom = 0x756B;
			}
			else
			{
				g_NewTargetSystem.GumpTop = 0x756F;
				g_NewTargetSystem.GumpBottom = 0x756C;
			}

			g_NewTargetSystem.ColorGump = 0x7570;

			g_NewTargetSystem.Hits = 0;
			g_NewTargetSystem.X = x;
			g_NewTargetSystem.TopY = y - (m_Z * 4) - size.Height - 8;
			g_NewTargetSystem.BottomY = y - (m_Z * 4) + 7;
		}

		DrawEffects(x, y);
	}
}
//----------------------------------------------------------------------------------
/*!
���������� �������
@param [__in] mode ����� ���������. true - ���������, false - ����� ��������
@param [__in] drawX �������� ���������� X �������
@param [__in] drawY �������� ���������� Y �������
@param [__in] ticks ������ �������
@return ��� ������ �������� ���������� ��������� �������
*/
void CGameItem::Select(const int &x, const int &y)
{
	if (m_Container == 0xFFFFFFFF && m_Graphic < 0x4000 && m_Graphic != 1)
	{
		if (IsCorpse()) //������
		{
			if (g_AnimationManager.CorpsePixelsInXY(this, x, y, m_Z))
				g_SelectedObject.Init(this);
		}
		else
		{
			bool doubleDraw = false;
			ushort goGraphic = GetDrawGraphic(doubleDraw);

			if (doubleDraw)
			{
				if (g_Orion.StaticPixelsInXY(goGraphic, x - 2, y - 5, m_Z))
					g_SelectedObject.Init(this);
				else if (g_Orion.StaticPixelsInXY(goGraphic, x + 3, y, m_Z))
					g_SelectedObject.Init(this);
			}
			else if (g_Orion.StaticPixelsInXYAnimated(goGraphic, x, y, m_Z))
				g_SelectedObject.Init(this);
		}
	}
}
//----------------------------------------------------------------------------------
/*!
�������� ������ �������� (��� ��������)
@return ������ ��������
*/
ushort CGameItem::GetMountAnimation()
{
	ushort graphic = m_Graphic;

	if (m_Layer == OL_MOUNT)
	{
		switch (graphic)
		{
			case 0x3E90: // 16016 Reptalon
			{
				graphic = 0x0114;
				break;
			}
			case 0x3E91: // 16017
			{
				graphic = 0x0115;
				break;
			}
			case 0x3E92: // 16018
			{
				graphic = 0x011C;
				break;
			}
			case 0x3E94: // 16020
			{
				graphic = 0x00F3;
				break;
			}
			case 0x3E95: // 16021
			{
				graphic = 0x00A9;
				break;
			}
			case 0x3E97: // 16023 Ethereal Giant Beetle
			{
				graphic = 0x00C3;
				break;
			}
			case 0x3E98: // 16024 Ethereal Swamp Dragon
			{
				graphic = 0x00C2;
				break;
			}
			case 0x3E9A: // 16026 Ethereal Ridgeback
			{
				graphic = 0x00C1;
				break;
			}
			case 0x3E9B: // 16027
			case 0x3E9D: // 16029 Ethereal Unicorn
			{
				graphic = 0x00C0;
				break;
			}
			case 0x3E9C: // 16028 Ethereal Kirin
			{
				graphic = 0x00BF;
				break;
			}
			case 0x3E9E: // 16030
			{
				graphic = 0x00BE;
				break;
			}
			case 0x3EA0: // 16032 light grey/horse3
			{
				graphic = 0x00E2;
				break;
			}
			case 0x3EA1: // 16033 greybrown/horse4
			{
				graphic = 0x00E4;
				break;
			}
			case 0x3EA2: // 16034 dark brown/horse
			{
				graphic = 0x00CC;
				break;
			}
			case 0x3EA3: // 16035 desert ostard
			{
				graphic = 0x00D2;
				break;
			}
			case 0x3EA4: // 16036 frenzied ostard (=zostrich)
			{
				graphic = 0x00DA;
				break;
			}
			case 0x3EA5: // 16037 forest ostard
			{
				graphic = 0x00DB;
				break;
			}
			case 0x3EA6: // 16038 Llama
			{
				graphic = 0x00DC;
				break;
			}
			case 0x3EA7: // 16039 Nightmare / Vortex
			{
				graphic = 0x0074;
				break;
			}
			case 0x3EA8: // 16040 Silver Steed
			{
				graphic = 0x0075;
				break;
			}
			case 0x3EA9: // 16041 Nightmare
			{
				graphic = 0x0072;
				break;
			}
			case 0x3EAA: // 16042 Ethereal Horse
			{
				graphic = 0x0073;
				break;
			}
			case 0x3EAB: // 16043 Ethereal Llama
			{
				graphic = 0x00AA;
				break;
			}
			case 0x3EAC: // 16044 Ethereal Ostard
			{
				graphic = 0x00AB;
				break;
			}
			case 0x3EAD: // 16045 Kirin
			{
				graphic = 0x0084;
				break;
			}
			case 0x3EAF: // 16047 War Horse (Blood Red)
			{
				graphic = 0x0078;
				break;
			}
			case 0x3EB0: // 16048 War Horse (Light Green)
			{
				graphic = 0x0079;
				break;
			}
			case 0x3EB1: // 16049 War Horse (Light Blue)
			{
				graphic = 0x0077;
				break;
			}
			case 0x3EB2: // 16050 War Horse (Purple)
			{
				graphic = 0x0076;
				break;
			}
			case 0x3EB3: // 16051 Sea Horse (Medium Blue)
			{
				graphic = 0x0090;
				break;
			}
			case 0x3EB4: // 16052 Unicorn
			{
				graphic = 0x007A;
				break;
			}
			case 0x3EB5: // 16053 Nightmare
			{
				graphic = 0x00B1;
				break;
			}
			case 0x3EB6: // 16054 Nightmare 4
			{
				graphic = 0x00B2;
				break;
			}
			case 0x3EB7: // 16055 Dark Steed
			{
				graphic = 0x00B3;
				break;
			}
			case 0x3EB8: // 16056 Ridgeback
			{
				graphic = 0x00BC;
				break;
			}
			case 0x3EBA: // 16058 Ridgeback, Savage
			{
				graphic = 0x00BB;
				break;
			}
			case 0x3EBB: // 16059 Skeletal Mount
			{
				graphic = 0x0319;
				break;
			}
			case 0x3EBC: // 16060 Beetle
			{
				graphic = 0x0317;
				break;
			}
			case 0x3EBD: // 16061 SwampDragon
			{
				graphic = 0x031A;
				break;
			}
			case 0x3EBE: // 16062 Armored Swamp Dragon
			{
				graphic = 0x031F;
				break;
			}
			case 0x3EC3: //16067 Beetle
			{
				graphic = 0x02D4;
				break;
			}
			case 0x3EC5: // 16069
			case 0x3F3A: // 16186 snow bear ???
			{
				graphic = 0x00D5;
				break;
			}
			case 0x3EC6: // 16070
			{
				graphic = 0x01B0;
				break;
			}
			case 0x3EC7: // 16071
			{
				graphic = 0x04E6;
				break;
			}
			case 0x3EC8: // 16072
			{
				graphic = 0x04E7;
				break;
			}
			case 0x3EC9: // 16073
			{
				graphic = 0x042D;
				break;
			}

			//start FWUO ???
			case 0x2F01: // 12033 Polar bear
			{
				graphic = 0x00D5;
				break;
			}
			case 0x2F03: // 12035 Ridgeback
			{
				graphic = 0x00F6;
				break;
			}
			case 0x2F04: // 12036 Skeletal mount
			{
				graphic = 0x00F3;
				break;
			}
			case 0x2F05: // 12037 Genie
			{
				graphic = 0x023D;
				break;
			}
			case 0x2F10: // 12048 Kyryn
			{
				graphic = 0x00EB;
				break;
			}
			case 0x3001: // 12289 Beetle
			{
				graphic = 0x00F4;
				break;
			}
			//end FWUO ???

			default: //lightbrown/horse2
			{
				graphic = 0x00C8;
				break;
			}
		}
	}
	else if (IsCorpse())
	{
		graphic = (ushort)m_Count;
		g_AnimationManager.GetCorpseGraphic(graphic);
	}

	return graphic;
}
//----------------------------------------------------------------------------------
/*!
�������� ������ � ������� ������
@return 
*/
void CGameItem::LoadMulti()
{
	CIndexMulti &index = g_Orion.m_MultiDataIndex[m_Graphic - 0x4000];
	
	if (index.Address != NULL)
	{
		uint address = index.Address;

		int count = index.Count;
		
		int minX = 0;
		int minY = 0;
		int maxX = 0;
		int maxY = 0;

		IFOR(j, 0, count)
		{
			PMULTI_BLOCK pmb = (PMULTI_BLOCK)(address + (j * sizeof(MULTI_BLOCK)));

			if (pmb->Flags)
			{
				CMultiObject *mo = new CMultiObject(pmb->ID, m_X + pmb->X, m_Y + pmb->Y, m_Z + (char)pmb->Z, pmb->Flags);

				if (ToLowerA(mo->GetStaticData()->Name) == "nodraw")
				{
					delete mo;
					continue;
				}

				g_MapManager->AddRender(mo);
				AddMultiObject(mo);
			}

			if (pmb->X < minX)
				minX = pmb->X;
			if (pmb->X > maxX)
				maxX = pmb->X;
			
			if (pmb->Y < minY)
				minY = pmb->Y;
			if (pmb->Y > maxY)
				maxY = pmb->Y;
		}

		CMulti *multi = (CMulti*)m_Items;

		if (multi != NULL)
		{
			multi->MinX = minX;
			multi->MinY = minY;

			multi->MaxX = maxX;
			multi->MaxY = maxY;
		}

		CGumpMinimap *minimap = (CGumpMinimap*)g_GumpManager.GetGump(g_PlayerSerial, 0, GT_MINIMAP);

		if (minimap != NULL)
			minimap->LastX = 0;
	}
}
//----------------------------------------------------------------------------------
/*!
�������� �������-������
@param [__in] obj ������ �� ������-������
@return 
*/
void CGameItem::AddMultiObject(CMultiObject *obj)
{
	if (m_Items == NULL)
	{
		m_Items = new CMulti(obj->X, obj->Y);
		m_Items->m_Next = NULL;
		m_Items->m_Items = obj;
		obj->m_Next = NULL;
		obj->m_Prev = NULL;
	}
	else
	{
		CMulti *multi = GetMultiAtXY(obj->X, obj->Y);

		if (multi != NULL)
		{
			QFOR(multiobj, multi->m_Items, CMultiObject*)
			{
				if (obj->Z < multiobj->Z)
				{
					if (multiobj->m_Prev == NULL)
					{
						obj->m_Prev = NULL;
						obj->m_Next = multiobj;
						multiobj->m_Prev = obj;
						multi->m_Items = obj;
					}
					else
					{
						obj->m_Next = multiobj->m_Next;
						multiobj->m_Next = obj;
						obj->m_Prev = multiobj;
					}

					return;
				}

				if (multiobj->m_Next == NULL)
				{
					multiobj->m_Next = obj;
					obj->m_Prev = multiobj;
					obj->m_Next = NULL;

					return;
				}
			}

			//���� ������ ���� - ���-�� ����� �� ���
		}
		else
		{
			CMulti *newmulti = new CMulti(obj->X, obj->Y);
			newmulti->m_Next = NULL;
			newmulti->m_Items = obj;
			obj->m_Next = NULL;
			obj->m_Prev = NULL;

			QFOR(multi, m_Items, CMulti*)
			{
				if (multi->m_Next == NULL)
				{
					multi->m_Next = newmulti;
					break;
				}
			}
		}
	}
}
//----------------------------------------------------------------------------------
/*!
��������� ������� ������ � �������� �����������
@param [__in] x ���������� X
@param [__in] y ���������� Y
@return ������ �� ������ ��� NULL
*/
CMulti *CGameItem::GetMultiAtXY(const short &x, const short &y)
{
	QFOR(multi, m_Items, CMulti*)
	{
		if (multi->X == x && multi->Y == y)
			return multi;
	}

	return NULL;
}
//----------------------------------------------------------------------------------
/*!
����� ������ ������ (����������) �� ���� � ������ (� ���) �����
@param [__in] graphic ������ ��������
@param [__in_opt] color ���� ��������
@return ������ �� ��������� ������ ��� NULL
*/
CGameItem *CGameItem::FindItem(const ushort &graphic, const ushort &color)
{
	CGameItem *item = NULL;

	if (color == 0xFFFF) //����� �� ������������ �����
	{
		WORD minColor = 0xFFFF;

		QFOR(obj, m_Items, CGameItem*)
		{
			if (obj->Graphic == graphic)
			{
				if (obj->Color < minColor)
				{
					item = obj;
					minColor = obj->Color;
				}
			}

			if (!obj->Empty())
			{
				CGameItem *found = obj->FindItem(graphic, color);
				
				if (found != NULL && found->Color < minColor)
				{
					item = found;
					minColor = found->Color;
				}
			}
		}
	}
	else //����������� �����
	{
		QFOR(obj, m_Items, CGameItem*)
		{
			if (obj->Graphic == graphic && obj->Color == color)
				item = obj;

			if (!obj->Empty())
			{
				CGameItem *found = obj->FindItem(graphic, color);
				
				if (found != NULL)
					item = found;
			}
		}
	}

	return item;
}
//----------------------------------------------------------------------------------
/*!
����� ������ �� ��������� ���� (��� ������)
@param [__in] layer ����� ����
@return ������ �� ��������� ������ ��� NULL
*/
CGameItem *CGameItem::FindLayer(const int &layer)
{
	QFOR(obj, m_Items, CGameItem*)
	{
		if (obj->Layer == layer)
			return obj;
	}

	return NULL;
}
//----------------------------------------------------------------------------------
