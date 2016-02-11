#ifndef MSHARE_H_
#define MSHARE_H_
#include <string>
#include <map>
#include "Actor.h"
#include <vector>
#include "GameStruct.h"
class CBaseDialog;
class TVDImage;
class TVDImageDatas;
TVDImage* GetMiniMapImage(std::string nMapIndex);
TVDImage* GetMapImage(int nFileIndex, int nImageIndex);
TVDImage* GetMonImage(int  nAppr,int imageIndex,int &nx,int &ny);
TVDImage* GetHumImg(int Dress,int m_btSex,int nFrame,int  &ax,int &ay,char color,int nHorse);
TVDImage* GetHumWringsImg(int Dress,int m_btSex,int nFrame,int  &ax,int &ay,char color,int nHorse);
TVDImage* GetWWeaponImg(int Weapon,int m_btSex,int nFrame,int  &ax, int &ay);
TVDImage* GetHumSImg(int Dress,int m_btSex,int nFrame,int &ax,int &ay,char color);
TVDImage* GetUIImage(int ImageIndex);
TVDImageDatas* GetUIDatas(int FileIndex);
TVDImage* GetBagImage(int ImageIndex);
TVDImage* GetWringsImage(int nIdx);
TVDImage* GetInsideImage(int nIdx);
TVDImageDatas* GetEffectBase(int mag,int mtype);
TVDImage* GetEffectImage(int mag,int idx,int &nx,int &ny);
TVDImage* GetNPCImageAndPXY(int nAppr, int ImageIndex,int &nx,int &ny);
TVDImage* GetNPCImage(int nAppr, int ImageIndex);
unsigned long GetRGB(unsigned char c256);
bool IsStringNumber(const char* str);
extern std::vector<TClientTaskItem*> g_TaskList;
extern std::map<std::string,TVDImageDatas*> g_UIImageHash;
extern std::map<std::string,TVDImageDatas*> g_MapVDDHash;
extern std::map<std::string,TVDImageDatas*> g_HumImagesHash;
extern std::map<std::string,TVDImageDatas*> g_WMonImagesHash;
extern THumActor* g_MySelf;
extern std::vector<int> g_ChangeFaceReadyList;
extern std::vector<TActor*> g_FreeActorList;
extern std::vector<TClientMagic*> g_MagicList;
extern std::vector<TClientMagicExInfo*> g_MagicExInfoList;
extern std::vector<TDropItem*> g_DropedItemList;
extern unsigned long g_dwDizzyDelayStart;
extern unsigned long g_dwDizzyDelayTime;
extern bool g_boServerChanging;
extern int g_nRunReadyCount;
extern bool g_boCanStartRun;
extern TIconInfo g_Icons[10];//人物图标信息
extern TShared Shared;
extern TActor* g_FocusCret; //焦点目标
extern TActor* g_focuscret1;
extern TActor* g_TargetCret; //锁定攻击目标
extern TActor* g_MagicTarget;;
extern int g_nDupSelection;
extern TMonsterAction  MANPC1000;
extern TMonsterAction MANPCDEF;
extern TMonsterAction PLANT;
extern TMonsterAction MINEDEF;
extern TMonsterAction MA0;
extern TMonsterAction MA27;
extern TMonsterAction HORSE;
extern TMonsterAction MADEF;
extern THumanAction HA;
extern unsigned char WORDER[2][3000];

