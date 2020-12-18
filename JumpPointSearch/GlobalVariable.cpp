//-----------------------------------------------------------------
// A Star Algorithm  Global Variable 
//-----------------------------------------------------------------


#include "MyLinkedList.h"
#include <Windows.h>
#include <iostream>
#include "StraightLine.h"
#include "GlobalVariable.h"


unsigned char g_CheckNum = LAST_ATTRIBUTE;

CList<Node*> g_OpenList;
CList<Node*> g_CloseList;
HDC g_HDC;
HWND g_hWnd;
HPEN g_Pen;
HPEN g_WhitePen;
HBRUSH g_RedBrush;
HBRUSH g_BlackBrush;
HBRUSH g_GrayBrush;
HBRUSH g_WhiteBrush;
HBRUSH g_BlueBrush;
HBRUSH g_GreenBrush;
HBRUSH g_YellowBrush;

int32_t g_StartX = -1;
int32_t g_StartY = -1;
int32_t g_PrevStartX = -1;
int32_t g_PrevStartY = -1;

int32_t g_EndX = -1;
int32_t g_EndY = -1;
int32_t g_PrevEndX = -1;
int32_t g_PrevEndY = -1;
unsigned char g_Grid[MAX_HEIGHT][MAX_WIDTH];

bool bStartSetting = false;
bool bEndSetting = true;
bool bBlockSetting = false;
bool bLine = false;
bool bOpti = false;

StraightLine straightLine;


std::vector<Node*> pathNode;
