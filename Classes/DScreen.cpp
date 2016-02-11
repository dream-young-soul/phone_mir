#include "DScreen.h"

#include "PlayScene.h"
#include "./Net/NetClient.h"
#include "./Net/NetRecvMsg.h"
#include "./Net/NetSendMsg.h"
#include "FrmMain.h"
#include "VD_Share.h"

#include "MShare.h"
#include "VDImage.h"
#include "./Common/IconvString.h"
#include "./UI/JoyStick.h"
#include "./UI/JoyVirtualKey.h"

using namespace VD_Net;

static TIntoScene* m_IntoScene_Instance = nullptr;
TIntoScene* TIntoScene::GetInstance()
{
	if(!m_IntoScene_Instance)
	{
		m_IntoScene_Instance = new TIntoScene;
	}
	return m_IntoScene_Instance;
}
void TIntoScene::Show(cocos2d::Layer* layer,cocos2d::Vec2 showpos)
{
	m_Layer = cocos2d::Layer::create();
	m_Layer->retain();
	layer->addChild(m_Layer);
	m_Layer->setPosition(showpos);

	TVDImage* img = GetUIImage(1000);
	cocos2d::Vec2 pos;
	if(img && img->Image_ )
	{
		pos.x = (SCREENWIDTH - img->pWidth) / 2;
		pos.y = (SCREENHEIGHT - img->pHeight) / 2;
		m_Layer->addChild(img->GetImage(pos.x,pos.y));
	}


}

void TIntoScene::Hide()
{
	m_Layer->release();
}

static TLoginScene* m_LoginScene_Instance = nullptr;
TLoginScene* TLoginScene::GetInstance()
{
	if(!m_LoginScene_Instance)
	{
		m_LoginScene_Instance = new TLoginScene;
	}
	return m_LoginScene_Instance;
}

void TLoginScene::Show(cocos2d::Layer* layer,cocos2d::Vec2 showpos)
{
	m_Layer = Layer::create();
	m_Layer->retain();
	layer->addChild(m_Layer);

	Node* rootNode = CSLoader::createNode("project_ui/Login_Scene.csb");

	//居中显示
	Size size = rootNode->getContentSize();
	Vec2 pos;
	rootNode->setAnchorPoint(pos);
	pos.x = (SCREENWIDTH - size.width) / 2;
	pos.y = (SCREENHEIGHT - size.height) / 2;
	pos = Director::getInstance()->convertToGL(pos);
	pos.y = pos.y - size.height;
	rootNode->setPosition(pos);
	//------------
	m_Layer->addChild(rootNode,1,11);
	btn_login = dynamic_cast<ui::Button*>(rootNode->getChildByName("btn_login"));
	ui::TextField* user_edit = dynamic_cast<ui::TextField*>(rootNode->getChildByName("TextField_user"));
	ui::TextField* pswd_edit = dynamic_cast<ui::TextField*>(rootNode->getChildByName("TextField_pswd"));
	user_edit->setString("ttt11");
	pswd_edit->setString("88888888");
	std::string str = user_edit->getString();
	btn_login->addTouchEventListener(CC_CALLBACK_2(TLoginScene::btn_Login_click, this));
}


void TLoginScene::btn_Login_click(Ref* pSender,Widget::TouchEventType type)
{
	

	if(type == Widget::TouchEventType::ENDED)
	{
		
		ui::Button* btn_login = dynamic_cast<ui::Button*>(pSender);
		Node* rootNode = btn_login->getParent();
		int nSize = rootNode->getChildrenCount();
		ui::TextField* user_edit = dynamic_cast<ui::TextField*>(rootNode->getChildByName("TextField_user"));
		ui::TextField* pswd_edit = dynamic_cast<ui::TextField*>(rootNode->getChildByName("TextField_pswd"));
		ui::Text* text_tips = dynamic_cast<ui::Text*>(rootNode->getChildByName("text_tips"));
		std::string sUser = user_edit->getString();
		std::string sPswd = pswd_edit->getString();
		std::string  str;
		char condest[1024];
		if(sUser.length() <= 0 && sPswd.length() <= 0) 
		{
			//需要做出提示
			str = "请输入帐号和密码";
			GBKToUTF8((char*)str.c_str(),str.length(),condest,sizeof(condest));
			str = condest;
			text_tips->setString(str);
			return;
		}
		//测试帐号
	
		std::string filepath = FileUtils::getInstance()->fullPathForFilename("data/ip.txt");
		ssize_t nLen = 0;

		cocos2d::Data fdata = cocos2d::FileUtils::getInstance()->getDataFromFile(filepath);
		std::string ip = "112.90.26.227";
		unsigned char* pIP = fdata.getBytes();
	
		ip = (char*)pIP;
		text_tips->setString(ip);
		//ip = "198.211.3.86";
		if(CNetClient::GetInstance()->Connect(ip.c_str(),1500))
		{
			CNetClient::GetInstance()->GetSendMsg()->Login(sUser.c_str(),sPswd.c_str());
			
		}else
		{
			str = "服务器连接失败";
			GBKToUTF8((char*)str.c_str(),str.length(),condest,sizeof(condest));
			str = condest;
			text_tips->setString(str);
		}
	}
	
	
}
void TLoginScene::Hide()
{
	m_Layer->release();
	m_Layer = nullptr;
}



