#include "MShare.h"
#include "cocos2d.h"
#include "VD_Share.h"
#include "./Common/VDImageDatas.h"
#include "./Common/Grobal2.h"
#include "VDImage.h"
#include <stdio.h>
#include <ctype.h>

class CBaseDialog;


//全局变量
std::vector<TClientTaskItem*> g_TaskList;
std::vector<TStdItem*> g_StdItemList;
std::map<std::string,TAdditionItem*> g_AdditionItemList;
std::map<int,TStdItem*> g_MItemArray;
std::map<std::string,TVDImageDatas*> g_MapVDDHash;
std::map<std::string,TVDImageDatas*> g_WMonImagesHash;
std::map<std::string,TVDImageDatas*> g_HumImagesHash;
std::map<std::string,TVDImageDatas*> g_UIImageHash;
std::vector<std::string> g_AnroidLog;
THumActor* g_MySelf = nullptr;
std::vector<int> g_ChangeFaceReadyList;
std::vector<TActor*> g_FreeActorList;
std::vector<TClientMagic*> g_MagicList;
std::vector<TClientMagicExInfo*> g_MagicExInfoList;
std::vector<TDropItem*> g_DropedItemList;
bool g_boServerChanging;
unsigned long g_dwDizzyDelayStart;
unsigned long g_dwDizzyDelayTime;
TShared Shared;
bool g_boCanRunHuman;
bool g_boCanRunNpc;
bool g_boCanRunAllInWarZone;
bool g_boCanRunMon;
unsigned long g_MySelfDeathTime;
int g_dwLastMoveSpeed;
int g_dwLastMoveSpeedTick;
int g_nMouseCurrY;
int g_nMouseCurrX;
int g_dwLastAttackTick;
TChrAction g_ChrAction;
int g_nTargetX;
int g_nTargetY;
int g_nMouseX;
int g_nMouseY;
int g_nAreaStateValue;
bool g_boAutoDig;
bool ActionFailLock;
unsigned long ActionFailLockTime;
unsigned long g_dwLatestSpellTick;
unsigned long g_dwMagicPKDelayTime;
unsigned long g_dwLastMoveTick;
int g_boMapMoving;
unsigned long g_dwAutoHiddentTick;
int g_nRunReadyCount;
bool g_boCanStartRun;
int g_nSendCount;
int g_nReceiveCount;
unsigned long g_dwLatestHitTick;
int g_nMDlgX;
int g_nMDlgY;
unsigned long g_dwLatestRushRushTick;
unsigned long g_dwLatestPoxue;
TActor* g_FocusCret;
TActor* g_MagicTarget;
TActor* g_focuscret1;
TActor* g_TargetCret;
int g_nDupSelection;
int g_horseTick;
bool g_boAutoFire;
int g_dwAutoFireTick;
bool g_boNextTimeFireHit;
unsigned long g_dwLatestMagicTick;
unsigned long g_dwMagicTime;
unsigned long g_dwLatestFireHitTick;
bool g_boCanLongHit;
int g_dwAutoOpenLongHit;
bool g_boAutoWide;
bool g_boCanWideHit;
int g_dwAutoOpenWide;
bool g_boNextTimePowerHit;
bool g_boAutoFireCT;
bool g_boCan34SKillHit;
bool g_boCan35SKillHit;
bool g_boCanTwnHit;
bool g_boCan34SkillHit;
bool g_boCan35SkillHit;
bool g_boCan103SkillHit;
bool g_boCanStnHit;
bool g_boCan103SKillHit;
bool g_boCanCrsHit;
unsigned long g_nHitTime;
int g_nItemSpeed;
TActor* g_MagicLockActor;
int g_nAutoPickUpX;
int g_nAutoPickupY;
int g_nAutoPickPos;
unsigned long g_dwAutoPickupTick;
unsigned long g_dwAutoPickupTime;
unsigned long g_dwAutoSayTick;
int g_nAutosayIdx;
unsigned long g_dwAutoShieldTick;
unsigned long g_dwSpellTime;
int g_dwMagicDelayTime;
int g_boWarrPx;
int g_boWarrTbs;
int g_ReAliveFreeCount;
int g_ReAliveNeedGameGold;
unsigned long g_dwLatestStruckTick;
std::map<std::string,TLocalMapInfo*>  g_alllocalmap;
std::vector<TSoundInfo*> g_SoundList;
int g_nMyAntiMagic;
int g_nCrit;
int g_nMyHitPoint;
int g_nMySpeedPoint;
int g_nMyAntiPoison;
int g_nMyPoisonRecover;
int g_nMyHealthRecover;
int g_nMySpellRecover;
int g_nPKPoint;
int g_nProtect;
int g_VIPLevel;
TSubAbilityExt g_SubAbil;
int g_nBonusPoint;
int g_nBonusPointChg;
int g_ReNewLevel;
int g_ReNewCount;
int g_RenewNeedGold;
TIconInfo g_Icons[10];
int g_ClearBonusPointNeedGameGold;
int g_addRenewCountNeedGameGold;
TNakedAbility g_BonusAbil;
TNakedAbility g_BonusTick;
TReNewInfo g_RenewInfo;
bool g_boMapAnonymous;
std::string g_sMapTitle;
int g_nMapMusic;
int g_nPlayMusicCount;
bool g_boMineMap;
std::string g_sMapMusic;
std::string g_sGameGoldName;
std::string g_sGoldName;
unsigned long g_dwDropItemFlashTime;
std::string g_sGamePointName;
int g_MapGateFrame;
int g_nCurMerchant;
unsigned long g_MapGateTick;
int g_AutoTargetx;
int g_AutoTargety;
int g_AutoTargetdx;
int g_AutoTargetdy;
std::vector<TGroupItem*> g_GroupItems;
std::string g_AutoRunTargetNCPName;    
std::string g_AutoKillMonName;
std::string g_AutoTargetMap;
std::string g_AutoCurMap;
bool g_AutobWalk;
int g_AutoTargetXYD;
int g_AutoRunx;
int g_AutoRuny;
unsigned char g_jmLevel1;
unsigned char g_jmLevel2;
unsigned char g_jmLevel3;
unsigned char g_jmLevel4;
unsigned char g_jmLevel5;
unsigned char g_jmLevel6;
int g_pneuma;
TMovingItem g_WaitingUseItem;
TDropItem* g_AutoPicUpItem;
std::string g_sHPUnbindItemName = "初级金创药(包),中级金创药(包),高级金创药(包),超级红药(包),超级金创药(包)";
std::string g_sMPUnbindItemName = "初级魔法药(包),中级魔法药(包),高级魔法药(包),超级蓝药(包),超级魔法药(包)";
std::string g_sFastUnbindItemName = "疗伤药(包),红花草(包),蘑菇(包),大还丹(包),天山血莲(包),天外血莲(包),万年雪霜(包),万年雪霜(包)绑,玫瑰玉露(包),玫瑰玉露包(绑)";

std::string g_sAutoEatHPName = "初级金创药,中级金创药,高级金创药,超级红药,超级金创药";
std::string g_sAutoEatMPName = "初级魔法药,中级魔法药,高级魔法药,超级蓝药,超级魔法药";
std::string g_sAutoEatFastName  = "疗伤药,红花草,蘑菇,大还丹,天山血莲,天外血莲,万年雪霜,万年雪霜绑,玫瑰玉露,玫瑰玉露绑";
std::string g_sAutoUseJuanName = "回城卷,回城石";
TClientUserStateInfo UserState1;//查看他人装备信息
TClientItem g_MouseItem;
TClientItem g_UseItems[MAXEQUIP]; //当前身上装备
bool BoNoDisplayMaxDura;
bool g_UIClick;
TLocalMapInfo* g_CurLocalMap;
TMonsterAction  MANPC1000;
TMonsterAction MANPCDEF;
TMonsterAction PLANT;
TMonsterAction MINEDEF;
TMonsterAction MA0;
TMonsterAction MA27;
TMonsterAction HORSE;
TMonsterAction MADEF;
THumanAction HA;

TClientItem g_ItemArr[MAXBAGITEMS];
TVDImage* GetHumSImg(int Dress,int m_btSex,int nFrame,int &ax,int &ay,char color)
{
	//人物分性别、衣服和动作,其中一个动作160帧计算，帧保持原有连续性，整除160获得对应文件
	char sText[1024] = {0};
	std::string sFileName="";
	if(m_btSex == 0)
	{
		sprintf(sText,HUMSIMGIMAGESFILE, Dress, nFrame / 160);
		sFileName = sText;
	}else
	{
		sprintf(sText,WHUMSIMGIMAGESFILE, Dress, nFrame / 160);
		sFileName = sText;
	}
	if(sFileName.length() <= 0)
	{
		CCLOG("GetHumSImg %d %d",Dress,nFrame);
		return nullptr;
	}
	//武器图片和人物身体图片用同一个哈希表存放
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_HumImagesHash.find(sFileName);
	if(it == g_HumImagesHash.end())
	{
		std::string path = cocos2d::FileUtils::getInstance()->
			fullPathForFilename(sFileName);
		if(!cocos2d::FileUtils::getInstance()->isFileExist(path))
		{
			return nullptr;
		}
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_HumImagesHash[sFileName] = vdd;
	}
	it = g_HumImagesHash.find(sFileName);
	if(it != g_HumImagesHash.end())
	{
		TVDImage* img = it->second->GetImage(nFrame % 160);
		if(img)
		{
			ax = img->nx;
			ay = img->ny;
		}
		return img;
	}

	return nullptr;
}
TVDImage* GetWWeaponImg(int Weapon,int m_btSex,int nFrame,int  &ax, int &ay)
{
	if( nFrame / 160 > 11 ) return nullptr;//12是打坐，武器没有以后的动作目前，暂时这样处理以免404
	//武器图片和衣服的一样，分性别动作,其中一个动作160帧计算，帧保持原有连续性，整除160获得对应文件
	char sText[1024] = {0};
	std::string sFileName;
	if(m_btSex == 0)
	{
		sprintf(sText,MWEAPONIMAGEFILE,Weapon,nFrame / 160);
		sFileName = sText;
	}else
	{
		sprintf(sText,WMWEAPONIMAGEFILE, Weapon-1, nFrame / 160);
		sFileName = sText;
	}
	 //武器图片和人物身体图片用同一个哈希表存放
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_HumImagesHash.find(sFileName);
	if(it == g_HumImagesHash.end())
	{
		std::string path = cocos2d::FileUtils::getInstance()->
			fullPathForFilename(sFileName);
		if(!cocos2d::FileUtils::getInstance()->isFileExist(path))
		{
			return nullptr;
		}
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_HumImagesHash[sFileName] = vdd;
	}
	it = g_HumImagesHash.find(sFileName);
	if(it != g_HumImagesHash.end())
	{
		TVDImage* img = it->second->GetImage(nFrame % 160);
		if(img)
		{
			ax = img->nx;
			ay = img->ny;
		}
		return img;
	}
	return nullptr;
}
TVDImage* GetHumWringsImg(int Dress,int m_btSex,int nFrame,int  &ax,int &ay,char color,int nHorse)
{

	char sText[1024] = {0};
	std::string sFileName;
	if(nHorse > 0)
	{
		if(m_btSex == 0)
		{
			sprintf(sText,HUMWRINGSHORSEIMAGESFILE,MAX(0,Dress),nFrame / 160);
			sFileName = sText;
		}else 
		{
			sprintf(sText,WHUMWRINGSHORSEIMAGESFILE, MAX(0, Dress -1)/*由于原传奇是女性相对便宜了1这里减去*/
				, nFrame / 160);
			sFileName = sText;
		}
	}else //没骑马的
	{
		if(m_btSex == 0)
		{
			sprintf(sText,HUMWRINGSIMAGESFILE, MAX(0, Dress), nFrame / 160);
			sFileName = sText;
		}else
		{
			sprintf(sText,WHUMWRINGSIMAGESFILE, MAX(0, Dress - 1), nFrame / 160);
			sFileName = sText;
		}
	}
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_HumImagesHash.find(sFileName);
	if(it == g_HumImagesHash.end())
	{
		std::string path = cocos2d::FileUtils::getInstance()->
			fullPathForFilename(sFileName);
		if(!cocos2d::FileUtils::getInstance()->isFileExist(path))
		{
			return nullptr;
		}
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_HumImagesHash[sFileName] = vdd;
	}
	it = g_HumImagesHash.find(sFileName);
	if(it != g_HumImagesHash.end())
	{
		TVDImage* img = it->second->GetImage(nFrame % 160);
		if(img)
		{
			ax = img->nx;
			ay = img->ny;
		}
		return img;
	}
	return nullptr;
}

