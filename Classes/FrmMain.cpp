#include "FrmMain.h"
#include "MShare.h"
#if	defined(WIN32)	
#include <windows.h>
#endif
#include "cocos2d.h"
#include "PlayScene.h"
#include "MapUnit.h"
#include "./Net/NetClient.h"
#include "./Net/NetSendMsg.h"
#include "./Net/EnDecode.h"
#include "./Common/Grobal2.h"
#include "FileStream.h"
#include "./Common/ZipUnit.h"
#include "./Common/SoundUtil.h"
#include "BaseConfig.h"
#include "clEvent.h"
#include "DScreen.h"
#include "PathHelper.h"
#include "GuaJiHelper.h"
#include "./UI/BaseDialog.h"
#include "./UI/NpcDialog.h"
#include "./UI/MyStatePan.h"
#include "MagicEff.h"
#include "./UI/ShortcutsDialog.h"
#include "./UI/RoleStateDialog.h"
#include "./UI/BagDialog.h"
#include "./UI/HitDialog.h"
#include "./UI/MagicDialog.h"
#include "./UI/MapMiniTitle.h"
#include "./UI/MiniTaskPan.h"
using namespace VD_Net;
using namespace VD_UI;
static FrmMain* m_Instance = nullptr;
FrmMain::FrmMain(void)
{
	m_ListDialog.clear();
	FailAction = 0;
	FailDir = 0;
	ActionLock = false;
	ActionLockTime = GetTickCount();
	m_MouseTimer = GetTickCount();
	m_MinTimer = GetTickCount();
	ActionKey = 0;
	m_bMove = false;
	m_MovePos.x = 0; m_MovePos.y  = 0;
	m_AutoTimer = GetTickCount();
	m_bAutoTimer = false;
}


FrmMain::~FrmMain(void)
{
}

FrmMain* FrmMain::GetInstance()
{
	if(!m_Instance)
	{
		m_Instance = new FrmMain();
	}
	return m_Instance;
}

bool FrmMain::ServerAcceptNextAction()
{
	if(ActionLock)
	{//若服务器未响应动作命令，则10秒后自动解锁
		if(GetTickCount() - ActionLockTime > /*10 * */1000)
		{
			ActionLock = false;
		}
		return false;
	}
	return true;
}

int FrmMain::Init()
{
	memset(&g_Icons[0],0,sizeof(g_Icons));
	g_jmLevel1 = 0;
	g_jmLevel2 = 0;
	g_jmLevel3 = 0;
	g_jmLevel4 = 0;
	g_jmLevel5 = 0;
	g_jmLevel6 = 0;
	g_pneuma = 0;
	g_UIClick = false;
	g_AutoPicUpItem =nullptr;
	g_AutoRunx = -1;
	g_AutoRuny = -1;
	g_AutoTargetx = -1;
	g_AutoTargety = -1;
	g_AutoTargetdx = -1;
	g_AutoTargetdy = -1;
	g_AutoRunTargetNCPName = "";    
	g_AutoKillMonName = "";
	g_AutoTargetMap = "";
	g_AutoCurMap = "";
	g_AutobWalk = false;
	g_AutoTargetXYD = -1;
	g_dwDropItemFlashTime = 2 *1000;
	g_DropedItemList.clear();
	g_MagicTarget = nullptr;
	g_sGameGoldName= "元宝";
	g_sGamePointName = "绑定金币";
	g_boMapAnonymous = false;
	g_sMapTitle = "";
	g_nMapMusic = 0;
	g_nPlayMusicCount = 0;
	g_boMineMap = false;
	g_sMapMusic = "";
	g_sGoldName ="金币";
	g_SoundList.clear();
	g_AnroidLog.clear();
	g_nDupSelection = 0;
	g_FocusCret = nullptr;
	g_focuscret1 = nullptr;
	g_TargetCret = nullptr;
	g_MapVDDHash.clear();
	g_HumImagesHash.clear();
	g_MySelf = nullptr;
	g_ChangeFaceReadyList.clear();
	g_FreeActorList.clear();
	g_dwDizzyDelayStart = 0;
	g_dwDizzyDelayTime = 0;
	g_boServerChanging = false;
	Shared.reset();
	LastActionOk = GetTickCount();
	g_boCanRunHuman = false;
	g_boCanRunNpc = false;
	g_boCanRunMon = false;
	g_MySelfDeathTime = 0;
	g_ChrAction = caWalk;
	g_nTargetX = 0;
	g_nTargetY = 0;
	g_nMouseX = 0;
	g_nMouseY = 0;
	g_boAutoDig = 0;
	g_nMouseCurrY = 0;
	g_nMouseCurrX = 0;
	g_dwLatestRushRushTick = GetTickCount();
	g_dwLatestPoxue = GetTickCount();
	g_dwAutoHiddentTick = GetTickCount();
	g_boMapMoving = false;
	g_dwLastAttackTick = GetTickCount();
	g_dwLastMoveSpeed = GetTickCount();
	g_dwLastMoveSpeedTick = GetTickCount();
	g_nSendCount = 0;
	ActionFailLock = false;
	ActionFailLockTime = GetTickCount();
	g_dwLastMoveTick = GetTickCount();
	g_dwLatestSpellTick = GetTickCount();
	g_dwMagicPKDelayTime = 0;
	g_dwLatestHitTick = GetTickCount();
	g_nRunReadyCount = 0;
	g_boCanStartRun = true;
	g_nMDlgX = 0;
	g_nMDlgY = 0;
	g_nReceiveCount = 0;
	g_horseTick = GetTickCount();
	g_boAutoFire = false;
	g_dwAutoFireTick = GetTickCount();
	g_boNextTimeFireHit = false;
	g_dwLatestMagicTick = GetTickCount();
	g_dwMagicTime = 1000;
	g_dwLatestFireHitTick = GetTickCount();
	g_boCanLongHit = false;
	g_dwAutoOpenLongHit;
	g_boAutoWide = false;
	g_boCanWideHit = false;
	g_dwAutoOpenWide = 0;
	g_boNextTimePowerHit = false;
	g_boAutoFireCT = false;
	g_boCan34SKillHit = false;
	g_boCan35SKillHit = false;
	g_boCanTwnHit = false;
	g_boCan34SkillHit = false;
	g_boCan35SkillHit = false;
	g_boCan103SkillHit = false;
	g_boCanStnHit = false;
	g_boCan103SKillHit = false;
	g_boCanCrsHit = false;

	g_nHitTime = 605;
	g_nItemSpeed = 10;
	g_MagicList.clear();
	g_MagicExInfoList.clear();
	g_MagicLockActor = 0;
	g_nAutoPickUpX = 0;
	g_nAutoPickupY = 0;
	g_nAutoPickPos = 0;
	g_dwAutoPickupTick = GetTickCount();
	g_dwAutoPickupTime = 500;
	g_dwAutoSayTick = GetTickCount();
	g_nAutosayIdx = 0;
	g_dwAutoShieldTick = GetTickCount();
	g_dwSpellTime =1000;
	g_dwMagicDelayTime = 0;
	g_boWarrPx = 0;
	g_boWarrTbs = 0;
	g_dwLatestStruckTick = GetTickCount();
	g_ReAliveFreeCount = 0;
	g_ReAliveNeedGameGold = 0;
	g_CurLocalMap = nullptr;

	g_MapGateFrame = 0;
	g_MapGateTick = GetTickCount();

	g_nMyAntiMagic = 0;
	g_nCrit = 0;
	g_nMyHitPoint = 0;
	g_nMySpeedPoint = 0;
	g_nMyAntiPoison = 0;
	g_nMyPoisonRecover = 0;
	g_nMyHealthRecover = 0;
	g_nMySpellRecover = 0;
	g_nPKPoint = 0;
	g_nProtect = 0;
	g_VIPLevel = 0;
	g_SubAbil.reset();


	g_nBonusPoint = 0;
	g_nBonusPointChg = 0;
	g_ReNewLevel  = 0;
	g_ReNewCount = 0;
	g_RenewNeedGold = 0;
	g_ClearBonusPointNeedGameGold = 0;
	g_addRenewCountNeedGameGold = 0;
	g_BonusAbil.reset();
	g_BonusTick.reset();
	g_RenewInfo.reset();
	g_nAreaStateValue = 0;
	g_boCanRunAllInWarZone = false;
	InitActorInfo();
	InitDialog();
	CBaseConfig::GetInstance()->LoadConfig();
	LoadMapGates(); //加载地图连接点信息
	//定时器
	//cocos2d::Layer* layer = TPlayScene::GetInstance()->GetActorLayer();
	//layer->scheduleOnce(schedule_selector(FrmMain::MouseTimerTimer,))


	//初始化的全局变量
	//一些全局控制的初始化赋值
	Shared.boItemFlash = true; //地上物品闪烁
	Shared.boShowBlood = true ;//显示血条
	Shared.boShowNumBlood = true; //头顶血条显示数字
	Shared.boCTRLPickUp = true;//快捷键捡东西
	Shared.boShowUserName = true;  //显名
	Shared.boAttackLock = true ;//魔法锁定默认开
	//
	Shared.boLongAttack = true ;//刀刀刺杀
	Shared.boSmartLongAttack = false;  //自动跨位刺杀
	g_boAutoFire = true ;//自动烈火默认开
	g_boAutoWide = true;
	Shared.boMoDun = true;
	Shared.boNoStone = true; //防止石化 麻痹
	//自动吃药的一些初始化



	Shared.boHpMin = true;     //自动吃hp红药
	Shared.nHpMin = 75;
	Shared.nHpTick = 5000;
	Shared.boMpMin = true;     //自动吃魔法药
	Shared.nMpMin = 75; //自动吃魔法药下限
	Shared.nMpTick = 5000; //时间间隔
	Shared.boHPMPfast = true;//快速恢复药
	Shared.nHPMPFastMin = 50;//快速恢复药下限
	Shared.nHPMPFastTack = 500;//时间间隔
	Shared.boUseJuan = false;    //使用回城卷
	Shared.nUseJuanMin = 20;  //使用回城卷hp下限
	Shared.nUseJuanTick = 30000;  //时间间隔
	Shared.boAutoPickUpGold = true; //自动捡取金币
	Shared.boShowLocalFashion = true;
	Shared.boAutoPickUp = true;      //自动捡东西
	Shared.boAutoPickUpDrug = true; //自动捡药
	Shared.boAutorecallBaobao = true; //自动召唤宝宝
	Shared.boHideActor = false;
	
	return 0;
}

