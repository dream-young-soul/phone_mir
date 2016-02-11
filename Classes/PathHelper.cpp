#include "PathHelper.h"
#include "MShare.h"
#include <map>
#include "MapUnit.h"
std::vector<TMapGateInfo*> g_MapGateRoadList;	//寻路路过地图
std::vector<TFindNode*> g_RoadList;
std::vector<unsigned long> g_passPoint;
std::vector<TTree*> g_FreeTreeList;
int g_nEcount;
int g_nGcount ;
//std::vector<TFindNode*> GuajiRoadList;
TLink* Queue,*GuajiQueue;// 保存没有处理的行走方法的节点
void FindMapPath(std::string sMap,std::string sDescMap)
{
	g_MapGateRoadList.clear();
	if(sMap == sDescMap) return;
	std::vector<TLocalMapInfo*> FindMapList;
	std::vector<TLocalMapInfo*> tmplist;
	TMapGateInfo* dgate;
	TLocalMapInfo* mapinfo = nullptr;
	TMapGateInfo* tmpgate;
	int findcount;
	FindMapList.clear();
	tmplist.clear();
	std::map<std::string,TLocalMapInfo*>::iterator it;
	it = g_alllocalmap.find(sMap);
	if(it == g_alllocalmap.end())
	{
		return;
	}
	mapinfo = it->second;
	FindMapList.push_back(mapinfo);
	 //起始地图加入待搜索地图列表
	dgate = nullptr;
	findcount = 0;
	while(true)
	{
		findcount ++;
		if( findcount > 1000)break;    //1000层都找不到，死去
		if(FindMapList.size() == 0)break;  //列表处理完还没找到
		mapinfo = FindMapList[0];
		tmplist.push_back(mapinfo);
		///循环当前搜索地图的所有跳点，看是否能跳到目标地图
		///如果跳不到目标地图，将该跳点对应的目标地图里的所有
		///跳点加入待搜索地图列表
		for(int i = 0;i < (int)mapinfo->Gates.size();i++)
		{
			tmpgate = (TMapGateInfo*)mapinfo->Gates[i];
			if(!tmpgate->DMapInfo)continue;
			bool bFind = false;
			for(int j = 0;j < (int)tmplist.size();j++)
			{
				if(tmplist[j] == tmpgate->DMapInfo)
				{
					bFind = true;
					break;
				}
			}
			if(bFind)continue;
			if(tmpgate->DMapName == sDescMap)
			{
				dgate = tmpgate;
				break;
			}else
			{
				//将目标地图上的所有跳点的来源跳点设为当前跳点
				for(int k = 0;k < (int)tmpgate->DMapInfo->Gates.size();k++)
				{
					((TMapGateInfo*)tmpgate->DMapInfo->Gates[k])->fromGate = tmpgate;
				}
				FindMapList.push_back(tmpgate->DMapInfo);;
			}
			tmplist.push_back(tmpgate->DMapInfo);
		}
		FindMapList.erase(FindMapList.begin());
		if(dgate != nullptr) break;
	}
	
	while(true)
	{
		if(dgate == nullptr)break;
		g_MapGateRoadList.insert(g_MapGateRoadList.begin(), dgate);
		if(dgate->SMapName == sMap)break;
		if(dgate->fromGate == nullptr) break;
		dgate = dgate->fromGate;
	}
	FindMapList.clear();
	tmplist.clear();
	
}