TVDImage* GetHumImg(int Dress,int m_btSex,int nFrame,int  &ax,int &ay,char color,int nHorse)
{

	char sText[1024] = {0};
	std::string sFileName;
	if(nHorse > 0)
	{
		if(m_btSex == 0)
		{
			sprintf(sText,HUMONHORSEIMAGESFILE,MAX(0,Dress),nFrame / 160);
			sFileName = sText;
		}else 
		{
			sprintf(sText,WHUMONHORSEIMAGESFILE, MAX(0, Dress -1)/*由于原传奇是女性相对便宜了1这里减去*/
			   , nFrame / 160);
			sFileName = sText;
		}
	}else //没骑马的
	{
		if(m_btSex == 0)
		{
			 sprintf(sText,HUMIMGIMAGESFILE, MAX(0, Dress), nFrame / 160);
			 sFileName = sText;
		}else
		{
			sprintf(sText,WHUMIMGIMAGESFILE, MAX(0, Dress - 1), nFrame / 160);
			sFileName = sText;
		}
	}
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_HumImagesHash.find(sFileName);
	if(it == g_HumImagesHash.end())
	{
		std::string path = cocos2d::FileUtils::getInstance()->
			fullPathForFilename(sFileName);
		if(!cocos2d::FileUtils::getInstance()->isFileExist(path))
		{
			return nullptr;
		}
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_HumImagesHash[sFileName] = vdd;
	}
	it = g_HumImagesHash.find(sFileName);
	if(it != g_HumImagesHash.end())
	{
		TVDImage* img = it->second->GetImage(nFrame % 160);
		if(img)
		{
			ax = img->nx;
			ay = img->ny;
		}
		return img;
	}
	return nullptr;
}
TVDImage* GetMonImage(int  nAppr,int imageIndex,int &nx,int &ny)
{
	char sText[1024] = {0};
	sprintf(sText,MONIMAGEFILENAME,nAppr,imageIndex / 160);
	std::string sFileName = sText;
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_WMonImagesHash.find(sFileName);
	if(it == g_WMonImagesHash.end())
	{
		std::string path = cocos2d::FileUtils::getInstance()->
			fullPathForFilename(sFileName);
		if(!cocos2d::FileUtils::getInstance()->isFileExist(path))
		{
			return nullptr;
		}
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_WMonImagesHash[sFileName] = vdd;
	}
	it = g_WMonImagesHash.find(sFileName);
	if(it != g_WMonImagesHash.end())
	{
		TVDImage* image = it->second->GetImage(imageIndex % 160);
		if(image)
		{
			nx = image->nx;
			ny = image->ny;
		}
		return image;
	}
	return nullptr;
}
TVDImage* GetNPCImage(int nAppr, int ImageIndex)
{
	char sText[1024] = {0};
	sprintf(sText,NPCIMAGESFILE,nAppr);
	std::string sFileName = sText;
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_HumImagesHash.find(sFileName);
	if(it == g_HumImagesHash.end())
	{
		std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename(sFileName);
		if(!cocos2d::FileUtils::getInstance()->isFileExist(path))
		{
			return nullptr;
		}
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_HumImagesHash[sFileName] = vdd;
	}
	it = g_HumImagesHash.find(sFileName);
	if(it != g_HumImagesHash.end())
	{
		return it->second->GetImage(ImageIndex);
	}
	return nullptr;
}
TVDImage* GetNPCImageAndPXY(int nAppr, int ImageIndex,int &nx,int &ny)
{
	TVDImage* Result = GetNPCImage(nAppr,ImageIndex);
	if(Result)
	{
		nx = Result->nx;
		ny = Result->ny;
	}
	return Result;
}

TVDImageDatas* GetEffectBase(int mag,int mtype)
{
	char sMapIndex[1024] = {0};
	sprintf(sMapIndex,EFFECTIMAGEFILE,mag);
	std::string sFileName = sMapIndex;
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_UIImageHash.find(sFileName);
	TVDImageDatas* vdd  = nullptr;
	if(it == g_UIImageHash.end())
	{
		vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_UIImageHash[sFileName] = vdd;
		return vdd;
	}
	vdd = (TVDImageDatas*)it->second;
	return vdd;
}
TVDImage* GetUIImage(int ImageIndex)
{
	char sMapIndex[1024] = {0};
	sprintf(sMapIndex,UIIMAGEFILE,ImageIndex / 100);
	std::string sFileName = sMapIndex;
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_UIImageHash.find(sFileName);
	if(it == g_UIImageHash.end())
	{
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_UIImageHash[sFileName] = vdd;
	}
	it = g_UIImageHash.find(sFileName);
	if(it != g_UIImageHash.end())
	{
		return it->second->GetImage(ImageIndex % 100);
	}
	return nullptr;
}
TVDImageDatas* GetUIDatas(int FileIndex)
{
	std::string sFileName;
	char sMapIndex[1024] = {0};
	sprintf(sMapIndex,UIIMAGEFILE,FileIndex);
	sFileName = sMapIndex;
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_UIImageHash.find(sFileName);
	if(it == g_UIImageHash.end())
	{
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_UIImageHash[sFileName] = vdd;
	}
	it = g_UIImageHash.find(sFileName);
	if(it != g_UIImageHash.end())
	{
		return it->second;
	}
	return nullptr;
}
TVDImage* GetBagImage(int ImageIndex)
{
	char sMapIndex[1024] = {0};
	sprintf(sMapIndex,BAGITEMIMAGEFILE,ImageIndex / 100);
	std::string sFileName = sMapIndex;
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_UIImageHash.find(sFileName);
	if(it == g_UIImageHash.end())
	{
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_UIImageHash[sFileName] = vdd;
	}
	it = g_UIImageHash.find(sFileName);
	if(it != g_UIImageHash.end())
	{
		return it->second->GetImage(ImageIndex % 100);
	}
	return nullptr;
}

TVDImage* GetWringsImage(int nIdx)
{

	std::string sFileName = WINGSEIMAGEFILE;
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_UIImageHash.find(sFileName);
	if(it == g_UIImageHash.end())
	{
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_UIImageHash[sFileName] = vdd;
	}
	it = g_UIImageHash.find(sFileName);
	if(it != g_UIImageHash.end())
	{
		return it->second->GetImage(nIdx);
	}
	return nullptr;
}
TVDImage* GetInsideImage(int nIdx)
{
	char sMapIndex[1024] = {0};
	sprintf(sMapIndex,INSIDEIMAGEFILE,nIdx / 100);
	std::string sFileName = sMapIndex;
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_UIImageHash.find(sFileName);
	if(it == g_UIImageHash.end())
	{
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_UIImageHash[sFileName] = vdd;
	}
	it = g_UIImageHash.find(sFileName);
	if(it != g_UIImageHash.end())
	{
		return it->second->GetImage(nIdx % 100);
	}
	return nullptr;
}
TVDImage* GetMiniMapImage(std::string nMapIndex)
{
	char sMapIndex[1024] = {0};

	std::string imgkey = "mmap" + nMapIndex;

	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_MapVDDHash.find(imgkey);
	if(it == g_MapVDDHash.end())
	{
		sprintf(sMapIndex,MINMAPIMAGEFILE,nMapIndex.c_str());
		std::string sFileName = sMapIndex;
		std::string path = cocos2d::FileUtils::getInstance()->
			fullPathForFilename(sFileName);
		if(!cocos2d::FileUtils::getInstance()->isFileExist(path))
		{
			return nullptr;
		}
		TVDImageDatas* vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_MapVDDHash[imgkey] = vdd;
	}
	it = g_MapVDDHash.find(imgkey);
	if(it != g_MapVDDHash.end())
	{
		return it->second->GetImage(0);
	}
	return nullptr;
}

TVDImage* GetMapImage(int nFileIndex, int nImageIndex)
{
	char sBuf[1024] = {0};
	sprintf(sBuf,"%d",nFileIndex);
	std::string imgkey = sBuf;
	std::map<std::string,TVDImageDatas*>::iterator it;
	it = g_MapVDDHash.find(imgkey);
	TVDImageDatas* vdd = nullptr;
	if(it == g_MapVDDHash.end())
	{
		sprintf(sBuf,MAPIMAGEFILENAME,nFileIndex);
		//如果文件不存在，并且资源下载列表中没有，则加入资源下载列表
		//if not FileExists(sFileName) or g_resdownload.Exists(sFileName) then begin
		//	g_Resdownload.Add(sFileName);
		//exit;
		//end;
		std::string sFileName = sBuf;
		vdd = TVDImageDatas::Create(sFileName);
		vdd->Initialize();
		g_MapVDDHash[imgkey] = vdd;
		//std::string sFileName = 
	}
	it = g_MapVDDHash.find(imgkey);
	if(it != g_MapVDDHash.end())
	{
		return it->second->GetImage(0);
	}
	return nullptr;
}

void AddChangeFace(int recogid)
{
	g_ChangeFaceReadyList.push_back(recogid);
}
void DelChangeFace(int recogid)
{
	std::vector<int>::iterator it;
	for(it = g_ChangeFaceReadyList.begin();it != g_ChangeFaceReadyList.end();it++)
	{
		if(*it == recogid)
		{
			g_ChangeFaceReadyList.erase(it);
			break;
		}
	}
}
bool IsChangingFace(int recogid)
{
	std::vector<int>::iterator it;
	for(it = g_ChangeFaceReadyList.begin();it != g_ChangeFaceReadyList.end();it++)
	{
		if(*it == recogid)
		{
			return true;
		}
	}
	return false;
}

int GetOffset(int Appr)
{
	int nrace,npos;
	nrace = Appr / 10;
	npos = Appr % 10;
	return  npos * 1000;
}

TMonsterAction* GetRaceByPM(int race,unsigned short Appr)
{
	TMonsterAction* Result = nullptr;
	switch(race)
	{
	case RC_NPC:
		{
			if(Appr > 999)
			{
				Result =  &MANPC1000;
			}else
			{
				 Result = &MANPCDEF;
			}
			break;
		}
	case RC_ANIMAL:
		{
			Result = &MANPCDEF;
			break;
		}
	case RC_PLANT:
		{
			Result = &PLANT;
			break;
		}
	case RC_MINE:
		{
			Result = &MINEDEF;
			break;
		}
	case RC_MON0: 
	case 45: //弓箭手
		{
			Result = &MA0;
			break;
		}
	case 98: //皇宫城墙
		{
			Result = &MA27;
			break;
		}
	case RC_HORSE:
		{
			Result = &HORSE;
			break;
		}
	default:
		{
			Result = &MADEF;
		}
	}
	return Result;

}

void GetFrontPosition(int sx,int sy,int dir,int &newx,int &newy)
{
	newx  = sx;
	newy = sy;
	switch(dir)
	{
	case DR_UP:
		{
			newy--;
			break;
		}
	case DR_DOWN:
		{
			newy++;
			break;
		}
	case DR_LEFT:
		{
			newx--;
			break;
		}
	case DR_RIGHT:
		{
			newx ++;
			break;
		}
	case DR_UPLEFT:
		{
			newx--;
			newy--;
			break;
		}
	case DR_UPRIGHT:
		{
			newx++;
			newy--;
			break;
		}
	case DR_DOWNLEFT:
		{
			newx--;
			newy--;
			break;
		}
	case DR_DOWNRIGHT:
		{
			newx++;
			newy++;
			break;
		}
	}
}
void GetBackPosition(int sx,int sy,int dir,int &newx,int &newy)
{
	newx = sx;
	newy = sy;
	switch(dir)
	{
	case DR_UP:
		{
			newy++;
			break;
		}
	case DR_DOWN:
		{
			newy --;
			break;
		}
	case DR_LEFT:
		{
			newx ++;
			break;
		}
	case DR_RIGHT:
		{
			newx -- ;
			break;
		}
	case DR_UPLEFT:
		{
			newx++;
			newy ++;
			break;
		}
	case DR_UPRIGHT:
		{
			newx--;
			newy ++;
			break;
		}
	case DR_DOWNLEFT:
		{
			newx --;
			newy ++;
			break;
		}
	case DR_DOWNRIGHT:
		{
			newx--;
			newy--;
			break;
		}
	}
}
unsigned char GetNextDirection(int sx,int sy,int dx,int dy)
{
	int flagx;
	int flagy;
	unsigned char Result = DR_DOWN;
	if(sx < dx)
	{
		flagx = 1;
	}else if(sx == dx)
	{
		flagx = 0;
	}else flagx = -1;
	if(abs(sy - dy) > 2)
	{
		if(sx >= dx - 1 && sx <= dx + 1)
		{
			flagx = 0;
		}
	}
	if(sy < dy)
	{
		flagy = 1;
	}else if(sy == dy)
	{
		flagy = 0;
	}else flagy = -1;

	if(abs(sx - dx) > 2)
	{
		if(sy > dy - 1 && sy <= dy + 1)
		{
			flagy = 0;
		}
	}
	if(flagx == 0 && flagy == -1)
	{
		Result = DR_UP;
	}
	if (flagx == 1 && flagy == -1)
	{
		Result = DR_UPRIGHT;
	}

	if (flagx == 1 && flagy == 0)
	{
		Result = DR_RIGHT;
	}

	if (flagx == 1 && flagy == 1)
	{
		Result = DR_DOWNRIGHT;
	}

	if (flagx == 0 && flagy == 1) 
	{
		Result = DR_DOWN;
	}

	if (flagx == -1 && flagy == 1)
	{
		Result = DR_DOWNLEFT;
	}

	if (flagx == -1 && flagy == 0) 
	{
		Result = DR_LEFT;
	}

	if (flagx == -1 && flagy == -1)
	{
		Result = DR_UPLEFT;
	}
	return Result;
}


void GetNextPosXY(unsigned char dir,int &x,int &y)
{
	switch(dir)
	{
	case DR_UP:
		{
			y--;
			break;
		}
	case DR_UPRIGHT:
		{
			x++;y--;
			break;
		}
	case DR_RIGHT:
		{
			x++;
			break;
		}
	case DR_DOWNRIGHT:
		{
			x++;y++;
			break;
		}

	case DR_DOWN:
		{
			y++;
			break;
		}
	case DR_DOWNLEFT:
		{
			x--;y++;
			break;
		}
	case DR_LEFT:
		{
			x--;
			break;
		}
	case DR_UPLEFT:
		{
			x--;y--;
			break;
		}

	}
}
void GetNextRunXY(unsigned char dir,int &x,int &y)
{
	switch(dir)
	{
	case DR_UP:
		{
			y-=2;
			break;
		}
	case DR_UPRIGHT:
		{
			x+=2;y-=2;
			break;
		}
	case DR_RIGHT:
		{
			x+=2;
			break;
		}
	case DR_DOWNRIGHT:
		{
			x+=2;y+=2;
			break;
		}

	case DR_DOWN:
		{
			y+=2;
			break;
		}
	case DR_DOWNLEFT:
		{
			x-=2;y+=2;
			break;
		}
	case DR_LEFT:
		{
			x-=2;
			break;
		}
	case DR_UPLEFT:
		{
			x-=2;y-=2;
			break;
		}

	}
}
void GetNextHorseRunXY(unsigned char dir,int &x,int &y)
{
	switch(dir)
	{
	case DR_UP:
		{
			y -= 3;
			break;
		}
	case DR_UPRIGHT:
		{
			x += 3;y-=3;
			break;
		}
	case DR_RIGHT:
		{
			x+= 3;
			break;
		}
	case DR_DOWNRIGHT:
		{
			x+= 3;y+= 3;
			break;
		}

	case DR_DOWN:
		{
			y+= 3;
			break;
		}
	case DR_DOWNLEFT:
		{
			x-= 3;y+= 3;
			break;
		}
	case DR_LEFT:
		{
			x-= 3;
			break;
		}
	case DR_UPLEFT:
		{
			x-= 3;y-= 3;
			break;
		}

	}
}

