#include "MyLinkedList.h"
#include <Windows.h>
#include <iostream>
#include "GlobalVariable.h"
#include "Global.h"

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
    //----------------------------------��������-----------------------------------
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


    SelectObject(hdc, g_GreenBrush);
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

void Draw_Tile(HDC hdc)
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
            // �̹� ���¸���Ʈ��������, �ش� G���� ���� ������ G���� ������ �Ǵ�
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
    // ��� ���� ������, ��带 �����Ѵ�.
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

        int endX = 0;
        int endY = 0;

        GetEndPoint(&endX, &endY);

        if ((*iter)->x == endX && (*iter)->y == endY)
        {
            Draw_Path(*iter);

            ReleaseList();
            return;
        }
        //GenNearbyNode(*iter);
        DirectionCheck(*iter);

        g_CloseList.push_back(*iter);
        g_OpenList.erase(iter);

        Draw_OpenNClose();
        Sleep(15);
    }
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

    Node* newNode = new Node;
    newNode->x = startX;
    newNode->y = startY;
    newNode->h = abs((endX - startX)) + abs((endY - startY));
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

    CheckNodeGen(centerNode->x - 1, centerNode->y - 1, centerNode, endX, endY, false); // �밢��
    CheckNodeGen(centerNode->x - 1, centerNode->y, centerNode, endX, endY, false);
    CheckNodeGen(centerNode->x - 1, centerNode->y + 1, centerNode, endX, endY, false);// �밢��
    CheckNodeGen(centerNode->x, centerNode->y - 1, centerNode, endX, endY, false);
    CheckNodeGen(centerNode->x, centerNode->y + 1, centerNode, endX, endY, false);
    CheckNodeGen(centerNode->x + 1, centerNode->y - 1, centerNode, endX, endY, false);// �밢��
    CheckNodeGen(centerNode->x + 1, centerNode->y, centerNode, endX, endY, false);
    CheckNodeGen(centerNode->x + 1, centerNode->y + 1, centerNode, endX, endY, false);// �밢��
}

bool tempSort(Node* node1, Node* node2)
{
    return node1->f > node2->f;
}

void Draw_Path(Node* curNode)
{
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
    if (node->parent == nullptr)
    {
        
        LeftSearch(node,node->x-1,node->y);        
        RightSearch(node,node->x+1,node->y);
        UpSearch(node, node->x, node->y - 1);
        DownSearch(node, node->x, node->y + 1);
        LRUSearch(node);
        LRDSearch(node);
        RLUSearch(node);
        RLDSearch(node);
    }
    else
    {
        switch (node->parentDir)
        {
        case ParentDirection::LEFT:
            if (g_Grid[node->y - 1][node->x] == BLOCK)
            {
              // RLUSearch(node, node->x - 1, node->y);
            }
            if (g_Grid[node->y + 1][node->x] == BLOCK)
            {
                // RLDSearch(node, node->x - 1, node->y);
            }
            break;
        case ParentDirection::RIGHT:
            RightSearch(node,node->x+1,node->y);
            break;
        case ParentDirection::UP:
            UpSearch(node,node->x,node->y-1);
            break;
        case ParentDirection::DOWN:
            DownSearch(node, node->x, node->y + 1);
            break;
        case ParentDirection::LRD:
            LRDSearch(node);
            break;
        case ParentDirection::RLD:
            RLDSearch(node);
            break;
        case ParentDirection::LRU:
            LRUSearch(node);
            break;
        case ParentDirection::RLU:
            RLUSearch(node);
            break;
        }
    }
    Draw_Check();

    

    
}

