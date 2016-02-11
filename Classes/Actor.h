#ifndef ACTOR_H_
#define ACTOR_H_
#include <Vector>
#include "GameStruct.h"
#include "cocos2d.h"
class TVDImage;
class TActor
{
public:
	TActor(void);
	~TActor(void);
public:
	int m_nShiftX;
	int m_nShiftY;
	int m_nRx;
	int m_nRy;
	bool g_boAttackSlow;
	bool g_boMoveSlow;
	int g_nMoveSlowLevel;
	bool m_boIceMoveSlow;
	int m_nIceMoveSlowLevel;
	bool IsAddBlood;
	int AddBloodNum;
	int AddBloodFram;
	unsigned long AddBloodTime;
	unsigned long AddBloodStartTime;
	bool IsEatItem;
	int EatItemNum;
	int EatItemFram;
	unsigned long EatItemTime;
	int EatItemStartTime;
	unsigned char m_btDressFrame;               //内观衣服效果
	unsigned long m_nDressTime;              //内观效果显示时间
	unsigned char m_btDressType;                //衣服外观效果类型
	unsigned char m_btWeaponFrame;              //内观衣服效果
	unsigned long m_nWeaponTime;             //内观效果显示时间
	unsigned int  m_nEffStruckFrame;
	bool m_boDieEff;
	bool m_boFightEff;
	int  m_nFightEffFrame;
	unsigned long  m_nFightEffTime;
	int  m_nFightEffNum;
	int  m_nRecogId;
	int  m_nCurrX;
	int  m_nCurrY;
	unsigned char m_btDir;
	unsigned char m_bWings;
	int  m_nHalo; //光环
	unsigned char m_btSex;
	unsigned char m_btRace;
	unsigned char m_btHair;
	unsigned char m_btDress;
	unsigned char m_btWeapon;
	unsigned char m_btHorse;
	unsigned char m_btEffect;
	unsigned char m_btDressColor;
	unsigned char m_btJob;
	unsigned short m_wAppearance;
	unsigned char m_btDeathState;
	int m_nFeature;
	int m_nFeatureEx;
	int m_nState;
	int m_nEatItemIndex;
	bool m_boYy, m_boMd;
	bool m_boDeath;
	bool m_boSkeleton;
	bool m_boDelActor;
	bool m_boDelActionAfterFinished;
	std::string m_sDescUserName;  //人名后缀
	std::string m_sGuildName;     //行会名
	std::string m_sGuildRankName;//行会封号
	std::string m_sRankName;    //封号
	std::string m_sDearName;     //爱人
	std::string m_sMasterName;
	int m_NameImg[3]; //封号图片编号
	std::string m_sUserName;
	unsigned long m_nNameColor;
	TAbility m_Abil ;
	int m_nGold;
	int m_nGameGold;
	int m_nGamePoint;  //暂时用来做绑定金币
	unsigned short m_nHitSpeed;
	bool m_boVisible;
	bool m_boHoldPlace;
	unsigned char m_btLifeAttrib;
	std::string m_SayingArr;
	int m_SayWidthsArr[5];
	long m_dwSayTime;
	int m_nSayX;
	int m_nSayY;
	int m_nSayLineCount;
	//翅膀坐标
	int m_nWx;
	int m_nWy;
	int m_nPx;
	int m_nHpx;
	int m_nHopx;
	int m_nHospx;
	int m_nWpx;
	int m_nWspx;
	int m_nSpx;
	int m_nEPx;                    //衣服的偏移X
	int m_nPy;
	int m_nHpy;
	int m_nHopy;
	int m_nHospy;
	int m_nWpy;
	int m_nWsPy;
	int m_nSpy;
	int m_nEpy;                    //衣服的偏移Y
	int m_nSType;
	int m_nDownDrawLevel;
	int m_nTargetX;
	int m_nTargetY;
	int m_nTargetRecog;
	int m_nHiterCode;
	int m_nMagicNum;
	int m_nCurrentEvent;
	bool m_boDigFragment;
	bool m_boThrow;
	int m_nBodyOffset;
	int m_nHairOffset;
	int m_nHumWinOffset;
	int m_nWeaponOffset;
	bool m_boUseMagic;
	int m_btMagicNum;
	bool m_boHitEffect;
	bool m_boMagicEff;
	int m_nMagicFrame;
	unsigned long m_nMagicFrameTime;
	int m_nMagicFrameStart;
	int m_boUseEffect;
	int m_nHitEffectNumber;
	unsigned long m_dwWaitMagicRequest;
	int m_nWaitForRecogId;
	int m_nWaitForFeature;
	int m_nWaitForStatus;
	unsigned long m_dwWaitMagicmode1;
	unsigned long m_dwWaitMagicmode2;
	int m_nCurEffFrame;  //当前效果帧
	int m_nSpellFrame;   //攻击帧数
	TUseMagicInfo m_CurMagic;
	int m_nGenAniCount;
	bool m_boOpenHealth;   //获得了健康情况，hp mp值
	bool m_noInstanceOpenHealth; //健康情况初始化
	unsigned long m_dwOpenHealthStart;
	unsigned long m_dwOpenHealthTime;
	TVDImage* m_BodySurface;
	TVDImage* m_BodySSurface;
	TVDImage* m_HorseBodySurface;
	TVDImage* m_WringsSurface; //翅膀图片 2013.9.18 文艺青年
	bool m_boGrouped;
	int m_nCurrentAction;
	bool m_boReverseFrame;
	bool m_boWarMode;
	unsigned long m_dwWarModeTime;
	bool m_boSitDownMode; //蹲下采集模式，此模式不要站起，不要绘制技能效果
	unsigned long m_dwSitDownModeTime;
	int m_nChrLight;
	int m_nMagLight;
	int m_nRushDir;
	int m_nXxI;
	bool m_boLockEndFrame;
	unsigned long m_dwLastStruckTime;
	long m_dwSendQueryUserNameTime;
	long m_dwDeleteTime;
	int m_nMagicStruckSound;
	bool m_boRunSound;
	int m_nFootStepSound;
	int m_nStruckSound;
	int m_nStruckWeaponSound;
	int m_nAppearSound;
	int m_nNormalSound;
	int m_nAttackSound;
	int m_nWeaponSound;
	int m_nScreamSound;
	int m_nDieSound;
	int m_nDie2Sound;
	int m_nMagicStartSound;
	int m_nMagicFireSound;
	int m_nMagicExplosionSound;
	TMonsterAction* m_Action;
	unsigned char m_btSpellAct;
	std::vector<TUseMagicInfo*> m_MonMagiList;
	bool m_bMeditation; //是否打坐中

