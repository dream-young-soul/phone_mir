//场景切换管理器
#ifndef TDSCREEN_H_
#define TDSCREEN_H_
#include "cocos2d.h"
#include "cocos-ext.h"
#include "GameStruct.h"
#include "cocostudio/CocoStudio.h"
#include <vector>
#include "GameStruct.h"
#include "ui/CocosGUI.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
//LOGO场景
class TIntoScene
{
public:
	TIntoScene(){};
	~TIntoScene(){};
	static TIntoScene* GetInstance();
	void Show(cocos2d::Layer* layer,cocos2d::Vec2 showpos);
	void Hide();
private:
	cocos2d::Layer* m_Layer;
};

//登录角色场景
class TLoginScene 
{
public:
	TLoginScene(){};
	~TLoginScene(){};
	static TLoginScene* GetInstance();
	void Show(cocos2d::Layer* layer,cocos2d::Vec2 showpos);
	void Hide();
private:
	cocos2d::Layer* m_Layer;
	ui::Button* btn_login;

	void btn_Login_click(Ref* pSender,Widget::TouchEventType type);
	
	
};

//选择角色场景
class TSelectChrScreen
{
public:
	TSelectChrScreen();
	~TSelectChrScreen();
	static TSelectChrScreen* GetInstance();
public:
	void Show(cocos2d::Layer* layer);
	void Hide();
public:
	int SelectedChrIndex;
	void AddChr(std::string uname,int job,int hair,int level,int sex);
	void ClearChr();
	int GetChrList(){return (int)m_ChrList.size();}
	void PlayScene();
	void SetChrChildInfo(int index,TUserCharacterInfo info);
	//设置选中角色
	void SetSelectRole(int index);
	void UpdateChrList();
private:
	cocos2d::Layer* m_Layer;
	std::vector<TUserCharacterInfo> m_ChrList;
private:
	void btn_Start_click(Ref* pSender,Widget::TouchEventType type);
	void btn_Create_click(Ref* pSender,Widget::TouchEventType type);
	void btn_Delete_click(Ref* pSender,Widget::TouchEventType type);
	void img_bg_Click(Ref* pSender,Widget::TouchEventType type);
	void onTouchesEnded(Touch *touch, Event *unused_event);
	void onTouchMoved(Touch *touch,Event* unused_event);
	bool onTouchesBegan(Touch *touch,Event *unused_event);
};

//创建角色场景
class TCreateScreen 
{
public:
	TCreateScreen();
	~TCreateScreen();
	static TCreateScreen* GetInstance();
public:
	void Show(cocos2d::Layer* layer);
	void Hide();
	cocos2d::Layer* GetLayer(){return m_Layer;}
	int m_nCurJob;
	int m_nCurSex;
	TUserCharacterInfo tempUserInfo;
	void SetTips(int errorcode);
private:
	cocos2d::Layer* m_Layer;
	bool onTouchesBegan(Touch *touch, Event *unused_event);
	void SetSelectJob(int index); //设置选中职业
	void SetSelectSex(int sex); //设置选中性别
	void btn_start_click(Ref* pSender,Widget::TouchEventType type);
	void btn_Job_click(Ref* pSender,Widget::TouchEventType type);
	void btn_Sex_click(Ref* pSender,Widget::TouchEventType type);
	void btn_random_click(Ref* pSender,Widget::TouchEventType type);
};
class TDScreen
{
public:
	TDScreen(void);
	~TDScreen(void);
	static TDScreen* GetInstance();
	void ChangeScene(TSceneType scene);
	void PlayScene();
	cocos2d::Layer* GetLayer(){return m_Layer;}
	TSceneType GetCurentScene(){return mScene;}


private:
	TSceneType mScene;
	cocos2d::Layer* m_Layer;
	unsigned long m_StartLogoTick;
};

#endif
