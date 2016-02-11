#ifndef GAMESTRUCT_H_
#define  GAMESTRUCT_H_

#include <string>
#include "./Common/Grobal2.h"
#include <vector>

enum TSceneType
{
	stDownload = 0, //下载场景
	stIntro = 1, //LOGO场景
	stLogin = 2, //登录场景
	stSelectChr = 3,//选择角色场景
	stNewChr = 4, //创建角色场景
	stLoginNotice = 5,//公告场景
	stPlayGame = 6, //游戏场景
};
struct TVDDataHeader
{
	char Title[40];
	int DBCount;
	int VerFlag;
	TVDDataHeader();
	void reset(void);
};


struct TVDDataInfo
{
	unsigned char nType;
	unsigned char n1,n2,n3;	//保留
	int nSize;	 //数据大小
	short px;
	short py;
	TVDDataInfo();
	void reset(void);
};


struct TMapHeader
{
	char Title[20];
	unsigned short Width;
	unsigned short Height;
	double UpdateDate;
	int	ZipSize;
	char Reserved[20];
	TMapHeader();
	void reset(void);
};

struct TMapInfo
{
	unsigned short BkAree;	//底层背景图块所在的vdd文件索引
	unsigned short BkImg;	 //底层图片索引 2  //最高位为1不可以行走，图片索引为低17位
	unsigned short MidImg;	//中间层图片索引 //图片索引为低17位
	unsigned short Area;	 //表层图片对应OBJECT索引
	unsigned short FrImg;	//表层图片索引   //最高位为1不可以行走
	char	DoorIndex;		//最高位为1有门，索引为低7位	
	char	DoorOffset;		//最高位为1是开，0是关	
	char AniFrame;			 //动画效果 (Draw Alpha)
	char	AniTick;		//阴影效果
	char light;				 //雾的效果（视线）
	char flags;				//保留
	TMapInfo();
	void reset(void);
};

struct TPoint
{
	int x;
	int y;
	TPoint();
	void reset(void);
};

struct TRect_
{
	int Left;
	int Top;
	int Right;
	int Bottom;
	TRect_();
	void reset(void);
	void Rect(int ALeft,int ATop,int ARight,int ABottom);
};

//这个结构体要内存对齐
#pragma pack(push)
#pragma pack(1)
struct TAbility
{
	unsigned short Level;                      
	int AC;  //防御
	int AC2;
	int MAC;   //魔防
	int MAC2;
	int DC;    //攻击力
	int DC2;
	int MC;   //魔法
	int MC2;
	int SC;   //道术
	int SC2;
	int HP;                    
	int MP;                        
	int MaxHP;                   
	int MaxMP;                   
	unsigned long Exp;                   
	unsigned long MaxExp;                
	int Weight;                   //骑宠数据拿来当星星数据使用 2014.326 Loser.DieYoung
	int MaxWeight;                
	int WearWeight;              
	int MaxWearWeight;           
	int HandWeight;              
	int MaxHandWeight;   
	TAbility();
	void reset(void);
};
#pragma pack(pop)   

enum TMagicType
{
	mtReady = 0,
	mtFly,
	mtExplosion,
	mtFlyAxe,
	mtFireWind,
	mtFireGun,
	mtLightingThunder,
	mtThunder,
	mtExploBujauk,
	mtBujaukGroundEffect,
	mtKyulKai,
	mtFlyArrow,
	mt12,
	mt13,
	mt14,
	mt15,
	mt16,
	mHeroMagic
};
struct TUseMagicInfo
{
	int ServerMagicCode;
	int MagicSerial;
	int target;
	TMagicType EffectType;
	int EffectNumber;
	int targx;
	int targy;
	bool Recusion;
	int anitime;
	TUseMagicInfo();
	void reset(void);
};

struct TActionInfo
{
	unsigned short start;
	unsigned short frame;
	unsigned short skip;
	unsigned short ftime;
	unsigned short usetick;
	TActionInfo();
	void reset(void);
};

struct TMonsterAction 
{
	TActionInfo ActStand ;
	TActionInfo ActWalk;   
	TActionInfo ActRun;
	TActionInfo ActAttack;
	TActionInfo ActCritical;
	TActionInfo ActStruck;
	TActionInfo ActDie;
	TActionInfo ActDeath;
	TActionInfo ActSpell;
	TActionInfo ActAttack1;
	TActionInfo ActAttack2;
	TActionInfo ActAttack3;
	TActionInfo ActAttack4;
	TActionInfo ActAttack5;
	TActionInfo ActAttack6;
	TMonsterAction();
	void reset();
};