static TSelectChrScreen* m_SelectChr_Instance = nullptr;
TSelectChrScreen::TSelectChrScreen()
{
	SelectedChrIndex = 0;
	m_ChrList.clear();
}

TSelectChrScreen::~TSelectChrScreen()
{

}
TSelectChrScreen* TSelectChrScreen::GetInstance()
{
	if(!m_SelectChr_Instance)
	{
		m_SelectChr_Instance = new TSelectChrScreen();
	}
	return m_SelectChr_Instance;
}

void TSelectChrScreen::SetSelectRole(int index)
{
	if(index >= (int)m_ChrList.size())return;
	SelectedChrIndex = index;
	cocos2d::Node* root = dynamic_cast<cocos2d::Node*>(m_Layer->getChildByTag(11));
	char c[128];
	std::string str;
	cocos2d::Sprite* img_select;
	for(int i = 0;i < 4;i++)
	{
		sprintf(c,"img_select_%d",i); 
		str = c;
		img_select = dynamic_cast<cocos2d::Sprite*>(root->getChildByName(str));
		img_select->setVisible(false);
		if(index == i)
		{
			img_select->setVisible(true);
		}
	}

}
void TSelectChrScreen::SetChrChildInfo(int index,TUserCharacterInfo info)
{
	std::string str_name;
	std::string str_job;
	std::string str_img;
	std::string str_bg;
	char c[128];
	sprintf(c,"bg_%d",index); str_bg = c;
	sprintf(c,"img_head_%d",index); str_img = c;
	sprintf(c,"text_name_%d",index);str_name = c;
	sprintf(c,"text_job_%d",index);str_job = c;
	cocos2d::Node* root = dynamic_cast<cocos2d::Node*>(m_Layer->getChildByTag(11));
	
	ui::ImageView* bg = dynamic_cast<ui::ImageView*>(root->getChildByName(str_bg));
	bg->setVisible(true);
	ui::Text* text_name = dynamic_cast<ui::Text*>(root->getChildByName(str_name));
	text_name->setVisible(true);
	ui::Text* text_job = dynamic_cast<ui::Text*>(root->getChildByName(str_job));
	text_job->setVisible(true);
	cocos2d::Sprite* img_head = dynamic_cast<cocos2d::Sprite*>(root->getChildByName(str_img));
	

	str_name = info.name; str_name = GBKToUTF8_string(str_name.c_str(),str_name.length());
	text_name->setString(str_name);
	str_job =IntToJob(info.job) +"   LV:";
	sprintf(c,"%s%d",str_job.c_str(),info.level);
	str_job = c;str_job = GBKToUTF8_string(str_job.c_str(),str_job.length());
	text_job->setString(str_job);

	//设置头像
	sprintf(c,"project_ui/select_role/%d_%d.png",info.sex,info.job);
	std::string spath = c;
	spath = FileUtils::getInstance()->fullPathForFilename(spath);
	if(FileUtils::getInstance()->isFileExist(spath))
	{
		cocos2d::Sprite* img_new = cocos2d::Sprite::create(spath);
		img_new->setPosition(img_head->getPosition());
		root->addChild(img_new);
	}

}

