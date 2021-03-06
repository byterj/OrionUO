/***********************************************************************************
**
** Constants.h
**
** Copyright (C) August 2016 Hotride
**
************************************************************************************
*/
//----------------------------------------------------------------------------------
#ifndef CONSTANTS_H
#define CONSTANTS_H
//----------------------------------------------------------------------------------
const int MAX_CONSOLE_STACK_SIZE = 100;

//!�������� ����� ������� ��� ��������� ���� ����������
const int FRAME_DELAY_ACTIVE_WINDOW = 30;

//!�������� ����� ������� ��� ����������� ���� ����������
const int FRAME_DELAY_UNACTIVE_WINDOW = (FRAME_DELAY_ACTIVE_WINDOW + 1) * 7;

const int DAMAGE_TEXT_NORMAL_DELAY = 800;

const int DAMAGE_TEXT_TRANSPARENT_DELAY = 400;

const int DAMAGE_TEXT_STEP = 2;

const int DAMAGE_TEXT_ALPHA_STEP = (DAMAGE_TEXT_TRANSPARENT_DELAY / FRAME_DELAY_ACTIVE_WINDOW);

const int DRAG_PIXEL_RANGE = 1; //3;

//!������������ ���������� ����� �� ������
static const int MAX_SHADOWS_COUNT = 100;

//!����������� ���������� ���������� ����� �� ������
const int MAX_LIGHT_SOURCES = 100;

//!������������ ���������� ������ ��� ������ Object Handles
const int MAX_OBJECT_HANDLES = 30;

//!������������ ������ fastwalk �����
const int MAX_FAST_WALK_STACK_SIZE = 255;

//!������������ ������ ������ ��� ������ ��� ������ � ���� (����� TFileWriter)
const int MAX_FILE_BUFFER_SIZE = 0x1000;

//!������������ ������ ������
const int SIZE_VARIABLE = 0;

//!������ ������� �������� ����� �� ���.���
const int MAX_LAND_DATA_INDEX_COUNT = 0x4000;

//!������ ������� �������� ������� �� ���.���
const int MAX_STATIC_DATA_INDEX_COUNT = 0x4000;

//!������ ������� �������� ������� ���������
const int MAX_LAND_TEXTURES_DATA_INDEX_COUNT = 0x1000;

//!������ ������� �������� ������
const int MAX_GUMP_DATA_INDEX_COUNT = 0x10000;

//!������ ������� �������� ������
const int MAX_SOUND_DATA_INDEX_COUNT = 0x0800;

const int MAX_MULTI_DATA_INDEX_COUNT = 0x2000;

//!������ ������� � ��3 �������
const int MAX_MUSIC_DATA_INDEX_COUNT = 100;

//!������ ������� �������� ��������
const int MAX_ANIMATIONS_DATA_INDEX_COUNT = 1000;

//!������ ������� �������� ��������
const int MAX_LIGHTS_DATA_INDEX_COUNT = 100;

//!������������ �����
const WORD SPECTRAL_COLOR = 0x4000;

//!����������� ���� ������������ ������ (����� ������ ������� �� �����, ��� ������ ���������� ������)
const WORD SPECTRAL_COLOR_SPECIAL = 0x4666;

//!������ ������� ��� ������ �������
const int UNICODE_SPACE_WIDTH = 8;

//!������������ ��� ������� ������� ������
const float ITALIC_FONT_KOEFFICIENT = 3.3f;

//!����������� ��������� ������ HTML ������
const int MAX_HTML_TEXT_HEIGHT = 18;

//!�������� �� ������� �������� �� ������ ������� ������ (��� ������)
const int GAME_FIGURE_GUMP_OFFSET = 11369;

//!������������ ������ ���������� ��������� �� ������� ����
const int TEXT_MESSAGE_MAX_WIDTH = 190;

//!����� ����� ������� ������
const DWORD DEATH_SCREEN_DELAY = 3000;

//!���� ���������� ���������
const WORD SELECT_LAND_COLOR = 0x0044;

//!���� ��������� �������
const WORD SELECT_STATIC_COLOR = 0x0077;

//!���� ���������� ������-�������
const WORD SELECT_MULTI_COLOR = 0x0066;

//!�������� ������ ��� ��������� �������� ����
const int MALE_GUMP_OFFSET = 50000;

//!�������� ������ ��� ��������� �������� ����
const int FEMALE_GUMP_OFFSET = 60000;

//!��������� �� ��������-�����������, ���� ������� ���� ������ ���������
const int REMOVE_CONTAINER_GUMP_RANGE = 3;

