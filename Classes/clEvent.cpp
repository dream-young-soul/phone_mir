#include "clEvent.h"
#include "VDImage.h"
#include "MShare.h"
TEvent::TEvent()
{
	m_nX = 0;
	m_nY = 0;
	m_nDir = 0;
	m_nPx = 0;
	m_nPy = 0;

	m_nEventType = 0;
	m_nEventParam = 0;
	m_nServerId = 0;
	m_Dsurface = nullptr;

	m_boBlend = false;
	m_dwFrameTime = 0;
	m_dwCurframe = 0;
	m_nLight = 0;
	m_nRunTime = 0;
	m_btColor = 0;
}
void TEvent::Create(int svid,int ax,int ay,int evtype,int RunTime)
{
	m_nServerId = svid;
	m_nX = ax;
	m_nY = ay;
	m_nEventType = evtype;
	m_nEventParam = 0;
	m_boBlend  = false;
	m_dwFrameTime = GetTickCount();
	m_dwCurframe = 0;
	m_nLight = 0;
	m_nRunTime = RunTime;
}

TEvent::~TEvent()
{
	
}

bool TEvent::DrawEvent(cocos2d::Layer* layer,int ax,int ay)
{
	//透明处理 啊-
	if(m_Dsurface && m_Dsurface->Image_)
	{
	
		layer->addChild(m_Dsurface->GetImage(ax + m_nPx,ay + m_nPy));
	}

	return true;
}

void TEvent::Run()
{
	if(GetTickCount() - m_dwFrameTime > m_nRunTime)
	{
		m_dwFrameTime = GetTickCount();
		m_dwCurframe ++ ;
	}
}

TClEvent::TClEvent(int svid,int ax,int ay,int evtype)
{
	TEvent::Create(svid, ax, ay, evtype, 50);
}

TClEvent::~TClEvent()
{

}

void TClEvent::Run()
{
	switch(m_nEventType)
	{
	case ET_HOLYCURTAIN://安全区
		{
			m_Dsurface = GetEffectImage(/*HOLYCURTAINBASE*/201, (m_dwCurframe % 10), m_nPx, m_nPy);
			m_nLight = 1;
			break;
		}
	case ET_FIRE: //火墙
		{
			m_Dsurface = GetEffectImage(/*FIREBURNBASE*/19, 10 + ((m_dwCurframe / 2) % 3), m_nPx, m_nPy);
			m_boBlend = true;
			m_nLight = 1;
			break;
		}
	}
	TEvent::Run();
}

TFlowerEvent::TFlowerEvent(int svid,int ax,int ay,int evtype)
{
	TEvent::Create(svid, ax, ay, evtype, 100);
	m_nExplosionSound = -1;
	m_dwCurframe = 0;
}

TFlowerEvent::~TFlowerEvent()
{
	

}

void TFlowerEvent::Run()
{
	TEvent::Run();
}

TClEventManager::TClEventManager()
{
	EventList.clear();
}

TClEventManager::~TClEventManager()
{

}

void TClEventManager::ClearEvents()
{

	TEvent* e;
	while(true)
	{
		if(EventList.size() <= 0) break;
		e = EventList[0];
		delete e;
		EventList.erase(EventList.begin());
	}
}

TEvent* TClEventManager::AddEvent(TEvent* evn)
{
	for(int i = 0;i < (int)EventList.size();i++)
	{
		TEvent* e = EventList[i];
		if(e == evn)
		{
			EventList.erase(EventList.begin() + i);
			delete e;
			break;
		}
	}
	EventList.push_back(evn);
	return evn;
}

void TClEventManager::DelEvent(TEvent* evn)
{
	for(int i = 0;i < (int)EventList.size();i++)
	{
		TEvent* e = EventList[i];
		if(e == evn)
		{
			EventList.erase(EventList.begin() + i);
			delete e;
			break;
		}
	}
}

void TClEventManager::DelEventById(int svid)
{
	for(int i = 0;i < (int)EventList.size();i++)
	{
		TEvent* e = EventList[i];
		if(e->m_nServerId == svid)
		{
			EventList.erase(EventList.begin() + i);
			delete e;
			break;
		}
	}
}

TEvent* TClEventManager::GetEvent(int ax,int ay,int etype)
{
	for(int i = 0;i < (int)EventList.size();i++)
	{
		TEvent* e = EventList[i];
		if(e->m_nX == ax && e->m_nY == ay && e->m_nEventType == etype)
		{
			return e;
		}
	}
	return nullptr;
}
void TClEventManager::Execute()
{
	for(int i = 0;i < (int)EventList.size();i++)
	{
		TEvent* e = EventList[i];
		e->Run();
	}
}

static TClEventManager* m_Instance = nullptr;
TClEventManager* TClEventManager::GetInstance()
{
	if(!m_Instance)
	{
		m_Instance = new TClEventManager();
	}
	return m_Instance;
}