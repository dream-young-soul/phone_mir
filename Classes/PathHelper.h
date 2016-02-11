#ifndef PATHHELPER_H_
#define PATHHELPER_H_
#include <string>
#include <vector>
#include "GameStruct.h"
void FindMapPath(std::string sMap,std::string sDescMap);
void FindPath(int Startx,int Starty,int end_x,int end_y);
void Init_Queue();
void Enter_Queue(TTree* node,int f);
TTree* Get_From_Queue();
bool Trytile(int x,int y,int end_x,int end_y,TTree* father,unsigned char dir);
int judge(int x,int y,int end_x,int end_y);
void FreeTree();
extern std::vector<TMapGateInfo*> g_MapGateRoadList;	//寻路路过地图
extern std::vector<TFindNode*> g_RoadList;
extern std::vector<unsigned long> g_passPoint;
extern std::vector<TTree*> g_FreeTreeList;
extern int g_nEcount;
extern int g_nGcount ;
//std::vector<TFindNode*> GuajiRoadList;
extern TLink* Queue,*GuajiQueue;// 保存没有处理的行走方法的节点

#endif