void TSelectChrScreen::onTouchesEnded(Touch *touch, Event *unused_event)
{
	cocos2d::Vec2 pos;
	
	
	//乱搞乱搞！！
	cocos2d::Node* root = m_Layer->getChildByTag(11);
	cocos2d::Sprite* img_head;
	std::string str; char c[128];
	for(int i = 0;i < 4;i++)
	{
		sprintf(c,"bg_%d",i); str = c;
		img_head = dynamic_cast<cocos2d::Sprite*>(root->getChildByName(str));
		pos = touch->getLocation();
		pos.y = pos.y - img_head->getContentSize().height / 2;
		pos.x = pos.x - img_head->getContentSize().width / 2;
		if(img_head->getBoundingBox().containsPoint(pos))
		{
			SetSelectRole(i);
			break;
		}
	}
	

}
void TSelectChrScreen::onTouchMoved(Touch *touch,Event* unused_event)
{
	
}
bool TSelectChrScreen::onTouchesBegan(Touch *touch,Event *unused_event)
{
	
	return true;
}

void TSelectChrScreen::UpdateChrList()
{

}
void TSelectChrScreen::Show(cocos2d::Layer* layer)
{
	m_Layer = cocos2d::Layer::create();
	m_Layer->retain();
	layer->addChild(m_Layer);
	
	cocos2d::Node* rootnode = CSLoader::createNode("project_ui/Select_scene.csb");
	//居中显示
	Size size = rootnode->getContentSize();
	Vec2 pos;
	rootnode->setAnchorPoint(pos);
	pos.x = (SCREENWIDTH - size.width) / 2;
	pos.y = (SCREENHEIGHT - size.height) / 2;
	pos = Director::getInstance()->convertToGL(pos);
	pos.y = pos.y - size.height;
	rootnode->setPosition(pos);
	//------------
	m_Layer->addChild(rootnode,1,11);
	
	for(int i = 0;i < (int)m_ChrList.size();i++)
	{
		if(i > 3)break;//只画四个
		TUserCharacterInfo info = m_ChrList[i];
		SetChrChildInfo(i,info);
	}
	//设置选中角色
	SetSelectRole(SelectedChrIndex);



	//触摸事件
	//m_Layer->setTouchEnabled(true);
	//EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();  
	//auto listen = EventListenerTouchOneByOne::create();
	//listen->onTouchBegan = CC_CALLBACK_2(TSelectChrScreen::onTouchesBegan,this); //触碰开始 
	//listen->onTouchMoved = CC_CALLBACK_2(TSelectChrScreen::onTouchesEnded,this);  //触碰移动
	//listen->onTouchEnded = CC_CALLBACK_2(TSelectChrScreen::onTouchesEnded,this);  //触碰结束
	//eventDispatcher->addEventListenerWithSceneGraphPriority(listen,rootnode);  

	//开始游戏
	ui::Button* btn_start = dynamic_cast<ui::Button*>(rootnode->getChildByName("btn_start"));
	btn_start->addTouchEventListener(CC_CALLBACK_2(TSelectChrScreen::btn_Start_click, this));
	//创建角色-
	ui::Button* btn_create = dynamic_cast<ui::Button*>(rootnode->getChildByName("btn_create"));
	btn_create->addTouchEventListener(CC_CALLBACK_2(TSelectChrScreen::btn_Create_click,this));
	//删除角色
	ui::Button* btn_delete = dynamic_cast<ui::Button*>(rootnode->getChildByName("btn_delete"));
	btn_delete->addTouchEventListener(CC_CALLBACK_2(TSelectChrScreen::btn_Delete_click,this));

	for(int i = 0;i < 4;i++)
	{
		char c[128];sprintf(c,"bg_%d",i);
		std::string str = c;
		ui::ImageView* img_bg = dynamic_cast<ui::ImageView*>(rootnode->getChildByName(str));
		img_bg->addTouchEventListener(CC_CALLBACK_2(TSelectChrScreen::img_bg_Click,this));
		
	}

}

