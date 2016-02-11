#include "BagDialog.h"
#include "../MShare.h"
#include "../VDImage.h"
#include "../PlayScene.h"
#include "../FrmMain.h"
#include "HitDialog.h"
namespace VD_UI
{
	CBagDialog::CBagDialog(void)
	{
		m_Layer = nullptr;
	}


	CBagDialog::~CBagDialog(void)
	{
	}

	void CBagDialog::Show(cocos2d::Layer* layer )
	{
		m_Layer  = cocos2d::Layer::create();
		m_Layer->retain();
		layer->addChild(m_Layer);
		CBaseDialog::Show(layer);

		m_LabelGold = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1);
		m_LabelGold->retain();

		m_LabelBindGold = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1);
		m_LabelBindGold->retain();

		m_LabelGameGold = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1);
		m_LabelGameGold->retain();

		//关闭按钮
		m_BtnClose = ui::Button::create(CLOSE_NORMAL,CLOSE_CLICK);
		cocos2d::Vec2 pos;
		pos = Vec2(m_Size.Left + 311,m_Size.Top + 6);
		pos = Director::getInstance()->convertToGL(pos);
		m_BtnClose->setAnchorPoint(cocos2d::Vec2(0,0));
		pos.y = pos.y - m_BtnClose->getContentSize().width;
		m_BtnClose->setPosition(pos);
		m_BtnClose->retain();
		m_BtnClose->addTouchEventListener(CC_CALLBACK_2(CBagDialog::btn_Close_click, this));

	}
	void CBagDialog::btn_Close_click(Ref* pSender,ui::Widget::TouchEventType type)
	{
		if(type == ui::Widget::TouchEventType::ENDED)
		{
			Hide();
			g_UIClick = true;
		}
	}
	void CBagDialog::Hide()
	{
		if(!m_Layer)return;
		m_Layer->removeAllChildrenWithCleanup(true);
		m_Layer->release();
		m_Layer = nullptr;
		m_LabelGold->release();
		m_LabelGameGold->release();
		m_LabelBindGold->release();
		CBaseDialog::Hide();
	}

	void CBagDialog::Render()
	{
		m_Layer->removeAllChildrenWithCleanup(true);
		TVDImage* img = GetUIImage(510);
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(m_Size.Left,m_Size.Top));
		}

		//标签
		cocos2d::Vec2 pos;
		std::string gbk_str,utf8_str;
		
		gbk_str = IntToStr(g_MySelf->m_nGold);
		pos.x = m_Size.Left + 45 ;
		pos.y = m_Size.Top + 377;
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y -  DEFAULT_FONTSIZE;
		m_LabelGold->setPosition(pos);
		m_LabelGold->setString(gbk_str);
		m_Layer->addChild(m_LabelGold);

		//绑定金币
		gbk_str = IntToStr(g_MySelf->m_nGamePoint);
		pos.x = m_Size.Left + 200 ;
		pos.y = m_Size.Top + 377;
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y -  DEFAULT_FONTSIZE;
		m_LabelBindGold->setPosition(pos);
		m_LabelBindGold->setString(gbk_str);
		m_Layer->addChild(m_LabelBindGold);

		//元宝
		gbk_str = IntToStr(g_MySelf->m_nGameGold);
		pos.x = m_Size.Left + 45 ;
		pos.y = m_Size.Top + 404;
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y -  DEFAULT_FONTSIZE;
		m_LabelGameGold->setPosition(pos);
		m_LabelGameGold->setString(gbk_str);
		m_Layer->addChild(m_LabelGameGold);


		int nx = 0;
		int ny = m_Size.Top + 49;
		int idx = 0;
		int index = 0;
		for(int i =0;i < 8;i++)
		{
			nx = m_Size.Left + 17;
			for(int j = 0;j < 8;j++)
			{
				if((int)strlen(g_ItemArr[index].s.Name) > 0)
				{
					img = GetBagImage(g_ItemArr[index].s.Looks);
					if(img && img->Image_)
					{
						m_Layer->addChild(img->GetImage(nx,ny ));
					}
					//强十发光
					img = nullptr;
				int stlevel = g_ItemArr[index].btValue[19] & 0x0F;
				if(stlevel == 10)
				{
					img = GetUIImage(5500 + GetTickCount() / 100 % 10);
				}else if(stlevel == 9)
				{
					img = GetUIImage(5540 + GetTickCount() / 100 % 10);
				}else if(stlevel == 8)
				{
					img = GetUIImage(5550 + GetTickCount() / 100 % 10);
				}
				cocos2d::Sprite* sprite;
				BlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
				if(img && img->Image_)
				{
					sprite = img->GetImage(nx + img->nx,
						ny +img->ny);
					
					sprite->setBlendFunc(cbl);
					m_Layer->addChild(sprite);
				}
				//画物品特效 2013.11.25
				if(g_ItemArr[index].s.CharLooks > 200/*排除翅膀*/)
				{
					img = GetUIImage(g_ItemArr[idx].s.CharLooks + GetTickCount() / 150 % 10);
					if(img && img->Image_)
					{
						sprite = img->GetImage(nx + img->nx,
							ny +img->ny);
						
						sprite->setBlendFunc(cbl);
						m_Layer->addChild(sprite);
					}
				}
				idx++;
				nx += 40;
				}

				index ++;
				
			}
			ny += 40;
		}
		m_Layer->addChild(m_BtnClose);
	}

	void CBagDialog::MouseDown(cocos2d::Vec2 pos)
	{
		int nx =0;
		int ny = m_Size.Top + 49;
		int index = 0;
		cocos2d::Rect rect;
		bool bFind = false;
		for(int i =0;i < 8;i++)
		{
			nx =  m_Size.Left + 17;
			for(int j = 0;j < 8;j++)
			{
				rect = cocos2d::Rect(nx,ny,40,40);
				if(rect.containsPoint(pos))
				{
					bFind = true;
					break;
				}
				nx += 40;
				index++;
			}
			if(bFind)break;
			ny += 40;
		}

		if((int)strlen(g_ItemArr[index].s.Name) > 0)
		{

			std::string iname,d1,d2,d3,mstr,str1;
			bool useable;
			g_MouseItem = g_ItemArr[index];
			GetMouseItemInfo(iname, d1, d2, d3, useable);
			GetMouseItemMosaicInfo(mstr);
			str1 = "[bold:]" + iname + "[/bold]" +d1 + "\\" + d2 + "\\" +d3 + GetGroupItemInfo(&g_MouseItem.s,g_MySelf->m_btSex);
			CHitDialog* hitdialog = (CHitDialog*)FrmMain::GetInstance()->GetDialog(DIALOG_TYPE::HIT);
			hitdialog->Hide();
			hitdialog->ShowHint(TPlayScene::GetInstance()->GetUILayer(),100,100,str1,0xFFFFFFFF,false,0xFF423018,mstr);
		}
	}
}
