
#ifndef _UIMANAGER_H_
#define _UIMANAGER_H_
#include "cocos2d.h"
namespace VD_UI
{
	class CUIManager
	{
	public:
		CUIManager(void);
		~CUIManager(void);
		static CUIManager* GetInstance();
		void Draw(cocos2d::Layer* layer);
	};

}


#endif