//!������������ ����������� ������ �������
const int g_MaxBlockZ = 15;

//!������������ ������, �� ������� ����� ���������
const int g_MaxClimbZ = 9;

//!������������ ������, �� ������� ����� ������
const int g_MaxFallZ = 19;

//!������������ ������ ������
const int g_MaxClimbMapZ = 19;

//!������ ���������
const int DEFAULT_CHARACTER_HEIGHT = 16;

//!������ ������������ ������������ ����������/�����������
const int DEFAULT_BLOCK_HEIGHT = 16;

//!�������� ��� ����������� ����� �� ������
const int STEP_DELAY_MOUNT_RUN = 100;

//!�������� ��� ����������� ������ �� ������
const int STEP_DELAY_MOUNT_WALK = 200;

//!�������� ��� ����������� �����
const int STEP_DELAY_RUN = 200;

//!�������� ��� ����������� ������
const int STEP_DELAY_WALK = 400;

//!�������� ��� ����� �����������
const int TURN_DELAY = 100;

//!�������� ������� ������
const int WALKING_DELAY = 200;

//!������� �������� �����������
const int CHARACTER_ANIMATION_DELAY_TABLE[2][2] =
{
	//!������
	{
		//!����
		STEP_DELAY_WALK,
		//!�����
		STEP_DELAY_RUN
	},
	//������
	{
		//!����
		STEP_DELAY_MOUNT_WALK,
		//!�����
		STEP_DELAY_MOUNT_RUN
	}
};

//!�������� �� ������� ������� �����
const int DCLICK_DELAY = 350;

//!�������� ����� ���������� ���������
const int SCROLL_LISTING_DELAY = 150;

//!�������� ����� ���������� ���������� ��������� � ��������
const int CHANGE_SHOP_COUNT_DELAY = 50;

//!�������� ����� ������ �������� � ������
const int CHANGE_MACRO_DELAY = 100;

//!�������� ����� ���������� �������� � ������
const int CHANGE_MACRO_LIST_DELAY = 500;

//!�������� ����� ��������� ���������� ������ � Ping (0x73) �������, 55 ������
const int SEND_TIMEOUT_DELAY = 55000;

//!��� � �������� ��� ��������� ��������� � ����
const int GUMP_MENU_PIXEL_STEP = 5;

//!��� � �������� ��� ��������� ���������
const int GUMP_SCROLLING_PIXEL_STEP = 10;

//!�����, ����� ������� ����������� �������� �������
const int CLEAR_TEXTURES_DELAY = 30000;

//!������ ������
const int WEATHER_TIMER = (6 * 60 * 1000);

//!������������ ����� �������� ��� ������� �� ������
const int WAIT_FOR_TARGET_DELAY = 2000;

//!������ �����, ���������� �� �����
static const bool LAYER_UNSAFE[30] =
{
	false,   //0
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	true,
	false,
	true,
	true,
	true,
	false,
	false,
	true,
	true,
	true,
	true,
	false, //0x15
	true,
	true,
	true,
	false,
	false,
	false,
	false,
	false
};

//!�������� �������
static const char *CITY_NAMES[9] =
{
	"Yew",
	"Minoc",
	"Britain",
	"Moonglow",
	"Trinsic",
	"Magincia",
	"Jhelom",
	"Skara Brae",
	"Vesper"
};

//!�������� ������ ����������
static char SPELL_CIRCLES_NAMES[8][15] =
{
	"First Circle",
	"Second Circle",
	"Third Circle",
	"Fourth Circle",
	"Fifth Circle",
	"Sixth Circle",
	"Seventh Circle",
	"Eighth Circle"
};

