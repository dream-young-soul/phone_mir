#include "GameStruct.h"

TVDDataHeader::TVDDataHeader()
{
	reset();
}

void TVDDataHeader::reset()
{
	memset(Title,0,sizeof(Title));
	DBCount = VerFlag = 0;

}

TVDDataInfo::TVDDataInfo()
{
	reset();
}

void TVDDataInfo::reset()
{
	nType = 0;
	n1 = n2 = n3 = 0;
	nSize = 0;
	px = py = 0;

}

TMapHeader::TMapHeader()
{
	reset();
}

void TMapHeader::reset(void)
{
	memset(Title,0,sizeof(Title));
	Width = Height = 0;
	UpdateDate = 0;
	ZipSize = 0;
	memset(Reserved,0,sizeof(Reserved));
}

TMapInfo::TMapInfo()
{
	reset();
}

void TMapInfo::reset()
{
	BkAree = 0;
	BkImg = 0;
	Area = 0;
	FrImg = 0;
	DoorIndex = 0;
	DoorOffset = 0;
	AniFrame = 0;
	AniTick = 0;
	light = 0;
	flags = 0;
}

TPoint::TPoint()
{
	reset();
}

void TPoint::reset(void)
{
	x = y = 0;
}

TRect_::TRect_()
{
	reset();
}

void TRect_::reset(void)
{
	Left = 0;
	Top = 0;
	Right = 0;
	Bottom = 0;
}

void TRect_::Rect(int ALeft,int ATop,int ARight,int ABottom)
{
	Left = ALeft;
	Top = ATop;
	Right = ARight;
	Bottom = ABottom;

}

TAbility::TAbility()
{
	reset();
}

void TAbility::reset(void)
{
	Level = 0;                      
	AC = 0;  //防御
	AC2 = 0;
	MAC = 0;   //魔防
	MAC2 = 0;
	DC = 0;    //攻击力
	DC2 = 0;
	MC = 0;   //魔法
	MC2 = 0;
	SC = 0;   //道术
	SC2 = 0;
	HP = 0;                    
	MP = 0;                        
	MaxHP = 0;                   
	MaxMP = 0;                   
	Exp = 0;                   
	MaxExp = 0;                
	Weight = 0;                   //骑宠数据拿来当星星数据使用 2014.326 Loser.DieYoung
	MaxWeight = 0;                
	WearWeight = 0;              
	MaxWearWeight = 0;           
	HandWeight = 0;              
	MaxHandWeight = 0;  
}

TUseMagicInfo::TUseMagicInfo()
{
	reset();
}

void TUseMagicInfo::reset(void)
{
	ServerMagicCode = 0;
	MagicSerial = 0;
	target = 0;
	EffectType = mtReady ;
	int EffectNumber = 0;
	int targx = 0;
	int targy = 0;
	bool Recusion = false;
	int anitime = 0;
}

TActionInfo::TActionInfo()
{
	reset();
}

void TActionInfo::reset()
{
	start = 0;
	frame = 0;
	skip = 0;
	ftime = 0;
	usetick = 0;
}

TMonsterAction::TMonsterAction()
{
	reset();
}
void TMonsterAction::reset()
{
	ActStand.reset() ;
	ActWalk.reset();   
	ActRun.reset();
	ActAttack.reset();
	ActCritical.reset();
	ActStruck.reset();
	ActDie.reset();
	ActDeath.reset();
	ActSpell.reset();
	ActAttack1.reset();
	ActAttack2.reset();
	ActAttack3.reset();
	ActAttack4.reset();
	ActAttack5.reset();
	ActAttack6.reset();
}

TNetEvent::TNetEvent()
{
	reset();
}

void TNetEvent::reset(void)
{
	event_type = TNETEVENTTYPE::NORMAL;
	msg.reset();
	Body = "";
}

TMessageBodyWL::TMessageBodyWL()
{
	reset();
}

void TMessageBodyWL::reset(void)
{
	lParam1 = lParam2 = 0;
	lTag1 = lTag2 = 0;
}

TChrMsg::TChrMsg()
{
	reset();
}

void TChrMsg::reset(void)
{
	Ident = 0;
	x = 0;
	y = 0;
	dir = 0;
	State = 0;
	feature = 0;
	saying = "";
	sound = 0;
}