void FrmMain::InitActorInfo()
{

	//----------MANPC1000------------------------------------------------------------npc 1000 10帧待机动作
	TActionInfo* action;
	action = &MANPC1000.ActStand;
	action->start = 0;action->frame = 10; action->skip = 0;action->ftime = 70;action->usetick = 0;
	action = &MANPC1000.ActWalk;
	action->start = 80; action->frame = 8; action->skip= 2; action->ftime=90; action->usetick = 3;
	action = &MANPC1000.ActAttack;
	action->start = 160; action->frame = 8; action->skip = 2; action->ftime = 100; action->usetick = 0;
	MANPC1000.ActCritical.reset();
	action = &MANPC1000.ActStruck;
	action->start = 160; action->frame = 2; action->skip = 8; action->ftime = 70; action->usetick= 0;
	action = &MANPC1000.ActDie;
	action->start= 240; action->frame = 8; action->skip =2; action->ftime = 120; action->usetick = 0;
	action = &MANPC1000.ActDeath;
	action->start = 247; action->frame = 1; action->skip= 9; action->ftime= 0; action->usetick= 0;
	action = &MANPC1000.ActAttack1;
	action->start = 400; action->frame = 10; action->skip= 0; action->ftime= 85; action->usetick= 0;
	action = &MANPC1000.ActAttack2;
	action->start = 480; action->frame = 10; action->skip= 0; action->ftime= 85; action->usetick= 0;
	action = &MANPC1000.ActAttack3;
	action->start = 560; action->frame = 10; action->skip= 0; action->ftime= 85; action->usetick= 0;
	action = &MANPC1000.ActAttack4;
	action->start = 640; action->frame = 10; action->skip= 0; action->ftime= 85; action->usetick= 0;
	action = &MANPC1000.ActAttack5;
	action->start = 720; action->frame = 10; action->skip= 0; action->ftime= 85; action->usetick= 0;
	action = &MANPC1000.ActAttack6;
	action->start = 800; action->frame = 10; action->skip= 0; action->ftime= 85; action->usetick= 0;
	//----------MANPC1000------------------------------------------------------------

	//---------MANPCDEF------------------------------------------------------------
	MANPCDEF.reset();
	action = &MANPCDEF.ActStand;
	action->start = 0; action->frame = 4; action->skip = 6;action->ftime = 70;action->usetick = 0;
	action = &MANPCDEF.ActWalk;
	action->start = 80; action->frame = 8; action->skip = 2;action->ftime = 90;action->usetick = 3;
	action = &MANPCDEF.ActAttack;
	action->start = 160; action->frame = 8; action->skip = 2;action->ftime = 100;action->usetick = 0;
	action = &MANPCDEF.ActStruck;
	action->start = 160; action->frame = 2; action->skip = 8;action->ftime = 70;action->usetick = 0;
	action = &MANPCDEF.ActDie;
	action->start = 240; action->frame = 8; action->skip = 2;action->ftime = 120;action->usetick = 0;
	action = &MANPCDEF.ActDeath;
	action->start = 247; action->frame = 1; action->skip = 9;action->ftime = 0;action->usetick = 0;
	action = &MANPCDEF.ActAttack1;
	action->start = 400; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MANPCDEF.ActAttack2;
	action->start = 480; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MANPCDEF.ActAttack3;
	action->start = 560; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MANPCDEF.ActAttack4;
	action->start = 640; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MANPCDEF.ActAttack5;
	action->start = 720; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MANPCDEF.ActAttack6;
	action->start = 800; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	//---------MANPCDEF------------------------------------------------------------


	//----------Plant------------------------------------------------------------------
	PLANT.reset();
	action = &PLANT.ActStand;
	action->start = 0; action->frame = 10; action->skip = 0;action->ftime = 30;action->usetick = 0;
	action = &PLANT.ActWalk;
	action->start = 0; action->frame = 0; action->skip = 2;action->ftime = 90;action->usetick = 3;
	action = &PLANT.ActAttack;
	action->start = 160; action->frame = 8; action->skip = 2;action->ftime = 100;action->usetick = 0;
	action = &PLANT.ActStruck;
	action->start = 160; action->frame = 2; action->skip = 8;action->ftime = 70;action->usetick = 0;
	action = &PLANT.ActDie;
	action->start = 10; action->frame = 1; action->skip = 9;action->ftime = 120;action->usetick = 0;
	action = &PLANT.ActDeath;
	action->start = 10; action->frame = 1; action->skip = 9;action->ftime = 120;action->usetick = 0;
	action = &PLANT.ActAttack1;
	action->start = 400; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &PLANT.ActAttack2;
	action->start = 480; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &PLANT.ActAttack3;
	action->start = 560; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &PLANT.ActAttack4;
	action->start = 640; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &PLANT.ActAttack5;
	action->start = 720; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &PLANT.ActAttack6;
	action->start = 800; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	//----------Plant------------------------------------------------------------------


	//--------------------MINEDEF----------------------------------------------------------
	MINEDEF.reset();
	action = &MINEDEF.ActStand;
	action->start = 0; action->frame = 4; action->skip = 0;action->ftime = 30;action->usetick = 0;
	action = &MINEDEF.ActWalk;
	action->start = 0; action->frame = 0; action->skip = 2;action->ftime = 90;action->usetick = 3;
	action = &MINEDEF.ActAttack;
	action->start = 160; action->frame = 8; action->skip = 2;action->ftime = 100;action->usetick = 0;
	action = &MINEDEF.ActStruck;
	action->start = 160; action->frame = 2; action->skip = 8;action->ftime = 70;action->usetick = 0;
	action = &MINEDEF.ActDie;
	action->start = 5; action->frame = 1; action->skip = 0;action->ftime = 120;action->usetick = 0;
	action = &MINEDEF.ActDeath;
	action->start = 10; action->frame = 1; action->skip = 9;action->ftime = 120;action->usetick = 0;
	action = &MINEDEF.ActAttack1;
	action->start = 400; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MINEDEF.ActAttack2;
	action->start = 480; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MINEDEF.ActAttack3;
	action->start = 560; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MINEDEF.ActAttack4;
	action->start = 640; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MINEDEF.ActAttack5;
	action->start = 720; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MINEDEF.ActAttack6;
	action->start = 800; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;

	//-------------------------------------------------------------------------------------
	MA0.reset();
	action = &MA0.ActStand;
	action->start = 0; action->frame = 4; action->skip = 0;action->ftime = 80;action->usetick = 0;
	action = &MA0.ActWalk;
	action->start = 160; action->frame = 6; action->skip = 0;action->ftime = 120;action->usetick = 3;
	action = &MA0.ActAttack;
	action->start = 320; action->frame = 6; action->skip = 0;action->ftime = 120;action->usetick = 0;
	action = &MA0.ActStruck;
	action->start = 480; action->frame = 2; action->skip = 0;action->ftime = 40;action->usetick = 0;
	action = &MA0.ActDie;
	action->start = 640; action->frame = 5; action->skip = 0;action->ftime = 100;action->usetick = 0;
	action = &MA0.ActDeath;
	action->start = 644; action->frame = 1; action->skip = 4;action->ftime = 0;action->usetick = 0;
	action = &MA0.ActAttack1;
	action->start = 400; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MA0.ActAttack2;
	action->start = 480; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MA0.ActAttack3;
	action->start = 560; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MA0.ActAttack4;
	action->start = 640; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MA0.ActAttack5;
	action->start = 720; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MA0.ActAttack6;
	action->start = 800; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	//-------------------------------------------------------------------------------------
	MA27.reset();
	action = &MA27.ActStand;
	action->start = 0; action->frame = 1; action->skip = 0;action->ftime = 200;action->usetick = 0;
	action = &MA27.ActWalk;
	action->start = 0; action->frame = 0; action->skip = 0;action->ftime = 250;action->usetick = 0;
	action = &MA27.ActAttack;
	action->start = 320; action->frame = 6; action->skip = 0;action->ftime = 120;action->usetick = 0;
	action = &MA27.ActCritical;
	action->start = 0; action->frame = 0; action->skip = 0;action->ftime = 250;action->usetick = 0;
	action = &MA27.ActStruck;
	action->start = 0; action->frame = 0; action->skip = 0;action->ftime = 100;action->usetick = 0;
	action = &MA27.ActDie;
	action->start = 1; action->frame = 10; action->skip = 0;action->ftime = 120;action->usetick = 0;
	action = &MA27.ActDeath;
	action->start = 11; action->frame = 1; action->skip = 0;action->ftime = 150;action->usetick = 0;
	//-------------------------------------------------------------------------------------
	HORSE.reset();


	action = &HORSE.ActStand;
	action->start = 0; action->frame = 4; action->skip = 6;action->ftime = 200;action->usetick = 0;
	action = &HORSE.ActWalk;
	action->start = 1680; action->frame = 6; action->skip = 4;action->ftime = 90;action->usetick = 2;
	action = &HORSE.ActRun;
	action->start = 1760; action->frame = 6; action->skip = 4;action->ftime = 120;action->usetick = 3;
	action = &HORSE.ActAttack;
	action->start = 720; action->frame = 6; action->skip = 4;action->ftime = 75;action->usetick = 0;
	action = &HORSE.ActStruck;
	action->start = 1200; action->frame = 3; action->skip = 7;action->ftime = 70;action->usetick = 0;
	action = &HORSE.ActDie;
	action->start = 1520; action->frame = 4; action->skip = 6;action->ftime = 80;action->usetick = 0;
	action = &HORSE.ActDeath;
	action->start = 1520; action->frame = 4; action->skip = 6;action->ftime = 80;action->usetick = 0;
	action = &HORSE.ActAttack1;
	action->start = 560; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &HORSE.ActAttack2;
	action->start = 480; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &HORSE.ActAttack3;
	action->start = 560; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &HORSE.ActAttack4;
	action->start = 640; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &HORSE.ActAttack5;
	action->start = 720; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &HORSE.ActAttack6;
	action->start = 800; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	//------------------------------------------------------------------------------------------
	//---------------------------------MADEF-----------------------------------------------------------
	MADEF.reset();
	action = &MADEF.ActStand;
	action->start = 0; action->frame = 5; action->skip = 5;action->ftime = 70;action->usetick = 0;
	action = &MADEF.ActWalk;
	action->start = 720; action->frame = 8; action->skip = 2;action->ftime = 100;action->usetick = 0;
	action = &MADEF.ActAttack;
	action->start = 720; action->frame = 6; action->skip = 4;action->ftime = 75;action->usetick = 0;
	action = &MADEF.ActStruck;
	action->start = 160; action->frame = 2; action->skip = 8;action->ftime = 70;action->usetick = 0;
	action = &MADEF.ActDie;
	action->start = 1520; action->frame = 8; action->skip = 2;action->ftime = 120;action->usetick = 0;
	action = &MADEF.ActDeath;
	action->start = 1520; action->frame = 1; action->skip = 9;action->ftime = 80;action->usetick = 0;
	action = &MADEF.ActAttack1;
	action->start = 560; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MADEF.ActAttack2;
	action->start = 480; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MADEF.ActAttack3;
	action->start = 560; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MADEF.ActAttack4;
	action->start = 640; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MADEF.ActAttack5;
	action->start = 720; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	action = &MADEF.ActAttack6;
	action->start = 800; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0;
	//------------------------------------------------------------------------
	//--------------HA------------------------------------------------------------
	HA.reset();
	action = &HA.ActStand;
	action->start = 0; action->frame = 4; action->skip = 6;action->ftime = 200;action->usetick = 0;
	action = &HA.ActWalk;
	action->start = 1680; action->frame = 6; action->skip = 4;action->ftime = 90;action->usetick = 2;
	action = &HA.ActRun;
	action->start = 1760; action->frame = 6; action->skip = 4;action->ftime = 120;action->usetick = 3;

	action = &HA.ActRush;
	action->start = 1760; action->frame = 3; action->skip = 7;action->ftime = 120;action->usetick = 3;

	action = &HA.ActWarMode;
	action->start = 560; action->frame = 2; action->skip = 8;action->ftime = 40;action->usetick = 0;
	action = &HA.ActHit;
	action->start = 720; action->frame = 6; action->skip = 4;action->ftime = 85;action->usetick = 0;
	action = &HA.ActHeavyHit;
	action->start = 640; action->frame = 6; action->skip = 4;action->ftime = 80;action->usetick = 0;
	action = &HA.ActBigHit;
	action->start = 720; action->frame = 6; action->skip = 4;action->ftime = 85;action->usetick = 0;
	action = &HA.ActFireHitReady;
	action->start = 192; action->frame = 6; action->skip = 4;action->ftime = 60;action->usetick = 0;
	action = &HA.ActTSpell;
	action->start = 160; action->frame = 5; action->skip = 5;action->ftime = 60;action->usetick = 0;
	action = &HA.ActFSpell;
	action->start = 160; action->frame = 5; action->skip = 5;action->ftime = 60;action->usetick = 0; //源代码里对传三的一些攻击用了特殊动作，暂时不用，统一
	action = &HA.ActSitdown;
	action->start = 640; action->frame = 6; action->skip = 4;action->ftime = 75;action->usetick = 0;  //蹲下的 挖肉
	action = &HA.ActStruck;
	action->start = 1200; action->frame = 3; action->skip = 7;action->ftime = 70;action->usetick = 0;  //蹲下的 挖肉
	action = &HA.ActStruck;
	action->start = 1360; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0; 
	action = &HA.Act35Hit;
	action->start = 1280; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0; 
	action = &HA.Act103Hit;
	action->start = 880; action->frame = 6 ;action->skip = 4;action->ftime = 85;action->usetick = 0; 
	action = &HA.ActKQStruck;
	action->start = 1440; action->frame = 10; action->skip = 0;action->ftime = 85;action->usetick = 0; 
	action = &HA.ActDie;
	action->start = 1520; action->frame = 4; action->skip = 6;action->ftime = 80;action->usetick = 0; 
	action = &HA.ActMeditation;
	action->start = 1920; action->frame = 4; action->skip = 0;action->ftime = 80;action->usetick = 0; 
	//-------------------------------

}

void FrmMain::ShowReAliveDlg()
{

}

void FrmMain::_DXDrawMouseDown(int x,int y)
{
	//测试--
	//CNetClient::GetInstance()->GetSendMsg()->SendTaskSelect(1,"@dagongji");
	//return;
	if(!g_MySelf && !VDMap::GetInstance()->m_Loaded)return;
	TGuaJiHelper::GetInstance()->Started(false);
	StopAutoRun(); //停止自动走
	g_nMouseX = x;
	g_nMouseY =y;
	g_boAutoDig = false;
	if (g_TargetCret && g_TargetCret->m_btRace != RCC_USERHUMAN)
	{
		g_TargetCret = nullptr;
	}
	int sel;
	TActor* target = TPlayScene::GetInstance()->GetAttackFocusCharacter(x, y, g_nDupSelection, sel, true); 
	TPlayScene::GetInstance()->CXYfromMouseXY(x,y,g_nMouseCurrX,g_nMouseCurrY);
	// //挖矿 待定
	g_nTargetX = -1;
	if(target && target != g_MySelf)
	{
		if(GetTickCount() - g_dwLastMoveTick > 600)
		{
			if(target->m_btRace == RCC_MERCHANT ) //对象是NPC
			{
				CNetClient::GetInstance()->sendDefMsg(CM_CLICKNPC,target->m_nRecogId,0,0,0);
				g_dwLastMoveTick = GetTickCount();
				return;
			}
			//目标没死，攻击
			if(!target->m_boDeath)
			{
				g_TargetCret = target;
				g_FocusCret = target;
				//攻击
				
				if (g_MySelf->m_btHorse == 0)/*骑马状态不可以操作*/ 
				{
					if ((target->m_btRace != RCC_USERHUMAN &&
						target->m_btRace != RCC_GUARD &&
						target->m_btRace != RC_HEROOBJECT &&
						target->m_btRace != RC_PLAYMOSTER &&
						target->m_btRace != RCC_MERCHANT) //&&
						//target->m_sUserName.find('(') < 0)
						)//包括'('的角色名称为召唤的宝宝
					{
						AttackTarget(target);
						
					}
				}

			}
		}
		return;
	}
	//点了自己站立的位置，默认捡东西
	if(g_nMouseCurrX == g_MySelf->m_nCurrX &&
		g_nMouseCurrY == g_MySelf->m_nCurrY)
	{
		if(CanNextAction() && ServerAcceptNextAction())
		{
			if(GetTickCount() - g_dwLastAttackTick > 100)
			{
				CNetClient::GetInstance()->GetSendMsg()->SendPickup(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY);  //捡物品 
				g_dwLastAttackTick = GetTickCount();
			}
		}
	}
	if(GetTickCount() - g_dwLastAttackTick > 600 )
	{
		if(abs(g_MySelf->m_nCurrX - g_nMouseCurrX) <= 3 &&
			abs(g_MySelf->m_nCurrY - g_nMouseCurrY) <= 3)
		{
			g_ChrAction = caWalk;
		}else
		{
			g_ChrAction = caRun;
		}
		g_nTargetX = g_nMouseCurrX;
		g_nTargetY = g_nMouseCurrY;
	}
}

bool FrmMain::CanNextAction()
{
	int r1 = g_MySelf->m_nState & 0x04000000;
	bool r2 = GetTickCount() - g_dwDizzyDelayStart > g_dwDizzyDelayTime;
	if( g_MySelf->IsIdle() &&  (r1 == 0  || Shared.boNoStone)
		&& r2 )
	{
		return true;
	}
	return false;
}

