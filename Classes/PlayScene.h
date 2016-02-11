#ifndef PLAYSCENE_H_
#define PLAYSCENE_H_
#include "cocos2d.h"
#include <vector>
#include "GameStruct.h"
#include "VD_Share.h"
class TActor;
class TMagicEff;
//地图蒙板--

class TPlayScene
{
public:
	TPlayScene(void);
	 ~TPlayScene(void);
	 static TPlayScene* GetInstance();
	 void PlayScene(); //绘制地砖 人物- 处理人物消息
	 void DrawScreen(); //绘制名字 蓝条之类的
	 void DrawTileMap();
	 //void DrawMapMask(cocos2d::GLProgram* gl);//绘制地图遮罩蒙板信息
	  bool IsMapMask(TActor* actor);
	 void ProcessNetEvent();
	 TActor* GetAttackFocusCharacter(int X,int Y,int wantsel,int &nowsel,bool liveonly);
	 TActor* GetCharacter(int X,int Y,int wantsel, int &nowsel,bool liveonly);
	 void SendMsg(int ident,int chrid,int x,int y,int cdir,int Feature,
		 int State,const char* str,int Fetureex = 0);
private:
	int m_nDefXX;
	int m_nDefYY;
private:
	cocos2d::Layer* m_LayerTitle;
	cocos2d::Layer* m_LayerActor; //npc 人物场景
	cocos2d::Layer* m_LayerUI; //UI场景
	int m_nLastTime;
public:
	cocos2d::Layer* GetTitleLayer(){return m_LayerTitle;} //取地砖层_
	cocos2d::Layer* GetActorLayer(){return m_LayerActor;} //取角色层
	cocos2d::Layer* GetUILayer(){return m_LayerUI;} //取UI层
	void CXYfromMouseXY(int x,int y,int &ccx,int &ccy);
	TActor* NewActor(int chrid,unsigned short cx,unsigned short cy,unsigned short cdir,
		int cfeature,int cstate, int featureEx = 0);

	void NewMagic(TActor* aowner,int magid,int magnumb,int cx,int cy,int tx,int ty,int targetcode
		,TMagicType mtype,bool Recusion,int anitime,bool &bofly);
	TActor* FindActor(int id);
	TActor* FindNPC(std::string sName); //查找npc，根据名字查找
	void DelActor(TActor* actor);

	bool IsChangingFace(int recogid);

	bool CanWalk(int mx,int my);
	bool CanWalkEx(int mx,int my);
	bool CanRun(int sx,int sy,int ex,int ey);
	bool CrashManEx(int mx,int my);
	bool CrashMan(int mx,int my);
	void ActorDied(TActor* Actor);

	void DrawFontEx(std::string str,int nx,int ny,unsigned long color = 0xFFFFFFFF,
		bool HaveStroke = false,int StrokeColor = 0xFF000000);
	cocos2d::Label* DrawFontEx(cocos2d::Layer* layer,std::string str,int nx,int ny,
		unsigned long Color = 0xFFFFFFFF,bool HaveStroke = false,unsigned long StrokeColor = 0xFF000000,
		bool underline = false,bool HaveBackGround= false, unsigned long BackGroundColor = 0xFF000000);
	int FindTargetXYCount(int nX,int nY,int nRange);
	TActor* FindActorXY(int nX,int nY);
	void ScreenXYfromMCXY(int cx,int cy,int &sx,int &sy);//地图坐标转换为鼠标坐标
	bool IsValidActor(TActor* actor);//检验对象是否有效
	void CleanObjects();
	
private:
	void ClearMapImage(); //清除多余地图精灵
	void ClearHumImage(); //清除多余NPC、英雄精灵
	void ClearMonsterImage();//清除多余怪物精灵
	void ClearMemoryObject();
	void ClearUIImage(); //清除多余UI精灵
	void DrawImgMsg();
	//cocos2d::Color4B HexColorToColor4B(unsigned long color); //十六进制转换rgba颜色值
	std::vector<cocos2d::Label*> m_LabelList; //标签
private:
	

	int m_dwMoveTime;
	int m_dwAniTime;
	int m_nMoveStepCount;
	int m_nAniCount;

	int m_dwFrameTime;
	int m_dwFrameCount;
	int m_dwDrawFrameCount;

	//显示中间的图片文字..什么完成任务啊什么的- 2015.8.8
	int m_ShowImgMsgIdx;
	unsigned long m_ShowImgMsgTick;
	int m_ShowImgMsgTop;
public:
	std::vector<TActor*> m_ActorList;
	std::vector<TMagicEff*>m_EffectList;

public:
	//UI操作
	void Show_Dialog(DIALOG_TYPE type); //显示面板
	void Hide_Dialog(DIALOG_TYPE type); //隐藏面板

	

};

#endif