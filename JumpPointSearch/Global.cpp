#include "MyLinkedList.h"
#include <Windows.h>
#include <iostream>
#include "StraightLine.h"
#include "GlobalVariable.h"
#include "Global.h"

#include <algorithm>
#include <stack>

void Init_GDI()
{
    g_HDC = GetDC(g_hWnd);
    g_Pen = CreatePen(PS_NULL, 0, RGB(0, 0, 0));
    g_WhitePen = CreatePen(PS_SOLID, 1, RGB(255, 255, 255));
    g_RedBrush = CreateSolidBrush(RGB(255, 0, 0));
    g_BlackBrush = CreateSolidBrush(RGB(0, 0, 0));;
    g_GrayBrush = CreateSolidBrush(RGB(192, 192, 192));
    g_WhiteBrush = CreateSolidBrush(RGB(255, 255, 255));

    g_BlueBrush = CreateSolidBrush(RGB(0, 0, 255));
    g_GreenBrush = CreateSolidBrush(RGB(0, 255, 0));

    g_YellowBrush = CreateSolidBrush(RGB(255, 255, 0));
}

void Draw_Block(int drawX, int drawY)
{
    HDC hdc = GetDC(g_hWnd);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, g_GrayBrush);

    oldBrush = (HBRUSH)SelectObject(hdc, g_GrayBrush);
    Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);

    SelectObject(hdc, oldBrush);

    ReleaseDC(g_hWnd, hdc);
}

void Draw_Start(int drawX, int drawY)
{
    HDC hdc = GetDC(g_hWnd);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, g_BlackBrush);

    oldBrush = (HBRUSH)SelectObject(hdc, g_BlackBrush);
    Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);

    SelectObject(hdc, oldBrush);

    ReleaseDC(g_hWnd, hdc);
}

void Draw_End(int drawX, int drawY)
{
    HDC hdc = GetDC(g_hWnd);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, g_RedBrush);

    oldBrush = (HBRUSH)SelectObject(hdc, g_RedBrush);
    Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);

    SelectObject(hdc, oldBrush);

    ReleaseDC(g_hWnd, hdc);
}

void Draw_Nothing(int drawX, int drawY)
{
    HDC hdc = GetDC(g_hWnd);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, g_WhiteBrush);

    oldBrush = (HBRUSH)SelectObject(hdc, g_WhiteBrush);
    Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);

    SelectObject(hdc, oldBrush);

    ReleaseDC(g_hWnd, hdc);
}
void Draw_Grid(HDC hdc)
{

    for (size_t x = 0; x <= MAX_WIDTH * LENGTH; x += LENGTH)
    {
        MoveToEx(hdc, x, 0, NULL);
        LineTo(hdc, x, MAX_HEIGHT * LENGTH);
    }

    for (size_t y = 0; y <= MAX_HEIGHT * LENGTH; y += LENGTH)
    {
        MoveToEx(hdc, 0, y, NULL);
        LineTo(hdc, MAX_WIDTH * LENGTH, y);
    }

}

void Draw_OpenNClose()
{
    //----------------------------------수정버전-----------------------------------
    auto openIter = g_OpenList.begin();
    auto closeIter = g_CloseList.begin();


    HDC hdc = GetDC(g_hWnd);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, g_BlueBrush);
    HPEN oldPen = (HPEN)SelectObject(hdc, g_Pen);

    for (; openIter != g_OpenList.end(); ++openIter)
    {
        if (((*openIter)->x == g_StartX && (*openIter)->y == g_StartY) ||
            (*openIter)->x == g_EndX && (*openIter)->y == g_EndY)
        {
            continue;
        }
        int drawX = (*openIter)->x * LENGTH;
        int drawY = (*openIter)->y * LENGTH;

        Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);
        if (FGH_ON)
        {
            WCHAR buf[256];
            wsprintf(buf, L"[G:%d]", (*openIter)->g);
            TextOut(hdc, drawX + (2 / LENGTH), drawY + (2 / LENGTH), buf, wcslen(buf));
            wsprintf(buf, L"[H:%d]", (*openIter)->h);
            TextOut(hdc, drawX + (2 / LENGTH), drawY + (2 / LENGTH) + 20, buf, wcslen(buf));
            wsprintf(buf, L"[F:%d]", (*openIter)->f);
            TextOut(hdc, drawX + (2 / LENGTH), drawY + (2 / LENGTH) + 40, buf, wcslen(buf));
        }

        //_stprintf_s(buf,128,L"[G:%0.2f]", (*openIter)->g);


        //_stprintf_s(buf, 128, L"[H:%0.2f]", (*openIter)->h);
        //
        //_stprintf_s(buf, 128, L"[F:%0.2f]", (*openIter)->f);
        //TextOut(hdc, drawX + (2 / LENGTH), drawY + (2 / LENGTH) + 40, buf, wcslen(buf));
    }


    SelectObject(hdc, g_YellowBrush);
    for (; closeIter != g_CloseList.end(); ++closeIter)
    {
        if (((*closeIter)->x == g_StartX && (*closeIter)->y == g_StartY) ||
            (*closeIter)->x == g_EndX && (*closeIter)->y == g_EndY)
        {
            continue;
        }

        int drawX = (*closeIter)->x * LENGTH;
        int drawY = (*closeIter)->y * LENGTH;

        Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);
        if (FGH_ON)
        {
            WCHAR buf[256];
            wsprintf(buf, L"[G:%d]", (*closeIter)->g);
            TextOut(hdc, drawX + (2 / LENGTH), drawY + (2 / LENGTH), buf, wcslen(buf));
            wsprintf(buf, L"[H:%d]", (*closeIter)->h);
            TextOut(hdc, drawX + (2 / LENGTH), drawY + (2 / LENGTH) + 20, buf, wcslen(buf));
            wsprintf(buf, L"[F:%d]", (*closeIter)->f);
            TextOut(hdc, drawX + (2 / LENGTH), drawY + (2 / LENGTH) + 40, buf, wcslen(buf));
        }

       // WCHAR buf[256];
        /*   _stprintf_s(buf, 128, L"[G:%0.2f]", (*closeIter)->g);
           TextOut(hdc, drawX + (2 / LENGTH), drawY + (2 / LENGTH), buf, wcslen(buf));
           _stprintf_s(buf, 128, L"[H:%0.2f]", (*closeIter)->h);
           TextOut(hdc, drawX + (2 / LENGTH), drawY + (2 / LENGTH) + 20, buf, wcslen(buf));
           _stprintf_s(buf, 128, L"[F:%0.2f]", (*closeIter)->f);
           TextOut(hdc, drawX + (2 / LENGTH), drawY + (2 / LENGTH) + 40, buf, wcslen(buf));*/
    }
    SelectObject(hdc, oldBrush);
    SelectObject(hdc, oldPen);

    ReleaseDC(g_hWnd, hdc);
}