TActorInfo::TActorInfo()
{
	reset();
}
void TActorInfo::reset(void)
{
	memset(name,0,sizeof(name));
	memset(dirChar,0,sizeof(dirChar));
	nx = 0;
	ny = 0;
	memset(sType,0,sizeof(sType));
}
TMagicInfo::TMagicInfo()
{
	reset();
}
void TMagicInfo::reset(void)
{
	memset(name,0,sizeof(name));
	Biao = 0;
	Fu = 0;
	magicID = 0;

}

TShared::TShared()
{
	reset();
}

void TShared::reset(void)
{
	boLongAttack = false;           
	boSmartLongAttack  = false;
	boShowUserName = false;          
	boShowInformation = false;       
	stimenow = "";                
	chrname = "";              
	leftchr = 0;                    
	topchr = 0;                   
	chrnameeditshow = false;      
	left = 0;
	top = 0;
	memset(sID,0,sizeof(sID));
	memset(sPass,0,sizeof(sPass));
	boEnter = false;
	btLoad = 0;
	memset(name,0,sizeof(name));
	boWarrC = true;
	bocloseform = false;
	boShowBlood = false;
	boShowNumBlood = true;
	boRunAndRun = false;
	boDuraAlern = false;
	boClearBody = false;  
	boNoHit = false;   
	boAttackLock = false;    
	boShowAttactTarget = false;
	boForceExit = false;
	boNoStone = true;
	boAttackChangeColor = false;
	boTeamChangeColor = false;
	boUseMagicDownHorse = false;   
	boCloseExp = false;
	boItemFlash = true;
	boShowItem = false;
	boAutoPickUp = true; 
	boShowLocalFashion = false;
	boAutoPickUpDrug = true ;
	boAutoPickUpGold  = true; 
	boCTRLPickUp = false;    
	boBindItem = false;
	unsbtMouseMiddle = 0;
	btMouseMiddelMagic = 0;
	boWarrLock = 0;
	boWarrTbs = false;
	boWarrPx = false;
	boAutoThree = false;
	boAutoFour = false;
	boBuffTime = false;
	boMoDun = true;
	boMoHiddent = false;
	boAutoDF = false;  
	memset(sProtect,0,sizeof(sProtect));
	boHpMin = false;   
	nHpMin = 0; 
	nHpTick = 0; 
	boMpMin = false;    
	nMpMin = 0; 
	nMpTick = 0; 
	boHPMPfast = false  ;
	nHPMPFastMin = 0 ;
	nHPMPFastTack = 0 ;
	boUseJuan = 0;   
	nUseJuanMin = 0 ;  
	nUseJuanTick = 0 ;  
	boAutorecallBaobao = false ;
	boAutoAnswer = false;
	memset(sAnswer,0,sizeof(sAnswer));
	memset(sBlackName,0,sizeof(sBlackName));

	boAutoSay = false;
	memset(sSayString,0,sizeof(sSayString));

	nAutoSayTime = 0;
	boSaveChat = false;
	btAddChatType = 0;
	memset(sAddString,0,sizeof(sAddString));
	memset(sBossName,0,sizeof(sBossName));
	boBossA = false;
	memset(rInfo,0,sizeof(rInfo));
	memset(sChatName,0,sizeof(sChatName));
	memset(rMagic,0,sizeof(rMagic));
	memset(sChatStr,0,sizeof(sChatStr));
	boSendChat = false;
	boHideActor = false;      //隐藏周围角色-  2014.12.31
}

THumanAction::THumanAction()
{
	reset();
}
void THumanAction::reset(void)
{	
	ActStand.reset();
	 ActWalk.reset();
	 ActRun.reset();
	 ActRush.reset();
	 ActWarMode.reset();
	 ActHit.reset();
	 ActHeavyHit.reset();
	 ActBigHit.reset();
	 ActFireHitReady.reset();
	 ActTSpell.reset();
	 ActFSpell.reset();
	 ActSitdown.reset();
	 ActStruck.reset();
	 Act34Hit.reset();
	 Act35Hit.reset();
	 Act103Hit.reset();
	 ActKQStruck.reset();
	 ActDie.reset();
	 ActMeditation.reset();
}