	TChrMsg RealActionMsg;
public:
	void SendMsg(int wIdent, int nX,int nY, int ndir, int nFeature, int nState,std::string sStr,int  nSound);
	void UpdateMsg(int wIdent,int nX, int nY, int ndir,int  nFeature,int nState,char* sStr, int nSound);
	void ProcMsg();
	bool GetMessage_(TChrMsg* ChrMsg);
	void ReadyAction(TChrMsg Msg);
	
	void ProcHurryMsg();
	bool IsIdle();
	bool Move(int step);
	void Shift(int dir,int step,int ncur,int Max);
	int CanWalk();
	int CanRun();
	void MoveFail();
	bool CheckSelect(int dx1,int dy1);
	int CharWidth();
	void CleanUserMsgs();
	void ProcName(const char* sstr);
	void DrawAddBlood(int dx,int dy,cocos2d::Layer* layer);
	bool CanCancelAction();
	void CancelAction();
	void CleanCharMapSetting(int x,int y);
	bool ActionFinished();
public:
	virtual void Run();
	virtual void RunFrameAction(int frame);
	virtual void ActionEnded();
	virtual void DefaultMotion();
	virtual int GetDefaultFrame(bool wmode);
	virtual bool DrawChr(int dx, int dy, bool blend,bool boFlag,cocos2d::Layer* layer,bool ismask = false);
	virtual void CalcActorFrame();
	virtual void LoadSurface();
	virtual bool MagicTimeOut();
	virtual void FeatureChanged();
	virtual void DrawEff(int dx,int dy);
	virtual void RunActSound(int frame);
	virtual void RunSound();
	virtual void SetSound();


public:
	std::vector<TChrMsg*> m_MsgList;

protected:
	int m_nStartFrame;
	int m_nEndFrame;
	int m_nCurrentFrame;
	char m_Spell[5];
	short m_btIdx;
	int m_nEffectStart;
	int m_nEffectFrame;
	int m_nEffectEnd;
	unsigned long m_dwEffectStartTime;
	unsigned long m_dwEffectFrameTime;
	unsigned long m_dwFrameTime;
	unsigned long m_dwStartTime;
	unsigned long m_dwStartMoveTime;