bool IsStringNumber(const char* str)
{
	int n;
	bool Result = true;
	char p;
	if(strlen(str) > 1)
	{
		if(str[1] == '-' || str[1] == '+')
		{
			n = 2;
		}else n = 1;
		for( int i = 0;i < (int)strlen(str);i++)
		{
			p = str[i];
			if(p < '0' || p > '9')
			{
				Result = false;
				break;
			}
		}
	}else
	{
		for( int i = 0;i < (int)strlen(str);i++)
		{
			p = str[i];
			if(p < '0' || p > '9')
			{
				Result =  false;
				break;
			}
		}
	}
	return Result;
}



// 20111231 兼容传奇原有调色板
//delphi的颜色代码与android是不一样的.-
unsigned long g_MainPalette[256] ={
	0x000000FF,
	0x800000FF,
	0x008000FF,
	0x808000FF,
	0x000080FF,
	0x800080FF,
	0x008080FF,
	0xC0C0C0FF,
	0x558097FF,
	0x9DB9C8FF,
	0x7B7373FF,
	0x2D2929FF,
	0x5A5252FF,
	0x635A5AFF,
	0x423939FF,
	0x1D1818FF,
	0x181010FF,
	0x291818FF,
	0x100808FF,
	0xF27971FF,
	0xE1675FFF,
	0xFF5A5AFF,
	0xFF3131FF,
	0xD65A52FF,
	0x941000FF,
	0x942918FF,
	0x390800FF,
	0x731000FF,
	0xB51800FF,
	0xBD6352FF,
	0x421810FF,
	0xFFAA99FF,
	0x5A1000FF,
	0x733929FF,
	0xA54A31FF,
	0x947B73FF,
	0xBD5231FF,
	0x522110FF,
	0x7B3118FF,
	0x2D1810FF,
	0x8C4A31FF,
	0x942900FF,
	0xBD3100FF,
	0xC67352FF,
	0x6B3118FF,
	0xC66B42FF,
	0xCE4A00FF,
	0xA56339FF,
	0x5A3118FF,
	0x2A1000FF,
	0x150800FF,
	0x3A1800FF,
	0x080000FF,
	0x290000FF,
	0x4A0000FF,
	0x9D0000FF,
	0xDC0000FF,
	0xDE0000FF,
	0xFB0000FF,
	0x9C7352FF,
	0x946B4AFF,
	0x734A29FF,
	0x523118FF,
	0x8C4A18FF,
	0x884411FF,
	0x4A2100FF,
	0x211810FF,
	0xD6945AFF,
	0xC66B21FF,
	0xEF6B00FF,
	0xFF7700FF,
	0xA59484FF,
	0x423121FF,
	0x181008FF,
	0x291808FF,
	0x211000FF,
	0x392918FF,
	0x8C6339FF,
	0x422910FF,
	0x6B4218FF,
	0x7B4A18FF,
	0x944A00FF,
	0x8C847BFF,
	0x6B635AFF,
	0x4A4239FF,
	0x292118FF,
	0x463929FF,
	0xB5A594FF,
	0x7B6B5AFF,
	0xCEB194FF,
	0xA58C73FF,
	0x8C735AFF,
	0xB59473FF,
	0xD6A573FF,
	0xEFA54AFF,
	0xEFC68CFF,
	0x7B6342FF,
	0x6B5639FF,
	0xBD945AFF,
	0x633900FF,
	0xD6C6ADFF,
	0x524229FF,
	0x946318FF,
	0xEFD6ADFF,
	0xA58C63FF,
	0x635A4AFF,
	0xBDA57BFF,
	0x5A4218FF,
	0xBD8C31FF,
	0x353129FF,
	0x948463FF,
	0x7B6B4AFF,
	0xA58C5AFF,
	0x5A4A29FF,
	0x9C7B39FF,
	0x423110FF,
	0xEFAD21FF,
	0x181000FF,
	0x292100FF,
	0x9C6B00FF,
	0x94845AFF,
	0x524218FF,
	0x6B5A29FF,
	0x7B6321FF,
	0x9C7B21FF,
	0xDEA500FF,
	0x5A5239FF,
	0x312910FF,
	0xCEBD7BFF,
	0x635A39FF,
	0x94844AFF,
	0xC6A529FF,
	0x109C18FF,
	0x428C4AFF,
	0x318C42FF,
	0x109429FF,
	0x081810FF,
	0x081818FF,
	0x082910FF,
	0x184229FF,
	0xA5B5ADFF,
	0x6B7373FF,
	0x182929FF,
	0x18424AFF,
	0x31424AFF,
	0x63C6DEFF,
	0x44DDFFFF,
	0x8CD6EFFF,
	0x736B39FF,
	0xF7DE39FF,
	0xF7EF8CFF,
	0xF7E700FF,
	0x6B6B5AFF,
	0x5A8CA5FF,
	0x39B5EFFF,
	0x4A9CCEFF,
	0x3184B5FF,
	0x31526BFF,
	0xDEDED6FF,
	0xBDBDB5FF,
	0x8C8C84FF,
	0xF7F7DEFF,
	0x000818FF,
	0x081839FF,
	0x081029FF,
	0x081800FF,
	0x082900FF,
	0x0052A5FF,
	0x007BDEFF,
	0x10294AFF,
	0x10396BFF,
	0x10528CFF,
	0x215AA5FF,
	0x10315AFF,
	0x104284FF,
	0x315284FF,
	0x182131FF,
	0x4A5A7BFF,
	0x526BA5FF,
	0x293963FF,
	0x104ADEFF,
	0x292921FF,
	0x4A4A39FF,
	0x292918FF,
	0x4A4A29FF,
	0x7B7B42FF,
	0x9C9C4AFF,
	0x5A5A29FF,
	0x424214FF,
	0x393900FF,
	0x595900FF,
	0xCA352CFF,
	0x6B7321FF,
	0x293100FF,
	0x313910FF,
	0x313918FF,
	0x424A00FF,
	0x526318FF,
	0x5A7329FF,
	0x314A18FF,
	0x182100FF,
	0x183100FF,
	0x183910FF,
	0x63844AFF,
	0x6BBD4AFF,
	0x63B54AFF,
	0x63BD4AFF,
	0x5A9C4AFF,
	0x4A8C39FF,
	0x63C64AFF,
	0x63D64AFF,
	0x52844AFF,
	0x317329FF,
	0x63C65AFF,
	0x52BD4AFF,
	0x10FF00FF,
	0x182918FF,
	0x4A884AFF,
	0x4AE74AFF,
	0x005A00FF,
	0x008800FF,
	0x009400FF,
	0x00DE00FF,
	0x00EE00FF,
	0x00FB00FF,
	0x4A5A94FF,
	0x6373B5FF,
	0x7B8CD6FF,
	0x6B7BD6FF,
	0x7788FFFF,
	0xC6C6CEFF,
	0x94949CFF,
	0x9C94C6FF,
	0x313139FF,
	0x291884FF,
	0x180084FF,
	0x4A4252FF,
	0x52427BFF,
	0x635A73FF,
	0xCEB5F7FF,
	0x8C7B9CFF,
	0x7722CCFF,
	0xDDAAFFFF,
	0xF0B42AFF,
	0xDF009FFF,
	0xE317B3FF,
	0xFFFBF0FF,
	0xA0A0A4FF,
	0x808080FF,
	0xFF0000FF,
	//0x00FF00FF,
	0xFF00FF00,
	0xFFFF00FF,
	//0x0000FFFF,
	0xFF0000FF,
	0xFF00FFFF,
	0x00FFFFFF,
	0xFFFFFFFF
};
//unsigned long g_MainPalette[256]={
//	0xFF000000,
//	0xFF800000,
//	0xFF008000,
//	0xFF808000,
//	0xFF000080,
//	0xFF800080,
//	0xFF008080,
//	0xFFC0C0C0,
//	0xFF558097,
//	0xFF9DB9C8,
//	0xFF7B7373,
//	0xFF2D2929,
//	0xFF5A5252,
//	0xFF635A5A,
//	0xFF423939,
//	0xFF1D1818,
//	0xFF181010,
//	0xFF291818,
//	0xFF100808,
//	0xFFF27971,
//	0xFFE1675F,
//	0xFFFF5A5A,
//	0xFFFF3131,
//	0xFFD65A52,
//	0xFF941000,
//	0xFF942918,
//	0xFF390800,
//	0xFF731000,
//	0xFFB51800,
//	0xFFBD6352,
//	0xFF421810,
//	0xFFFFAA99,
//	0xFF5A1000,
//	0xFF733929,
//	0xFFA54A31,
//	0xFF947B73,
//	0xFFBD5231,
//	0xFF522110,
//	0xFF7B3118,
//	0xFF2D1810,
//	0xFF8C4A31,
//	0xFF942900,
//	0xFFBD3100,
//	0xFFC67352,
//	0xFF6B3118,
//	0xFFC66B42,
//	0xFFCE4A00,
//	0xFFA56339,
//	0xFF5A3118,
//	0xFF2A1000,
//	0xFF150800,
//	0xFF3A1800,
//	0xFF080000,
//	0xFF290000,
//	0xFF4A0000,
//	0xFF9D0000,
//	0xFFDC0000,
//	0xFFDE0000,
//	0xFFFB0000,
//	0xFF9C7352,
//	0xFF946B4A,
//	0xFF734A29,
//	0xFF523118,
//	0xFF8C4A18,
//	0xFF884411,
//	0xFF4A2100,
//	0xFF211810,
//	0xFFD6945A,
//	0xFFC66B21,
//	0xFFEF6B00,
//	0xFFFF7700,
//	0xFFA59484,
//	0xFF423121,
//	0xFF181008,
//	0xFF291808,
//	0xFF211000,
//	0xFF392918,
//	0xFF8C6339,
//	0xFF422910,
//	0xFF6B4218,
//	0xFF7B4A18,
//	0xFF944A00,
//	0xFF8C847B,
//	0xFF6B635A,
//	0xFF4A4239,
//	0xFF292118,
//	0xFF463929,
//	0xFFB5A594,
//	0xFF7B6B5A,
//	0xFFCEB194,
//	0xFFA58C73,
//	0xFF8C735A,
//	0xFFB59473,
//	0xFFD6A573,
//	0xFFEFA54A,
//	0xFFEFC68C,
//	0xFF7B6342,
//	0xFF6B5639,
//	0xFFBD945A,
//	0xFF633900,
//	0xFFD6C6AD,
//	0xFF524229,
//	0xFF946318,
//	0xFFEFD6AD,
//	0xFFA58C63,
//	0xFF635A4A,
//	0xFFBDA57B,
//	0xFF5A4218,
//	0xFFBD8C31,
//	0xFF353129,
//	0xFF948463,
//	0xFF7B6B4A,
//	0xFFA58C5A,
//	0xFF5A4A29,
//	0xFF9C7B39,
//	0xFF423110,
//	0xFFEFAD21,
//	0xFF181000,
//	0xFF292100,
//	0xFF9C6B00,
//	0xFF94845A,
//	0xFF524218,
//	0xFF6B5A29,
//	0xFF7B6321,
//	0xFF9C7B21,
//	0xFFDEA500,
//	0xFF5A5239,
//	0xFF312910,
//	0xFFCEBD7B,
//	0xFF635A39,
//	0xFF94844A,
//	0xFFC6A529,
//	0xFF109C18,
//	0xFF428C4A,
//	0xFF318C42,
//	0xFF109429,
//	0xFF081810,
//	0xFF081818,
//	0xFF082910,
//	0xFF184229,
//	0xFFA5B5AD,
//	0xFF6B7373,
//	0xFF182929,
//	0xFF18424A,
//	0xFF31424A,
//	0xFF63C6DE,
//	0xFF44DDFF,
//	0xFF8CD6EF,
//	0xFF736B39,
//	0xFFF7DE39,
//	0xFFF7EF8C,
//	0xFFF7E700,
//	0xFF6B6B5A,
//	0xFF5A8CA5,
//	0xFF39B5EF,
//	0xFF4A9CCE,
//	0xFF3184B5,
//	0xFF31526B,
//	0xFFDEDED6,
//	0xFFBDBDB5,
//	0xFF8C8C84,
//	0xFFF7F7DE,
//	0xFF000818,
//	0xFF081839,
//	0xFF081029,
//	0xFF081800,
//	0xFF082900,
//	0xFF0052A5,
//	0xFF007BDE,
//	0xFF10294A,
//	0xFF10396B,
//	0xFF10528C,
//	0xFF215AA5,
//	0xFF10315A,
//	0xFF104284,
//	0xFF315284,
//	0xFF182131,
//	0xFF4A5A7B,
//	0xFF526BA5,
//	0xFF293963,
//	0xFF104ADE,
//	0xFF292921,
//	0xFF4A4A39,
//	0xFF292918,
//	0xFF4A4A29,
//	0xFF7B7B42,
//	0xFF9C9C4A,
//	0xFF5A5A29,
//	0xFF424214,
//	0xFF393900,
//	0xFF595900,
//	0xFFCA352C,
//	0xFF6B7321,
//	0xFF293100,
//	0xFF313910,
//	0xFF313918,
//	0xFF424A00,
//	0xFF526318,
//	0xFF5A7329,
//	0xFF314A18,
//	0xFF182100,
//	0xFF183100,
//	0xFF183910,
//	0xFF63844A,
//	0xFF6BBD4A,
//	0xFF63B54A,
//	0xFF63BD4A,
//	0xFF5A9C4A,
//	0xFF4A8C39,
//	0xFF63C64A,
//	0xFF63D64A,
//	0xFF52844A,
//	0xFF317329,
//	0xFF63C65A,
//	0xFF52BD4A,
//	0xFF10FF00,
//	0xFF182918,
//	0xFF4A884A,
//	0xFF4AE74A,
//	0xFF005A00,
//	0xFF008800,
//	0xFF009400,
//	0xFF00DE00,
//	0xFF00EE00,
//	0xFF00FB00,
//	0xFF4A5A94,
//	0xFF6373B5,
//	0xFF7B8CD6,
//	0xFF6B7BD6,
//	0xFF7788FF,
//	0xFFC6C6CE,
//	0xFF94949C,
//	0xFF9C94C6,
//	0xFF313139,
//	0xFF291884,
//	0xFF180084,
//	0xFF4A4252,
//	0xFF52427B,
//	0xFF635A73,
//	0xFFCEB5F7,
//	0xFF8C7B9C,
//	0xFF7722CC,
//	0xFFDDAAFF,
//	0xFFF0B42A,
//	0xFFDF009F,
//	0xFFE317B3,
//	0xFFFFFBF0,
//	0xFFA0A0A4,
//	0xFF808080,
//	0xFFFF0000,
//	0xFF00FF00,
//	0xFFFFFF00,
//	0xFF0000FF,
//	0xFFFF00FF,
//	0xFF00FFFF,
//	0xFFFFFFFF
//};