struct  THumanAction 
{
	TActionInfo ActStand;
	TActionInfo ActWalk;
	TActionInfo ActRun;
	TActionInfo ActRush;
	TActionInfo ActWarMode;
	TActionInfo ActHit;
	TActionInfo ActHeavyHit;
	TActionInfo ActBigHit;
	TActionInfo ActFireHitReady;
	TActionInfo ActTSpell;
	TActionInfo ActFSpell;
	TActionInfo ActSitdown;
	TActionInfo ActStruck;
	TActionInfo Act34Hit;
	TActionInfo Act35Hit;
	TActionInfo Act103Hit;
	TActionInfo ActKQStruck;
	TActionInfo ActDie;
	TActionInfo ActMeditation;
	THumanAction();
	void reset(void);
};

//网络事件类型
enum TNETEVENTTYPE
{
	NORMAL = 0,
	SOCKET_CONNECT_SELGATE = 1, //连接选人服务器失败
	SOCKET_CONNECT_RUNGATE = 2,		//连接网关服务器失败
	NETPACKET = 3,					//网络封包-
	NETPACKET_SPECIAL = 4 //特殊封包
};
struct TNetEvent
{

	TNETEVENTTYPE event_type;
	tagDefaultMessage msg;
	std::string Body;
	TNetEvent();
	void reset(void);
};

struct TMessageBodyWL
{
	int	lParam1;
	int	lParam2;
	int	lTag1;
	int	lTag2;
	TMessageBodyWL();
	void reset(void);
};


struct TChrMsg
{
	int Ident;
	int x;
	int y;
	int dir;
	int State;
	int feature;
	std::string saying;
	int sound;
	TChrMsg();
	void reset(void);
};

struct TMagicInfo
{
	char name[20];
	char Biao;
	unsigned short Fu;
	unsigned short magicID;
	TMagicInfo();
	void reset(void);
};
struct TActorInfo
{
	char name[20];
	char dirChar[2];
	unsigned short nx;
	unsigned short ny;
	char sType[4];
	TActorInfo();
	void reset(void);
};
struct TShared                    //内挂
{
	bool boLongAttack;              //刀刀刺杀
	bool boSmartLongAttack ; //自动隔位刺杀 跨位刺杀
	bool boShowUserName;            //chatop 加显示人名 2010-12-2
	bool boShowInformation;         //chatop加在头部显示信息  2010-11-30
	std::string stimenow;                   //chatop加在头部显示的时间信息  2010-11-30
	std::string chrname;              //chatop加新建角色的名字 2011-1-8
	int leftchr;                     //chatop加新建角色的名字的显示位置 2011-1-8
	int topchr;                    //chatop加新建角色的名字的显示位置 2011-1-8
	bool chrnameeditshow;       //chatop加新建角色的名字是否显示 2011-1-8
	int  left;
	int  top;
	char sID[20];
	char sPass[20];
	bool boEnter;
	unsigned char btLoad;
	char name[20];
	bool boWarrC;
	bool bocloseform;
	bool boShowBlood;
	bool boShowNumBlood; //数字显血
	bool boRunAndRun;
	bool boDuraAlern;
	bool boClearBody;  //清理尸体，只是隐藏，并不是真的清理掉了
	bool boNoHit;    //被攻击不弯腰
	bool boAttackLock;     //锁定攻击 魔法锁定
	bool boShowAttactTarget;
	bool boForceExit;
	bool boNoStone;
	bool boAttackChangeColor;
	bool boTeamChangeColor;
	bool boUseMagicDownHorse;    //使用魔法自动下马
	bool boCloseExp;
	bool boItemFlash;
	bool boShowItem;
	bool boAutoPickUp;  //自动捡取物品
	bool boShowLocalFashion;//显示本地时装-
	bool boAutoPickUpDrug ; //自动捡取药物
	bool boAutoPickUpGold ; //自动捡取金币
	bool boCTRLPickUp;     //ctrl按键捡取物品 现在为空格键
	bool boBindItem;
	unsigned char unsbtMouseMiddle;
	unsigned char btMouseMiddelMagic;
	unsigned char boWarrLock;
	bool boWarrTbs;
	bool boWarrPx;
	bool boAutoThree;
	bool boAutoFour;
	bool boBuffTime;
	bool boMoDun;
	bool boMoHiddent;//自动隐身
	bool boAutoDF;  //自动毒符
	char sProtect[10];    //攻击模式
	bool boHpMin;     //自动吃药
	int nHpMin; //自动吃药下限
	int nHpTick; //时间间隔
	bool boMpMin;     //自动吃魔法药
	int nMpMin; //自动吃魔法药下限
	int nMpTick; //时间间隔
	bool boHPMPfast  ;//快速恢复药
	int nHPMPFastMin ;//快速恢复药下限
	int nHPMPFastTack ;//时间间隔
	int boUseJuan;    //使用回城卷
	int nUseJuanMin ;  //使用回城卷hp下限
	int nUseJuanTick ;  //时间间隔
	bool boAutorecallBaobao ;//自动召唤宝宝
	bool boAutoAnswer;
	char sAnswer[50];
	char sBlackName[255];
	bool boAutoSay;
	char sSayString[255];
	int nAutoSayTime;
	bool boSaveChat;
	unsigned char btAddChatType;
	char sAddString[255];
	char  sBossName[255];
	bool boBossA;
	TActorInfo rInfo[100];
	char sChatName[20];
	TMagicInfo rMagic[51];
	char sChatStr[255];
	bool boSendChat;
	bool boHideActor;      //隐藏周围角色-  2014.12.31
	TShared();
	void reset(void);
};