void LeftSearch(Node* node, int32_t x, int32_t y)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY>MAX_HEIGHT-1  || nodeX<0 || nodeY <0)
    {
        return;
    }
    //----------------------------------------------------
    // ��� ���� ����
    //----------------------------------------------------
    if ((g_Grid[nodeY - 1][nodeX] == BLOCK   && 
        g_Grid[nodeY - 1][nodeX-1]==NOTHING&&
        g_Grid[nodeY][nodeX-1]==NOTHING) ||
        (g_Grid[nodeY +1][nodeX] == BLOCK &&
         g_Grid[nodeY +1][nodeX - 1] == NOTHING &&
         g_Grid[nodeY][nodeX - 1] == NOTHING))
    {
        int gValue = 10;
        int hValue = 1;

        Node* newNode = new Node;
        newNode->x = nodeX;
        newNode->y = nodeY;
        newNode->h = (abs(g_EndX - newNode->x) + abs(g_EndY - newNode->y)) * hValue;
        newNode->g = node->g + gValue;
        newNode->f = newNode->h + newNode->g;
        newNode->parent = node;
        newNode->parentDir = ParentDirection::LEFT;
        g_OpenList.push_back(newNode);
        return;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        int gValue = 10;
        int hValue = 1;

        Node* newNode = new Node;
        newNode->x = nodeX;
        newNode->y = nodeY;
        newNode->h = (abs(g_EndX - newNode->x) + abs(g_EndY - newNode->y)) * hValue;
        newNode->g = node->g + gValue;
        newNode->f = newNode->h + newNode->g;
        newNode->parent = node;
        newNode->parentDir = ParentDirection::LEFT;
        g_OpenList.push_back(newNode);
        return;
    }
    g_Grid[nodeY][nodeX] = g_CheckNum;
    LeftSearch(node, nodeX - 1, nodeY);
}

void RightSearch(Node* node, int32_t x, int32_t y)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }
    //----------------------------------------------------
    // ��� ���� ����
    //----------------------------------------------------
    if ((g_Grid[nodeY - 1][nodeX] == BLOCK &&
        g_Grid[nodeY - 1][nodeX + 1] == NOTHING &&
        g_Grid[nodeY][nodeX +1] == NOTHING) ||
        (g_Grid[nodeY + 1][nodeX] == BLOCK &&
            g_Grid[nodeY + 1][nodeX + 1] == NOTHING &&
            g_Grid[nodeY][nodeX + 1] == NOTHING))
    {
        int gValue = 10;
        int hValue = 1;

        Node* newNode = new Node;
        newNode->x = nodeX;
        newNode->y = nodeY;
        newNode->h = (abs(g_EndX - newNode->x) + abs(g_EndY - newNode->y)) * hValue;
        newNode->g = node->g + gValue;
        newNode->f = newNode->h + newNode->g;
        newNode->parent = node;
        newNode->parentDir = ParentDirection::RIGHT;
        g_OpenList.push_back(newNode);
        return;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        int gValue = 10;
        int hValue = 1;

        Node* newNode = new Node;
        newNode->x = nodeX;
        newNode->y = nodeY;
        newNode->h = (abs(g_EndX - newNode->x) + abs(g_EndY - newNode->y)) * hValue;
        newNode->g = node->g + gValue;
        newNode->f = newNode->h + newNode->g;
        newNode->parent = node;
        newNode->parentDir = ParentDirection::RIGHT;
        g_OpenList.push_back(newNode);
        return;
    }
    g_Grid[nodeY][nodeX] = g_CheckNum;
    RightSearch(node, nodeX +1, nodeY);
}

