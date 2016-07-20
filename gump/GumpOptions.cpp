/****************************************************************************
**
** OptionsGump.cpp
**
** Copyright (C) September 2015 Hotride
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
*****************************************************************************
*/
//----------------------------------------------------------------------------
#include "stdafx.h"
//----------------------------------------------------------------------------
const WORD g_OptionsTextColor = 0;
//----------------------------------------------------------------------------
TTextTexture TGumpOptions::m_TexturePage1[8];	//Sound and Music
TTextTexture TGumpOptions::m_TexturePage2[3];	//Orion's configuration
TTextTexture TGumpOptions::m_TexturePage3[6];	//Language
TTextTexture TGumpOptions::m_TexturePage4[19];	//Chat
TTextTexture TGumpOptions::m_TexturePage5[7];	//Macro Options
TTextTexture TGumpOptions::m_TexturePage6[15];	//Interface
TTextTexture TGumpOptions::m_TexturePage7[18];	//Display
TTextTexture TGumpOptions::m_TexturePage8[9];	//Reputation System
TTextTexture TGumpOptions::m_TexturePage9[9];	//Miscellaneous
TTextTexture TGumpOptions::m_TexturePage10[2];	//Filter Options
//----------------------------------------------------------------------------
TGumpOptions::TGumpOptions(DWORD serial, short x, short y)
: TGump(GT_OPTIONS, serial, x, y), m_Page(0), m_LastChangeMacroTime(0),
m_MacroSelection(0), m_MacroElement(0), m_MacroListOffset(0), m_MacroListCount(0),
m_MacroListOffsetYStart(0), m_MacroListOffsetYEnd(0), m_MacroListNameOffset(0),
m_MacroPointer(NULL), m_MacroObjectPointer(NULL)
{
	TextEntryGameSizeX = new TEntryText(2000, 0, 0, true);
	TextEntryGameSizeY = new TEntryText(2000, 0, 0, true);
	TextEntryMacro = new TEntryText();
}
//----------------------------------------------------------------------------
TGumpOptions::~TGumpOptions()
{
	if (TextEntryGameSizeX != NULL)
	{
		delete TextEntryGameSizeX;
		TextEntryGameSizeX = NULL;
	}

	if (TextEntryGameSizeY != NULL)
	{
		delete TextEntryGameSizeY;
		TextEntryGameSizeY = NULL;
	}

	if (TextEntryMacro != NULL)
	{
		delete TextEntryMacro;
		TextEntryMacro = NULL;
	}
}
//----------------------------------------------------------------------------
void TGumpOptions::Init()
{
	OptionsMacroManager->LoadFromMacro();

	m_MacroPointer = (TMacro*)OptionsMacroManager->m_Items;
	m_MacroObjectPointer = (TMacroObject*)m_MacroPointer->m_Items;

	TextEntryMacro->SetText(m_HotkeyText[m_MacroPointer->Key & 0xFF]);
}
//----------------------------------------------------------------------------
bool TGumpOptions::EntryPointerHere()
{
	return (EntryPointer == TextEntryGameSizeX || EntryPointer == TextEntryGameSizeY || EntryPointer == TextEntryMacro || OptionsMacroManager->EntryPointerHere());
}
//----------------------------------------------------------------------------
void TGumpOptions::PrepareTextures()
{
	Orion->ExecuteResizepic(0x00C8);
	Orion->ExecuteResizepic(0x0A28);
	Orion->ExecuteResizepic(0x0BB8);
	Orion->ExecuteButton(0x0867);
	Orion->ExecuteButton(0x099C);
	Orion->ExecuteButton(0x099F);
	Orion->ExecuteButton(0x09A2);
	Orion->ExecuteButton(0x09A5);
	Orion->ExecuteGumpPart(0x09B5, 5);
	Orion->ExecuteGumpPart(0x0983, 11);
	Orion->ExecuteGumpPart(0x00D0, 42);
}
//----------------------------------------------------------------------------
void TGumpOptions::InitTextTextures()
{
	BYTE font = 0; // (BYTE)(ConnectionManager.ClientVersion >= CV_305D);

	//Sound and Music
	wstring str = L"Sound and Music";
	FontManager->GenerateW(font, m_TexturePage1[0], str.c_str(), g_OptionsTextColor, 30, 460, TS_CENTER);

	str = L"These settings affect the sound and music you will hear while playing Ultima Online.";
	FontManager->GenerateW(font, m_TexturePage1[1], str.c_str(), g_OptionsTextColor, 30, 500);

	str = L"Sound on/off";
	FontManager->GenerateW(font, m_TexturePage1[2], str.c_str(), g_OptionsTextColor);

	str = L"Sound volume";
	FontManager->GenerateW(font, m_TexturePage1[3], str.c_str(), g_OptionsTextColor);

	str = L"Music on/off";
	FontManager->GenerateW(font, m_TexturePage1[4], str.c_str(), g_OptionsTextColor);

	str = L"Music volume";
	FontManager->GenerateW(font, m_TexturePage1[5], str.c_str(), g_OptionsTextColor);

	str = L"Play footstep sounds";
	FontManager->GenerateW(font, m_TexturePage1[6], str.c_str(), g_OptionsTextColor);

	str = L"Play combat music";
	FontManager->GenerateW(font, m_TexturePage1[7], str.c_str(), g_OptionsTextColor);



	//Orion's configuration
	str = L"Orion's configuration";
	FontManager->GenerateW(font, m_TexturePage2[0], str.c_str(), g_OptionsTextColor, 30, 460, TS_CENTER);

	str = L"These settings configure the Orion UO Client.";
	FontManager->GenerateW(font, m_TexturePage2[1], str.c_str(), g_OptionsTextColor);

	str = L"FPS rate:";
	FontManager->GenerateW(font, m_TexturePage2[2], str.c_str(), g_OptionsTextColor);


	//Language
	str = L"Language";
	FontManager->GenerateW(font, m_TexturePage3[0], str.c_str(), g_OptionsTextColor, 30, 460, TS_CENTER);

	str = L"The language you use when playing UO is obtained from your Operating System settings.";
	FontManager->GenerateW(font, m_TexturePage3[1], str.c_str(), g_OptionsTextColor, 30, 480);

	str = L"Use Tool-tips";
	FontManager->GenerateW(font, m_TexturePage3[2], str.c_str(), g_OptionsTextColor);

	str = L"Delay befor Tool-tip appears";
	FontManager->GenerateW(font, m_TexturePage3[3], str.c_str(), g_OptionsTextColor);

	str = L"Color of Tool-tip text";
	FontManager->GenerateW(font, m_TexturePage3[4], str.c_str(), g_OptionsTextColor);

	str = L"Font for Tool-tips";
	FontManager->GenerateW(font, m_TexturePage3[5], str.c_str(), g_OptionsTextColor);



	//Chat
	str = L"Chat";
	FontManager->GenerateW(font, m_TexturePage4[0], str.c_str(), g_OptionsTextColor, 30, 460, TS_CENTER);

	str = L"These settings affect the interface display for the chat system.";
	FontManager->GenerateW(font, m_TexturePage4[1], str.c_str(), g_OptionsTextColor);

	str = L"Input text color";
	FontManager->GenerateW(font, m_TexturePage4[2], str.c_str(), g_OptionsTextColor);

	str = L"Menu option color";
	FontManager->GenerateW(font, m_TexturePage4[3], str.c_str(), g_OptionsTextColor);

	str = L"Player color in member list";
	FontManager->GenerateW(font, m_TexturePage4[4], str.c_str(), g_OptionsTextColor);

	str = L"Chat text color";
	FontManager->GenerateW(font, m_TexturePage4[5], str.c_str(), g_OptionsTextColor);

	str = L"Player name without speaking privileges";
	FontManager->GenerateW(font, m_TexturePage4[6], str.c_str(), g_OptionsTextColor, 30, 160);

	str = L"Muted text color";
	FontManager->GenerateW(font, m_TexturePage4[7], str.c_str(), g_OptionsTextColor);

	str = L"Channel moderator name";
	FontManager->GenerateW(font, m_TexturePage4[8], str.c_str(), g_OptionsTextColor);

	str = L"Channel moderator text";
	FontManager->GenerateW(font, m_TexturePage4[9], str.c_str(), g_OptionsTextColor);

	str = L"My name's color";
	FontManager->GenerateW(font, m_TexturePage4[10], str.c_str(), g_OptionsTextColor);

	str = L"My text color";
	FontManager->GenerateW(font, m_TexturePage4[11], str.c_str(), g_OptionsTextColor);

	str = L"System message color";
	FontManager->GenerateW(font, m_TexturePage4[12], str.c_str(), g_OptionsTextColor);

	str = L"Text Output Background Color";
	FontManager->GenerateW(font, m_TexturePage4[13], str.c_str(), g_OptionsTextColor);

	str = L"Text Input Background Color";
	FontManager->GenerateW(font, m_TexturePage4[14], str.c_str(), g_OptionsTextColor);

	str = L"User List Background Color";
	FontManager->GenerateW(font, m_TexturePage4[15], str.c_str(), g_OptionsTextColor);

	str = L"Conference List Background Color";
	FontManager->GenerateW(font, m_TexturePage4[16], str.c_str(), g_OptionsTextColor);

	str = L"Command List Background Color";
	FontManager->GenerateW(font, m_TexturePage4[17], str.c_str(), g_OptionsTextColor);

	str = L"Chat font";
	FontManager->GenerateW(font, m_TexturePage4[18], str.c_str(), g_OptionsTextColor);



	//Macro Options
	str = L"Macro Options";
	FontManager->GenerateW(font, m_TexturePage5[0], str.c_str(), g_OptionsTextColor, 30, 460, TS_CENTER);
	
	str = L"Keystroke";
	FontManager->GenerateW(font, m_TexturePage5[1], str.c_str(), g_OptionsTextColor);
	
	str = L"Key";
	FontManager->GenerateW(font, m_TexturePage5[2], str.c_str(), g_OptionsTextColor);
	
	str = L"Shift";
	FontManager->GenerateW(font, m_TexturePage5[3], str.c_str(), g_OptionsTextColor);
	
	str = L"Alt";
	FontManager->GenerateW(font, m_TexturePage5[4], str.c_str(), g_OptionsTextColor);
	
	str = L"Ctrl";
	FontManager->GenerateW(font, m_TexturePage5[5], str.c_str(), g_OptionsTextColor);
	
	str = L"Actions";
	FontManager->GenerateW(font, m_TexturePage5[6], str.c_str(), g_OptionsTextColor);




	//Interface
	str = L"Interface";
	FontManager->GenerateW(font, m_TexturePage6[0], str.c_str(), g_OptionsTextColor, 30, 460, TS_CENTER);

	str = L"These options affect your interface.";
	FontManager->GenerateW(font, m_TexturePage6[1], str.c_str(), g_OptionsTextColor);

	str = L"Enable pathfinding with double-right-click";
	FontManager->GenerateW(font, m_TexturePage6[2], str.c_str(), g_OptionsTextColor);

	str = L"Hold down TAB key for combat, instead of tapping it to toggle combat mode";
	FontManager->GenerateW(font, m_TexturePage6[3], str.c_str(), g_OptionsTextColor, 30, 450);

	str = L"Offset interface windows rather than perfectly stacking them";
	FontManager->GenerateW(font, m_TexturePage6[4], str.c_str(), g_OptionsTextColor);

	str = L"Automatically arrange minimized windows";
	FontManager->GenerateW(font, m_TexturePage6[5], str.c_str(), g_OptionsTextColor);

	str = L"Your character will always run if this is checked";
	FontManager->GenerateW(font, m_TexturePage6[6], str.c_str(), g_OptionsTextColor);

	str = L"Disable the Menu Bar";
	FontManager->GenerateW(font, m_TexturePage6[7], str.c_str(), g_OptionsTextColor);

	str = L"Gray out of range objects";
	FontManager->GenerateW(font, m_TexturePage6[8], str.c_str(), g_OptionsTextColor);

	str = L"Disable New Target System";
	FontManager->GenerateW(font, m_TexturePage6[9], str.c_str(), g_OptionsTextColor);

	str = L"Object Handles";
	FontManager->GenerateW(font, m_TexturePage6[10], str.c_str(), g_OptionsTextColor);
	
	str = L"Reduce FPS when Window is Unactive";
	FontManager->GenerateW(font, m_TexturePage6[11], str.c_str(), g_OptionsTextColor);

	str = L"Display Item Properties Icon";
	FontManager->GenerateW(font, m_TexturePage6[12], str.c_str(), g_OptionsTextColor);

	str = L"Hold Shift For Context Menus";
	FontManager->GenerateW(font, m_TexturePage6[13], str.c_str(), g_OptionsTextColor);

	str = L"Hold Shift For Enable Pathfinding";
	FontManager->GenerateW(font, m_TexturePage6[14], str.c_str(), g_OptionsTextColor);



	//Display
	str = L"Display";
	FontManager->GenerateW(font, m_TexturePage7[0], str.c_str(), g_OptionsTextColor, 30, 460, TS_CENTER);

	str = L"These options affect your display, and adjusting some of them may improve your graphics performance.";
	FontManager->GenerateW(font, m_TexturePage7[1], str.c_str(), g_OptionsTextColor, 30, 500);

	str = L"Game Play Window Size";
	FontManager->GenerateW(font, m_TexturePage7[2], str.c_str(), g_OptionsTextColor);

	str = L"Adjust how long speech remains on screen";
	FontManager->GenerateW(font, m_TexturePage7[3], str.c_str(), g_OptionsTextColor);

	str = L"Scale speech duration based on length";
	FontManager->GenerateW(font, m_TexturePage7[4], str.c_str(), g_OptionsTextColor);

	str = L"Speech Color";
	FontManager->GenerateW(font, m_TexturePage7[5], str.c_str(), g_OptionsTextColor);

	str = L"Emote Color";
	FontManager->GenerateW(font, m_TexturePage7[6], str.c_str(), g_OptionsTextColor);

	str = L"Party Message Color";
	FontManager->GenerateW(font, m_TexturePage7[7], str.c_str(), g_OptionsTextColor);
	
	str = L"Guild Message Color";
	FontManager->GenerateW(font, m_TexturePage7[8], str.c_str(), g_OptionsTextColor);

	str = L"Alliance Message Color";
	FontManager->GenerateW(font, m_TexturePage7[9], str.c_str(), g_OptionsTextColor);
	
	str = L"Ignore Guild Messages";
	FontManager->GenerateW(font, m_TexturePage7[10], str.c_str(), g_OptionsTextColor);

	str = L"Ignore Alliance Messages";
	FontManager->GenerateW(font, m_TexturePage7[11], str.c_str(), g_OptionsTextColor);

	str = L"Dark Nights";
	FontManager->GenerateW(font, m_TexturePage7[12], str.c_str(), g_OptionsTextColor);

	str = L"Colored Lighting";
	FontManager->GenerateW(font, m_TexturePage7[13], str.c_str(), g_OptionsTextColor);

	str = L"Standard characters animation delay";
	FontManager->GenerateW(font, m_TexturePage7[14], str.c_str(), g_OptionsTextColor);

	str = L"Standard items animation delay";
	FontManager->GenerateW(font, m_TexturePage7[15], str.c_str(), g_OptionsTextColor);

	str = L"Lock game window resizing";
	FontManager->GenerateW(font, m_TexturePage7[16], str.c_str(), g_OptionsTextColor);

	str = L"Lock gumps moving";
	FontManager->GenerateW(font, m_TexturePage7[17], str.c_str(), g_OptionsTextColor);
	


	//Reputation System
	str = L"Reputation System";
	FontManager->GenerateW(font, m_TexturePage8[0], str.c_str(), g_OptionsTextColor, 30, 460, TS_CENTER);

	str = L"These settings affect the reputation system, which is Ultima Online's system for controlling antisocial behavior.";
	FontManager->GenerateW(font, m_TexturePage8[1], str.c_str(), g_OptionsTextColor, 30, 500);

	str = L"Innocent highlight color";
	FontManager->GenerateW(font, m_TexturePage8[2], str.c_str(), g_OptionsTextColor);

	str = L"Friendly guilds highlight color";
	FontManager->GenerateW(font, m_TexturePage8[3], str.c_str(), g_OptionsTextColor);

	str = L"Someone that can be attacked color";
	FontManager->GenerateW(font, m_TexturePage8[4], str.c_str(), g_OptionsTextColor);

	str = L"Criminal highlight color";
	FontManager->GenerateW(font, m_TexturePage8[5], str.c_str(), g_OptionsTextColor);

	str = L"Enemy guildmembers color";
	FontManager->GenerateW(font, m_TexturePage8[6], str.c_str(), g_OptionsTextColor);

	str = L"Murderer highlight color";
	FontManager->GenerateW(font, m_TexturePage8[7], str.c_str(), g_OptionsTextColor);

	str = L"Query before performing criminal actions";
	FontManager->GenerateW(font, m_TexturePage8[8], str.c_str(), g_OptionsTextColor);



	//Miscellaneous
	str = L"Miscellaneous";
	FontManager->GenerateW(font, m_TexturePage9[0], str.c_str(), g_OptionsTextColor, 30, 460, TS_CENTER);

	str = L"Miscellaneous options.";
	FontManager->GenerateW(font, m_TexturePage9[1], str.c_str(), g_OptionsTextColor);

	str = L"Show Names of Approaching Players";
	FontManager->GenerateW(font, m_TexturePage9[2], str.c_str(), g_OptionsTextColor);

	str = L"Use circle of transparency";
	FontManager->GenerateW(font, m_TexturePage9[3], str.c_str(), g_OptionsTextColor);

	str = L"Set radius of transparency circle";
	FontManager->GenerateW(font, m_TexturePage9[4], str.c_str(), g_OptionsTextColor);

	str = L"Inform me when my skills improve this much (in tenths)";
	FontManager->GenerateW(font, m_TexturePage9[5], str.c_str(), g_OptionsTextColor);

	str = L"Inform me of increases in strength, dexterity, and intelligence.";
	FontManager->GenerateW(font, m_TexturePage9[6], str.c_str(), g_OptionsTextColor);

	str = L"Console need press 'Enter' to activate it.";
	FontManager->GenerateW(font, m_TexturePage9[7], str.c_str(), g_OptionsTextColor);

	str = L"Set the font for speech";
	FontManager->GenerateW(font, m_TexturePage9[8], str.c_str(), g_OptionsTextColor);



	//Filter Options

}
//----------------------------------------------------------------------------
void TGumpOptions::ReleaseTextTextures()
{
	IFOR(i, 0, 8)
		m_TexturePage1[i].Clear();

	IFOR(i, 0, 3)
		m_TexturePage2[i].Clear();

	IFOR(i, 0, 6)
		m_TexturePage3[i].Clear();

	IFOR(i, 0, 19)
		m_TexturePage4[i].Clear();

	IFOR(i, 0, 7)
		m_TexturePage5[i].Clear();

	IFOR(i, 0, 15)
		m_TexturePage6[i].Clear();

	IFOR(i, 0, 18)
		m_TexturePage7[i].Clear();

	IFOR(i, 0, 9)
		m_TexturePage8[i].Clear();

	IFOR(i, 0, 9)
		m_TexturePage9[i].Clear();

	//IFOR(i, 0, 2)
		//m_TexturePage10[i].Clear();
}
//---------------------------------------------------------------------------
void TGumpOptions::GenerateFrame()
{
	if (!g_DrawMode)
	{
		m_FrameRedraw = false;
		m_FrameCreated = false;

		return;
	}

	DWORD index = (DWORD)this;

	CalculateGumpState();

	TMacroObject *obj = m_MacroObjectPointer;
	if (obj != NULL)
	{
		int macroCount = 0;

		while (obj != NULL)
		{
			char hasMenu = obj->HasSubMenu;

			if (hasMenu)
			{
				if (hasMenu != 1 && ((TMacroObjectEntry*)obj)->TextEntry->Changed)
					((TMacroObjectEntry*)obj)->TextEntry->DrawA(1, 0x0386, 118, 5, TS_LEFT, UOFONT_FIXED);
			}

			obj = (TMacroObject*)obj->m_Next;
		}
	}

	glNewList((GLuint)this, GL_COMPILE);
	
		Orion->DrawResizepicGump(0x0A28, 40, 0, 550, 450); //Body



		//Left page buttons

		//Sound and Music
		WORD gumpID = 0x00DA;
		if (!m_Page)
			gumpID--;
		Orion->DrawGump(gumpID, 0, 0, 45);

		//Orion's configuration
		gumpID = 0x00DC;
		if (m_Page == 1)
			gumpID--;
		Orion->DrawGump(gumpID, 0, 0, 111);

		//Language
		gumpID = 0x00DE;
		if (m_Page == 2)
			gumpID--;
		Orion->DrawGump(gumpID, 0, 0, 177);

		//Chat
		gumpID = 0x00E0;
		if (m_Page == 3)
			gumpID--;
		Orion->DrawGump(gumpID, 0, 0, 243);

		//Macro Options
		gumpID = 0x00ED;
		if (m_Page == 4)
			gumpID--;
		Orion->DrawGump(gumpID, 0, 0, 309);
		


		//Right page buttons

		//Interface
		gumpID = 0x00E2;
		if (m_Page == 5)
			gumpID--;
		Orion->DrawGump(gumpID, 0, 576, 45);

		//Display
		gumpID = 0x00E4;
		if (m_Page == 6)
			gumpID--;
		Orion->DrawGump(gumpID, 0, 576, 111);

		//Reputation System
		gumpID = 0x00E6;
		if (m_Page == 7)
			gumpID--;
		Orion->DrawGump(gumpID, 0, 576, 177);

		//Miscellaneous
		gumpID = 0x00E8;
		if (m_Page == 8)
			gumpID--;
		Orion->DrawGump(gumpID, 0, 576, 243);

		//Filter Options
		gumpID = 0x00EB;
		if (m_Page == 9)
			gumpID--;
		Orion->DrawGump(gumpID, 0, 576, 309);
		


		if (g_GumpPressedElement == ID_GO_CANCEL)
			gumpID = 0x00F1; //Cancel button (down)
		else if (g_GumpSelectElement == ID_GO_CANCEL)
			gumpID = 0x00F2; //Cancel button selected
		else
			gumpID = 0x00F3; //Cancel button
		Orion->DrawGump(gumpID, 0, 154, 405);
		
		if (g_GumpPressedElement == ID_GO_APPLY)
			gumpID = 0x00F0; //Apply button (down)
		else if (g_GumpSelectElement == ID_GO_APPLY)
			gumpID = 0x00EE; //Apply button selected
		else
			gumpID = 0x00EF; //Apply button
		Orion->DrawGump(gumpID, 0, 248, 405);
		
		if (g_GumpPressedElement == ID_GO_DEFAULT)
			gumpID = 0x00F4; //Default button (down)
		else if (g_GumpSelectElement == ID_GO_DEFAULT)
			gumpID = 0x00F5; //Default button selected
		else
			gumpID = 0x00F6; //Default button
		Orion->DrawGump(gumpID, 0, 346, 405);
		
		if (g_GumpPressedElement == ID_GO_OKAY)
			gumpID = 0x00F8; //Okay button (down)
		else if (g_GumpSelectElement == ID_GO_OKAY)
			gumpID = 0x00F7; //Okay button selected
		else
			gumpID = 0x00F9; //Okay button
		Orion->DrawGump(gumpID, 0, 443, 405);

		bool renderMode = true;

		switch (m_Page)
		{
			case 0:
			{
				DrawPage1(renderMode, index); //Sound and Music
				break;
			}
			case 1:
			{
				DrawPage2(renderMode, index); //Orion's configuration
				break;
			}
			case 2:
			{
				DrawPage3(renderMode, index); //Language
				break;
			}
			case 3:
			{
				DrawPage4(renderMode, index); //Chat
				break;
			}
			case 4:
			{
				DrawPage5(renderMode, index); //Macro Options
				break;
			}
			case 5:
			{
				DrawPage6(renderMode, index); //Interface
				break;
			}
			case 6:
			{
				DrawPage7(renderMode, index); //Display
				break;
			}
			case 7:
			{
				DrawPage8(renderMode, index); //Reputation System
				break;
			}
			case 8:
			{
				DrawPage9(renderMode, index); //Miscellaneous
				break;
			}
			case 9:
			{
				DrawPage10(renderMode, index); //Filter Options
				break;
			}
			default:
				break;
		}

	glEndList();

	m_FrameRedraw = true;
	m_FrameCreated = true;
}
//----------------------------------------------------------------------------
int TGumpOptions::Draw(bool &mode)
{
	DWORD index = (DWORD)this;

	CalculateGumpState();

	DWORD ticks = g_Ticks;

	if (m_LastChangeMacroTime < ticks)
	{
		if (g_GumpPressedElement == ID_GO_P5_BUTTON_PREVEOUS) //Preveous button
		{
			if (m_MacroPointer->m_Prev != NULL)
			{
				m_MacroPointer = (TMacro*)m_MacroPointer->m_Prev;
				m_MacroObjectPointer = (TMacroObject*)m_MacroPointer->m_Items;

				TextEntryMacro->SetText(m_HotkeyText[m_MacroPointer->Key & 0xFF]);
			}

			m_LastChangeMacroTime = ticks + CHANGE_MACRO_DELAY;
		}
		else if (g_GumpPressedElement == ID_GO_P5_BUTTON_NEXT) //Next button
		{
			if (m_MacroPointer->m_Next != NULL)
			{
				m_MacroPointer = (TMacro*)m_MacroPointer->m_Next;
				m_MacroObjectPointer = (TMacroObject*)m_MacroPointer->m_Items;

				TextEntryMacro->SetText(m_HotkeyText[m_MacroPointer->Key & 0xFF]);
			}

			m_LastChangeMacroTime = ticks + CHANGE_MACRO_DELAY;
		}
		else if (m_MacroSelection)
		{
			if (m_MacroListOffset && g_MouseY < (int)g_GumpTranslateY + m_MacroListOffsetYStart)
			{
				m_MacroListOffset -= m_MacroListMaxCount;
				m_LastChangeMacroTime = ticks + CHANGE_MACRO_LIST_DELAY;
			}
			else if ((m_MacroListOffset + m_MacroListMaxCount < m_MacroListCount) && g_MouseY >(int)g_GumpTranslateY + m_MacroListOffsetYEnd)
			{
				m_MacroListOffset += m_MacroListMaxCount;
				m_LastChangeMacroTime = ticks + CHANGE_MACRO_LIST_DELAY;
			}
		}
	}

	if (mode)
	{
		if (!m_FrameCreated || g_GumpSelectElement) // || g_GumpPressed
			GenerateFrame();
		else if (m_FrameRedraw)
		{
			GenerateFrame();
			m_FrameRedraw = false;
		}

		glTranslatef(g_GumpTranslateX, g_GumpTranslateY, 0.0f);

		glCallList((GLuint)index);

		glTranslatef(-g_GumpTranslateX, -g_GumpTranslateY, 0.0f);
	}
	else
	{
		int oldMouseX = g_MouseX;
		int oldMouseY = g_MouseY;
		g_MouseX -= (int)g_GumpTranslateX;
		g_MouseY -= (int)g_GumpTranslateY;

		int LSG = 0;

		if (Orion->ResizepicPixelsInXY(0x0A28, 40, 0, 550, 450)) //Body
		{
			g_LastSelectedObject = 0;
			g_LastSelectedGump = index;
		}



		//Left page buttons

		//Sound and Music
		WORD gumpID = 0x00DA;
		if (!m_Page)
			gumpID--;
		if (Orion->GumpPixelsInXY(gumpID, 0, 45))
			LSG = ID_GO_PAGE_0;

		//Orion's configuration
		gumpID = 0x00DC;
		if (m_Page == 1)
			gumpID--;
		if (Orion->GumpPixelsInXY(gumpID, 0, 111))
			LSG = ID_GO_PAGE_1;

		//Language
		gumpID = 0x00DE;
		if (m_Page == 2)
			gumpID--;
		if (Orion->GumpPixelsInXY(gumpID, 0, 177))
			LSG = ID_GO_PAGE_2;

		//Chat
		gumpID = 0x00E0;
		if (m_Page == 3)
			gumpID--;
		if (Orion->GumpPixelsInXY(gumpID, 0, 243))
			LSG = ID_GO_PAGE_3;

		//Macro Options
		gumpID = 0x00ED;
		if (m_Page == 4)
			gumpID--;
		if (Orion->GumpPixelsInXY(gumpID, 0, 309))
			LSG = ID_GO_PAGE_4;


		
		//Right page buttons

		//Interface
		gumpID = 0x00E2;
		if (m_Page == 5)
			gumpID--;
		if (Orion->GumpPixelsInXY(gumpID, 576, 45))
			LSG = ID_GO_PAGE_5;

		//Display
		gumpID = 0x00E4;
		if (m_Page == 6)
			gumpID--;
		if (Orion->GumpPixelsInXY(gumpID, 576, 111))
			LSG = ID_GO_PAGE_6;

		//Reputation System
		gumpID = 0x00E6;
		if (m_Page == 7)
			gumpID--;
		if (Orion->GumpPixelsInXY(gumpID, 576, 177))
			LSG = ID_GO_PAGE_7;

		//Miscellaneous
		gumpID = 0x00E8;
		if (m_Page == 8)
			gumpID--;
		if (Orion->GumpPixelsInXY(gumpID, 576, 243))
			LSG = ID_GO_PAGE_8;

		//Filter Options
		gumpID = 0x00EB;
		if (m_Page == 9)
			gumpID--;
		if (Orion->GumpPixelsInXY(gumpID, 576, 309))
			LSG = ID_GO_PAGE_9;
		

		 //Cancel button
		if (Orion->GumpPixelsInXY(0x00F3, 154, 405))
			LSG = ID_GO_CANCEL;

		 //Apply button
		if (Orion->GumpPixelsInXY(0x00EF, 248, 405))
			LSG = ID_GO_APPLY;

		 //Default button
		if (Orion->GumpPixelsInXY(0x00F6, 346, 405))
			LSG = ID_GO_DEFAULT;

		 //Okay button
		if (Orion->GumpPixelsInXY(0x00F9, 443, 405))
			LSG = ID_GO_OKAY;

		if (LSG != 0 || g_LastSelectedGump == index)
		{
			int oldLSG = LSG;

			switch (m_Page)
			{
				case 0:
					LSG = DrawPage1(mode, index); //Sound and Music
					break;
				case 1:
					LSG = DrawPage2(mode, index); //Orion's configuration
					break;
				case 2:
					LSG = DrawPage3(mode, index); //Language
					break;
				case 3:
					LSG = DrawPage4(mode, index); //Chat
					break;
				case 4:
					LSG = DrawPage5(mode, index); //Macro Options
					break;
				case 5:
					LSG = DrawPage6(mode, index); //Interface
					break;
				case 6:
					LSG = DrawPage7(mode, index); //Display
					break;
				case 7:
					LSG = DrawPage8(mode, index); //Reputation System
					break;
				case 8:
					LSG = DrawPage9(mode, index); //Miscellaneous
					break;
				case 9:
					LSG = DrawPage10(mode, index); //Filter Options
					break;
				default:
					break;
			}

			if (!LSG)
				LSG = oldLSG;
		}

		g_MouseX = oldMouseX;
		g_MouseY = oldMouseY;

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
int TGumpOptions::DrawPage1(bool &mode, DWORD &index)
{
	//Sound and Music
	if (mode)
	{
		if (g_GumpPressed)
		{
			if (g_LastObjectLeftMouseDown == ID_GO_P1_SOUND_VOLUME) //Sound volume slider pressed
			{
				int currentX = g_MouseX - (int)g_GumpTranslateX - 3; //������� ������� ��������

				if (currentX < 64)
					currentX = 64; //����� �� ���������� ������, ������������ �� �������
				else if (currentX > 152)
					currentX = 152; //����� �� ���������� ������, ������������ �� ��������
			
				int count = g_OptionsConfig.SoundVolume; //���������� ��������� � �����
				if (currentX > 64) //������� �������� ������ ��������
				{
					if (currentX < 152) //������� �������� ������ ���������, ���������
					{
						float ValPer = ((currentX - 64.0f) / g_SphereListWidth) * 100.0f;

						if (ValPer == 0.0f)
							count = 0;
						else
							count = (int)((255 * ValPer) / 100.0f);
					}
					else
						count = 255; //������� ����� ���������, ���������� �������� 255
				}
				else
					count = 0; //������� ����� ��������, ���������� �������� 0

				g_OptionsConfig.SoundVolume = count;
			}
			else if (g_LastObjectLeftMouseDown == ID_GO_P1_MUSIC_VOLUME) //Music volume slider pressed
			{
				int currentX = g_MouseX - (int)g_GumpTranslateX - 3; //������� ������� ��������

				if (currentX < 64)
					currentX = 64; //����� �� ���������� ������, ������������ �� �������
				else if (currentX > 152)
					currentX = 152; //����� �� ���������� ������, ������������ �� ��������
			
				int count = g_OptionsConfig.MusicVolume; //���������� ��������� � �����
				if (currentX > 64) //������� �������� ������ ��������
				{
					if (currentX < 152) //������� �������� ������ ���������, ���������
					{
						float ValPer = ((currentX - 64.0f) / g_SphereListWidth) * 100.0f;

						if (ValPer == 0.0f)
							count = 0;
						else
							count = (int)((255 * ValPer) / 100.0f);
					}
					else
						count = 255; //������� ����� ���������, ���������� �������� 255
				}
				else
					count = 0; //������� ����� ��������, ���������� �������� 0

				g_OptionsConfig.MusicVolume = count;
			}
		}

		//UO->DrawUnicodeFont(0, L"Sound and Music", g_OptionsTextColor, posX + 254, posY + 22);
		m_TexturePage1[0].Draw(84, 22);

		//UO->DrawUnicodeFontFixed(0, L"Sound and Music", 1, posX + 240, posY + 42, 100);
		//UO->DrawUnicodeFontCropped(0, L"Sound and Music", 1, posX + 240, posY + 62, 60);

		//UO->DrawUnicodeFont(0, L"These settings affect the sound and music you will hear while playing Ultima Online.", g_OptionsTextColor, posX + 64, posY + 44, 480.0f);
		m_TexturePage1[1].Draw(64, 44);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.Sound, 0, 64, 90);
		//UO->DrawUnicodeFont(0, L"Sound on/off", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage1[2].Draw(86, 90);

		//UO->DrawUnicodeFont(0, L"Sound volume", g_OptionsTextColor, posX + 64, posY + 22);
		m_TexturePage1[3].Draw(64, 112);
		
		Orion->DrawSphereGump(g_OptionsConfig.SoundVolume, 255.0f, 0, 133, 90);

		FontManager->DrawW(0, std::to_wstring(g_OptionsConfig.SoundVolume).c_str(), g_OptionsTextColor, 176, 130);
		


		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.Music, 0, 64, 151);
		//UO->DrawUnicodeFont(0, L"Music on/off", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage1[4].Draw(88, 151);

		//UO->DrawUnicodeFont(0, L"Music volume", g_OptionsTextColor, posX + 64, posY + 22);
		m_TexturePage1[5].Draw(64, 173);
		
		Orion->DrawSphereGump(g_OptionsConfig.MusicVolume, 255.0f, 0, 194, 90);

		FontManager->DrawW(0, std::to_wstring(g_OptionsConfig.MusicVolume).c_str(), g_OptionsTextColor, 176, 191);

		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.FootstepsSound, 0, 64, 212);
		//UO->DrawUnicodeFont(0, L"Play footstep sounds", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage1[6].Draw(86, 212);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.GetCombatMusic(), 0, 64, 232);
		//UO->DrawUnicodeFont(0, L"Play combat music", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage1[7].Draw(88, 232);
	}
	else
	{
		int LSG = 0;
		
		if (Orion->GumpPixelsInXY(0x00D2, 64, 90))
			LSG = ID_GO_P1_SOUND_ON_OFF; //Sound on/off
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 151))
			LSG = ID_GO_P1_MUSIC_ON_OFF; //Music on/off
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 212))
			LSG = ID_GO_P1_PLAY_FOOTSTEP_SOUNDS; //Play footstep sounds
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 232))
			LSG = ID_GO_P1_PLAY_COMBAT_MUSIC; //Play combat music
		else if (Orion->PolygonePixelsInXY(64, 130, (int)g_SphereListWidth + 10, 16))
			LSG = ID_GO_P1_SOUND_VOLUME; //Sound volume
		else if (Orion->PolygonePixelsInXY(64, 192, (int)g_SphereListWidth + 10, 16))
			LSG = ID_GO_P1_MUSIC_VOLUME; //Music volume

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
int TGumpOptions::DrawPage2(bool &mode, DWORD &index)
{
	//Orion's configuration
	if (mode)
	{
		if (g_GumpPressed)
		{
			if (g_LastObjectLeftMouseDown == ID_GO_P2_CLIENT_FPS) //FPS rate slider pressed
			{
				int currentX = g_MouseX - (int)g_GumpTranslateX - 3; //������� ������� ��������

				if (currentX < 64)
					currentX = 64; //����� �� ���������� ������, ������������ �� �������
				else if (currentX > 152)
					currentX = 152; //����� �� ���������� ������, ������������ �� ��������
			
				int count = g_OptionsConfig.ClientFPS - 16; //���������� ��������� � �����

				if (currentX > 64) //������� �������� ������ ��������
				{
					if (currentX < 152) //������� �������� ������ ���������, ���������
					{
						float ValPer = ((currentX - 64.0f) / g_SphereListWidth) * 100.0f;

						if (ValPer == 0.0f)
							count = 16;
						else
							count = (int)((48 * ValPer) / 100.0f) + 16;
					}
					else
						count = 64; //������� ����� ���������, ���������� �������� 64
				}
				else
					count = 16; //������� ����� ��������, ���������� �������� 16

				g_OptionsConfig.ClientFPS = count;
			}
		}

		m_TexturePage2[0].Draw(84, 22);
		
		m_TexturePage2[1].Draw(64, 44);
		
		m_TexturePage2[2].Draw(64, 90); //FPS rate:
		
		Orion->DrawSphereGump(g_OptionsConfig.GetClientFPS() - 16, 48.0f, 0, 111, 90);

		FontManager->DrawW(0, std::to_wstring(g_OptionsConfig.GetClientFPS()).c_str(), g_OptionsTextColor, 176, 108);
	}
	else
	{
		int LSG = 0;
		
		if (Orion->PolygonePixelsInXY(64, 109, (int)g_SphereListWidth + 10, 16))
			LSG = ID_GO_P2_CLIENT_FPS; //FPS rate:

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
int TGumpOptions::DrawPage3(bool &mode, DWORD &index)
{
	//Language
	if (mode)
	{
		if (g_GumpPressed)
		{
			if (g_LastObjectLeftMouseDown == ID_GO_P3_DELAY_BEFORE_TOOLTIP) //Delay befor Tool-tip appears slider pressed
			{
				int currentX = g_MouseX - (int)g_GumpTranslateX - 3; //������� ������� ��������

				if (currentX < 64)
					currentX = 64; //����� �� ���������� ������, ������������ �� �������
				else if (currentX > 152)
					currentX = 152; //����� �� ���������� ������, ������������ �� ��������
			
				WORD count = g_OptionsConfig.ToolTipsDelay; //���������� ��������� � �����
				if (currentX > 64) //������� �������� ������ ��������
				{
					if (currentX < 152) //������� �������� ������ ���������, ���������
					{
						float ValPer = ((currentX - 64.0f) / g_SphereListWidth) * 100.0f;

						if (ValPer == 0.0f)
							count = 0;
						else
							count = (int)(5000.0f * ValPer) / 100;
					}
					else
						count = 5000; //������� ����� ���������, ���������� �������� 255
				}
				else
					count = 0; //������� ����� ��������, ���������� �������� 0

				g_OptionsConfig.ToolTipsDelay = count;
			}
		}

		//UO->DrawUnicodeFont(0, L"Language", g_OptionsTextColor, posX + 280, posY + 22);
		m_TexturePage3[0].Draw(84, 22);
		
		//UO->DrawUnicodeFont(0, L"The language you use when playing UO is obtained from your Operating System settings.", g_OptionsTextColor, posX + 64, posY + 44, 480.0f);
		m_TexturePage3[1].Draw(64, 44);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.UseToolTips, 0, 64, 90);
		//UO->DrawUnicodeFont(0, L"Use Tool-tips", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage3[2].Draw(86, 90);

		//UO->DrawUnicodeFont(0, L"Delay befor Tool-tip appears", g_OptionsTextColor, posX + 64, posY + 22);
		m_TexturePage3[3].Draw(64, 112);
		
		Orion->DrawGump(0x00D5, 0, 64, 133); //Sphere line gump start
		Orion->DrawGump(0x00D7, 0, 152, 133); //Sphere line gump end
		Orion->DrawGump(0x00D6, 0, 77, 133, 75, 0); //Sphere line gump body

		float ValPer = (g_OptionsConfig.ToolTipsDelay / 5000.0f) * 100.0f;
		ValPer = (g_SphereListWidth * ValPer) / 100.0f;
		if (ValPer < 0.0f)
			ValPer = 0.0f;
		Orion->DrawGump(0x00D8, 0, 64 + (int)ValPer, 133); //Sphere gump

		FontManager->DrawW(0, std::to_wstring(g_OptionsConfig.ToolTipsDelay).c_str(), g_OptionsTextColor, 176, 130);
		


		Orion->DrawGump(0x00D4, 0, 64, 151);
		DWORD clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ToolTipsTextColor != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ToolTipsTextColor);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 154, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Color of Tool-tip text", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage3[4].Draw(88, 151);
		
		Orion->DrawGump(0x00D0, 0, 64, 173);
		//UO->DrawUnicodeFont(0, L"Font for Tool-tips", g_OptionsTextColor, posX + 64, posY + 22);
		m_TexturePage3[5].Draw(88, 173);
	}
	else
	{
		int LSG = 0;
		
		if (Orion->GumpPixelsInXY(0x00D2, 64, 90))
			LSG = ID_GO_P3_USE_TOOLTIP; //Use Tool-tips
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 151))
			LSG = ID_GO_P3_TEXT_COLOR; //Color of Tool-tip text
		else if (Orion->GumpPixelsInXY(0x00D0, 64, 173))
			LSG = ID_GO_P3_TEXT_FONT; //Font for Tool-tips
		else if (Orion->PolygonePixelsInXY(64, 130, (int)g_SphereListWidth + 10, 16))
			LSG = ID_GO_P3_DELAY_BEFORE_TOOLTIP; //Delay befor Tool-tip appears

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
int TGumpOptions::DrawPage4(bool &mode, DWORD &index)
{
	//Chat

	if (mode)
	{
		//UO->DrawUnicodeFont(0, L"Chat", g_OptionsTextColor, posX + 292, posY + 22);
		m_TexturePage4[0].Draw(84, 22);
		
		//UO->DrawUnicodeFont(0, L"These settings affect the interface display for the chat system.", g_OptionsTextColor, posX + 64, posY + 44, 480.0f);
		m_TexturePage4[1].Draw(64, 44);
		


		Orion->DrawGump(0x00D4, 0, 64, 90);
		DWORD clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorInputText != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorInputText);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 93, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Input text color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage4[2].Draw(88, 90);
		
		Orion->DrawGump(0x00D4, 0, 64, 109);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorMenuOption != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorMenuOption);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 112, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Menu option color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage4[3].Draw(88, 109);
		
		Orion->DrawGump(0x00D4, 0, 64, 128);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorPlayerInMemberList != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorPlayerInMemberList);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 131, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Player color in member list", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage4[3].Draw(88, 128);
		
		Orion->DrawGump(0x00D4, 0, 64, 147);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorText != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorText);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 150, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Chat text color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage4[5].Draw(88, 147);
		
		Orion->DrawGump(0x00D4, 0, 64, 166);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorPlayerNameWithout != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorPlayerNameWithout);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 169, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Player name without speaking privileges", g_OptionsTextColor, posX + 88, posY, 140);
		m_TexturePage4[6].Draw(88, 166);
		
		Orion->DrawGump(0x00D4, 0, 64, 201);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorMuted != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorMuted);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 204, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Muted text color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage4[7].Draw(88, 201);
		
		Orion->DrawGump(0x00D4, 0, 64, 220);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorChannelModeratorName != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorChannelModeratorName);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 223, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Channel moderator name", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage4[8].Draw(88, 220);
		
		Orion->DrawGump(0x00D4, 0, 64, 239);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorChannelModeratorText != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorChannelModeratorText);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 242, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Channel moderator text", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage4[9].Draw(88, 239);
		
		Orion->DrawGump(0x00D4, 0, 64, 258);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorMyName != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorMyName);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 261, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"My name's color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage4[10].Draw(88, 258);
		
		Orion->DrawGump(0x00D4, 0, 64, 277);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorMyText != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorMyText);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 280, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"My text color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage4[11].Draw(88, 277);
		
		Orion->DrawGump(0x00D4, 0, 64, 296);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorSystemMessage != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorSystemMessage);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 299, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"System message color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage4[12].Draw(88, 296);

		

		Orion->DrawGump(0x00D4, 0, 300, 90);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorBGOutputText != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorBGOutputText);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(303, 93, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Text Output Background Color", g_OptionsTextColor, posX + 324, posY);
		m_TexturePage4[13].Draw(324, 90);

		Orion->DrawGump(0x00D4, 0, 300, 109);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorBGInputText != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorBGInputText);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(303, 112, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Text Input Background Color", g_OptionsTextColor, posX + 324, posY);
		m_TexturePage4[14].Draw(324, 109);

		Orion->DrawGump(0x00D4, 0, 300, 128);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorBGUserList != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorBGUserList);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(303, 131, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"User List Background Color", g_OptionsTextColor, posX + 324, posY);
		m_TexturePage4[15].Draw(324, 128);

		Orion->DrawGump(0x00D4, 0, 300, 147);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorBGConfList != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorBGConfList);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(303, 150, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Conference List Background Color", g_OptionsTextColor, posX + 324, posY);
		m_TexturePage4[16].Draw(324, 147);

		Orion->DrawGump(0x00D4, 0, 300, 166);
		clr = 0xFF7F7F7F;
		if (g_OptionsConfig.ChatColorBGCommandList != 0xFFFF)
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.ChatColorBGCommandList);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(303, 169, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Command List Background Color", g_OptionsTextColor, posX + 324, posY);
		m_TexturePage4[17].Draw(324, 166);

		
		Orion->DrawGump(0x00D0, 0, 300, 192);
		//UO->DrawUnicodeFont(0, L"Chat font", g_OptionsTextColor, posX + 300, posY);
		m_TexturePage4[18].Draw(324, 192);
	}
	else
	{
		int LSG = 0;
		
		if (Orion->GumpPixelsInXY(0x00D2, 64, 90))
			LSG = ID_GO_P4_TEXT_COLOR; //Input text color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 109))
			LSG = ID_GO_P4_TEXT_COLOR + 1; //Menu option color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 128))
			LSG = ID_GO_P4_TEXT_COLOR + 2; //Player color in member list
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 147))
			LSG = ID_GO_P4_TEXT_COLOR + 3; //Chat text color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 166))
			LSG = ID_GO_P4_TEXT_COLOR + 4; //Player name without speaking privileges
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 201))
			LSG = ID_GO_P4_TEXT_COLOR + 5; //Muted text color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 220))
			LSG = ID_GO_P4_TEXT_COLOR + 6; //Channel moderator name
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 239))
			LSG = ID_GO_P4_TEXT_COLOR + 7; //Channel moderator text
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 258))
			LSG = ID_GO_P4_TEXT_COLOR + 8; //My name's color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 277))
			LSG = ID_GO_P4_TEXT_COLOR + 9; //My text color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 296))
			LSG = ID_GO_P4_TEXT_COLOR + 10; //System message color
		else if (Orion->GumpPixelsInXY(0x00D2, 300, 90))
			LSG = ID_GO_P4_TEXT_COLOR + 11; //Text Output Background Color
		else if (Orion->GumpPixelsInXY(0x00D2, 300, 109))
			LSG = ID_GO_P4_TEXT_COLOR + 12; //Text Input Background Color
		else if (Orion->GumpPixelsInXY(0x00D2, 300, 128))
			LSG = ID_GO_P4_TEXT_COLOR + 13; //User List Background Color
		else if (Orion->GumpPixelsInXY(0x00D2, 300, 147))
			LSG = ID_GO_P4_TEXT_COLOR + 14; //Conference List Background Color
		else if (Orion->GumpPixelsInXY(0x00D2, 300, 166))
			LSG = ID_GO_P4_TEXT_COLOR + 15; //Command List Background Color
		else if (Orion->GumpPixelsInXY(0x00D0, 300, 192))
			LSG = ID_GO_P4_TEXT_FONT; //Chat font

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
int TGumpOptions::DrawPage5(bool &mode, DWORD &index)
{
	const int maxMacroDraw = 7;

	int captionY = 22;
	int posY = captionY + 38;
	int posX = 30;

	//Macro Options
	if (mode)
	{
		bool alt = false;
		bool ctrl = false;
		bool shift = false;
		WORD key = 0;

		if (m_MacroPointer != NULL)
		{
			alt = m_MacroPointer->Alt;
			ctrl = m_MacroPointer->Ctrl;
			shift = m_MacroPointer->Shift;
			key = m_MacroPointer->Key;
		}

		m_TexturePage5[0].Draw(114, 22); //"Macro Options"
		
		//Add button
		WORD gumpID = 0x099C;
		if (g_GumpPressedElement == ID_GO_P5_BUTTON_ADD)
			gumpID++;
		else if (g_GumpSelectElement == ID_GO_P5_BUTTON_ADD)
			gumpID = 0x099E;

		Orion->DrawGump(gumpID, 0, posX + 152, 60);
		
		//Delete button
		if (g_GumpPressedElement == ID_GO_P5_BUTTON_DELETE)
			gumpID = 0x09A0;
		else
			gumpID = 0x099F + (int)((g_GumpSelectElement == ID_GO_P5_BUTTON_DELETE) ? 2 : 0);

		Orion->DrawGump(gumpID, 0, posX + 205, 60);
		
		//Preveous button
		if (g_GumpPressedElement == ID_GO_P5_BUTTON_PREVEOUS)
			gumpID = 0x09A3;
		else
			gumpID = 0x09A2 + (int)((g_GumpSelectElement == ID_GO_P5_BUTTON_PREVEOUS) ? 2 : 0);

		Orion->DrawGump(gumpID, 0, posX + 273, 60);
		
		//Next button
		if (g_GumpPressedElement == ID_GO_P5_BUTTON_NEXT)
			gumpID = 0x09A6;
		else
			gumpID = 0x09A5 + (int)((g_GumpSelectElement == ID_GO_P5_BUTTON_NEXT) ? 2 : 0);

		Orion->DrawGump(gumpID, 0, posX + 357, 60);
		
		m_TexturePage5[1].Draw(posX + 134, 82); //"Keystroke"
		
		//KeyBox
		Orion->DrawGump(0x098B, 0, posX + 133, 112);
		TextEntryMacro->DrawA(1, 0x0386, posX + 137, 117);
		
		m_TexturePage5[2].Draw(posX + 200, 111); //"Key"
		
		//Shift checkbox
		if (shift)
			gumpID = 0x0869;
		else
			gumpID = 0x0867 + (int)(g_GumpSelectElement == ID_GO_P5_BUTTON_SHIFT);

		Orion->DrawGump(gumpID, 0, posX + 248, 79);
		
		m_TexturePage5[3].Draw(posX + 280, 82); //"Shift"
		
		//Alt checkbox
		if (alt)
			gumpID = 0x0869;
		else
			gumpID = 0x0867 + (int)(g_GumpSelectElement == ID_GO_P5_BUTTON_ALT);

		Orion->DrawGump(gumpID, 0, posX + 248, 107);
		
		m_TexturePage5[4].Draw(posX + 280, 111); //"Alt"
		
		//Ctrl checkbox
		if (ctrl)
			gumpID = 0x0869;
		else
			gumpID = 0x0867 + (int)(g_GumpSelectElement == ID_GO_P5_BUTTON_CTRL);

		Orion->DrawGump(gumpID, 0, posX + 248, 135);
		
		m_TexturePage5[5].Draw(posX + 280, 140); //"Ctrl"
		
		posX += 134;

		m_TexturePage5[6].Draw(posX, 163); //"Actions"
		
		int boxPosY = posY + 127;
		int arrowPosY = posY + 133;
		bool drawEmptyBox = true;
		
		TMacroObject *obj = m_MacroObjectPointer;
		if (obj != NULL)
		{
			if (obj->m_Prev != NULL)
				Orion->DrawGump(0x0983 + (int)(g_GumpSelectElement == ID_GO_P5_BUTTON_UP), 0, posX + 292, posY + 113);
			
			int macroCount = 0;

			while (obj != NULL && macroCount < maxMacroDraw)
			{
				Orion->DrawGump(0x098D, 0, posX, boxPosY);
				FontManager->DrawA(1, TMacro::GetActionName(obj->Code), 0x0386, posX + 4, boxPosY + 5, 98, TS_CENTER, UOFONT_FIXED);
				Orion->DrawGump(0x0985, 0, posX + 94, arrowPosY);

				char hasMenu = obj->HasSubMenu;
				if (hasMenu)
				{
					Orion->DrawGump(0x098E, 0, posX + 112, boxPosY);

					if (hasMenu == 1) //����� ��������� ����
					{
						Orion->DrawGump(0x0985, 0, posX + 274, arrowPosY);
						
						FontManager->DrawA(1, TMacro::GetAction(obj->SubCode), 0x0386, posX + 118, boxPosY + 5, 150, TS_LEFT, UOFONT_FIXED);
					}
					else
					{
						g_GL.Scissor((int)g_GumpTranslateX + posX + 118, (int)g_GumpTranslateY + boxPosY + 5, 150, 20);

						((TMacroObjectEntry*)obj)->TextEntry->DrawA(1, 0x0386, posX + 118, boxPosY + 5, TS_LEFT, UOFONT_FIXED);

						glDisable(GL_SCISSOR_TEST);
					}
				}

				boxPosY += 26;
				arrowPosY += 26;
				macroCount++;

				if (obj->m_Next == NULL)
					break;

				obj = (TMacroObject*)obj->m_Next;
			}
			
			if (macroCount >= maxMacroDraw)
			{
				drawEmptyBox = false;
				Orion->DrawGump(0x0985 + (int)(g_GumpSelectElement == ID_GO_P5_BUTTON_DOWN), 0, posX + 292, boxPosY);
			}
			else if (obj->Code == MC_NONE)
				drawEmptyBox = false;
		}

		if (drawEmptyBox)
		{
			Orion->DrawGump(0x098D, 0, posX, boxPosY);
			Orion->DrawGump(0x0985, 0, posX + 94, arrowPosY);
		}

		if (m_MacroSelection)
		{
			bool isAction = false;
			if (m_MacroSelection == 0x20000000) //Action
			{
				posX += 116;
				isAction = true;
			}

			int textIndex = m_MacroListOffset;

			posY -= 60;
			posY += m_MacroListOffsetYStart;
				
			//Top
			Orion->DrawGump(0x09B5, 0, posX - 5, posY - 11);

			if (textIndex > 0)
				Orion->DrawGump(0x0983, 0, posX + 85, posY - 8);
				
			int ofs = 0;

			int count = m_MacroListMaxCount;

			if (count > m_MacroListCount)
				count = m_MacroListCount;

			IFOR(i, 0, count)
			{
				gumpID = 0x09B6 + ofs;
				ofs = (ofs + 1) % 3;

				int itemPosY = posY + (i * 15);

				Orion->DrawGump(gumpID, 0, posX, itemPosY);
				
				int textNameIndex = textIndex + m_MacroListNameOffset;

				if (textIndex < m_MacroListCount)
				{
					if (g_GumpSelectElement >= ID_GO_P5_SELECTION)
					{
						if (textNameIndex == (g_GumpSelectElement - ID_GO_P5_SELECTION))
							g_GL.DrawPolygone(posX + 4, itemPosY, 150, 14);
					}

					if (isAction) //Action
					{
						if (textNameIndex < 210)
						{
							FontManager->DrawA(1, TMacro::GetAction(textNameIndex), 0x0386, posX + 4, itemPosY);
							textIndex++;
						}
					}
					else //Action name
					{
						if (textNameIndex < 60)
						{
							FontManager->DrawA(1, TMacro::GetActionName(textNameIndex), 0x0386, posX + 4, itemPosY);
							textIndex++;
						}
					}
				}
			}

			int offsBottomY = (m_MacroListOffsetYEnd - m_MacroListOffsetYStart);

			//Bottom
			Orion->DrawGump(0x09B9, 0, posX - 5, posY + offsBottomY);

			if (m_MacroListOffset + m_MacroListMaxCount < m_MacroListCount)
				Orion->DrawGump(0x0985, 0, posX + 85, posY + offsBottomY - 2);
		}
	}
	else
	{
		int LSG = 0;
		
		if (Orion->GumpPixelsInXY(0x099C, posX + 152, posY))
			LSG = ID_GO_P5_BUTTON_ADD; //Add
		else if (Orion->GumpPixelsInXY(0x099F, posX + 205, posY))
			LSG = ID_GO_P5_BUTTON_DELETE; //Delete
		else if (Orion->GumpPixelsInXY(0x09A2, posX + 273, posY))
			LSG = ID_GO_P5_BUTTON_PREVEOUS; //Preveous
		else if (Orion->GumpPixelsInXY(0x09A5, posX + 357, posY))
			LSG = ID_GO_P5_BUTTON_NEXT; //Next
		else if (Orion->GumpPixelsInXY(0x098B, posX + 133, posY + 52))
			LSG = ID_GO_P5_KEY_BOX; //Key box
		else if (Orion->GumpPixelsInXY(0x0867, posX + 248, posY + 19))
			LSG = ID_GO_P5_BUTTON_SHIFT; //Shift
		else if (Orion->GumpPixelsInXY(0x0867, posX + 248, posY + 47))
			LSG = ID_GO_P5_BUTTON_ALT; //Shift
		else if (Orion->GumpPixelsInXY(0x0867, posX + 248, posY + 75))
			LSG = ID_GO_P5_BUTTON_CTRL; //Shift

		posX += 134;

		int boxPosY = posY + 127;
		int arrowPosY = posY + 133;
		bool drawEmptyBox = true;
		
		TMacroObject *obj = m_MacroObjectPointer;
		if (obj != NULL)
		{
			if (obj->m_Prev != NULL && Orion->GumpPixelsInXY(0x0983, posX + 292, posY + 113))
				LSG = ID_GO_P5_BUTTON_UP; //UP arrow
			
			int macroCount = 0;

			while (obj != NULL && macroCount < maxMacroDraw)
			{
				if (Orion->GumpPixelsInXY(0x098D, posX, boxPosY))
					LSG = ID_GO_P5_LEFT_BOX + macroCount; //Left macro box

				char hasMenu = obj->HasSubMenu;
				if (hasMenu)
				{
					if (Orion->GumpPixelsInXY(0x098E, posX + 112, boxPosY))
						LSG = ID_GO_P5_RIGHT_BOX + macroCount; //Right macro box
				}

				boxPosY += 26;
				arrowPosY += 26;
				macroCount++;
					
				if (obj->m_Next == NULL)
					break;

				obj = (TMacroObject*)obj->m_Next;
			}
			
			if (macroCount >= maxMacroDraw)
			{
				drawEmptyBox = false;

				if (Orion->GumpPixelsInXY(0x0985, posX + 292, boxPosY))
					LSG = ID_GO_P5_BUTTON_DOWN; //Down arrow
			}
			else if (obj->Code == MC_NONE)
				drawEmptyBox = false;

			if (macroCount >= maxMacroDraw || obj->Code == MC_NONE)
				drawEmptyBox = false;
		}

		if (drawEmptyBox)
		{
			if (Orion->GumpPixelsInXY(0x098D, posX, boxPosY))
				LSG = ID_GO_P5_EMPTY_BOX; //Empty macro box
		}

		if (m_MacroSelection)
		{
			bool isAction = false;
			if (m_MacroSelection == 0x20000000) //Action
			{
				posX += 116;
				isAction = true;
			}

			int textIndex = m_MacroListOffset;

			posY -= 60;
			posY += m_MacroListOffsetYStart;
				
			int ofs = 0;

			int count = m_MacroListMaxCount;

			if (count > m_MacroListCount)
				count = m_MacroListCount;

			IFOR(i, 0, count)
			{
				if (Orion->GumpPixelsInXY(0x09B6 + ofs, posX, posY + (i * 15)))
					LSG = ID_GO_P5_SELECTION + textIndex + m_MacroListNameOffset;
					
				ofs = (ofs + 1) % 3;
				textIndex++;
			}
		}

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
int TGumpOptions::DrawPage6(bool &mode, DWORD &index)
{
	//Interface
	if (mode)
	{
		//UO->DrawUnicodeFont(0, L"Interface", g_OptionsTextColor, posX + 276, posY + 22);
		m_TexturePage6[0].Draw(84, 22);
		
		//UO->DrawUnicodeFont(0, L"These options affect your interface.", g_OptionsTextColor, posX + 64, posY + 44, 480.0f);
		m_TexturePage6[1].Draw(64, 44);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.EnablePathfind, 0, 64, 90);
		//UO->DrawUnicodeFont(0, L"Enable pathfinding with double-right-click", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[2].Draw(86, 90);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.HoldTabForCombat, 0, 64, 110);
		//UO->DrawUnicodeFont(0, L"Hold down TAB key for combat, instead of tapping it to toggle combat mode", g_OptionsTextColor, posX + 86, posY, 450);
		m_TexturePage6[3].Draw(86, 110);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.OffsetInterfaceWindows, 0, 64, 146);
		//UO->DrawUnicodeFont(0, L"Offset interface windows rather than perfectly stacking them", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[4].Draw(86, 146);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.AutoArrange, 0, 64, 166);
		//UO->DrawUnicodeFont(0, L"Automatically arrange minimized windows", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[5].Draw(86, 166);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.AlwaysRun, 0, 64, 186);
		//UO->DrawUnicodeFont(0, L"Your character will always run if this is checked", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[6].Draw(86, 186);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.DisableMenubar, 0, 64, 206);
		//UO->DrawUnicodeFont(0, L"Disable the Menu Bar", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[7].Draw(86, 206);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.GrayOutOfRangeObjects, 0, 64, 226);
		//UO->DrawUnicodeFont(0, L"Gray out of range objects", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[8].Draw(86, 226);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.DisableNewTargetSystem, 0, 64, 246);
		//UO->DrawUnicodeFont(0, L"Disable New Target System", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[9].Draw(86, 246);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.ObjectHandles, 0, 64, 266);
		//UO->DrawUnicodeFont(0, L"Object Handles", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[10].Draw(86, 266);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.GetReduceFPSUnactiveWindow(), 0, 64, 286);
		//UO->DrawUnicodeFont(0, L"Reduce FPS when Window is Unactive", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[11].Draw(86, 286);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.ItemPropertiesIcon, 0, 64, 306);
		//UO->DrawUnicodeFont(0, L"Display Item Properties Icon", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[12].Draw(86, 306);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.HoldShiftForContextMenus, 0, 64, 326);
		//UO->DrawUnicodeFont(0, L"Hold Shift For Context Menus", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[13].Draw(86, 326);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.HoldShiftForEnablePathfind, 0, 64, 346);
		//UO->DrawUnicodeFont(0, L"Hold Shift For Enable Pathfinding", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage6[14].Draw(86, 346);
	}
	else
	{
		int LSG = 0;
		
		if (Orion->GumpPixelsInXY(0x00D2, 64, 90))
			LSG = ID_GO_P6_ENABLE_PATHFINDING; //Enable pathfinding with double-right-click
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 110))
			LSG = ID_GO_P6_HOLD_TAB_FOR_COMBAT; //Hold down TAB key for combat, instead of tapping it to toggle combat mode
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 146))
			LSG = ID_GO_P6_OFFSET_INTERFACE_WINDOWS; //Offset interface windows rather than perfectly stacking them
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 166))
			LSG = ID_GO_P6_AUTO_ARRANGE_MINIMIZED_WINDOWS; //Automatically arrange minimized windows
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 186))
			LSG = ID_GO_P6_ALWAYS_RUN; //Your character will always run if this is checked
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 206))
			LSG = ID_GO_P6_DISABLE_MENUBAR; //Disable the Menu Bar
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 226))
			LSG = ID_GO_P6_GRAY_OUT_OF_RANGE_OBJECTS; //Gray out of range objects
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 246))
			LSG = ID_GO_P6_DISABLE_NEW_TARGET_SYSTEM; //Disable New Target System
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 266))
			LSG = ID_GO_P6_OBJECT_HANDLES; //Object Handles
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 286))
			LSG = ID_GO_P6_REDUCE_FPS_UNACTIVE_WINDOW; //Reduce FPS when Window is Unactive
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 306))
			LSG = ID_GO_P6_DISPLAY_ITEM_PROPERTIES_ICON; //Display Item Properties Icon
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 326))
			LSG = ID_GO_P6_HOLD_SHIFT_FOR_CONTEXT_MENUS; //Hold Shift For Context Menus
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 346))
			LSG = ID_GO_P6_HOLD_SHIFT_FOR_ENABLE_PATHFINDING; //Hold Shift For Enable Pathfinding
		
		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