void TSelectChrScreen::img_bg_Click(Ref* pSender,Widget::TouchEventType type)
{
	if(type == Widget::TouchEventType::ENDED)
	{
		ui::ImageView* sel = dynamic_cast<ui::ImageView*>(pSender);
		cocos2d::Node* rootNode = dynamic_cast<cocos2d::Node*>(m_Layer->getChildByTag(11));
		std::string str;
		char c[128];
		for(int i = 0;i < 4;i++)
		{
			sprintf(c,"bg_%d",i); str = c;
			ui::ImageView* img = dynamic_cast<ui::ImageView*>(rootNode->getChildByName(str));
			if(str == sel->getName())
			{
				SetSelectRole(i);
				break;
			}
		}
	}
}
void TSelectChrScreen::btn_Delete_click(Ref* pSender,Widget::TouchEventType type)
{
	if(type == Widget::TouchEventType::ENDED)
	{
		TUserCharacterInfo info = m_ChrList[SelectedChrIndex];
		CNetClient::GetInstance()->GetSendMsg()->SendDelChr(info.name.c_str());
	}

}
void TSelectChrScreen::btn_Create_click(Ref* pSender,Widget::TouchEventType type)
{
	TDScreen::GetInstance()->ChangeScene(stNewChr);
}
void TSelectChrScreen::btn_Start_click(Ref* pSender,Widget::TouchEventType type)
{
	if(type == Widget::TouchEventType::ENDED)
	{
		TUserCharacterInfo info = m_ChrList[SelectedChrIndex];
		CNetClient::GetInstance()->chrname = info.name;
		CNetClient::GetInstance()->GetSendMsg()->SelectChr(info.name.c_str());
	}
}
void TSelectChrScreen::PlayScene()
{


}
void TSelectChrScreen::Hide()
{
	m_Layer->release();
}
void TSelectChrScreen::ClearChr()
{
	m_ChrList.clear();
}
void TSelectChrScreen::AddChr(std::string uname,int job,int hair,int level,int sex)
{
	TUserCharacterInfo info;
	info.name = uname;
	info.job = job;
	info.hair = hair;
	info.level = level;
	info.sex = sex;
	m_ChrList.push_back(info);
}
static TCreateScreen* m_CreateScene_Instance = nullptr;
TCreateScreen::TCreateScreen()
{

}

TCreateScreen::~TCreateScreen()
{

}

TCreateScreen* TCreateScreen::GetInstance()
{
	if(!m_CreateScene_Instance)
	{
		m_CreateScene_Instance = new TCreateScreen();
	}
	return m_CreateScene_Instance;
}

void TCreateScreen::Show(cocos2d::Layer* layer)
{

	m_nCurJob = m_nCurSex = 0;
	m_Layer = cocos2d::Layer::create();
	m_Layer->retain();
	layer->addChild(m_Layer);
	Node* rootNode = CSLoader::createNode("project_ui/Create_scene.csb");
	//居中显示-------------
	Size size = rootNode->getContentSize();
	Vec2 pos;
	rootNode->setAnchorPoint(pos);
	pos.x = (SCREENWIDTH - size.width) / 2;
	pos.y = (SCREENHEIGHT - size.height) / 2;
	pos = Director::getInstance()->convertToGL(pos);
	pos.y = pos.y - size.height;
	rootNode->setPosition(pos);
	//-------------------
	m_Layer->addChild(rootNode,1,11);

	SetSelectJob(m_nCurJob);
	SetSelectSex(m_nCurSex);
	//EventDispatcher* eventDispatcher = Director::getInstance()->getEventDispatcher();  
	//auto listen = EventListenerTouchOneByOne::create();
	//listen->onTouchBegan = CC_CALLBACK_2(TCreateScreen::onTouchesBegan,this); //触碰开始 
	//listen->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchesMoved,this);  //触碰移动
	//listen->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchesEnded,this);  //触碰结束
	//listen->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchesCancelled,this);  //触碰取消
	//eventDispatcher->addEventListenerWithSceneGraphPriority(listen,rootNode);  
	//按钮事件-

	//随机名称
	ui::Button* btn_start = dynamic_cast<ui::Button*>(rootNode->getChildByName("btn_start"));
	btn_start->addTouchEventListener(CC_CALLBACK_2(TCreateScreen::btn_start_click,this));
	ui::Button* btn_random = dynamic_cast<ui::Button*>(rootNode->getChildByName("btn_random"));
	btn_random->addTouchEventListener(CC_CALLBACK_2(TCreateScreen::btn_random_click,this));
	//三个职业
	ui::Button* btn_warrior = dynamic_cast<ui::Button*>(rootNode->getChildByName("btn_warrior"));
	btn_warrior->addTouchEventListener(CC_CALLBACK_2(TCreateScreen::btn_Job_click,this));
	ui::Button* btn_maga = dynamic_cast<ui::Button*>(rootNode->getChildByName("btn_maga"));
	btn_maga->addTouchEventListener(CC_CALLBACK_2(TCreateScreen::btn_Job_click,this));
	ui::Button* btn_tao = dynamic_cast<ui::Button*>(rootNode->getChildByName("btn_tao"));
	btn_tao->addTouchEventListener(CC_CALLBACK_2(TCreateScreen::btn_Job_click,this));
	std::string str_sex[] = {"man_warror","woman_warror","man_maga","woman_maga","man_tao","woman_tao"};
	for(int i =0;i < 6;i++)
	{
		ui::ImageView* img = dynamic_cast<ui::ImageView*>(rootNode->getChildByName(str_sex[i]));
		img->addTouchEventListener(CC_CALLBACK_2(TCreateScreen::btn_Sex_click,this));
	}
}