void FindPath(int Startx,int Starty,int end_x,int end_y)
{
	TTree* root,*p;
	int x,y,dir;

	TFindNode* temp;
	bool bTry;
	int ii;

	g_nEcount = 0; g_nGcount = 0;
	if(! VDMap::GetInstance()->CanMove(end_x,end_y))
	{
		return;
	}
	g_passPoint.resize(VDMap::GetInstance()->Header.Height * VDMap::GetInstance()->Header.Width);
	for(int i =0;i < (int)g_passPoint.size();i++)
	{
			g_passPoint[i] = 0xFFFFFFFF;
	}
	Init_Queue();
	root = new TTree();
	root->x = Startx;
	root->y = Starty;
	root->h = 0;
	root->Father = nullptr;
	Enter_Queue(root,judge(Startx,Starty,end_x,end_y));
	g_FreeTreeList.push_back(root);
	ii = 0;
	int index = 0;
	while(true)
	{
		root = Get_From_Queue(); //将第一个弹出
		ii++;
		if(ii == 86610)ii = 0;
		if(root == nullptr) break;

	/*	FILE* f_ = fopen("c:/1.txt","a");
		char sLog[1024];
		sprintf(sLog,"index: %d x: %d y: %d h: %d \n",index,root->x,root->y,root->h);
		fputs(sLog,f_);
		sprintf(sLog,"---------------------------------------------------------------\n");
		fputs(sLog,f_);
		fputs(sLog,f_);
		fclose(f_);*/

		index++;

		x = root->x;
		y = root->y;
		if(x == end_x && y == end_y)
		{
			break;
		}
		bTry =false;
		if (Trytile(x, y - 1, end_x, end_y, root, 0)) bTry = true; //尝试向上移动
		if (Trytile(x + 1, y - 1, end_x, end_y, root, 1)) bTry = true; //尝试向右上移动
		if (Trytile(x + 1, y, end_x, end_y, root, 2)) bTry = true; //尝试向右移动
		if (Trytile(x + 1, y + 1, end_x, end_y, root, 3)) bTry = true; //尝试向右下移动
		if (Trytile(x, y + 1, end_x, end_y, root, 4) ) bTry = true; //尝试向下移动
		if (Trytile(x - 1, y + 1, end_x, end_y, root, 5)) bTry = true; //尝试向左下移动
		if (Trytile(x - 1, y, end_x, end_y, root, 6)) bTry = true; //尝试向左移动
		if (Trytile(x - 1, y - 1, end_x, end_y, root, 7)) bTry = true; //尝试向左上移动
	}

	if(root == nullptr) return;
	g_RoadList.clear();
	temp = new TFindNode();
	temp->x = root->x;
	temp->y = root->y;
	g_RoadList.push_back(temp);
	p = root;
	dir = -1;
	root = root->Father;
	while(root != nullptr)
	{
		if(p->dir != dir || root->dir != dir)
		{
			temp = new TFindNode();
			temp->x = p->x;
			temp->y = p->y;
			g_RoadList.insert(g_RoadList.begin(),temp);
			dir = p->dir;
		}
		p = root;
		root = root->Father;
	}
	FreeTree();
}
void Init_Queue()
{
	if(Queue)
	{
		if(Queue->next)
		{
			delete Queue->next;
		}
		if(Queue->node)delete Queue->node;
		delete Queue;
	}
	Queue = new TLink;
	Queue->node = nullptr;
	Queue->f = -1;
	Queue->next=new TLink;
	Queue->next->f = 0xfffffff;
	Queue->next->node = nullptr;
	Queue->next->next = nullptr;
	for(int i = 0;i < (int)g_RoadList.size();i++)
	{
		TFindNode* n = g_RoadList[i];
		delete n;
	}
	g_RoadList.clear();
}

// 待处理节点入队列, 依靠对目的地估价距离插入排序
void Enter_Queue(TTree* node,int f)
{

	TLink *p = nullptr,*Father = nullptr,*q = nullptr;
	p = Queue;
	Father = p;
	while (f > p->f)
	{
		Father = p;
		p = p->next;
		if(p == nullptr)
		{
			break;
		}
	}
	q = new TLink;
	q->f = f;
	q->node = node;
	q->next = p;
	Father->next =q;

	//FILE* f_ = fopen("c:/1.txt","a");
	//char sLog[1024];
	//sprintf(sLog,"x: %d y: %d h: %d \n",node->x,node->y,node->h);
	//fputs(sLog,f_);
	//fclose(f_);
}

TTree* Get_From_Queue()
{
	TTree* bestchoice;
	TLink* Next;
	bestchoice =Queue->next->node;
	Next = Queue->next->next;
	delete Queue->next;
	Queue->next = Next;
	return bestchoice;
}
// 尝试下一步移动到 x,y 可行否
bool Trytile(int x,int y,int end_x,int end_y,TTree* father,unsigned char dir)
{
	TTree* p;
	unsigned long h;
	bool Result  = false;
	if(!VDMap::GetInstance()->CanMove(x,y))
	{
		return Result;
	}
	p = father;
	while(p != nullptr)
	{
		if(x == p->x && y == p->y)
		{
			return false;
		}
		p = p->Father;
	}
	if(dir == 0 || dir == 2 || dir == 4 || dir == 6)
	{
		h = father->h + 10;
	}else
	{
		h = father->h + 14;
	}
	if(h >= (unsigned long)g_passPoint[x * VDMap::GetInstance()->Header.Height + y])
	{
		return false; //// 如果曾经有更好的方案移动到 (x,y) 失败
	}
	g_passPoint[x * VDMap::GetInstance()->Header.Height + y] = h; // 记录这次到 (x,y) 的距离为历史最佳距离
	g_nEcount ++;
	p = new TTree;
	p->Father = father;
	p->h = h;
	p->x = x;
	p->y = y;
	p->dir = dir;
	Enter_Queue(p,p->h + judge(x,y,end_x,end_y));
	g_FreeTreeList.push_back(p);
	return true;
}

// 估价函数,估价 x,y 到目的地的距离,估计值必须保证比实际值小		
int judge(int x,int y,int end_x,int end_y)
{
	int nx = end_x - x;
	int ny = end_y - y;
	return abs(nx) + abs(ny);
}
// 释放申请过的所有节点
void FreeTree()
{
	TLink* p;
	while(Queue != nullptr)
	{
		p = Queue;
		Queue = Queue->next;
		delete p;
	}
	for(int i = 0;i < (int)g_FreeTreeList.size();i++)
	{
		TTree* t = g_FreeTreeList[i];
		delete t;
	}
	g_FreeTreeList.clear();
}