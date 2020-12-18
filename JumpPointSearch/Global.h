#pragma once

void Init_GDI();
void Draw_Block(int drawX, int drawY);
void Draw_Start(int drawX, int drawY);
void Draw_End(int drawX, int drawY);
void Draw_Nothing(int drawX, int drawY);

void Draw_Grid(HDC hdc);
void Clear_Tile(HDC hdc);
void Draw_Path(Node* curNode);
void Clear_Tile();
void Clear_Except();
void Draw_OpenNClose();


void ReleaseList();
void CheckNodeGen(int x, int y, Node* centerNode, int endX, int endY, bool dFlag);

bool GetStartPoint(int32_t* outX, int32_t* outY);
bool GetEndPoint(int32_t* outX, int32_t* outY);

void GenNearbyNode(Node* centerNode);
bool tempSort(Node* node1, Node* node2);



//--------------------------------------------
// Jump PointSearch Function
//--------------------------------------------

void JPSStart();
void JPSSearch();

void DirectionCheck(Node* node);
void LeftSearch(Node* node, int32_t x, int32_t y, int32_t gValue);
void RightSearch(Node* node, int32_t x, int32_t y,int32_t gValue);
void UpSearch(Node* node, int32_t x, int32_t y, int32_t gValue);
void DownSearch(Node* node, int32_t x, int32_t y, int32_t gValue);
void LRUSearch(Node* node,int32_t x, int32_t y, int32_t gValue);
void LRDSearch(Node* node, int32_t x, int32_t y, int32_t gValue);
void RLUSearch(Node* node, int32_t x, int32_t y, int32_t gValue);
void RLDSearch(Node* node, int32_t x, int32_t y, int32_t gValue);

bool SmallLeftSearch(Node* node, int32_t x, int32_t y);
bool SmallRightSearch(Node* node, int32_t x, int32_t y);
bool SmallUpSearch(Node* node, int32_t x, int32_t y);
bool SmallDownSearch(Node* node, int32_t x, int32_t y);
//--------------------------------------------
// 하나하나 체크하는 Draw
//--------------------------------------------
void Draw_Check(int32_t nodeX, int32_t nodeY);
//--------------------------------------------

//--------------------------------------------
// 체크 다해놓고 한번 그리는 Draw
//--------------------------------------------
void Check_Grid(int32_t nodeX, int32_t nodeY);
void OnlyDraw_Check();
//--------------------------------------------

void CheckNCreateNode(int32_t nodeX, int32_t nodeY, int32_t gValue,ParentDirection parentDir,Node* parentNode);
void CreateNewNode(int32_t nodeX, int32_t nodeY, int32_t gValue, ParentDirection parentDir, Node* parentNode);


//------------------------------------------------
// 라인 그리기
//------------------------------------------------
void Draw_Check2(int32_t nodeX, int32_t nodeY);
void LineTest(int32_t startX, int32_t startY, int32_t endX, int32_t endY);

void CheckLinePath();

bool BlockCheck(int32_t startX, int32_t startY, int32_t endX, int32_t endY);


void DeleteVector(Node* node);

void Draw_OptimizationPath2();

void Draw_OptimizationPath();

void Draw_Block();