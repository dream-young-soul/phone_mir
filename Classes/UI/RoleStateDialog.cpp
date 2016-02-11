#include "RoleStateDialog.h"
#include "VDImage.h"
#include "MShare.h"
#include "../PlayScene.h"
#include "../Common/IconvString.h"
#include "../Net/NetClient.h"
#include "../Net/NetSendMsg.h"
namespace VD_UI
{
	CRoleStateDialog::CRoleStateDialog(void)
	{
		m_Layer = nullptr;
	}


	CRoleStateDialog::~CRoleStateDialog(void)
	{
	}

	void CRoleStateDialog::Show(cocos2d::Layer* layer )
	{
		if(IsVisible())return;
		CBaseDialog::Show(layer);
		m_Layer = cocos2d::Layer::create();
		m_Layer->retain();
		layer->addChild(m_Layer);

		m_LabelUserName = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,g_MySelf->m_nNameColor,true);
		m_LabelUserName->retain();

		m_LabelJobTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xffdc90ff,true);
		m_LabelJobTips->retain();
		m_LabelJob = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xf2ebaeff,true);
		m_LabelJob->retain();
		//性别
		m_LabelSexTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xffdc90ff,true);
		m_LabelSexTips->retain();
		m_LabelSex = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xf2ebaeff,true);
		m_LabelSex->retain();
		//等级
		m_LabelLvTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xffdc90ff,true);
		m_LabelLvTips->retain();
		m_LabelLv = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xf2ebaeff,true);
		m_LabelLv->retain();
		//生命
		m_LabelLifeTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xffdc90ff,true);
		m_LabelLifeTips->retain();
		m_LabelLife = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xf2ebaeff,true);
		m_LabelLife->retain();
		//魔法
		m_LabelMageTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xffdc90ff,true);
		m_LabelMageTips->retain();
		m_LabelMage = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xf2ebaeff,true);
		m_LabelMage->retain();
		//物理防御
		m_LabelAcTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xcdff6dFF,true);
		m_LabelAcTips->retain();
		m_LabelAc = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xFFFFFFFF,true);
		m_LabelAc->retain();
		//魔法防御
		m_LabelMacTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xcdff6dFF,true);
		m_LabelMacTips->retain();
		m_LabelMac = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xFFFFFFFF,true);
		m_LabelMac->retain();
		//物理攻击
		m_LabelDcTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xcdff6dFF,true);
		m_LabelDcTips->retain();
		m_LabelDc = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xFFFFFFFF,true);
		m_LabelDc->retain();
		//魔法攻击
		m_LabelMcTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xcdff6dFF,true);
		m_LabelMcTips->retain();
		m_LabelMc = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xFFFFFFFF,true);
		m_LabelMc->retain();
		//道术攻击
		m_LabelScTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xcdff6dFF,true);
		m_LabelScTips->retain();
		m_LabelSc = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xFFFFFFFF,true);
		m_LabelSc->retain();
		//准确
		m_LabelHitTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0x6cf8f0FF,true);
		m_LabelHitTips->retain();
		m_LabelHit = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xFFFFFFFF,true);
		m_LabelHit->retain();
		//敏捷
		m_LabelSpeedTips =TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0x6cf8f0FF,true);
		m_LabelSpeedTips->retain();
		m_LabelSpeed = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xFFFFFFFF,true);
		m_LabelSpeed->retain();
		//PK值
		m_LabelPKTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0x6cf8f0FF,true);
		m_LabelPKTips->retain();
		m_LabelPK = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xFFFFFFFF,true);
		m_LabelPK->retain();
		//暴击
		m_LabelProtectTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0x6cf8f0FF,true);
		m_LabelProtectTips->retain();
		m_LabelProtect = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xFFFFFFFF,true);
		m_LabelProtect->retain();

		m_LabelCritTips = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0x6cf8f0FF,true);
		m_LabelCritTips->retain();
		m_LabelCrit = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xFFFFFFFF,true);
		m_LabelCrit->retain();

		//关闭按钮
		m_BtnClose = ui::Button::create(CLOSE_NORMAL,CLOSE_CLICK);
		cocos2d::Vec2 pos;
		pos = Vec2(m_Size.Left + 385,m_Size.Top + 6);
		pos = Director::getInstance()->convertToGL(pos);
		m_BtnClose->setAnchorPoint(cocos2d::Vec2(0,0));
		pos.y = pos.y - m_BtnClose->getContentSize().width;
		m_BtnClose->setPosition(pos);
		m_BtnClose->retain();
		m_BtnClose->addTouchEventListener(CC_CALLBACK_2(CRoleStateDialog::btn_Close_click, this));
		//获取图标信息
		VD_Net::CNetClient::GetInstance()->GetSendMsg()->SendGetIcons();
	}
	void CRoleStateDialog::btn_Close_click(Ref* pSender,ui::Widget::TouchEventType type)
	{
		if(type == ui::Widget::TouchEventType::ENDED)
		{
			Hide();
			g_UIClick = true;
		}
	}
	void CRoleStateDialog::Hide()
	{
		if(!m_Layer)return;
		m_Layer->removeAllChildrenWithCleanup(true);
		m_Layer->release();
		m_LabelUserName->release();
		m_LabelJob->release();
		m_LabelJobTips->release();
		m_LabelSexTips->release();
		m_LabelSex->release();
		m_LabelLvTips->release();
		m_LabelLv->release();
		m_LabelLifeTips->release();
		m_LabelLife->release();
		m_LabelMageTips->release();
		m_LabelMage->release();
		m_LabelAcTips->release();
		m_LabelAc->release();
		m_LabelMacTips->release();
		m_LabelMac->release();
		m_LabelDcTips->release();
		m_LabelDc->release();
		m_LabelMcTips->release();
		m_LabelMc->release();
		m_LabelScTips->release();
		m_LabelSc->release();

		m_LabelHitTips->release();
		m_LabelHit->release();
		m_LabelSpeedTips->release();
		m_LabelSpeed->release();
		m_LabelPKTips->release();
		m_LabelPK->release();
		m_LabelProtectTips->release();
		m_LabelProtect->release();
		m_LabelCritTips->release();
		m_LabelCrit->release();
		m_BtnClose->release();
		m_Layer = nullptr;
		CBaseDialog::Hide();
	}

	void CRoleStateDialog::Render()
	{
		m_Layer->removeAllChildrenWithCleanup(true);
		
		TVDImage* img;
		img = GetUIImage(500);
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(m_Size.Left,m_Size.Top));
		}
		img = GetUIImage(501);
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(m_Size.Left + 6,m_Size.Top + 62));
		}
		img = nullptr;
		// //画人物形象--
		cocos2d::Sprite* sprite;
		BlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
		int nx,ny;
		nx = m_Size.Left + 73;
		ny = m_Size.Top + 170;

		//翅膀 2103.10.28 Loser.DieYoung
		if((int)strlen(g_UseItems[U_WINGS].s.Name) > 0)
		{
			img  = GetWringsImage(g_UseItems[U_WINGS].s.CharLooks);
			if(img && img->Image_)
			{
				m_Layer->addChild(img->GetImage(nx + img->nx,ny + img->ny));
			}
		}
		//衣服
		if((int)strlen(g_UseItems[U_FASHIONDRESS].s.Name) > 0 && Shared.boShowLocalFashion == true)
		{
			img = GetInsideImage(g_UseItems[U_FASHIONDRESS].s.Looks);
		}else
		{
			if((int)strlen(g_UseItems[U_DRESS].s.Name) > 0)
			{
				img = GetInsideImage(g_UseItems[U_DRESS].s.Looks);
			}
		}
		if(!img)
		{
			if(g_MySelf->m_btSex == 0)
			{
				img = GetUIImage(203);
			}else img = GetUIImage(204);
		}
		int stlevel;
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(nx + img->nx,ny + img->ny));
			if((int)strlen(g_UseItems[U_DRESS].s.Name) > 0)
			{
				//强十发光
				stlevel = g_UseItems[U_DRESS].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5520 + GetTickCount() / 100 % 10));
					if(img)
					{
						sprite = img->GetImage(m_Size.Left + 110 + img->nx,
							m_Size.Top + 212 + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}
		//武器
		//变身内观-- 不显示武器
		if((int)strlen(g_UseItems[U_FASHIONDRESS].s.Name) == 0 ||
			((int)strlen(g_UseItems[U_FASHIONDRESS].s.Name) > 0 && 
			g_UseItems[U_FASHIONDRESS].s.CharLooks <= 0))
		{
			if((int)strlen(g_UseItems[U_WEAPON].s.Name)> 0)
			{
				img = GetInsideImage(g_UseItems[U_WEAPON].s.Looks);
			}
		}
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(nx + img->nx,ny + img->ny));
		}

		//头盔
		if((int)strlen(g_UseItems[U_FASHIONDRESS].s.Name) == 0 ||
			((int)strlen(g_UseItems[U_FASHIONDRESS].s.Name) > 0 && 
			g_UseItems[U_FASHIONDRESS].s.CharLooks <= 0))
		{
			if((int)strlen(g_UseItems[U_HELMET].s.Name) > 0)
			{
				img = GetInsideImage(g_UseItems[U_HELMET].s.Looks);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + img->nx,ny + img->ny));
				}
			}
			
		}
		int idx;
		static const int GRIDWIDTH = 32;
		static const int GRIDHEIGHT = 32;
		//格子里的装备
		if((int)strlen(g_UseItems[U_NECKLACE].s.Name) > 0)
		{
			idx = g_UseItems[U_NECKLACE].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left + 211;
				ny = m_Size.Top + 72 + 73;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				 //强十发光
				stlevel = g_UseItems[U_NECKLACE].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_NECKLACE].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_NECKLACE].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
						
					}
				}
			}
		}

		//格子里的装备
		if((int)strlen(g_UseItems[U_RIGHTHAND].s.Name) > 0)
		{
			idx = g_UseItems[U_RIGHTHAND].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left + 211;
				ny = m_Size.Top + 72 +120;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_RIGHTHAND].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_RIGHTHAND].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_RIGHTHAND].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}

		//格子里的装备
		if((int)strlen(g_UseItems[U_ARMRINGR].s.Name) > 0)
		{
			idx = g_UseItems[U_ARMRINGR].s.Looks;
			if(idx >= 0)
			{
				nx =m_Size.Left  + 19;
				ny =m_Size.Top + 72 + 166;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_ARMRINGR].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_ARMRINGR].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_ARMRINGR].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}

		//格子里的装备
		if((int)strlen(g_UseItems[U_ARMRINGL].s.Name) > 0)
		{
			idx = g_UseItems[U_ARMRINGL].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left + 211;
				ny = m_Size.Top + 72 +166;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_ARMRINGL].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_ARMRINGL].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_ARMRINGL].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}

		//格子里的装备
		if((int)strlen(g_UseItems[U_RINGR].s.Name) > 0)
		{
			idx = g_UseItems[U_RINGR].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left +19;
				ny = m_Size.Top + 72 + 213;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_RINGR].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_RINGR].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_RINGR].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}
		//格子里的装备
		if((int)strlen(g_UseItems[U_RINGL].s.Name) > 0)
		{
			idx = g_UseItems[U_RINGL].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left  + 211;
				ny = m_Size.Top + 72 + 213;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_RINGL].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_RINGL].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_RINGL].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}
		//格子里的装备
		if((int)strlen(g_UseItems[U_BUJUK].s.Name) > 0)
		{
			idx = g_UseItems[U_BUJUK].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left +211;
				ny =m_Size.Top + 72 + 258;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_BUJUK].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_BUJUK].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_BUJUK].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}

		//格子里的装备
		if((int)strlen(g_UseItems[U_BELT].s.Name) > 0)
		{
			idx = g_UseItems[U_BELT].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left  + 116;
				ny = m_Size.Top + 72 + 258;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_BUJUK].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_BELT].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_BELT].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}

		//格子里的装备
		if((int)strlen(g_UseItems[U_BOOTS].s.Name) > 0)
		{
			idx = g_UseItems[U_BOOTS].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left  +163;
				ny = m_Size.Top + 72 + 258;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_BOOTS].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_BOOTS].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_BOOTS].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}
		//格子里的装备
		if((int)strlen(g_UseItems[U_CHARM].s.Name) > 0)
		{
			idx = g_UseItems[U_CHARM].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left + 19;
				ny = m_Size.Top + 72 + 258;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_CHARM].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_CHARM].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_CHARM].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}


		//格子里的装备
		if((int)strlen(g_UseItems[U_WINGS].s.Name) > 0)
		{
			idx = g_UseItems[U_WINGS].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left  + 68;
				ny = m_Size.Top + 72 + 258;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_WINGS].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_WINGS].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_WINGS].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}
		//格子里的装备
		if((int)strlen(g_UseItems[U_FASHIONDRESS].s.Name) > 0)
		{
			idx = g_UseItems[U_FASHIONDRESS].s.Looks;
			if(idx >= 0)
			{
				nx = m_Size.Left  + 20;
				ny = m_Size.Top + 72 + 116;
				img = GetBagImage(idx);
				if(img && img->Image_)
				{
					m_Layer->addChild(img->GetImage(nx + (GRIDWIDTH - img->pWidth) / 2,
						ny + (GRIDHEIGHT - img->pHeight) / 2));
				}
				//强十发光
				stlevel = g_UseItems[U_WINGS].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(((int)5500 + GetTickCount() / 100 % 10));
				}else if(stlevel == 9)
				{
					img = GetUIImage(((int)5540 + GetTickCount() / 100 % 10));
				}else if(stlevel == 8)
				{
					img = GetUIImage(((int)5550 + GetTickCount() / 100 % 10));
				}
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,ny + img->ny);
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//物品特效 2013.11.25 Loser.DieYoung
				if(g_UseItems[U_FASHIONDRESS].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_UseItems[U_FASHIONDRESS].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,ny + img->ny);
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
			}
		}


		//人物名称
		cocos2d::Vec2 pos;
		std::string gbk_str,utf8_str;
		char szChar[512]={0};
		gbk_str = UTF8ToGBK_string(g_MySelf->m_sUserName.c_str(),g_MySelf->m_sUserName.length());
		pos.x = m_Size.Left + 125 - TextWidth(gbk_str) /2;
		pos.y = m_Size.Top + 100;
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y -  DEFAULT_FONTSIZE;
		m_LabelUserName->setPosition(pos);
		m_LabelUserName->setString(gbk_str);
		m_Layer->addChild(m_LabelUserName);

		nx = m_Size.Left + 270;
		ny = m_Size.Top + 85;
		//属性文字
		gbk_str = "职    业:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelJobTips->setPosition(pos);
		m_LabelJobTips->setString(utf8_str);
		m_Layer->addChild(m_LabelJobTips);

		pos.x = nx + 60;pos.y = ny;
		gbk_str = IntToJob(g_MySelf->m_btJob);
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelJob->setPosition(pos);
		m_LabelJob->setString(utf8_str);
		m_Layer->addChild(m_LabelJob);
		ny += 23;
		gbk_str = "性    别:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelSexTips->setPosition(pos);
		m_LabelSexTips->setString(utf8_str);
		m_Layer->addChild(m_LabelSexTips);

		pos.x = nx + 60;pos.y = ny;
		gbk_str = IntToSex(g_MySelf->m_btSex);
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelSex->setPosition(pos);
		m_LabelSex->setString(utf8_str);
		m_Layer->addChild(m_LabelSex);
		ny += 23;
		gbk_str = "等    级:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelLvTips->setPosition(pos);
		m_LabelLvTips->setString(utf8_str);
		m_Layer->addChild(m_LabelLvTips);

		pos.x = nx + 60;pos.y = ny;
		gbk_str = IntToStr(g_MySelf->m_Abil.Level);
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelLv->setPosition(pos);
		m_LabelLv->setString(utf8_str);
		m_Layer->addChild(m_LabelLv);

		ny += 23;
		gbk_str = "生    命:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelLifeTips->setPosition(pos);
		m_LabelLifeTips->setString(utf8_str);
		m_Layer->addChild(m_LabelLifeTips);

		pos.x = nx + 60;pos.y = ny;
		sprintf(szChar,"%d/%d",g_MySelf->m_Abil.HP,g_MySelf->m_Abil.MaxHP);
		gbk_str = szChar;
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelLife->setPosition(pos);
		m_LabelLife->setString(utf8_str);
		m_Layer->addChild(m_LabelLife);

		ny += 23;
		gbk_str = "魔    法:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelMageTips->setPosition(pos);
		m_LabelMageTips->setString(utf8_str);
		m_Layer->addChild(m_LabelMageTips);

		pos.x = nx + 60;pos.y = ny;
		sprintf(szChar,"%d/%d",g_MySelf->m_Abil.MP,g_MySelf->m_Abil.MaxMP);
		gbk_str = szChar;
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelMage->setPosition(pos);
		m_LabelMage->setString(utf8_str);
		m_Layer->addChild(m_LabelMage);

		ny += 30;
		gbk_str = "物理防御:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelAcTips->setPosition(pos);
		m_LabelAcTips->setString(utf8_str);
		m_Layer->addChild(m_LabelAcTips);

		pos.x = nx + 60;pos.y = ny;
		sprintf(szChar,"%d/%d",g_MySelf->m_Abil.AC,g_MySelf->m_Abil.AC2);
		gbk_str = szChar;
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelAc->setPosition(pos);
		m_LabelAc->setString(utf8_str);
		m_Layer->addChild(m_LabelAc);

		ny += 23;
		gbk_str = "魔法防御:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelMacTips->setPosition(pos);
		m_LabelMacTips->setString(utf8_str);
		m_Layer->addChild(m_LabelMacTips);

		pos.x = nx + 60;pos.y = ny;
		sprintf(szChar,"%d/%d",g_MySelf->m_Abil.MAC,g_MySelf->m_Abil.MAC2);
		gbk_str = szChar;
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelMac->setPosition(pos);
		m_LabelMac->setString(utf8_str);
		m_Layer->addChild(m_LabelMac);

		ny += 23;
		gbk_str = "物理攻击:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelDcTips->setPosition(pos);
		m_LabelDcTips->setString(utf8_str);
		m_Layer->addChild(m_LabelDcTips);

		pos.x = nx + 60;pos.y = ny;
		sprintf(szChar,"%d/%d",g_MySelf->m_Abil.DC,g_MySelf->m_Abil.DC2);
		gbk_str = szChar;
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelDc->setPosition(pos);
		m_LabelDc->setString(utf8_str);
		m_Layer->addChild(m_LabelDc);


		ny += 23;
		gbk_str = "魔法攻击:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelMcTips->setPosition(pos);
		m_LabelMcTips->setString(utf8_str);
		m_Layer->addChild(m_LabelMcTips);

		pos.x = nx + 60;pos.y = ny;
		sprintf(szChar,"%d/%d",g_MySelf->m_Abil.MC,g_MySelf->m_Abil.MC2);
		gbk_str = szChar;
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelMc->setPosition(pos);
		m_LabelMc->setString(utf8_str);
		m_Layer->addChild(m_LabelMc);

		ny += 23;
		gbk_str = "道术攻击:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelScTips->setPosition(pos);
		m_LabelScTips->setString(utf8_str);
		m_Layer->addChild(m_LabelScTips);

		pos.x = nx + 60;pos.y = ny;
		sprintf(szChar,"%d/%d",g_MySelf->m_Abil.SC,g_MySelf->m_Abil.SC2);
		gbk_str = szChar;
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelSc->setPosition(pos);
		m_LabelSc->setString(utf8_str);
		m_Layer->addChild(m_LabelSc);

		ny += 25;
		gbk_str = "准确:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelHitTips->setPosition(pos);
		m_LabelHitTips->setString(utf8_str);
		m_Layer->addChild(m_LabelHitTips);

		pos.x = nx + 36;pos.y = ny;
		gbk_str = IntToStr(g_nMyHitPoint);
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelHit->setPosition(pos);
		m_LabelHit->setString(utf8_str);
		m_Layer->addChild(m_LabelHit);

		ny += 18;
		gbk_str = "敏捷:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelSpeedTips->setPosition(pos);
		m_LabelSpeedTips->setString(utf8_str);
		m_Layer->addChild(m_LabelSpeedTips);

		pos.x = nx + 36;pos.y = ny;
		gbk_str = IntToStr(g_nMySpeedPoint);
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelSpeed->setPosition(pos);
		m_LabelSpeed->setString(utf8_str);
		m_Layer->addChild(m_LabelSpeed);

		ny += 18;
		gbk_str = "PK值:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelPKTips->setPosition(pos);
		m_LabelPKTips->setString(utf8_str);
		m_Layer->addChild(m_LabelPKTips);

		pos.x = nx + 36;pos.y = ny;
		gbk_str = IntToStr(g_nPKPoint);
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelPK->setPosition(pos);
		m_LabelPK->setString(utf8_str);
		m_Layer->addChild(m_LabelPK);

		ny += 18;
		gbk_str = "暴击:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelCritTips->setPosition(pos);
		m_LabelCritTips->setString(utf8_str);
		m_Layer->addChild(m_LabelCritTips);

		pos.x = nx + 36;pos.y = ny;
		gbk_str = IntToStr(g_nCrit);
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelCrit->setPosition(pos);
		m_LabelCrit->setString(utf8_str);
		m_Layer->addChild(m_LabelCrit);

		ny += 18;
		gbk_str = "守护:";
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelProtectTips->setPosition(pos);
		m_LabelProtectTips->setString(utf8_str);
		m_Layer->addChild(m_LabelProtectTips);

		pos.x = nx + 36;pos.y = ny;
		gbk_str = IntToStr(g_nProtect);
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		pos = Director::getInstance()->convertToGL(pos);
		m_LabelProtect->setPosition(pos);
		m_LabelProtect->setString(utf8_str);
		m_Layer->addChild(m_LabelProtect);

		//人物图标
		nx = m_Size.Left + 17;
		for(int i = 0;i < sizeof(g_Icons) / sizeof(TIconInfo);i++)
		{
			if(g_Icons[i].imgIndex > 0)
			{
				img = GetBagImage(g_Icons[i].imgIndex);
				if(img && img->Image_)
				{
					ny = m_Size.Top + 380 + ((16 - img->pHeight) / 2);
					m_Layer->addChild(img->GetImage(nx,ny));
				}
				nx += 26;
			}
		}

		//关闭按钮
		m_Layer->addChild(m_BtnClose);
	}

	

}