//{
//	鼠标控制 左　键 控制基本的行动：行走、攻击拾取物品和其他东西
//		右　键 近处的点击能够看到物品使用方法，远处的点击能够在地图上跑动。
//		Shift + 左键 强制攻击
//		Ctrl + 左键 跑动
//		Ctrl + 右键 关于对手的信息，如同F10一样。
//		Alt + 右键 取得肉或者其他玩家因为死亡丢失的东西。
//		双　击 拾取在地上的物品或者使用自己包裹中的物品。
//}
void FrmMain::ProcessActionMessages()
{

	int mx, my, mx1, my1, dx, dy, crun;
	unsigned char ndir, adir, mdir;
	bool bowalk, bostop ;
	unsigned char RunStep ;
	if(!g_MySelf)return;
	ProcessTimer();

	//一直按着屏幕跑动
	if(m_bMove)
	{
		_DXDrawMouseDown(m_MovePos.x,m_MovePos.y);
	}
	
	if( Shared.boRunAndRun)//跑不停
	{
		g_ChrAction = caRun;
		g_nTargetX = g_nMouseCurrX;
		g_nTargetY = g_nMouseCurrY;
	}
	if(g_nTargetX > 0)
	{
		CCLOG("targetx:%d",g_nTargetX);
	}
	if(g_nTargetX >= 0)
	{
		g_dwLastMoveSpeed = GetTickCount() - g_dwLastMoveSpeedTick;
		g_dwLastMoveSpeedTick = GetTickCount();

		if(CanNextAction() && ServerAcceptNextAction())
		{
			
			if(g_nTargetX != g_MySelf->m_nCurrX || g_nTargetY != g_MySelf->m_nCurrY)
			{
				mx = g_MySelf->m_nCurrX;
				my = g_MySelf->m_nCurrY;
				dx = g_nTargetX;
				dy = g_nTargetY;
				ndir = GetNextDirection(mx, my, dx, dy);
				switch(g_ChrAction)
				{
				case caWalk:
					{
LB_WALK:
						crun = g_MySelf->CanWalk();
						
						bool isUnLockAction = IsUnLockAction(CM_WALK,ndir);
						bool isNextMove = CanNextMove();
						if(isUnLockAction && isNextMove && crun > 0)
						{
							CCLOG("code 2");
							GetNextPosXY(ndir,mx,my);
							bowalk = true;
							bostop = false;
							g_dwAutoHiddentTick = GetTickCount();    //跑动中不自动隐身
							if(!TPlayScene::GetInstance()->CanWalkEx(mx,my))
							{
								bowalk = false;
								adir = 0;
								if(!bowalk)//这句if 没有任何必要加上去。  上面bowalk永久性等于false。。-----2013.4.7
								{
									mx = g_MySelf->m_nCurrX;
									my = g_MySelf->m_nCurrY;
									GetNextPosXY(ndir, mx, my);
									if( CheckDoorAction(mx, my) )  // 检测传送点-
									{
										bostop = true;
									}
								}
								if(!bostop && !TPlayScene::GetInstance()->CrashMan(mx,my))
								{
									mx = g_MySelf->m_nCurrX;
									my = g_MySelf->m_nCurrY;
									adir = PrivDir(ndir);
									GetNextPosXY(adir, mx, my);
									if(VDMap::GetInstance()->CanMove(mx, my))
									{
										mx = g_MySelf->m_nCurrX;
										my = g_MySelf->m_nCurrY;
										adir = NextDir(ndir);
										GetNextPosXY(adir, mx, my);
										if(VDMap::GetInstance()->CanMove(mx,my))
										{
											bowalk = true;
										}
									}else
									{
										bowalk = true;
									}
								}

								if(bowalk)
								{
									g_MySelf->UpdateMsg(CM_WALK, mx, my, adir, 0, 0, "", 0);
									g_dwLastMoveTick = GetTickCount();
									CCLOG("hero run");

								}else //隐身
								{
									mdir = GetNextDirection(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, dx, dy);
									if( mdir != g_MySelf->m_btDir)
									{
										g_MySelf->SendMsg(CM_TURN, g_MySelf->m_nCurrX, 
											g_MySelf->m_nCurrY, mdir, 0, 0,
											"", 0);
									}

								}
							}else
							{
								g_MySelf->UpdateMsg(CM_WALK, mx, my, ndir, 0, 0, "", 0);
								g_dwLastMoveTick = GetTickCount();
							}

						}else
						{
							g_nTargetX = -1;
						}

						break;
					}
				case caRun:
					{
						if(g_nRunReadyCount >= 1 || g_boCanStartRun)
						{
							crun = g_MySelf->CanRun();  //判断自己的血量是不是能跑得起来
							if( g_MySelf->m_btHorse > 0)
							{
								RunStep = 3;
							}else
							{
								RunStep = 2;
							}

							g_dwAutoHiddentTick = GetTickCount();    //跑动中不自动隐身
							bool bRun =GetDistance(mx, my, dx, dy) >= RunStep;
							if( bRun && crun > 0)
							{
								if(IsUnLockAction(CM_RUN, ndir) && CanNextMove())//是否被锁定---
								{
									mx1 = mx;
									my1 = my;
									if(g_MySelf->m_btHorse > 0)
									{
										GetNextHorseRunXY(ndir, mx, my);
									}else
									{
										GetNextRunXY(ndir, mx, my); //得到下一个坐标
									}

									if(TPlayScene::GetInstance()->CanRun(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, mx, my))
									{
										if(g_MySelf->m_btHorse > 0 )
										{
											g_MySelf->UpdateMsg(CM_HORSERUN, mx, my, ndir, 0, 0, "", 0);
										}else
										{
											g_MySelf->UpdateMsg(CM_RUN, mx, my, ndir, 0, 0, "", 0);
										}
										g_dwLastMoveTick = GetTickCount();
									}else
									{
										mx = mx1;
										my = my1;
										goto LB_WALK;
									}
								}else
								{
									g_nTargetX = -1;
								}
							}else
							{
								g_nTargetX = -1;
								goto LB_WALK;
							}
						}else
						{
							g_nRunReadyCount ++;
							goto LB_WALK;
						}
					}
				}
			}
		}
	}

	g_nTargetX = -1;
	if(g_MySelf->RealActionMsg.Ident > 0)
	{
		FailAction = g_MySelf->RealActionMsg.Ident; //角菩且锭 措厚
		FailDir = g_MySelf->RealActionMsg.dir;

		if(g_MySelf->RealActionMsg.Ident == CM_SPELL)
		{
			SendSpellMsg(g_MySelf->RealActionMsg.Ident,
				g_MySelf->RealActionMsg.x,
				g_MySelf->RealActionMsg.y,
				g_MySelf->RealActionMsg.dir,
				g_MySelf->RealActionMsg.State);
		}else
		{
			SendActMsg(g_MySelf->RealActionMsg.Ident, g_MySelf->RealActionMsg.x,
				g_MySelf->RealActionMsg.y, g_MySelf->RealActionMsg.dir, g_MySelf->RealActionMsg.feature);
		}

		g_MySelf->RealActionMsg.Ident = 0;
		if(g_nMDlgX != -1)
		{
			if(abs(g_nMDlgX - g_MySelf->m_nCurrX) >= 8 &&
				abs(g_nMDlgY - g_MySelf->m_nCurrY) >= 8)
			{
				//FrmDlg.CloseMDlg;
				g_nMDlgX = -1;
			}
		}
	}

}
void FrmMain::SendButchAnimal(int x,int y,int dir,int actorid)
{
	unsigned long tick = GetTickCount();
	tick = (tick >> 16 & 0x0000ffff) | (tick << 16 & 0xFFFF0000);
	char sText[256]={0};
	sprintf(sText,"%d",tick);
	CNetClient::GetInstance()->sendDefMsg(CM_BUTCH,actorid,x,y,dir,sText,true,"/");
	ActionLock = true;                 
	ActionLockTime = GetTickCount();
	g_nSendCount++;
}
void FrmMain::SendActMsg(int ident,int X,int Y,int dir,int nF)
{
	unsigned long tick;
	//客户端时间校验屏蔽
	//m_DemoTick = GetTickCount() + 90 * 6;\
	//时间戳有问题- 待修改 2015.6.9
	tick = GetTickCount();
	tick = (tick >> 16 & 0x0000ffff) | (tick << 16 & 0xFFFF0000);
	char sText[256]={0};
	sprintf(sText,"%d",tick);
	CNetClient::GetInstance()->sendDefMsg(ident,MAKELONG_(X,Y),
		LOWORD_(nF),dir,HIWORD_(nF),sText,true,"/");

	ActionLock = true;                   //辑滚俊辑 #+FAIL! 捞唱 #+GOOD!捞 棵锭鳖瘤 扁促覆
	ActionLockTime = GetTickCount();
	g_nSendCount++;
	
	switch(ident)
	{
	case CM_WALK:
	case CM_RUN:
	case CM_HORSERUN:
		{
			g_dwLastMoveTick = GetTickCount();
			break;
		}
	case CM_BUTCH:
	case CM_HEAVYHIT://采集挖矿和攻击算到一起
	case CM_HIT:
	case CM_BIGHIT:
	case CM_POWERHIT:
	case CM_LONGHIT:
	case CM_WIDEHIT:
	case CM_FIREHIT:
	case CM_CRSHIT:
	case CM_TWNHIT:
		{
			g_dwLatestHitTick = GetTickCount();
			break;
		}
	}

}
void FrmMain::SendSpellMsg(int ident, int X, int Y, int dir, int target)
{
	int tick = GetTickCount();
	tick = (tick >> 16 & 0x0000ffff) | (tick << 16 & 0xFFFF0000);
	char sText[256]={0};
	sprintf(sText,"%d/",tick);
	CNetClient::GetInstance()->sendDefMsg(ident,MAKELONG_(X,Y),
		LOWORD_(target),dir,HIWORD_(target),sText);

	ActionLock = true;
	ActionLockTime = GetTickCount();
	g_nSendCount++;

}
bool FrmMain::IsUnLockAction(int Action,int adir)
{
	bool Result = false;
	if( ActionFailLock ) //如果操作被锁定，则在指定时间后解锁
	{
		if( GetTickCount() - ActionFailLockTime > 1000)
		{
			ActionFailLock = false;
		}
	}

	if( ActionFailLock || g_boMapMoving || g_boServerChanging)
	{
		Result = false;
	}else Result = true;
	return Result;
}

bool FrmMain::CanNextMove()
{
	if(GetTickCount() - g_dwLastMoveTick > getNextMoveflag())
	{
		return true;
	}
	return false;
}

unsigned long FrmMain::getNextMoveflag()
{
	return 0x126 ^ 0xd8;
}

bool FrmMain::CheckDoorAction(int dx,int dy)
{
	//待加
	return false;
}

void FrmMain::ProcessSpecialMsg(const char* msg)
{
	std::string str = msg;

	if(str.find("GOOD") == 0)
	{
		//CCLOG("walk success");
		ActionLock = false;
		g_nSendCount ++;
		ActionOK();

	}else if(str.find("FAIL") == 0)
	{
		CCLOG("walk fail!!");
		ActionFailed();
		ActionLock = true;
		g_nReceiveCount++;
		g_dwLatestHitTick = GetTickCount();
		g_dwLastMoveTick = GetTickCount();
	}else if(str.find("PWR") == 0)	 //打开攻杀
	{
		g_boNextTimePowerHit = true;
	}else if(str.find("LNG") == 0) //打开刺杀
	{
		g_boCanLongHit = true;
	}else if(str.find("ULNG") == 0)////关闭刺杀
	{
		g_boCanLongHit = false;
	}else if(str.find("WID") == 0) //打开半月
	{
		g_boCanWideHit = true;
	}else if(str.find("UWID") == 0) //关闭半月
	{
		g_boCanWideHit = false;
	}else if(str.find("CRS") == 0)//打开双龙    抱月刀法
	{
		g_boCanCrsHit = true;
	}else if(str.find("UCRS") == 0) //关闭双龙  抱月刀法
	{
		g_boCanCrsHit = false;
	}else if(str.find("TWN")== 0) //打开狂风斩
	{
		g_boCanTwnHit = true;
	}else if(str.find("UTWN") == 0) //关闭狂风斩
	{
		g_boCanTwnHit = false;
	}else if(str.find("STN")== 0) //打开狂风斩
	{
		g_boCanStnHit = true;
	}else if(str.find("USTN") == 0) //关闭狂风斩
	{
		g_boCanStnHit = false;
	}else if(str.find("FIR") == 0) //打开烈火剑法
	{
		g_boNextTimeFireHit = true;
		g_dwLatestFireHitTick = GetTickCount();
	}else if(str.find("UFIR"))
	{
		g_boNextTimeFireHit = false; //关闭烈火
	}else if(str.find("S34") == 0) //打开莲月
	{
		g_boCan34SkillHit = true;
	}else if(str.find("US34") == 0) //关闭莲月
	{
		g_boCan34SkillHit = false;
	}else if(str.find("S35") == 0)
	{
		g_boCan35SkillHit = true;
	}else if(str.find("US35") == 0)
	{
		g_boCan35SkillHit = false;
	}else if(str.find("S103") == 0)
	{
		g_boCan103SkillHit = true;
	}else if(str.find("US103") == 0)
	{
		g_boCan103SkillHit = false;
	}
}

void FrmMain::ActionOK()
{
	LastActionOk = GetTickCount();
}
void FrmMain::AttackTarget(TActor* target)
{
	m_bMove = false; //要停止一直按着鼠标走啊 这个BUGGGGGGGGGG 找了好久好久啊啊啊啊 啊 2015.8.8
	int tdir,dx,dy,nHitMsg;
	bool boSpellOk;
	unsigned long nTick;
	TClientMagic* pm;      

	g_horseTick = GetTickCount() + 500;
	nHitMsg = CM_HIT;
	nTick = GetTickCount();
	tdir = GetNextDirection(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, 
		target->m_nCurrX, target->m_nCurrY);
	if(!target->m_boDeath)
	{
		//植物矿物 一个格子以内开始采集
		if (target->m_btRace == RC_PLANT ||
			target->m_btRace == RC_MINE) //植物类  矿类
		{
			if( (abs(g_MySelf->m_nCurrX - target->m_nCurrX) <= 1)
				&& (abs(g_MySelf->m_nCurrY - target->m_nCurrY) <= 1)) 
			{
				if(CanNextAction() && ServerAcceptNextAction() &&
					CanNextHit())
				{
					SendButchAnimal(target->m_nCurrX, target->m_nCurrY, 
						tdir, target->m_nRecogId);  //这个是把消息发送到了服务端
					g_MySelf->SendMsg(CM_BUTCH, g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, tdir, 
						target->m_nRecogId, 0, "", 0); //这个消息不发送到服务器 只是用来更新动作--
					g_dwLatestHitTick = GetTickCount();
				}
			}

		}else
		{
			//距离一格，或者刺杀时距离两格以内，可以攻击
			if( abs(g_MySelf->m_nCurrX - target->m_nCurrX) <= 1
				&& abs(g_MySelf->m_nCurrY - target->m_nCurrY) <= 1
				|| (Shared.boLongAttack && g_MySelf->m_btJob == 0)
				&& FindMagic(12)
				&& abs(g_MySelf->m_nCurrX - target->m_nCurrX) <= 2
				&& abs(g_MySelf->m_nCurrY - target->m_nCurrY) <= 2
				&& (abs(g_MySelf->m_nCurrX - target->m_nCurrX) +
				abs(g_MySelf->m_nCurrY - target->m_nCurrY)) % 2 == 0
				) 
			{
				if( g_MySelf->m_btJob == 0)
				{
					unsigned long nt =  10 * 1000;
					//自动烈火
					if( g_boAutoFire
						&& nTick - g_dwAutoFireTick > 2000
						&& g_MySelf->m_Abil.MP >= 7 && !g_boNextTimeFireHit
						&& nTick - g_dwLatestMagicTick > g_dwMagicTime
						&& nTick - g_dwLatestFireHitTick >= nt)
					{
						g_dwAutoFireTick = GetTickCount();
						pm = FindMagic(26);
						if(pm)
						{
							UseMagic(g_nMouseX, g_nMouseY, pm);
							ActionKey = 0;
							g_nTargetX = -1;
						}
					}
					//自动刺杀 并且刺杀没开 就使用刺杀开启
					if(Shared.boLongAttack && !g_boCanLongHit)
					{
						if(GetTickCount() - g_dwAutoOpenLongHit > 5000)
						{
							g_dwAutoOpenLongHit = GetTickCount();
							pm = FindMagic(12);
							if( pm)
							{
								UseMagic(g_nMouseX, g_nMouseY, pm);
								ActionKey = 0;
								g_nTargetX = -1;
							}
						}
					}
					//自动开半月
					if (! g_boCanWideHit && g_boAutoWide)
					{
						if (GetTickCount() - g_dwAutoOpenWide > 5000)
						{
							pm = FindMagic(25);
							if(pm)
							{
								g_dwAutoOpenWide = GetTickCount();
								UseMagic(g_nMouseX, g_nMouseY, pm);
								ActionKey = 0;
								g_nTargetX = -1;
							}
						}
					}
				}
					///
					if( CanNextAction()
						&& ServerAcceptNextAction()
						&& CanNextHit())
					{
						boSpellOk = true;
						if( g_MySelf->m_btJob == 0)//战士技能- 攻击技能
						{
							if( g_boNextTimeFireHit
								&& g_MySelf->m_Abil.MP >= 7) 
							{
								//如果是烈火，并且在一个格子以外，则不攻击，跳出等走进攻击
								if( g_boAutoFireCT &&
									(abs(g_MySelf->m_nCurrX - target->m_nCurrX) > 1 || abs(g_MySelf->m_nCurrY - target->m_nCurrY) >1))
								{
									boSpellOk = false;
								}else
								{
									g_boNextTimeFireHit = false;
									nHitMsg = CM_FIREHIT;          //烈火
								}

							}else if(g_boNextTimePowerHit)
							{
								if( g_boAutoFireCT &&
									(abs(g_MySelf->m_nCurrX - target->m_nCurrX) > 1 || 
									abs(g_MySelf->m_nCurrY - target->m_nCurrY) >1))
								{  //如果是烈火，并且在一个格子以外，则不攻击，跳出等走进攻击
									boSpellOk = false;
								}else
								{
									g_boNextTimePowerHit = false;
									nHitMsg = CM_POWERHIT;
								}
							}else
							{
								if( g_boCan34SKillHit)
								{
									g_boCan34SKillHit = false;
									nHitMsg = CM_34SKILLHIT;
								}else if(g_boCan35SKillHit)
								{
									g_boCan35SKillHit = false;
									nHitMsg = CM_35SKILLHIT;
								}else if(g_boCanTwnHit && g_MySelf->m_Abil.MP >= 10)
								{
									g_boCanTwnHit = false;
									nHitMsg = CM_TWINHIT;
								}else if(g_boCanWideHit && g_MySelf->m_Abil.MP >= 3)
								{
									nHitMsg = CM_WIDEHIT;        //半月
								}else if(g_boCan103SKillHit)
								{
									nHitMsg = CM_103SKILLHIT;
								}else if(g_boCanLongHit && TargetInSwordLongAttackRange(tdir))
								{
									nHitMsg = CM_LONGHIT;        //刺杀
								}else if(g_boCanCrsHit && g_MySelf->m_Abil.MP >= 6)
								{
									nHitMsg = CM_CRSHIT;
								}
								if( Shared.boLongAttack && g_boCanLongHit)
								{
									nHitMsg = CM_LONGHIT;          //刺杀
								}
								if( g_boCanWideHit && g_boAutoWide && g_MySelf->m_Abil.MP >= 3 &&
									TPlayScene::GetInstance()->FindTargetXYCount(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, 2) > 2 )
								{
									nHitMsg = CM_WIDEHIT;          //半月
								}
							}

						}
						if(boSpellOk)
						{
							g_MySelf->SendMsg(nHitMsg, g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, tdir, target->m_nRecogId, 0, "", 0);
							g_dwLatestHitTick = GetTickCount();
							return;
						}
					}

				
			}

		}
	}
	//到目标跟前去
	if( abs(g_MySelf->m_nCurrX - target->m_nCurrX) <= 2
		&& abs(g_MySelf->m_nCurrY - target->m_nCurrY) <= 2
		&& ! target->m_boDeath) 
	{
		g_ChrAction = caWalk;
	}else 
	{
		g_ChrAction = caRun;
	}
	GetBackPosition(target->m_nCurrX, target->m_nCurrY, tdir, dx, dy);
	//开启远距离刺杀模式时可以退后两格刺杀   不能是植物矿物
	if( Shared.boLongAttack
		&& target->m_btRace != RC_PLANT
		&& (target->m_btRace != RC_MINE)
		&& (g_MySelf->m_btJob == 0)
		&& FindMagic(12)
		&& Shared.boSmartLongAttack/*{自动隔位刺杀}*/)
	{
		GetBackPosition(dx, dy, tdir, dx, dy);
	}
	
	g_nTargetX = dx;
	g_nTargetY = dy;

}
void FrmMain::ActionFailed()
{
	g_nTargetX = -1;
	g_nTargetY = -1;
	ActionFailLock = true;
	ActionFailLockTime = GetTickCount(); //Jacky
	g_MySelf->MoveFail();
}

