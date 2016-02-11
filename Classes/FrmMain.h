#ifndef FRMMAIN_H_
#define FRMMAIN_H_
#include "GameStruct.h"
#include "VD_Share.h"
#include "./UI/BaseDialog.h"
class TActor;
class FrmMain
{
public:
	FrmMain(void);
	~FrmMain(void);
	static FrmMain* GetInstance();
public:
	bool ServerAcceptNextAction();
	int Init();
	void InitDialog();//初始化对话框
	void ShowReAliveDlg();
	void _DXDrawMouseDown(int x,int y);
	bool CanNextAction();
	void ProcessActionMessages();
	bool IsUnLockAction(int Action,int adir);
	bool CanNextMove();
	unsigned long  getNextMoveflag();
	bool CheckDoorAction(int dx,int dy);
	void SendSpellMsg(int ident, int X, int Y, int dir, int target);
	void SendActMsg(int ident,int X,int Y,int dir,int nF);
	void ProcessSpecialMsg(const char* msg);
	void ActionOK();
	void ActionFailed();
	void AttackTarget(TActor* target);
	bool CanNextHit();
	bool TargetInSwordLongAttackRange(int ndir);
	void AutoEat();
	void AutoPickUpItem();
	bool AutoPickUpItemEx();
	void SendMagicKeyChange(int magid,unsigned char keych);
	void AutoRecallBaobao(); //自动召唤宝宝
	void SendSay(std::string str);

	void SetMove(bool bMove,int x = 0,int y = 0);
	void UseMagicSpell(int who,int effnum,int targetx,int targety,int magic_id);

	void ShowDialog(DIALOG_TYPE nType,std::string param = "",std::string param2 = "");
	VD_UI::CBaseDialog* GetDialog(DIALOG_TYPE nType);
	bool IsDialogVisible(DIALOG_TYPE nType);
	void HideDialog(DIALOG_TYPE nType);
	bool CheckDialogClickBegan(cocos2d::Vec2 pos);
	bool ClickDialog(cocos2d::Vec2 pos);
	void ProcessDialogUI();
	int ActionKey;
	void UseMagic(int tx,int ty,TClientMagic* pcm);
	void DoLocalTaskCMD(int nTaskID,std::string sCMD);

private:
	//int m_DemoTick;
	bool ActionLock;
	unsigned long ActionLockTime;
	int LastActionOk; ///wukong 20130417 最后一次收到动作成功的时间戳
	
	bool m_bMove;
	TPoint m_MovePos;
	std::map<int,VD_UI::CBaseDialog*> m_ListDialog;
private:
	void InitActorInfo();
	void SendButchAnimal(int x,int y,int dir,int actorid);
	TClientMagic* FindMagic(int wMagicId);
	
	void MouseTimerTimer();
	void MinTimerTimer();
	void AutoTimer();
	void ProcessTimer(); //处理时钟定时器事件
	//nType: Integer; ObjectID: TActor; nLib: word; nStart: Integer; nFrame: integer);
	void DrawEffectHumex(int nType,TActor* ObjectID,unsigned short nLib = 0,int nStart = 0,int nFrame = 0);
public:
	int FailAction;
	int FailDir;
	unsigned long m_MouseTimer;
	unsigned long m_MinTimer;
	bool m_bAutoTimer;
	unsigned long m_AutoTimer;

public:
	void ClientGetHealthSpellChanged(tagDefaultMessage* msg);
	void ShowAddBlood(TActor* actor,int Num);
	void ClientGetSTRUCK(tagDefaultMessage* msg,std::string body);
	void ClientGetActorHP(tagDefaultMessage* msg,std::string body);
	void ClientGetAdjustBonus(tagDefaultMessage* msg,std::string body);
	void Client_ServerConfig(tagDefaultMessage* msg);
	void Client_MapDescription(tagDefaultMessage* msg,std::string body);
	void Client_GameGoldName(tagDefaultMessage* msg,std::string body);
	
	void Client_MagicFire(int who,int efftype,int effnum,int targetx,int targety,int target);
	void Client_AddMagic(std::string body);
	void Client_SendMyMagic(std::string body);
	void Client_ShowEvent(tagDefaultMessage* msg,std::string body);
	void Client_MerchantSay(tagDefaultMessage* msg,std::string body);
	void Client_QueryChr(tagDefaultMessage* msg,std::string body);
	void Client_ItemShow(tagDefaultMessage* msg,std::string body);
	void Client_ItemHide(tagDefaultMessage* msg,std::string body);
	void Client_BagItems(tagDefaultMessage* msg,std::string body);
	void Client_SendUseItems(tagDefaultMessage* msg,std::string body);
	void Client_WalkTo(tagDefaultMessage* msg,std::string body);
	void Client_TakeOnOK(tagDefaultMessage* msg,std::string body);
	void Client_UpdateItem(tagDefaultMessage* msg,std::string body);
	void Client_KillMon(tagDefaultMessage* msg,std::string body);
	void Client_LevelUp(tagDefaultMessage* msg,std::string body);
	void Client_AddItem(tagDefaultMessage* msg,std::string body);
	void Client_SendJingMai(tagDefaultMessage* msg,std::string body);
	void Client_ChangeNameColor(tagDefaultMessage* msg,std::string body);
	void Client_MagicEff(tagDefaultMessage* msg,std::string body);
	void Client_DuraChange(tagDefaultMessage* msg,std::string body);
	void Client_MagicLvExp(tagDefaultMessage* msg,std::string body);
	void Client_GetIcons(tagDefaultMessage* msg,std::string body);
	void Client_Task(tagDefaultMessage* msg,std::string body);
	void Client_SpeelNeed(tagDefaultMessage* msg,std::string body);
public:

	bool LoadMapGates(); //加载地图连接点信息
	void ClearMapGate();//清空地图连接点信息
	void reCurMapGate(); //更新当前地图连接点列表信息
	void BeginAutoRun(std::string sDescMap,int nx,int ny,std::string sTargetname="",
		bool bKillMon = false,int nTargetXYD = 0,bool bWalk = false);
	void StopAutoRun(bool stopkillmon = true);
	bool AutoRun();
	
};

#endif