enum TChrAction
{
	caWalk = 0,
	caRun,
	caHorseRun,
	caHit,
	caSpell,
	caSitdown
};

struct TCharDesc
{
	int feature;
	int featureEx;
	TCharDesc();
	void reset(void);
};
// 20120627 重新排列过顺序，其中增加了类型字段，用来以
//后扩充英雄技能，原本的英雄技能是通过描述字段判断的
struct TMagic
{
	char sMagicName[16];
	unsigned short wMagicId;
	unsigned char wMagicType;//类型，0普通，1 英雄的
	unsigned char  bt1;//保留凑数的
	unsigned char TrainLevel[4];
	int MaxTrain[4];
	unsigned char btEffectType;
	unsigned char btEffect;
	unsigned short wSpell;
	unsigned short wPower;
	unsigned short wMagicIdx;
	unsigned long dwDelayTime;
	unsigned char btTrainLv;
	unsigned char btJob;
	unsigned char btDefSpell;
	unsigned char btDefPower;
	unsigned short wMaxPower;
	unsigned char btDefMaxPower;
	unsigned char bt11;
	char sDescr[24]; //：修改长度请考虑实际占用内存大小是否对齐
	TMagic();
	void reset(void);
};

struct TClientMagic
{
	unsigned char Key;//待验证
	unsigned char Level;
	int CurTrain;
	TMagic Def;
	TClientMagic();
	void reset(void);
};
struct THumBaseInfo
{
	int MaxMP;
	int MP;
	THumBaseInfo();
	void reset(void);
};
//本地地图信息，用来客户端跨地图寻路
struct   TLocalMapInfo
{
	std::string sMapName;
	std::vector<void*> Gates;/*TMapGateInfo*/
	TLocalMapInfo();
	void reset(void);
	void release(); //释放
};
struct TMapGateInfo
{
	TLocalMapInfo* SMapInfo; //来源地图信息, 主要用于跨地图寻路
	std::string SMapName;
	int SX;
	int SY; 
	TLocalMapInfo* DMapInfo; //目标地图信息
	std::string DMapName;
	std::string DMapTitle;
	int DX;
	int DY;
	TMapGateInfo* fromGate;
	TMapGateInfo();
	void reset(void);
};

struct TSoundInfo
{
	std::string sFileName;
	unsigned long dwLastTick;
	TSoundInfo();
	void reset(void);
};

struct TSubAbilityExt
{
	int MaxWrathPoint;
	int WrathPoint;
	TSubAbilityExt();
	void reset(void);
};

struct TNakedAbility
{
	int DC;
	int MC;
	int SC;
	int AC;
	int MAC;
	int HP;
	int MP;
	int Hit;
	int Speed;
	int X2;
	TNakedAbility();
	void reset(void);
};

struct TReNewInfo
{
	unsigned short NeedLevel;  //需要等级
	unsigned char Probability ;    //成功几率
	unsigned char DownLevel;     //下降等级到 
	int BonusPoint;    //奖励点数
	unsigned short Count;         //每天转生次数
	unsigned short Crit;          //暴击
	unsigned short w1;    //下面是预留的
	unsigned short w2;
	int i1;
	int i2;
	TReNewInfo();
	void reset(void);
};