void Clear_Tile(HDC hdc)
{
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, g_WhiteBrush);

    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_WIDTH; x++)
        {
            int drawX = x * LENGTH;
            int drawY = y * LENGTH;
            //oldBrush = (HBRUSH)SelectObject(hdc, g_WhiteBrush);
            Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);
        }
    }
    SelectObject(hdc, oldBrush);
}

void Draw_CurrentTile(HDC hdc)
{
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, g_WhiteBrush);

    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_WIDTH; x++)
        {

            switch (g_Grid[y][x])
            {
            case NOTHING:
                SelectObject(hdc, g_WhiteBrush);
                break;
            case BLOCK:
                SelectObject(hdc, g_GrayBrush);
                break;
            case START:
                SelectObject(hdc, g_BlackBrush);
                break;
            case END:
                SelectObject(hdc, g_BlackBrush);
                break;
            }
            int drawX = x * LENGTH;
            int drawY = y * LENGTH;
            Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);
        }
    }
}
void ReleaseList()
{
    auto iterOpen = g_OpenList.begin();

    for (; iterOpen != g_OpenList.end();)
    {
        delete (*iterOpen);
        iterOpen = g_OpenList.erase(iterOpen);
    }

    auto iterClose = g_CloseList.begin();

    for (; iterClose != g_CloseList.end();)
    {
        delete (*iterClose);
        iterClose = g_CloseList.erase(iterClose);
    }

    g_OpenList.clear();
    g_CloseList.clear();
    
}

void Clear_Tile()
{
    memset(g_Grid, 0, sizeof(g_Grid));
    ReleaseList();
    InvalidateRect(g_hWnd, NULL, TRUE);
}

void Clear_Except()
{
    HDC hdc = GetDC(g_hWnd);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, g_WhiteBrush);
    ReleaseList();

    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_WIDTH; x++)
        {
            if ((x == g_EndX && y == g_EndY) || (x == g_StartX && y == g_StartY))
            {
                continue;
            }
            if (g_Grid[y][x] == BLOCK)
            {
                continue;
            }

            g_Grid[y][x] = NOTHING;
            
        }
    }

    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_WIDTH; x++)
        {
            if (g_Grid[y][x] == NOTHING)
            {
                int drawX = x * LENGTH;
                int drawY = y * LENGTH;
                Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);
            }
        }
    }
    SelectObject(hdc, oldBrush);
    ReleaseDC(g_hWnd, hdc);

    g_CheckNum = LAST_ATTRIBUTE;
}

void CheckNodeGen(int x, int y, Node* centerNode, int endX, int endY, bool dFlag)
{
    Node* changeNode = nullptr;

    if (x < 0 || y < 0)
    {
        return;
    }
    if (x > MAX_WIDTH - 1 || y > MAX_HEIGHT - 1)
    {
        return;
    }
    auto iterOpenList = g_OpenList.begin();
    auto iterCloseList = g_CloseList.begin();

    if (g_Grid[y][x] == BLOCK)
    {
        return;
    }
    for (; iterOpenList != g_OpenList.end(); ++iterOpenList)
    {
        if ((*iterOpenList)->x == x && (*iterOpenList)->y == y)
        {
            //----------------------------------------------------------
            // 이미 오픈리스트에있지만, 해당 G값이 새로 생성된 G보다 작은지 판단
            //----------------------------------------------------------
            if ((*iterOpenList)->g < centerNode->g + 1)
            {
                return;
            }
            else
            {
                changeNode = *iterOpenList;
                break;
            }
        }
    }
    for (; iterCloseList != g_CloseList.end(); ++iterCloseList)
    {
        if ((*iterCloseList)->x == x && (*iterCloseList)->y == y)
        {
            return;
        }
    }
    //----------------------------------------------------------
    // 모든 조건 충족시, 노드를 생성한다.
    //--------------------------------------------------------
    int gValue = 1;
    int hValue = 1;

    if (dFlag)
    {
        gValue = 15;
        hValue = 10;
    }
    else
    {
        gValue = 10;
        hValue = 10;
    }

    if (changeNode != nullptr)
    {
        changeNode->g = centerNode->g + gValue;
        changeNode->f = changeNode->h + changeNode->g;
        changeNode->parent = centerNode;
    }
    else
    {

        Node* newNode = new Node;
        newNode->x = x;
        newNode->y = y;
        newNode->h = (abs(endX - newNode->x) + abs(endY - newNode->y)) * hValue;
        newNode->g = centerNode->g + gValue;
        newNode->f = newNode->h + newNode->g;
        newNode->parent = centerNode;
        g_OpenList.push_back(newNode);
    }
}

