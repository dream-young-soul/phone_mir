#include "MyStatePan.h"
#include "VDImage.h"
#include "MShare.h"
#include "PlayScene.h"
#include "./Common/IconvString.h"
namespace VD_UI
{
	CMyStatePan::CMyStatePan(void)
	{
	}


	CMyStatePan::~CMyStatePan(void)
	{
	}

	void CMyStatePan::Show(cocos2d::Layer* layer )
	{
		CBaseDialog::Show(layer);
		m_Layer = cocos2d::Layer::create();
		m_Layer->retain();
		layer->addChild(m_Layer);

		m_LabelName = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xffeeb4FF,true);
		m_LabelName->setDimensions(150,12);
		m_LabelName->retain();
		m_LabelLv = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",1,1,0xffeeb4FF,true);
		m_LabelLv->retain();
	}

	void CMyStatePan::Hide()
	{
		CBaseDialog::Hide();
		m_Layer->removeAllChildrenWithCleanup(true);
		m_Layer->release();
		m_Layer = nullptr;
		m_LabelName->release();
		m_LabelLv->release();
	}
	
	void CMyStatePan::Render()
	{
		if(!g_MySelf)return;
		m_Layer->removeAllChildrenWithCleanup(true);

		TVDImage* img = GetUIImage(250);
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(m_Size.Left,m_Size.Top));
		}
		 //Í·Ïñ
		int i  = 340 + g_MySelf->m_btJob * 2 + g_MySelf->m_btSex;
		img = GetUIImage(i);
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(m_Size.Left + 16,m_Size.Top + 82- img->pHeight));
		}
		//vip
		i = 850 + MAX_(0,g_VIPLevel);
		img = GetUIImage(i);
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(79,0));
		}
		char szChar[1024]={0};
		cocos2d::Vec2 pos;
		std::string gbk_str;
		gbk_str = UTF8ToGBK_string(g_MySelf->m_sUserName.c_str(),
		g_MySelf->m_sUserName.size());

		pos.x = 65 +( 150 - TextWidth(gbk_str)) /2;
		pos.y = 25;
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y -  DEFAULT_FONTSIZE;
		m_LabelName->setPosition(pos);
		m_LabelName->setString(g_MySelf->m_sUserName);
		sprintf(szChar,"%d",g_MySelf->m_Abil.Level);
		pos.x = m_Size.Left + 88 - TextWidth(szChar) / 2;
		pos.y = m_Size.Top + 79;
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y -  DEFAULT_FONTSIZE;
		m_LabelLv->setPosition(pos);
		m_LabelLv->setString(szChar);

		m_Layer->addChild(m_LabelName);
		m_Layer->addChild(m_LabelLv);
		cocos2d::Sprite* sprite;
		cocos2d::Rect r;
		int nx;int ny;
		//»­hp
		if(g_MySelf->m_Abil.MaxHP  > 0 && g_MySelf->m_Abil.MaxMP > 0)
		{
			img = GetUIImage(247);
			if(img && img->Image_)
			{
				r = cocos2d::Rect(0,0,(float)img->pWidth * ((float)g_MySelf->m_Abil.HP /
					(float)g_MySelf->m_Abil.MaxHP),25);
				nx = m_Size.Left + 92;
				ny = m_Size.Top + 41;
				sprite = img->GetImage(nx,ny);
				sprite->setVertexRect(r);
				m_Layer->addChild(sprite);

			}

			img = GetUIImage(248);
			if(img && img->Image_)
			{
				r = cocos2d::Rect(0,0,(float)img->pWidth * ((float)g_MySelf->m_Abil.MP /
					(float)g_MySelf->m_Abil.MaxMP),25);
				nx = m_Size.Left + 92;
				ny = m_Size.Top + 52;
				sprite = img->GetImage(nx,ny);
				sprite->setVertexRect(r);
				m_Layer->addChild(sprite);
			}

			img = GetUIImage(249);
			if(img && img->Image_)
			{
				r = cocos2d::Rect(0,0,(float)img->pWidth * ((float)g_SubAbil.WrathPoint /
					(float)g_SubAbil.MaxWrathPoint),25);
				nx = m_Size.Left + 92;
				ny = m_Size.Top + 63;
				sprite = img->GetImage(nx,ny);
				sprite->setVertexRect(r);
				m_Layer->addChild(sprite);
			}
		}
		
	}
}