void TCreateScreen::SetTips(int errorcode)
{
	cocos2d::Node* rootnode = m_Layer->getChildByTag(11);
	ui::Text* text_tips = dynamic_cast<ui::Text*>(rootnode->getChildByName("text_tips"));
	std::string str;
	switch(errorcode)
	{
	case 0:
		{
			str = "[错误信息] 输入的角色名称包含非法字符！ 错误代码 = 0";
			break;
		}
	case 2:
		{
			str = "[错误信息] 创建角色名称已被其他人使用！ 错误代码 = 2";
			break;
		}
	case 3:
		{
			str = "[错误信息] 不能创建更多的角色了！ 错误代码 = 3";
			break;
		}
	case 4:
		{
			str = "[错误信息] 创建角色时出现错误！ 错误代码 = 4";
			break;;
		}
	default:
		{
			str = "[错误信息] 创建角色时出现未知错误,可能存在重名或其他原因！";
		}
	}
	str = GBKToUTF8_string(str.c_str(),str.length());
	text_tips->setString(str);
}

void TCreateScreen::btn_random_click(Ref* pSender,Widget::TouchEventType type)
{
	if(type == Widget::TouchEventType::ENDED)
	{
		std::string sName = randomName(m_nCurSex);
		sName = GBKToUTF8_string(sName.c_str(),sName.length());
		cocos2d::Node* rootNode = dynamic_cast<cocos2d::Node*>(m_Layer->getChildByTag(11));
		ui::TextField* text_name = dynamic_cast<ui::TextField*>(rootNode->getChildByName("text_name"));
		text_name->setString(sName);

	}
}
void TCreateScreen::btn_Sex_click(Ref* pSender,Widget::TouchEventType type)
{
	if(type == Widget::TouchEventType::ENDED)
	{
		ui::ImageView* img = dynamic_cast<ui::ImageView*>(pSender);
		std::string str = img->getName();
		int nSex = 1;
		if(str == "man_warror" || str == "man_maga" || str == "man_tao")
		{
			nSex = 0;
		}
		SetSelectSex(nSex);	
	}

}
void TCreateScreen::btn_Job_click(Ref* pSender,Widget::TouchEventType type)
{
	if(type == Widget::TouchEventType::ENDED)
	{
		ui::Button* btn = dynamic_cast<ui::Button*>(pSender);
		std::string str = btn->getName();
		int njob = 0;
		if(str == "btn_warrior") njob = 0;
		if(str == "btn_maga") njob = 1;
		if(str == "btn_tao") njob = 2;
		SetSelectJob(njob);
	}

}
void TCreateScreen::btn_start_click(Ref* pSender,Widget::TouchEventType type)
{
	
	if(Widget::TouchEventType::ENDED == type)
	{
		cocos2d::Node* rootnode = m_Layer->getChildByTag(11);
		ui::TextField* edit_name = dynamic_cast<ui::TextField*>(rootnode->getChildByName("text_name"));
		std::string name = edit_name->getString();
		if(name.length() <= 0)
		{
			return;
		}
		name = UTF8ToGBK_string(name.c_str(),name.length());
		char c[10]; sprintf(c,"%d",m_nCurJob);
		char c_sex[10];sprintf(c_sex,"%d",m_nCurSex);
		tempUserInfo.name = name;
		tempUserInfo.job = m_nCurJob;
		tempUserInfo.sex = m_nCurSex;
		CNetClient::GetInstance()->GetSendMsg()->SendNewChr(name.c_str(),c,c_sex);
	}
}
bool TCreateScreen::onTouchesBegan(Touch *touch, Event *unused_event)
{
	//Node* rootNode = m_Layer->getChildByTag(11);
	////三个职业的按钮选择
	//cocos2d::Vec2 pos ;
	//std::string str_job[] = {"btn_warrior","btn_maga","btn_tao"};
	//for(int i = 0;i < 3;i++)
	//{
	//
	//	cocos2d::Sprite* img_job = dynamic_cast<Sprite*>(rootNode->getChildByName(str_job[i]));
	//	pos = touch->getLocation();
	//	pos = Director::getInstance()->convertToUI(pos);
	//	pos.y = pos.y - img_job->getContentSize().height / 2;
	//	pos.x = pos.x - img_job->getContentSize().width / 2;
	//	if(img_job->getBoundingBox().containsPoint(pos))
	//	{
	//		SetSelectJob(i);
	//	}
	//}

	//std::string str_sex[] = {"man_warror","woman_warror","man_maga","woman_maga","man_tao","woman_tao"};
	//for(int i = 0;i < 6;i++)
	//{
	//	ui::ImageView* img_sex = dynamic_cast<ui::ImageView*>(rootNode->getChildByName(str_sex[i]));
	//	if(img_sex->isVisible())
	//	{
	//
	//		pos = touch->getLocation();
	//		pos.y = pos.y - img_sex->getContentSize().height ;
	//		pos.x = pos.x - img_sex->getContentSize().width ;
	//		if(img_sex->getBoundingBox().containsPoint(pos))
	//		{
	//			int nsex = 1;
	//			if(i == 0 || i == 2 || i == 4)
	//			{
	//				nsex = 0;
	//			}
	//			SetSelectSex(nsex);
	//			break;
	//		}
	//	}
	//}
	
	//Sprite* man = dynamic_cast<Sprite*>(rootNode->getChildByName("man_warror_1"));

	//a->getBoundingBox()
	//Vec2 pos = touch->getLocation();
	//if(man->getBoundingBox().containsPoint(pos))
	//{
	//	CCLOG("click hero img");
	//}
	return true;
}
void TCreateScreen::Hide()
{
	m_Layer->release();
}