int TGumpOptions::DrawPage7(bool &mode, DWORD &index)
{
	//Display
	if (mode)
	{
		if (g_GumpPressed)
		{
			if (g_LastObjectLeftMouseDown == ID_GO_P7_AJUST_LONG_SPEECH) //Adjust how long speech remains on screen slider pressed
			{
				int currentX = g_MouseX - (int)g_GumpTranslateX - 3; //������� ������� ��������

				if (currentX < 64)
					currentX = 64; //����� �� ���������� ������, ������������ �� �������
				else if (currentX > 152)
					currentX = 152; //����� �� ���������� ������, ������������ �� ��������
			
				int count = g_OptionsConfig.SpeechDelay; //���������� ��������� � �����
				if (currentX > 64) //������� �������� ������ ��������
				{
					if (currentX < 152) //������� �������� ������ ���������, ���������
					{
						float ValPer = ((currentX - 64.0f) / g_SphereListWidth) * 100.0f;

						if (ValPer == 0.0f)
							count = 0;
						else
							count = (int)(999.0f * ValPer) / 100;

						if (count < 10)
							count = 10;
					}
					else
						count = 999; //������� ����� ���������, ���������� �������� 255
				}
				else
					count = 10; //������� ����� ��������, ���������� �������� 0

				g_OptionsConfig.SpeechDelay = count;
			}
		}

		//UO->DrawUnicodeFont(0, L"Display", g_OptionsTextColor, posX + 276, posY + 22);
		m_TexturePage7[0].Draw(84, 22);
		
		//UO->DrawUnicodeFont(0, L"These options affect your display, and adjusting some of them may improve your graphics performance.", g_OptionsTextColor, posX + 64, posY + 44, 480.0f);
		m_TexturePage7[1].Draw(64, 44);
		
		//UO->DrawUnicodeFont(0, L"Game Play Window Size", g_OptionsTextColor, posX + 64, posY);
		m_TexturePage7[2].Draw(64, 90);
		
		Orion->DrawResizepicGump(0x0BB8, 64, 112, 60, 22); //X field
		FontManager->DrawW(0, L"x", g_OptionsTextColor, 126, 112);
		Orion->DrawResizepicGump(0x0BB8, 139, 112, 60, 22); //Y field

		TextEntryGameSizeX->DrawW(0, g_OptionsTextColor, 68, 114);

		TextEntryGameSizeY->DrawW(0, g_OptionsTextColor, 143, 114);

		//UO->DrawUnicodeFont(0, L"Adjust how long speech remains on screen", g_OptionsTextColor, posX + 64, posY + 26);
		m_TexturePage7[3].Draw(64, 140);
		
		Orion->DrawGump(0x00D5, 0, 64, 160); //Sphere line gump start
		Orion->DrawGump(0x00D7, 0, 152, 160); //Sphere line gump end
		Orion->DrawGump(0x00D6, 0, 77, 160, 75, 0); //Sphere line gump body

		float ValPer = (g_OptionsConfig.SpeechDelay / 999.0f) * 100.0f;
		ValPer = (g_SphereListWidth * ValPer) / 100.0f;
		if (ValPer < 0.0f)
			ValPer = 0.0f;
		Orion->DrawGump(0x00D8, 0, 64 + (int)ValPer, 160); //Sphere gump

		FontManager->DrawW(0, std::to_wstring(g_OptionsConfig.SpeechDelay).c_str(), g_OptionsTextColor, 176, 157);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.GetScaleSpeechDelay(), 0, 64, 182);
		//UO->DrawUnicodeFont(0, L"Scale speech duration based on length", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage7[4].Draw(86, 182);
		
		Orion->DrawGump(0x00D4, 0, 64, 204);
		DWORD clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.SpeechColor);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 207, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Speech color", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage7[5].Draw(86, 204);
		
		Orion->DrawGump(0x00D4, 0, 64, 223);
		clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.EmoteColor);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 226, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Emote color", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage7[6].Draw(86, 223);
		
		Orion->DrawGump(0x00D4, 0, 64, 242);
		clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.PartyMessageColor);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 245, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Party Message color", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage7[7].Draw(86, 242);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.DarkNights, 0, 64, 264);
		//UO->DrawUnicodeFont(0, L"Dark Nights", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage7[12].Draw(86, 264);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.ColoredLighting, 0, 64, 284);
		//UO->DrawUnicodeFont(0, L"Colored Lighting", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage7[13].Draw(86, 284);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.StandartCharactersAnimationDelay, 0, 64, 304);
		//UO->DrawUnicodeFont(0, L"Standard characters animation delay", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage7[14].Draw(86, 304);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.StandartItemsAnimationDelay, 0, 64, 324);
		//UO->DrawUnicodeFont(0, L"Standard items animation delay", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage7[15].Draw(86, 324);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.LockResizingGameWindow, 0, 64, 344);
		//UO->DrawUnicodeFont(0, L"Lock game window resizing", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage7[16].Draw(86, 344);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.LockGumpsMoving, 0, 64, 364);
		//UO->DrawUnicodeFont(0, L"Lock gumps moving", g_OptionsTextColor, posX + 86, posY);
		m_TexturePage7[17].Draw(86, 364);

		if (ConnectionManager.ClientVersion >= CV_6000)
		{
			Orion->DrawGump(0x00D4, 0, 354, 204);
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.GuildMessageColor);
			glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
			g_GL.DrawPolygone(357, 207, 13, 14);
			glColor3f(1.0f, 1.0f, 1.0f);
			//UO->DrawUnicodeFont(0, L"Guild Message Color", g_OptionsTextColor, posX + 86, posY);
			m_TexturePage7[8].Draw(376, 204);
		
			Orion->DrawGump(0x00D4, 0, 354, 223);
			clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.AllianceMessageColor);
			glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
			g_GL.DrawPolygone(357, 226, 13, 14);
			glColor3f(1.0f, 1.0f, 1.0f);
			//UO->DrawUnicodeFont(0, L"Alliance Message Color", g_OptionsTextColor, posX + 86, posY);
			m_TexturePage7[9].Draw(376, 223);
			
			Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.IgnoreGuildMessage, 0, 354, 245);
			//UO->DrawUnicodeFont(0, L"Ignore Guild Messages", g_OptionsTextColor, posX + 86, posY);
			m_TexturePage7[10].Draw(376, 245);

			Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.IgnoreAllianceMessage, 0, 354, 265);
			//UO->DrawUnicodeFont(0, L"Ignore Alliance Messages", g_OptionsTextColor, posX + 86, posY);
			m_TexturePage7[11].Draw(376, 265);
		}
	}
	else
	{
		int LSG = 0;
		
		if (Orion->GumpPixelsInXY(0x00D2, 64, 182))
			LSG = ID_GO_P7_SCALE_SPEECH_DURATION; //Scale speech duration based on length
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 204))
			LSG = ID_GO_P7_SPEECH_COLOR; //Speech color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 223))
			LSG = ID_GO_P7_EMOTE_COLOR; //Emote color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 242))
			LSG = ID_GO_P7_PARTY_MESSAGE_COLOR; //Party Message color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 264))
			LSG = ID_GO_P7_DARK_NIGHTS; //Dark Nights
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 284))
			LSG = ID_GO_P7_COLORED_LIGHTING; //Colored Lighting
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 304))
			LSG = ID_GO_P7_CHARACTERS_ANIMATION_DELAY; //Standard characters animation delay
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 324))
			LSG = ID_GO_P7_ITEMS_ANIMATION_DELAY; //Standard items animation delay
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 344))
			LSG = ID_GO_P7_LOCK_GAME_WINDOW_RESIZING; //Lock game window resizing
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 364))
			LSG = ID_GO_P7_LOCK_GUMP_MOVING; //Lock gump moving
		else if (Orion->PolygonePixelsInXY(64, 160, (int)g_SphereListWidth + 10, 16))
			LSG = ID_GO_P7_AJUST_LONG_SPEECH; //Adjust how long speech remains on screen
		else if (Orion->PolygonePixelsInXY(64, 112, 60, 22))
			LSG = ID_GO_P7_GAME_WINDOW_SIZE_X; //Game Play Window Size X
		else if (Orion->PolygonePixelsInXY(139, 112, 60, 22))
			LSG = ID_GO_P7_GAME_WINDOW_SIZE_Y; //Game Play Window Size Y
		else if (ConnectionManager.ClientVersion >= CV_6000)
		{
			if (Orion->GumpPixelsInXY(0x00D2, 354, 204))
				LSG = ID_GO_P7_GUILD_MESSAGE_COLOR; //Guild Message Color
			else if (Orion->GumpPixelsInXY(0x00D2, 354, 223))
				LSG = ID_GO_P7_ALLIANCE_MESSAGE_COLOR; //Alliance Message Color
			else if (Orion->GumpPixelsInXY(0x00D2, 354, 245))
				LSG = ID_GO_P7_IGNORE_GUILD_MESSAGE; //Ignore Guild Messages
			else if (Orion->GumpPixelsInXY(0x00D2, 354, 265))
				LSG = ID_GO_P7_IGNORE_ALLIANCE_MESSAGE; //Ignore Alliance Messages
		}

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
int TGumpOptions::DrawPage8(bool &mode, DWORD &index)
{
	//Reputation System

	if (mode)
	{
		//UO->DrawUnicodeFont(0, L"Reputation System", g_OptionsTextColor, posX + 246, posY + 22);
		m_TexturePage8[0].Draw(84, 22);
		
		//UO->DrawUnicodeFont(0, L"These settings affect the reputation system, which is Ultima Online's system for controlling antisocial behavior.", g_OptionsTextColor, posX + 64, posY + 44, 480.0f);
		m_TexturePage8[1].Draw(64, 44);
		
		Orion->DrawGump(0x00D4, 0, 64, 90);
		DWORD clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.InnocentColor);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 93, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Innocent highlight color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage8[2].Draw(88, 90);
		
		Orion->DrawGump(0x00D4, 0, 64, 109);
		clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.FriendlyColor);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 112, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Friendly guilds highlight color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage8[3].Draw(88, 109);
		
		Orion->DrawGump(0x00D4, 0, 64, 128);
		clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.SomeoneColor);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 131, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Someone that can be attacked color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage8[4].Draw(88, 128);
		
		Orion->DrawGump(0x00D4, 0, 64, 147);
		clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.CriminalColor);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 150, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Criminal highlight color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage8[5].Draw(88, 147);
		
		Orion->DrawGump(0x00D4, 0, 64, 166);
		clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.EnemyColor);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 169, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Enemy guildmembers color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage8[6].Draw(88, 166);
		
		Orion->DrawGump(0x00D4, 0, 64, 185);
		clr = ColorManager->GetPolygoneColor(5, g_OptionsConfig.MurdererColor);
		glColor3ub((GetRValue(clr)), GetGValue(clr), GetBValue(clr));
		g_GL.DrawPolygone(67, 188, 13, 14);
		glColor3f(1.0f, 1.0f, 1.0f);
		//UO->DrawUnicodeFont(0, L"Murderer highlight color", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage8[7].Draw(88, 185);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.CriminalActionsQuery, 0, 64, 204);
		//UO->DrawUnicodeFont(0, L"Query before performing criminal actions", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage8[8].Draw(88, 204);
	}
	else
	{
		int LSG = 0;
		
		if (Orion->GumpPixelsInXY(0x00D2, 64, 90))
			LSG = ID_GO_P8_INNOCENT_COLOR; //Innocent highlight color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 109))
			LSG = ID_GO_P8_FRIENDLY_COLOR; //Friendly guilds highlight color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 128))
			LSG = ID_GO_P8_SOMEONE_COLOR; //Someone that can be attacked color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 147))
			LSG = ID_GO_P8_CRIMINAL_COLOR; //Criminal highlight color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 166))
			LSG = ID_GO_P8_ENEMY_COLOR; //Enemy guildmembers color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 185))
			LSG = ID_GO_P8_MURDERER_COLOR; //Murderer highlight color
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 204))
			LSG = ID_GO_P8_QUERY_CRIMINAL_ACTIONS; //Query before performing criminal actions

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
int TGumpOptions::DrawPage9(bool &mode, DWORD &index)
{
	//Miscellaneous
	if (mode)
	{
		if (g_GumpPressed)
		{
			if (g_LastObjectLeftMouseDown == ID_GO_P9_TRANSPARENCY_RADIUS) //Set radius of transparency circle slider pressed
			{
				int currentX = g_MouseX - (int)g_GumpTranslateX - 3; //������� ������� ��������

				if (currentX < 64)
					currentX = 64; //����� �� ���������� ������, ������������ �� �������
				else if (currentX > 152)
					currentX = 152; //����� �� ���������� ������, ������������ �� ��������
			
				int count = g_OptionsConfig.CircleTransRadius; //���������� ��������� � �����
				if (currentX > 64) //������� �������� ������ ��������
				{
					if (currentX < 152) //������� �������� ������ ���������, ���������
					{
						float ValPer = ((currentX - 64.0f) / g_SphereListWidth) * 100.0f;

						if (ValPer == 0.0f)
							count = 0;
						else
							count = (int)(200.0f * ValPer) / 100;
					}
					else
						count = 200; //������� ����� ���������, ���������� �������� 255
				}
				else
					count = 0; //������� ����� ��������, ���������� �������� 0

				g_OptionsConfig.CircleTransRadius = count;
			}
			else if (g_LastObjectLeftMouseDown == ID_GO_P9_INFORM_SKILLS) //Inform me when my skills improve this much (in tenths) slider pressed
			{
				int currentX = g_MouseX - (int)g_GumpTranslateX - 3; //������� ������� ��������

				if (currentX < 64)
					currentX = 64; //����� �� ���������� ������, ������������ �� �������
				else if (currentX > 152)
					currentX = 152; //����� �� ���������� ������, ������������ �� ��������
			
				int count = g_OptionsConfig.SkillReport; //���������� ��������� � �����
				if (currentX > 64) //������� �������� ������ ��������
				{
					if (currentX < 152) //������� �������� ������ ���������, ���������
					{
						float ValPer = ((currentX - 64.0f) / g_SphereListWidth) * 100.0f;

						if (ValPer == 0.0f)
							count = 0;
						else
							count = (int)(100.0f * ValPer) / 100;
					}
					else
						count = 100; //������� ����� ���������, ���������� �������� 255
				}
				else
					count = 0; //������� ����� ��������, ���������� �������� 0

				g_OptionsConfig.SkillReport = count;
			}
		}

		//UO->DrawUnicodeFont(0, L"Miscellaneous", g_OptionsTextColor, posX + 266, posY + 22);
		m_TexturePage9[0].Draw(84, 22);
		
		//UO->DrawUnicodeFont(0, L"Miscellaneous options.", g_OptionsTextColor, posX + 64, posY + 44);
		m_TexturePage9[1].Draw(64, 44);
		
		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.ShowIncomingNames, 0, 64, 90);
		//UO->DrawUnicodeFont(0, L"Show Names of Approaching Players", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage9[2].Draw(88, 90);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.UseCircleTrans, 0, 64, 110);
		//UO->DrawUnicodeFont(0, L"Use circle of transparency", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage9[3].Draw(88, 110);
		
		//UO->DrawUnicodeFont(0, L"Set radius of transparency circle", g_OptionsTextColor, posX + 64, posY + 22);
		m_TexturePage9[4].Draw(64, 132);
		
		Orion->DrawGump(0x00D5, 0, 64, 153); //Sphere line gump start
		Orion->DrawGump(0x00D7, 0, 152, 153); //Sphere line gump end
		Orion->DrawGump(0x00D6, 0, 77, 153, 75, 0); //Sphere line gump body

		float ValPer = (g_OptionsConfig.CircleTransRadius / 200.0f) * 100.0f;
		ValPer = (g_SphereListWidth * ValPer) / 100.0f;
		if (ValPer < 0.0f)
			ValPer = 0.0f;
		Orion->DrawGump(0x00D8, 0, 64 + (int)ValPer, 153); //Sphere gump

		FontManager->DrawW(0, std::to_wstring(g_OptionsConfig.CircleTransRadius).c_str(), g_OptionsTextColor, 176, 150);
		


		//UO->DrawUnicodeFont(0, L"Inform me when my skills improve this much (in tenths)", g_OptionsTextColor, posX + 64, posY + 22);
		m_TexturePage9[5].Draw(64, 175);
		
		Orion->DrawGump(0x00D5, 0, 64, 196); //Sphere line gump start
		Orion->DrawGump(0x00D7, 0, 152, 196); //Sphere line gump end
		Orion->DrawGump(0x00D6, 0, 77, 196, 75, 0); //Sphere line gump body
		
		ValPer = (g_OptionsConfig.SkillReport / 100.0f) * 100.0f;
		ValPer = (g_SphereListWidth * ValPer) / 100.0f;
		if (ValPer < 0)
			ValPer = 0;
		Orion->DrawGump(0x00D8, 0, 64 + (int)ValPer, 196); //Sphere gump

		FontManager->DrawW(0, std::to_wstring(g_OptionsConfig.SkillReport).c_str(), g_OptionsTextColor, 176, 193);
		
		

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.StatReport, 0, 64, 216);
		//UO->DrawUnicodeFont(0, L"Inform me of increases in strength, dexterity, and intelligence.", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage9[6].Draw(88, 216);

		Orion->DrawGump(0x00D2 + (int)g_OptionsConfig.GetConsoleNeedEnter(), 0, 64, 236);
		//UO->DrawUnicodeFont(0, L"Console need press 'Enter' to activate it.", g_OptionsTextColor, posX + 88, posY);
		m_TexturePage9[7].Draw(88, 236);
		



		Orion->DrawGump(0x00D0, 0, 64, 262);
		//UO->DrawUnicodeFont(0, L"Set the font for speech", g_OptionsTextColor, posX + 64, posY + 22);
		m_TexturePage9[8].Draw(88, 262);
	}
	else
	{
		int LSG = 0;
		
		if (Orion->GumpPixelsInXY(0x00D2, 64, 90))
			LSG = ID_GO_P9_SHOW_APPROACHING_NAMES; //Show Names of Approaching Players
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 110))
			LSG = ID_GO_P9_USE_CIRCLE_OF_TRANSPARENCY; //Use circle of transparency
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 216))
			LSG = ID_GO_P9_INFORM_STATS; //Inform me of increases in strength, dexterity, and intelligence.
		else if (Orion->GumpPixelsInXY(0x00D2, 64, 236))
			LSG = ID_GO_P9_CONSOLE_ENTER; //Console need press 'Enter' to activate it.
		else if (Orion->GumpPixelsInXY(0x00D0, 64, 262))
			LSG = ID_GO_P9_SPEECH_FONT; //Set the font for speech
		else if (Orion->PolygonePixelsInXY(64, 145, (int)g_SphereListWidth + 10, 16))
			LSG = ID_GO_P9_TRANSPARENCY_RADIUS; //Set radius of transparency circle
		else if (Orion->PolygonePixelsInXY(64, 188, (int)g_SphereListWidth + 10, 16))
			LSG = ID_GO_P9_INFORM_SKILLS; //Inform me when my skills improve this much (in tenths)

		return LSG;
	}

	return 0;
}
//----------------------------------------------------------------------------
int TGumpOptions::DrawPage10(bool &mode, DWORD &index)
{
	//Filter Options
	if (mode)
	{
	}
	else
	{
	}

	return 0;
}
//----------------------------------------------------------------------------
void TGumpOptions::OnLeftMouseDown()
{
	if (g_LastSelectedObject == ID_GO_P5_BUTTON_PREVEOUS) //Preveous button
	{
		if (m_MacroPointer->m_Prev != NULL)
		{
			m_MacroPointer = (TMacro*)m_MacroPointer->m_Prev;
			m_MacroObjectPointer = (TMacroObject*)m_MacroPointer->m_Items;

			TextEntryMacro->SetText(m_HotkeyText[m_MacroPointer->Key & 0xFF]);
		}

		m_LastChangeMacroTime = g_Ticks + CHANGE_MACRO_DELAY;
	}
	else if (g_LastSelectedObject == ID_GO_P5_BUTTON_NEXT) //Next button
	{
		if (m_MacroPointer->m_Next != NULL)
		{
			m_MacroPointer = (TMacro*)m_MacroPointer->m_Next;
			m_MacroObjectPointer = (TMacroObject*)m_MacroPointer->m_Items;

			TextEntryMacro->SetText(m_HotkeyText[m_MacroPointer->Key & 0xFF]);
		}

		m_LastChangeMacroTime = g_Ticks + CHANGE_MACRO_DELAY;
	}
	else if (g_LastSelectedObject >= ID_GO_P5_LEFT_BOX && g_LastSelectedObject < ID_GO_P5_RIGHT_BOX) //Left action box
	{
		m_MacroElement = g_LastSelectedObject - ID_GO_P5_LEFT_BOX;
		m_MacroSelection = 0x10000000;
		m_MacroListOffset = 0;
		m_MacroListCount = 60;
		m_MacroListNameOffset = 0;
		m_MacroListOffsetYStart = 92;
		m_MacroListOffsetYEnd = 392;
	}
	else if (g_LastSelectedObject >= ID_GO_P5_RIGHT_BOX && g_LastSelectedObject < ID_GO_P5_EMPTY_BOX) //Right action box
	{
		m_MacroElement = g_LastSelectedObject - ID_GO_P5_RIGHT_BOX;
		
		TMacroObject *obj = m_MacroObjectPointer;
					
		IFOR(i, 0, (int)m_MacroElement)
		{
			if (obj->m_Next == NULL)
				break;

			obj = (TMacroObject*)obj->m_Next;
		}
		
		m_MacroListCount = 0;
		m_MacroListOffset = 0;
		m_MacroListNameOffset = 0;

		TMacro::GetBoundByCode(obj->Code, m_MacroListCount, m_MacroListNameOffset);

		if (m_MacroListCount)
		{
			m_MacroSelection = 0x20000000;

			if (m_MacroListCount >= m_MacroListMaxCount)
			{
				m_MacroListOffsetYStart = 92;
				m_MacroListOffsetYEnd = 392;
			}
			else
			{
				int startY = 187 + (m_MacroElement * 26) + 26;

				int heightWindow = m_MacroListCount * 15;

				if (heightWindow + startY > 392)
				{
					m_MacroListOffsetYStart = 392 - heightWindow;
					m_MacroListOffsetYEnd = 392;
				}
				else
				{
					m_MacroListOffsetYStart = startY;
					m_MacroListOffsetYEnd = startY + heightWindow;
				}
			}
		}
		else
		{
			m_MacroSelection = 0;
			m_MacroListOffsetYStart = 0;
			m_MacroListOffsetYEnd = 0;

			if (obj->HasSubMenu == 2)
			{
				int x = g_MouseX - (X + 110);
				int y = 0; //g_MouseY - (Y + 57);

				((TMacroObjectEntry*)obj)->TextEntry->OnClick(this, 1, false, x, y, TS_LEFT, UOFONT_FIXED);
			}
		}
	}
	else if (g_LastSelectedObject == ID_GO_P5_EMPTY_BOX) //Empty left action box
	{
		m_MacroSelection = 0x40000000;
		m_MacroListOffset = 0;
		m_MacroListCount = 60;
		m_MacroListNameOffset = 0;
		m_MacroListOffsetYStart = 92;
		m_MacroListOffsetYEnd = 392;
	}
}
//----------------------------------------------------------------------------
void TGumpOptions::OnLeftMouseUp()
{
	if (g_LastObjectLeftMouseDown != g_LastSelectedObject)
	{
		if (m_Page == 4 && g_LastSelectedObject >= ID_GO_P5_SELECTION)
			{}
		else
		{
			if (m_MacroSelection != 0)
				m_MacroSelection = 0;

			return;
		}
	}

	if (g_LastObjectLeftMouseDown == ID_GO_PAGE_0)
		m_Page = 0;
	else if (g_LastObjectLeftMouseDown == ID_GO_PAGE_1)
		m_Page = 1;
	else if (g_LastObjectLeftMouseDown == ID_GO_PAGE_2)
		m_Page = 2;
	else if (g_LastObjectLeftMouseDown == ID_GO_PAGE_3)
		m_Page = 3;
	else if (g_LastObjectLeftMouseDown == ID_GO_PAGE_4)
		m_Page = 4;
	else if (g_LastObjectLeftMouseDown == ID_GO_PAGE_5)
		m_Page = 5;
	else if (g_LastObjectLeftMouseDown == ID_GO_PAGE_6)
	{
		m_Page = 6;

		TextEntryGameSizeX->SetText(std::to_string(g_OptionsConfig.GameWindowWidth));
		TextEntryGameSizeY->SetText(std::to_string(g_OptionsConfig.GameWindowHeight));
	}
	else if (g_LastObjectLeftMouseDown == ID_GO_PAGE_7)
		m_Page = 7;
	else if (g_LastObjectLeftMouseDown == ID_GO_PAGE_8)
		m_Page = 8;
	else if (g_LastObjectLeftMouseDown == ID_GO_PAGE_9)
		m_Page = 9;
	else if (g_LastObjectLeftMouseDown == ID_GO_CANCEL) //Cancel
	{
		GumpManager->CloseGump(g_PlayerSerial, 0, GT_OPTIONS);

		OptionsMacroManager->Clear();
	}
	else if (g_LastObjectLeftMouseDown == ID_GO_APPLY) //Apply
		ApplyPageChanges();
	else if (g_LastObjectLeftMouseDown == ID_GO_DEFAULT) //Default
	{
		switch (m_Page)
		{
			case 0:
			{
				g_OptionsConfig.DefaultPage1();
				break;
			}
			case 1:
			{
				g_OptionsConfig.DefaultPage2();
				break;
			}
			case 2:
			{
				g_OptionsConfig.DefaultPage3();
				break;
			}
			case 3:
			{
				g_OptionsConfig.DefaultPage4();
				break;
			}
			case 5:
			{
				g_OptionsConfig.DefaultPage6();
				break;
			}
			case 6:
			{
				g_OptionsConfig.DefaultPage7();
		
				TextEntryGameSizeX->SetText(std::to_string(g_OptionsConfig.GameWindowWidth));
				TextEntryGameSizeY->SetText(std::to_string(g_OptionsConfig.GameWindowHeight));
				break;
			}
			case 7:
			{
				g_OptionsConfig.DefaultPage8();
				break;
			}
			case 8:
			{
				g_OptionsConfig.DefaultPage9();
				break;
			}
			default:
				break;
		}
	}
	else if (g_LastObjectLeftMouseDown == ID_GO_OKAY) //Okay
	{
		/*IFOR(i, 0, 10)
		{
			m_Page = i;
			ApplyPageChanges();
		}*/
		ApplyPageChanges();
		GumpManager->CloseGump(g_PlayerSerial, 0, GT_OPTIONS);

		OptionsMacroManager->Clear();

		return;
	}
	else
	{
		switch (m_Page)
		{
			case 0: //Sound and Music
			{
				if (g_LastObjectLeftMouseDown == ID_GO_P1_SOUND_ON_OFF) //Sound on/off
					g_OptionsConfig.Sound = !g_OptionsConfig.Sound;
				else if (g_LastObjectLeftMouseDown == ID_GO_P1_MUSIC_ON_OFF) //Music on/off
					g_OptionsConfig.Music = !g_OptionsConfig.Music;
				else if (g_LastObjectLeftMouseDown == ID_GO_P1_PLAY_FOOTSTEP_SOUNDS) //Play footstep sounds
					g_OptionsConfig.FootstepsSound = !g_OptionsConfig.FootstepsSound;
				else if (g_LastObjectLeftMouseDown == ID_GO_P1_PLAY_COMBAT_MUSIC) //Play combat music
					g_OptionsConfig.CombatMusic = !g_OptionsConfig.CombatMusic;

				break;
			}
			case 1: //Orion's configuration
			{
				break;
			}
			case 2: //Language
			{
				if (g_LastObjectLeftMouseDown == ID_GO_P3_USE_TOOLTIP) //Use Tool-tips
					g_OptionsConfig.UseToolTips = !g_OptionsConfig.UseToolTips;
				else if (g_LastObjectLeftMouseDown == ID_GO_P3_TEXT_COLOR) //Color of Tool-tip text
				{
					TGumpSelectColor *gump = new TGumpSelectColor(g_PlayerSerial, 100, 100, SCGS_OPT_TOOLTIP_TEXT);

					GumpManager->AddGump(gump);
				}
				else if (g_LastObjectLeftMouseDown == ID_GO_P3_TEXT_FONT) //Font
				{
					TGumpSelectFont *gump = new TGumpSelectFont(g_PlayerSerial, 320, 240, SFGS_OPT_TOOLTIP);

					GumpManager->AddGump(gump);
				}

				break;
			}
			case 3: //Chat
			{
				if (g_LastObjectLeftMouseDown >= ID_GO_P4_TEXT_COLOR) //Input text color
				{
					TGumpSelectColor *gump = new TGumpSelectColor(g_PlayerSerial, 100, 100, (SELECT_COLOR_GUMP_STATE)(SCGS_OPT_CHAT_INPUT_TEXT + (g_LastObjectLeftMouseDown - ID_GO_P4_TEXT_COLOR)));

					GumpManager->AddGump(gump);
				}
				else if (g_LastObjectLeftMouseDown == ID_GO_P4_TEXT_FONT) //Font
				{
					TGumpSelectFont *gump = new TGumpSelectFont(g_PlayerSerial, 320, 240, SFGS_OPT_CHAT);

					GumpManager->AddGump(gump);
				}

				break;
			}
			case 4: //Macro Options
			{
				if (g_LastObjectLeftMouseDown == ID_GO_P5_BUTTON_ADD) //Add button
				{
					m_MacroPointer = TMacro::CreateBlankMacro();
					m_MacroObjectPointer = (TMacroObject*)m_MacroPointer->m_Items;
					OptionsMacroManager->Add(m_MacroPointer);

					TextEntryMacro->SetText(m_HotkeyText[m_MacroPointer->Key & 0xFF]);
				}
				else if (g_LastObjectLeftMouseDown == ID_GO_P5_BUTTON_DELETE) //Delete button
				{
					TMacro *newpointer = (TMacro*)m_MacroPointer->m_Next;
					if (newpointer == NULL)
						newpointer = (TMacro*)m_MacroPointer->m_Prev;

					OptionsMacroManager->Delete(m_MacroPointer);

					if (newpointer == NULL)
					{
						newpointer = TMacro::CreateBlankMacro();
						OptionsMacroManager->Add(newpointer);
					}

					m_MacroPointer = newpointer;
					m_MacroObjectPointer = (TMacroObject*)m_MacroPointer->m_Items;

					TextEntryMacro->SetText(m_HotkeyText[m_MacroPointer->Key & 0xFF]);
				}
				/*else if (g_LastObjectLeftMouseDown == ID_GO_P5_BUTTON_PREVEOUS) //Preveous button
				{
					if (m_MacroPointer->m_Prev != NULL)
					{
						m_MacroPointer = (TMacro*)m_MacroPointer->m_Prev;
						m_MacroObjectPointer = (TMacroObject*)m_MacroPointer->m_Items;
					}
				}
				else if (g_LastObjectLeftMouseDown == ID_GO_P5_BUTTON_NEXT) //Next button
				{
					if (m_MacroPointer->m_Next != NULL)
					{
						m_MacroPointer = (TMacro*)m_MacroPointer->m_Next;
						m_MacroObjectPointer = (TMacroObject*)m_MacroPointer->m_Items;
					}
				}*/
				else if (g_LastObjectLeftMouseDown == ID_GO_P5_KEY_BOX) //Key box
				{
					int x = g_MouseX - (X + 137);
					int y = g_MouseY - (Y + 57);

					TextEntryMacro->OnClick(this, 1, false, x, y);
				}
				else if (g_LastObjectLeftMouseDown == ID_GO_P5_BUTTON_SHIFT) //Shift checkbox
					m_MacroPointer->Shift = !m_MacroPointer->Shift;
				else if (g_LastObjectLeftMouseDown == ID_GO_P5_BUTTON_ALT) //Alt checkbox
					m_MacroPointer->Alt = !m_MacroPointer->Alt;
				else if (g_LastObjectLeftMouseDown == ID_GO_P5_BUTTON_CTRL) //Ctrl checkbox
					m_MacroPointer->Ctrl = !m_MacroPointer->Ctrl;
				else if (g_LastObjectLeftMouseDown == ID_GO_P5_BUTTON_UP) //Up button
				{
					if (m_MacroObjectPointer->m_Prev != NULL)
						m_MacroObjectPointer = (TMacroObject*)m_MacroObjectPointer->m_Prev;
				}
				else if (g_LastObjectLeftMouseDown == ID_GO_P5_BUTTON_DOWN) //Down button
				{
					if (m_MacroObjectPointer->m_Next != NULL)
						m_MacroObjectPointer = (TMacroObject*)m_MacroObjectPointer->m_Next;
				}
				else if (g_LastSelectedObject >= ID_GO_P5_SELECTION) //Action selection
				{
					DWORD index = g_LastSelectedObject - ID_GO_P5_SELECTION;

					switch (m_MacroSelection)
					{
						case 0x10000000:
						case 0x40000000:
						{
							TMacroObject *obj = m_MacroObjectPointer;

							if (m_MacroSelection == 0x40000000)
							{
								obj = TMacro::CreateMacro((MACRO_CODE)index);
								m_MacroPointer->Add(obj);
							}
							else
							{
								IFOR(i, 0, (int)m_MacroElement)
								{
									if (obj->m_Next == NULL)
									{
										obj = TMacro::CreateMacro((MACRO_CODE)index);
										m_MacroPointer->Add(obj);

										break;
									}

									obj = (TMacroObject*)obj->m_Next;
								}
							}
							
							if (obj->Code != (MACRO_CODE)index)
							{
								TMacroObject *newobj = TMacro::CreateMacro((MACRO_CODE)index);

								if (obj == m_MacroObjectPointer)
									m_MacroObjectPointer = newobj;
								
								m_MacroPointer->ChangeObject(obj, newobj);
							}

							break;
						}
						case 0x20000000:
						{
							TMacroObject *obj = m_MacroObjectPointer;
							
							IFOR(i, 0, (int)m_MacroElement)
							{
								if (obj->m_Next == NULL)
									break;

								obj = (TMacroObject*)obj->m_Next;
							}

							obj->SubCode = (MACRO_SUB_CODE)index;

							break;
						}
						default:
							break;
					}
				}

				break;
			}
			case 5: //Interface
			{
				if (g_LastObjectLeftMouseDown == ID_GO_P6_ENABLE_PATHFINDING) //Enable pathfinding with double-right-click
					g_OptionsConfig.EnablePathfind = !g_OptionsConfig.EnablePathfind;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_HOLD_TAB_FOR_COMBAT) //Hold down TAB key for combat, instead of tapping it to toggle combat mode
					g_OptionsConfig.HoldTabForCombat = !g_OptionsConfig.HoldTabForCombat;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_OFFSET_INTERFACE_WINDOWS) //Offset interface windows rather than perfectly stacking them
					g_OptionsConfig.OffsetInterfaceWindows = !g_OptionsConfig.OffsetInterfaceWindows;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_AUTO_ARRANGE_MINIMIZED_WINDOWS) //Automatically arrange minimized windows
					g_OptionsConfig.AutoArrange = !g_OptionsConfig.AutoArrange;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_ALWAYS_RUN) //Your character will always run if this is checked
					g_OptionsConfig.AlwaysRun = !g_OptionsConfig.AlwaysRun;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_DISABLE_MENUBAR) //Disable the Menu Bar
					g_OptionsConfig.DisableMenubar = !g_OptionsConfig.DisableMenubar;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_GRAY_OUT_OF_RANGE_OBJECTS) //Gray out of range objects
					g_OptionsConfig.GrayOutOfRangeObjects = !g_OptionsConfig.GrayOutOfRangeObjects;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_DISABLE_NEW_TARGET_SYSTEM) //Disable New Target System
					g_OptionsConfig.DisableNewTargetSystem = !g_OptionsConfig.DisableNewTargetSystem;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_OBJECT_HANDLES) //Object Handles
					g_OptionsConfig.ObjectHandles = !g_OptionsConfig.ObjectHandles;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_REDUCE_FPS_UNACTIVE_WINDOW) //Reduce FPS when Window is Unactive
					g_OptionsConfig.SetReduceFPSUnactiveWindow(!g_OptionsConfig.GetReduceFPSUnactiveWindow());
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_DISPLAY_ITEM_PROPERTIES_ICON) //Display Item Properties Icon
					g_OptionsConfig.ItemPropertiesIcon = !g_OptionsConfig.ItemPropertiesIcon;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_HOLD_SHIFT_FOR_CONTEXT_MENUS) //Hold Shift For Context Menus
					g_OptionsConfig.HoldShiftForContextMenus = !g_OptionsConfig.HoldShiftForContextMenus;
				else if (g_LastObjectLeftMouseDown == ID_GO_P6_HOLD_SHIFT_FOR_ENABLE_PATHFINDING) //Hold Shift For Enable Pathfinding
					g_OptionsConfig.HoldShiftForEnablePathfind = !g_OptionsConfig.HoldShiftForEnablePathfind;

				break;
			}
			case 6: //Display
			{
				if (g_LastObjectLeftMouseDown == ID_GO_P7_SCALE_SPEECH_DURATION) //Scale speech duration based on length
					g_OptionsConfig.ScaleSpeechDelay = !g_OptionsConfig.ScaleSpeechDelay;
				else if (g_LastObjectLeftMouseDown >= ID_GO_P7_SPEECH_COLOR && g_LastObjectLeftMouseDown <= ID_GO_P7_ALLIANCE_MESSAGE_COLOR) //Speech color
				{
					TGumpSelectColor *gump = new TGumpSelectColor(g_PlayerSerial, 100, 100, (SELECT_COLOR_GUMP_STATE)(SCGS_OPT_DISPLAY_SPEECH + (g_LastObjectLeftMouseDown - ID_GO_P7_SPEECH_COLOR)));

					GumpManager->AddGump(gump);
				}
				else if (g_LastObjectLeftMouseDown == ID_GO_P7_IGNORE_GUILD_MESSAGE) //Ignore Guild Messages
					g_OptionsConfig.IgnoreGuildMessage = !g_OptionsConfig.IgnoreGuildMessage;
				else if (g_LastObjectLeftMouseDown == ID_GO_P7_IGNORE_ALLIANCE_MESSAGE) //Ignore Alliance Messages
					g_OptionsConfig.IgnoreAllianceMessage = !g_OptionsConfig.IgnoreAllianceMessage;
				else if (g_LastObjectLeftMouseDown == ID_GO_P7_DARK_NIGHTS) //Dark Nights
					g_OptionsConfig.DarkNights = !g_OptionsConfig.DarkNights;
				else if (g_LastObjectLeftMouseDown == ID_GO_P7_COLORED_LIGHTING) //Colored Lighting
					g_OptionsConfig.ColoredLighting = !g_OptionsConfig.ColoredLighting;
				else if (g_LastObjectLeftMouseDown == ID_GO_P7_GAME_WINDOW_SIZE_X) //Game Play Window Size X
				{
					int x = g_MouseX - (X + 68);
					int y = g_MouseY - Y;

					TextEntryGameSizeX->OnClick(this, 0, true, x, y);
				}
				else if (g_LastObjectLeftMouseDown == ID_GO_P7_GAME_WINDOW_SIZE_Y) //Game Play Window Size Y
				{
					int x = g_MouseX - (X + 143);
					int y = g_MouseY - Y;

					TextEntryGameSizeY->OnClick(this, 0, true, x, y);
				}
				else if (g_LastObjectLeftMouseDown == ID_GO_P7_CHARACTERS_ANIMATION_DELAY) //Standard characters animation delay
					g_OptionsConfig.StandartCharactersAnimationDelay = !g_OptionsConfig.StandartCharactersAnimationDelay;
				else if (g_LastObjectLeftMouseDown == ID_GO_P7_ITEMS_ANIMATION_DELAY) //Standard items animation delay
					g_OptionsConfig.StandartItemsAnimationDelay = !g_OptionsConfig.StandartItemsAnimationDelay;
				else if (g_LastObjectLeftMouseDown == ID_GO_P7_LOCK_GAME_WINDOW_RESIZING) //Lock game window resizing
					g_OptionsConfig.LockResizingGameWindow = !g_OptionsConfig.LockResizingGameWindow;
				else if (g_LastObjectLeftMouseDown == ID_GO_P7_LOCK_GUMP_MOVING) //Lock gump moving
					g_OptionsConfig.LockGumpsMoving = !g_OptionsConfig.LockGumpsMoving;

				break;
			}
			case 7: //Reputation System
			{
				if (g_LastObjectLeftMouseDown >= ID_GO_P8_INNOCENT_COLOR && g_LastObjectLeftMouseDown <= ID_GO_P8_MURDERER_COLOR) //Innocent highlight color
				{
					/*if (g_LastObjectLeftMouseDown == 100) //Innocent highlight color
					else if (g_LastObjectLeftMouseDown == 101) //Friendly guilds highlight color
					else if (g_LastObjectLeftMouseDown == 102) //Someone that can be attacked color
					else if (g_LastObjectLeftMouseDown == 103) //Criminal highlight color
					else if (g_LastObjectLeftMouseDown == 104) //Enemy guildmembers color
					else if (g_LastObjectLeftMouseDown == 105) //Murderer highlight color*/
					
					TGumpSelectColor *gump = new TGumpSelectColor(g_PlayerSerial, 100, 100, (SELECT_COLOR_GUMP_STATE)(SCGS_OPT_REPSYS_INNOCENT + (g_LastObjectLeftMouseDown - ID_GO_P8_INNOCENT_COLOR)));

					GumpManager->AddGump(gump);
				}
				else if (g_LastObjectLeftMouseDown == ID_GO_P8_QUERY_CRIMINAL_ACTIONS) //Query before performing criminal actions
					g_OptionsConfig.CriminalActionsQuery = !g_OptionsConfig.CriminalActionsQuery;

				break;
			}
			case 8: //Miscellaneous
			{
				if (g_LastObjectLeftMouseDown == ID_GO_P9_SHOW_APPROACHING_NAMES) //Show Names of Approaching Players
					g_OptionsConfig.ShowIncomingNames = !g_OptionsConfig.ShowIncomingNames;
				else if (g_LastObjectLeftMouseDown == ID_GO_P9_USE_CIRCLE_OF_TRANSPARENCY) //Use circle of transparency
					g_OptionsConfig.UseCircleTrans = !g_OptionsConfig.UseCircleTrans;
				else if (g_LastObjectLeftMouseDown == ID_GO_P9_INFORM_STATS) //Inform me of increases in strength, dexterity, and intelligence.
					g_OptionsConfig.StatReport = !g_OptionsConfig.StatReport;
				else if (g_LastObjectLeftMouseDown == ID_GO_P9_CONSOLE_ENTER) //Console need press 'Enter' to activate it.
					g_OptionsConfig.SetConsoleNeedEnter(!g_OptionsConfig.GetConsoleNeedEnter());
				else if (g_LastObjectLeftMouseDown == ID_GO_P9_SPEECH_FONT) //Speech Font
				{
					TGumpSelectFont *gump = new TGumpSelectFont(g_PlayerSerial, 320, 240, SFGS_OPT_MISCELLANEOUS);

					GumpManager->AddGump(gump);
				}

				break;
			}
			case 9: //Filter Options
			{
				break;
			}
			default:
				break;
		}
	}

	if (m_MacroSelection != 0)
		m_MacroSelection = 0;
}
//----------------------------------------------------------------------------
void TGumpOptions::OnCharPress(WPARAM &wparam, LPARAM &lparam)
{
	if (wparam == VK_RETURN || wparam == VK_BACK || wparam == VK_ESCAPE || EntryPointer == NULL)
		return; //Ignore no print keys

	if (EntryPointer == TextEntryGameSizeX || EntryPointer == TextEntryGameSizeY)
	{
		if (wparam >= '0' && wparam <= '9')
		{
			EntryPointer->Insert(wparam);

			int val = atoi(EntryPointer->c_str());
			if (val > 2000)
				EntryPointer->Remove(true);
			else
				m_FrameCreated = false;
		}
	}
	else if (EntryPointer != TextEntryMacro)
	{
		TMacroObject *obj = m_MacroPointer->EntryPointerHere();

		if (obj != NULL)
		{
			bool canAdd = false;

			switch (obj->Code)
			{
				case MC_DELAY:
				case MC_SET_UPDATE_RANGE:
				case MC_MODIFY_UPDATE_RANGE:
				{
					if (wparam >= '0' && wparam <= '9')
						canAdd = true;

					break;
				}
				case MC_SAY:
				case MC_EMOTE:
				case MC_WHISPER:
				case MC_YELL:
				{
					canAdd = true;

					break;
				}
				default:
					break;
			}

			if (canAdd)
			{
				EntryPointer->Insert(wparam);
				m_FrameCreated = false;
			}
		}
	}
}
//----------------------------------------------------------------------------
void TGumpOptions::OnKeyPress(WPARAM &wparam, LPARAM &lparam)
{
	if (EntryPointer == TextEntryMacro)
	{
		m_MacroPointer->Key = wparam & 0xFF;

		TextEntryMacro->SetText(m_HotkeyText[wparam & 0xFF]);

		m_FrameCreated = false;
	}
	else
	{
		if (wparam == VK_RETURN)
		{
			if (ConfigManager.GetConsoleNeedEnter())
				EntryPointer = NULL;
			else
				EntryPointer = GameConsole;

			m_FrameCreated = false;
		}
		else
			EntryPointer->OnKey(this, wparam);
	}
}
//----------------------------------------------------------------------------
void TGumpOptions::ApplyPageChanges()
{
	switch (m_Page)
	{
		case 0: //Sound and Music
		{		
			//������ ��������� ����� �������� � ������� ��������
			if (ConfigManager.SoundVolume != g_OptionsConfig.SoundVolume)
			{
				ConfigManager.SoundVolume = g_OptionsConfig.SoundVolume;
				Orion->AdjustSoundEffects(g_Ticks + 100000, SoundManager.GetVolumeValue());
			}

			//������ ��������� ����� ������ � ������� ������
			if (ConfigManager.MusicVolume != g_OptionsConfig.MusicVolume)
			{
				ConfigManager.MusicVolume = g_OptionsConfig.MusicVolume;
				SoundManager.SetMusicVolume(SoundManager.GetVolumeValue(-1, true));
			}
			
		    //��������� ���� ��������.
			if (ConfigManager.Sound && !g_OptionsConfig.Sound)
			{								
				Orion->AdjustSoundEffects(g_Ticks + 100000);
			}
			ConfigManager.Sound = g_OptionsConfig.Sound;


			//��������� ���� ������.
			if (ConfigManager.Music && !g_OptionsConfig.Music)
			{
				SoundManager.StopMusic();	
				SoundManager.StopWarMusic();
			}
			ConfigManager.Music = g_OptionsConfig.Music;

			ConfigManager.FootstepsSound = g_OptionsConfig.FootstepsSound;
			ConfigManager.CombatMusic = g_OptionsConfig.CombatMusic;

			break;
		}
		case 1: //Orion's configuration
		{
			ConfigManager.ClientFPS = g_OptionsConfig.ClientFPS;
			ConfigManager.UpdateClientFPS();

			break;
		}
		case 2: //Language
		{
			ConfigManager.UseToolTips = g_OptionsConfig.UseToolTips;
			ConfigManager.ToolTipsTextColor = g_OptionsConfig.ToolTipsTextColor;
			ConfigManager.ToolTipsTextFont = g_OptionsConfig.ToolTipsTextFont;
			ConfigManager.ToolTipsDelay = g_OptionsConfig.ToolTipsDelay;

			break;
		}
		case 3: //Chat
		{
			ConfigManager.ChatColorInputText = g_OptionsConfig.ChatColorInputText;
			ConfigManager.ChatColorMenuOption = g_OptionsConfig.ChatColorMenuOption;
			ConfigManager.ChatColorPlayerInMemberList = g_OptionsConfig.ChatColorPlayerInMemberList;
			ConfigManager.ChatColorText = g_OptionsConfig.ChatColorText;
			ConfigManager.ChatColorPlayerNameWithout = g_OptionsConfig.ChatColorPlayerNameWithout;
			ConfigManager.ChatColorMuted = g_OptionsConfig.ChatColorMuted;
			ConfigManager.ChatColorChannelModeratorName = g_OptionsConfig.ChatColorChannelModeratorName;
			ConfigManager.ChatColorChannelModeratorText = g_OptionsConfig.ChatColorChannelModeratorText;
			ConfigManager.ChatColorMyName = g_OptionsConfig.ChatColorMyName;
			ConfigManager.ChatColorMyText = g_OptionsConfig.ChatColorMyText;
			ConfigManager.ChatColorSystemMessage = g_OptionsConfig.ChatColorSystemMessage;
			ConfigManager.ChatColorBGOutputText = g_OptionsConfig.ChatColorBGOutputText;
			ConfigManager.ChatColorBGInputText = g_OptionsConfig.ChatColorBGInputText;
			ConfigManager.ChatColorBGUserList = g_OptionsConfig.ChatColorBGUserList;
			ConfigManager.ChatColorBGConfList = g_OptionsConfig.ChatColorBGConfList;
			ConfigManager.ChatColorBGCommandList = g_OptionsConfig.ChatColorBGCommandList;
			ConfigManager.ChatFont = g_OptionsConfig.ChatFont;

			break;
		}
		case 4: //Macro Options
		{
			MacroManager->LoadFromOptions();
			break;
		}
		case 5: //Interface
		{
			ConfigManager.EnablePathfind = g_OptionsConfig.EnablePathfind;
			ConfigManager.HoldTabForCombat = g_OptionsConfig.HoldTabForCombat;

			if (ConfigManager.OffsetInterfaceWindows != g_OptionsConfig.OffsetInterfaceWindows && g_OptionsConfig.OffsetInterfaceWindows)
				ContainerRect.MakeDefault();

			ConfigManager.OffsetInterfaceWindows = g_OptionsConfig.OffsetInterfaceWindows;
			ConfigManager.AutoArrange = g_OptionsConfig.AutoArrange;
			ConfigManager.AlwaysRun = g_OptionsConfig.AlwaysRun;
			ConfigManager.DisableMenubar = g_OptionsConfig.DisableMenubar;
			ConfigManager.GrayOutOfRangeObjects = g_OptionsConfig.GrayOutOfRangeObjects;
			ConfigManager.DisableNewTargetSystem = g_OptionsConfig.DisableNewTargetSystem;
			ConfigManager.ObjectHandles = g_OptionsConfig.ObjectHandles;
			ConfigManager.SetReduceFPSUnactiveWindow(g_OptionsConfig.GetReduceFPSUnactiveWindow());
			ConfigManager.ItemPropertiesIcon = g_OptionsConfig.ItemPropertiesIcon;
			ConfigManager.HoldShiftForContextMenus = g_OptionsConfig.HoldShiftForContextMenus;
			ConfigManager.HoldShiftForEnablePathfind = g_OptionsConfig.HoldShiftForEnablePathfind;

			if (g_OptionsConfig.DisableMenubar)
				GumpManager->CloseGump(g_PlayerSerial, 0, GT_MENUBAR);
			else
				GumpManager->AddGump(new TGumpMenubar(g_PlayerSerial, 0, 0));

			break;
		}
		case 6: //Display
		{
			int curX = 0;

			if (TextEntryGameSizeX->Length())
				curX = atoi(TextEntryGameSizeX->c_str());

			if (curX < 640)
				curX = 640;
			else if (curX > (g_ClientWidth - 20))
				curX = g_ClientWidth - 20;

			g_OptionsConfig.GameWindowWidth = curX;
			ConfigManager.GameWindowWidth = curX;
			
			int curY = 0;
			
			if (TextEntryGameSizeY->Length())
				curY = atoi(TextEntryGameSizeY->c_str());

			if (curY < 480)
				curY = 480;
			else if (curY > (g_ClientHeight - 40))
				curY = (g_ClientHeight - 40);

			g_OptionsConfig.GameWindowHeight = curY;
			ConfigManager.GameWindowHeight = curY;

			if (PacketManager.GetClientVersion() >= CV_200)
			{
				TPacketGameWindowSize packet;
				packet.Send();
			}

			ConfigManager.SpeechDelay = g_OptionsConfig.SpeechDelay;
			ConfigManager.ScaleSpeechDelay = g_OptionsConfig.ScaleSpeechDelay;
			ConfigManager.SpeechColor = g_OptionsConfig.SpeechColor;
			ConfigManager.EmoteColor = g_OptionsConfig.EmoteColor;
			ConfigManager.PartyMessageColor = g_OptionsConfig.PartyMessageColor;
			ConfigManager.GuildMessageColor = g_OptionsConfig.GuildMessageColor;
			ConfigManager.AllianceMessageColor = g_OptionsConfig.AllianceMessageColor;
			ConfigManager.IgnoreGuildMessage = g_OptionsConfig.IgnoreGuildMessage;
			ConfigManager.IgnoreAllianceMessage = g_OptionsConfig.IgnoreAllianceMessage;
			ConfigManager.DarkNights = g_OptionsConfig.DarkNights;
			ConfigManager.ColoredLighting = g_OptionsConfig.ColoredLighting;
			ConfigManager.StandartCharactersAnimationDelay = g_OptionsConfig.StandartCharactersAnimationDelay;
			ConfigManager.StandartItemsAnimationDelay = g_OptionsConfig.StandartItemsAnimationDelay;
			ConfigManager.LockResizingGameWindow = g_OptionsConfig.LockResizingGameWindow;
			ConfigManager.LockGumpsMoving = g_OptionsConfig.LockGumpsMoving;
			
			break;
		}
		case 7: //Reputation System
		{
			ConfigManager.InnocentColor = g_OptionsConfig.InnocentColor;
			ConfigManager.FriendlyColor = g_OptionsConfig.FriendlyColor;
			ConfigManager.SomeoneColor = g_OptionsConfig.SomeoneColor;
			ConfigManager.CriminalColor = g_OptionsConfig.CriminalColor;
			ConfigManager.EnemyColor = g_OptionsConfig.EnemyColor;
			ConfigManager.MurdererColor = g_OptionsConfig.MurdererColor;
			ConfigManager.CriminalActionsQuery = g_OptionsConfig.CriminalActionsQuery;

			break;
		}
		case 8: //Miscellaneous
		{
			ConfigManager.ShowIncomingNames = g_OptionsConfig.ShowIncomingNames;
			ConfigManager.UseCircleTrans = g_OptionsConfig.UseCircleTrans;
			ConfigManager.StatReport = g_OptionsConfig.StatReport;
			ConfigManager.SetConsoleNeedEnter(g_OptionsConfig.GetConsoleNeedEnter());
			ConfigManager.CircleTransRadius = g_OptionsConfig.CircleTransRadius;
			ConfigManager.SkillReport = g_OptionsConfig.SkillReport;
			ConfigManager.SpeechFont = g_OptionsConfig.SpeechFont;

			g_CircleOfTransparency.Create(ConfigManager.CircleTransRadius);

			break;
		}
		case 9: //Filter Options
		{
			break;
		}
		default:
			break;
	}
}
//---------------------------------------------------------------------------
const char *TGumpOptions::m_HotkeyText[0x100] =
{
	"",         //0x00
	"Left Mouse",   //0x01
	"Right Mouse",  //0x02
	"Ctrl-Break",   //0x03
	"Middle Mouse", //0x04
	"0x05",         //0x05
	"0x06",         //0x06
	"0x07",         //0x07
	"Backspace",    //0x08
	"Tab",          //0x09
	"0x0a",         //0x0a
	"0x0b",         //0x0b
	"Clear",        //0x0c
	"Enter",        //0x0d
	"0x0e",         //0x0e
	"0x0f",         //0x0f
	"Shift",        //0x10
	"Ctrl",         //0x11
	"Alt",          //0x12
	"Pause",        //0x13
	"Caps Lock",    //0x14
	"0x15",         //0x15
	"0x16",         //0x16
	"0x17",         //0x17
	"0x18",         //0x18
	"0x19",         //0x19
	"0x1a",         //0x1a
	"Esc",          //0x1b
	"0x1c",         //0x1c
	"0x1d",         //0x1d
	"0x1e",         //0x1e
	"0x1f",         //0x1f
	"Space",        //0x20
	"Page Up",      //0x21
	"Page Down",    //0x22
	"End",          //0x23
	"Home",         //0x24
	"Left Arrow",   //0x25
	"Up Arrow",     //0x26
	"Right Arrow",  //0x27
	"Down Arrow",   //0x28
	"Select",       //0x29
	"OEM 2A",       //0x2a
	"Execute",      //0x2b
	"Print Screen", //0x2c
	"Ins",          //0x2d
	"Del",          //0x2e
	"Help",         //0x2f
	"0",            //0x30
	"1",            //0x31
	"2",            //0x32
	"3",            //0x33
	"4",            //0x34
	"5",            //0x35
	"6",            //0x36
	"7",            //0x37
	"8",            //0x38
	"9",            //0x39
	"0x3a",         //0x3a
	"0x3b",         //0x3b
	"0x3c",         //0x3c
	"0x3d",         //0x3d
	"0x3e",         //0x3e
	"0x3f",         //0x3f
	"0x40",         //0x40
	"A",            //0x41
	"B",            //0x42
	"C",            //0x43
	"D",            //0x44
	"E",            //0x45
	"F",            //0x46
	"G",            //0x47
	"H",            //0x48
	"I",            //0x49
	"J",            //0x4a
	"K",            //0x4b
	"L",            //0x4c
	"M",            //0x4d
	"N",            //0x4e
	"O",            //0x4f
	"P",            //0x50
	"Q",            //0x51
	"R",            //0x52
	"S",            //0x53
	"T",            //0x54
	"U",            //0x55
	"V",            //0x56
	"W",            //0x57
	"X",            //0x58
	"Y",            //0x59
	"Z",            //0x5a
	"Left Win",     //0x5b
	"Right Win",    //0x5c
	"Apps",         //0x5d
	"0x5e",         //0x5e
	"0x5f",         //0x5f
	"Num 0",        //0x60
	"Num 1",        //0x61
	"Num 2",        //0x62
	"Num 3",        //0x63
	"Num 4",        //0x64
	"Num 5",        //0x65
	"Num 6",        //0x66
	"Num 7",        //0x67
	"Num 8",        //0x68
	"Num 9",        //0x69
	"Num *",        //0x6a
	"Num +",        //0x6b
	"Separator",    //0x6c
	"Num -",        //0x6d
	"Num .",        //0x6e
	"Num /",        //0x6f
	"F1",           //0x70
	"F2",           //0x71
	"F3",           //0x72
	"F4",           //0x73
	"F5",           //0x74
	"F6",           //0x75
	"F7",           //0x76
	"F8",           //0x77
	"F9",           //0x78
	"F10",          //0x79
	"F11",          //0x7a
	"F12",          //0x7b
	"Wheel Click",	//"F13",	//0x7c
	"Wheel Up",		//"F14",	//0x7d
	"Wheel Down",	//"F15",	//0x7e
	"Mouse+ Forward",//"F16",	//0x7f
	"Mouse+ Back",	//"F17",	//0x80
	"F18",          //0x81
	"F19",          //0x82
	"F20",          //0x83
	"F21",          //0x84
	"F22",          //0x85
	"F23",          //0x86
	"F24",          //0x87
	"0x88",         //0x88
	"0x89",         //0x89
	"0x8a",         //0x8a
	"0x8b",         //0x8b
	"0x8c",         //0x8c
	"0x8d",         //0x8d
	"0x8e",         //0x8e
	"0x8f",         //0x8f
	"Num Lock",      //0x90
	"Scroll Lock",   //0x91
	"0x92",         //0x92
	"0x93",         //0x93
	"0x94",         //0x94
	"0x95",         //0x95
	"0x96",         //0x96
	"0x97",         //0x97
	"0x98",         //0x98
	"0x99",         //0x99
	"0x9a",         //0x9a
	"0x9b",         //0x9b
	"0x9c",         //0x9c
	"0x9d",         //0x9d
	"0x9e",         //0x9e
	"0x9f",         //0x9f
	"0xa0",         //0xa0
	"0xa1",         //0xa1
	"0xa2",         //0xa2
	"0xa3",         //0xa3
	"0xa4",         //0xa4
	"0xa5",         //0xa5
	"0xa6",         //0xa6
	"0xa7",         //0xa7
	"0xa8",         //0xa8
	"0xa9",         //0xa9
	"0xaa",         //0xaa
	"0xab",         //0xab
	"0xac",         //0xac
	"0xad",         //0xad
	"0xae",         //0xae
	"0xaf",         //0xaf
	"0xb0",         //0xb0
	"0xb1",         //0xb1
	"0xb2",         //0xb2
	"0xb3",         //0xb3
	"0xb4",         //0xb4
	"0xb5",         //0xb5
	"0xb6",         //0xb6
	"0xb7",         //0xb7
	"0xb8",         //0xb8
	"0xb9",         //0xb9
	";",            //0xba
	"=",            //0xbb
	",",            //0xbc
	"-",            //0xbd
	".",            //0xbe
	"/",            //0xbf
	"`",            //0xc0
	"0xc1",         //0xc1
	"0xc2",         //0xc2
	"0xc3",         //0xc3
	"0xc4",         //0xc4
	"0xc5",         //0xc5
	"0xc6",         //0xc6
	"0xc7",         //0xc7
	"0xc8",         //0xc8
	"0xc9",         //0xc9
	"0xca",         //0xca
	"0xcb",         //0xcb
	"0xcc",         //0xcc
	"0xcd",         //0xcd
	"0xce",         //0xce
	"0xcf",         //0xcf
	"0xd0",         //0xd0
	"0xd1",         //0xd1
	"0xd2",         //0xd2
	"0xd3",         //0xd3
	"0xd4",         //0xd4
	"0xd5",         //0xd5
	"0xd6",         //0xd6
	"0xd7",         //0xd7
	"0xd8",         //0xd8
	"0xd9",         //0xd9
	"0xda",         //0xda
	"[",            //0xdb
	"\\",            //0xdc
	"]",            //0xdd
	"'",            //0xde
	"OEM DF",       //0xdf
	"OEM E0",       //0xe0
	"OEM E1",       //0xe1
	"OEM E2",       //0x32
	"OEM E3",       //0xe3
	"OEM E4",       //0xe4
	"0xe5",         //0xe5
	"OEM E6",       //0xe6
	"0xe7",         //0xe7
	"0xe8",         //0xe8
	"OEM E9",       //0xe9
	"OEM EA",       //0xea
	"OEM EB",       //0xeb
	"OEM EC",       //0xec
	"OEM ED",       //0xed
	"OEM EE",       //0xee
	"OEM EF",       //0xef
	"OEM F0",       //0xf0
	"OEM F1",       //0xf1
	"OEM F2",       //0xf2
	"OEM F3",       //0xf3
	"OEM F4",       //0xf4
	"OEM F5",       //0xf5
	"Attn",         //0xf6
	"Crsel",        //0xf7
	"Exsel",        //0xf8
	"Erase EOF",    //0xf9
	"Play",         //0xfa
	"Zoom",         //0xfb
	"0xfc",         //0xfc
	"PA1",          //0xfd
	"Clear",        //0xfe
	"0xff"          //0xff
};
//----------------------------------------------------------------------------