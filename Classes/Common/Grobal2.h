#ifndef GROBAL2_H_
#define GROBAL2_H_
#include "../Net/EnDecode.h"
#include <string>

const int UNITX = 48;
const int UNITY = 32;
const int LONGHEIGHT_IMAGE = 35;
const int HALFX  = 24;
const int HALFY  = 16;
const int MAXMAGIC = 20;  
const int LOGICALMAPUNIT  = 80;

#define ACTORNAMELEN      30

#define DEFAULT_FONTSIZE 12 //默认字体大小
//一次性最多1024条队列数据- 溢出不管啦。。
const int MAX_NETEVENT_COUNT = 1024;

#define MAKEWORD_(a, b)      ((unsigned short)(((unsigned char)(((unsigned long)(a)) & 0xff)) | ((unsigned short)((unsigned char)(((unsigned long)(b)) & 0xff))) << 8))
#define MAKELONG_(a, b)      ((long)(((unsigned short)(((unsigned long)(a)) & 0xffff)) | ((unsigned long)((unsigned short)(((unsigned long)(b)) & 0xffff))) << 16))
#define LOWORD_(l)           ((unsigned short)(((unsigned long)(l)) & 0xffff))
#define HIWORD_(l)           ((unsigned short)((((unsigned long)(l)) >> 16) & 0xffff))
#define LOBYTE_(w)           ((unsigned char)(((unsigned long)(w)) & 0xff))
#define HIBYTE_(w)           ((unsigned char)((((unsigned long)(w)) >> 8) & 0xff))

unsigned char RACEfeature(int cfeature);
unsigned char HAIRfeature(int cfeature);
unsigned char DRESSfeature(int cfeature);
unsigned char WEAPONfeature(int cfeature);
unsigned char Horsefeature(int cfeature);
unsigned char Effectfeature(int cfeature);
unsigned char Colorfeature(int cfeature);
unsigned short APPRfeature(int cfeature);
int PrivDir(int ndir);
int NextDir(int ndir);
int GetDistance(int sx, int sY, int dx, int dy);
int GetFlyDirection(int sx,int sy,int ttx,int tty);
std::string GetValidStr3Ex(std::string src,std::string &dest,char divider,bool utf8 = false);
std::string ArrestStringEx(std::string Source,std::string SearchAfter,std::string ArrestBefore,std::string& ArrestStr);

typedef struct tagDefaultMessage
{
	int	Recog;
	int	Ident;
	int	Param;
	int	Tag;
	int	Serise;
	tagDefaultMessage();
	void reset(void);
}DEFAULTMESSAGE, *PDEFAULTMESSAGE;
#define	MAKEDEFMSG(m, i, r, p, t, s)	{(m)->Recog = r; (m)->Ident = i; (m)->Param = p; (m)->Tag = t; (m)->Serise = s;}
#define MAX_(x,y) (((x) < (y)) ? (y) : (x))
static const int NEXTX[8] = {0, 1, 1, 1, 0, -1, -1, -1};
static const int NEXTY[8] = {-1, -1, 0, 1, 1, 1, 0, -1};
//协议头编码大小
#define	DEFBLOCKSIZE	27   /*16*/

#define     EncodeDefMessage(buf,msg) fnEncode6BitBufA((char*)msg,buf,sizeof(DEFAULTMESSAGE),DEFBLOCKSIZE)
#define     DecodeDefMessage(msg,buf) fnDecode6BitBufA(buf,(char*)msg,sizeof(DEFAULTMESSAGE))

#define CLIENT_VERSION_NUMBER  220540328
#define CLIENT_VERSION_NUMBERFIX  113022060

#define ENEMYCOLOR 69
#define RUN_MINHEALTH 10 //少于这个血量值为走路
#define MAXWPEFFECTFRAME 5
#define   DEFSPELLFRAME     10
#define  HUMANFRAME  3000
#define  STATE_OPENHEATH 1
// 20120821 原本RC_和RCC_应该是分别表示服务器端和客户端类型定义，但
///后续不断演变中此定义使用较为混乱，要修改会有较多影响。现决定对原有定义
///  不做修改，后续开发中，用RS_表示服务器端race定义，RC_表示客户端的定义
#define RC_PLAYOBJECT      0
#define RC_GUARD			12		//大刀守卫
#define RC_PLAYMOSTER      150              //人形怪物
#define RC_HEROOBJECT      66              //英雄
#define RC_GUARD           12               //大刀守卫
#define RC_PEACENPC        15
#define RC_MON0            20        //怪物0类型
#define RC_ANIMAL          50
#define RC_MONSTER         80
#define RC_NPC             10
#define RC_ARCHERGUARD     112    //弓箭手
#define RC_PLANT           200   //植物
#define RC_MINE            201//矿石类
#define RC_HORSE           210      //马匹类的
#define RC_BIAOCHE         222//镖车   //服务器端的值