void SearchDirection()
{

}



void JPSSearch()
{
    while (g_OpenList.size() != 0)
    {
        g_OpenList.sort(tempSort);

        auto iter = g_OpenList.begin();

        if ((*iter)->x == g_EndX && (*iter)->y == g_EndY)
        {
            pathNode.clear();
            Draw_Path(*iter);
            CheckLinePath();
            Draw_OptimizationPath();
            ReleaseList();
            return;
        }
        DirectionCheck(*iter);

        g_CloseList.push_back(*iter);
        g_OpenList.erase(iter);

        Draw_OpenNClose();
        
    }
    int a = 10;
}



bool GetStartPoint(int32_t* outX, int32_t* outY)
{
    for (int32_t y = 0; y < MAX_HEIGHT; ++y)
    {
        for (int32_t x = 0; x < MAX_WIDTH; ++x)
        {
            if (g_Grid[y][x] == START)
            {
                *outX = x;
                *outY = y;
                return true;
            }
        }
    }

    return false;
}

bool GetEndPoint(int32_t* outX, int32_t* outY)
{
    for (int32_t y = 0; y < MAX_HEIGHT; ++y)
    {
        for (int32_t x = 0; x < MAX_WIDTH; ++x)
        {
            if (g_Grid[y][x] == END)
            {
                *outX = x;
                *outY = y;
                return true;
            }
        }
    }
    return false;
}

void JPSStart()
{
    int startX = 0;
    int startY = 0;
    int endX = 0;
    int endY = 0;

    if (false == GetStartPoint(&startX, &startY))
    {
        MessageBox(g_hWnd, L"Error:Line:236", MB_OK, 0);
    }

    if (false == GetEndPoint(&endX, &endY))
    {
        MessageBox(g_hWnd, L"Error:Line:236", MB_OK, 0);
    }

    char temp = g_Grid[0][1];

    Node* newNode = new Node;
    newNode->x = g_StartX;
    newNode->y = g_StartY;
    newNode->h = abs((g_EndX - g_StartX)) + abs((g_EndY - g_StartY));
    newNode->g = 0;
    newNode->parent = nullptr;

    g_OpenList.push_back(newNode);

    JPSSearch();

}

void GenNearbyNode(Node* centerNode)
{
    //------------------------------------------------------
    //  x-1 y-1      x y-1         x+1  y-1 
    //  x-1,y        /x y/           x+1  y
    //  x-1 y+1      x y+1         x+1  y+1
    //------------------------------------------------------
    int endX = 0;
    int endY = 0;
    GetEndPoint(&endX, &endY);

    CheckNodeGen(centerNode->x - 1, centerNode->y - 1, centerNode, endX, endY, false); // 대각선
    CheckNodeGen(centerNode->x - 1, centerNode->y, centerNode, endX, endY, false);
    CheckNodeGen(centerNode->x - 1, centerNode->y + 1, centerNode, endX, endY, false);// 대각선
    CheckNodeGen(centerNode->x, centerNode->y - 1, centerNode, endX, endY, false);
CheckNodeGen(centerNode->x, centerNode->y + 1, centerNode, endX, endY, false);
CheckNodeGen(centerNode->x + 1, centerNode->y - 1, centerNode, endX, endY, false);// 대각선
CheckNodeGen(centerNode->x + 1, centerNode->y, centerNode, endX, endY, false);
CheckNodeGen(centerNode->x + 1, centerNode->y + 1, centerNode, endX, endY, false);// 대각선
}

bool tempSort(Node* node1, Node* node2)
{
    return node1->f > node2->f;
}

void Draw_Path(Node* curNode)
{
    pathNode.push_back(curNode);

    if (curNode->parent == nullptr)
    {
        return;
    }

    HDC hdc = GetDC(g_hWnd);

    int tempX = (curNode->x * LENGTH) + (LENGTH / 2);
    int tempY = (curNode->y * LENGTH) + (LENGTH / 2);
    int tempParentX = (curNode->parent->x * LENGTH) + (LENGTH / 2);
    int tempParentY = (curNode->parent->y * LENGTH) + (LENGTH / 2);

    MoveToEx(hdc, tempX, tempY, NULL);
    LineTo(hdc, tempParentX, tempParentY);
    ReleaseDC(g_hWnd, hdc);
    Draw_Path(curNode->parent);
}