bool FrmMain::CanNextHit()
{
	//攻击速度默认600，物品加速后最快速度控制在500
	int LevelFastTime;unsigned long NextHitTime;
	LevelFastTime = MIN(100, g_MySelf->m_nHitSpeed * g_nItemSpeed /*{10}*/) ;
	NextHitTime = g_nHitTime /*{600}*/ - LevelFastTime;

	if( NextHitTime < 0)/* {攻击速度调整}*/
	{
		NextHitTime = 0;
	}

	if( GetTickCount() - g_dwLatestHitTick > NextHitTime )
	{
		return true;
	}
	return false;


}

TClientMagic* FrmMain::FindMagic(int wMagicId)
{
	TClientMagic* pm = nullptr;
	for(int i = 0;i < (int)g_MagicList.size();i++)
	{
		pm = g_MagicList[i];
		if(pm->Def.wMagicId == wMagicId)
		{
			return pm;
		}
	}
	return nullptr;
}

void FrmMain::UseMagic(int tx,int ty,TClientMagic* pcm)
{
	TClientMagicExInfo* mex = nullptr;
	int tdir,myx,myy,targx,targy,targid;

	
	if(!pcm)return;
	g_horseTick = GetTickCount() + 500; //骑马延时
	 //算出个人所在屏幕坐标，后面计算鼠标点击方向用
	TPlayScene::GetInstance()->ScreenXYfromMCXY(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY,
		myx,myy);
	myx += HALFX;
	myy += HALFY;
	if(g_MySelf->m_btHorse > 0)return;
	//是否可以使用魔法：需要的点数<当前点数，或者是魔法EffectType = 0

	if(pcm->Def.wSpell + pcm->Def.btDefSpell <= g_MySelf->m_Abil.MP ||
		pcm->Def.btEffectType == 0)
	{
		for(int i = 0;i <(int)g_MagicExInfoList.size();i++)
		{
			if(g_MagicExInfoList[i]->wMagIdx == pcm->Def.wMagicId)
			{
				mex = g_MagicExInfoList[i];
				break;
			}
		}
		if(mex)
		{
			if(mex->NeedWrathPoint > 0 && g_SubAbil.WrathPoint < mex->NeedWrathPoint)
			{
				//怒值不够
				return;
			}
			if(GetTickCount() - mex->UpdateTime < mex->NeedTime)
			{
				//技能冷却
				return;
			}
		}
			if(pcm->Def.btEffectType == 0 && pcm->Def.wMagicId != 107 
				&& pcm->Def.wMagicId != 108)
			{
				if(pcm->Def.wMagicId == 26) //烈火
				{
					if(GetTickCount() - g_dwLatestFireHitTick < 10 * 1000) return;
				}
				if(pcm->Def.wMagicId == 27) //野蛮冲撞
				{
					if(GetTickCount() - g_dwLatestRushRushTick < 3 * 1000) return;
				}
				if(pcm->Def.wMagicId == 106 || pcm->Def.wMagicId == 102)
				{
					if(GetTickCount() - g_dwLatestPoxue)
					{
						g_dwLatestPoxue = GetTickCount() + (pcm->Level + 1) * 30 * 1000;
						g_MySelf->m_boMagicEff = true;
						g_MySelf->m_nMagicFrameTime = GetTickCount();
						g_MySelf->m_nMagicFrameTime = 0;
						g_MySelf->m_btDir = 4;
						g_MySelf->m_boWarMode = true;
						g_MySelf->m_nCurrentAction = 0;
						g_MySelf->m_dwWarModeTime = GetTickCount() - 3000;
						if(pcm->Def.wMagicId == 106)
						{
							g_MySelf->m_nMagicFrameStart = 60;
							PlaySound_(11062);
						}else
						{
							g_MySelf->m_nMagicFrameStart = 40;
							PlaySound_(11022);
						}
					}else
					{
						//过一会才能使用
					}
				}
				if(GetTickCount() - g_dwLatestSpellTick > g_dwSpellTime)
				{
					g_dwLatestSpellTick = GetTickCount();
					g_dwMagicDelayTime = 0;        //pcm.Def.DelayTime;
					SendSpellMsg(CM_SPELL, g_MySelf->m_btDir , 0, pcm->Def.wMagicId, 0);
				}
			}else
			{
				//控制客户端释放魔法的速度，以匹配服务端        if pcm.Def.wMagicId in [150] then begin
				if(pcm->Def.wMagicId == 150 && 
					GetTickCount() - g_dwLatestMagicTick < g_dwMagicTime)return;
				if(Shared.boAutoDF && g_MySelf->m_btJob == 2)
				{
					//AutoChgItemType(pcm);   //自动毒符
				}
				tdir = GetFlyDirection(myx, myy, tx, ty);
				//魔法锁定
				if(pcm->Def.wMagicId == 22 ||  //火墙
				   pcm->Def.wMagicId == 23 ||  //火龙气焰
				   pcm->Def.wMagicId == 33 || //冰咆哮
				   pcm->Def.wMagicId == 19 || //群隐
				   pcm->Def.wMagicId == 14 || //群防
				   pcm->Def.wMagicId == 16 || //困魔咒 大镇妖术
				   pcm->Def.wMagicId == 38 ||  //群体施毒术
				   pcm->Def.wMagicId == 29 )  //大治疗 群体治疗//以上这些技能，不能锁定
				{
					g_MagicTarget =nullptr;
				}else if( pcm->Def.wMagicId == 2) //小治疗术要能锁定自己
				{
					g_MagicLockActor = g_MySelf;
				}else
				{
					 //鼠标移动到了某个对象，重新锁定  
					if(TPlayScene::GetInstance()->IsValidActor(g_FocusCret))
					{
						if(g_FocusCret->m_boDeath ||
							(g_FocusCret->m_Abil.MaxHP > 0 && g_FocusCret->m_Abil.HP == 0))
						{
							if(g_nAutoPickUpX < 0)
							{
								g_nAutoPickUpX = g_FocusCret->m_nCurrX;
								g_nAutoPickupY = g_FocusCret->m_nCurrY;
								g_nAutoPickPos = 12;
								g_FocusCret = nullptr;
								return;
							}
							g_FocusCret = nullptr;
						}else
						{
							if(Shared.boAttackLock)
							{
								g_MagicLockActor = g_FocusCret;
							}else {
								g_MagicTarget = g_FocusCret;
								g_MagicLockActor = nullptr;
							}
						}
					}
					//已经锁定目标
					if(g_MagicLockActor && !g_MagicLockActor->m_boDeath)
					{
						g_MagicTarget = g_MagicLockActor;
					}
				}


				if(!TPlayScene::GetInstance()->IsValidActor(g_MagicTarget))g_MagicTarget = nullptr;
				if(!g_MagicTarget)
				{
					TPlayScene::GetInstance()->CXYfromMouseXY(tx,ty,targx,targy);
					targid = 0;
				}else 
				{
					targx = g_MagicTarget->m_nCurrX;
					targy = g_MagicTarget->m_nCurrY;
					targid = g_MagicTarget->m_nRecogId;
				}
				TUseMagicInfo* pmag;
				if(CanNextAction() && ServerAcceptNextAction())
				{
					pmag = new TUseMagicInfo();
					pmag->EffectNumber = pcm->Def.btEffect;
					pmag->MagicSerial = pcm->Def.wMagicId;
					pmag->ServerMagicCode = 0;
					g_dwMagicDelayTime = pcm->Def.dwDelayTime;
					g_dwLatestMagicTick = GetTickCount();
					if(pmag->MagicSerial == 31 || pmag->MagicSerial == 122) //魔法盾
					{
						targx = g_MySelf->m_nCurrX;
						targy = g_MySelf->m_nCurrY;
						targid = g_MySelf->m_nRecogId;
					}
					if(pmag->MagicSerial == 9 || pmag->MagicSerial == 53 ||
						pmag->MagicSerial == 73 || pmag->MagicSerial == 110) //地狱火
					{
						targx = g_MySelf->m_nCurrX;
						targy = g_MySelf->m_nCurrY;
						GetNextPosXY(tdir, targx, targy);
					}
					if((pmag->MagicSerial == 2 || pmag->MagicSerial == 120) &&
						!g_MagicTarget)//治愈术
					{
						targx = g_MySelf->m_nCurrX;
						targy = g_MySelf->m_nCurrY;
						targid = g_MySelf->m_nRecogId;
					}
					g_dwMagicPKDelayTime = 0;
					if(g_MagicTarget)
					{
						if(g_MagicTarget->m_btRace == 0)
						{
							g_dwMagicPKDelayTime = 300 + Random_Int(0,1100);
							tdir = GetFlyDirection(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY,g_MagicTarget->m_nCurrX,
								g_MagicTarget->m_nCurrY);
						}
					}
					if(pcm->Def.wMagicId == 56)
					{
						TPlayScene::GetInstance()->CXYfromMouseXY(tx,ty,targx,targy);
						g_MySelf->SendMsg(CM_SPELL, targx, targy, tdir, (int)&*pmag, 0, "", 0);
					}else
					{
						 g_MySelf->SendMsg(CM_SPELL, targx, targy, tdir, (int)&*pmag, targid, "", 0);
					}
					g_dwLatestSpellTick = GetTickCount();
					//由于网络延迟，可能造成有冷却时间的技能释放后没有获得下次冷却时
					//间数据的时候玩家再放技能，会卡住，所以这里加入两秒内不让再次客户端释放
					//也就是这种技能最低冷却时间是2秒
					if(mex)
					{
						mex->UpdateTime = GetTickCount();
						mex->NeedTime = 29000;
					}
				}
			}
		
	}

}

bool FrmMain::TargetInSwordLongAttackRange(int ndir)
{
	int nX,nY;
	TActor* Actor;
	GetFrontPosition(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, ndir, nX, nY);
	GetFrontPosition(nX, nY, ndir, nX, nY);
	if( abs(g_MySelf->m_nCurrX - nX) == 2 || abs(g_MySelf->m_nCurrY - nY) == 2) 
	{

		Actor =TPlayScene::GetInstance()->FindActorXY(nX, nY);
		if(Actor) 
		{
			if(!Actor->m_boDeath)
			{
				return true;
			}
		}

	}
	return false;
}