TCharDesc::TCharDesc()
{
	reset();
}

void TCharDesc::reset(void)
{
	feature = 0;
	featureEx = 0;
}

TMagic::TMagic()
{
	reset();
}

void TMagic::reset(void)
{
	memset(sMagicName,0,sizeof(sMagicName));
	wMagicId = 0;
	wMagicType = 0;
	bt1 = 0;
	TrainLevel[0] = TrainLevel[1] = TrainLevel[2] = TrainLevel[3] = 0;
	MaxTrain[0] = MaxTrain[1] = MaxTrain[2] = MaxTrain[3] = 0;
	btEffectType = 0;
	btEffect = 0;
	wSpell = 0;
	wPower = 0;
	wMagicIdx = 0;
	dwDelayTime = 0;
	btTrainLv = 0;
	btJob = 0;
	btDefSpell = 0;
	btDefPower = 0;
	wMaxPower = 0;
	btDefMaxPower = 0;
	bt11 = 0;
	memset(sDescr,0,sizeof(sDescr));
}

TClientMagic::TClientMagic()
{
	reset();
}

void TClientMagic::reset(void)
{
	Key = 0;
	Level = 0;
	CurTrain = 0;
	Def.reset();
}

THumBaseInfo::THumBaseInfo()
{
	reset();
}

void THumBaseInfo::reset(void)
{
	MaxMP = 0;
	MP = 0;
}

TLocalMapInfo::TLocalMapInfo()
{
	reset();
};

void TLocalMapInfo::reset(void)
{
	sMapName = "";
	Gates.clear();

}

void TLocalMapInfo::release() //释放
{
	sMapName = "";
	std::vector<void*>::iterator it;
	for(it = Gates.begin();it != Gates.end();it++)
	{
		TMapGateInfo* info = (TMapGateInfo*)*it;
		delete info;
	}
	Gates.clear();
}

TMapGateInfo::TMapGateInfo()
{
	reset();
}
void TMapGateInfo::reset(void)
{
	SMapInfo = nullptr;
	SMapName = "";
	SX = 0;
	SY = 0; 
	DMapInfo = nullptr;
	DMapName = "";
	DMapTitle = "";
	DX = 0;
	DY = 0;
	fromGate = nullptr;
}

TSoundInfo::TSoundInfo()
{
	reset();
}

void TSoundInfo::reset(void)
{
	sFileName = "";
	dwLastTick = 0;
}

TSubAbilityExt::TSubAbilityExt()
{
	reset();
}

void TSubAbilityExt::reset(void)
{
	MaxWrathPoint = 0;
	WrathPoint = 0;
}

TNakedAbility::TNakedAbility()
{
	reset();
}

void TNakedAbility::reset(void)
{
	DC = 0;
	MC = 0;
	SC = 0;
	AC = 0;
	MAC = 0;
	HP = 0;
	MP = 0;
	Hit = 0;
	Speed = 0;
	X2 = 0;
}

TReNewInfo::TReNewInfo()
{
	reset();
}

void TReNewInfo::reset(void)
{
	NeedLevel = 0;  //需要等级
	Probability  = 0;    //成功几率
	DownLevel = 0;     //下降等级到 
	BonusPoint = 0;    //奖励点数
	Count = 0;         //每天转生次数
	Crit = 0;          //暴击
	w1 = 0;    //下面是预留的
	w2 = 0;
	i1 = 0;
	i2 = 0;
}


TStdItem::TStdItem()
{
	reset();
};

void TStdItem::reset(void)
{
	memset(Name,0,sizeof(Name));

	ID = 0;	
	job = 0; 
	NeedIdentify = 0; 
	Reserved = 0;
	StdMode = 0;
	Shape = 0;	
	Weight = 0;
	CharLooks = 0; 
	AniCount = 0;
	Source = 0;   
	_throw = 0;
	Looks = 0;   
	DuraMax = 0;    
	AC = 0;                      
	AC2 = 0;
	MAC = 0;                     
	MAC2  = 0;
	DC = 0;                       
	DC2 = 0;
	MC = 0;                       
	MC2 = 0;
	SC = 0;
	SC2 = 0;
	Need = 0;                   
	NeedLevel = 0;            
	Price = 0; 
	memset(memo,0,sizeof(memo));
}

