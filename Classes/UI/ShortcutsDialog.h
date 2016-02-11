#ifndef SHORTCUTSDIALOG_H_
#define SHORTCUTSDIALOG_H_
#include "cocos2d.h"
#include "BaseDialog.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
// Ö÷¿Ø¶Ô»°¿ò 2015.6.30 - 
namespace VD_UI
{
	class CShortcutsDialog : public CBaseDialog
	{
	public:
		static CShortcutsDialog* GetInstance();
		CShortcutsDialog(void);
		~CShortcutsDialog(void);
		//void Show(cocos2d::Layer* rootNode);
		void Show(cocos2d::Layer* layer);
		void Hide();
		void Render();
	private:
		cocos2d::Layer* m_Layer;
		void btn_Role_click(Ref* pSender,Widget::TouchEventType type);
		void btn_Bag_Click(Ref* pSender,Widget::TouchEventType type);
		void btn_Magic_Click(Ref* pSender,Widget::TouchEventType type);
		void btn_Team_Click(Ref* pSender,Widget::TouchEventType type);
	};

#endif


}
