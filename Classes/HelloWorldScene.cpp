#include "HelloWorldScene.h"
#include "PlayScene.h"
//#include "MapUnit.h"
#include "MShare.h"
#include "./Net/NetClient.h"
#include "./Net/NetSendMsg.h"
//#include "./Net/NetRecvMsg.h"
#include "FrmMain.h"
#include "VD_Share.h"
#include "DScreen.h"

#include "ui/CocosGUI.h"
#include "./UI/JoyStick.h"

USING_NS_CC;

using namespace VD_Net;
Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{

    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }

	FrmMain::GetInstance()->Init();
	//鼠标事件
	//this->setTouchEnabled(true);
	//this->setTouchMode(Touch::DispatchMode::ONE_BY_ONE);//单点触控
	EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();  
	auto listen = EventListenerTouchOneByOne::create();
	listen->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchesBegan,this); //触碰开始 
	listen->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved,this);  //触碰移动
	listen->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded,this);  //触碰结束
	listen->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchesCancelled,this);  //触碰取消
	eventDispatcher->addEventListenerWithSceneGraphPriority(listen,this);  
	
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//把场景加进来。
	this->addChild(TDScreen::GetInstance()->GetLayer());
	TDScreen::GetInstance()->ChangeScene(stIntro);

	this->schedule(schedule_selector(HelloWorld::_update));

    return true;
}


void HelloWorld::_update(float fDelay)
{

	TDScreen::GetInstance()->PlayScene();

}



bool HelloWorld::onTouchesBegan(Touch *touch, Event *unused_event)
{
	if(g_UIClick)
	{
		g_UIClick = false;
		return true;
	}
	//摇杆- 
	if(CJoyStick::GetInstance()->IsMove())return true;
	//检测是否单击了对话框
	Vec2 pos = touch->getLocationInView();
	if(FrmMain::GetInstance()->CheckDialogClickBegan(pos))
	{
		return true;
	}
	FrmMain::GetInstance()->SetMove(true,pos.x,pos.y);
	return true;

}
void HelloWorld::onTouchesMoved(Touch *touch, Event *unused_event)
{
	if(g_UIClick)
	{
		g_UIClick = false;
		return ;
	}
	//摇杆- 
	Vec2 pos;
	pos = touch->getLocationInView();
	if(CJoyStick::GetInstance()->IsMove())
	{
		return;
	}
	//检测是否单击了对话框
	if(FrmMain::GetInstance()->CheckDialogClickBegan(pos))
	{
		FrmMain::GetInstance()->SetMove(false);
		return;
	}
	FrmMain::GetInstance()->SetMove(true,pos.x,pos.y);

}
void HelloWorld::onTouchesEnded(Touch *touch, Event *unused_event)
{
	if(g_UIClick)
	{
		g_UIClick = false;
		return;
	}
	Vec2 pos;
	pos = touch->getLocationInView();
	FrmMain::GetInstance()->ClickDialog(pos);

	FrmMain::GetInstance()->SetMove(false);

}
void HelloWorld::onTouchesCancelled(Touch *touch, Event *unused_event)
{
	FrmMain::GetInstance()->SetMove(false);
}