void FrmMain::MouseTimerTimer()
{
	if(!g_MySelf && !VDMap::GetInstance()->m_Loaded) return;
	//有目标对象，是人物 骑宠，查看人物信息
	if(g_TargetCret && g_TargetCret->m_boDeath)
	{
		//if(g_TargetCret->m_btRace == RCC_USERHUMAN)
		//{

		//}
		//if (g_TargetCret.m_btRace = RCC_USERHUMAN) then begin
		//	if not frmDlg.DTargerStateSpan.Visible then frmDlg.DTargerStateSpan.Visible := true;
		//FrmDlg.DTargerHorseStateSpan.Visible := false;
		//end else if (g_TargetCret.m_btRace = RC_HORSE) then begin
		//	if not frmDlg.DTargerHorseStateSpan.Visible then frmDlg.DTargerHorseStateSpan.Visible := true;
		//FrmDlg.DTargerStateSpan.Visible := false;
		//end else begin
		//	frmDlg.DTargerStateSpan.Visible := false;
		//frmDlg.DTargerHorseStateSpan.Visible := false;
		//end;
	}
	if(g_MagicLockActor)
	{
		if(g_MagicLockActor->m_boDeath || (g_MagicLockActor->m_Abil.MaxHP > 0 && 
			g_MagicLockActor->m_Abil.HP == 0))
		{
			if(g_nAutoPickUpX < 0)
			{
				g_nAutoPickUpX = g_MagicLockActor->m_nCurrX;
				g_nAutoPickupY = g_MagicLockActor->m_nCurrY;
				g_nAutoPickPos = 12;
			}
			g_MagicLockActor = nullptr;
		}
	}

	//自动吃药西，吃药
	AutoEat();
	//自动捡取
	if(Shared.boAutoPickUp || Shared.boAutoPickUpDrug || Shared.boAutoPickUpGold)
	{
		if(GetTickCount() - g_dwAutoPickupTick > g_dwAutoPickupTime )
		{
			g_dwAutoPickupTick = GetTickCount();
			AutoPickUpItem();
		}
		if(AutoPickUpItemEx())
		{
			return;
		}else
		{
			if(g_nAutoPickUpX >= 0)
			{
				g_nAutoPickUpX = -1;
				g_nAutoPickupY = -1;       
				g_nAutoPickPos = 0;
			}
		}

	}
	//GetCursorPos(pt);
	//SetCursorPos(pt.X, pt.Y);
	//有效锁定目标

	if(g_TargetCret)
	{
		if(ActionKey > 0) //快捷键
		{
			//	ProcessKeyMessages();
		}else
		{
			if( !g_TargetCret->m_boDeath && TPlayScene::GetInstance()->IsValidActor(g_TargetCret))
			{
				if (g_MySelf->m_btHorse == 0)/*{骑马状态不可以操作} */
				{
					if((g_TargetCret->m_btRace != RCC_USERHUMAN &&
						g_TargetCret->m_btRace != RCC_GUARD &&
						g_TargetCret->m_btRace != RC_HEROOBJECT &&
						g_TargetCret->m_btRace != RC_PLAYMOSTER &&
						g_TargetCret->m_btRace != RCC_MERCHANT &&
						g_TargetCret->m_sUserName.find('(') < 0)
						|| g_TargetCret->m_nNameColor == ENEMYCOLOR
						|| g_TargetCret->m_btRace != RCC_MERCHANT)
					{
						AttackTarget(g_TargetCret);
					}
				}
			}else
			{
				if( g_nAutoPickUpX < 0 )
				{
					g_nAutoPickUpX = g_TargetCret->m_nCurrX;
					g_nAutoPickupY = g_TargetCret->m_nCurrY; 
					g_nAutoPickPos = 12;
				}
				g_TargetCret = nullptr;
			}
		}
	}

	if(g_boAutoDig)
	{
		if( CanNextAction() && ServerAcceptNextAction() && CanNextHit())
		{
			g_MySelf->SendMsg(CM_HEAVYHIT, g_MySelf->m_nCurrX, g_MySelf->m_nCurrY,
				g_MySelf->m_btDir, 0, 0, "", 0);
			g_dwLatestHitTick = GetTickCount();
		}
	}

	if(g_MySelf && !g_MySelf->m_boDeath)
	{
		///自动和npc说话? 点npc
		TActor* target = nullptr;
		if(Shared.btLoad == 1)
		{
			for(int i = 0;TPlayScene::GetInstance()->m_ActorList.size();i++)
			{
				target = TPlayScene::GetInstance()->m_ActorList[i];
				if(target->m_sUserName == Shared.sChatName)
				{
					break;
				}
				
				CNetClient::GetInstance()->sendDefMsg(CM_CLICKNPC,target->m_nRecogId,0,0,0);
				Shared.btLoad = 0;
			}
		}
		//改变魔法快捷键
		if(Shared.btLoad == 3)
		{
			Shared.btLoad = 0;
			TMagicInfo* magic;
			TClientMagic* pm;
			for(int i = 0;i < 50;i++)
			{
				magic = &Shared.rMagic[i];
				if(strlen(magic->name) > 0)
				{
					pm = g_MagicList[i];
					pm->Key = magic->Biao;
					SendMagicKeyChange(pm->Def.wMagicId,pm->Key);
				}else
				{
					break;
				}
			}

		}

		AutoRecallBaobao();
		//自动喊话
		unsigned long nt =Shared.nAutoSayTime * 1000;
		if(Shared.boAutoSay && GetTickCount() - g_dwAutoSayTick > nt)
		{
			bool bo = false;
			std::string str = Shared.sSayString;
			std::string str1;
			int i = 0;
			while(true)
			{
				str = GetValidStr3Ex(str,str1,'/');
				if(str.length() > 0 && g_nAutosayIdx == i)
				{
					SendSay(str1);
					g_nAutosayIdx++;
					bo = true;
					g_dwAutoSayTick = GetTickCount();
					break;
				}
				i++;
				if(str.length() <= 0)break;
			}
			if(!bo)
			{
				g_nAutosayIdx = 0;
			}
		}
		if(Shared.boSendChat && strlen(Shared.sChatStr) > 0)
		{
			Shared.boSendChat = false;
			SendSay(Shared.sChatStr);
			Shared.bocloseform = true;
		}

		//持续魔法盾
	
		if( Shared.boMoDun && g_MySelf->m_btJob == 1
			&& (GetTickCount() - g_dwAutoShieldTick > 1000)
			&& ((g_MySelf->m_nState & 0x00100000) == 0))
		{
			unsigned long nt = g_dwSpellTime /*{500}*/ + g_dwMagicDelayTime;
			if(GetTickCount() - g_dwLatestSpellTick > nt)
			{
				g_dwAutoShieldTick = GetTickCount();
				TClientMagic* pm = FindMagic(31);
				if(pm)
				{
					if(pm->Def.wSpell + pm->Def.btDefSpell <= g_MySelf->m_Abil.MP 
						||pm->Def.btEffectType == 0)
					{
						UseMagic(g_nMouseX, g_nMouseY, pm);
						ActionKey = 0;
						g_nTargetX = -1;
					}
				}
			}
		}
		//自动隐身 道士
		if(Shared.boMoHiddent && g_MySelf->m_btJob == 2
			&& GetTickCount() - g_dwAutoHiddentTick > 1000
			&& (g_MySelf->m_nState & 0x800000) == 0) 
		{
			g_dwAutoHiddentTick = GetTickCount();
			TClientMagic* pm = FindMagic(18);
			int nx,ny;
			if( pm )
			{
				if(pm->Def.wSpell + pm->Def.btDefSpell <= g_MySelf->m_Abil.MP
					|| pm->Def.btEffectType == 0)
				{
					TPlayScene::GetInstance()->ScreenXYfromMCXY(g_MySelf->m_nCurrX, 
						g_MySelf->m_nCurrY, nx,ny);
					UseMagic(nx,ny, pm);
					ActionKey = 0;
					g_nTargetX = -1;
				}
			}
		}
		if(Shared.boWarrC)
		{
			TClientMagic* pm;
			if(!g_boWarrPx && Shared.boWarrPx)
			{
				pm = FindMagic(106);
				if(pm)
				{
					UseMagic(g_nMouseX, g_nMouseY, pm);
					ActionKey = 0;
					g_nTargetX = -1;
					g_boWarrPx = true;
				}
			}
			if(!g_boWarrTbs && Shared.boWarrTbs)
			{
				pm = FindMagic(106);
				if(pm)
				{
					UseMagic(g_nMouseX, g_nMouseY, pm);
					ActionKey = 0;
					g_nTargetX = -1;
					g_boWarrTbs = true;
				}
			}
			if(g_MySelf->m_btHorse == 0) TGuaJiHelper::GetInstance()->Run();
		
		}
	}
}

void FrmMain::AutoEat()
{
	//待定
}

void FrmMain::AutoPickUpItem()
{
	if(!g_MySelf)return;
	if(CheckBagFulll() && !Shared.boAutoPickUpGold) //包裹满了还得捡钱
	{
		g_nTargetX = -1;
	}
	bool bFind = false;
	TDropItem* pDropItem;
	if(CanNextAction() && ServerAcceptNextAction())
	{
		for(int i = 0;i < (int)g_DropedItemList.size();i++)
		{
			pDropItem = g_DropedItemList[i];
			//if HaveKey(pDropItem->sName, g_sNotPickItems) continue;//不捡取的物品
			if(pDropItem->x == g_MySelf->m_nCurrX && pDropItem->y == g_MySelf->m_nCurrY)
			{
				if((int)pDropItem->sName.find(g_sAutoEatHPName) >= 0 ||
					(int)pDropItem->sName.find(g_sAutoEatMPName) >= 0 ||
					(int)pDropItem->sName.find(g_sAutoEatFastName) >= 0 ||
					(int)pDropItem->sName.find(g_sAutoUseJuanName) >= 0 )
				{
					if(Shared.boAutoPickUpDrug && !CheckBagFulll())
					{
						bFind = true;
						break;
					}
				}else if((int)pDropItem->sName.find(g_sGoldName) >= 0 ||
					(int)pDropItem->sName.find(g_sGamePointName) >= 0)
				{
					if(Shared.boAutoPickUpGold)
					{
						bFind = true;
						break;
					}
				}else
				{
					if(Shared.boAutoPickUp && !CheckBagFulll())
					{
						bFind = true;
						break;
					}
				}
	
			}
		}
		if(bFind)
		{
			if(g_nAutoPickPos > 0 ) g_nAutoPickPos--;
			CNetClient::GetInstance()->GetSendMsg()->SendPickup(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY);
		}
	}

}
bool FrmMain::AutoPickUpItemEx()
{
	//待定
	return false;
}

void FrmMain::SendMagicKeyChange(int magid,unsigned char keych)
{
	//待定
}

void FrmMain::AutoRecallBaobao()
{
	//待定
}

void FrmMain::SendSay(std::string str)
{
	//待定
}

void FrmMain::ProcessTimer()
{

	if(GetTickCount() - m_MouseTimer > 50)
	{
		MouseTimerTimer();
		m_MouseTimer = GetTickCount();
	}
	if(GetTickCount() - m_MinTimer > 1000)
	{
		m_MinTimer = GetTickCount();
		MinTimerTimer();
	}

	if(m_bAutoTimer)
	{
		if(GetTickCount() - m_AutoTimer > 20)
		{
			AutoTimer();
		}
	}
}


void FrmMain::ClientGetHealthSpellChanged(tagDefaultMessage* msg)
{
	TActor* actor = TPlayScene::GetInstance()->FindActor(msg->Recog);
	int num;
	if(actor)
	{
		if(actor->m_Abil.HP > 0)
		{
			num = msg->Param - actor->m_Abil.HP;
			ShowAddBlood(actor,num);
		}
		actor->m_Abil.HP = msg->Param;
		actor->m_Abil.MP = msg->Tag;
		actor->m_Abil.MaxHP = msg->Serise;
	}

}
void FrmMain::ShowAddBlood(TActor* actor,int Num)
{
	if(Num == 0)return;
	if(actor->m_btRace != 0 && Num > 0)return;
	actor->IsAddBlood = true;
	actor->AddBloodFram = 1;
	actor->AddBloodNum = Num;
	actor->AddBloodTime = GetTickCount();
	actor->AddBloodStartTime = GetTickCount();
}

void FrmMain::ClientGetSTRUCK(tagDefaultMessage* msg,std::string body)
{
	TMessageBodyWL wl;
	fnDecode6BitBufA((char*)body.c_str(),(char*)&wl,sizeof(TMessageBodyWL));
	TActor* actor = TPlayScene::GetInstance()->FindActor(msg->Recog);
	if(actor)
	{
		if(actor == g_MySelf)
		{
			if(g_MySelf->m_nNameColor == 249)
			{
				g_dwLatestStruckTick = GetTickCount();
			}
		}else
		{
			if(actor->CanCancelAction())
			{
				actor->CancelAction();
			}
		}
		int num = 0;
		if(actor->m_Abil.HP > 0)
		{
			num = msg->Param - actor->m_Abil.HP;
			ShowAddBlood(actor,num);
			actor->m_Abil.HP = msg->Param;
			actor->m_Abil.MaxHP = msg->Tag;
		}
	}
	

}

void FrmMain::ClientGetActorHP(tagDefaultMessage* msg,std::string body)
{
	THumBaseInfo info;
	TActor* actor = TPlayScene::GetInstance()->FindActor(msg->Recog);
	if(actor)
	{
		fnDecode6BitBufA((char*)body.c_str(),(char*)&info,sizeof(THumBaseInfo));
		actor->m_Abil.MaxHP = msg->Param;
		actor->m_Abil.HP = msg->Tag;
		actor->m_Abil.Level = msg->Serise;
		actor->m_Abil.MaxMP = info.MaxMP;
		actor->m_Abil.MP = info.MP;
	}
}

bool FrmMain::LoadMapGates()
{
	const std::string sFileName = "data/mr_1.mpp";
	std::string filepath = cocos2d::FileUtils::getInstance()->fullPathForFilename(sFileName);
	ssize_t nLen = 0;
	int len;
	
	cocos2d::Data fdata = cocos2d::CCFileUtils::getInstance()->getDataFromFile(filepath);
	nLen = fdata.getSize();
	unsigned char* data = fdata.getBytes();
//	unsigned char* data = cocos2d::CCFileUtils::getInstance()->getFileData(filepath.c_str(),"rb",&nLen);
	unsigned char* pData;
	CFileStream stream;
	std::string tmp;
	std::string v;
	std::string smap;
	std::string dmap;
	std::string dtitle;
	int dx,dy,sx,sy;
	TMapGateInfo* itm;
	std::map<std::string,TLocalMapInfo*>::iterator n;
	std::vector<TMapGateInfo*> tmpList;
	if(data)
	{
		pData = UnCompression(data,nLen,len);
		if(!pData)
		{
			CCLOG("loadmapgates error! code: 1 %s",filepath.c_str());
			return false;
		}
		ClearMapGate();
		stream.Init(pData,len);
		tmpList.clear();
		std::string str = stream.readString(len);
		while(str.length() > 0)
		{
			str = GetValidStr3Ex(str,tmp,'/');
			if(tmp.length() <= 0)break;
			tmp = GetValidStr3Ex(tmp,v,',');
			smap = v;
			tmp = GetValidStr3Ex(tmp, v, ',');
			sx = atoi(v.c_str());
			tmp = GetValidStr3Ex(tmp, v, ',');
			sy = atoi(v.c_str());
			tmp = GetValidStr3Ex(tmp, v, ',');
			dmap = v;
			tmp = GetValidStr3Ex(tmp, v, ',');
			dtitle = v;
			tmp = GetValidStr3Ex(tmp, v, ',');
			dx = atoi(v.c_str());
			tmp = GetValidStr3Ex(tmp, v, ',');
			dy = atoi(v.c_str());
			itm = new TMapGateInfo();
			itm->SMapName = smap;
			itm->SX = sx;
			itm->SY = sy;
			itm->DMapName = dmap;
			itm->DMapTitle = dtitle;
			itm->DX = dx;
			itm->DY = dy;
			//找到对应的地图信息
			TLocalMapInfo* MapInfo = nullptr;
			n = g_alllocalmap.find(smap);
			if(n != g_alllocalmap.end())
			{
				MapInfo = n->second;
			}
			//没找到，创建
			if(!MapInfo)
			{
				MapInfo = new TLocalMapInfo();
				MapInfo->sMapName =smap;
				g_alllocalmap[smap] = MapInfo;
			}
			//将地图连接点添加到地图信息
			itm->SMapInfo = MapInfo;
			itm->fromGate = nullptr;
			MapInfo->Gates.push_back(itm);

			tmpList.push_back(itm);
		}

	}else
	{
		CCLOG("loadmapgates error!code: 2 %s",filepath.c_str());
		return false;
	}
	//更新目标地图信息
	for(int i = 0;i < (int)tmpList.size();i++)
	{
		itm = tmpList[i];
		itm->DMapInfo = nullptr;
		n = g_alllocalmap.find(itm->DMapName);
		if(n != g_alllocalmap.end())
		{
			itm->DMapInfo = n->second;
		}
	}
	//if(data)
	//{
	//	delete []data;
	//}
	if(pData)
	{
		delete [] pData;
	} 
	tmpList.clear();
	return true;
}

void FrmMain::ClearMapGate()
{
	std::map<std::string,TLocalMapInfo*>::iterator it;
	for(it = g_alllocalmap.begin();it != g_alllocalmap.end();it++)
	{
		TLocalMapInfo* info = it->second;
		delete info;
	}
	g_alllocalmap.clear();
}

void FrmMain::reCurMapGate()
{
	g_CurLocalMap = nullptr;
	std::map<std::string,TLocalMapInfo*>::iterator it;
	std::string sMapName = VDMap::GetInstance()->m_sMapName;
	it =g_alllocalmap.find(sMapName);
	if(it != g_alllocalmap.end())
	{
		g_CurLocalMap = it->second;
	}
}

void FrmMain::MinTimerTimer()
{
	if(!g_MySelf && !VDMap::GetInstance()->m_Loaded)
	{
		return;
	}
	//组队人物状态  -。- 待定
	/*TActor* actor;
	for(int i = 0;i < TPlayScene::GetInstance->m_ActorList.size();i++)
	{
	actor = TPlayScene::GetInstance()->m_ActorList[i];
	if(IsGroupMember(actor->m_sUserName))
	{
	actor->m_boGrouped = true;
	}else 
	{
	actor->m_boGrouped = false;
	}
	}*/
	TActor* actor;
	if(g_FreeActorList.size() > 0)
	{
		/*std::vector<TActor*> templist;
		templist.clear();*/
		for(int i = 0;i < (int)g_FreeActorList.size();i++)
		{
			actor = g_FreeActorList[i];
			delete actor;
			//if(GetTickCount() - actor->m_dwDeleteTime > 30000)
			//{
			//	
			//	
			//}
		}
		g_FreeActorList.clear();
	}


}


