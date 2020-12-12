#pragma once
#define MAX_WIDTH 90
#define MAX_HEIGHT 35
#define LENGTH 15
#define FGH_ON 0

enum class ParentDirection
{
    RIGHT,
    LEFT,
    UP,
    DOWN,
    LRU,
    RLU,
    LRD,
    RLD,
    ALL
};
struct Node
{
    int x;
    int y;
    int g;
    int h;
    int f;
    Node* parent;
    ParentDirection parentDir;
};

enum
{
    NOTHING,
    START,
    END,
    BLOCK,
    OPEN,
    CLOSE,
    LAST_ATTRIBUTE
};
extern char g_CheckNum;
extern CList<Node*> g_OpenList;
extern CList<Node*> g_CloseList;
extern HDC g_HDC;
extern HWND g_hWnd;
extern HPEN g_Pen;
extern HPEN g_WhitePen;
extern HBRUSH g_RedBrush;
extern HBRUSH g_BlackBrush;
extern HBRUSH g_GrayBrush;
extern HBRUSH g_WhiteBrush;
extern HBRUSH g_BlueBrush;
extern HBRUSH g_GreenBrush;
extern HBRUSH g_YellowBrush;

extern int32_t g_StartX ;
extern int32_t g_StartY ;
extern int32_t g_PrevStartX;
extern int32_t g_PrevStartY;
 
extern int32_t g_EndX;
extern int32_t g_EndY;
extern int32_t g_PrevEndX ;
extern int32_t g_PrevEndY ;
extern char g_Grid[MAX_HEIGHT][MAX_WIDTH];

extern bool bStartSetting;
extern bool bEndSetting ;
extern bool bBlockSetting ;