extern bool g_boCanRunHuman;
extern bool g_boCanRunNpc;
extern bool g_boCanRunAllInWarZone;
extern bool g_boCanRunMon;
extern unsigned long g_MySelfDeathTime;
extern int g_nAreaStateValue;
extern TChrAction g_ChrAction;
extern int g_nTargetX;
extern int g_nTargetY;
extern int g_nMouseX;
extern int g_nMouseY;
extern bool g_boAutoDig;
extern int g_nMouseCurrY;
extern int g_nMouseCurrX;
extern int g_dwLastAttackTick;
extern int g_dwLastMoveSpeed;
extern int g_dwLastMoveSpeedTick;
extern bool ActionFailLock;
extern unsigned long ActionFailLockTime;
extern unsigned long g_dwLatestSpellTick;
extern unsigned long g_dwMagicPKDelayTime;
extern unsigned long g_dwLastMoveTick;
extern int g_boMapMoving;
extern unsigned long g_dwAutoHiddentTick;
extern int g_nSendCount;
extern int g_nReceiveCount;
extern unsigned long g_dwLatestHitTick;
extern int g_nMDlgX;
extern int g_nMDlgY;
extern unsigned long g_dwLatestRushRushTick;
extern unsigned long g_dwLatestPoxue;
extern bool g_boMapAnonymous;
extern std::string g_sMapTitle;
extern int g_nMapMusic;
extern int g_nPlayMusicCount;
extern bool g_boMineMap;
extern std::string g_sMapMusic;
extern std::string g_sGoldName;
extern unsigned long g_dwDropItemFlashTime;
extern int g_horseTick;
extern bool g_boAutoFire;
extern int g_dwAutoFireTick;
extern bool g_boNextTimeFireHit;
extern unsigned long g_dwLatestMagicTick;
extern unsigned long g_dwMagicTime;
extern unsigned long g_dwLatestFireHitTick;
extern bool g_boCanLongHit;
extern int g_dwAutoOpenLongHit;
extern bool g_boAutoWide;
extern bool g_boCanWideHit;
extern int g_dwAutoOpenWide;
extern bool g_boNextTimePowerHit;
extern bool g_boAutoFireCT;
extern bool g_boCan34SKillHit;
extern bool g_boCan35SKillHit;
extern bool g_boCanTwnHit;
extern bool g_boCanStnHit;
extern bool g_boCan34SkillHit;
extern bool g_boCan35SkillHit;
extern bool g_boCan103SkillHit;
extern bool g_boCan103SKillHit;
extern bool g_boCanCrsHit;
extern unsigned long g_nHitTime;
extern int g_nItemSpeed;
extern TActor* g_MagicLockActor;
extern int g_nAutoPickUpX;
extern int g_nAutoPickupY;
extern int g_nAutoPickPos;
extern unsigned long g_dwAutoPickupTick;
extern unsigned long g_dwAutoPickupTime;
extern unsigned long g_dwAutoSayTick;
extern int g_nAutosayIdx;
extern unsigned long g_dwAutoShieldTick;
extern unsigned long g_dwSpellTime;
extern int g_dwMagicDelayTime;
extern int g_boWarrPx;
extern int g_boWarrTbs;
extern int g_ReAliveFreeCount;
extern int g_ReAliveNeedGameGold;
extern unsigned long g_dwLatestStruckTick;
extern std::map<std::string,TLocalMapInfo*>  g_alllocalmap;
extern TLocalMapInfo* g_CurLocalMap;
extern int g_MapGateFrame;
extern	unsigned long g_MapGateTick;
extern std::vector<TSoundInfo*> g_SoundList; //加载的音乐文件-
extern int g_nMyAntiMagic;
extern int g_nCrit;
extern int g_nMyHitPoint;
extern int g_nMySpeedPoint;
extern int g_nMyAntiPoison;
extern int g_nMyPoisonRecover;
extern int g_nMyHealthRecover;
extern int g_nMySpellRecover;
extern int g_nPKPoint;
extern int g_nProtect;
extern int g_VIPLevel;
extern TSubAbilityExt g_SubAbil;
extern int g_nBonusPoint;
extern int g_nBonusPointChg;
extern int g_ReNewLevel;
extern int g_ReNewCount;
extern int g_RenewNeedGold;
extern int g_ClearBonusPointNeedGameGold;
extern int g_addRenewCountNeedGameGold;
extern TNakedAbility g_BonusAbil;
extern TNakedAbility g_BonusTick;
extern TReNewInfo g_RenewInfo;
extern std::string g_sGameGoldName;
extern std::string g_sGamePointName;
extern unsigned char g_jmLevel1;
extern unsigned char g_jmLevel2;
extern unsigned char g_jmLevel3;
extern unsigned char g_jmLevel4;
extern unsigned char g_jmLevel5;
extern unsigned char g_jmLevel6;
extern int g_pneuma;
//调试--
extern TClientUserStateInfo UserState1;
extern std::vector<TGroupItem*> g_GroupItems;
extern std::vector<std::string> g_AnroidLog;
extern std::map<std::string,TAdditionItem*> g_AdditionItemList;
extern std::vector<TStdItem*> g_StdItemList;
extern  std::map<int,TStdItem*> g_MItemArray;
extern TClientItem g_ItemArr[MAXBAGITEMS];