unsigned char WORDER[2][3000] = { {   0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, /*{0..79}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{80..159}*/
	//未知动作{5张图片}
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, /*{160..239}*/
	//未知动作{5张图片}
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, /*{240..319}*/
	//挡(1张图)
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, /*{320..399}*/
	//未知动作(1张图)
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, /*{400..479}*/
	//未知动作(1张图)
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, /*{480..559}*/
	//准备攻击(3张图)
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, /*{560..639}*/
	//掏肉动作(2张图)
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{640..719}*/
	//攻击
	1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, /*{720..799}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{800..879}*/
	//未知动作(6张图片)
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{880..959}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{960..1039}*/
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{1040..1119}*/
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{1020..1199}*/
	//后仰
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, /*{1200..1279}*/
	//未知动作(10图片)
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{1280..1359}*/
	//未知动作(10图片)
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{1360..1439}*/
	//踢腿动作(10图片)
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{1440..1519}*/
	//死亡动作(10图片)
	0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, /*{1520..1599}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{1600..1679}*/
	//走路
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, /*{1680..1759}*/

	//跑
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, /*{1760..1839}*/
	//刺客跑
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, /*{1840..1919}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{1920..1999}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2000..2079}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2080..2159}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2160..2239}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2240..2319}*/
	//骑马不动
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2320..2399}*/
	//骑马走
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2400..2479}*/
	//骑马跑
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2480..2559}*/
	//马上后仰
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2560..2639}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2640..2719}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2720..2799}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2800..2879}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{2880..2959}*/
	//空图片
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 /*{2960..2999}*/},
{
	//站立
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,  /*{0..79}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{80..159}*/
		//未知动作{5张图片}
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,  /*{160..239}*/
		//未知动作{5张图片}
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,  /*{240..319}*/
		//挡(1张图)
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,  /*{320..399}*/
		//未知动作(1张图)
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,  /*{400..479}*/
		//未知动作(1张图)
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1,  /*{480..559}*/
		//准备攻击(3张图)
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,  /*{560..639}*/
		//掏肉动作(2张图)
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{640..719}*/
		//攻击
		1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1,  /*{720..799}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{800..879}*/
		//未知动作(6张图片)
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{880..959}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{960..1039}*/
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /*{1040..1119}*/
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{1020..1199}*/
		//后仰
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,  /*{1200..1279}*/
		//未知动作(10图片)
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{1280..1359}*/
		//未知动作(10图片)
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{1360..1439}*/
		//踢腿动作(10图片)
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{1440..1519}*/
		//死亡动作(10图片)
		0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,
		0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1,  /*{1520..1599}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{1600..1679}*/
		//走路
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,  /*{1680..1759}*/

		//跑
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,  /*{1760..1839}*/
		//刺客跑
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 0, 0, 1, 1, 1,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,  /*{1840..1919}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{1920..1999}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2000..2079}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2080..2159}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2160..2239}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2240..2319}*/
		//骑马不动
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, /* {2320..2399}*/
		//骑马
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2400..2479}*/
		//骑马
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2480..2559}*/
		//马上后仰
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2560..2639}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2640..2719}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2720..2799}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2800..2879}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  /*{2880..2959}*/
		//空图片
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
		0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 /*{2960..2999}*/}};


		unsigned long GetRGB(unsigned char c256)
		{
			return g_MainPalette[c256];
		}


		void SetRandomSeed()
		{
			//time_t tt;
			//time(&tt);
			//struct tm * now;
			//now = localtime(&tt);
			//
			//timeval tv;
	
			//
			//CCTime::gettimeofdayCocos2d(&tv,NULL);
			//unsigned long reed = tv.tv_sec*1000+tv.tv_usec/1000;
			//srand(reed);
		}
		int Random_Int(int start,int end)
		{
			return CCRANDOM_0_1()*(end-start)+start;
		}
		float Random_Float(float start,float end)
		{
			return CCRANDOM_0_1()*(end-start)+start;
		}


		int GetFlyDirection16(int sx,int sy,int ttx,int tty)
		{
			int Result;
			int fx,fy;
			fx = ttx - sx;
			fy = tty - sy;
			sx = 0;
			sy = 0;
			Result = 0;
			if(fx == 0)
			{
				if(fy < 0)
				{
					Result = 0;
				}else Result = 8;
				return Result;
			}
			if(fy == 0)
			{
				if(fx < 0)
				{
					Result = 12;
				}else Result = 4;
				return Result;
			}
			if(fx > 0 && fy < 0)
			{
				Result = 4;
				if(-fy > fx / 4)Result = 3;
				if(-fy > fx / 1.9)Result = 2;
				if(-fy > fx * 1.4)Result = 1;
				if(-fy > fx * 4)Result = 0;

			}
			if(fx > 0 && fy > 0)
			{
				Result = 4;
				if(fy > fx / 4) Result = 5;
				if(fy > fx / 1.9) Result = 6;
				if(fy > fx * 1.4) Result = 7;
				if(fy > fx * 4)Result = 8;
			}
			if(fx < 0 && fy > 0)
			{
				Result = 12;
				if(fy > -fx / 4) Result = 11;
				if(fy > -fx / 1.9) Result = 10;
				if(fy > -fx * 1.4) Result = 9;
				if(fy > -fx * 4) Result = 8;
			}
			if(fx < 0 && fy < 0)
			{
				Result = 12;
				if(-fy > -fx /4)Result = 13;
				if(-fy > -fx / 1.9) Result = 14;
				if(-fy > -fx * 1.4) Result = 15;
				if(-fy > -fx *4) Result = 0;
			}
			return Result;
		}


		TVDImage* GetEffectImage(int mag,int idx,int &nx,int &ny)
		{
			TVDImageDatas* vdds = GetEffectBase(mag,1);
			TVDImage* result = nullptr;
			if(vdds)
			{
				result = vdds->GetImage(idx);
				if(result)
				{
					nx = result->nx;
					ny = result->ny;
				}
			}
			return result;
		}

		std::string randomName(unsigned char gend)
		{
			
			std::vector<std::string> xing = split_String(g_xing,",");
			std::string str  = xing[Random_Int(0,(int)xing.size()-1)];
			if(gend == 0)
			{
				std::vector<std::string> nanming =split_String(g_nanming,",");
				std::vector<std::string> nanzi = split_String(g_nanzi,",");
				str += nanming[Random_Int(0,(int)nanming.size()-1)] + nanzi[Random_Int(0,(int)nanzi.size()-1)];
			}else
			{
				std::vector<std::string> nvming =split_String(g_nvming,",");
				std::vector<std::string> nvzi = split_String(g_nvzi,",");
				str += nvming[Random_Int(0,(int)nvming.size()-1)] + nvzi[Random_Int(0,(int)nvzi.size()-1)];
			}
		
			return str;
		}

		std::string IntToJob(unsigned char btJob)
		{
			std::string ret = "未知";
			switch(btJob)
			{
			case 0:
				{
					ret = "战士";
					break;
				}
			case 1:
				{
					ret = "法师";
					break;
				}
			case 2:
				{
					ret = "道士";
					break;
				}
			}
			return ret;
		}
		std::string IntToSex(unsigned char btSex)
		{
			std::string ret = "未知";
			switch(btSex)
			{
			case 0:
				{
					ret = "男";
					break;
				}
			case 1:
				{
					ret = "女";
					break;
				}
			}
			return ret;
		}

		std::vector<std::string> split_String( std::string str, std::string pattern)
		{

			std::vector<std::string> ret;

			if(pattern.empty()) return ret;

			size_t start=0,index=str.find_first_of(pattern,0);

			while(index!=str.npos)

			{

				if(start!=index)

					ret.push_back(str.substr(start,index-start));

				start=index+1;

				index=str.find_first_of(pattern,start);

			}

			if(!str.substr(start).empty())

				ret.push_back(str.substr(start));

			return ret;

		}

		std::string StringUpper(const char* pStr)
		{
			int nSize = (int)strlen(pStr);
			if(nSize <= 0)return "";
			char* pData = new char[nSize + 1];
			memset(pData,0,nSize);
			for(int i = 0;i < nSize;i++)
			{
				pData[i] = toupper(pStr[i]);
			}
			pData[nSize] = 0;
			std::string ret = pData;
			delete []pData;
			return ret;
		}

		std::string StringToLower(const char* pStr)
		{
			int nSize = (int)strlen(pStr);
			if(nSize <= 0)return "";
			char* pData = new char[nSize + 1];
			memset(pData,0,nSize);
			for(int i = 0;i < nSize;i++)
			{
				pData[i] = tolower(pStr[i]);
			}
			pData[nSize] = 0;
			std::string ret = pData;
			delete []pData;
			return ret;
		}

		void StringReplace(std::string&s1,const std::string&s2,const std::string&s3)
		{
			std::string::size_type pos=0;
			std::string::size_type a=s2.size();
			std::string::size_type b=s3.size();
			while((pos=s1.find(s2,pos))!=std::string::npos)
			{
				s1.replace(pos,a,s3);
				pos+=b;
			}
		}

		TStdItem* GetStdItemInfo(std::string sName)
		{
			TStdItem* stditem = nullptr;
			for(int i = 0;i < (int)g_StdItemList.size();i++)
			{
				stditem = g_StdItemList[i];
				if(strcmp(sName.c_str(),stditem->Name) == 0)
				{
					break;
				}
			}
			return stditem;
		}
		TStdItem* GetStdItemInfo(int nIdx)
		{
			int n;
			TStdItem* pitm,*pitem;
			pitm = nullptr;
			n = nIdx - 1;
			///先根据编号作为索引尝试一下
			if(n >= 0 && n < (int)g_StdItemList.size())
			{
				pitem = g_StdItemList[n];
				if(pitem->ID == n)
				{
					pitm = g_StdItemList[n];
				}
			}
			//没找到就试试逐个检索一遍
			if(pitm == nullptr)
			{
				for(int i = 0;i < (int)g_StdItemList.size();i++)
				{
					pitem = g_StdItemList[0];
					if(pitem->ID == n)
					{
						pitm = g_StdItemList[n];
						break;
					}
				}
			}

			return pitm;
		}

		cocos2d::Color4B HexColorToColor4B(unsigned long color)
		{
			Color4B ret;
			ret.r = color & 0xff;
			ret.g = (color>>8) & 0xff;
			ret.b = (color>> 16) & 0xff;
			ret.a = color >> 24 & 0xff;
			return ret;
		}

		//检测包裹是否已满
		bool CheckBagFulll()
		{
			int n;
			bool ret;
		//	if(GetTickCount() > g_CheckBagFullTick)
		//	{
				n = 0; 
				for(int i = 0;i < MAXBAGITEMS;i++)
				{
					if(strlen((const char*)&g_ItemArr[i].s.Name[0]) > 0) n++;
				}
				
				ret = n >= MAXBAGITEMS;
			//	g_CheckBagFullTick = GetTickCount();
			//}
			return ret;
		}
		//取物品的附属属性 添加值
		void GetItemAddValueFun(TUserItem* UserItem,TStdItem* StdItem)
		{
			switch(StdItem->StdMode)	//武器
			{
			case 5:
			case 6:
				{
					StdItem->DC2 += UserItem->btValue[0];
					StdItem->MC2 += UserItem->btValue[1];
					StdItem->SC2 += UserItem->btValue[2];
					StdItem->AC += UserItem->btValue[3];
					StdItem->AC2 += UserItem->btValue[5];    //加准确
					StdItem->MAC +=  UserItem->btValue[4];
					StdItem->MAC2 += UserItem->btValue[6];  //加攻击速度
					if (UserItem->btValue[7] - 1 < 10 ) //神圣
					{
						StdItem->Source = UserItem->btValue[7];
					}
					  //祈灵到的准确和攻击速度 攻魔道
					if(UserItem->btValue[9] > 0)
					{
						if(StdItem->MAC2 > 10)
						{
							StdItem->MAC2 += UserItem->btValue[9]; //加攻击速度				
						}else if(StdItem->MAC2 > 0)
						{
							StdItem->MAC2 = StdItem->MAC2 - UserItem->btValue[9]; //加攻击速度
							if(StdItem->MAC2 < 0)StdItem->MAC2 = abs(StdItem->MAC2) + 10;
						}else
						{
							StdItem->MAC2 = UserItem->btValue[9] + 10;
						}

						StdItem->AC2 += UserItem->btValue[10];
						StdItem->DC2 += UserItem->btValue[11];
						StdItem->MC2 += UserItem->btValue[11];
						StdItem->SC2 +=  UserItem->btValue[11];
					}
					

					break;
				}
			case 7:
			case 10:
			case 11:
			case 13:
				{
					if(StdItem->StdMode  == 7)break;
					StdItem->AC2 +=  UserItem->btValue[0];
					StdItem->MAC2 += UserItem->btValue[1];
					StdItem->DC2 +=  UserItem->btValue[2];
					StdItem->MC2 +=  UserItem->btValue[3];
					StdItem->SC2 += UserItem->btValue[4];
					//祈灵得到的物防魔防 攻魔道
					StdItem->AC2 +=  UserItem->btValue[9];
					StdItem->MAC2 += UserItem->btValue[10];
					StdItem->DC2 += UserItem->btValue[11];
					StdItem->MC2 += UserItem->btValue[11];
					StdItem->SC2 += UserItem->btValue[11];
					break;
				}
			case 15:
			case 19:
			case 20:
			case 21:
			case 22:
			case 23:
			case 24:
			case 26:
			case 51:
			case 52:
			case 53:
			case 54:
			case 62:
			case 63:
			case 64:
			case 30:
				{
					StdItem->AC2 += UserItem->btValue[0];
					StdItem->MAC2 +=  UserItem->btValue[1];
					StdItem->DC2 +=  UserItem->btValue[2];
					StdItem->MC2 += UserItem->btValue[3];
					StdItem->SC2 += UserItem->btValue[4];
					if (UserItem->btValue[5] > 0)
						StdItem->Need = UserItem->btValue[5];
					
					if (UserItem->btValue[6] > 0)
						StdItem->NeedLevel = UserItem->btValue[6];
					break;
				}
			case 100:
			case 101:
			case 102:
			case 103:
			case 104:
				{
					if(StdItem->StdMode == 7)break;
					StdItem->AC2 += UserItem->btValue[0];
					StdItem->MAC2 += UserItem->btValue[1];
					StdItem->DC2 +=  UserItem->btValue[2];
					StdItem->MC2 +=UserItem->btValue[3];
					StdItem->SC2 += UserItem->btValue[4];
					//祈灵得到的物防魔防 攻魔道
					StdItem->AC2 += UserItem->btValue[9];
					StdItem->MAC2 += UserItem->btValue[10];
					StdItem->DC2 += UserItem->btValue[11];
					StdItem->MC2 += UserItem->btValue[11];
					StdItem->SC2 +=  UserItem->btValue[11];
					break;
				}
			}
		}

		bool AddItemBag(TClientItem cu)
		{
			int nLen = (int)cu.s.Name;
			if(nLen<= 0)return false;
			//有同一个物品，覆盖
			for(int i = 0;i < MAXBAGITEMS;i++)
			{
				if(g_ItemArr[i].MakeIndex == cu.MakeIndex
					&& strcmp((const char*)&g_ItemArr[i].s.Name,(const char*)&cu.s.Name) == 0)
				{
					memcpy(&g_ItemArr[i],&cu,sizeof(TClientItem));
					return true;
				}
			}
			//找个空位放进去
			for(int i = 0;i < MAXBAGITEMS;i++)
			{
				nLen = (int)strlen((char*)g_ItemArr[i].s.Name);
				if(nLen <= 0)
				{
					memcpy(&g_ItemArr[i],&cu,sizeof(TClientItem));
					return true;
				}
			}
			return false;
			ArrangeItemBag();
		}
		bool UpdateItemBag(TClientItem cu)
		{
			std::string sName;
			std::string sSrcName = cu.s.Name;
			for(int i = 0;i < MAXBAGITEMS;i++)
			{
				sName = g_ItemArr[i].s.Name;
				if(sName== sSrcName && g_ItemArr[i].MakeIndex == cu.MakeIndex)
				{
					g_ItemArr[i] = cu;
					return true;
				}
			}
			return false;
		}
		void ArrangeItemBag()
		{
			int nLen;
			for(int i = 0;i < MAXBAGITEMS;i++)
			{
				nLen = (int)strlen((char*)g_ItemArr->s.Name);
				for(int k = i + 1; k < MAXBAGITEMS;k++)
				{
					if(strcmp((const char*)&g_ItemArr[i].s.Name,(const char*)&g_ItemArr[k].s.Name) == 0 &&
						g_ItemArr[i].MakeIndex == g_ItemArr[k].MakeIndex)
					{
						memset(&g_ItemArr[k],0,sizeof(TClientItem));
					}
					//if(strchr((char*)g_ItemArr[i].s.Name,(char*)g_ItemArr[l].s.Name) &&
					//	g_ItemArr[i].MakeIndex == g_ItemArr[k].MakeIndex)
					//{
					//	
					//}
					//If (g_ItemArr[I].S.Name = g_MovingItem.Item.S.Name) And (g_ItemArr[I].MakeIndex = g_MovingItem.Item.MakeIndex) Then
					//	Begin
					//	g_MovingItem.Index := 0;
					//g_MovingItem.Item.S.Name := '';
					//End;
				}

			}
		}

		std::string GetDuraStr(int Dura,int DuraMax)
		{
			char sRet[1024]={0};
			sprintf(sRet,"%d/%d",(int)Dura / 1000,(int)DuraMax / 1000);
			std::string s = sRet;
			return sRet;
		}

		std::string GetDura100Str(int Dura,int DuraMax)
		{
			char sRet[1024]={0};
			sprintf(sRet,"%d/%d",(int)Dura / 100,(int)DuraMax / 1000);
			std::string s = sRet;
			return sRet;
		}
		bool GetHorseNeedStr(std::string &returnstr)
		{
			bool result = false;
			returnstr = "";
			char sRet[1024]={0};
			switch(g_MouseItem.s.Need)
			{
			case 0:
				{
					if(g_MouseItem.s.NeedLevel > 100)
					{
						if(g_MySelf->m_Abil.Level >= g_MouseItem.s.NeedLevel- 100)
						{
							result =  true;
							sprintf(sRet,"所需宠物等级%d(高级物品)",(int)g_MouseItem.s.NeedLevel -100);
							returnstr = sRet;
						}else
						{
							if(g_MySelf->m_Abil.Level >= g_MouseItem.s.NeedLevel)
							{
								result = true;
								sprintf(sRet,"所需宠物等级%d",g_MouseItem.s.NeedLevel);
								returnstr = sRet;
							}
						}
					}
					break;
				}

			}
			return result;
		}

		bool GetNeedStr(std::string returnstr)
		{
			bool result  =false;
			returnstr = "";
			char sRet[1024]={0};
			switch(g_MouseItem.s.Need)
			{
			case 0:
				{
					if(g_MouseItem.s.NeedLevel > 100)
					{
						if(g_MySelf->m_Abil.Level >= g_MouseItem.s.NeedLevel - 100)
						{
							result = true;
							sprintf(sRet,"所需等级%d(高级物品)",(int)g_MouseItem.s.NeedLevel - 100);
							returnstr = sRet;
						}else
						{
							if(g_MySelf->m_Abil.Level >= g_MouseItem.s.NeedLevel)
							{
								result = true;
								sprintf(sRet,"所需等级: %d",g_MouseItem.s.NeedLevel);
								returnstr = sRet;
							}
						}
					}
					break;
				}
			case 1:
				{
					if(g_MySelf->m_Abil.DC2 >= g_MouseItem.s.NeedLevel)
					{
						result = true;
						sprintf(sRet,"需要破坏力：%d",g_MouseItem.s.NeedLevel);
						returnstr = sRet;
					}
					break;
				}
			case 2:
				{
					if(g_MySelf->m_Abil.MC2 >= g_MouseItem.s.NeedLevel)
					{
						result = true;
						sprintf(sRet,"需要魔法力(自然系): %d",g_MouseItem.s.NeedLevel);
					}
					break;
				}
			case 3:
				{
					if(g_MySelf->m_Abil.SC2 >= g_MouseItem.s.NeedLevel)
					{
						result =true;
						sprintf(sRet,"需要魔法力(灵魂系): %d",g_MouseItem.s.NeedLevel);
						returnstr = sRet;
					}
					break;
				}
			case 4:
				{
					result = true;
					sprintf(sRet,"所需转生等级: %d",g_MouseItem.s.NeedLevel);
					returnstr = sRet;
					break;
				}
			case 5:
				{
					result = true;
					sprintf(sRet,"所需境界等级: %d",g_MouseItem.s.NeedLevel);
					returnstr = sRet;
					break;
				}
			case 6:
				{
					result = true;
					returnstr= "行会成员专用";
					break;
				}
			case 7:
				{
					result = true;
					returnstr = "沙城成员专用";
					break;
				}
			case 8:
				{
					result = true;
					returnstr ="会员专用";
					break;
				}
			case 40:
				{
					result = true;
					sprintf(sRet,"所需转生等级: %d\\所需等级: %d",
						LOWORD_(g_MouseItem.s.NeedLevel),HIWORD_(g_MouseItem.s.NeedLevel));
					returnstr = sRet;
					break;
				}
			case 41:
				{
					result =true;
					sprintf(sRet,"所需转生: %d\\所需攻击力: %d",
						LOWORD_(g_MouseItem.s.NeedLevel),HIWORD_(g_MouseItem.s.NeedLevel));
					returnstr = sRet;
					break;
				}
			case 42:
				{
					result = true;
					sprintf(sRet,"所需转生: %d\\魔法力: %d",
						LOWORD_(g_MouseItem.s.NeedLevel),HIWORD_(g_MouseItem.s.NeedLevel));
					returnstr = sRet;
					break;
				}
			case 43:
				{
					result = true;
					sprintf(sRet,"所需转生: %d\\道术: %d",
						LOWORD_(g_MouseItem.s.NeedLevel),HIWORD_(g_MouseItem.s.NeedLevel));
					returnstr = sRet;
					break;
				}
			case 44:
				{
					result = true;
					sprintf(sRet,"所需转生: %d\\境界等级: %d",
						LOWORD_(g_MouseItem.s.NeedLevel),HIWORD_(g_MouseItem.s.NeedLevel));
					returnstr = sRet;
					break;
				}
			case 60:
				{
					result = true;
					returnstr = "行会掌门专用";
					break;
				}
			case 70:
				{
					result = true;
					returnstr ="沙城城主专用";
					break;
				}
			case 81:
			case 82:
				{
					result = true;
					sprintf(sRet,"会员类型 =%d 会员等级 >= %d",LOWORD_(g_MouseItem.s.NeedLevel),
						HIWORD_(g_MouseItem.s.NeedLevel));
					returnstr = sRet;
					break;
				}


			}
			return result;
		}

		std::string GetItemQualityName(TStdItem* stditem)
		{
			std::string name ="";
			std::string color ="";
			color = GetItemQualityColor(stditem);
			char sRet[1024];
			sprintf(sRet,"[color:%s]%s[/color]",color.c_str(),stditem->Name);
			name = sRet;
			return name;
		}
		std::string GetItemQualityColor(TStdItem* stditem)
		{
			TAdditionItem* additem;
			std::string color = "0xffffffff";
			std::string sName = stditem->Name;
			additem  = GetAdditionItemInfo(sName);
			if(!additem)return color;
			switch (additem->quality)
			{
				case 1:color = "FF989897"; break;  //灰色(劣质\垃圾)
				case 2: color = "FFFFFFFF"; break;   //灰色(劣质\垃圾)
				case 3: color ="FF00FF2A"; break;   //绿色(低级\优秀)
				case 4: color = "FF0078FF"; break;   //蓝色(中级\精良)
				case 5: color = "FF9000FF"; break;   //  紫色(高级\史诗)，
				case 6: color = "FFFF7800"; break;  //橙色(极品\传说)，
				case 7: color = "FFFF0000";  break;  //红色(特殊\稀有)
			}
			return color;
		}

		TAdditionItem* GetAdditionItemInfo(std::string sName)
		{
			std::map<std::string,TAdditionItem*>::iterator it;
			it = g_AdditionItemList.find(sName);
			if(it == g_AdditionItemList.end()) return nullptr;
			return  it->second;
		}

		void ClientItem2UserItem(TClientItem* citem,TUserItem* uitem)
		{
			uitem->MakeIndex = citem->MakeIndex;
			uitem->wIndex = citem->s.ID + 1;
			uitem->Dura = citem->Dura;
			uitem->DuraMax = citem->DuraMax;
			memcpy(&citem->btValue,&uitem->btValue,sizeof(citem->btValue));
		}
		void GetMouseItemMosaicInfo(std::string &sstr)
		{
			TUserItem useitem;
			int MID = 0;
			TStdItem* pmitem = nullptr;
			int nHoleCount = 0,nOpenHoleCount = 0;
			
			ClientItem2UserItem(&g_MouseItem,&useitem);
			nHoleCount = GetItemHoleCount(&useitem);
			nOpenHoleCount = GetItemOpenHoleCount(&useitem);
			char sChar[1024]={0};
			if(nOpenHoleCount > 0)
			{
				sprintf(sChar,"[color:FFff00ff][bold:]已开孔[%d/%d] 镶嵌宝石::[/bold][/color]\\ \\",nHoleCount,nOpenHoleCount - nHoleCount);
				sstr += sChar;
				for(int i = 0; i < 5 - 1;i++)
				{
					if(i < nHoleCount)
					{
						MID = GetMosaicItemIdxInHole(&useitem, i);
						
						pmitem = GetMStdItemInfo(MID);
						if(i > 0)
						{
							sstr += "[line:]\\";
						}
						if(pmitem)
						{
							sprintf(sChar,"[item:%d] [bold:]%s[/bold]\\",pmitem->Looks,pmitem->Name);
							sstr += sChar;
							if(pmitem->AC > 0)
							{
								sprintf(sChar,"[color:FF0099ff]生命＋%d[/color]\\",pmitem->AC);
								sstr += sChar;
							}
							if(pmitem->MAC > 0)
							{
								sprintf(sChar,"[color:FF0099ff]魔法＋%d[/color]\\",pmitem->MAC);
								sstr += sChar;
							}
							if(pmitem->DC2)
							{
								sprintf(sChar,"[color:FF0099ff]攻击＋%d[/color]\\",pmitem->DC2);
								sstr += sChar;
							}
							if(pmitem->MC2)
							{
								sprintf(sChar,"[color:FF0099ff]魔法＋%d[/color]\\",pmitem->MC2);
								sstr += sChar;
							}
							if(pmitem->SC2)
							{
								sprintf(sChar,"[color:FF0099ff]道术＋%d[/color]\\",pmitem->SC2);
								sstr += sChar;
							}	
							if(pmitem->DC)
							{
								sprintf(sChar,"[color:FF0099ff]免伤＋%d[/color]\\",pmitem->DC / 100);
								sstr += sChar;
							}				
						}else
						{
							sstr += "[item:0][color:FF888888] 暂无镶嵌宝石[/color]\\";
						}

					}
				}
			}

		}
		TStdItem* GetMStdItemInfo(int mID)
		{
			std::map<int,TStdItem*>::iterator it;
			if(mID >= 0 && mID <= (int)g_MItemArray.size())
			{
				it = g_MItemArray.find(mID);
				if(it != g_MItemArray.end())
				{
					if((int)strlen(it->second->Name) > 0)
					{
						return it->second;
					}
				}

			}
			return nullptr;
		}
		int GetMosaicItemIdxInHole(TUserItem* userItem,int holdIdx)
		{
			int ret = 0;
			if(userItem)
			{
				switch(holdIdx)
				{
				case 0:
					{
						ret = userItem->btValue[15] & 0x00FF;
						break;
					}
				case 1:
					{
						ret = userItem->btValue[16] & 0xFF00 >> 8;
						break;
					}
				case 2:
					{
						ret = userItem->btValue[16] & 0x00FF;
						break;
					}
				case 3:
					{
						ret = userItem->btValue[17] && 0xFF00 >> 8;
						break;
					}
				case 4:
					{
						ret = userItem->btValue[17] & 0x00FF;
						break;
					}
				}
			}
			return ret;
		}
		int GetItemOpenHoleCount(TUserItem* useritem)
		{
			if(useritem)
			{
				return useritem->btValue[15] & 0x0F00 >> 12; 
			}
			return 0;
		}
		int GetItemHoleCount(TUserItem* userItem)
		{
			if(userItem)
			{
				return userItem->btValue[15] & 0x0F00 >> 8; //前一个字节存放打孔数量
			}
			return 0;
		}
		void GetMouseItemInfo(std::string &iname,std::string &line1,std::string &line2,std::string &line3,bool &useable)
		{
			int i = 0,n = 0;
			std::string str = "",addstr = "";
			int stlevel = 0,stcount = 0;
			std::string ucolor = "";
			char sRet[1024];
			if(!g_MySelf) return;
			iname = line1 = line2 = line3 ="";
			useable = true;
			if((int)strlen((char*)g_MouseItem.s.Name) > 0)
			{
				iname += GetItemQualityName(&g_MouseItem.s) + "\\";
				switch(g_MouseItem.s.StdMode)
				{
				case 0:
					{
						switch(g_MouseItem.s.Shape)
						{
						case 0:
							{
								if(g_MouseItem.s.AC > 0 && g_MouseItem.s.DuraMax == 0)
								{
									sprintf(sRet,"恢复: %d HP",g_MouseItem.s.AC);
									line2 = sRet;
								}else if(g_MouseItem.s.MAC > 0 && g_MouseItem.s.AC == 0)
								{
									sprintf(sRet,"恢复: %d MP",g_MouseItem.s.MAC);
									line2 = sRet;
								}else
								{
									sprintf(sRet,"恢复: %d HP %d MP",g_MouseItem.s.AC,g_MouseItem.s.MAC);
									line2 = sRet;
								}
								break;
							}
						case 1:
							{
								if(g_MouseItem.s.AC > 0 && g_MouseItem.s.MAC == 0)
								{
									sprintf(sRet,"立即恢复: %d HP",g_MouseItem.s.AC);
									line2 = sRet;
								}else if(g_MouseItem.s.MAC > 0 && g_MouseItem.s.AC == 0)
								{
									sprintf(sRet,"立即恢复: %d MP");
									line2 = sRet;
								}else 
								{
									sprintf(sRet,"立即恢复: %d HP %d MP",g_MouseItem.s.AC,g_MouseItem.s.MAC);
									line2 = sRet;
								}
								break;
							}
						case 3:
							{
								if(g_MouseItem.s.AC > 0 && g_MouseItem.s.MAC == 0)
								{
									sprintf(sRet,"立即恢复: %d %HP",g_MouseItem.s.AC);
									line2 = sRet;
								}else if(g_MouseItem.s.MAC > 0 && g_MouseItem.s.AC == 0)
								{
									sprintf(sRet,"立即恢复: %d %MP");
									line2 = sRet;
								}else 
								{
									sprintf(sRet,"立即恢复: %d %HP %d %MP",g_MouseItem.s.AC,g_MouseItem.s.MAC);
									line2 = sRet;
								}
								break;
							}
						case 10:
							{
								if(g_MouseItem.s.AC > 0 && g_MouseItem.s.MAC == 0)
								{
									sprintf(sRet,"立即恢复骑宠: %d HP",g_MouseItem.s.AC);
									line2 = sRet;
								}else if(g_MouseItem.s.MAC > 0 && g_MouseItem.s.AC == 0)
								{
									sprintf(sRet,"立即恢复骑宠: %d MP");
									line2 = sRet;
								}else 
								{
									sprintf(sRet,"立即恢复骑宠: %d HP %d MP",g_MouseItem.s.AC,g_MouseItem.s.MAC);
									line2 = sRet;
								}
								break;
							}
						}
						break;
					}
				case 1:
					{
						switch(g_MouseItem.s.Shape)
						{
						case 1:
						case 2:
						case 5:
						case 6:
						case 7:
							{
								str = GetDuraStr(g_MouseItem.Dura,g_MouseItem.DuraMax);
								sprintf(sRet,"持续使用: %s 小时",str.c_str());
								line2 = sRet;
								break;
							}
						case 3:
						case 4:
						case 8:
						case 9:
						case 10:
							{
								str = GetDuraStr(g_MouseItem.Dura,g_MouseItem.DuraMax);
								sprintf(sRet,"累积使用: %s 小时",str.c_str());
								line2 = sRet;
								break;
							}
						}
						break;
					}
				case 2:
					{
						switch(g_MouseItem.s.Shape)
						{
						case 0:
							{
								str = GetDuraStr(g_MouseItem.Dura,g_MouseItem.DuraMax);
								sprintf(sRet,"使用 %s 次",str.c_str());
								line2 = sRet;
								break;
							}
						case 1:
							{
								str = GetDura100Str(g_MouseItem.Dura,g_MouseItem.DuraMax);
								sprintf(sRet,"使用 %s 次",str.c_str());
								line2 = sRet;
								break;
							}
						case 2:
						case 4:
							{
								str = GetDuraStr(g_MouseItem.Dura,g_MouseItem.DuraMax);
								sprintf(sRet,"使用 %s 次",str.c_str());
								line2 = sRet;
								break;
								break;
							}
						}
						break;
					}
				case 3:
					{
						break;
					}
				case 4:
					{
						sprintf(sRet,"所需等级: %d",g_MouseItem.s.DuraMax);
						line3 = sRet;
						useable = false;
						switch(g_MouseItem.s.Shape)
						{
						case 0:
							{
								line2 = "战士秘技";
								if(g_MySelf->m_btJob == 0 && g_MySelf->m_Abil.Level >= g_MouseItem.s.DuraMax)
								{
									useable = true;
								}
								break;
							}
						case 1:
							{
								line2 = "法师秘技";
								if(g_MySelf->m_btJob == 1 && g_MySelf->m_Abil.Level >= g_MouseItem.s.DuraMax)
								{
									useable = true;
								}
								break;
							}
						case 2:
							{
								line2 = "道士秘技";
								if(g_MySelf->m_btJob == 2 && g_MySelf->m_Abil.Level >= g_MouseItem.s.DuraMax)
								{
									useable = true;
								}
								break;
							}
						}
						break;
					}
				case 5:
				case 6:
					{
						if(g_MouseItem.s.CharLooks == 0) useable = false;
						if((g_MouseItem.s.Reserved & 0x01) != 0 ) iname = "(*)" + iname;
						//强化信息
						stlevel = g_MouseItem.btValue[19] & 0x0F;
						stcount = g_MouseItem.btValue[19] & 0xF0 >> 4;
						n = 10 - stcount;
						for(int i = 0;i < stlevel + n - 1;i++)
						{
							if(i < stlevel)
							{
								line1 += "[img:63]";
							}else 
							{
								line1 += "[img:64]";
							}
						}
						line1 += " \\";
						line1 += " \\";
						// 所需等级
						str = "";
						useable = GetNeedStr(str);
						if(str.length() > 0)
						{
							if(useable)
							{
								ucolor = "[color:FF00FF00]";
							}else
							{
								ucolor = "[color:FFFF0000]";
							}
							line1 = line1 + ucolor + str  + "[/color] \\";
						}
						if(g_MouseItem.Dura > 0)
						{
							str = GetDuraStr(g_MouseItem.Dura, g_MouseItem.DuraMax);
							sprintf(sRet,"[color:FF00AA00]持久: %s[/color] \\ \\",str.c_str());
							line1 += sRet;
						}else
						{
							line1 += "[color:FFFF0000]此装备已损坏，需修理。[/color] \\ \\";
						}
					
						if(g_MouseItem.s.DC2)
						{
							addstr = "";
							if(g_MouseItem.btValue[0] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[0]);
								addstr = sRet;
							}
							sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.DC,g_MouseItem.s.DC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr  = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr;
						}
						//魔法攻击
						if(g_MouseItem.s.MC2 > 0)
						{
							addstr = "";
							if(g_MouseItem.btValue[1] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[1]);
								addstr = sRet;
							}
							sprintf(sRet,"魔法攻击: %d-%d",g_MouseItem.s.MC,g_MouseItem.s.MC2);
							str = sRet;
							line1 += str + addstr;
							 //祈灵的属性
							addstr  = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr;
						}
						//道术攻击
						if(g_MouseItem.s.SC2 > 0)
						{
							addstr = "";
							if(g_MouseItem.btValue[2] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[2]);
								addstr = sRet;
							}
							sprintf(sRet,"道术攻击: %d-%d",g_MouseItem.s.SC,g_MouseItem.s.SC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr  = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr;
						}
						str = "";
						if(g_MouseItem.btValue[7] > 0)
						{
							sprintf(sRet,"强度: %d (+%d)\\",g_MouseItem.btValue[7],g_MouseItem.btValue[7]);
							str = sRet;
						}
						if(g_MouseItem.s.AC2 >= 0 && g_MouseItem.s.AC2 <= 100)
						{
							sprintf(sRet,"准确: +",g_MouseItem.s.AC2);
							str += sRet;
						}else if(g_MouseItem.s.AC2 > 100)
						{
							sprintf(sRet,"准确: -",g_MouseItem.s.AC2 - 100);
							str += sRet;
						}
						 //祈灵的属性
						addstr = "";
						if(g_MouseItem.btValue[10] > 0)
						{
							sprintf(sRet,"[color:FF00FF00][+%d][/color]\\",g_MouseItem.btValue[10]);
							str += sRet;
						}
						if(g_MouseItem.s.MAC2 > 0)
						{
							if(g_MouseItem.s.MAC2 > 10)
							{
								sprintf(sRet,"\\攻击速度: +%d",g_MouseItem.s.MAC2 - 10);
								str += sRet;
							}else 
							{
								sprintf(sRet,"\\攻击速度: -%d",g_MouseItem.s.MAC2);
								str += sRet;
							}
						}
						   //祈灵的属性
						addstr = "";
						if(g_MouseItem.btValue[9] > 0)
						{
							sprintf(sRet,"[color:FF00FF00][+%d][/color]\\",g_MouseItem.btValue[9]);
							addstr = sRet;
						}else addstr = "\\";
						str += addstr;
						if(g_MouseItem.s.AC > 0)
						{
							sprintf(sRet,"幸运: +%d\\",g_MouseItem.s.AC);
							str += sRet;
						}
						if(g_MouseItem.s.MAC > 0)
						{
							sprintf(sRet,"诅咒: +%d",g_MouseItem.s.MAC);
							str += sRet;
						}
						if(str.length() > 0)
						{
							//str = Trim(str);
							if(str[str.length() - 1] == '\\')
							{
								str = str.substr(0,str.length() - 1);
							}

							line1 += "[color:FF0099FF]" +str + "[/color]";
						}
						break;
					}
				case 7:
					{
						str = "";
						switch(g_MouseItem.s.Shape)
						{
						case 0:
							{
								addstr  =GetDuraStr(g_MouseItem.Dura, g_MouseItem.DuraMax);
								sprintf(sRet,"使用: %s 次",addstr.c_str());
								str = sRet;
								break;
							}
						case 1:
						case 2:
						case 3:
							{
								sprintf(sRet,"剩余恢复量:%d万/%d万",g_MouseItem.Dura / 1000,g_MouseItem.DuraMax / 1000);
								str = sRet;
								break;
							}
						}
						if(str.length() > 0)
						{
							//str := Trim(str);
							if(str[str.length() - 1] == '\\')
							{
								str = str.substr(0,str.length()- 1);
							}
							line1 += " \\[color:FF0099FF]" + str + "[/color]";
						}
						break;
					}
				case 10://男衣服, 女衣服,翅膀}
				case 11:
				case 113: 
					{
						useable =false;
						stlevel = g_MouseItem.btValue[19] & 0x0F;
						stcount = g_MouseItem.btValue[19] & 0xF0 >> 4;
						n = 10 - stcount;
						for(int i = 0;i < stlevel + n - 1;i++)
						{
							if(i < stlevel)
							{
								line1 += "[img::63]";
							}else line1 += "[img::64]";
						}
						line1 += "\\"; line1 += "\\";
						 // 所需等级
						str = "";
						useable = GetNeedStr(str);
						if(str.length() > 0)
						{
							if(useable) ucolor = "[color:FF00FF00]";
							else ucolor = "[color:FFFF0000]";
							line1 += ucolor + str + "[/color] \\";
						}
						if(g_MouseItem.Dura > 0)
						{
							addstr = GetDuraStr(g_MouseItem.Dura, g_MouseItem.DuraMax);
							sprintf(sRet,"[color:FF00AA00]持久: %s[/color] \\ \\",addstr.c_str());
							line1 += sRet;
						}else 
						{
							line1 += "[color:FFFF0000]此装备已损坏，需修理。[/color] \\ \\";
						}
						//物理防御
						if(g_MouseItem.s.AC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[0] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[0]);
							}
							sprintf(sRet,"物理防御: %d-%d",g_MouseItem.s.AC,g_MouseItem.s.AC2);
							str = sRet;
							line1 += str + addstr;
							  //祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[9] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[9]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//魔法防御
						if(g_MouseItem.s.MAC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[1] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[1]);
							}
							sprintf(sRet,"魔法防御: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[10] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[10]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//物理攻击
						if(g_MouseItem.s.DC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[2] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[2]);
							}
							sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.DC,g_MouseItem.s.DC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//魔法攻击
						if(g_MouseItem.s.MC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[3] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[3]);
							}
							sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MC,g_MouseItem.s.MC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//道术攻击
						if(g_MouseItem.s.SC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[4] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[4]);
							}
							sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.SC,g_MouseItem.s.SC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						break;
					}
				case 111: //男时装、女时装
				case 112:
					{
						useable = false;
						 // 所需等级
						str = "";
						useable = GetNeedStr(str);
						if(str.length() > 0)
						{
							if(useable) ucolor = "[color:FF00FF00]";
							else ucolor = "[color:FFFF0000]";
							line1 += ucolor + str +"[/color] \\";
						}
						line1 += " \\";
						//物理防御
						if(g_MouseItem.s.AC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[0] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[0]);
							}
							sprintf(sRet,"物理防御: %d-%d",g_MouseItem.s.AC,g_MouseItem.s.AC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[9] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[9]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//魔法防御
						if(g_MouseItem.s.MAC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[1] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[1]);
							}
							sprintf(sRet,"魔法防御: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[10] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[10]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//物理攻击
						if(g_MouseItem.s.DC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[2] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[2]);
							}
							sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//魔法攻击
						if(g_MouseItem.s.MC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[3] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[3]);
							}
							sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MC,g_MouseItem.s.MC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//道术攻击
						if(g_MouseItem.s.SC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[4] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[4]);
							}
							sprintf(sRet,"道术攻击: %d-%d",g_MouseItem.s.SC,g_MouseItem.s.SC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						break;
					}
				case 15:	//头盔
				case 52:	//鞋
				case 62:	//鞋
				case 54:	//腰带
				case 64:	//腰带
					{
						//强化信息
						stlevel = g_MouseItem.btValue[19] & 0x0F;
						stcount = g_MouseItem.btValue[19] & 0xF0 >> 4;
						n = 10 - stcount;
						for(int i = 0;i < stlevel + n - 1;i++)
						{
							if(i < stlevel)
							{
								line1 += "[img::63]";
							}else line1 += "[img::64]";
						}
						line1 += "\\"; line1 += "\\";
						// 所需等级
						str = "";
						useable = GetNeedStr(str);
						if(str.length() > 0)
						{
							if(useable) ucolor = "[color:FF00FF00]";
							else ucolor = "[color:FFFF0000]";
							line1 += ucolor + str + "[/color] \\";
						}
						if(g_MouseItem.Dura > 0)
						{
							addstr = GetDuraStr(g_MouseItem.Dura, g_MouseItem.DuraMax);
							sprintf(sRet,"[color:FF00AA00]持久: %s[/color] \\ \\",addstr.c_str());
							line1 += sRet;
						}else 
						{
							line1 += "[color:FFFF0000]此装备已损坏，需修理。[/color] \\ \\";
						}
						//物理防御
						if(g_MouseItem.s.AC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[0] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[0]);
							}
							sprintf(sRet,"物理防御: %d-%d",g_MouseItem.s.AC,g_MouseItem.s.AC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[9] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[9]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//魔法防御
						if(g_MouseItem.s.MAC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[1] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[1]);
							}
							sprintf(sRet,"魔法防御: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[10] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[10]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//物理攻击
						if(g_MouseItem.s.DC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[2] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[2]);
							}
							sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//魔法攻击
						if(g_MouseItem.s.MC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[3] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[3]);
							}
							sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MC,g_MouseItem.s.MC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//道术攻击
						if(g_MouseItem.s.SC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[4] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[4]);
							}
							sprintf(sRet,"道术攻击: %d-%d",g_MouseItem.s.SC,g_MouseItem.s.SC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						break;
					}
				case 19:
				case 20:
				case 21:
				case 22:
				case 23:
				case 24:
				case 51:
				case 53:
				case 63: //戒指、项链、手镯、宝石
					{
						//强化信息
						stlevel = g_MouseItem.btValue[19] & 0x0F;
						stcount = g_MouseItem.btValue[19] & 0xF0 >> 4;
						n = 10 - stcount;
						for(int i = 0;i < stlevel + n - 1;i++)
						{
							if(i < stlevel)
							{
								line1 += "[img::63]";
							}else line1 += "[img::64]";
						}
						line1 += "\\"; line1 += "\\";
						// 所需等级
						str = "";
						useable = GetNeedStr(str);
						if(str.length() > 0)
						{
							if(useable) ucolor = "[color:FF00FF00]";
							else ucolor = "[color:FFFF0000]";
							line1 += ucolor + str + "[/color] \\";
						}
						if(g_MouseItem.Dura > 0)
						{
							addstr = GetDuraStr(g_MouseItem.Dura, g_MouseItem.DuraMax);
							sprintf(sRet,"[color:FF00AA00]持久: %s[/color] \\ \\",addstr.c_str());
							line1 += sRet;
						}else 
						{
							line1 += "[color:FFFF0000]此装备已损坏，需修理。[/color] \\ \\";
						}
						//物理防御
						if(g_MouseItem.s.AC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[0] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[0]);
							}
							sprintf(sRet,"物理防御: %d-%d",g_MouseItem.s.AC,g_MouseItem.s.AC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[9] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[9]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//魔法防御
						if(g_MouseItem.s.MAC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[1] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[1]);
							}
							sprintf(sRet,"魔法防御: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[10] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[10]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//物理攻击
						if(g_MouseItem.s.DC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[2] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[2]);
							}
							sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//魔法攻击
						if(g_MouseItem.s.MC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[3] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[3]);
							}
							sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MC,g_MouseItem.s.MC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//道术攻击
						if(g_MouseItem.s.SC2 > 0 )
						{
							addstr = "";
							if(g_MouseItem.btValue[4] > 0)
							{
								sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[4]);
							}
							sprintf(sRet,"道术攻击: %d-%d",g_MouseItem.s.SC,g_MouseItem.s.SC2);
							str = sRet;
							line1 += str + addstr;
							//祈灵的属性
							addstr = "";
							if(g_MouseItem.btValue[11] > 0)
							{
								sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
								addstr = sRet;
							}
							line1 += addstr + "\\";
						}
						//附加属性
						str ="";
						switch (g_MouseItem.s.StdMode)
						{
						case 19://项链}
						case 53:
							{
								if(g_MouseItem.s.AC2 > 0)
								{
									sprintf(sRet,"魔法躲避: +%d0%\\",g_MouseItem.s.AC2);
									str += sRet;
								}
								if(g_MouseItem.s.MAC > 0)
								{
									sprintf(sRet,"诅咒: +%d\\",g_MouseItem.s.MAC);
									str += sRet;
								}
								if(g_MouseItem.s.MAC2 > 0)
								{
									sprintf(sRet,"幸运: +%d\\",g_MouseItem.s.MAC2);
									str += sRet;
								}
								break;
							}
						case 20: //项链 及 手镯: MaxAC -> Hit,  MaxMac -> Speed}
						case 24:
						case 52:
							{
								if(g_MouseItem.s.AC2 > 0)
								{
									sprintf(sRet,"准确: +%d\\",g_MouseItem.s.AC2);
									str += sRet;
								}
								if(g_MouseItem.s.MAC2 > 0)
								{
									sprintf(sRet,"敏捷: +5d\\",g_MouseItem.s.MAC2);
									str += sRet;
								}
								break;
							}
						case 21://项链}
						case 54:
							{
								if(g_MouseItem.s.AC2 > 0)
								{
									sprintf(sRet,"体力恢复: +%d0%\\",g_MouseItem.s.AC2);
									str += sRet;
								}
								if(g_MouseItem.s.MAC2 > 0)
								{
									sprintf(sRet,"体力恢复: +%d0%\\",g_MouseItem.s.MAC2);
									str += sRet;
								}
								if(g_MouseItem.s.AC > 0)
								{
									sprintf(sRet,"攻击速度: +%d\\",g_MouseItem.s.AC);
									str += sRet;
								}
								if(g_MouseItem.s.MAC > 0)
								{
									sprintf(sRet,"攻击速度: -%d\\",g_MouseItem.s.MAC);
									str += sRet;
								}
								break;
							}
						case 23://戒指}
							{
								if(g_MouseItem.s.AC2 > 0)
								{
									sprintf(sRet,"毒物躲避: +%d0%\\",g_MouseItem.s.AC2);
									str += sRet;
								}
								if(g_MouseItem.s.MAC2 > 0)
								{
									sprintf(sRet,"中毒恢复: +%d0%\\",g_MouseItem.s.MAC2);
									str += sRet;
								}
								if(g_MouseItem.s.AC > 0)
								{
									sprintf(sRet,"攻击速度: +%d\\",g_MouseItem.s.AC);
									str += sRet;
								}
								if(g_MouseItem.s.MAC > 0)
								{
									sprintf(sRet,"攻击速度: -%d\\",g_MouseItem.s.MAC);
									str += sRet;
								}	
								break;
							}

						}
						if(str.length() > 0)
						{
							// str := Trim(str);
							if(str[str.length()-1] == '\\') str = str.substr(0,str.length() - 1);
							line1 += "[color:FF0099FF]" + str +	"[/color]";	
						}
						break;
	
					}
					case 25: ////护身符及毒药}
						{
							switch(g_MouseItem.s.Shape )
							{
							case 1:
							case 2:
							case 5:
								{
									str  = GetDura100Str(g_MouseItem.Dura,g_MouseItem.DuraMax);
									sprintf(sRet,"数量: %s",str.c_str());
									line2 = str;
									break;
								}
							case 6:
							case 7:
								{
									str  = GetDura100Str(g_MouseItem.Dura,g_MouseItem.DuraMax);
									sprintf(sRet,"使用: %s",str.c_str());
									line2 =str;
									break;
								}
							}
							break;
						}
					case 26:
					case 30://勋章 和特殊的手镯，有攻魔道，还有防御，但顺序和衣服不同
						{
							//强化信息
							stlevel = g_MouseItem.btValue[19] & 0x0F;
							stcount = g_MouseItem.btValue[19] & 0xF0 >> 4;
							n = 10 - stcount;
							for(int i = 0;i < stlevel + n - 1;i++)
							{
								if(i < stlevel)
								{
									line1 += "[img::63]";
								}else line1 += "[img::64]";
							}
							line1 += "\\"; line1 += "\\";
							// 所需等级
							str = "";
							useable = GetNeedStr(str);
							if(str.length() > 0)
							{
								if(useable) ucolor = "[color:FF00FF00]";
								else ucolor = "[color:FFFF0000]";
								line1 += ucolor + str + "[/color] \\";
							}
							if(g_MouseItem.Dura > 0)
							{
								addstr = GetDuraStr(g_MouseItem.Dura, g_MouseItem.DuraMax);
								sprintf(sRet,"[color:FF00AA00]持久: %s[/color] \\ \\",addstr.c_str());
								line1 += sRet;
							}else 
							{
								line1 += "[color:FFFF0000]此装备已损坏，需修理。[/color] \\ \\";
							}
							//物理防御
							if(g_MouseItem.s.AC2 > 0 )
							{
								addstr = "";
								if(g_MouseItem.btValue[0] > 0)
								{
									sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[0]);
								}
								sprintf(sRet,"物理防御: %d-%d",g_MouseItem.s.AC,g_MouseItem.s.AC2);
								str = sRet;
								line1 += str + addstr;
								//祈灵的属性
								addstr = "";
								if(g_MouseItem.btValue[9] > 0)
								{
									sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[9]);
									addstr = sRet;
								}
								line1 += addstr + "\\";
							}
							//魔法防御
							if(g_MouseItem.s.MAC2 > 0 )
							{
								addstr = "";
								if(g_MouseItem.btValue[1] > 0)
								{
									sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[1]);
								}
								sprintf(sRet,"魔法防御: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
								str = sRet;
								line1 += str + addstr;
								//祈灵的属性
								addstr = "";
								if(g_MouseItem.btValue[10] > 0)
								{
									sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[10]);
									addstr = sRet;
								}
								line1 += addstr + "\\";
							}
							//物理攻击
							if(g_MouseItem.s.DC2 > 0 )
							{
								addstr = "";
								if(g_MouseItem.btValue[2] > 0)
								{
									sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[2]);
								}
								sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
								str = sRet;
								line1 += str + addstr;
								//祈灵的属性
								addstr = "";
								if(g_MouseItem.btValue[11] > 0)
								{
									sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
									addstr = sRet;
								}
								line1 += addstr + "\\";
							}
							//魔法攻击
							if(g_MouseItem.s.MC2 > 0 )
							{
								addstr = "";
								if(g_MouseItem.btValue[3] > 0)
								{
									sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[3]);
								}
								sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MC,g_MouseItem.s.MC2);
								str = sRet;
								line1 += str + addstr;
								//祈灵的属性
								addstr = "";
								if(g_MouseItem.btValue[11] > 0)
								{
									sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
									addstr = sRet;
								}
								line1 += addstr + "\\";
							}
							//道术攻击
							if(g_MouseItem.s.SC2 > 0 )
							{
								addstr = "";
								if(g_MouseItem.btValue[4] > 0)
								{
									sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[4]);
								}
								sprintf(sRet,"道术攻击: %d-%d",g_MouseItem.s.SC,g_MouseItem.s.SC2);
								str = sRet;
								line1 += str + addstr;
								//祈灵的属性
								addstr = "";
								if(g_MouseItem.btValue[11] > 0)
								{
									sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
									addstr = sRet;
								}
								line1 += addstr + "\\";
							}
							break;
						}
					case 40: //肉
						{
							str = GetDuraStr(g_MouseItem.Dura, g_MouseItem.DuraMax);
							sprintf(sRet,"品质%s",str.c_str());
							line1 += sRet;
							break;
						}
					case 42://药材
						{
							line1 += "药材";
							break;
						}
					case 43://矿石
						{
							sprintf(sRet,"纯度%d",(int)g_MouseItem.Dura / 1000);
							line1 += sRet;
							break;
						}
					case 200: //镶嵌的宝石
						{
							if(g_MouseItem.s.AC > 0)
							{
								sprintf(sRet,"[color:FF0099ff]生命+%d[/color]\\",g_MouseItem.s.AC);
								line1 += sRet;
							}
							if(g_MouseItem.s.MAC > 0)
							{
								sprintf(sRet,"[color:FF0099ff]魔法+%d[/color]\\",g_MouseItem.s.MAC);
								line1 += sRet;
							}					
							if(g_MouseItem.s.DC2 > 0)
							{
								sprintf(sRet,"[color:FF0099ff]攻击+%d[/color]\\",g_MouseItem.s.DC2);
								line1 += sRet;
							}	
							if(g_MouseItem.s.MC2 > 0)
							{
								sprintf(sRet,"[color:FF0099ff]魔法+%d[/color]\\",g_MouseItem.s.MC2);
								line1 += sRet;
							}	
							if(g_MouseItem.s.SC2 > 0)
							{
								sprintf(sRet,"[color:FF0099ff]道术+%d[/color]\\",g_MouseItem.s.SC2);
								line1 += sRet;
							}	
				
							if(g_MouseItem.s.DC > 0)
							{
								sprintf(sRet,"[color:FF0099ff]免伤＋d%[/color]\\",g_MouseItem.s.DC / 100);
								line1 += sRet;
							}	
							break;
						}
						case 100: //骑宠装备}
						case 101:
						case 102:
						case 103:
						case 104:
						{
							useable = false;
							 //强化信息
							stlevel = g_MouseItem.btValue[19] & 0x0F;
							stcount = g_MouseItem.btValue[19] & 0xF0 >> 4;
							n = 10 - stcount;
							for(int i = 0;i < stlevel + n - 1;i++)
							{
								if(i < stlevel)
								{
									line1 += "[img::63]";
								}else line1 += "[img::64]";
							}
							line1 += "\\"; line1 += "\\";
							// 所需等级
							str = "";
							useable = GetNeedStr(str);
							if(str.length() > 0)
							{
								if(useable) ucolor = "[color:FF00FF00]";
								else ucolor = "[color:FFFF0000]";
								line1 += ucolor + str + "[/color] \\";
							}
							if(g_MouseItem.Dura > 0)
							{
								addstr = GetDuraStr(g_MouseItem.Dura, g_MouseItem.DuraMax);
								sprintf(sRet,"[color:FF00AA00]持久: %s[/color] \\ \\",addstr.c_str());
								line1 += sRet;
							}else 
							{
								line1 += "[color:FFFF0000]此装备已损坏，需修理。[/color] \\ \\";
							}
							//物理防御
							if(g_MouseItem.s.AC2 > 0 )
							{
								addstr = "";
								if(g_MouseItem.btValue[0] > 0)
								{
									sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[0]);
								}
								sprintf(sRet,"物理防御: %d-%d",g_MouseItem.s.AC,g_MouseItem.s.AC2);
								str = sRet;
								line1 += str + addstr;
								//祈灵的属性
								addstr = "";
								if(g_MouseItem.btValue[9] > 0)
								{
									sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[9]);
									addstr = sRet;
								}
								line1 += addstr + "\\";
							}
							//魔法防御
							if(g_MouseItem.s.MAC2 > 0 )
							{
								addstr = "";
								if(g_MouseItem.btValue[1] > 0)
								{
									sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[1]);
								}
								sprintf(sRet,"魔法防御: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
								str = sRet;
								line1 += str + addstr;
								//祈灵的属性
								addstr = "";
								if(g_MouseItem.btValue[10] > 0)
								{
									sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[10]);
									addstr = sRet;
								}
								line1 += addstr + "\\";
							}
							//物理攻击
							if(g_MouseItem.s.DC2 > 0 )
							{
								addstr = "";
								if(g_MouseItem.btValue[2] > 0)
								{
									sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[2]);
								}
								sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MAC,g_MouseItem.s.MAC2);
								str = sRet;
								line1 += str + addstr;
								//祈灵的属性
								addstr = "";
								if(g_MouseItem.btValue[11] > 0)
								{
									sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
									addstr = sRet;
								}
								line1 += addstr + "\\";
							}
							//魔法攻击
							if(g_MouseItem.s.MC2 > 0 )
							{
								addstr = "";
								if(g_MouseItem.btValue[3] > 0)
								{
									sprintf(sRet,"[color:FF00FF00](+%d)[/color]",g_MouseItem.btValue[3]);
								}
								sprintf(sRet,"物理攻击: %d-%d",g_MouseItem.s.MC,g_MouseItem.s.MC2);
								str = sRet;
								line1 += str + addstr;
								//祈灵的属性
								addstr = "";
								if(g_MouseItem.btValue[11] > 0)
								{
									sprintf(sRet,"[color:FF00FF00][+%d][/color]",g_MouseItem.btValue[11]);
									addstr = sRet;
								}
								line1 += addstr + "\\";
							}
							break;
						}
				}
			}
			if(strlen(g_MouseItem.s.memo) > 0)
			{
				sprintf(sRet,"\\ \\%s",g_MouseItem.s.memo);
				line3 += sRet;
			}
		}

		int TextWidth(std::string Text,int FontSize/* = 12*/)
		{ 
			int i = 0;
			int nRowWidth = 0;
			while(true)
			{
				if(i >= (int)Text.length())break;
				char p = Text[i];
				if(p >= 0 && p <= 127)
				{
					i++;
					nRowWidth +=((int) FontSize / 2);
				}else   //双字节
				{
					i+=2;
					nRowWidth += FontSize ;
				}
			}
			return nRowWidth;
		}

		std::string IntToStr(int V)
		{
			char szStr[1024]={0};
			sprintf(szStr,"%d",V);
			return szStr;
		}

		int StrToInt(const char* v)
		{
			return atoi(v);
		}

		std::string GetBeforeStr(std::string str,std::string &dest,std::string Divider)
		{
			std::string result= "";
			int s = (int)str.find(Divider);
			if(s >= 0)
			{
				dest = str.substr(0,s);
				result = str.substr(s + Divider.length(),str.length() - s);

			}else
			{
				dest = str;
			}
			return result;
		}
		//套装信息
		//playidx =0标识是比对自己 =1 标识比对对方
		std::string GetGroupItemInfo(TStdItem* stditem,unsigned char btSex,int playidx)
		{
			std::string sstr = "";
			TGroupItem* gitem = nullptr;
			bool bfind = false;
			TStdItem* dressStdItem = nullptr;
			bool boHave;
			if(g_MouseItem.s.StdMode > 3)
			{
				for(int i = 0;i < (int)g_GroupItems.size();i++)
				{
					gitem = g_GroupItems[i];
					//先检测衣服性别,不合适的直接下一个
					if(gitem->FLD_USEITEMS[U_DRESS].length() > 0)
					{
						dressStdItem = GetStdItemInfo(gitem->FLD_USEITEMS[U_DRESS]);
						if(dressStdItem)
						{
							if(playidx == 1)
							{
								if((dressStdItem->StdMode == 10 && DRESSfeature(UserState1.feature) % 2 != 9)
									|| (dressStdItem->StdMode == 11 && DRESSfeature(UserState1.feature) % 2 != 1))
								{
									continue;
								}
							}else
							{
								if((dressStdItem->StdMode == 10 && btSex != 0) ||
									(dressStdItem->StdMode == 11 && btSex !=1))
								{
									continue;
								}
							}
						}
					}
					for(int j = 0;j < MAXEQUIP;j++)
					{
						if(gitem->FLD_USEITEMS[j].length() > 0)
						{
							if(strcmp(stditem->Name,gitem->FLD_USEITEMS[j].c_str()) == 0)
							{
								bfind = true;
								break;
							}
						}
					}
					if(bfind)break;
				}
				if(bfind)
				{
					if(gitem)
					{
						sstr += gitem->FLD_TITLE + "\\";
						for(int i = 0;i < MAXEQUIP;i++)
						{
							if(gitem->FLD_USEITEMS[i].length() > 0)
							{
								//判断是否有穿戴
								boHave = false;
								if(playidx == 1)
								{
									if(CheckUseItem1(gitem->FLD_USEITEMS[i]))
									{
										boHave = true;
									}
								}else
								{
									if(CheckUseItem(gitem->FLD_USEITEMS[i]))
									{
										boHave = true;
									}
								}
								if(boHave)
								{
									sstr += gitem->FLD_USEITEMS[i] + "\\";
								}else
								{
									sstr += "[color:FF888888]" + gitem->FLD_USEITEMS[i] + "[/color]\\";
								}
							}
						}
						sstr += "\\" + gitem->FLD_HINTMSG;
					}
				}
			}
			if(sstr.length() > 0)
			{
				sstr = "\\" +sstr;
			}
			return sstr;
		}

		bool CheckUseItem(std::string itemname)
		{
			for(int i = 0;i < MAXEQUIP;i++)
			{
				if(strcmp(g_UseItems[i].s.Name,itemname.c_str()) == 0)
				{
					return true;
				}
			}
			return false;
		}
		bool CheckUseItem1(std::string itemname)
		{
			for(int i = 0; i < MAXEQUIP;i++)
			{
				if(strcmp(itemname.c_str(),UserState1.UseItems[i].s.Name) == 0)
				{
					return true;
				}
			}
			return false;
		}

		/****************************************************************************
		函数名称: str_to_hex
		函数功能: 字符串转换为十六进制
		输入参数: string 字符串 cbuf 十六进制 len 字符串的长度。
		输出参数: 无
		*****************************************************************************/ 
		unsigned long str_to_hex(std::string string)
		{
			unsigned char high, low;
			int idx, ii=0;
			unsigned long ret = 0;
			unsigned char* cbuf = (unsigned char *)&ret;
			int len = string.length();
			for (idx=0; idx<len; idx+=2) 
			{
				high = string[idx];
				low = string[idx+1];

				if(high>='0' && high<='9')
					high = high-'0';
				else if(high>='A' && high<='F')
					high = high - 'A' + 10;
				else if(high>='a' && high<='f')
					high = high - 'a' + 10;
				else
					return -1;

				if(low>='0' && low<='9')
					low = low-'0';
				else if(low>='A' && low<='F')
					low = low - 'A' + 10;
				else if(low>='a' && low<='f')
					low = low - 'a' + 10;
				else
					return -1;

				cbuf[ii++] = high<<4 | low;
			}
			return ret;
		}

		//字符串替换
		std::string& replace_all_distinct(std::string& str,const std::string& old_value,const std::string& new_value)   
		{     
			for(std::string::size_type   pos(0);   pos!=std::string::npos;   pos+=new_value.length())   {     
				if(   (pos=str.find(old_value,pos))!=std::string::npos   )     
					str.replace(pos,old_value.length(),new_value);     
				else   break;     
			}     
			return   str;     
		}     