//!����������� �������� �� ����������
static const WORD SPELL_REAGENTS[64][4] =
{
	{ 0x0F7B, 0x0F88, 0, 0 },
	{ 0x0F84, 0x0F85, 0x0F86, 0 },
	{ 0x0F85, 0x0F88, 0, 0 },
	{ 0x0F84, 0x0F85, 0x0F8D, 0 },
	{ 0x0F7A, 0x0F88, 0, 0 },
	{ 0x0F8C, 0x0F8D, 0, 0 },
	{ 0x0F84, 0x0F8C, 0x0F8D, 0 },
	{ 0x0F84, 0x0F88, 0, 0 },
	{ 0x0F7B, 0x0F86, 0, 0 },
	{ 0x0F86, 0x0F88, 0, 0 },
	{ 0x0F84, 0x0F85, 0, 0 },
	{ 0x0F88, 0x0F8D, 0, 0 },
	{ 0x0F84, 0x0F8C, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F8C, 0, 0 },
	{ 0x0F84, 0x0F85, 0x0F8C, 0 },
	{ 0x0F86, 0x0F88, 0, 0 },
	{ 0x0F84, 0x0F86, 0, 0 },
	{ 0x0F7A, 0x0F8C, 0, 0 },
	{ 0x0F8C, 0x0F7B, 0x0F84, 0 },
	{ 0x0F88, 0, 0, 0 },
	{ 0x0F7B, 0x0F86, 0, 0 },
	{ 0x0F7B, 0x0F86, 0, 0 },
	{ 0x0F7B, 0x0F8C, 0, 0 },
	{ 0x0F7B, 0x0F84, 0, 0 },
	{ 0x0F84, 0x0F85, 0x0F86, 0 },
	{ 0x0F84, 0x0F85, 0x0F86, 0x0F8C },
	{ 0x0F84, 0x0F88, 0x0F8C, 0 },
	{ 0x0F7A, 0x0F8D, 0x0F8C, 0 },
	{ 0x0F84, 0x0F85, 0x0F86, 0x0F8D },
	{ 0x0F7A, 0x0F86, 0x0F8C, 0 },
	{ 0x0F7A, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7A, 0x0F7B, 0x0F86, 0 },
	{ 0x0F7A, 0x0F86, 0x0F88, 0 },
	{ 0x0F84, 0x0F7A, 0x0F8D, 0x0F8C },
	{ 0x0F7B, 0x0F84, 0x0F88, 0 },
	{ 0x0F84, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7A, 0x0F86, 0x0F88, 0x0F8C },
	{ 0x0F84, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7A, 0x0F88, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0 },
	{ 0x0F84, 0x0F86, 0x0F8C, 0 },
	{ 0x0F7A, 0x0F88, 0, 0 },
	{ 0x0F7A, 0x0F86, 0x0F8C, 0 },
	{ 0x0F7B, 0x0F88, 0, 0 },
	{ 0x0F7A, 0x0F7B, 0x0F86, 0 },
	{ 0x0F84, 0x0F86, 0x0F88, 0x0F8C },
	{ 0x0F7A, 0x0F85, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F8C, 0, 0 },
	{ 0x0F7A, 0x0F86, 0x0F7B, 0x0F8C },
	{ 0x0F7A, 0x0F86, 0x0F8D, 0x0F8C },
	{ 0x0F8D, 0x0F8C, 0, 0 },
	{ 0x0F7A, 0x0F86, 0x0F8C, 0 },
	{ 0x0F7A, 0x0F7B, 0x0F86, 0x0F8D },
	{ 0x0F7A, 0x0F84, 0x0F86, 0x0F8C },
	{ 0x0F7B, 0x0F8D, 0x0F86, 0x0F8C },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F85, 0x0F86, 0x0F8C },
	{ 0x0F7A, 0x0F7B, 0x0F86, 0x0F88 },
	{ 0x0F7B, 0x0F84, 0x0F85, 0 },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0x0F8C },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0 },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0x0F8C },
	{ 0x0F7B, 0x0F86, 0x0F8D, 0 }
};

//!������������ ����������
static char SPELL_CAST_ABBREVIATURE[64][8] =
{
	"U J",
	"I M Y",
	"R W",
	"I M",
	"I P Y",
	"I L",
	"S F",
	"D M",
	"E U",
	"U W",
	"A N",
	"A M",
	"I J",
	"A J",
	"U S",
	"U M",
	"R S",
	"V F",
	"A P",
	"I N",
	"O P Y",
	"R P",
	"E P",
	"I S Y",
	"W A N",
	"V U S",
	"D S",
	"I F G",
	"I V M",
	"P O G",
	"O R",
	"K O P",
	"I J H Y",
	"A G",
	"K I E",
	"I J S",
	"P C W",
	"A E P",
	"I N G",
	"K X",
	"A O",
	"C P",
	"V O F",
	"K P Y",
	"V D S",
	"I E G",
	"W Q",
	"V O G",
	"I S G",
	"K V F",
	"V R P",
	"O S",
	"V A O",
	"K D F Y",
	"V Y R",
	"I V P",
	"V C P",
	"A C",
	"K V X A",
	"K V X D",
	"K V X T",
	"K V X F",
	"K V X A"
};

//!��������� � ������� � ������������ ���� ��������
struct TREE_UNIONS
{
	//!������ ������ �����������
	WORD GraphicStart;

	//!������ ���������� �����������
	WORD GraphicEnd;
};

//!���������� ��������, ������� �������� �����
const int TREE_COUNT = 9;

