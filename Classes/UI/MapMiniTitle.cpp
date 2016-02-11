#include "MapMiniTitle.h"
#include "../VDImage.h"
#include "../MShare.h"
#include "../PlayScene.h"
#include "../Common/IconvString.h"
namespace VD_UI
{
	CMapMiniTitle::CMapMiniTitle(void)
	{
		 m_Layer = nullptr;
	}


	CMapMiniTitle::~CMapMiniTitle(void)
	{
	}

	void CMapMiniTitle::Show(cocos2d::Layer* layer )
	{
		if(m_Layer)Hide();
		m_Layer = cocos2d::Layer::create();
		m_Layer->retain();
		layer->addChild(m_Layer);

		m_LabelName = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",m_Size.Left + 9,6);
		m_LabelPoint = TPlayScene::GetInstance()->DrawFontEx(m_Layer,"",m_Size.Left,6);
		m_LabelName->retain();
		m_LabelPoint->retain();
		CBaseDialog::Show(layer);
	}

	void CMapMiniTitle::Hide()
	{
		if(!m_Layer)return;
		m_Layer->removeAllChildrenWithCleanup(true);
		m_Layer->release();

		m_LabelName->release();
		m_LabelPoint->release();
		m_Layer = nullptr;
		CBaseDialog::Hide();
	}

	void CMapMiniTitle::Render()
	{
		
		if(!g_MySelf)return;
		m_Layer->removeAllChildrenWithCleanup(true);
		TVDImage* img = GetUIImage(140);
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(m_Size.Left,m_Size.Top));
		}
		
		cocos2d::Vec2 pos; int nx,ny;
		std::string gbk_str,utf8_str;
		char szBuf[100];
		gbk_str = g_sMapTitle;
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		//pos.x = nx;pos.y = ny;
		//pos = Director::getInstance()->convertToGL(pos);
		//m_LabelName->setPosition(pos);
		m_LabelName->setString(utf8_str);
		m_Layer->addChild(m_LabelName);
	
		sprintf(szBuf,"%d,%d",g_MySelf->m_nCurrX,g_MySelf->m_nCurrY);
		gbk_str = szBuf;
		utf8_str = GBKToUTF8_string(gbk_str.c_str(),gbk_str.length());
		nx = m_Size.Left + 147 - TextWidth(gbk_str);
		ny = 6;
		pos.x = nx;pos.y = ny;
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y - 12;
		m_LabelPoint->setPosition(pos);
		m_LabelPoint->setString(utf8_str);
		m_Layer->addChild(m_LabelPoint);
		
	}

	void CMapMiniTitle::MouseDown(cocos2d::Vec2 pos)
	{

	}

}