extern int g_AutoTargetx;
extern int g_AutoTargety;
extern int g_AutoTargetdx;
extern int g_AutoTargetdy;
extern std::string g_AutoRunTargetNCPName;    
extern std::string g_AutoKillMonName;
extern std::string g_AutoTargetMap;
extern std::string g_AutoCurMap;
extern int g_AutoRunx;
extern int g_AutoRuny;
extern bool g_AutobWalk;
extern TDropItem* g_AutoPicUpItem;
extern int g_AutoTargetXYD;
extern std::string g_sHPUnbindItemName;
extern std::string g_sMPUnbindItemName;
extern std::string g_sFastUnbindItemName;
extern std::string g_sAutoEatHPName;
extern std::string g_sAutoEatMPName ;
extern std::string g_sAutoEatFastName ;
extern std::string g_sAutoUseJuanName;
extern TClientItem g_MouseItem;
extern TClientItem g_UseItems[MAXEQUIP];
extern int g_nCurMerchant; //当前兑换的npcid
extern bool BoNoDisplayMaxDura;
extern TMovingItem g_WaitingUseItem;
extern bool g_UIClick; //cocosstudio的单击控件会穿透到frmmain的单击事件- 做个标识
void AddChangeFace(int recogid);
void DelChangeFace(int recogid);
bool IsChangingFace(int recogid);
//Ator.pas
int GetOffset(int Appr);
TMonsterAction* GetRaceByPM(int race,unsigned short Appr);
unsigned char GetNextDirection(int sx,int sy,int dx,int dy);
void GetFrontPosition(int sx,int sy,int dir,int &newx,int &newy);
void GetBackPosition(int sx,int sy,int dir,int &newx,int &newy);
void GetNextPosXY(unsigned char dir,int &x,int &y);
void GetNextHorseRunXY(unsigned char dir,int &x,int &y);
void GetNextRunXY(unsigned char dir,int &x,int &y);
int GetFlyDirection16(int sx,int sy,int ttx,int tty);
std::string IntToStr(int V);
int StrToInt(const char* v);
//取随机数
void SetRandomSeed();
int Random_Int(int start,int end);
float Random_Float(float start,float end);
std::string IntToJob(unsigned char btJob); 
std::string IntToSex(unsigned char btSex);
unsigned long str_to_hex(std::string string);
std::string randomName(unsigned char gend); //随机姓名
std::vector<std::string> split_String( std::string str, std::string pattern);//分割文本

std::string StringUpper(const char* pStr); //转换成大写
std::string StringToLower(const char* pStr); //转换到小写
void StringReplace(std::string&s1,const std::string&s2,const std::string&s3); //字符串替换
cocos2d::Color4B HexColorToColor4B(unsigned long color);
bool CheckBagFulll();
TStdItem* GetStdItemInfo(int nIdx);
TStdItem* GetStdItemInfo(std::string sName);
void GetItemAddValueFun(TUserItem* UserItem,TStdItem* StdItem);
bool AddItemBag(TClientItem cu);
bool UpdateItemBag(TClientItem cu);
void ArrangeItemBag();
void GetMouseItemInfo(std::string &iname,std::string &line1,std::string &line2,std::string &line3,bool &useable);
void GetMouseItemMosaicInfo(std::string &sstr);
std::string GetGroupItemInfo(TStdItem* stditem,unsigned char btSex,int playidx = 0);
bool CheckUseItem(std::string itemname);
bool CheckUseItem1(std::string itemname);
int GetItemHoleCount(TUserItem* userItem);
int GetItemOpenHoleCount(TUserItem* useritem);//获得物品属性里的开孔次数，不是开成功的次数，是开了几次，包含失败的
int GetMosaicItemIdxInHole(TUserItem* userItem,int holdIdx);
TStdItem* GetMStdItemInfo(int mID);
std::string GetBeforeStr(std::string str,std::string &dest,std::string Divider);
void ClientItem2UserItem(TClientItem* citem,TUserItem* uitem);
std::string GetDuraStr(int Dura,int DuraMax);
std::string GetDura100Str(int Dura,int DuraMax);
bool GetHorseNeedStr(std::string &returnstr);	
bool GetNeedStr(std::string returnstr);// //所需属性字符串生成 返回是否可用
std::string GetItemQualityName(TStdItem* stditem);
std::string GetItemQualityColor(TStdItem* stditem);
TAdditionItem* GetAdditionItemInfo(std::string sName);
std::string& replace_all_distinct(std::string& str,const std::string& old_value,const std::string& new_value);    
int TextWidth(std::string Text,int FontSize = 12); //取字符串内容的宽度
#if	defined(WIN32)								// win32
//#	include	<windows.h>
#elif defined(__APPLE__) && defined(__MACH__)	// mac os
#	include <float.h>
#	include <mach/mach_time.h>
inline	unsigned long	GetTickCount()
{
	static	double	ticksToMicroSeconds	= 0.0;
	if( ticksToMicroSeconds <= DBL_EPSILON )
	{
		mach_timebase_info_data_t	sTimebaseInfo;
		mach_timebase_info(&sTimebaseInfo);
		ticksToMicroSeconds = (double)sTimebaseInfo.numer / sTimebaseInfo.denom / 1000000.0;
	}
	return	(unsigned long)(mach_absolute_time() * ticksToMicroSeconds);
}
#else											// linux
#	include	<time.h>
inline	unsigned long	GetTickCount()
{
	struct timespec ts;
	clock_gettime(CLOCK_MONOTONIC, &ts);
	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}
#endif



#endif