//!������ � ��������� ������ (������� �������� �� ������� 7.0.45.0)
static const TREE_UNIONS TREE_INFO[TREE_COUNT] =
{
	{ 0x0D45, 0x0D4C },
	{ 0x0D4D, 0x0D53 },
	{ 0x0D5C, 0x0D62 },
	{ 0x0D63, 0x0D69 },
	{ 0x0D73, 0x0D79 },
	{ 0x0D7A, 0x0D7F },
	{ 0x0D87, 0x0D8B },
	{ 0x0D8C, 0x0D90 },
	{ 0x12BE, 0x12C7 }
};

//!�������� ��� �������� �������� ��������� �� ��� X
const int SITTING_OFFSET_X = 8;

//!��������� ������ � ���������, �� ������� ����� ������ � ��������� �����������
struct SITTING_INFO_DATA
{
	//!������ �������� ��������
	WORD Graphic;

	//!����������� �������� ��� ���������� ���������:
	//!��� 7, 0
	char Direction1; //0

	//!��� 1, 2
	char Direction2; //2
	
	//!��� 3, 4
	char Direction3; //4
	
	//!��� 5, 6
	char Direction4; //6
	
	//!�������� �� ��� Y
	char OffsetY;
	
	//!�������� �� ��� Y ��� ���������� ����������� ���������
	char MirrorOffsetY;

	//!������ ������ ��� ���?
	bool DrawBack;
};

//!���������� ��������, �� ������� ����� ������
const int SITTING_ITEMS_COUNT = 98;

#define SITTING_N 0, 0, 0, 0
#define SITTING_E 2, 2, 2, 2
#define SITTING_S 4, 4, 4, 4
#define SITTING_W 6, 6, 6, 6
#define SITTING_N_S 0, -1, 4, -1
#define SITTING_E_W -1, 2, -1, 6
#define SITTING_ALL 0, 2, 4, 6
#define SITTING_UNKNOWN 0, 2, 4, 6