//基本物品结构 20120627 重新排列了顺序增加了id，字节尽量对齐
struct TStdItem
{
	char Name[32];//物品名称
	unsigned short ID ;	 //物品id，数据库中的索引编号
	unsigned char job;   //职业
	unsigned char NeedIdentify; //需要记录日志
	unsigned short Reserved;//保留 ：20120801 会有功能用到，比如吃药加血量的单位是百分比还是点数
	//reserved 大概跟掉落有关 可能是这样 8 死亡必掉 10 死亡必掉??? 4无法取下 实际已经无用
	unsigned short StdMode; ///物品分类 0/1/2/3：药， 5/6:武器，10/11：盔甲，
	///15：头盔，22/23：戒指，24/26：手镯，19/20/21：项链
	///20130326新增 100 头饰 101 马铠 102 马鞍  103 马镫 104 缰绳
	///  2013.5.18 200.宝石-
	unsigned short Shape;	//装配外观
	unsigned short Weight; //重量
	unsigned short CharLooks; //:20121220 服务端暂没发现有用，目前改来作为特殊类型属性用，镶嵌物品stdmode 200 这个值标识镶嵌类物品MID
	unsigned short AniCount;
	unsigned short Source;    //源动力
	unsigned short	_throw;
	int Looks;   //外观，即Items.WIL中的图片索引
	int DuraMax;     //最大持久
	int AC;                        //0x1A
	int AC2;
	int MAC;                       //0x1C
	int MAC2;
	int DC;                        //0x1E
	int DC2;
	int MC;                        //0x20
	int MC2;
	int SC;
	int SC2;
	int Need;                      //0x24
	int NeedLevel;                 //0x25
	int Price;                     //0x28
	 char memo[52];
	TStdItem();
	void reset(void);
};

struct TAdditionItem
{
	int id;
	int quality;
	TAdditionItem();
	void reset(void);
};
struct TShortMessage
{
	unsigned short Ident;
	unsigned short wMsg;
	TShortMessage();
	void reset(void);
};

struct TUserCharacterInfo
{
	std::string name;
	unsigned char job;
	unsigned char hair;
	unsigned short level;
	unsigned char sex;
	TUserCharacterInfo();
	void reset(void);
};


struct TDropItem
{
	int x;
	int y;
	int id;
	int Looks;
	std::string sName;
	unsigned long FlashTime;
	unsigned long FlashStepTime;
	int	FlashStep;
	bool boFlash;
	unsigned short stdmode;
	TDropItem();
	void reset(void);
};


struct TClientItem
{
	TStdItem s;
	int MakeIndex;
	int Dura;
	int DuraMax;
	unsigned short btValue[20];
	TClientItem();
	void reset(void);
};

struct TFindNode
{
	int x;
	int y;
	TFindNode();
	void reset(void);
};

struct TTree
{
	int h;
	int x;
	int y;
	unsigned char dir;
	TTree* Father;
	TTree();
	void reset(void);
};

struct TLink
{
	TTree* node;
	int f;
	TLink* next;
	TLink();
	void reset(void);
};

struct TUserItem
{
	int MakeIndex;		 // 序列号吧?
	int wIndex;				//物品id
	unsigned short Dura;	 //当前持久值
	unsigned short DuraMax;	 //最大持久值
	unsigned short btValue[20];
	TUserItem();
	void reset(void);
};

//点击热点
struct TClickPoint
{
	TRect_ rc;
	std::string rstr;
	int id;					//任务脚本的点击热点用来记录任务id
	unsigned char nType;	//类型 默认0 物品图标1
	TClickPoint();
	void reset(void);
};

struct TMovingItem
{
	int index;
	TClientItem item;
	TMovingItem();
	void reset(void);
};

struct TMapWalkXY
{
	bool boWalk;
	int nMonCount;
	int nX;
	int nY;
	TMapWalkXY();
	void reset(void);
};
struct TIconInfo
{
	int imgIndex;
	char title[24];
	TIconInfo();
	void reset(void);
};

struct TGroupItem
{
	std::string FLD_USEITEMS[MAXEQUIP];
	int FLD_RATE[20];
	bool FLD_FLAG[20];
	std::string FLD_TITLE;
	std::string FLD_HINTMSG;
	TGroupItem();
	void reset(void);
};

struct TClientUserStateInfo
{
	int feature;
	unsigned long NAMECOLOR;
	char UserName[ACTORNAMELEN];
	char GuildName[ACTORNAMELEN];
	char GuildRankName[17];
	TClientItem UseItems[MAXEQUIP];
	unsigned char GuildFlag;
	TIconInfo useIcons[10];
	TClientUserStateInfo();
	void reset(void);
};


struct TTaskItem
{
	unsigned short TaskID;
	unsigned short State;
	unsigned short param1;
	unsigned short param2;
	unsigned short param3;
	unsigned short param4;
	TTaskItem();
	void reset(void);
};

struct TClientTaskItem
{
	TTaskItem item;
	std::string Title;
	std::string ShortDesc;
	std::string Desc;
	TClientTaskItem();
	void reset(void);
};

 //扩展的一些魔法的属性，目前是存放需要的属性
struct TClientMagicExInfo
{
	unsigned short wMagIdx;
	unsigned long UpdateTime;
	unsigned long NeedTime;
	int NeedWrathPoint;
	TClientMagicExInfo();
	void reset(void);
};
#endif