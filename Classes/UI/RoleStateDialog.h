#ifndef ROLESTATEDIALOG_H_
#define ROLESTATEDIALOG_H_
#include "BaseDialog.h"
#include "cocos2d.h"
#include "cocostudio/CocoStudio.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
using namespace cocos2d::ui;
//角色状态对话框
namespace VD_UI
{
	

	class CRoleStateDialog : public CBaseDialog
	{
	public:
		CRoleStateDialog(void);
		~CRoleStateDialog(void);
		void Show(cocos2d::Layer* layer /* = nullptr */);
		void Hide();
		void Render();
	private:
		cocos2d::Layer* m_Layer;
		cocos2d::Label* m_LabelUserName;

		////职业
		cocos2d::Label* m_LabelJobTips;
		cocos2d::Label* m_LabelJob;
		//性别
		cocos2d::Label* m_LabelSexTips;
		cocos2d::Label* m_LabelSex;
		//等级
		cocos2d::Label* m_LabelLvTips;
		cocos2d::Label* m_LabelLv;
		//生命
		cocos2d::Label* m_LabelLifeTips;
		cocos2d::Label* m_LabelLife;
		//魔法
		cocos2d::Label* m_LabelMageTips;
		cocos2d::Label* m_LabelMage;
		//物理防御
		cocos2d::Label* m_LabelAcTips;
		cocos2d::Label* m_LabelAc;
		//魔法防御
		cocos2d::Label* m_LabelMacTips;
		cocos2d::Label* m_LabelMac;
		//物理攻击
		cocos2d::Label* m_LabelDcTips;
		cocos2d::Label* m_LabelDc;
		//魔法攻击
		cocos2d::Label* m_LabelMcTips;
		cocos2d::Label* m_LabelMc;
		//道术攻击
		cocos2d::Label* m_LabelScTips;
		cocos2d::Label* m_LabelSc;
		//准确
		cocos2d::Label* m_LabelHitTips;
		cocos2d::Label* m_LabelHit;
		//敏捷
		cocos2d::Label* m_LabelSpeedTips;
		cocos2d::Label* m_LabelSpeed;
		//PK值
		cocos2d::Label* m_LabelPKTips;
		cocos2d::Label* m_LabelPK;
		//暴击
		cocos2d::Label* m_LabelProtectTips;
		cocos2d::Label* m_LabelProtect;
		//守护
		cocos2d::Label* m_LabelCritTips;
		cocos2d::Label* m_LabelCrit;
		//关闭按钮
		ui::Button* m_BtnClose;

		void btn_Close_click(Ref* pSender,ui::Widget::TouchEventType type);
		
	};
}


#endif