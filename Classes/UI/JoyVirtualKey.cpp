#include "JoyVirtualKey.h"
#include "../VD_Share.h"
#include "../MShare.h"
#include "../Actor.h"
#include "../FrmMain.h"
#include "../GuaJiHelper.h"
static CJoyVirtualKey* m_Instance = nullptr;
CJoyVirtualKey::CJoyVirtualKey(void)
{
	m_Layer = nullptr;
}


CJoyVirtualKey::~CJoyVirtualKey(void)
{
}

CJoyVirtualKey* CJoyVirtualKey::GetInstance()
{
	if(!m_Instance)
	{
		m_Instance = new CJoyVirtualKey;
	}
	return m_Instance;
}

void CJoyVirtualKey::Show(cocos2d::Layer* layer)
{
	if(m_Layer)Hide();
	m_Layer = cocos2d::Layer::create();
	m_Layer->retain();
	layer->addChild(m_Layer);
	//共用一个纹理
	m_BGImage = new cocos2d::Image;
	m_BGImage->initWithImageFile("project_ui/hotkey/bg.png");
	m_BGTex = new cocos2d::Texture2D;
	m_BGTex->initWithImage(m_BGImage);

	//四个背景框-
	cocos2d::Vec2 pos;
	pos = cocos2d::Vec2(SCREENWIDTH - m_BGImage->getWidth() - 40,
		SCREENHEIGHT - m_BGImage->getHeight() - 10);
	CreateBGSprite(pos);
	ui::Button* btn_Attack = ui::Button::create(ATTACK_NORMAL,ATTACK_CLICK);
	btn_Attack->setAnchorPoint(cocos2d::Vec2(0,0));
	cocos2d::Vec2 glpos = cocos2d::Director::getInstance()->convertToGL(pos);
	btn_Attack->setPosition(glpos);
	m_Layer->addChild(btn_Attack);
	btn_Attack->addTouchEventListener(CC_CALLBACK_2(CJoyVirtualKey::btn_key1_click, this));
}

void CJoyVirtualKey::btn_key1_click(cocos2d::Ref* pSender,ui::Widget::TouchEventType type)
{
	TActor* actor = TGuaJiHelper::GetInstance()->SearchTargetEx();
	if(actor)
	{
		g_TargetCret = actor;
		FrmMain::GetInstance()->AttackTarget(actor);
	}
}

void CJoyVirtualKey::Hide()
{
	if(!m_Layer)return;
	m_Layer->removeAllChildrenWithCleanup(true);
	m_Layer->release();
	m_Layer = nullptr;
	delete m_BGImage;
	delete m_BGTex;
}

void CJoyVirtualKey::CreateBGSprite(cocos2d::Vec2 pos)
{
	cocos2d::Sprite* bgs;
	bgs = cocos2d::Sprite::createWithTexture(m_BGTex);
	bgs->setAnchorPoint(cocos2d::Vec2(0,0));
	m_Layer->addChild(bgs,0,100);
	cocos2d::Vec2 glpos = cocos2d::Director::getInstance()->convertToGL(pos);
	bgs->setPosition(glpos);
}