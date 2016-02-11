#include "UIManager.h"

namespace VD_UI
{
	static CUIManager* m_Instance = nullptr;
	CUIManager::CUIManager(void)
	{
	}


	CUIManager::~CUIManager(void)
	{
	}

	CUIManager* CUIManager::GetInstance()
	{
		if(!m_Instance)
		{
			m_Instance =new CUIManager();
		}
		return m_Instance;
	}

	void CUIManager::Draw(cocos2d::Layer* layer)
	{

	}
}
