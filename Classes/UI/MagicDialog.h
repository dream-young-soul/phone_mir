#ifndef MAGICDIALOG_H_
#define MAGICDIALOG_H_
#include "BaseDialog.h"
#include <vector>
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
//技能面板
//2015.7.19
namespace VD_UI
{
	class CMagicDialog : public CBaseDialog
	{
	public:
		CMagicDialog(void);
		~CMagicDialog(void);
		void Show(cocos2d::Layer* layer /* = nullptr */);
		void Hide();
		void Render();
		void MouseDown(cocos2d::Vec2 pos);
	private:
		cocos2d::Layer* m_Layer;
		std::vector<cocos2d::Label*> m_MagicName;
		std::vector<cocos2d::Label*> m_Level;
		cocos2d::ui::Button* m_BtnClose;//关闭按钮
		void btn_Close_click(Ref* pSender,ui::Widget::TouchEventType type);
	};
}


#endif