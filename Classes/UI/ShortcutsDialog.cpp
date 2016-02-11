#include "ShortcutsDialog.h"
#include "VD_Share.h"
#include "cocostudio/CocoStudio.h"
#include "../FrmMain.h"
#include "../GuaJiHelper.h"
#include "../MShare.h"
namespace VD_UI
{
	static CShortcutsDialog* m_Instance = nullptr;
	CShortcutsDialog::CShortcutsDialog(void)
	{
		m_Layer = nullptr;
	}


	CShortcutsDialog::~CShortcutsDialog(void)
	{
	}

	CShortcutsDialog* CShortcutsDialog::GetInstance()
	{
		if(!m_Instance)
		{
			m_Instance = new CShortcutsDialog;
		}
		return m_Instance;
	}

	void CShortcutsDialog::Show(cocos2d::Layer* layer)
	{
		CBaseDialog::Show(layer);
		m_Layer = cocos2d::Layer::create();
		layer->addChild(m_Layer);
		cocos2d::Node* node =  CSLoader::createNode("project_ui/child_shortcuts.csb");
		node->retain();
		m_Layer->addChild(node,DIALOG_TYPE::SHORTCUTS);

		ui::Button* btn_role  = dynamic_cast<ui::Button*>(node->getChildByName("btn_role"));
		btn_role->addTouchEventListener(CC_CALLBACK_2(CShortcutsDialog::btn_Role_click, this));

		ui::Button* btn_bag = dynamic_cast<ui::Button*>(node->getChildByName("btn_bag"));
		btn_bag->addTouchEventListener(CC_CALLBACK_2(CShortcutsDialog::btn_Bag_Click, this));
		ui::Button* btn_magic = dynamic_cast<ui::Button*>(node->getChildByName("btn_skill"));
		btn_magic->addTouchEventListener(CC_CALLBACK_2(CShortcutsDialog::btn_Magic_Click, this));
		//组队 btn_team
		ui::Button* btn_team = dynamic_cast<ui::Button*>(node->getChildByName("btn_team"));
		btn_team->addTouchEventListener(CC_CALLBACK_2(CShortcutsDialog::btn_Team_Click, this));
		//行会 btn_guild
		//坐骑 btn_horse
		//好友 btn_friend
		//强化 btn_strong
	}

	void CShortcutsDialog::btn_Team_Click(Ref* pSender,Widget::TouchEventType type)
	{

	}
	void CShortcutsDialog::btn_Magic_Click(Ref* pSender,Widget::TouchEventType type)
	{
		if(type == Widget::TouchEventType::ENDED)
		{
			if(FrmMain::GetInstance()->IsDialogVisible(DIALOG_TYPE::MAGIC))
			{
				FrmMain::GetInstance()->HideDialog(DIALOG_TYPE::MAGIC);
			}else
			{
				FrmMain::GetInstance()->ShowDialog(DIALOG_TYPE::MAGIC);
			}
		}
	}
	void CShortcutsDialog::btn_Bag_Click(Ref* pSender,Widget::TouchEventType type)
	{
		if(type == Widget::TouchEventType::ENDED)
		{
			if(FrmMain::GetInstance()->IsDialogVisible(DIALOG_TYPE::BAGITEM))
			{
				FrmMain::GetInstance()->HideDialog(DIALOG_TYPE::BAGITEM);
			}else
			{
				FrmMain::GetInstance()->ShowDialog(DIALOG_TYPE::BAGITEM);
			}
		}
	}
	void CShortcutsDialog::btn_Role_click(Ref* pSender,Widget::TouchEventType type)
	{
		if(type == Widget::TouchEventType::ENDED)
		{
			if(FrmMain::GetInstance()->IsDialogVisible(DIALOG_TYPE::ROLESTATE))
			{
				FrmMain::GetInstance()->HideDialog(DIALOG_TYPE::ROLESTATE);
			}else
			{
				FrmMain::GetInstance()->ShowDialog(DIALOG_TYPE::ROLESTATE);
			}
			
		}
	}
	void CShortcutsDialog::Hide()
	{
		CBaseDialog::Hide();
	}
	void CShortcutsDialog::Render()
	{

	}
}