//!������ � ���������, �� ������� ����� ������ (������� �������� �� ������� 7.0.45.0)
static const SITTING_INFO_DATA SITTING_INFO[SITTING_ITEMS_COUNT] =
{
	{ 0x0459, SITTING_N_S, 2, 2, false },
	{ 0x045A, SITTING_E_W, 2, 2, false },
	{ 0x045B, SITTING_N_S, 2, 2, false },
	{ 0x045C, SITTING_E_W, 2, 2, false },
	{ 0x0A2A, SITTING_ALL, -4, -4, false },
	{ 0x0A2B, SITTING_ALL, -8, -8, false },
	{ 0x0B2C, SITTING_E_W, 2, 2, false },
	{ 0x0B2D, SITTING_N_S, 2, 2, false },
	{ 0x0B2E, SITTING_S, 0, 0, false },
	{ 0x0B2F, SITTING_E, 6, 6, false },
	{ 0x0B30, SITTING_W, -8, 8, true },
	{ 0x0B31, SITTING_N, 0, 4, true },
	{ 0x0B32, SITTING_S, 0, 0, false },
	{ 0x0B33, SITTING_E, 0, 0, false },
	{ 0x0B4E, SITTING_E, 0, 0, false },
	{ 0x0B4F, SITTING_S, 0, 0, false },
	{ 0x0B50, SITTING_N, 0, 0, true },
	{ 0x0B51, SITTING_W, 0, 0, true },
	{ 0x0B52, SITTING_E, 0, 0, false },
	{ 0x0B53, SITTING_S, 0, 0, false },
	{ 0x0B54, SITTING_N, 0, 0, true },
	{ 0x0B55, SITTING_W, 0, 0, true },
	{ 0x0B56, SITTING_E, 4, 4, false },
	{ 0x0B57, SITTING_S, 4, 4, false },
	{ 0x0B58, SITTING_W, 0, 8, true },
	{ 0x0B59, SITTING_N, 0, 8, true },
	{ 0x0B5A, SITTING_E, 8, 8, false },
	{ 0x0B5B, SITTING_S, 8, 8, false },
	{ 0x0B5C, SITTING_N, 0, 8, true },
	{ 0x0B5D, SITTING_W, 0, 8, true },
	{ 0x0B5E, SITTING_ALL, -8, -8, false },
	{ 0x0B5F, SITTING_E_W, 3, 14, false },
	{ 0x0B60, SITTING_E_W, 3, 14, false },
	{ 0x0B61, SITTING_E_W, 3, 14, false },
	{ 0x0B62, SITTING_E_W, 3, 10, false },
	{ 0x0B63, SITTING_E_W, 3, 10, false },
	{ 0x0B64, SITTING_E_W, 3, 10, false },
	{ 0x0B65, SITTING_N_S, 3, 10, false },
	{ 0x0B66, SITTING_N_S, 3, 10, false },
	{ 0x0B67, SITTING_N_S, 3, 10, false },
	{ 0x0B68, SITTING_N_S, 3, 10, false },
	{ 0x0B69, SITTING_N_S, 3, 10, false },
	{ 0x0B6A, SITTING_N_S, 3, 10, false },
	{ 0x0B91, SITTING_S, 6, 6, false },
	{ 0x0B92, SITTING_S, 6, 6, false },
	{ 0x0B93, SITTING_E, 6, 6, false },
	{ 0x0B94, SITTING_E, 6, 6, false },
	{ 0x0CF3, SITTING_E_W, 2, 8, false },
	{ 0x0CF4, SITTING_E_W, 2, 8, false },
	{ 0x0CF6, SITTING_N_S, 2, 8, false },
	{ 0x0CF7, SITTING_N_S, 2, 8, false },
	{ 0x11FC, SITTING_ALL, 2, 7, false },
	{ 0x1218, SITTING_S, 4, 4, false },
	{ 0x1219, SITTING_E, 4, 4, false },
	{ 0x121A, SITTING_N, 0, 8, true },
	{ 0x121B, SITTING_W, 0, 8, true },
	{ 0x1527, SITTING_E, 0, 0, false },
	{ 0x1771, SITTING_ALL, 0, 0, false },
	{ 0x1776, SITTING_ALL, 0, 0, false },
	{ 0x1779, SITTING_ALL, 0, 0, false },
	{ 0x1DC7, SITTING_E_W, 3, 10, false },
	{ 0x1DC8, SITTING_E_W, 3, 10, false },
	{ 0x1DC9, SITTING_E_W, 3, 10, false },
	{ 0x1DCA, SITTING_N_S, 3, 10, false },
	{ 0x1DCB, SITTING_N_S, 3, 10, false },
	{ 0x1DCC, SITTING_N_S, 3, 10, false },
	{ 0x1DCD, SITTING_E_W, 3, 10, false },
	{ 0x1DCE, SITTING_E_W, 3, 10, false },
	{ 0x1DCF, SITTING_E_W, 3, 10, false },
	{ 0x1DD0, SITTING_N_S, 3, 10, false },
	{ 0x1DD1, SITTING_N_S, 3, 10, false },
	{ 0x1DD2, SITTING_E_W, 3, 10, false },
	//!��� ������
	{ 0x2A58, SITTING_S, 0, 0, false },
	{ 0x2A59, SITTING_E, 0, 0, false },
	{ 0x2A5A, SITTING_UNKNOWN, 0, 0, false },
	{ 0x2A5B, SITTING_UNKNOWN, 10, 10, false },
	{ 0x2A7F, SITTING_UNKNOWN, 0, 0, false },
	{ 0x2A80, SITTING_UNKNOWN, 0, 0, false },
	{ 0x2DDF, SITTING_UNKNOWN, 2, 2, false },
	{ 0x2DE0, SITTING_UNKNOWN, 2, 2, false },
	{ 0x2DE3, SITTING_E, 4, 4, false },
	{ 0x2DE4, SITTING_S, 4, 4, false },
	{ 0x2DE5, SITTING_W, 4, 4, false },
	{ 0x2DE6, SITTING_N, 4, 4, false },
	{ 0x2DEB, SITTING_N, 4, 4, false },
	{ 0x2DEC, SITTING_S, 4, 4, false },
	{ 0x2DED, SITTING_E, 4, 4, false },
	{ 0x2DEE, SITTING_W, 4, 4, false },
	{ 0x2DF5, SITTING_UNKNOWN, 4, 4, false },
	{ 0x2DF6, SITTING_UNKNOWN, 4, 4, false },
	{ 0x3088, SITTING_UNKNOWN, 4, 4, false },
	{ 0x3089, SITTING_UNKNOWN, 4, 4, false },
	{ 0x308A, SITTING_UNKNOWN, 4, 4, false },
	{ 0x308B, SITTING_UNKNOWN, 4, 4, false },
	{ 0x35ED, SITTING_UNKNOWN, 0, 0, false },
	{ 0x35EE, SITTING_UNKNOWN, 0, 0, false },
	//
	{ 0x3DFF, SITTING_N_S, 2, 2, false },
	{ 0x3E00, SITTING_E_W, 2, 2, false }
};
//----------------------------------------------------------------------------------
#endif
//----------------------------------------------------------------------------------