#define RCC_PLANT     160//植物类 服务器端的值
#define RCC_MINE     161//矿物类 服务器端的值
#define RCC_LIANGONG  162//练功怪物，掉血给经验的
#define RCC_LIANGONG1  163//练功怪物，掉血给经验的
#define RCC_USERHUMAN     RC_PLAYOBJECT
#define RCC_MERCHANT       RC_ANIMAL
#define  RCC_GUARD          RC_GUARD
#define RS_HORSE           165 //马匹 服务器端值

#define SM_WINEXP		44		//获得经验
#define SM_LEVELUP		45		//升级
#define SM_BAGITEMS		201		//包裹数据
#define SM_PASSWD_FAIL   503      //登录密码失败
#define SM_PASSOK_SELECTSERVER 529 //登录成功，开始选择服务器
#define CM_SELECTSERVER    104      //客户端发送选择服务器
#define SM_SELECTSERVER_OK  530     //选择服务器成功
#define SM_STARTPLAY       525      //进入游戏
#define SM_STARTFAIL       526      //选择服务器进游戏失败
#define SM_SENDNOTICE      658
#define SM_ITEMSHOW 610			//掉落物品显示
#define SM_ITEMHIDE 611			//掉落物品隐藏
#define SM_WEIGHTCHANGED 622
#define SM_IDPASSWORDOK  32001
#define SM_HORSERUN        5
#define SM_RUSH            6
#define SM_RUSHKUNG       7               //野蛮冲撞
#define SM_FIREHIT        8                //烈火
#define SM_BACKSTEP        9             
#define SM_TURN				10				//转向
#define SM_WALK            11               //走
#define SM_SITDOWN         12
#define SM_RUN            13               //跑
#define SM_HIT             14               //砍
#define SM_HEAVYHIT       15               //
#define SM_BIGHIT          16               //
#define SM_SPELL         17               //使用魔法
#define SM_POWERHIT       18               //攻杀
#define SM_LONGHIT         19               //刺杀
#define SM_DIGUP         20
#define SM_DIGDOWN         21
#define SM_FLYAXE         22
#define SM_LIGHTING       23
#define SM_WIDEHIT        24
#define SM_CRSHIT         25   //抱月刀
#define SM_TWINHIT         26   //开天斩重击
#define SM_ALIVE           27
#define SM_MOVEFAIL        28              //
#define SM_HIDE            29               //
#define SM_DISAPPEAR       30
#define SM_STRUCK          31
#define SM_DEATH           32
#define SM_SKELETON        33
#define SM_NOWDEATH        34
#define SM_34SKILLHIT     35               //莲月
#define SM_35SKILLHIT      36              //翔空
#define SM_103SKILLHIT    37
#define SM_REMOTEHIT	38
#define SM_MONSPELL 39
#define SM_FEATURECHANGED 41
#define SM_USERNAME 42
#define SM_MONSPELLEFF 47
#define SM_MAGICEFF 49
#define SM_ABILITY 52		//人物属性
#define  SM_HEALTHSPELLCHANGED 53
#define SM_MAPDESCRIPTION 54
#define SM_GAMEGOLDNAME 55
#define SM_SYSMESSAGE 100 //系统消息
#define SM_ADDITEM 200
#define SM_UPDATEITEM 203
#define SM_ADDMAGIC 210 //新学技能
#define SM_SENDMYMAGIC 211 //返回技能信息
#define SM_EATITEM 609
#define SM_TAKEON_OK 615 //穿戴成功
#define SM_SENDUSEITEMS 621 //获得身上装备信息
#define SM_CLEAROBJECTS 633
#define  SM_BUTCH 637
#define SM_MAGICFIRE 638
#define SM_MAGICFIRE_FAIL 639
#define SM_MERCHANTSAY 643 //npc对话
#define SM_DURACHANGE 642 //损耗度
#define SM_MERCHANTDLGCLOSE 644 //关闭npc对话框
#define SM_CHANGELIGHT 654 //游戏亮度- 貌似作废哒
#define SM_CHANGENAMECOLOR 656 //改变名字颜色
#define SM_CHARSTATUSCHANGED 657
#define SM_AREASTATE 708
#define SM_SUBABILITY 752 
#define SM_SPACEMOVE_HIDE  800
#define SM_GHOST 803
#define MAXMAGICTYPE 16
#define SM_SHOWEVENT 804
#define SM_HIDEEVENT 805
#define SM_SPACEMOVE_HIDE2  806
#define SM_SPACEMOVE_SHOW  801  //飞到某地后 命令瞬移 gm飞
#define SM_SPACEMOVE_SHOW2 807   //技能飞 瞬间移动技能
#define SM_SPACEMOVE_SHOW3  808
#define SM_ADJUST_BONUS 811
#define CM_PICKUP	1001
#define CM_BUTCH 1007
#define CM_CLICKNPC 1010
#define CM_MERCHANTDLGSELECT 1011 //npc对话
#define CM_IDPASSWORD	2001  //帐号密码
#define CM_THROW           3005
#define CM_HORSERUN 3009
#define CM_TURN 3010
#define CM_SITDOWN 3012
#define CM_RUN            3013
#define CM_HIT 3014
#define CM_HEAVYHIT        3015//挖矿//stdmode=6技能可以打出的，可能是双手武器技能，暂时无用
#define CM_BIGHIT 3016
#define CM_SPELL 3017
#define  CM_POWERHIT 3018 //攻杀
#define CM_LONGHIT 3019 //刺杀
#define  CM_REMOTEHIT       3020
#define CM_WIDEHIT         3024             //半月
#define CM_FIREHIT         3025             //烈火
#define CM_34SKILLHIT      3026             //莲月
#define CM_35SKILLHIT      3027            //莲月
#define CM_103SKILLHIT     3028
#define CM_SAY             3030
#define CM_CRSHIT          3036             //抱月刀
#define CM_TWNHIT          3037            //开天斩重击
#define CM_TWINHIT         CM_TWNHIT  //开天斩重击
#define CM_PHHIT           3038;            //破魂斩
#define SM_CREATEHERO 5004
#define CM_ACTORHP 6000
#define SM_ACTORHP 6001
#define SM_SERVERCONFIG 20002
#define CM_QUERYCHR       24001   //查询角色
#define CM_NEWCHR         24002  //新建角色/
#define CM_DELCHR		  24003  //删除角色
#define CM_SELCHR         24004  //选择角色
#define SM_QUERYCHR       24005 //服务器返回角色信息 *名字/职业/头发，暂时无用/等级/性别/
#define SM_QUERYCHR_FAIL  24006  //服务器返回角色失败
#define SM_DELCHR_SUCCESS  24009 //删除角色成功
#define SM_DELCHR_FAIL     24010 //失败
#define SM_TASK				25001 //任务
#define CM_TASKSELECT		25004
#define SM_WALKTO			25007 //自动走到目标
#define	SM_SHOWIMGMSG		25008 //显示完成任务
#define SM_MEDITATION  25042	//打坐 
#define SM_KILLMON 25044 //自动打怪，服务器
#define SM_SHOWPACKAGE 25120 //显示礼包图标
#define CM_GETICONS 25121
#define SM_GETICONS 25122
#define SM_SENDJINGMAI 25225 //经脉信息
#define SM_SPELLNEED 25253 //额外的技能属性
#define SM_PACKS 25295  //接收一个礼包图标
#define CM_LOGINNOTICEOK  1018   //确定登录通知
#define SM_LOGON          50
#define CM_LOGON          2 
#define CM_WANTMINIMAP          1033 
#define CM_WALK           3011
#define CM_QUERYBAGITEMS          81 
#define CM_QUERYUSERNAME          80 
#define SM_CHANGEMAP      634        //改变了地图
#define SM_MAGIC_LVEXP		640		//技能升级
#define SM_NEWMAP         51      //新地图
#define SM_NEWCHR_SUCCESS  24007 //新建角色成功
#define SM_NEWCHR_FAIL     24008 //新建角色失败
#define  SM_MISS 25298
#define  SM_THROW         65069