void DirectionCheck(Node* node)
{
    g_CheckNum++;
    if (g_CheckNum > 254)
    {
        g_CheckNum = LAST_ATTRIBUTE;
    }
    HDC hdc = GetDC(g_hWnd);
    WCHAR string[128];
    wsprintf(string, L"g_CheckNUM:%d", g_CheckNum);
    TextOut(hdc, 20, 20, string, wcslen(string));
    ReleaseDC(g_hWnd, hdc);


    if (node->parent == nullptr)
    {

        LeftSearch(node, node->x - 1, node->y, node->g);
        RightSearch(node, node->x + 1, node->y,node->g);
        UpSearch(node, node->x, node->y - 1,node->g);
        DownSearch(node, node->x, node->y + 1, node->g);
        LRUSearch(node,node->x+1,node->y-1,node->g);
        LRDSearch(node, node->x + 1, node->y + 1, node->g);
        RLUSearch(node, node->x - 1, node->y - 1, node->g);
        RLDSearch(node,node->x-1,node->y+1,node->g);
    }
    else
    {
        switch (node->parentDir)
        {
        case ParentDirection::LEFT:
            if (g_Grid[node->y - 1][node->x] == BLOCK)
            {
                RLUSearch(node, node->x - 1, node->y-1,node->g);
            }
            if (g_Grid[node->y + 1][node->x] == BLOCK)
            {
                RLDSearch(node, node->x - 1, node->y+1,node->g);
            }
            LeftSearch(node, node->x - 1, node->y,node->g);
            break;
        case ParentDirection::RIGHT:
            if (g_Grid[node->y - 1][node->x] == BLOCK)
            {
                LRUSearch(node, node->x + 1, node->y - 1, node->g);
            }
            if (g_Grid[node->y + 1][node->x] == BLOCK)
            {
                LRDSearch(node, node->x +1, node->y + 1, node->g);
            }
             RightSearch(node, node->x + 1, node->y,node->g);
            break;
        case ParentDirection::UP:
            if (g_Grid[node->y ][node->x-1] == BLOCK)
            {
                RLUSearch(node, node->x - 1, node->y - 1, node->g);
            }
            if (g_Grid[node->y][node->x+1] == BLOCK)
            {
                LRUSearch(node, node->x + 1, node->y - 1, node->g);
            }           
            UpSearch(node, node->x, node->y - 1,node->g);
            break;
        case ParentDirection::DOWN:
            if (g_Grid[node->y][node->x - 1] == BLOCK)
            {
                RLDSearch(node, node->x - 1, node->y +1, node->g);
            }
            if (g_Grid[node->y][node->x + 1] == BLOCK)
            {
                LRDSearch(node, node->x + 1, node->y +1, node->g);
            }
            DownSearch(node, node->x, node->y +1, node->g);
            break;
        case ParentDirection::LRD:
            if (g_Grid[node->y-1][node->x] == BLOCK)
            {
                LRUSearch(node, node->x +1, node->y - 1, node->g);
            }
            if (g_Grid[node->y][node->x-1] == BLOCK)
            {
                RLDSearch(node, node->x -1, node->y + 1, node->g);
            }
            RightSearch(node, node->x + 1, node->y, node->g);
            DownSearch(node, node->x, node->y + 1, node->g);
            LRDSearch(node, node->x + 1, node->y + 1, node->g);
            break;
        case ParentDirection::LRU:
            if (g_Grid[node->y][node->x - 1] == BLOCK)
            {
                RLUSearch(node, node->x - 1, node->y - 1, node->g);
            }
            if (g_Grid[node->y + 1][node->x] == BLOCK)
            {
                LRDSearch(node, node->x +1, node->y + 1, node->g);
            }
            RightSearch(node, node->x + 1, node->y, node->g);
            UpSearch(node, node->x, node->y - 1, node->g);
            LRUSearch(node, node->x + 1, node->y - 1, node->g);
            break;
        case ParentDirection::RLD:
            
            if (g_Grid[node->y-1][node->x] == BLOCK)
            {
                RLUSearch(node, node->x -1, node->y - 1, node->g);
            }
            if (g_Grid[node->y][node->x+1] == BLOCK)
            {
                LRDSearch(node, node->x +1, node->y + 1, node->g);
            }
            LeftSearch(node, node->x - 1, node->y, node->g);
            DownSearch(node, node->x, node->y +1, node->g);

            RLDSearch(node, node->x - 1, node->y + 1, node->g);
            break;
        case ParentDirection::RLU:
            if (g_Grid[node->y ][node->x+1] == BLOCK)
            {
                LRUSearch(node, node->x+1 , node->y - 1, node->g);
            }
            if (g_Grid[node->y+1][node->x] == BLOCK)
            {
                RLDSearch(node, node->x - 1, node->y + 1, node->g);
            }
            LeftSearch(node, node->x-1, node->y, node->g);
            UpSearch(node, node->x, node->y-1, node->g);

            RLUSearch(node, node->x-1 , node->y-1 , node->g);
            break;
        }
    }

    //OnlyDraw_Check();
}

void LeftSearch(Node* node, int32_t x, int32_t y,int32_t gValue)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::LEFT, node);
        return;
    }

    //----------------------------------------------------
    // 노드(코너) 생성 조건
    //----------------------------------------------------

    bool bCanMakeCorner = false;

    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX - 1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY - 1][nodeX] == BLOCK &&
            g_Grid[nodeY - 1][nodeX - 1] == NOTHING )
        {
            bCanMakeCorner = true;
        }
    }

    if ((0 <= nodeY + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX - 1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY + 1][nodeX] == BLOCK &&
            g_Grid[nodeY + 1][nodeX - 1] == NOTHING )
        {
            bCanMakeCorner = true;
        }
    }

    if (bCanMakeCorner)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::LEFT, node);
        return;
    }


    //Check_Grid(nodeX, nodeY);
    Draw_Check(nodeX,nodeY);
   
    LeftSearch(node, nodeX - 1, nodeY, gValue+10);
}

void RightSearch(Node* node, int32_t x, int32_t y, int32_t gValue)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::RIGHT, node);
        return;
    }
    //----------------------------------------------------
    // 노드 생성 조건
    //----------------------------------------------------
    bool bCanMakeCorner = false; 


    if (((0 <= nodeY - 1) && (nodeY - 1 <= MAX_HEIGHT - 1) )&&
        ((0 <= nodeX + 1 )&& (nodeX + 1 <= MAX_WIDTH - 1)))
    {

        if (g_Grid[nodeY - 1][nodeX] == BLOCK &&
            g_Grid[nodeY - 1][nodeX + 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if ((0 <= (nodeY + 1) && (nodeY + 1) <= MAX_HEIGHT - 1) &&
        (0 <= (nodeX + 1) && (nodeX + 1) <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY + 1][nodeX] == BLOCK &&
            g_Grid[nodeY + 1][nodeX + 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if (bCanMakeCorner)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::RIGHT, node);
        return;
    }
   

    Draw_Check(nodeX,nodeY);
    //Check_Grid(nodeX, nodeY);
    RightSearch(node, nodeX +1, nodeY, gValue+10);
}

void UpSearch(Node* node, int32_t x, int32_t y, int32_t gValue)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }

    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::UP, node);
        Draw_Check(nodeX, nodeY);
        return;
    }
    //----------------------------------------------------
    // 노드 생성 조건
    //----------------------------------------------------
    bool bCanMakeCorner = false;

    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX - 1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if ((g_Grid[nodeY][nodeX - 1] == BLOCK &&
            g_Grid[nodeY - 1][nodeX - 1] == NOTHING))
        {
            bCanMakeCorner = true;
        }
    }
    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX + 1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY][nodeX + 1] == BLOCK &&
            g_Grid[nodeY - 1][nodeX + 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }
    if (bCanMakeCorner)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::UP, node);
        Draw_Check(nodeX, nodeY);
        return;
    }

   
  
    Draw_Check(nodeX, nodeY);
    //Check_Grid(nodeX, nodeY);
    UpSearch(node, nodeX, nodeY-1, gValue +10);
}