void FrmMain::SetMove(bool bMove,int x,int y)
{
	m_bMove = bMove;
	m_MovePos.x = x;
	m_MovePos.y = y;
}

void FrmMain::UseMagicSpell(int who,int effnum,int targetx,int targety,int magic_id)
{
	TActor* actor = TPlayScene::GetInstance()->FindActor(who);
	if(actor)
	{
		int adir = GetFlyDirection(actor->m_nCurrX, actor->m_nCurrY, targetx, targety);
		TUseMagicInfo* UseMagic = new TUseMagicInfo;
		UseMagic->reset();
		UseMagic->EffectNumber = effnum;    //magnum;
		UseMagic->ServerMagicCode = 0;      //烙矫
		UseMagic->MagicSerial = magic_id;
		actor->SendMsg(SM_SPELL, 0, 0, adir, (int)UseMagic, 0, "", 0);
		//g_nSpellCount++;
	}else
	{
		//g_nSpellFailCount++;
	}
}

void FrmMain::ClientGetAdjustBonus(tagDefaultMessage* msg,std::string body)
{
	g_nBonusPoint = msg->Recog;
	g_nBonusPointChg = g_nBonusPoint;
	g_ReNewLevel = LOWORD_(msg->Param);
	g_ReNewCount = HIWORD_(msg->Param);
	g_RenewNeedGold = LOWORD_(msg->Tag);
	g_ClearBonusPointNeedGameGold = HIWORD_(msg->Tag);
	g_addRenewCountNeedGameGold = LOWORD_(msg->Serise);

	std::string str1;	
	std::string str2;
	std::string str3;
	std::string body_ = GetValidStr3Ex(body, str1, '/');
	str3 = GetValidStr3Ex(body_, str2, '/');

	fnDecode6BitBufA((char*)str1.c_str(),(char*)&g_BonusAbil,sizeof(TNakedAbility));
	fnDecode6BitBufA((char*)str2.c_str(),(char*)&g_BonusTick,sizeof(TNakedAbility));
	g_RenewInfo.reset();
	if(str3.length() > 0)
	{
		fnDecode6BitBufA((char*)str3.c_str(),(char*)&g_RenewInfo,sizeof(TReNewInfo));
	}

}

void FrmMain::Client_ServerConfig(tagDefaultMessage* msg)
{
	g_boCanRunHuman = LOBYTE_(LOWORD_(msg->Recog)) == 1;
	g_boCanRunMon = HIBYTE_(LOWORD_(msg->Recog)) == 1;
	g_boCanRunNpc = LOBYTE_(HIWORD_(msg->Recog)) == 1;
	g_boCanRunAllInWarZone = HIBYTE_(HIWORD_(msg->Recog)) == 1;
}

void FrmMain::Client_MapDescription(tagDefaultMessage* msg,std::string body)
{
	std::string sbody;
	std::string sTitle;
	std::string sMapMusic;
	std::string sAnonymous;
	//13为 \r

	sbody = GetValidStr3Ex(body,sTitle,13);
	
	sbody = GetValidStr3Ex(sbody, sMapMusic, 13);
	sbody = GetValidStr3Ex(sbody, sAnonymous,13);
	if (sAnonymous == "1" )
	{
		g_boMapAnonymous = true;
	}else 
	{
		g_boMapAnonymous = false;
	}
	g_sMapTitle = sTitle;
	g_nMapMusic = msg->Recog;
	
	g_nPlayMusicCount = atoi(sbody.c_str());
	if ((msg->Param & 0x80) > 0 ) 
	{
		g_boMineMap = true;
	}
	std::string soldmusic = g_sMapMusic;
	g_sMapMusic = sMapMusic;
	PlayMapMusic(soldmusic,g_sMapMusic);
}

void FrmMain::Client_GameGoldName(tagDefaultMessage* msg,std::string body)
{
	if(body.length() > 0)
	{
		std::string sBody;
		std::string sData;
		sBody = GetValidStr3Ex(body,sData,13);
		g_sGameGoldName = sData;
		g_sGamePointName = sBody;
	}
	g_MySelf->m_nGameGold =msg->Recog;
	g_MySelf->m_nGamePoint = MAKELONG_(msg->Param,msg->Tag);
}

void FrmMain::Client_MagicFire(int who,int efftype,int effnum,int targetx,int targety,int target)
{
	TActor* actor = TPlayScene::GetInstance()->FindActor(who);
	int sound = 0;
	if(actor)
	{
		actor->SendMsg(SM_MAGICFIRE,target,efftype,effnum,targetx,targety,"",sound);
	}
	g_MagicTarget = nullptr;
}

void FrmMain::Client_AddMagic(std::string body)
{
	TClientMagic* pcm = new TClientMagic;
	fnDecode6BitBufA((char*)body.c_str(),(char*)pcm,sizeof(TClientMagic));
	//delphi string数据类型前面多了个字节
	unsigned char nNameLen = pcm->Def.sMagicName[0];
	memcpy(&pcm->Def.sMagicName,&pcm->Def.sMagicName[1],nNameLen);
	pcm->Def.sMagicName[nNameLen] = 0;
	
	//memcpy(pcm->Def.sMagicName,&pcm->Def.sMagicName[1],sizeof(pcm->Def.sMagicName) - 1);
	nNameLen = pcm->Def.sDescr[0];
	memcpy(&pcm->Def.sDescr,&pcm->Def.sDescr[1],nNameLen);
	pcm->Def.sDescr[nNameLen] = 0;
	//memcpy(pcm->Def.sDescr,&pcm->Def.sDescr[1],sizeof(pcm->Def.sDescr) - 1);
	g_MagicList.push_back(pcm);
	TGuaJiHelper::GetInstance()->SelectMagicLise();

}

void FrmMain::Client_SendMyMagic(std::string body)
{
	//清空技能
	TClientMagic* pcm;
	while(true)
	{
		if(g_MagicList.size() <= 0)break;
		pcm = g_MagicList[0];
		g_MagicList.erase(g_MagicList.begin());
		delete pcm;
	}

	std::string sBody = body;
	std::string data;
	while(true)
	{
		sBody = GetValidStr3Ex(sBody,data,'/');
		if(data.length() > 0)
		{
			pcm = new TClientMagic;
			fnDecode6BitBufA((char*)data.c_str(),(char*)pcm,sizeof(TClientMagic));
			//delphi string数据类型前面多了个字节
			//memcpy(pcm->Def.sMagicName,&pcm->Def.sMagicName[1],sizeof(pcm->Def.sMagicName) - 1);
			//memcpy(pcm->Def.sDescr,&pcm->Def.sDescr[1],sizeof(pcm->Def.sDescr) - 1);
			unsigned char nNameLen = pcm->Def.sMagicName[0];
			memcpy(&pcm->Def.sMagicName,&pcm->Def.sMagicName[1],nNameLen);
			pcm->Def.sMagicName[nNameLen] = 0;

			//memcpy(pcm->Def.sMagicName,&pcm->Def.sMagicName[1],sizeof(pcm->Def.sMagicName) - 1);
			nNameLen = pcm->Def.sDescr[0];
			memcpy(&pcm->Def.sDescr,&pcm->Def.sDescr[1],nNameLen);
			pcm->Def.sDescr[nNameLen] = 0;
			if(strlen(pcm->Def.sMagicName) > 0)
			{
				g_MagicList.push_back(pcm);
			}else delete pcm;
		}else break;
	}
	TGuaJiHelper::GetInstance()->SelectMagicLise();
}

void FrmMain::Client_ShowEvent(tagDefaultMessage* msg,std::string body)
{
	TShortMessage sMsg;
	TEvent* evn;
	fnDecode6BitBufA((char*)body.c_str(),(char*)&sMsg,sizeof(TShortMessage));
	if(msg->Param >= 7 && msg->Param <= 14)
	{
		//烟花
	}else
	{
		//火墙
		evn = new TClEvent(msg->Recog,LOWORD_(msg->Tag),LOWORD_(msg->Serise),msg->Param);
	}
	evn->m_nDir = 0;
	evn->m_nEventParam = sMsg.Ident;
	evn->m_btColor = sMsg.wMsg;
	TClEventManager::GetInstance()->AddEvent(evn);
}

void FrmMain::Client_MerchantSay(tagDefaultMessage* msg,std::string body)
{

	int merchant = msg->Recog;
	int face =msg->Param;
	std::string saying = body;
	if(g_nCurMerchant != merchant)
	{
		g_nCurMerchant = merchant;
	}
	//g_nMDlgX := g_MySelf.m_nCurrX;
	//g_nMDlgY := g_MySelf.m_nCurrY;
	//FrmDlg.ResetMenuDlg;
	//If g_nCurMerchant <> merchant Then Begin
	//g_nCurMerchant := merchant;
	//FrmDlg.CloseMDlg;
	//End;
	//   ShowMessage(saying);
	std::string npcname;

	saying = GetValidStr3Ex(saying, npcname, '/');
	std::string cmd = StringToLower(npcname.c_str());
	if(cmd == "vip")
	{

	}else if(cmd == "activities")
	{

	}else if(cmd == "packs")
	{

	}
	else
	{
		ShowDialog(DIALOG_TYPE::NPC,npcname,saying);
	}
	//if(npcname == "QManage")return; //暂时先屏蔽
	//VD_UI::CNpcDialog::GetInstance()->Show(npcname,saying,TPlayScene::GetInstance()->GetUILayer());
	
	//if LowerCase(npcname) = 'vip' then begin
	//	FrmDlg.DVIPTextBlock.Text := saying;
	//end else if LowerCase(npcname) = 'activities' then  begin
	//	frmdlg.ShowActivitiesDlg(face, npcname, saying);
	//end else if LowerCase(npcname) = 'packs' then begin
	//	FrmDlg.ShowGifiBagDlg(face,npcname,saying);
	//end else begin
	//	FrmDlg.ShowMDlg(face, npcname, saying);
	//end;
}

void FrmMain::Client_QueryChr(tagDefaultMessage* msg,std::string body)
{
	TSelectChrScreen::GetInstance()->ClearChr();
	int curidx = msg->Serise;
	TSelectChrScreen::GetInstance()->SelectedChrIndex = curidx;
	std::string uname;
	std::string sjob;
	std::string slevel;
	std::string ssex;
	std::string str =body;
	int select = 0;
	while(str.length() > 0)
	{
		str =GetValidStr3Ex(str,uname,'/');
		str =GetValidStr3Ex(str,sjob,'/');
		str =GetValidStr3Ex(str,slevel,'/');
		str =GetValidStr3Ex(str,ssex,'/');
		select = 0;
		if(uname.length() > 0  && slevel.length() > 0 && ssex.length() > 0)
		{
			int njob = atoi(sjob.c_str());
			int nhair = 0;
			int nLevel = atoi(slevel.c_str());
			int nSex = atoi(ssex.c_str());
			TSelectChrScreen::GetInstance()->AddChr(uname,njob,nhair,nLevel,nSex);
		}
	}
	//没有角色- 进入创建角色场景
	if(TSelectChrScreen::GetInstance()->GetChrList() <= 0)
	{
		TDScreen::GetInstance()->ChangeScene(stNewChr);
	}else
	{
		//这里先用笨方法代替- 直接重新切换场景
		if(TDScreen::GetInstance()->GetCurentScene() == stSelectChr)
		{
			TDScreen::GetInstance()->ChangeScene(stSelectChr);
			//TSelectChrScreen::GetInstance()->UpdateChrList();
		}else
		{
			TDScreen::GetInstance()->ChangeScene(stSelectChr);
		}
		
	}
	//需要二级密码,待定
}


void FrmMain::Client_ItemShow(tagDefaultMessage* msg,std::string body)
{
	int itemid = msg->Recog;
	int x = msg->Param;
	int y =msg->Tag;
	int looks = msg->Serise;
	std::string itmname = body;
	TDropItem* pItem;
	for(int i = 0;i < (int)g_DropedItemList.size();i++)
	{
		pItem = g_DropedItemList[i];
		if(pItem->id == itemid)
		{
			return;
		}
	}
	pItem = new TDropItem();
	pItem->id = itemid;
	pItem->x = x;
	pItem->y = y;
	pItem->Looks = HIWORD_(looks);
	pItem->sName = itmname;
	pItem->FlashTime = GetTickCount() - (unsigned long)Random_Int(1,3000);
	pItem->boFlash = false;
	pItem->stdmode = LOWORD_(looks);
	g_DropedItemList.push_back(pItem);
}

void FrmMain::Client_ItemHide(tagDefaultMessage* msg,std::string body)
{
	int itemid = msg->Recog;
	int x = msg->Param;
	int y = msg->Tag;
	TDropItem* pItem;
	for(int i = 0;i < (int)g_DropedItemList.size();i++)
	{
		pItem = g_DropedItemList[i];
		if(pItem->id == itemid)
		{
			g_DropedItemList.erase(g_DropedItemList.begin() + i);
			delete pItem;
			break;
		}
	}
}

void FrmMain::Client_BagItems(tagDefaultMessage* msg,std::string body)
{
	int itemCount = msg->Serise;
	TStdItem* pStditem;
	TUserItem userItem;
	TClientItem cItem;
	memset(&g_ItemArr[0],0,sizeof(g_ItemArr));
	if(itemCount > 0)
	{
		int nLen = itemCount * sizeof(TUserItem);
		char* szDef = new char[nLen];
		memset(szDef,0,sizeof(szDef));
		fnDecode6BitBufA((char*)body.c_str(),szDef,nLen,true);
		for(int i = 0;i < itemCount; i++)
		{
			memcpy(&userItem,&szDef[i * sizeof(TUserItem)],sizeof(TUserItem));
			cItem.reset();
			//取基本物品数据，并将基本物品数据附加值加入
			pStditem = GetStdItemInfo(userItem.wIndex);
			if(pStditem)
			{
				memcpy(&cItem.s,pStditem,sizeof(TStdItem));
				GetItemAddValueFun(&userItem,&cItem.s); //额外的附加属性
				if(pStditem->StdMode == 50)
				{
					char spr[128];sprintf(spr,"%s#%d",cItem.s.Name,userItem.Dura);
					strcpy((char*)cItem.s.Name,spr);
				}
				cItem.MakeIndex = userItem.MakeIndex;
				cItem.Dura = userItem.Dura;
				cItem.DuraMax = userItem.DuraMax;
				memcpy(&cItem.btValue[0],&userItem.btValue[0],sizeof(cItem.btValue));
				AddItemBag(cItem); //加入到背包

			}
		}
		if(szDef) delete []szDef;
		ArrangeItemBag();//整理包裹
	}

}

void FrmMain::Client_SendUseItems(tagDefaultMessage* msg,std::string body)
{
	memset(&g_UseItems[0],0,sizeof(g_UseItems));
	int n = msg->Param;
	if(n > 0)
	{
		TClientItem cu;
		int idx;
		char* pDes = new char[(sizeof(TClientItem) + 1) * n];
		char* p = pDes;
		fnDecode6BitBufA((char*)body.c_str(),pDes,body.length(),true);
		//FILE* f = fopen("c:\\1.dat","wb");
		//fwrite(pDes,(sizeof(TClientItem) + 1) * n,1,f);
		//fclose(f);
		for(int i = 0;i < n;i++)
		{
			idx = (int)*p;
			p++;
			if(idx >= 0 && idx < MAXEQUIP)
			{
				memcpy(&g_UseItems[idx],p,sizeof(TClientItem));
				//---------------
				//delphi string数据类型，前一个字节是字符串长度
				unsigned char nNameLen = g_UseItems[idx].s.Name[0];
				memcpy(&g_UseItems[idx].s.Name,&g_UseItems[idx].s.Name[1],nNameLen);
				g_UseItems[idx].s.Name[nNameLen] = 0;
				p += sizeof(TClientItem);
				if(i == U_DRESS)
				{
					g_MySelf->m_btDressType = g_UseItems[idx].s.Source;
				}
			}
		}
		if(pDes) delete []pDes;
	}
}