TAdditionItem::TAdditionItem()
{
	reset();
	
}
void TAdditionItem::reset(void)
{
	id = quality = 0;
}
TShortMessage::TShortMessage()
{
	reset();
}

void TShortMessage::reset(void)
{
	Ident = 0;
	wMsg = 0;
}

TUserCharacterInfo::TUserCharacterInfo()
{
	reset();
}
void TUserCharacterInfo::reset(void)
{
	name = "";
	job = 0;
	hair = 0;
	level = 0;
	sex = 0;
}

TDropItem::TDropItem()
{
	reset();
}
void TDropItem::reset(void)
{
	x = 0;
	y = 0;
	id = 0;
	Looks = 0;
	sName = "";
	FlashTime = 0;
	FlashStepTime = 0;
	FlashStep = 0;
	boFlash = 0;
	stdmode = 0;
}

TClientItem::TClientItem()
{
	reset();
}

void TClientItem::reset(void)
{
	s.reset();
	MakeIndex = 0;
	Dura = 0;
	DuraMax = 0;
	memset(&btValue[0],0,sizeof(btValue));
}


TFindNode::TFindNode()
{
	reset();
}

void TFindNode::reset(void)
{
	x = 0;
	y = 0;
}

TTree::TTree()
{
	reset();
}

void TTree::reset(void)
{
	h = 0;
	x = 0;
	y = 0;
	dir = 0;
	Father = nullptr;
}

TLink::TLink()
{
	reset();
}

void TLink::reset(void)
{
	node = nullptr;
	f = 0;
	next = nullptr;
}


TUserItem::TUserItem()
{
	reset();
}
void TUserItem::reset(void)
{
	MakeIndex = wIndex = 0;
	DuraMax = Dura = 0;
	memset(&btValue[0],0,sizeof(btValue));
}

TClickPoint::TClickPoint()
{
	reset();
}

void TClickPoint::reset(void)
{
	rc.reset();
	rstr = "";
	id = 0;
	nType = 0;
}

TMovingItem::TMovingItem()
{
	reset();
}

void TMovingItem::reset(void)
{
	index = 0;
	item.reset();
}

TMapWalkXY::TMapWalkXY()
{
	reset();
}

void TMapWalkXY::reset(void)
{
	boWalk =false;
	nMonCount = nX = nY = 0;

}

TIconInfo::TIconInfo()
{
	reset();
}

void TIconInfo::reset(void)
{
	imgIndex = 0;
	memset(title,0,sizeof(title));
}

TGroupItem::TGroupItem()
{
	reset();
}

void TGroupItem::reset(void)
{
	for(int i= 0;i<MAXEQUIP;i++)
	{
		FLD_USEITEMS[i] ="";
	}
	std::string FLD_USEITEMS[MAXEQUIP];
	memset(&FLD_RATE[0],0,sizeof(FLD_RATE));
	memset(&FLD_FLAG[0],0,sizeof(FLD_FLAG));
	FLD_TITLE = "";
	FLD_HINTMSG = "";
}

TClientUserStateInfo::TClientUserStateInfo()
{
	reset();

}
void TClientUserStateInfo::reset(void)
{
	feature = 0;
	NAMECOLOR = 0;
	memset(UserName,0,sizeof(UserName));
	memset(GuildName,0,sizeof(GuildName));
	memset(&UseItems[0],0,sizeof(UseItems));
	GuildFlag = 0;
	memset(&useIcons[0],0,sizeof(useIcons));

}

TTaskItem::TTaskItem()
{
	reset();
}

void TTaskItem::reset(void)
{
	TaskID = 0;
	State = 0;
	param1 = param2 = param3 = param4 = 0;
}

TClientTaskItem::TClientTaskItem()
{
	reset();
}

void TClientTaskItem::reset(void)
{
	item.reset();
	Title = ShortDesc = Desc ="";

}

TClientMagicExInfo::TClientMagicExInfo()
{
	reset();
}

void TClientMagicExInfo::reset(void)
{
	wMagIdx = UpdateTime = NeedTime = NeedWrathPoint = 0;
}