void DownSearch(Node* node, int32_t x, int32_t y, int32_t gValue)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }

    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::DOWN, node);
        return;
    }

    bool bCanMakeCorner = false;

    if ((0 <= nodeY  + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX - 1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if(g_Grid[nodeY][nodeX - 1] == BLOCK &&
            g_Grid[nodeY+1][nodeX - 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if ((0 <= nodeY + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX + 1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY][nodeX + 1] == BLOCK &&
            g_Grid[nodeY + 1][nodeX + 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }
    if (bCanMakeCorner)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::DOWN, node);
        return;
    }


    Draw_Check(nodeX, nodeY);
    //Check_Grid(nodeX, nodeY);
    DownSearch(node, nodeX, nodeY + 1, gValue+10);
}

void LRUSearch(Node* node, int32_t x, int32_t y, int32_t gValue)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::LRU, node);
        //Check_Grid(nodeX, nodeY);
        Draw_Check(nodeX, nodeY);
        return;
    }
    //----------------------------------------------------
    // 노드(코너) 생성 조건
    //----------------------------------------------------

    bool bCanMakeCorner = false;

    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX -1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY][nodeX -1] == BLOCK &&
            g_Grid[nodeY - 1][nodeX -1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if ((0 <= nodeY + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX + 1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY + 1][nodeX] == BLOCK &&
            g_Grid[nodeY + 1][nodeX + 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if (bCanMakeCorner)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::LRU, node);
        //Check_Grid(nodeX, nodeY);
        Draw_Check(nodeX, nodeY);

        return;
    }

    if (SmallRightSearch(node, nodeX+1, nodeY))
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::LRU, node);
        //Check_Grid(nodeX, nodeY);
        Draw_Check(nodeX, nodeY);
        return;
    }

    if (SmallUpSearch(node, nodeX, nodeY-1))
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::LRU, node);
        //Check_Grid(nodeX, nodeY);
        Draw_Check(nodeX, nodeY);
        return;
    }
  
    Draw_Check(nodeX, nodeY);
    //Check_Grid(nodeX, nodeY);
    LRUSearch(node, nodeX +1, nodeY - 1, gValue + 15);
}

void LRDSearch(Node* node, int32_t x, int32_t y, int32_t gValue)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::LRD, node);
        Check_Grid(nodeX, nodeY);
        return;
    }
    //----------------------------------------------------
    // 노드(코너) 생성 조건
    //----------------------------------------------------

    bool bCanMakeCorner = false;

    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX + 1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY-1][nodeX] == BLOCK &&
            g_Grid[nodeY - 1][nodeX + 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if ((0 <= nodeY + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX - 1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY][nodeX-1] == BLOCK &&
            g_Grid[nodeY + 1][nodeX - 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if (bCanMakeCorner)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::LRD, node);
        Check_Grid(nodeX, nodeY);

        return;
    }

    if (SmallRightSearch(node, nodeX+1, nodeY))
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::LRD, node);
        Check_Grid(nodeX, nodeY);
        return;
    }

    if (SmallDownSearch(node, nodeX, nodeY+1))
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::LRD, node);
        Check_Grid(nodeX, nodeY);
        return;
    }
 

    Draw_Check(nodeX, nodeY);
    //Check_Grid(nodeX, nodeY);
    LRDSearch(node, nodeX + 1, nodeY + 1, gValue + 15);
}

void RLUSearch(Node* node, int32_t x, int32_t y, int32_t gValue)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::RLU, node);
        Check_Grid(nodeX, nodeY);
        return;
    }
    //----------------------------------------------------
    // 노드(코너) 생성 조건
    //----------------------------------------------------

    bool bCanMakeCorner = false;

    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX + 1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY][nodeX+1] == BLOCK &&
            g_Grid[nodeY-1 ][nodeX +1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if ((0 <= nodeY + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX - 1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY + 1][nodeX] == BLOCK &&
            g_Grid[nodeY + 1][nodeX - 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if (bCanMakeCorner)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::RLU, node);
        Check_Grid(nodeX, nodeY);

        return;
    }
    
    if (SmallLeftSearch(node, nodeX-1, nodeY))
    {
     
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::RLU, node);
        Check_Grid(nodeX, nodeY);
        return;
    }

    if (SmallUpSearch(node, nodeX, nodeY-1))
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::RLU, node);
        Check_Grid(nodeX, nodeY);
        return;
    }


    Draw_Check(nodeX, nodeY);
    //Check_Grid(nodeX, nodeY);
    RLUSearch(node, nodeX -1, nodeY-1, gValue + 15);
}

