#ifndef BASEDIALOG_H_
#define BASEDIALOG_H_
#include "cocos2d.h"
#include "GameStruct.h"
//对话框基类
namespace VD_UI
{
	class CBaseDialog
	{
	public:
		CBaseDialog(void);
		~CBaseDialog(void);
		virtual void Show(cocos2d::Layer* layer = nullptr);
		virtual void Hide();
		virtual void SetRect(TRect_ size);
		virtual void SetRect(int x,int y,int width,int height);
		virtual void Render(){};	
		cocos2d::Rect GetRect();
		virtual void MouseDown(cocos2d::Vec2 pos){};
		bool IsVisible(){return m_bVisible;}
	protected:
		TRect_ m_Size;
		bool m_bVisible;
		

	};
}


#endif