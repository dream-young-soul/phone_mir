//地图事件- 
//2015.5.18
#ifndef CLEVENT_H_
#define CLEVENT_H_
#include "cocos2d.h"
class TVDImage;
class TEvent
{
public:
	void Create(int svid,int ax,int ay,int evtype,int RunTime);
	TEvent();
	~TEvent();
	virtual bool DrawEvent(cocos2d::Layer* layer,int ax,int ay);
	virtual void Run();
	int m_nX;
	int m_nY;
	int m_nDir;
	int m_nPx;
	int m_nPy;
	int m_nEventType;
	int m_nEventParam;
	int m_nServerId;
	TVDImage* m_Dsurface;
	bool m_boBlend;
	unsigned long m_dwFrameTime;
	unsigned short m_dwCurframe;
	int m_nLight;
	unsigned long m_nRunTime;
	unsigned char m_btColor;
};


class TClEvent : public TEvent
{
public:
	TClEvent(int svid,int ax,int ay,int evtype);
	~TClEvent();
	virtual void Run();
};

//没用的啊-
class TFlowerEvent : public TEvent
{
public:
	TFlowerEvent(int svid,int ax,int ay,int evtype);
	~TFlowerEvent();
	virtual void Run();
	int m_nExplosionSound;
};

class TClEventManager 
{
public:
	static TClEventManager* GetInstance();
	TClEventManager();
	~TClEventManager();
	std::vector<TEvent*> EventList;
	void ClearEvents();
	TEvent* AddEvent(TEvent* evn);
	void DelEvent(TEvent* evn);
	void DelEventById(int svid);
	TEvent* GetEvent(int ax,int ay,int etype);
	void Execute();

};
#endif