void RLDSearch(Node* node, int32_t x, int32_t y, int32_t gValue)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::RLD, node);
        Check_Grid(nodeX, nodeY);
        return;
    }
    //----------------------------------------------------
    // 노드(코너) 생성 조건
    //----------------------------------------------------

    bool bCanMakeCorner = false;

    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX + 1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY-1][nodeX] == BLOCK &&
            g_Grid[nodeY - 1][nodeX -1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if ((0 <= nodeY + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX + 1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY][nodeX+1] == BLOCK &&
            g_Grid[nodeY + 1][nodeX +1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if (bCanMakeCorner)
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::RLD, node);
        Check_Grid(nodeX, nodeY);
        return;
    }

    if (SmallLeftSearch(node, nodeX-1, nodeY))
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::RLD, node);
        Check_Grid(nodeX, nodeY);
        return;
    }

    if (SmallDownSearch(node, nodeX, nodeY+1))
    {
        CheckNCreateNode(nodeX, nodeY, gValue, ParentDirection::RLD, node);
        Check_Grid(nodeX, nodeY);
        return;
    }

    Draw_Check(nodeX, nodeY);
    //Check_Grid(nodeX, nodeY);
    RLDSearch(node, nodeX - 1, nodeY + 1, gValue + 15);
}

bool SmallLeftSearch(Node* node, int32_t x, int32_t y)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return false;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return false;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        return true;
    }
    //----------------------------------------------------
    // 노드(코너) 생성 조건
    //----------------------------------------------------

    bool bCanMakeCorner = false;

    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX - 1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY - 1][nodeX] == BLOCK &&
            g_Grid[nodeY - 1][nodeX - 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if ((0 <= nodeY + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX - 1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY + 1][nodeX] == BLOCK &&
            g_Grid[nodeY + 1][nodeX - 1] == NOTHING )
        {
            bCanMakeCorner = true;
        }
    }

    if (bCanMakeCorner)
    {
        return true;
    }


     Draw_Check(nodeX, nodeY);
    //Check_Grid(nodeX, nodeY);
    return SmallLeftSearch(node, nodeX - 1, nodeY);
}

bool SmallRightSearch(Node* node, int32_t x, int32_t y)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return false;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return false;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        return true;
    }
    //----------------------------------------------------
    // 노드(코너) 생성 조건
    //----------------------------------------------------

    bool bCanMakeCorner = false;

    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX -+1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY - 1][nodeX] == BLOCK &&
            g_Grid[nodeY - 1][nodeX + 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if ((0 <= nodeY + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX + 1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY + 1][nodeX] == BLOCK &&
            g_Grid[nodeY + 1][nodeX + 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if (bCanMakeCorner)
    {
        return true;
    }

     Draw_Check(nodeX, nodeY);
    //Check_Grid(nodeX, nodeY);
    return SmallRightSearch(node, nodeX + 1, nodeY);
}

bool SmallUpSearch(Node* node, int32_t x, int32_t y)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return false;
    }

    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return false;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        return true;
    }
    //----------------------------------------------------
    // 노드(코너) 생성 조건
    //----------------------------------------------------

    bool bCanMakeCorner = false;

    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX - 1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if ((g_Grid[nodeY][nodeX - 1] == BLOCK &&
            g_Grid[nodeY - 1][nodeX - 1] == NOTHING)) 
        {
            bCanMakeCorner = true;
        }
    }

    if ((0 <= nodeY - 1 && nodeY - 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX + 1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY][nodeX + 1] == BLOCK &&
            g_Grid[nodeY - 1][nodeX + 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }

    if (bCanMakeCorner)
    {
        return true;
    }



    Draw_Check(nodeX, nodeY);
    //Check_Grid(nodeX, nodeY);
    return SmallUpSearch(node, nodeX, nodeY-1);
}

bool SmallDownSearch(Node* node, int32_t x, int32_t y)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return false;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return false;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        return true;
    }
    //----------------------------------------------------
    // 노드(코너) 생성 조건
    //----------------------------------------------------

    bool bCanMakeCorner = false;

    if ((0 <= nodeY + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX - 1 && nodeX - 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY][nodeX - 1] == BLOCK &&
            g_Grid[nodeY + 1][nodeX - 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }
    if ((0 <= nodeY + 1 && nodeY + 1 <= MAX_HEIGHT - 1) &&
        (0 <= nodeX + 1 && nodeX + 1 <= MAX_WIDTH - 1))
    {
        if (g_Grid[nodeY][nodeX + 1] == BLOCK &&
            g_Grid[nodeY + 1][nodeX + 1] == NOTHING)
        {
            bCanMakeCorner = true;
        }
    }
    if (bCanMakeCorner)
    {
        return true;
    }


    Draw_Check(nodeX,nodeY);
    //Check_Grid(nodeX, nodeY);
    return SmallDownSearch(node, nodeX, nodeY + 1);
}

void Draw_Check(int32_t nodeX, int32_t nodeY)
{
    //Sleep(30);
    
    if (g_Grid[nodeY][nodeX] == BLOCK )
    {
        return;
    }
    if ((nodeX == g_EndX && nodeY == g_EndY) || (nodeX == g_StartX && nodeY == g_StartY))
    {
        return;
    }
    
    g_Grid[nodeY][nodeX] = g_CheckNum;

   
    HDC hdc = GetDC(g_hWnd);
    unsigned char r = (g_CheckNum * 50) % 200;
    unsigned char g = (g_CheckNum*30)%200;
    unsigned char b = (g_CheckNum * 70) % 200;

    //// Red Black Green Blue White Gray
    //if (r == 254)
    //{
    //    r -= 100;
    //}
    //if (g == 254)
    //{
    //    g -= 100;
    //}
    //if (b == 255)
    //{
    //    b -= 100;
    //}

    HBRUSH  randBrush = CreateSolidBrush(RGB(r, g, b));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, randBrush);
    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_WIDTH; x++)
        {

            if ((x == g_EndX && y == g_EndY) || (x == g_StartX && y == g_StartY))
            {
                continue;
            }
            if (g_Grid[y][x] == BLOCK)
            {
                continue;
            }
         
            if (g_Grid[y][x] == g_CheckNum)
            {
                int drawX = x * LENGTH;
                int drawY = y * LENGTH;

                Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);
            }
        }
    }
    SelectObject(hdc, oldBrush);
    DeleteObject(randBrush);
    ReleaseDC(g_hWnd, hdc);

    Draw_OpenNClose();

}