void FrmMain::InitDialog()
{
	CNpcDialog* npcdialog =  new CNpcDialog();
	npcdialog->SetRect(150,50,304,404);
	m_ListDialog[DIALOG_TYPE::NPC] = (VD_UI::CBaseDialog*)npcdialog;

	CMyStatePan* mystate = new CMyStatePan();
	mystate->SetRect(5,5,250,107);
	m_ListDialog[DIALOG_TYPE::MYSTATE] = (VD_UI::CBaseDialog*)mystate;

	CShortcutsDialog* shortcuts = new CShortcutsDialog();
	m_ListDialog[DIALOG_TYPE::SHORTCUTS] = (VD_UI::CBaseDialog*)shortcuts;

	CRoleStateDialog* rolestatedialog = new CRoleStateDialog();
	rolestatedialog->SetRect(50,50,413,414);
	m_ListDialog[DIALOG_TYPE::ROLESTATE] = (VD_UI::CBaseDialog*)rolestatedialog;

	CBagDialog* bagdialog = new CBagDialog();
	bagdialog->SetRect(SCREENWIDTH - 400,30,346,441);
	m_ListDialog[DIALOG_TYPE::BAGITEM] = (VD_UI::CBaseDialog*)bagdialog;

	CHitDialog* hitdialog = new CHitDialog();
	hitdialog->SetRect(200,30,346,440);
	m_ListDialog[DIALOG_TYPE::HIT] = (VD_UI::CBaseDialog*)hitdialog;

	CMagicDialog* magicdialog = new CMagicDialog();
	magicdialog->SetRect(SCREENWIDTH - 334, 30, 324, 392);
	m_ListDialog[DIALOG_TYPE::MAGIC] = (VD_UI::CBaseDialog*)magicdialog;

	CMapMiniTitle* mapminititle = new CMapMiniTitle();
	mapminititle->SetRect(SCREENWIDTH - 178,0,178,26);
	m_ListDialog[DIALOG_TYPE::MAPMINITITLE] = (VD_UI::CBaseDialog*)mapminititle;

	CMiniTaskPan* minitaskpan = new CMiniTaskPan();
	minitaskpan->SetRect(SCREENWIDTH - 162,100,154,20);
	m_ListDialog[DIALOG_TYPE::MINITASK] = (VD_UI::CBagDialog*)minitaskpan;
}

bool FrmMain::IsDialogVisible(DIALOG_TYPE nType)
{
	std::map<int,VD_UI::CBaseDialog*>::iterator it = m_ListDialog.find(nType);
	if(it != m_ListDialog.end())
	{
		return it->second->IsVisible();
	}
	return false;
}

VD_UI::CBaseDialog* FrmMain::GetDialog(DIALOG_TYPE nType)
{
	std::map<int,VD_UI::CBaseDialog*>::iterator it = m_ListDialog.find(nType);
	if(it != m_ListDialog.end())
	{
		return it->second;
	}
	return nullptr;
}
void FrmMain::ShowDialog(DIALOG_TYPE nType,std::string param,std::string param2)
{
	std::map<int,VD_UI::CBaseDialog*>::iterator it = m_ListDialog.find(nType);
	if(it == m_ListDialog.end())
	{
		return;
	}
	
	//要隐藏的面板
	
	static DIALOG_TYPE HideDialog[]={DIALOG_TYPE::NPC,DIALOG_TYPE::ROLESTATE,
		DIALOG_TYPE::BAGITEM,DIALOG_TYPE::HIT,DIALOG_TYPE::MAGIC};

		for(int i = 0;i < sizeof(HideDialog) / sizeof(int);i++)
		{
			this->HideDialog(HideDialog[i]);
		}

	cocos2d::Layer* ui_layer = TPlayScene::GetInstance()->GetUILayer();
	switch(nType)
	{
	case DIALOG_TYPE::NPC:
		{
			((CNpcDialog*)it->second)->Show(param,param2,ui_layer);
			break;
		}
	case DIALOG_TYPE::MYSTATE:
		{
			it->second->Show(ui_layer);
			break;
		}
	case DIALOG_TYPE::ROLESTATE:
		{
			it->second->Show(ui_layer);
			break;
		}
	case DIALOG_TYPE::BAGITEM:
	case DIALOG_TYPE::MAGIC:
		{
			it->second->Show(ui_layer);
			break;
		}
	case DIALOG_TYPE::HIT:
		{
			//((CHitDialog*)it->second)->ShowHint(ui_layer,0,0,param);
			break;
		}
	default:
		{
			it->second->Show(ui_layer);
			break;
		}
	
	}
}
void FrmMain::HideDialog(DIALOG_TYPE nType)
{
	std::map<int,VD_UI::CBaseDialog*>::iterator it = m_ListDialog.find(nType);
	if(it == m_ListDialog.end())
	{
		return;
	}

	switch(nType)
	{
	case DIALOG_TYPE::NPC:
		{
			((CNpcDialog*)it->second)->Hide();
			break;
		}
	case DIALOG_TYPE::ROLESTATE:
		{
			it->second->Hide();
			break;
		}
	case DIALOG_TYPE::BAGITEM:
		{
			it->second->Hide();
			break;
		}
	case DIALOG_TYPE::HIT:
		{
			it->second->Hide();
			break;
		}
		default:
			{
				it->second->Hide();
			}
	}
}
bool FrmMain::CheckDialogClickBegan(cocos2d::Vec2 pos)
{
	std::map<int,VD_UI::CBaseDialog*>::iterator it;
	cocos2d::Rect rec = cocos2d::Rect(pos.x,pos.y,1,1);
	
	for(it = m_ListDialog.begin();it != m_ListDialog.end();it++)
	{
		if(!it->second->IsVisible())continue;
		rec  = it->second->GetRect();
		if(rec.containsPoint(pos))
		{
			return true;
		}
	}

	//判断是否单击任务栏--
	CMiniTaskPan* pan = (CMiniTaskPan*)GetDialog(DIALOG_TYPE::MINITASK);
	if(pan->DMiniTaskPanelClickFun(pos))
	{
		return true;
	}
	return false;
}

void FrmMain::ProcessDialogUI()
{
	std::map<int,VD_UI::CBaseDialog*>::iterator it;
	bool bVisible;
	for(it = m_ListDialog.begin();it != m_ListDialog.end();it++)
	{
		bVisible = it->second->IsVisible();
		if(bVisible)
		{
			it->second->Render();
		}
		
	}
}
bool FrmMain::ClickDialog(cocos2d::Vec2 pos)
{
	std::map<int,VD_UI::CBaseDialog*>::iterator it;
	cocos2d::Rect rec = cocos2d::Rect(pos.x,pos.y,1,1);
	bool bVisible;
	for(it = m_ListDialog.begin();it != m_ListDialog.end();it++)
	{
		bVisible = it->second->IsVisible();
		if(!bVisible)continue;
		rec  = it->second->GetRect();
		if(rec.containsPoint(pos))
		{
			it->second->MouseDown(pos);
			/*	switch(it->first)
			{
			case DIALOG_TYPE::NPC:
			{
			((CNpcDialog*)it->second)->MouseDown(pos);
			}
			}*/
			return true;
		}
	}
	return false;
}

void FrmMain::Client_WalkTo(tagDefaultMessage* msg,std::string body)
{
	int nx,ny;
	std::string str = body;
	int boWalk = msg->Tag;
	nx = msg->Recog;
	ny = msg->Param;
	std::string sMap;
	std::string snpc = GetValidStr3Ex(str,sMap,'/');
	if(snpc.length() <= 0) snpc = "*";
	bool bWalk = boWalk == 1;
	BeginAutoRun(sMap, nx, ny, snpc,false,0,bWalk);

}

void FrmMain::BeginAutoRun(std::string sDescMap,int nx,int ny,std::string sTargetname/* ="" */, 
						   bool bKillMon /* = false */,int nTargetXYD /* = 0 */,bool bWalk /* = false */)
{
	TGuaJiHelper::GetInstance()->Started(false);
	StopAutoRun();
	g_AutoTargetMap = sDescMap;
	g_AutoTargetdx = nx;
	g_AutoTargetdy = ny;
	g_AutoTargetx = -1;
	g_AutoTargety = -1;
	g_AutoCurMap = "";
	g_AutoTargetXYD = nTargetXYD;
	g_AutobWalk =  bWalk;
		//自动捡东西停下来
	g_nAutoPickUpX = -1;
	g_nAutoPickupY = -1;
	g_nAutoPickPos = 0;

	FindMapPath(VDMap::GetInstance()->m_sMapName, sDescMap);
	g_TargetCret = nullptr;//停止当前锁定打怪
	
	if(bKillMon)
	{
		g_AutoKillMonName = sTargetname;
		g_AutoRunTargetNCPName = "";
	}else
	{
		g_AutoRunTargetNCPName = sTargetname;
		g_AutoKillMonName = "";
	}
	m_bAutoTimer = true; //自动走路定时器  

}


void FrmMain::StopAutoRun(bool stopkillmon /* = true */)
{
	m_bAutoTimer = false;
	TFindNode* node;
	for(int i = 0;i < (int)g_RoadList.size();i++)
	{
		node  =g_RoadList[i];
		delete node;
	}
	g_RoadList.clear();

	g_AutoTargetx = -1;
	g_AutoTargety = -1;
	g_AutoTargetdx = -1;
	g_AutoTargetdy = -1;
	g_MapGateRoadList.clear();
	g_AutoRunTargetNCPName = "";
	if(stopkillmon)
	{
		g_AutoKillMonName = "";
	}

	
}

void FrmMain::AutoTimer()
{
	TMapGateInfo* NextGate;
	if(ServerAcceptNextAction())
	{
		if(!VDMap::GetInstance()->m_Loaded) return;
		 //如果有目标npc，判断是否接近npc，点击npc
		if(g_AutoRunTargetNCPName.length() > 0)
		{
			TActor* target = TPlayScene::GetInstance()->FindNPC(g_AutoRunTargetNCPName);
			if(target)
			{
				if(abs(target->m_nCurrX - g_MySelf->m_nCurrX) < 5 &&
					abs(target->m_nCurrY - g_MySelf->m_nCurrY) < 5)
				{
					StopAutoRun();//停止自动走路
					
					CNetClient::GetInstance()->sendDefMsg(CM_CLICKNPC,target->m_nRecogId,0,0,0);
					return;
				}
			}
		}
		//接近目标距离小于指定误差值 停下来
		if(g_AutoTargetMap == VDMap::GetInstance()->m_sMapName && g_AutoTargetXYD > 0)
		{
			if(abs(g_AutoTargetx - g_MySelf->m_nCurrX) <= g_AutoTargetXYD &&
				abs(g_AutoTargety - g_MySelf->m_nCurrY) <= g_AutoTargetXYD)
			{
				StopAutoRun();//停止自动走路
				return;
			}
		}
		if(g_AutobWalk)g_ChrAction = caWalk;
		else g_ChrAction = caRun;
		if((int)g_RoadList.size() == 0) //路径走完
		{
			if((int)g_MapGateRoadList.size() > 0)
			{
				NextGate = g_MapGateRoadList[0];
				if(NextGate->SMapName == VDMap::GetInstance()->m_sMapName)
				{
					g_MapGateRoadList.erase(g_MapGateRoadList.begin());
					FindPath(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, NextGate->SX, NextGate->SY);
					g_AutoTargetx = NextGate->SX;
					g_AutoTargety = NextGate->SY;
					g_AutoCurMap = NextGate->DMapName;
					return;
				}
			}
		
			if(g_AutoTargetMap == VDMap::GetInstance()->m_sMapName )//|| g_AutoTargetMap.length() > 0 这里会出现一个情况，还没载入地图后就开始寻路
			{
				if(g_AutoCurMap == g_AutoTargetMap || g_AutoTargetx != g_AutoTargetdx
					|| g_AutoTargety != g_AutoTargetdy)
				{
					g_AutoTargetx = g_AutoTargetdx;
					g_AutoTargety = g_AutoTargetdy;
					g_AutoCurMap = "";
					FindPath(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY,g_AutoTargetx,g_AutoTargety);
					return;
				}
			
			}
			if(g_AutoTargetMap.length() > 0 && g_AutoTargetMap != VDMap::GetInstance()->m_sMapName)return;//放到这里 (*^__^*) 嘻嘻
			m_bAutoTimer = false;
			if(g_AutoKillMonName.length() > 0)
			{
				TGuaJiHelper::GetInstance()->m_KillMonName = g_AutoKillMonName;
				TGuaJiHelper::GetInstance()->Start();
			}
			return;

		}
		 //到达一个目标点 删掉拐点
		TFindNode* t = g_RoadList[0];
		if(g_MySelf->m_nCurrX == t->x && g_MySelf->m_nCurrY == t->y)
		{
			delete t;
			g_RoadList.erase(g_RoadList.begin());
			g_AutoRunx = -1;
			g_AutoRuny = -1;
		}
		 //走完了  关闭计时器
		if((int)g_RoadList.size() == 0)
		{
			if((int)g_MapGateRoadList.size() > 0)
			{

				NextGate = g_MapGateRoadList[0];
				if(NextGate->SMapName == VDMap::GetInstance()->m_sMapName)
				{
					g_MapGateRoadList.erase(g_MapGateRoadList.begin());
					FindPath(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY,NextGate->SX,NextGate->SY);
					g_AutoTargetx = NextGate->SX;
					g_AutoTargety = NextGate->SY;
					g_AutoCurMap = NextGate->DMapName;
					return;
				}
				if(g_AutoTargetMap == VDMap::GetInstance()->m_sMapName /*|| g_AutoTargetMap.length() > 0*/)
				{
					if(g_AutoCurMap == g_AutoTargetMap)
					{
						if(g_AutoTargetx != g_AutoTargetdx || g_AutoTargety != g_AutoTargetdy)
						{
							g_AutoTargetx = g_AutoTargetdx;
							g_AutoTargety = g_AutoTargetdy;
							g_AutoCurMap = "";
							FindPath(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY,g_AutoTargetx,g_AutoTargety);
							return;
						}
					}
				}
				if(g_AutoTargetMap.length() > 0 && g_AutoTargetMap != VDMap::GetInstance()->m_sMapName)return;//放到这里 (*^__^*) 嘻嘻
				m_bAutoTimer = false;
				if(g_AutoKillMonName.length() > 0)
				{
					TGuaJiHelper::GetInstance()->m_KillMonName = g_AutoKillMonName;
					TGuaJiHelper::GetInstance()->Start();
				}
				return;
			}
			return;
		}
		t = g_RoadList[0];
		g_AutoRunx = t->x;
		g_AutoRuny = t->y;
		AutoRun();
	}
}

