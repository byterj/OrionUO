/***********************************************************************************
**
** GUIHitBox.h
**
** ���������� ��� ������ ����, ��� ����������� ����-���� �� ���
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef GUIHITBOX_H
#define GUIHITBOX_H
//----------------------------------------------------------------------------------
#include "GUIPolygonal.h"
//----------------------------------------------------------------------------------
class CGUIHitBox : public CGUIPolygonal
{
	//!������ �������� ��� ����������� (���� ������������, �� ����������� CGUIButton)
	SETGET(int, ToPage);

public:
	CGUIHitBox(const uint &serial, const int &x, const int &y, const int &width, const int &height, const bool &callOnMouseUp = false);
	virtual ~CGUIHitBox();
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