void Check_Grid(int32_t nodeX, int32_t nodeY)
{
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if ((nodeX == g_EndX && nodeY == g_EndY) || (nodeX == g_StartX && nodeY == g_StartY))
    {
        return;
    }
    g_Grid[nodeY][nodeX] = g_CheckNum;

}

void OnlyDraw_Check()
{
    HDC hdc = GetDC(g_hWnd);
    unsigned char r = 100;
    unsigned char g = (g_CheckNum * 10) % 200;
    unsigned char b = 54;

    HBRUSH  randBrush = CreateSolidBrush(RGB(r, g, b));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, randBrush);
    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_WIDTH; x++)
        {

            if ((x == g_EndX && y == g_EndY) || (x == g_StartX && y == g_StartY))
            {
                continue;
            }
            if (g_Grid[y][x] == BLOCK)
            {
                continue;
            }

            if (g_Grid[y][x] == g_CheckNum)
            {
                int drawX = x * LENGTH;
                int drawY = y * LENGTH;

                Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);
            }
        }
    }
    SelectObject(hdc, oldBrush);
    DeleteObject(randBrush);
    ReleaseDC(g_hWnd, hdc);

    Draw_OpenNClose();
}

void CheckNCreateNode(int32_t nodeX, int32_t nodeY, int32_t gValue, ParentDirection parentDir, Node* parentNode)
{
    auto openIter = g_OpenList.begin();
    auto closeIter = g_CloseList.begin();

    Node* changeNode = nullptr;

    for (; openIter != g_OpenList.end(); ++openIter)
    {
        if ((*openIter)->x == nodeX && (*openIter)->y == nodeY)
        {
            if (gValue < (*openIter)->g)
            {
                changeNode = *openIter;
                break;
            }
            else
            {
                return;
            }
        }
    }
    for (; closeIter != g_CloseList.end(); ++closeIter)
    {
        if ((*closeIter)->x == nodeX && (*closeIter)->y == nodeY)
        {
            return;
        }
    }

    if (changeNode != nullptr)
    {
        changeNode->g = gValue;
        changeNode->f = changeNode->g + changeNode->h;
        changeNode->parentDir = parentDir;
        changeNode->parent = parentNode;
    }
    else
    {
        CreateNewNode(nodeX, nodeY, gValue, parentDir, parentNode);
    }
  
}

void CreateNewNode(int32_t nodeX, int32_t nodeY,int32_t gValue,ParentDirection parentDir, Node* parentNode)
{
    int hValue = 10;

    Node* newNode = new Node;
    newNode->x = nodeX;
    newNode->y = nodeY;
    newNode->h = (abs(g_EndX - newNode->x) + abs(g_EndY - newNode->y)) * hValue;
    newNode->g = gValue;
    newNode->f = newNode->h + newNode->g;
    newNode->parent = parentNode;
    newNode->parentDir = parentDir;
    g_OpenList.push_back(newNode); 
}

void Draw_Check2(int32_t nodeX, int32_t nodeY)
{
    HDC hdc = GetDC(g_hWnd);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, g_GreenBrush);

    int drawX = nodeX * LENGTH;
    int drawY = nodeY * LENGTH;
    Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);

    SelectObject(hdc, oldBrush);
    ReleaseDC(g_hWnd, hdc);
}