void TCreateScreen::SetSelectSex(int sex)
{
	std::string str_job[] = {"man_warror","woman_warror","man_maga","woman_maga","man_tao","woman_tao"};
	int wIndex[2];
	switch(m_nCurJob)
	{
	case 0:
		{
			wIndex[0] = 0; wIndex[1] = 1;
			break;
		}
	case 1:
		{
			wIndex[0]=2; wIndex[1]=3;
			break;
		}
	case 2:
		{
			wIndex[0] =4; wIndex[1] = 5;
			break;
		}
	}
	cocos2d::Node* root_node = dynamic_cast<cocos2d::Node*>(m_Layer->getChildByTag(11));

	for(int i = 0;i < sizeof(wIndex) / sizeof(int);i++)
	{
		ui::ImageView* img_sex = dynamic_cast<ui::ImageView*>(root_node->getChildByName(str_job[wIndex[i]]));
		if(sex == i) 
		{
			img_sex->setOpacity(255);
		}else img_sex->setOpacity(150);
	}
	m_nCurSex = sex;


}
void TCreateScreen::SetSelectJob(int index)
{
	
	cocos2d::Node* root = dynamic_cast<cocos2d::Node*>(m_Layer->getChildByTag(11));
	cocos2d::Sprite* img_select = dynamic_cast<cocos2d::Sprite*>(root->getChildByName("img_select"));
	ui::Button* img_job;
	std::string str_job[] = {"man_warror","woman_warror","man_maga","woman_maga","man_tao","woman_tao"};
	for(int i = 0;i < 6;i++)
	{
		ui::ImageView* _img = dynamic_cast<ui::ImageView*>(root->getChildByName(str_job[i]));
		_img->setVisible(false);
		_img->setOpacity(150); //透明
	}
	int wIndex[2];
	switch(index)
	{
	case 0:
		{
			img_job = dynamic_cast<ui::Button*>(root->getChildByName("btn_warrior"));
		    wIndex[0] = 0; wIndex[1] = 1;
			break;
		}
	case 1:
		{
			img_job = dynamic_cast<ui::Button*>(root->getChildByName("btn_maga"));
			wIndex[0]=2; wIndex[1]=3;
			break;
		}
	case 2:
		{
			img_job = dynamic_cast<ui::Button*>(root->getChildByName("btn_tao"));
			wIndex[0] =4; wIndex[1] = 5;
			break;
		}
	}
	img_select->setVisible(true);
	img_select->setPosition(img_job->getPosition());

	for(int i = 0;i < sizeof(wIndex) / sizeof(int);i++)
	{
		ui::ImageView* img_ = dynamic_cast<ui::ImageView*>(root->getChildByName(str_job[wIndex[i]]));
		img_->setVisible(true);
	}
	m_nCurJob = index;
	m_nCurSex = 0;
	SetSelectSex(m_nCurSex);
}
static TDScreen* m_Instance = nullptr;