	int m_nMaxTick;
	int m_nCurTick;
	int m_nMoveStep;
	bool m_boMsgMuch;
	unsigned long m_dwStruckFrameTime;
	int m_nCurrentDefFrame;
	unsigned long m_dwDefFrameTime;
	int m_nDefFrameCount;
	int m_nSkipTick;
	int m_nIceSkipTickx;
	unsigned long m_dwSmoothMoveTime;
	unsigned long m_dwGenAnicountTime;
	unsigned long m_dwLoadSurfaceTime;
	int m_nOldx;
	int m_nOldy;
	int m_nOldDir;
	int m_nActBeforeX;
	int m_nActBeforeY;
	int m_nWpord;
	int eax, eay;
	int eax1, eay1;

private:
	



};


class THumActor : public TActor
{
public:
	THumActor(void);
	~THumActor(void);
public:
	virtual void RunFrameAction(int frame);
	virtual bool DrawChr(int dx, int dy, bool blend,bool boFlag,cocos2d::Layer* layer,bool ismask = false);
	virtual void LoadSurface();
	virtual void CalcActorFrame();
	virtual void Run();
	virtual int GetDefaultFrame(bool wmode);
public:
	TVDImage* m_WeaponSurface;

private:
	bool m_boWeaponEffect;
	int m_nCurWeaponEffect;
	int m_nCurBubbleStruck;
	unsigned long m_dwWeaponpEffectTime;
	bool m_boHideWeapon;
	int m_nFrame;
	unsigned long m_dwFrameTick;
	unsigned long m_dwFrameTime;
	unsigned long m_dwHitFrameTimeTime;
	bool m_bo2D0;
};

class TNpcActor : public TActor
{
public:
	TNpcActor(void);
	~TNpcActor(void);
private:
	int m_nEffX;
	int m_nEffY;
	bool m_bo248;
	unsigned long m_dwUseEffectTick;
	bool m_boNpcWalkEffect;
	int m_nNpcWalkEffectPx;
	int m_nNpcWalkEffectPy;
	bool g_boNpcWalk;
public:
	virtual void Run();
	virtual void CalcActorFrame();
	virtual int GetDefaultFrame(bool wmode);
	virtual bool DrawChr(int dx, int dy, bool blend,bool boFlag,cocos2d::Layer* layer,bool ismask = false);
	virtual void DrawEff(int dx,int dy);
	virtual void LoadSurface();

};


class TSkeletonOma : public TActor
{
public:
		TSkeletonOma();
		~TSkeletonOma();
protected:
		int ax;
		int ay;
public:
	virtual void CalcActorFrame();
	virtual int GetDefaultFrame(bool wmode);
	virtual void Run();
	virtual bool DrawChr(int dx, int dy, bool blend,bool boFlag,cocos2d::Layer* layer,bool ismask = false);
	virtual void LoadSurface();
};

//普通怪
class TCatMon: public TSkeletonOma
{
public:
	TCatMon();
	~TCatMon();
public:
	virtual bool DrawChr(int dx, int dy, bool blend,bool boFlag,cocos2d::Layer* layer,bool ismask = false);
};

//植物之类的怪物
class TPlant : public TActor
{
public:
	TPlant(){};
	~TPlant(){};

	virtual void LoadSurface();
};

//矿石之类的怪物
class TMine : public TActor
{
public:
	TMine(){};
	~TMine(){};
	virtual void LoadSurface();
};

//弓箭手
class TArcherMon : public TCatMon
{
public:
	TArcherMon(){};
	~TArcherMon(){};
	virtual void Run();
};
#endif