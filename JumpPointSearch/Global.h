#pragma once


void Init_GDI();
void Draw_Block(int drawX, int drawY);
void Draw_Start(int drawX, int drawY);
void Draw_End(int drawX, int drawY);
void Draw_Nothing(int drawX, int drawY);

void Draw_Grid(HDC hdc);
void Draw_Tile(HDC hdc);
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
void LeftSearch(Node* node, int32_t x, int32_t y);
void RightSearch(Node* node, int32_t x, int32_t y);
void UpSearch(Node* node, int32_t x, int32_t y);
void DownSearch(Node* node, int32_t x, int32_t y);
void LRUSearch(Node* node);
void LRDSearch(Node* node);
void RLUSearch(Node* node);
void RLDSearch(Node* node);

void Draw_Check();