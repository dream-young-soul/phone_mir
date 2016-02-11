#include "MagicDialog.h"
#include "../VDImage.h"
#include "../MShare.h"
#include "../PlayScene.h"
#include "../Common/IconvString.h"
namespace VD_UI
{

	CMagicDialog::CMagicDialog(void)
	{
		m_Layer = nullptr;
		m_MagicName.clear();
		m_Level.clear();
	}


	CMagicDialog::~CMagicDialog(void)
	{
		
	}

	void CMagicDialog::Show(cocos2d::Layer* layer /* = nullptr */)
	{
		if(m_Layer)Hide();
		CBaseDialog::Show(layer);
		m_Layer = cocos2d::Layer::create();
		m_Layer->retain();
		layer->addChild(m_Layer);

		m_BtnClose = ui::Button::create(CLOSE_NORMAL,CLOSE_CLICK);
		cocos2d::Vec2 pos;
		pos = Vec2(m_Size.Left + 292,m_Size.Top + 6);
		pos = Director::getInstance()->convertToGL(pos);
		m_BtnClose->setAnchorPoint(cocos2d::Vec2(0,0));
		pos.y = pos.y - m_BtnClose->getContentSize().width;
		m_BtnClose->setPosition(pos);
		m_BtnClose->retain();
		m_BtnClose->addTouchEventListener(CC_CALLBACK_2(CMagicDialog::btn_Close_click, this));
		
	}

	void CMagicDialog::btn_Close_click(Ref* pSender,ui::Widget::TouchEventType type)
	{
		if(type == ui::Widget::TouchEventType::ENDED)
		{
			Hide();
			g_UIClick = true;
		}
	}
	void CMagicDialog::Hide()
	{
		if(!m_Layer)return;
		m_Layer->removeAllChildrenWithCleanup(true);
		m_Layer->release();
		m_Layer = nullptr;

		cocos2d::Label* label;
		for(int i = 0;i < (int)m_MagicName.size();i++)
		{
			label = m_MagicName[i];
			label->release();

			label = m_Level[i];
			label->release();
		}
		m_Level.clear();
		m_MagicName.clear();
		m_BtnClose->release();
		CBaseDialog::Hide();
	}
	void CMagicDialog::MouseDown(cocos2d::Vec2 pos)
	{

	}

	void CMagicDialog::Render()
	{
		m_Layer->removeAllChildrenWithCleanup(true);
		TVDImage* img;
		img = GetUIImage(511);
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(m_Size.Left,m_Size.Top));
		}
		TVDImage* bkimg = GetUIImage(220);
		TVDImage* expimg = GetUIImage(221);
		//画技能图标
		TClientMagic* pm;
		int nx,ny;
		cocos2d::Label* label;
		std::string utf_str;
		for(int i = 0;i < (int)g_MagicList.size();i++)
		{
			pm = g_MagicList[i];
			nx = m_Size.Left + 15 + (i % 2) * 150;
			ny = m_Size.Top + 50 + (i / 2) * 50;
			if(bkimg && bkimg->Image_)
			{
				m_Layer->addChild(bkimg->GetImage(nx,ny)); //魔法区块
			}
			img  = GetUIImage(pm->Def.wMagicId - 1 + 10000); //魔法图标  ,ui图片10000开始是魔法图标
			if(img && img->Image_)
			{
				m_Layer->addChild(img->GetImage( nx + 19 - img->pWidth / 2,
					ny + 19 - img->pHeight / 2));
			}
			
			//魔法名字
			utf_str = GBKToUTF8_string(pm->Def.sMagicName,strlen(pm->Def.sMagicName));
			if(i >= (int)m_MagicName.size())
			{
				
				label = TPlayScene::GetInstance()->DrawFontEx(m_Layer,utf_str,nx + 48,ny + 7,0xffffffff);
				label->retain();
				m_MagicName.push_back(label);
			}else 
			{
				label = m_MagicName[i];
				m_Layer->addChild(label);
			}
			label->setString(utf_str);

			//魔法等级
			utf_str = IntToStr(pm->Level);
			if(i >= (int)m_Level.size())
			{

				label = TPlayScene::GetInstance()->DrawFontEx(m_Layer,utf_str,nx + 61,ny + 26,0xffffffff);
				label->retain();
				m_Level.push_back(label);
			}else 
			{
				label = m_Level[i];
				m_Layer->addChild(label);
			}
			label->setString(utf_str);
			//魔法等级
			if(expimg && expimg->Image_ && pm->Level >= 0 && pm->Level < 4)
			{
				cocos2d::Sprite* sprite = expimg->GetImage(nx + 104,ny + 28);
				cocos2d::Rect rect;
				rect = cocos2d::Rect(0,0,(float)expimg->pWidth * (float)pm->CurTrain / (float)pm->Def.MaxTrain[pm->Level],
					expimg->pHeight);
				sprite->setTextureRect(rect);
				m_Layer->addChild(sprite);
			}
		}
		m_Layer->addChild(m_BtnClose);
	}
}