TDScreen::TDScreen(void)
{
	m_Layer = cocos2d::Layer::create();
	m_Layer->retain();

}


TDScreen::~TDScreen(void)
{
}
TDScreen* TDScreen::GetInstance()
{
	if(!m_Instance)
	{
		m_Instance = new TDScreen();
	}	
	return m_Instance;
}

void TDScreen::ChangeScene(TSceneType scene)
{
	m_Layer->removeAllChildrenWithCleanup(true);
	switch (mScene)
	{
	case stIntro:
		{
			TIntoScene::GetInstance()->Hide();
			break;
		}
	case stLogin:
		{
			TLoginScene::GetInstance()->Hide();
			break;
		}
	case stSelectChr:
		{
			TSelectChrScreen::GetInstance()->Hide();
			break;
		}
	case stNewChr:
		{
			TCreateScreen::GetInstance()->Hide();
			break;
		}
	case stLoginNotice:
		{
			break;
		}
	case stPlayGame:
		{
			break;
		}
	}
	mScene = scene;
	cocos2d::Vec2 pos;
	switch(mScene)
	{
	case stIntro:
		{
			
			TIntoScene::GetInstance()->Show(m_Layer,pos);
			m_StartLogoTick = GetTickCount();
			break;
		}
	case stLogin:
		{
			TLoginScene::GetInstance()->Show(m_Layer,pos);
			break;
		}
	case stNewChr:
		{
			TCreateScreen::GetInstance()->Show(m_Layer);
			
			break;
		}
	case stSelectChr:
		{
			TSelectChrScreen::GetInstance()->Show(m_Layer);
			break;
		}
	case stPlayGame:
		{
			//---先清理无用的纹理
			
			Director::getInstance()->getTextureCache()->removeUnusedTextures();

			
			//str = Director::getInstance()->getTextureCache()->getCachedTextureInfo();
			m_Layer->addChild(TPlayScene::GetInstance()->GetTitleLayer());
			m_Layer->addChild(TPlayScene::GetInstance()->GetActorLayer());
			m_Layer->addChild(TPlayScene::GetInstance()->GetUILayer());

			//显示左上角
			FrmMain::GetInstance()->ShowDialog(DIALOG_TYPE::MYSTATE);
			//显示摇杆
			CJoyStick::GetInstance()->Show(TPlayScene::GetInstance()->GetUILayer());
			//显示虚拟按键
			CJoyVirtualKey::GetInstance()->Show(TPlayScene::GetInstance()->GetUILayer());
			//显示主控面板
			TPlayScene::GetInstance()->Show_Dialog(DIALOG_TYPE::SHORTCUTS);
			//显示迷你地图栏
			FrmMain::GetInstance()->ShowDialog(DIALOG_TYPE::MAPMINITITLE);
			//显示迷你任务栏
			FrmMain::GetInstance()->ShowDialog(DIALOG_TYPE::MINITASK);
			
			
			break;
		}
	}
}

void TDScreen::PlayScene()
{
	//LOGO界面切换-
	if(mScene == stIntro)
	{
		if(GetTickCount() - m_StartLogoTick > 2000)
		{
			ChangeScene(stLogin);
			return;
		}
	}
	switch(mScene)
	{
	case stLogin:
		{
			break;
		}
	case stNewChr:
		{
			break;
		}
	case stSelectChr:
		{
			TSelectChrScreen::GetInstance()->PlayScene();
			break;
		}
	case stPlayGame:
		{
			//UI层--
			FrmMain::GetInstance()->ProcessDialogUI();
			FrmMain::GetInstance()->ProcessActionMessages();
			TPlayScene::GetInstance()->PlayScene();
			break;
		}
	}
	//处理网络封包事件
	bool ret = CNetClient::GetInstance()->ProcessMsg();
	if(ret)
	{
		CNetRecvMsg* recvmsg =  CNetClient::GetInstance()->GetRecvMsg();
		TPlayScene::GetInstance()->ProcessNetEvent();
		recvmsg->ClearNetEventData();
	}
}