void UpSearch(Node* node, int32_t x, int32_t y)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }
    //----------------------------------------------------
    // ��� ���� ����
    //----------------------------------------------------
    if ((g_Grid[nodeY][nodeX-1] == BLOCK &&
        g_Grid[nodeY-1][nodeX + 1] == NOTHING &&
        g_Grid[nodeY-1][nodeX - 1] == NOTHING) ||
        (g_Grid[nodeY][nodeX+1] == BLOCK &&
            g_Grid[nodeY - 1][nodeX + 1] == NOTHING &&
            g_Grid[nodeY-1][nodeX - 1] == NOTHING))
    {
        int gValue = 10;
        int hValue = 1;

        Node* newNode = new Node;
        newNode->x = nodeX;
        newNode->y = nodeY;
        newNode->h = (abs(g_EndX - newNode->x) + abs(g_EndY - newNode->y)) * hValue;
        newNode->g = node->g + gValue;
        newNode->f = newNode->h + newNode->g;
        newNode->parent = node;
        newNode->parentDir = ParentDirection::UP;
        g_OpenList.push_back(newNode);
        return;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        int gValue = 10;
        int hValue = 1;

        Node* newNode = new Node;
        newNode->x = nodeX;
        newNode->y = nodeY;
        newNode->h = (abs(g_EndX - newNode->x) + abs(g_EndY - newNode->y)) * hValue;
        newNode->g = node->g + gValue;
        newNode->f = newNode->h + newNode->g;
        newNode->parent = node;
        newNode->parentDir = ParentDirection::UP;
        g_OpenList.push_back(newNode);
        return;
    }
    g_Grid[nodeY][nodeX] = g_CheckNum;
    UpSearch(node, nodeX, nodeY-1);
}

void DownSearch(Node* node, int32_t x, int32_t y)
{
    int nodeX = x;
    int nodeY = y;

    if (nodeX > MAX_WIDTH - 1 || nodeY > MAX_HEIGHT - 1 || nodeX < 0 || nodeY < 0)
    {
        return;
    }
    //----------------------------------------------------
    // ��� ���� ����
    //----------------------------------------------------
    if ((g_Grid[nodeY][nodeX - 1] == BLOCK &&
        g_Grid[nodeY + 1][nodeX + 1] == NOTHING &&
        g_Grid[nodeY + 1][nodeX - 1] == NOTHING) ||
        (g_Grid[nodeY][nodeX + 1] == BLOCK &&
            g_Grid[nodeY + 1][nodeX + 1] == NOTHING &&
            g_Grid[nodeY + 1][nodeX - 1] == NOTHING))
    {
        int gValue = 10;
        int hValue = 1;

        Node* newNode = new Node;
        newNode->x = nodeX;
        newNode->y = nodeY;
        newNode->h = (abs(g_EndX - newNode->x) + abs(g_EndY - newNode->y)) * hValue;
        newNode->g = node->g + gValue;
        newNode->f = newNode->h + newNode->g;
        newNode->parent = node;
        newNode->parentDir = ParentDirection::DOWN;
        g_OpenList.push_back(newNode);
        return;
    }
    if (g_Grid[nodeY][nodeX] == BLOCK)
    {
        return;
    }
    if (nodeX == g_EndX && nodeY == g_EndY)
    {
        int gValue = 10;
        int hValue = 1;

        Node* newNode = new Node;
        newNode->x = nodeX;
        newNode->y = nodeY;
        newNode->h = (abs(g_EndX - newNode->x) + abs(g_EndY - newNode->y)) * hValue;
        newNode->g = node->g + gValue;
        newNode->f = newNode->h + newNode->g;
        newNode->parent = node;
        newNode->parentDir = ParentDirection::DOWN;
        g_OpenList.push_back(newNode);
        return;
    }
    g_Grid[nodeY][nodeX] = g_CheckNum;
    DownSearch(node, nodeX, nodeY + 1);
}

void LRUSearch(Node* node)
{
}

void LRDSearch(Node* node)
{
}

void RLUSearch(Node* node)
{
}

void RLDSearch(Node* node)
{
}

void Draw_Check()
{
    HDC hdc = GetDC(g_hWnd);

    HBRUSH  randBrush = CreateSolidBrush(RGB(rand() % 255, rand() % 255, rand() % 255));
    HBRUSH oldBrush = (HBRUSH)SelectObject(hdc, randBrush);
    for (int y = 0; y < MAX_HEIGHT; y++)
    {
        for (int x = 0; x < MAX_WIDTH; x++)
        {
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
}