//方向
#define DR_UP             0
#define DR_UPRIGHT        1
#define DR_RIGHT          2
#define DR_DOWNRIGHT      3
#define DR_DOWN           4
#define DR_DOWNLEFT       5
#define DR_LEFT           6
#define DR_UPLEFT         7

#define U_DRESS           0             //衣服
#define U_WEAPON          1              //武器
#define U_RIGHTHAND       2              //右手
#define U_NECKLACE        3              //项链
#define U_HELMET          4              //头盔
#define U_ARMRINGL        5              //
#define U_ARMRINGR        6
#define U_RINGL           7              //
#define U_RINGR           8
#define U_BUJUK           9               //符 现在用来放置宝石
#define U_BELT            10              //勋章/花
#define U_BOOTS           11              //鞋
#define U_CHARM           12            //宝石 现在用来防止魔血石

#define U_WINGS           13              //翅膀
#define U_FASHIONDRESS    14              //时装
//骑宠穿戴位置
#define HU_Headdress      0       //头饰
#define HU_armor          1       //马铠
#define HU_Saddle         2       //马鞍
#define HU_Stirrup        3       //马镫
#define HU_Rein           4       //缰绳
#define HU_GEM            5      //宝石魔血石

#define ET_DIGOUTZOMBI    1
#define ET_PILESTONES     3
#define ET_HOLYCURTAIN    4 //安全区
#define ET_FIRE           5
#define ET_SCULPEICE      6

#define MAXBAGITEMS		64 //最大包裹数量
#define MAXEQUIP		15 //最大装备格子
int GetBack(int dir);
int GetNpcOffset(int nAppr);
int GetCodeMsgSize(double x);

#endif