//这个函数要改 - 返回值永远是false
bool FrmMain::AutoRun()
{
	int mx = 0,my = 0,mx1 = 0,my1 = 0,dx = 0,dy = 0,crun = 0;
	unsigned char ndir;
	bool bowalk,bostop;
	unsigned char RunStep;
	bool result = false;
	 tagDefaultMessage msg;
	if(g_AutoRunx != g_MySelf->m_nCurrX || g_AutoRuny != g_MySelf->m_nCurrY)
	{
		mx = g_MySelf->m_nCurrX;
		my = g_MySelf->m_nCurrY;
		dx = g_AutoRunx;
		dy = g_AutoRuny;
		ndir = GetNextDirection(mx,my,dx,dy);
		switch(g_ChrAction)
		{
		case caWalk:
			{
LB_WALK_:
				crun = g_MySelf->CanWalk();
				if(IsUnLockAction(CM_WALK,ndir) && crun > 0)
				{
					GetNextPosXY(ndir, mx, my);
					bowalk = true;
					bostop = false;
					if(!TPlayScene::GetInstance()->CanWalk(mx,my))
					{
						////如果不能走
			
					//	if GuajiRoadList.Count > 0 then begin
					//		Init_Queue();
					//g_AutoRunx := -1;
					//	end;
					//g_AutoRunx := -1;
						if (g_AutoPicUpItem)
						{
							msg.Recog = g_AutoPicUpItem->id;
							msg.Param = g_AutoPicUpItem->x;
							msg.Tag = g_AutoPicUpItem->y;
							Client_ItemHide(&msg,"");
						}
						return result;
					}else
					{
						g_nTargetX = mx;
						g_nTargetY = my;
						//g_dwLastMoveTick = GetTickCount();
						
					}

				}else g_AutoRunx = -1;
				break;;
			}
		case caRun:
			{
				//免助跑
				crun = g_MySelf->CanRun();
				RunStep = 2;
				if(g_MySelf->m_btHorse > 0)RunStep = 3;//如果骑马了，防止跑过
				if(GetDistance(mx,my,dx,dy) >= RunStep && crun > 0)
				{
					if(IsUnLockAction(caRun,ndir))
					{
						mx1 = mx;
						my1 = my;

						if(g_MySelf->m_btHorse > 0)
						{
							GetNextHorseRunXY(ndir,mx,my);
						}else GetNextRunXY(ndir,mx,my);
						if(TPlayScene::GetInstance()->CanRun(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY,mx,my))
						{
							g_nTargetX = mx;
							g_nTargetY = my;
							g_MySelf->UpdateMsg(CM_RUN,mx,my,ndir,0,0,"",0);
							g_dwLastMoveTick = GetTickCount();
							
						}else
						{
							mx = mx1;
							my = my1;
							goto LB_WALK_;
						}
					}
				}else
				{
					g_AutoRunx = -1;
					goto LB_WALK_;
				}
			}
		}
	}else
	{
		if(g_AutoPicUpItem)
		{
			 CNetClient::GetInstance()->GetSendMsg()->SendPickup(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY);
			 //假死一百毫秒
			 unsigned long nTick = GetTickCount();
			 while(true)
			 {
				 if(GetTickCount() - nTick > 100)break;
			 }
			 msg.Recog = g_AutoPicUpItem->id;
			 msg.Param = g_AutoPicUpItem->x;
			 msg.Tag = g_AutoPicUpItem->y;
			 Client_ItemHide(&msg,"");
			 

		}
			
	}
	return false;
}


void FrmMain::Client_TakeOnOK(tagDefaultMessage* msg,std::string body)
{

	int i = 0,nWhere = 0,nMakeIndex = 0;
	std::string sItemName;
	g_MySelf->m_nFeature = msg->Recog;
	g_MySelf->m_nFeatureEx = msg->Param;
	g_MySelf->FeatureChanged();
	if(((int)strlen(g_WaitingUseItem.item.s.Name)) > 0)
	{
		nWhere = msg->Tag;
		nMakeIndex = msg->Serise;
		sItemName = body;
		std::string sName;
		if(nWhere >= 0 && nWhere <= MAXEQUIP - 1)
		{
			for(i = 0;i < MAXBAGITEMS;i++)
			{
				sName = g_ItemArr[i].s.Name;
				if(sName.length() > 0)
				{
					if(sName == sItemName && g_ItemArr[i].MakeIndex == nMakeIndex)
					{
						g_UseItems[nWhere] = g_ItemArr[i];
						memset(g_ItemArr[i].s.Name,0,sizeof(g_ItemArr[i].s.Name));
						break;
					}
				}
			
			}
		}
	}else  //手工穿戴
	{
		if(g_WaitingUseItem.index >= 0 && g_WaitingUseItem.index <= MAXEQUIP - 1)
		{
			g_UseItems[g_WaitingUseItem.index] = g_WaitingUseItem.item;
		}
	}
	memset(g_WaitingUseItem.item.s.Name,0,sizeof(g_WaitingUseItem.item.s.Name));

}

void FrmMain::Client_UpdateItem(tagDefaultMessage* msg,std::string body)
{
	if(body.length() > 0)
	{
		TClientItem cu;
		fnDecode6BitBufA((char*)body.c_str(),(char*)&cu,sizeof(TClientItem));
		UpdateItemBag(cu);
		for(int i = 0;i < MAXEQUIP;i++)
		{
			if(strcmp(g_ItemArr[i].s.Name,cu.s.Name) == 0 && g_ItemArr[i].MakeIndex == cu.MakeIndex)
			{
				g_UseItems[i] = cu;
				break;
			}
		}
		//更新骑宠装备
	}
}

void FrmMain::Client_KillMon(tagDefaultMessage* msg,std::string body)
{
	int nx = msg->Recog;
	int ny = msg->Param;
	std::string sMap,sMon;
	sMon = GetValidStr3Ex(body,sMap,'/');
	if(sMon.length() <= 0)sMon = "*";
	BeginAutoRun(sMap,nx,ny,sMon,true);
}

void FrmMain::Client_LevelUp(tagDefaultMessage* msg,std::string body)
{
	//看其他玩家升级效果.
	int i = MAKELONG_(msg->Tag,msg->Serise);
	TActor* actor = TPlayScene::GetInstance()->FindActor(i);
	if(actor)
	{
		DrawEffectHumex(12,actor);
		if(actor == g_MySelf)
		{
			g_MySelf->m_Abil.Level = msg->Param;
		}
	}
	

}

void FrmMain::DrawEffectHumex(int nType,TActor* ObjectID,unsigned short nLib,int nStart,int nFrame)
{
	TMagicEff* Effect = nullptr;
	TVDImageDatas* Lib = nullptr;
	unsigned char btDir = 0;
	switch(nType)
	{
	case 11:
		{
			if(nLib > 100)
			{
				btDir = 1;
				nLib = nLib % 100;
			}
			if(nLib == 0)
			{
				Lib = GetEffectBase(nStart + 1000,1);
			}
		
			if(Lib)
			{
				Effect = new TObjectEffects(ObjectID,Lib,btDir * (ObjectID->m_btDir * nFrame),nFrame,100,true);
			}
			break;
		}
	case 12:		//等级提升
		{
			Lib = GetUIDatas(12);
			Effect = new TObjectEffects(ObjectID, Lib, 0, 10, 100, false);
			PlaySound_(s_Level_Up);
			break;
		}
	case 82: //变身特效
		{
			Lib = GetUIDatas(82);
			Effect = new TObjectEffects(ObjectID, Lib, 0, 12, 100, false);
			PlaySound_(s_Level_Up);
		}
		break;
	}
	if(Effect)
	{
		Effect->MagOwner = ObjectID;
		TPlayScene::GetInstance()->m_EffectList.push_back(Effect);
	}
}


void FrmMain::Client_AddItem(tagDefaultMessage* msg,std::string body)
{
	if(body.length() > 0)
	{
		TClientItem cu;
		fnDecode6BitBufA((char*)body.c_str(),(char*)&cu,sizeof(TClientItem));
		AddItemBag(cu);
	}
}

void FrmMain::Client_SendJingMai(tagDefaultMessage* msg,std::string body)
{
	g_jmLevel1 = LOBYTE_( LOWORD_(msg->Param));
	g_jmLevel2 = HIBYTE_( LOWORD_(msg->Param));
	g_jmLevel3 = LOBYTE_( HIWORD_(msg->Param));
	g_jmLevel4 = HIBYTE_( HIWORD_(msg->Param));
	g_jmLevel5 = LOBYTE_( LOWORD_(msg->Serise));
	g_jmLevel6 = HIBYTE_( LOWORD_(msg->Serise));
	g_pneuma = msg->Tag;
}

void FrmMain::Client_ChangeNameColor(tagDefaultMessage* msg,std::string body)
{
	TActor* actor =  TPlayScene::GetInstance()->FindActor(msg->Recog);
	if(actor)
	{
		actor->m_nNameColor = GetRGB(msg->Param);
	}
}

void FrmMain::Client_MagicEff(tagDefaultMessage* msg,std::string body)
{
	TActor* actor = TPlayScene::GetInstance()->FindActor(msg->Recog);
	if(actor)
	{
		DrawEffectHumex(11,actor,msg->Serise,msg->Param,msg->Tag);
	}

}

void FrmMain::Client_DuraChange(tagDefaultMessage* msg,std::string body)
{

	int uidx,newdura,newduramax;
	uidx = msg->Param;
	newdura = msg->Recog;
	newduramax = MAKELONG_(msg->Tag,msg->Serise);
	if(uidx >= 0 && uidx < MAXEQUIP)
	{
		if(((int)strlen(g_UseItems[uidx].s.Name)) > 0)
		{
			g_UseItems[uidx].Dura = newdura;
			g_UseItems[uidx].DuraMax = newduramax;
		}
	}

}

void FrmMain::Client_MagicLvExp(tagDefaultMessage* msg,std::string body)
{
	int magid,maglv,magtrain;
	magid = msg->Recog;
	maglv = msg->Param;
	magtrain = MAKELONG_(msg->Tag,msg->Serise);
	TClientMagic* p;
	for(int i = 0;i < (int)g_MagicList.size();i++)
	{
		p = g_MagicList[i];
		if(p->Def.wMagicId == magid)
		{
			p->Level = maglv;
			p->CurTrain  = magtrain;
		}
	}
}

void FrmMain::Client_GetIcons(tagDefaultMessage* msg,std::string body)
{
	int n  = msg->Param;
	int nSize = sizeof(g_Icons) / sizeof(TIconInfo);
	if(n > 0 && n < nSize)
	{
		nSize = sizeof(TIconInfo) * n;
		nSize = body.length();
		char* psDef = new char[nSize];
		fnDecode6BitBufA((char*)body.c_str(),psDef,nSize,true);
		for(int i = 0;i < n;i++)
		{
			memcpy(&g_Icons[i],&psDef[i * sizeof(TIconInfo)],sizeof(TIconInfo));
			//delphi字符串-
			int nLen = g_Icons[i].title[0];
			memcpy(g_Icons[i].title,&g_Icons[i].title[1],sizeof(g_Icons[i].title) - 1);
			g_Icons[i].title[nLen] = 0;
		}
		delete []psDef;
	}
}

void FrmMain::Client_Task(tagDefaultMessage* msg,std::string body)
{
	//ClearMiniTaskPoints();--清空迷你任务栏热点-
	std::string str,data;
	str = body;
	TTaskItem item;
	int TaskId = msg->Recog;
	TClientTaskItem* clienttask;
	if((int)body.length() > 0)
	{
		str = GetValidStr3Ex(str,data,'/');
		if(data.length() > 0)
		{
			fnDecode6BitBufA((char*)data.c_str(),(char*)&item,sizeof(TTaskItem));
			bool bFind = false;
			//找到对应任务
			for(int i = 0; i < (int)g_TaskList.size();i++)
			{
				clienttask = g_TaskList[i];
				if(clienttask->item.TaskID == TaskId)
				{
					bFind =true;
					break;
				}
			}
			if(!bFind)
			{
				clienttask = new TClientTaskItem();
				int n = -1;
				//找到大的任务编号，插入到前面，保证顺序正确
				for(int i = 0;i < (int)g_TaskList.size();i++)
				{
					if(((TClientTaskItem*)g_TaskList[i])->item.TaskID > TaskId)
					{
						n = i;
						break;
					}
				}
				if(n  == -1)
				{
					g_TaskList.push_back(clienttask);
				}else
				{
					g_TaskList.insert(g_TaskList.begin() + n,clienttask);
				}
			
			}
			clienttask->item = item;
			str = GetValidStr3Ex(str,data,'/');
			char szBuf[1024]={0};
			if(data.length() > 0)
			{
				DecodeString((char*)data.c_str(),szBuf,data.length());
				clienttask->ShortDesc = szBuf;
				//替换变量信息
				clienttask->ShortDesc = replace_all_distinct(clienttask->ShortDesc,"{TaskID}",IntToStr(item.TaskID));
				clienttask->ShortDesc = replace_all_distinct(clienttask->ShortDesc,"{TaskState}",IntToStr(item.State));
				clienttask->ShortDesc = replace_all_distinct(clienttask->ShortDesc,"{TaskParam1}",IntToStr(item.param1));
				clienttask->ShortDesc = replace_all_distinct(clienttask->ShortDesc,"{TaskParam2}",IntToStr(item.param2));
				clienttask->ShortDesc = replace_all_distinct(clienttask->ShortDesc,"{TaskParam3}",IntToStr(item.param3));
				clienttask->ShortDesc = replace_all_distinct(clienttask->ShortDesc,"{TaskParam4}",IntToStr(item.param4));
			}

		}
	}else
	//数据为空，删除任务
	{
		for(int i = 0; i < (int)g_TaskList.size();i++)
		{
			if(g_TaskList[i]->item.TaskID == TaskId)
			{
				clienttask = g_TaskList[i];
				g_TaskList.erase(g_TaskList.begin() + i);
				delete clienttask;
			}
		}
	}
	CMiniTaskPan* pan = (CMiniTaskPan*)GetDialog(DIALOG_TYPE::MINITASK);
	pan->ProcessTask();
}

void FrmMain::DoLocalTaskCMD(int nTaskID,std::string sCMD)
{
	std::string sCmd,tmp,cmdstr;
	sCmd = sCMD;
	sCmd = GetValidStr3Ex(sCmd,tmp,':');
	sCmd = GetValidStr3Ex(sCmd,tmp,' ');
	std::vector<std::string> param;
	param.clear();
	cmdstr = tmp;
	if(cmdstr.length() <= 0)return;
	while(tmp.length() > 0 && sCmd.length() > 0)
	{
		sCmd = GetValidStr3Ex(sCmd,tmp,' ');
		if(tmp.length() > 0)
		{
			param.push_back(tmp);
		}
	}
	if(cmdstr == "goto")
	{
		if((int)param.size() == 4)	 //自动走
		{
			BeginAutoRun(param[0],StrToInt(param[1].c_str()),StrToInt(param[2].c_str()),param[3].c_str());
			
		}else
		{
			BeginAutoRun(param[0],StrToInt(param[1].c_str()),StrToInt(param[2].c_str()),"");
		}
	}else if(cmdstr == "killmon")	//自动打怪
	{
		if((int)param.size() == 3)
		{
			BeginAutoRun(param[0],StrToInt(param[1].c_str()),StrToInt(param[2].c_str()),"*",true);
		}else
		{
			BeginAutoRun(param[0],StrToInt(param[1].c_str()),StrToInt(param[2].c_str()),param[3],true);
		}
		
	}
}

void FrmMain::Client_SpeelNeed(tagDefaultMessage* msg,std::string body)
{
	int mid = LOWORD_(msg->Param);
	int ntime = HIWORD_(msg->Param);
	int nWrathPoint = msg->Serise;
	TClientMagicExInfo* magicex;
	for(int i = 0;i < (int)g_MagicExInfoList.size();i++)
	{
		magicex = g_MagicExInfoList[i];
		if(magicex->wMagIdx == mid)
		{
			magicex->wMagIdx = mid;
			magicex->NeedTime = ntime;
			magicex->UpdateTime= GetTickCount();
			magicex->NeedWrathPoint = nWrathPoint;
			return;
		}
	}
	magicex = new TClientMagicExInfo();
	magicex->wMagIdx = mid;
	magicex->NeedTime = ntime;
	magicex->UpdateTime= GetTickCount();
	magicex->NeedWrathPoint = nWrathPoint;
	g_MagicExInfoList.push_back(magicex);
}