void LineTest(int32_t startX, int32_t startY, int32_t endX, int32_t endY)
{
    int xDelta = endX - startX;
    int yDelta = endY - startY;

    int absXDelta = abs(xDelta);
    int absYDelta = abs(yDelta);

    bool bDeltaDiff = abs(xDelta) > abs(yDelta);

    int error = 0;
    int xCount = 0;
    int yCount = 0;

    int delValue = 0;
    int loopCount = 0;
    bool bFirst = true;

    if (bDeltaDiff)
    {
        while (g_StartX + xCount != endX || g_StartY + yCount != endY)
        {
            if (yDelta == 0)
            {
                if (xDelta > 0)
                {
                    ++xCount;
                }
                else
                {
                    --xCount;
                }
                Draw_Check2(g_StartX + xCount, g_StartY + yCount);

            }
            else if (abs(yDelta) == 1)
            {
                if (bFirst)
                {
                    delValue = absXDelta / 2;
                    loopCount = absXDelta - delValue;
                }
                while (true)//error < loopCount)
                {
                    error += absYDelta;
                    if (xDelta > 0)
                    {
                        xCount++;
                    }
                    else
                    {
                        xCount--;
                    }
                    if (error >= loopCount)
                    {
                        break;
                    }
                    Draw_Check2(g_StartX + xCount, g_StartY + yCount);
                }
                if (bFirst)
                {
                    error -= loopCount;
                    if (yDelta > 0)
                    {
                        yCount++;
                    }
                    else
                    {
                        yCount--;
                    }
                    loopCount = absXDelta - loopCount;
                    bFirst = false;
                }
                Draw_Check2(g_StartX + xCount, g_StartY + yCount);
            }
            else
            {
                while (true)//error < absXDelta)
                {
                    error += absYDelta;

                    if (xDelta > 0)
                    {
                        xCount++;
                    }
                    else
                    {
                        xCount--;
                    }

                    if (error >= absXDelta)
                    {
                        break;
                    }
                    Draw_Check2(g_StartX + xCount, g_StartY + yCount);
                }
                error -= absXDelta;
                if (yDelta > 0)
                {
                    yCount++;
                }
                else
                {
                    yCount--;
                }
                Draw_Check2(g_StartX + xCount, g_StartY + yCount);
            }
        }
    }
    else
    {
        while (g_StartX + xCount != endX || g_StartY + yCount != endY)
        {

            if (xDelta == 0)
            {
                if (yDelta > 0)
                {
                    yCount++;
                }
                else
                {
                    yCount--;
                }
                Draw_Check2(g_StartX + xCount, g_StartY + yCount);
            }
            else if (abs(xDelta) == 1)
            {
                if (bFirst)
                {
                    delValue = absYDelta / 2;
                    loopCount = absYDelta - delValue;
                }
                while (true)
                {
                    error += absXDelta;
                    if (yDelta > 0)
                    {
                        yCount++;
                    }
                    else
                    {
                        yCount--;
                    }
                    if (error >= loopCount)
                    {
                        break;
                    }
                    Draw_Check2(g_StartX + xCount, g_StartY + yCount);
                }
                if (bFirst)
                {
                    error -= loopCount;
                    if (xDelta > 0)
                    {
                        xCount++;
                    }
                    else
                    {
                        xCount--;
                    }
                    loopCount = absYDelta - loopCount;
                    bFirst = false;
                }
                Draw_Check2(g_StartX + xCount, g_StartY + yCount);
            }
            else
            {
                while (true)
                {
                    error += absXDelta;
                    if (yDelta > 0)
                    {
                        yCount++;
                    }
                    else
                    {
                        yCount--;
                    }
                    if (error >= absYDelta)
                    {
                        break;
                    }
                    Draw_Check2(g_StartX + xCount, g_StartY + yCount);
                }
                error -= absYDelta;

                if (xDelta > 0)
                {
                    xCount++;
                }
                else
                {
                    xCount--;
                }
                Draw_Check2(g_StartX + xCount, g_StartY + yCount);
            }
        }
    }

}

void CheckLinePath()
{
    int index1 = 0;
    int index2 = index1+1;
    std::stack<Node*> tempStack;

    while (index2< pathNode.size())
    {
            //직선체크하다가 블락을 만나버리면
            if (!BlockCheck(pathNode[index1]->x, pathNode[index1]->y, pathNode[index2]->x, pathNode[index2]->y))
            {
                //첫번째꺼 제외
                tempStack.pop();
                int cnt = 0;
                while (!tempStack.empty())
                {
                    DeleteVector(tempStack.top());
                    tempStack.pop();
                    cnt++;
                }
                index1 = index2 - 1-cnt;
                index2 = index1;    
            }
            else
            {
                tempStack.push(pathNode[index2]);
                if (index2 == pathNode.size() - 1)
                {
                    tempStack.pop();

                    while (!tempStack.empty())
                    {
                        DeleteVector(tempStack.top());
                        tempStack.pop();
                    }
                }
            }
            index2++;
    }
}

bool BlockCheck(int32_t startX, int32_t startY, int32_t endX, int32_t endY)
{
    std::vector<StraightLine::Point*> temp = straightLine.GetLineValue(startX, startY, endX, endY);

    for (size_t i = 0; i < temp.size(); i++)
    {
        if (g_Grid[temp[i]->m_Y][temp[i]->m_X] == BLOCK)
        {
            return false;
        }
    }
    return true;
}

void DeleteVector(Node* node)
{
    auto iter = pathNode.begin();

    for (; iter != pathNode.end();++iter)
    {
        if ((*iter) == node)
        {
            pathNode.erase(iter);
            break;

        }
    }
}

void Draw_OptimizationPath2()
{
    for (size_t i = 0; i + 1 < pathNode.size(); i++)
    {
        std::vector<StraightLine::Point*> temp = straightLine.GetLineValue(pathNode[i]->x, pathNode[i]->y, pathNode[i + 1]->x, pathNode[i + 1]->y);

        for (size_t i = 0; i < temp.size(); i++)
        {
            Draw_Check2(temp[i]->m_X, temp[i]->m_Y);
        }
    }
}
void Draw_OptimizationPath()
{
    HDC hdc = GetDC(g_hWnd);
    HPEN pen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));

    HPEN oldPen = (HPEN)SelectObject(hdc, pen);

    for (size_t i = 0; i+1 < pathNode.size(); i++)
    {
        int tempX = (pathNode[i]->x * LENGTH) + (LENGTH / 2);
        int tempY = (pathNode[i]->y * LENGTH) + (LENGTH / 2);
        int tempParentX = (pathNode[i+1]->x * LENGTH) + (LENGTH / 2);
        int tempParentY = (pathNode[i + 1]->y * LENGTH) + (LENGTH / 2);
        MoveToEx(hdc, tempX, tempY, NULL);
        LineTo(hdc, tempParentX, tempParentY);
    }
 
    SelectObject(hdc, oldPen);
    DeleteObject(pen);
    ReleaseDC(g_hWnd, hdc);
}

void Draw_Block()
{
    HDC hdc = GetDC(g_hWnd);
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, g_GrayBrush);


    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_WIDTH; x++)
        {
            if (g_Grid[y][x] == BLOCK)
            {
                int drawX = x * LENGTH;
                int drawY = y * LENGTH;
                Rectangle(hdc, drawX, drawY, drawX + LENGTH, drawY + LENGTH);
            }
        }
    }
    SelectObject(hdc, oldBrush);
    ReleaseDC(g_hWnd, hdc);
}
