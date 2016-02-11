#include "Actor.h"
#include "./Common/Grobal2.h"
#include "./Common/SoundUtil.h"
#include "MShare.h"
#include "FrmMain.h"
#include "PlayScene.h"
#include "VDImage.h"
#include "MapUnit.h"
#include "./Common/VDImageDatas.h"

#if	defined(WIN32)
#include <windows.h>
#endif
TActor::TActor(void)
{
	RealActionMsg.reset();
	m_MsgList.clear();
	m_nShiftX = 0;
	m_nShiftY = 0;
	m_nRx = 0;
	m_nRy = 0;
	g_boAttackSlow = false;
	g_boMoveSlow = false;
	g_nMoveSlowLevel = 0;
	m_boIceMoveSlow = false;
	m_nIceMoveSlowLevel = 0;
	IsAddBlood = false;
	AddBloodNum = 0;
	AddBloodFram = 0;
	AddBloodTime = GetTickCount();
	AddBloodStartTime = 0;
	IsEatItem = 0;
	EatItemNum = 0;
	EatItemFram = 0;
	EatItemTime = GetTickCount();
	EatItemStartTime = 0;
	m_btDressFrame = 0;         
	m_nDressTime = GetTickCount();              
	m_btDressType = 0;               
	m_btWeaponFrame = 0;            
	m_nWeaponTime = GetTickCount();            
	m_nEffStruckFrame = 0;
	m_boDieEff = false;
	m_boFightEff = false;
	m_nFightEffFrame = 0;
	m_nFightEffTime = GetTickCount();
	m_nFightEffNum = 0;
	m_nRecogId = 0;
	m_nCurrX = 0;
	m_nCurrY = 0;
	m_btDir;
	m_bWings;
	m_nHalo = 0; 
	m_btSex = 0;
	m_btRace = 0;
	m_btHair = 0;
	m_btDress = 0;
	m_btWeapon = 0;
	m_btHorse = 0;
	m_btEffect = 0;
	m_btDressColor = 0;
	m_btJob = 0;
	m_wAppearance = 0;
	m_btDeathState = 0;
	m_nFeature = 0;
	m_nFeatureEx = 0;
	m_nState = 0;
	m_nEatItemIndex = 0;
	m_boYy = m_boMd = false;
	m_boDeath = false;
	m_boSkeleton = false;
	m_boDelActor = false;
	m_boDelActionAfterFinished = false;
	m_sDescUserName = ""; 
	m_sGuildName = "";    
	m_sGuildRankName = "";
	m_sRankName = "";   
	m_sDearName = "";   
	m_sMasterName = "";
	memset(&m_NameImg[0],0,sizeof(m_NameImg));
	m_sUserName = "";
	long m_nNameColor = 0;
	m_Abil.reset() ;
	m_nGold = 0;
	m_nGameGold = 0;
	m_nGamePoint = 0; 
	m_nHitSpeed = 0;
	m_boVisible = true;
	m_boHoldPlace = true;
	m_btLifeAttrib = 0;
	m_SayingArr = "";
	memset(&m_SayWidthsArr[0],0,sizeof(m_SayWidthsArr));
	m_dwSayTime = 0;
	m_nSayX = 0;
	m_nSayY = 0;
	m_nSayLineCount = 0;
	m_nWx = 0;
	m_nWy = 0;
	m_nPx = 0;
	m_nHpx = 0;
	m_nHopx = 0;
	m_nHospx = 0;
	m_nWpx = 0;
	m_nWspx = 0;
	m_nSpx = 0;
	m_nEPx = 0;                   
	m_nPy = 0;
	m_nHpy = 0;
	m_nHopy = 0;
	m_nHospy = 0;
	m_nWpy = 0;
	m_nWsPy = 0;
	m_nSpy = 0;
	m_nEpy = 0;                  
	m_nSType = 0;
	m_nDownDrawLevel = 0;
	m_nTargetX = 0;
	m_nTargetY = 0;
	m_nTargetRecog = 0;
	m_nHiterCode = 0;
	m_nMagicNum = 0;
	m_nCurrentEvent = 0;
	m_boDigFragment = false;
	m_boThrow = false;
	m_nBodyOffset = 0;
	m_nHairOffset = 0;
	m_nHumWinOffset = 0;
	m_nWeaponOffset = 0;
	m_boUseMagic = false;
	m_btMagicNum = 0;
	m_boHitEffect = false;
	m_boMagicEff = false;
	m_nMagicFrame = 0;
	m_nMagicFrameTime = GetTickCount();
	m_nMagicFrameStart = 0;
	m_boUseEffect = 0;
	m_nHitEffectNumber = 0;
	m_dwWaitMagicRequest = 0;
	m_nWaitForRecogId = 0;
	m_nWaitForFeature = 0;
	m_nWaitForStatus = 0;
	m_dwWaitMagicmode1 = 0;
	m_dwWaitMagicmode2 = 0;
	m_nCurEffFrame = 0;  
	m_nSpellFrame = DEFSPELLFRAME;   
	m_CurMagic.reset();
	m_nGenAniCount = 0;
	m_boOpenHealth = false;   
	m_noInstanceOpenHealth = false; 
	m_dwOpenHealthStart = 0;
	m_dwOpenHealthTime = GetTickCount();
	m_BodySurface = nullptr;
	m_BodySSurface = nullptr;
	m_HorseBodySurface = nullptr;
	m_WringsSurface = nullptr; 
	bool m_boGrouped = 0;
	m_nCurrentAction = 0;
	m_boReverseFrame = false;
	m_boWarMode = false;
	m_dwWarModeTime = GetTickCount();
	m_boSitDownMode = 0; 
	m_dwSitDownModeTime = GetTickCount();
	m_nChrLight = 0;
	m_nMagLight = 0;
	m_nRushDir = 0;
	m_nXxI = 0;
	m_boLockEndFrame = false;
	m_dwLastStruckTime = 0;
	m_dwSendQueryUserNameTime = 0;
	m_dwDeleteTime = GetTickCount();
	m_nMagicStruckSound = 0;
	m_boRunSound = false;
	m_nFootStepSound = -1;
	m_nStruckSound = 0;
	m_nStruckWeaponSound = 0;
	m_nAppearSound = 0;
	m_nNormalSound = -1;
	m_nAttackSound = -1;
	m_nWeaponSound = -1;
	m_nScreamSound = -1;
	m_nDieSound = -1;
	m_nDie2Sound = -1;
	m_nMagicStartSound = 0;
	m_nMagicFireSound = 0;
	m_nMagicExplosionSound = 0;
	m_Action = nullptr;
	m_btSpellAct = 0;
	m_MonMagiList.clear();
	m_bMeditation = false; 

	m_nStartFrame = 0;
	m_nEndFrame = 0;
	m_nCurrentFrame = -1;
	memset(m_Spell,0,sizeof(m_Spell));
	m_btIdx = 0;
	m_nEffectStart = 0;
	m_nEffectFrame = -1;
	m_nEffectEnd = 0;
	m_dwEffectStartTime = GetTickCount();
	m_dwEffectFrameTime = GetTickCount();
	m_dwFrameTime = GetTickCount();
	m_dwStartTime = GetTickCount();
	m_dwStartMoveTime = GetTickCount();

	m_nMaxTick = 0;
	m_nCurTick = 0;
	m_nMoveStep = 0;
	m_boMsgMuch = false;
	m_dwStruckFrameTime = GetTickCount();
	m_nCurrentDefFrame = 0;
	m_dwDefFrameTime = GetTickCount();
	m_nDefFrameCount = 0;
	m_nSkipTick = 0;
	m_nIceSkipTickx = 0;
	m_dwSmoothMoveTime = GetTickCount();
	m_dwGenAnicountTime = GetTickCount();
	m_dwLoadSurfaceTime = GetTickCount();
	m_nOldx = 0;
	m_nOldy = 0;
	m_nOldDir = 0;
	m_nActBeforeX = 0;
	m_nActBeforeY = 0;
	m_nWpord = 0;
	eax = eay = 0;
	eax1 = eay1 = 0;

}


TActor::~TActor(void)
{
}

void TActor::UpdateMsg(int wIdent,int nX, int nY, int ndir,int  nFeature,int nState,char* sStr, int nSound)
{
	TChrMsg* Msg;
	std::vector<TChrMsg*>::iterator it;
	std::vector<int> list;
	int i = 0;
	for(it = m_MsgList.begin();it != m_MsgList.end();it++)
	{
		Msg =*it;
		if(this == g_MySelf && Msg->Ident >= 3000 && Msg->Ident <=  3099 || Msg->Ident == wIdent)
		{
			list.push_back(i);
		}
		i++;
	}
	for(i = 0;i < (int)list.size();i++)
	{
		Msg = m_MsgList[list[i]];
		m_MsgList.erase(m_MsgList.begin() + list[i]);
		delete Msg;

	}
	list.clear();
	SendMsg(wIdent, nX, nY, ndir, nFeature, nState, sStr, nSound);
}
void TActor::SendMsg(int wIdent, int nX,int nY, int ndir, int nFeature, int nState,std::string sStr,int nSound)
{
	TChrMsg* Msg = new TChrMsg();
	Msg->Ident = wIdent;
	Msg->x = nX;
	Msg->y = nY;
	Msg->dir = ndir;
	Msg->feature = nFeature;
	Msg->State = nState;
	Msg->saying = sStr;
	Msg->sound = nSound;
	m_MsgList.push_back(Msg);

}

bool TActor::GetMessage_(TChrMsg* ChrMsg)
{
	if(m_MsgList.size() > 0)
	{
		std::vector<TChrMsg*>::iterator it = m_MsgList.begin();
		TChrMsg* msg = *it;
		ChrMsg->dir = msg->dir;
		ChrMsg->feature = msg->feature;
		ChrMsg->Ident = msg->Ident;
		ChrMsg->saying = msg->saying;
		ChrMsg->sound = msg->sound;
		ChrMsg->State = msg->State;
		ChrMsg->x = msg->x;
		ChrMsg->y = msg->y;
		delete msg;
		m_MsgList.erase(it);
		return true;
	}
	return false;
}
void TActor::ProcMsg()
{
	TChrMsg Msg;
	while(m_nCurrentAction == 0 && GetMessage_(&Msg))
	{
		switch(Msg.Ident)
		{
		case SM_STRUCK:
			{
				m_nHiterCode = Msg.sound;
				ReadyAction(Msg);
				break;
			}
		case SM_SPACEMOVE_HIDE:
			{
				break;
			}
		case  SM_SPACEMOVE_HIDE2:
			{
				break;
			}
		case SM_SPACEMOVE_SHOW:
			{
				break;
			}
		case SM_SPACEMOVE_SHOW2:
			{
				break;
			}
		case SM_SPACEMOVE_SHOW3:
			{
				break;
			}
		default:
			{
				ReadyAction(Msg);
			}
		}
	}
}

void TActor::ReadyAction(TChrMsg Msg)
{
	bool bofly;
	TUseMagicInfo* UseMagic;
	m_nActBeforeX = m_nCurrX;
	m_nActBeforeY = m_nCurrY;
	if(Msg.Ident == SM_ALIVE)
	{
		m_boDeath = false;
		m_boSkeleton = false;
	}
	if(!m_boDeath)
	{
		switch(Msg.Ident)
		{
		case SM_TURN:
		case SM_WALK:
		case SM_BACKSTEP:
		case SM_RUSH:
		case SM_RUSHKUNG:
		case SM_RUN:
		case SM_HORSERUN:
		case SM_DIGUP:
		case SM_ALIVE:
			{
				m_nFeature = Msg.feature;
				m_nState = Msg.State;
				if(m_nState && STATE_OPENHEATH != 0) 
				{
					m_boOpenHealth = true;	
				}else
				{
					m_boOpenHealth = false;
				}

				break;
			}
		}
		int n = 0;
		if(Msg.Ident == SM_LIGHTING)
		{
			n = 0;
		}
		if(this == g_MySelf)
		{
			if (Msg.Ident == CM_WALK) 
			{
				if(!TPlayScene::GetInstance()->CanWalk(Msg.x,Msg.y))
				{
					return;
				}
			}
			if (Msg.Ident == CM_RUN) 
			{
				if(!TPlayScene::GetInstance()->CanRun(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY,Msg.x,Msg.y))
				{
					return;
				}
			}

			if (Msg.Ident == CM_HORSERUN)
			{

				if(!TPlayScene::GetInstance()->CanRun(g_MySelf->m_nCurrY,g_MySelf->m_nCurrY,Msg.x,Msg.y))
				{
					return;
				}
			}

			switch(Msg.Ident)
			{
			case CM_TURN:
			case CM_WALK:
			case CM_SITDOWN:
			case CM_RUN:
			case CM_HIT:
			case CM_HEAVYHIT:
			case CM_BIGHIT:
			case CM_POWERHIT:
			case CM_LONGHIT:
			case CM_WIDEHIT:
				{
					RealActionMsg = Msg;
					Msg.Ident = Msg.Ident - 3000;
					break;
				}
			case CM_REMOTEHIT:
				{
					RealActionMsg = Msg;
					Msg.Ident = SM_REMOTEHIT;
					break;
				}
			case CM_HORSERUN:
				{
					RealActionMsg = Msg;
					Msg.Ident = SM_HORSERUN;
					break;
				}
			case CM_THROW:
				{
					if( m_nFeature != 0)
					{
						TActor* actor;
						actor = (TActor*) Msg.feature;
						m_nTargetX = actor->m_nCurrX;
						m_nTargetY = actor->m_nCurrY;
						m_nTargetRecog = actor->m_nRecogId;

					}
					RealActionMsg = Msg;
					Msg.Ident = SM_THROW;
					break;
				}
			case CM_FIREHIT:
				{
					RealActionMsg = Msg;
					Msg.Ident = SM_FIREHIT;
					break;
				}
			case CM_34SKILLHIT:
				{
					RealActionMsg = Msg;
					Msg.Ident = SM_34SKILLHIT;
					break;
				}
			case CM_103SKILLHIT:
				{
					RealActionMsg = Msg;
					Msg.Ident = SM_103SKILLHIT;
					break;
				}
			case CM_35SKILLHIT:
				{
					RealActionMsg = Msg;
					Msg.Ident = SM_35SKILLHIT;
					break;
				}
			case CM_CRSHIT:
				{
					RealActionMsg = Msg;
					Msg.Ident = SM_CRSHIT;
					break;
				}
			case CM_TWINHIT:
				{
					RealActionMsg = Msg;
					Msg.Ident = SM_TWINHIT;
					break;
				}
			case CM_SPELL:
				{
					RealActionMsg = Msg;

					UseMagic =(TUseMagicInfo*)Msg.feature;
					RealActionMsg.dir = UseMagic->MagicSerial;
					Msg.Ident = Msg.Ident - 3000;
					break;
				}
			case CM_BUTCH:
				{
					RealActionMsg.Ident = 0;
					Msg.Ident = SM_BUTCH;
					break;
				}
			}
			m_nOldx = m_nCurrX;
			m_nOldy = m_nCurrY;
			m_nOldDir = m_btDir;

		}
		switch( Msg.Ident)
		{
		case SM_MAGICFIRE:
			{
				//nothing 20120614 由于有些飞行火攻的技能比如火球，冰咆哮，sendmsg的
				//数据中坐标并不是真正的坐标，会造成人物飞到非法的地图坐标，所以，这里
				//特殊处理这个消息，不进行其他处理，不走到下面的case的else那里
				break;
			}
		case SM_STRUCK:
			{

				m_nMagicStruckSound = Msg.x;
				n = int(200 - m_Abil.Level * 5);
				if( n > 80)
				{
					m_dwStruckFrameTime = n;
				}else
				{
					m_dwStruckFrameTime = 80;
				}
				m_dwLastStruckTime = GetTickCount();
				break;
			}
		case SM_SPELL:
			{
				m_btDir = Msg.dir;
				UseMagic = (TUseMagicInfo*)Msg.feature;
				if( UseMagic)
				{
					memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
				}
				m_CurMagic.ServerMagicCode = -1;
				m_CurMagic.targx = Msg.x;
				m_CurMagic.targy = Msg.y;
				delete UseMagic;
				break;
			}
		case SM_MONSPELL:
			{
				break;
			}
		case SM_MONSPELLEFF:
			{
				UseMagic = (TUseMagicInfo*)Msg.feature;
				switch(Msg.dir)
				{
				case 100:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 113;
							delete UseMagic;
						}
						break;
					}
				case 101:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 114;
							delete UseMagic;
						}
						break;
					}
				case 102:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 115;
							delete UseMagic;
						}
						break;
					}
				case 103:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 116;
							delete UseMagic;
						}
						break;
					}
				case 104:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 117;
							delete UseMagic;
						}
						break;
					}
				case 105:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 119;
							delete UseMagic;
						}
						break;
					}
				case 106:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 120;
							delete UseMagic;
						}
						break;
					}
				case 107:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 121;
							delete UseMagic;
						}
						break;
					}
				case 108:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 122;
							delete UseMagic;
						}
						break;
					}
				case 109:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 118;
							delete UseMagic;
						}
						break;
					}
				case 110:
				case 112:
					{
						if(UseMagic)
						{
							memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
							m_CurMagic.ServerMagicCode = 123;
							delete UseMagic;
						}
						break;
					}
				case 111:
					{
						if(UseMagic)
						{
							if((UseMagic->EffectNumber / 1000000) % 10 == 2)
							{
								m_boUseMagic = true;
								m_btMagicNum = UseMagic->EffectNumber;
							}else
							{
								memcpy(&m_CurMagic,UseMagic,sizeof(TUseMagicInfo));
								m_CurMagic.ServerMagicCode = 124;
							}
							delete UseMagic;
						}
						break;
					}

				}
				TPlayScene::GetInstance()->NewMagic(this,
					m_CurMagic.ServerMagicCode,
					m_CurMagic.EffectNumber,
					m_nCurrX,m_nCurrY,m_CurMagic.targx,m_CurMagic.targy,
					m_CurMagic.target,m_CurMagic.EffectType,m_CurMagic.Recusion,
					m_CurMagic.anitime,bofly);
				m_CurMagic.ServerMagicCode = 0;
			}
		default:
			{
				// 为了防止某些动作数据中含有不是坐标的数据走到这里，
				//特意增加简单的判断，如果是错误的坐标，不更新坐标位置
				if (Msg.x >=0 && Msg.x < VDMap::GetInstance()->Header.Width
					&& Msg.y >= 0 && Msg.y < VDMap::GetInstance()->Header.Height)
				{
					m_nCurrX = Msg.x;
					m_nCurrY = Msg.y;
					if(Msg.dir >= DR_UP || Msg.dir <= DR_UPLEFT)
					{
						m_btDir = Msg.dir;
					}

				}


			}
		
			break;
		}
		m_nCurrentAction = Msg.Ident;
		CalcActorFrame();
	}else
	{
		if( Msg.Ident == SM_SKELETON )
		{
			m_nCurrentAction = Msg.Ident;
			CalcActorFrame();
			m_boSkeleton = true;
		}

	}
	if (Msg.Ident == SM_DEATH || Msg.Ident == SM_NOWDEATH)
	{
		m_boDeath = true;
		TPlayScene::GetInstance()->ActorDied(this);
		if(this == g_MySelf)
		{
			g_MySelfDeathTime = GetTickCount();
			FrmMain::GetInstance()->ShowReAliveDlg();
		}
	}

	RunSound();
}

void TActor::Run()
{
	if (m_nCurrentAction == SM_WALK ||
		m_nCurrentAction == SM_BACKSTEP ||
		m_nCurrentAction == SM_RUN ||
		m_nCurrentAction == SM_HORSERUN ||
		m_nCurrentAction == SM_RUSH ||
		m_nCurrentAction == SM_RUSHKUNG)
	{
		return;
	}
	m_boMsgMuch = false;
	if(this != g_MySelf)
	{
		if(m_MsgList.size() >= 2)
		{
			m_boMsgMuch = true;
		}
	}

	unsigned long dwFrameTimetime;
	RunActSound(m_nCurrentFrame - m_nStartFrame);
	RunFrameAction(m_nCurrentFrame - m_nStartFrame);
	int prv = m_nCurrentFrame;
	if(m_nCurrentAction != 0)
	{
		if(m_nCurrentFrame < m_nStartFrame || m_nCurrentFrame > m_nEndFrame)
		{
			m_nCurrentFrame = m_nStartFrame;
		}
		if (this != g_MySelf && m_boUseMagic)
		{
			dwFrameTimetime = int(m_dwFrameTime / 1.8);
		}else
		{
			if(m_boMsgMuch)
			{
				dwFrameTimetime = int(m_dwFrameTime * 2 / 3);
			}else
			{
				dwFrameTimetime = m_dwFrameTime;

			}
		}

		if(GetTickCount() - m_dwStartTime > dwFrameTimetime)
		{
			if(m_nCurrentFrame < m_nEndFrame )
			{
				if(m_boUseMagic)
				{
					if(m_nCurEffFrame == m_nSpellFrame - 2 || MagicTimeOut())
					{
						if(m_CurMagic.ServerMagicCode >= 0 || MagicTimeOut())
						{
							m_nCurrentFrame++;
							m_nCurEffFrame++;
							m_dwStartTime = GetTickCount();
						}
					}else
					{
						if(m_nCurrentFrame < m_nEndFrame - 1)
						{
							m_nCurrentFrame++;
						}
						m_nCurEffFrame++;
						m_dwStartTime = GetTickCount();
					}
				}else
				{
					m_nCurrentFrame++;
					m_dwStartTime = GetTickCount();
				}
			}else
			{
				if(m_boDelActionAfterFinished)
				{
					m_boDelActor = true;
				}
				if(this == g_MySelf)
				{
					if(FrmMain::GetInstance()->ServerAcceptNextAction())
					{
						ActionEnded();
						m_nCurrentAction = 0;
						m_boUseMagic = false;
					}
				}else
				{
					ActionEnded();
					m_nCurrentAction = 0;
					m_boUseMagic = false;
				}
			}


			if(m_boUseMagic)
			{
				if(m_nCurEffFrame == m_nSpellFrame - 1)
				{
					if(m_CurMagic.ServerMagicCode > 0)
					{
						bool bofly;
						TPlayScene::GetInstance()->NewMagic(this,
							m_CurMagic.ServerMagicCode,m_CurMagic.EffectNumber,m_nCurrX,m_nCurrY,
							m_CurMagic.targx,m_CurMagic.targy,m_CurMagic.target,m_CurMagic.EffectType,
							m_CurMagic.Recusion,m_CurMagic.anitime,bofly);
						if(bofly)
						{
							PlaySound_(m_nMagicFireSound);
						}else
						{
							PlaySound_(m_nMagicExplosionSound);
						}
					}
				}
				m_CurMagic.ServerMagicCode = 0;
			}
		}
		if(m_wAppearance == 0 || m_wAppearance == 1 || m_wAppearance == 43)
		{
			m_nCurrentDefFrame = -10;
		}else
		{
			m_nCurrentDefFrame = 0;
		}
		m_dwDefFrameTime = GetTickCount();
	}else
	{
		if(GetTickCount() - m_dwSmoothMoveTime > 200)
		{
			if(GetTickCount() - m_dwDefFrameTime > 500)
			{
				m_dwDefFrameTime = GetTickCount();
				m_nCurrentDefFrame ++;
				if(m_nCurrentDefFrame >= m_nDefFrameCount)
				{
					m_nCurrentDefFrame = 0;
				}
			}
			DefaultMotion();
		}
	}
	if(prv != m_nCurrentFrame)
	{
		m_dwLoadSurfaceTime = GetTickCount();
		LoadSurface();
	}
}


void TActor::DrawEff(int dx,int dy)
{

}
void TActor::FeatureChanged()
{
	int haircount = 0;
	unsigned char nbHair = 0;
	switch(m_btRace)
	{
	case 0:
		{
			nbHair = HAIRfeature(m_nFeature);
			m_btHair = nbHair >> 7;
			m_bWings = nbHair & 0x7F;
			m_btDress = DRESSfeature(m_nFeature);
			m_btWeapon = WEAPONfeature(m_nFeature);

			m_btHorse = Horsefeature(m_nFeatureEx);
			m_btEffect = Effectfeature(m_nFeatureEx);
			m_btDressColor = Colorfeature(m_nFeatureEx);
			m_nBodyOffset = HUMANFRAME * (m_btDress / 2);
			///////20120401 头发数据用作他用/////////////
			if(m_btHair > 0)
			{
				m_bMeditation = true;
				g_TargetCret = nullptr; 
			}else
			{
				m_bMeditation = false;
			}
			haircount = -1;
			switch(m_btDress % 2)
			{
			case 0:
				{
					haircount = m_btHair * 2;
					break;
				}
			case 1:
				{
					haircount = m_btHair + 1;
					break;
				}
			}
			if(haircount > 0)
			{
				m_nHairOffset = HUMANFRAME * (haircount + m_btSex);
			}else
			{
				m_nHairOffset = -1;
			}
			m_nWeaponOffset = HUMANFRAME * m_btWeapon;
			if(m_btEffect != 0)
			{
				if(m_btEffect == 50)
				{
					m_nHumWinOffset = 352;
				}else
				{
					m_nHumWinOffset = (m_btEffect - 1) * HUMANFRAME;
				}
			}
			break;
		}
	case 50:
		{
			m_btWeapon = WEAPONfeature(m_nFeature);
			m_wAppearance = APPRfeature(m_nFeature);
			m_btEffect = Effectfeature(m_nFeatureEx);
			if( m_wAppearance > 10000)
			{
				m_btHair = (m_wAppearance - 10000);
				m_wAppearance = 10000;
			}

			break;
		}
	default:
		{
			m_wAppearance = APPRfeature(m_nFeature);
			m_nBodyOffset = GetOffset(m_wAppearance);
		}

	}
}
bool TActor::MagicTimeOut()
{
	bool Result = false;
	if(this == g_MySelf)
	{
		if( GetTickCount() - m_dwWaitMagicRequest > m_dwWaitMagicmode1)
		{
			Result = true;
		}
	
	}else
	{
		 if( GetTickCount() - m_dwWaitMagicRequest > m_dwWaitMagicmode2)
		 {
			 Result = true;
		 }
	}
	if(Result)
	{
		m_CurMagic.ServerMagicCode = 0;
	}
	return Result;
}
void TActor::ProcHurryMsg()
{
	int n = 0;
	TChrMsg* Msg;
	while(true) 
	{
		if(n >= (int)m_MsgList.size()) break;
		Msg = m_MsgList[n];
		bool fin = false;
		switch(Msg->Ident)
		{
		case SM_MAGICFIRE:
			{
				m_CurMagic.ServerMagicCode = 111;
				m_CurMagic.target = Msg->x;
				if(Msg->y >= 0 && Msg->y <  MAXMAGICTYPE)
				{
					m_CurMagic.EffectType = TMagicType(Msg->y);
				}
				m_CurMagic.EffectNumber = Msg->dir; 
				m_CurMagic.targx = Msg->feature;
				m_CurMagic.targy = Msg->State;
				m_CurMagic.Recusion = true;
				fin = true;

				break;
			}
		case SM_MAGICFIRE_FAIL:
			{
				if(m_CurMagic.ServerMagicCode != 0)
				{
					m_CurMagic.ServerMagicCode = 0;
					fin = true;
				}
				break;
			}
		}

		if(fin)
		{
			std::vector<TChrMsg*>::iterator it;
			for(it = m_MsgList.begin();it != m_MsgList.end();it++)
			{
				if((TChrMsg*)*it == Msg)
				{
					m_MsgList.erase(it);
					break;
				}
			}
			delete Msg;

		}else
		{
			n ++;
		}
	}


}

bool TActor::IsIdle()
{
	if(m_nCurrentAction == 0 && m_MsgList.size() == 0)
	{
		return true;
	}
	return false;
}

bool TActor::Move(int step)
{
	bool result = false;
	bool fastmove = false;
	bool normmove = false;
	int curstep = 0;
	int maxstep = 0;
	if(m_nCurrentAction == SM_RUSH || m_nCurrentAction == SM_RUSHKUNG)
	{
		normmove = true;
	}

	if(g_MySelf && this == g_MySelf && !fastmove && !normmove)
	{
		g_nMoveSlowLevel = 0;
		g_boMoveSlow = false;
		if(m_Abil.Weight > m_Abil.MaxWeight)
		{
			g_nMoveSlowLevel = m_Abil.Weight / m_Abil.MaxWeight;
			g_boMoveSlow = true;
		}
		if(m_Abil.WearWeight > m_Abil.MaxWearWeight)
		{
			g_nMoveSlowLevel= g_nMoveSlowLevel + m_Abil.WearWeight / m_Abil.MaxWearWeight;
			g_boMoveSlow = true;
		}
		if(m_Abil.HandWeight > m_Abil.MaxHandWeight)
		{
			g_boAttackSlow = true;
		}else 
		{
			g_boAttackSlow = false;
		}
		if(g_boMoveSlow && (m_nSkipTick < g_nMoveSlowLevel))
		{
			m_nSkipTick++;
			return false;
		}else
		{
			m_nSkipTick = 0;
		}
		//if(m_boIceMoveSlow && m_nIceSkipTick < m_nIceMoveSlowLevel)
		//{
		//	m_nIceSkipTick++;
		//	return;
		//}else 
		//{
		//	m_nIceSkipTick = 0;
		//}
		if (m_nCurrentAction == SM_WALK ||
			m_nCurrentAction == SM_BACKSTEP ||
			m_nCurrentAction == SM_RUN ||
			m_nCurrentAction == SM_HORSERUN ||
			m_nCurrentAction == SM_RUSH ||
			m_nCurrentAction == SM_RUSHKUNG)
		{
			switch(m_nCurrentFrame - m_nStartFrame)
			{
			case 1:
				{
					PlaySound_(m_nFootStepSound);
					break;
				}
			case 4:
				{
					PlaySound_(m_nFootStepSound + 1);
					break;
				}
			}
		}
	}
	m_boMsgMuch = false;
	if(this != g_MySelf) 
	{
		if(m_MsgList.size() >= 2)
		{
			m_boMsgMuch = true;
		}
	}

	int prv = m_nCurrentFrame;
	if (m_nCurrentAction == SM_WALK ||
		m_nCurrentAction == SM_RUN ||
		m_nCurrentAction == SM_HORSERUN ||
		m_nCurrentAction == SM_RUSH ||
		m_nCurrentAction == SM_RUSHKUNG)
	{
		if (m_nCurrentFrame < m_nStartFrame || m_nCurrentFrame > m_nEndFrame) 
		{
			m_nCurrentFrame = m_nStartFrame - 1;
		}
		if(m_nCurrentFrame < m_nEndFrame)  
		{
			m_nCurrentFrame++;
			if( m_boMsgMuch &&  !normmove )  //加快步伐
			{
				if( m_nCurrentFrame < m_nEndFrame)
				{
					m_nCurrentFrame++;
				}
			}
			int curstep = m_nCurrentFrame - m_nStartFrame + 1;
			int maxstep = m_nEndFrame - m_nStartFrame + 1;
			Shift(m_btDir, m_nMoveStep, curstep, maxstep);
		}

		if( m_nCurrentFrame >= m_nEndFrame)
		{
			if(this == g_MySelf)
			{
				if( FrmMain::GetInstance()->ServerAcceptNextAction())
				{
					m_nCurrentAction = 0;
					m_boLockEndFrame = true;
					m_dwSmoothMoveTime = GetTickCount();
				}
			}else
			{
				m_nCurrentAction = 0;
				m_boLockEndFrame = true;
				m_dwSmoothMoveTime = GetTickCount();
			}
			result = true;
		}

		if(m_nCurrentAction == SM_RUSH) 
		{
			if(this == g_MySelf)
			{
				g_dwDizzyDelayStart = GetTickCount();
				g_dwDizzyDelayTime = 300;
			}
		}
		if( m_nCurrentAction == SM_RUSHKUNG)
		{
			if( m_nCurrentFrame >= m_nEndFrame - 3)
			{
				m_nCurrX = m_nActBeforeX;
				m_nCurrY = m_nActBeforeY;
				m_nRx = m_nCurrX;
				m_nRy = m_nCurrY;
				m_nCurrentAction = 0;
				m_boLockEndFrame = true;
			}
		}
		result = true;
	}

	if (m_nCurrentAction == SM_BACKSTEP) 
	{
		if (m_nCurrentFrame > m_nEndFrame || m_nCurrentFrame < m_nStartFrame) 
		{
			m_nCurrentFrame = m_nEndFrame + 1;
		}
		if( m_nCurrentFrame > m_nStartFrame)
		{
			m_nCurrentFrame--;
			if( m_boMsgMuch || fastmove)
			{
				if(m_nCurrentFrame > m_nStartFrame)
				{
					m_nCurrentFrame --;
				}
			}
			curstep = m_nEndFrame - m_nCurrentFrame + 1;
			maxstep = m_nEndFrame - m_nStartFrame + 1;
			Shift(GetBack(m_btDir), m_nMoveStep, curstep, maxstep);
		}

		if( m_nCurrentFrame <= m_nStartFrame)
		{
			if(this == g_MySelf)
			{
				m_nCurrentAction = 0;
				m_boLockEndFrame = true;
				m_dwSmoothMoveTime = GetTickCount();

				g_dwDizzyDelayStart = GetTickCount();
				g_dwDizzyDelayTime = 1000;
			}else
			{
				m_nCurrentAction = 0;
				m_boLockEndFrame = true;
				m_dwSmoothMoveTime = GetTickCount();
			}

		}
		result = true;
	}
	if( prv != m_nCurrentFrame )
	{
		m_dwLoadSurfaceTime = GetTickCount();
		LoadSurface();
	}

	return result;
}

void TActor::Shift(int dir,int step,int ncur,int Max)
{
	int unx, uny, ss, v;

	unx = UNITX * step;
	uny = UNITY * step;
	int cur = ncur;
	if( cur > Max) cur = Max; //NM

	m_nRx = m_nCurrX;
	m_nRy = m_nCurrY;
	ss = int((Max - cur - 1) / Max) * step;
	switch(dir)
	{
	case DR_UP:
		{
			ss = int((Max - cur) / Max) * step;
			m_nShiftX = 0;
			m_nRy = m_nCurrY + ss;
			if( ss == step)
			{
				m_nShiftY = -int(uny / Max * cur);
			}else
			{
				m_nShiftY = int(uny / Max * (Max - cur));
			}
			break;
		}
	case DR_UPRIGHT:
		{
			if(Max >= 6)
			{
				v = 2;
			}else v = 0;
			ss = int((Max - cur + v) / Max) * step;
			m_nRx = m_nCurrX - ss;
			m_nRy = m_nCurrY + ss;
			if(ss == step)
			{
				m_nShiftX = int(unx / Max * cur);
				m_nShiftY = -int(uny / Max * cur);
			}else
			{
				m_nShiftX = -int(unx / Max * (Max - cur));
				m_nShiftY = int(uny / Max * (Max - cur));
			}
			break;
		}
	case DR_RIGHT:
		{
			ss = int((Max - cur) / Max) * step;
			m_nRx = m_nCurrX - ss;
			if(ss == step)
			{
				m_nShiftX = int(unx / Max * cur);
			}else
			{
				m_nShiftX = -int(unx / Max * (Max - cur));
			}
			m_nShiftY = 0;
			break;
		}
	case DR_DOWNRIGHT:
		{
			if(Max >= 6)
			{
				v = 2;
			}else v = 0;
			ss = int((Max - cur - v) / Max) * step;
			m_nRx = m_nCurrX - ss;
			m_nRy = m_nCurrY - ss;
			if(ss == step)
			{
				m_nShiftX = int(unx / Max * cur);
				m_nShiftY = int(uny / Max * cur);
			}else
			{
				m_nShiftX = -int(unx / Max * (Max - cur));
				m_nShiftY = -int(uny / Max * (Max - cur));
			}
			break;
		}
	case DR_DOWN:
		{
			if(Max >= 6)
			{
				v = 1;
			}else v = 0;
			ss = int((Max - cur - v) / Max) * step;
			m_nShiftX = 0;
			m_nRy = m_nCurrY - ss;
			if(ss == step)
			{
				m_nShiftY = int(uny / Max * cur);
			}else
			{
				m_nShiftY = -int(uny / Max * (Max - cur));
			}
			break;
		}
	case DR_DOWNLEFT:
		{
			if(Max >= 6)
			{
				v = 2;
			}else v = 0;
			ss = int((Max - cur - v) / Max) * step;
			m_nRx = m_nCurrX + ss;
			m_nRy = m_nCurrY - ss;
			if(ss == step)
			{
				m_nShiftX = -int(unx / Max * cur);
				m_nShiftY = int(uny / Max * cur);
			}else
			{
				m_nShiftX = int(unx / Max * (Max - cur));
				m_nShiftY = -int(uny / Max * (Max - cur));
			}
			break;
		}
	case DR_LEFT:
		{
			ss = int((Max - cur) / Max) * step;
			m_nRx = m_nCurrX + ss;
			if(ss == step)
			{
				m_nShiftX = -int(unx / Max * cur);
			}else
			{
				m_nShiftX = int(unx / Max * (Max - cur));
			}
			m_nShiftY = 0;
			break;
		}
	case DR_UPLEFT:
		{
			if(Max >= 6)
			{
				v = 2;
			}else v = 0;
			ss = int((Max - cur + v) / Max) * step;
			m_nRx = m_nCurrX + ss;
			m_nRy = m_nCurrY + ss;
			if(ss == step)
			{
				m_nShiftX = -int(unx / Max * cur);
				m_nShiftY = -int(uny / Max * cur);
			}else
			{
				m_nShiftX = int(unx / Max * (Max - cur));
				m_nShiftY = int(uny / Max * (Max - cur));
			}
		}
	}
}


void TActor::LoadSurface()
{
	if(!m_boReverseFrame)
	{
		m_BodySurface = GetMonImage(m_wAppearance, m_nCurrentFrame, m_nPx, m_nPy);
	}else
	{
		m_BodySurface = GetMonImage(m_wAppearance, GetOffset(m_wAppearance) + m_nEndFrame - (m_nCurrentFrame - m_nStartFrame),
			m_nPx, m_nPy);
	}
	if (!m_BodySurface && !m_boDeath && m_btRace != 50)
	{
		m_nCurrentAction = 0;
		m_nCurrentFrame = m_btDir * 10;
		m_boUseMagic = false;
		m_boUseEffect = false;
		m_BodySurface = GetMonImage(m_wAppearance, m_nCurrentFrame, m_nPx, m_nPy);
	}

}

int TActor::CanRun()
{
	return 1;
	//待定
	/*if(m_Abil.HP < RUN_MINHEALTH)
	{
	return -1;
	}
	return 1;*/
}
int TActor::CanWalk()
{
	if(GetTickCount() - g_dwLatestSpellTick < g_dwMagicPKDelayTime)
	{
		return -1;
	}
	return 1;
}

bool TActor::CheckSelect(int dx1,int dy1)
{
	if(m_BodySurface && m_BodySurface->Image_)
	{
		unsigned long c = m_BodySurface->getPixels(dx1,dy1);
		if(c != 0 && (m_BodySurface->getPixels(dx1 - 1,dy1) != 0) && m_BodySurface->getPixels(dx1 + 1,dy1)
			&& m_BodySurface->getPixels(dx1,dy1 - 1) && m_BodySurface->getPixels(dx1,dy1 + 1))
		{
			return true;
		}
	}
	return false;
}
int TActor::CharWidth()
{
	if(m_BodySurface && m_BodySurface->Image_)
	{
		return m_BodySurface->pWidth;
	}
	return 48;

}
void TActor::MoveFail()
{
	m_nCurrentAction = 0;
	m_boLockEndFrame = true;
	g_MySelf->m_nCurrX = m_nOldx;
	g_MySelf->m_nCurrY = m_nOldy;
	g_MySelf->m_btDir = m_nOldDir;
	CleanUserMsgs();
}

void TActor::ProcName(const char* sstr)
{
	std::string wstr = sstr;
	m_sDescUserName = GetValidStr3Ex(wstr, m_sUserName, '\\',true);
	m_sDescUserName = GetValidStr3Ex(m_sDescUserName, m_sRankName, '\\',true);
	m_sDescUserName = GetValidStr3Ex(m_sDescUserName, m_sGuildName, '\\',true);
	m_sGuildRankName = GetValidStr3Ex(m_sGuildName, m_sGuildName, ':',true);

	m_sDescUserName = GetValidStr3Ex(m_sDescUserName, m_sDearName, '\\',true);
	m_sDescUserName = GetValidStr3Ex(m_sDescUserName, m_sMasterName, '\\',true);
	std::string tmp;
	//封号图片编号
	m_sDescUserName = GetValidStr3Ex(m_sDescUserName, tmp, '\\');
	if (tmp.length() > 0 && IsStringNumber(tmp.c_str()))
	{
		m_NameImg[0] = atoi(tmp.c_str());
	}


	m_sDescUserName = GetValidStr3Ex(m_sDescUserName, tmp, '\\');  
	if (tmp.length() > 0 && IsStringNumber(tmp.c_str()))
	{
		m_NameImg[1] = atoi(tmp.c_str());
	}

	m_sDescUserName = GetValidStr3Ex(m_sDescUserName, tmp, '\\');  
	if (tmp.length() > 0 && IsStringNumber(tmp.c_str()))
	{
		m_NameImg[2] = atoi(tmp.c_str());
	}

}

void TActor::DrawAddBlood(int dx,int dy,cocos2d::Layer* layer)
{
	const int IncBloodNumImgIndex = 313; //加血图片索引
	const int DecBloodNumImgIndex = 325; //减血图片索引
	const int MissImgIndex = 312;  //躲避图片索引
	if(IsAddBlood)
	{
		if(GetTickCount() - AddBloodTime > 2000)
		{
			IsAddBlood =  false;
			if(GetTickCount() - AddBloodStartTime > 100)
			{
				AddBloodFram ++;
				AddBloodStartTime = GetTickCount();
			}
		}
	}
	 //加减血显示
	int BooldNum;
	char sNum[1024]={0};
	int numstart,chrWidth,sumWidth,ny;
	if(IsAddBlood)
	{
		BooldNum = abs(AddBloodNum);
		sprintf(sNum,"%d",BooldNum);
		TVDImage* img = GetUIImage(IncBloodNumImgIndex);
		if(!img)return;
		chrWidth = img->pWidth;
		sumWidth = (strlen(sNum) + 1) * img->pWidth;
		ny = dy + m_nHpy + m_nShiftY - AddBloodFram * (2) - 60;
		//画+-号
		if(AddBloodNum > 0 && AddBloodNum != 999999999)
		{
			img = GetUIImage(IncBloodNumImgIndex + 1);
			if(img && img->Image_)
			{
				layer->addChild(img->GetImage( m_nSayX - sumWidth / 2,ny));
			}
			numstart = IncBloodNumImgIndex + 2;
		}else if(AddBloodNum < 0)
		{
			img = GetUIImage(DecBloodNumImgIndex);
			if(img && img->Image_)
			{
				layer->addChild(img->GetImage(m_nSayX - sumWidth / 2,ny));
			}
			numstart = DecBloodNumImgIndex + 2;
		}else
		{
			img = GetUIImage(MissImgIndex);
			if(img && img->Image_)
			{
				layer->addChild(img->GetImage(m_nSayX - img->pWidth / 2,ny));
			}
			return;
		}
		//数字
		int nx =  m_nSayX - sumWidth / 2 + chrWidth;
		int n;
		for(int i = 0;i < (int)strlen(sNum);i++)
		{
			char c_s = sNum[i];
			n = numstart + atoi(&c_s);
			img = GetUIImage(n);
			if(img && img->Image_)
			{
				layer->addChild(img->GetImage(nx,ny));
			}
			nx += chrWidth;
		}
	}
}

bool TActor::CanCancelAction()
{
	if(m_nCurrentAction == SM_HIT)
	{
		if(!m_boUseEffect)
		{
			return true;
		}
	}
	return false;
}
void TActor::CancelAction()
{
	m_nCurrentAction = 0;
	m_boLockEndFrame = true;
}
bool TActor::ActionFinished()
{
	if(m_nCurrentAction == 0 || m_nCurrentFrame >= m_nEndFrame)
	{
		return true;
	}
	return false;
}
void TActor::CleanCharMapSetting(int x,int y)
{
	g_MySelf->m_nCurrX = x;
	g_MySelf->m_nCurrY = y;
	g_MySelf->m_nRx = x;
	g_MySelf->m_nRy = y;
	m_nOldx = x;
	m_nOldy = y;
	m_nCurrentAction = 0;
	m_nCurrentFrame = -1;
	CleanUserMsgs();
}
void TActor::CleanUserMsgs()
{
	std::vector<TChrMsg*>::iterator it;
	std::vector<int> list;
	TChrMsg* m;
	list.clear();
	int i = 0;
	for(it = m_MsgList.begin();it != m_MsgList.end();it++)
	{
		m = *it;
		if(m->Ident >= 3000 && m->Ident <= 3099)
		{
			list.push_back(i);
		}
		i++;
	}
	
	for(i = 0;i < (int)list.size();i++)
	{
		m = m_MsgList[list[i]];;
		delete m;
		m_MsgList.erase(m_MsgList.begin() + i);
	}

	list.clear();
}
void TActor::CalcActorFrame()
{
	int haircount = 0;
	m_boUseMagic = false;
	m_nCurrentFrame = -1;
	m_nBodyOffset = GetOffset(m_wAppearance);
	m_Action = GetRaceByPM(m_btRace, m_wAppearance);
	if(! m_Action)
	{
		return;
	}
	switch(m_nCurrentAction)
	{
	case SM_TURN:
		{
			m_nStartFrame = m_Action->ActStand.start + m_btDir * (m_Action->ActStand.frame + m_Action->ActStand.skip);
			m_nEndFrame = m_nStartFrame + m_Action->ActStand.frame - 1;
			m_dwFrameTime = m_Action->ActStand.ftime;
			m_dwStartTime = GetTickCount();
			m_nDefFrameCount = m_Action->ActStand.frame;
			Shift(m_btDir, 0, 0, 1);
			break;
		}
	case SM_WALK:
	case SM_RUSH:
	case SM_RUSHKUNG:
	case SM_BACKSTEP:
		{
			m_nStartFrame = m_Action->ActWalk.start + m_btDir * (m_Action->ActWalk.frame + m_Action->ActWalk.skip);
			m_nEndFrame = m_nStartFrame + m_Action->ActWalk.frame - 1;
			m_dwFrameTime = m_Action->ActWalk.ftime;
			m_dwStartTime = GetTickCount();
			m_nMaxTick = m_Action->ActWalk.usetick;
			m_nCurTick = 0;
			m_nMoveStep = 1;
			if( m_nCurrentAction == SM_BACKSTEP)
			{
				Shift(GetBack(m_btDir), 2, 0, m_nEndFrame - m_nStartFrame + 1);
			}else
			{
				Shift(m_btDir, m_nMoveStep, 0, m_nEndFrame - m_nStartFrame + 1);
			}
			break;
		}
	case SM_HIT:
	case SM_REMOTEHIT:
		{
			m_nStartFrame = m_Action->ActAttack.start + m_btDir * (m_Action->ActAttack.frame + m_Action->ActAttack.skip);
			m_nEndFrame = m_nStartFrame + m_Action->ActAttack.frame - 1;
			m_dwFrameTime = m_Action->ActAttack.ftime;
			m_dwStartTime = GetTickCount();
			m_dwWarModeTime = GetTickCount();
			Shift(m_btDir, 0, 0, 1);
			break;
		}
	case SM_STRUCK:
		{
			m_nStartFrame = m_Action->ActStruck.start + m_btDir * (m_Action->ActStruck.frame + m_Action->ActStruck.skip);
			m_nEndFrame = m_nStartFrame + m_Action->ActStruck.frame - 1;
			m_dwFrameTime = m_dwStruckFrameTime;
			m_dwStartTime = GetTickCount();
			Shift(m_btDir, 0, 0, 1);
			break;
		}
	case SM_DEATH:
		{
			m_nStartFrame = m_Action->ActDie.start + m_btDir * (m_Action->ActDie.frame + m_Action->ActDie.skip);
			m_nEndFrame = m_nStartFrame + m_Action->ActDie.frame - 1;
			m_nStartFrame = m_nEndFrame;
			m_dwFrameTime = m_Action->ActDie.ftime;
			m_dwStartTime = GetTickCount();
			break;
		}
	case SM_NOWDEATH:
		{
			m_nStartFrame = m_Action->ActDie.start + m_btDir * (m_Action->ActDie.frame + m_Action->ActDie.skip);
			m_nEndFrame = m_nStartFrame + m_Action->ActDie.frame - 1;
			m_dwFrameTime = m_Action->ActDie.ftime;
			m_dwStartTime = GetTickCount();
			break;
		}
	case SM_SKELETON:
		{
			m_nStartFrame = m_Action->ActDeath.start + m_btDir;
			m_nEndFrame = m_nStartFrame + m_Action->ActDeath.frame - 1;
			m_dwFrameTime = m_Action->ActDeath.ftime;
			m_dwStartTime = GetTickCount();
			break;
		}
	case SM_MONSPELL:
		{
			switch(m_btSpellAct)
			{
			case 0:
				{
					m_nStartFrame = m_Action->ActStand.start + m_btDir * (m_Action->ActStand.frame + m_Action->ActStand.skip);
					m_nEndFrame = m_nStartFrame + m_Action->ActStand.frame - 1;
					m_dwFrameTime = m_Action->ActStand.ftime;
					break;
				}
			case 1:
				{
					m_nStartFrame = m_Action->ActAttack.start + m_btDir * (m_Action->ActAttack.frame + m_Action->ActAttack.skip);
					m_nEndFrame = m_nStartFrame + m_Action->ActAttack.frame - 1;
					m_dwFrameTime = m_Action->ActAttack.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 2:
				{
					m_nStartFrame = m_Action->ActAttack1.start + m_btDir * (m_Action->ActAttack1.frame + m_Action->ActAttack1.skip);
					m_nEndFrame = m_nStartFrame + m_Action->ActAttack1.frame - 1;
					m_dwFrameTime = m_Action->ActAttack1.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 3:
				{
					m_nStartFrame = m_Action->ActAttack2.start + m_btDir * (m_Action->ActAttack2.frame + m_Action->ActAttack2.skip);
					m_nEndFrame = m_nStartFrame + m_Action->ActAttack2.frame - 1;
					m_dwFrameTime = m_Action->ActAttack2.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 4:
				{
					m_nStartFrame = m_Action->ActAttack3.start + m_btDir * (m_Action->ActAttack3.frame + m_Action->ActAttack3.skip);
					m_nEndFrame = m_nStartFrame + m_Action->ActAttack3.frame - 1;
					m_dwFrameTime = m_Action->ActAttack3.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 5:
				{
					m_nStartFrame = m_Action->ActAttack4.start + m_btDir * (m_Action->ActAttack4.frame + m_Action->ActAttack4.skip);
					m_nEndFrame = m_nStartFrame + m_Action->ActAttack4.frame - 1;
					m_dwFrameTime = m_Action->ActAttack4.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 6:
				{
					m_nStartFrame = m_Action->ActAttack5.start + m_btDir * (m_Action->ActAttack5.frame + m_Action->ActAttack5.skip);
					m_nEndFrame = m_nStartFrame + m_Action->ActAttack5.frame - 1;
					m_dwFrameTime = m_Action->ActAttack5.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 7:
				{
					m_nStartFrame = m_Action->ActAttack6.start + m_btDir * (m_Action->ActAttack6.frame + m_Action->ActAttack6.skip);
					m_nEndFrame = m_nStartFrame + m_Action->ActAttack6.frame - 1;
					m_dwFrameTime = m_Action->ActAttack6.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			}
			m_dwStartTime = GetTickCount();
			Shift(m_btDir, 0, 0, 1);
			break;
		}

	}
}
int TActor::GetDefaultFrame(bool wmode)
{
	int Result = 0;
	int cf = 0;

	TMonsterAction* pm;
	pm = GetRaceByPM(m_btRace, m_wAppearance);
	if(!pm)return Result;
	if(m_boDeath)
	{
		if(m_boSkeleton)
		{
			Result = pm->ActDeath.start;
		}else
		{
			Result = pm->ActDie.start + m_btDir * (pm->ActDie.frame + pm->ActDie.skip)
				+ (pm->ActDie.frame - 1);
		}
	}else
	{
		m_nDefFrameCount = pm->ActStand.frame;
		if( m_nCurrentDefFrame < 0)
		{
			cf = 0;
		}else if(m_nCurrentDefFrame >= pm->ActStand.frame)
		{
		}else
		{
			cf = m_nCurrentDefFrame;
		}
	}
	Result = pm->ActStand.start + m_btDir * (pm->ActStand.frame + pm->ActStand.skip) + cf;
	return Result;

}
void TActor::DefaultMotion()
{

	m_boReverseFrame = false;
	//蹲下模式清理
	if(m_boSitDownMode)
	{
		if(GetTickCount() - m_dwSitDownModeTime > 2 * 1000 )
		{
			m_boSitDownMode = false;
		}
	}

	//攻击等待模式清理
	if(m_boWarMode) 
	{
		if (GetTickCount() - m_dwWarModeTime > 2 * 1000)
		{
			m_boWarMode = false;
		}
	}

	m_nCurrentFrame = GetDefaultFrame(m_boWarMode);
	Shift(m_btDir, 0, 1, 1);
}
void TActor::ActionEnded()
{
	if(m_nCurrentAction == SM_DIGDOWN && m_btRace == 33) 
	{
		std::vector<TActor*>::iterator it;
		for(it = TPlayScene::GetInstance()->m_ActorList.begin();
			it != TPlayScene::GetInstance()->m_ActorList.end();it++)
		{
			if(*it == this)
			{
				TPlayScene::GetInstance()->m_ActorList.erase(it);
				break;
			}
		}

	}


}
void TActor::RunFrameAction(int frame)
{

}
void TActor::RunActSound(int frame)
{
	if(m_boRunSound)
	{
		if(m_btRace == 0)
		{
			switch(m_nCurrentAction)
			{
			case SM_THROW:
			case SM_HIT:
			case SM_HIT + 1:
			case SM_HIT + 2:
			case SM_REMOTEHIT:
			case SM_MONSPELL:
				{
					if(frame == 2)
					{
						PlaySound_(m_nWeaponSound);
						m_boRunSound = false;
					}
					break;
				}
			case SM_POWERHIT:
				{
					if(frame == 2)
					{
						PlaySound_(m_nWeaponSound);
						if(m_btSex == 0)
						{
							PlaySound_(s_yedo_man);
						}else
						{
							PlaySound_(s_yedo_woman);
						}
						m_boRunSound = false;
					}
					break;
				}
			case SM_LONGHIT:
				{
					if(frame == 2)
					{
						PlaySound_(m_nWeaponSound);
						PlaySound_(s_longhit);
						m_boRunSound = false;
					}
					break;
				}
			case SM_WIDEHIT:
				{
					if(frame == 2)
					{
						PlaySound_(m_nWeaponSound);
						PlaySound_(s_widehit);
						m_boRunSound = false;
					}
					break;
				}
			case SM_FIREHIT:
				{
					if(frame == 2)
					{
						PlaySound_(m_nWeaponSound);
						PlaySound_(s_firehit);
						m_boRunSound = false;
					}
					break;
				}
			case SM_34SKILLHIT:
				{
					if(frame == 2)
					{
						PlaySound_(m_nWeaponSound);
						PlaySound_(s_34hit);
						m_boRunSound = false;
					}
					break;
				}
			case SM_35SKILLHIT:
				{
					if(frame == 2)
					{
						PlaySound_(m_nWeaponSound);
						PlaySound_(s_35hit);
						m_boRunSound = false;
					}
					break;
				}
			case SM_103SKILLHIT:
				{
					if(frame == 2)
					{
						PlaySound_(m_nWeaponSound);
						PlaySound_(s_103hit);
						m_boRunSound = false;
					}
					break;
				}
			case SM_CRSHIT:
			case SM_TWINHIT:
				{
					if(frame == 2)
					{
						PlaySound_(m_nWeaponSound);
						PlaySound_(s_firehit);
						m_boRunSound = false;
					}
					break;
				}
			}
		}else
		{
			if(m_btRace != 50)
			{
				if(m_nCurrentAction == SM_WALK ||
					m_nCurrentAction == SM_TURN)
				{
					if(frame == 1 && Random_Int(0,8) + 1)
					{
						PlaySound_(m_nNormalSound);
						m_boRunSound = false;
					}
				}
				if(m_nCurrentAction == SM_HIT)
				{
					if(frame == 3 && m_nAttackSound >= 0)
					{
						PlaySound_(m_nWeaponSound);
						m_boRunSound = false;
					}
				}
				if(m_wAppearance == 80)
				{
					if(m_nCurrentAction == SM_NOWDEATH)
					{
						if(frame == 2)
						{
							PlaySound_(m_nDie2Sound);
							m_boRunSound = false;
						}
					}
				}
			}
		}
	}
}

void TActor::RunSound()
{
	m_boRunSound = true;
	SetSound();
	switch(m_nCurrentAction)
	{
	case SM_STRUCK:
		{
			if (m_nStruckWeaponSound >= 0)
			{
				PlaySound_(m_nStruckWeaponSound);
			}
				
			if (m_nStruckSound >= 0) 
			{
				PlaySound_(m_nStruckSound);
			}
				
			if (m_nScreamSound >= 0)
			{
				PlaySound_(m_nScreamSound);
			}
			break;
		}
	case SM_NOWDEATH:
		{
			if(m_nDieSound >= 0)
			{
				PlaySound_(m_nDieSound);
			}
			break;
		}
	case SM_ALIVE:
	case SM_DIGUP:
		{
			PlaySound_(m_nAppearSound);
			break;
		}
	case SM_SPELL:
		{
			PlaySound_(m_nMagicStartSound);
			break;
		}
	case SM_HEAVYHIT:
	case SM_SITDOWN:
		{
			if(g_TargetCret && g_TargetCret->m_btRace == RC_PLANT)
			{
				PlaySound_(s_sitdown + 1);   //植物
			}else
			{
				 PlaySound_(s_sitdown); //矿类采集声音
			}
			break;
		}
	}
}

void TActor::SetSound()
{
	if(m_btRace == 0)
	{
		if(this == g_MySelf && (m_nCurrentAction == SM_WALK ||
			m_nCurrentAction == SM_BACKSTEP || m_nCurrentAction == SM_RUN ||
			m_nCurrentAction == SM_HORSERUN || m_nCurrentAction == SM_RUSH ||
			m_nCurrentAction == SM_RUSHKUNG))
		{
			m_nFootStepSound = s_walk_ground_l; //走路声音
		}
		//设置被攻击和死亡声音
		if(m_btSex == 0)
		{
			m_nScreamSound = s_man_struck;
			m_nDieSound = s_man_die;
		}else
		{
			m_nScreamSound = s_wom_struck;
			m_nDieSound = s_wom_die;
		}
		switch(m_nCurrentAction)
		{
		case SM_THROW:
		case SM_HIT:
		case SM_HIT + 2:
		case SM_POWERHIT:
		case SM_LONGHIT:
		case SM_WIDEHIT:
		case SM_FIREHIT:
		case SM_CRSHIT:
		case SM_TWINHIT:
		case SM_34SKILLHIT:
		case SM_35SKILLHIT:
		case SM_103SKILLHIT:
		case SM_REMOTEHIT:
		case SM_MONSPELL:
			{
				if(m_btWeapon / 2 == 0)
				{
					m_nWeaponSound = s_hit_Weapon;
				}else
				{
					m_nWeaponSound = s_hit_fist;
				}
				break;
			}	
		}
		//默认音效无声
		m_nMagicStartSound = 0;
		m_nMagicFireSound = 0;
		m_nMagicExplosionSound = 0;
		//技能爆炸音效
		if(m_boUseMagic && m_CurMagic.MagicSerial > 0)
		{
			if( m_CurMagic.MagicSerial >= 1 && m_CurMagic.MagicSerial <= 13) //火球术和道神灵符灵魂火符
			{
				m_nMagicExplosionSound = 10132;
			}else if(m_CurMagic.MagicSerial == 2 || m_CurMagic.MagicSerial == 20 
				|| m_CurMagic.MagicSerial == 29)//治愈术 诱惑 群疗术
			{
				m_nMagicExplosionSound = 10202;
			}else if(m_CurMagic.MagicSerial == 33)//冰咆哮
			{
				m_nMagicExplosionSound = 10331;
			}else if(m_CurMagic.MagicSerial == 10)
			{
				m_nMagicStartSound = 10100; //开始就响
				m_nMagicFireSound = 10100;
			}else if(m_CurMagic.MagicSerial ==11) //雷电术
			{
				 m_nMagicExplosionSound = 10112;
			}else if(m_CurMagic.MagicSerial == 8) //抗拒火环
			{
				 m_nMagicExplosionSound = 11140;
			}else if(m_CurMagic.MagicSerial == 22) //火墙
			{
				m_nMagicExplosionSound = 10220;
			}else if(m_CurMagic.MagicSerial == 31) //魔法盾
			{
				m_nMagicExplosionSound = 10310;
			}else if(m_CurMagic.MagicSerial == 18)//小隐身术
			{
				m_nMagicExplosionSound = 11141;
			}else if(m_CurMagic.MagicSerial == 19)//大隐身术
			{
				m_nMagicExplosionSound = 11142;
			}else if(m_CurMagic.MagicSerial == 16)//大镇妖术
			{
				m_nMagicExplosionSound = 11144;
			}else if(m_CurMagic.MagicSerial == 38)//群毒
			{
				m_nMagicExplosionSound = 11145;
			}else if(m_CurMagic.MagicSerial == 14)//符咒护身
			{
				m_nMagicExplosionSound = 11146;
			}else if(m_CurMagic.MagicSerial == 24)//地狱魔焰
			{
				m_nMagicExplosionSound = 11147;
			}else if(m_CurMagic.MagicSerial == 32)//镇狱圣光
			{
				m_nMagicExplosionSound = 11148;
			}else if(m_CurMagic.MagicSerial == 17)//天神召唤
			{
				m_nMagicExplosionSound = 11149;
			}else if(m_CurMagic.MagicSerial == 150)
			{
				m_nMagicExplosionSound = 11150;
			}else if(m_CurMagic.MagicSerial == 23)//火龙气焰
			{
				m_nMagicExplosionSound = 11151;
			}
		}
	}

}


bool TActor::DrawChr(int dx, int dy, bool blend,bool boFlag,cocos2d::Layer* layer,bool ismask)
{
	if(m_btDir < DR_UP || m_btDir > DR_UPLEFT)
	{
		return false;
	}
	if(GetTickCount() - m_dwLoadSurfaceTime > 60 * 1000)
	{
		m_dwLoadSurfaceTime = GetTickCount();
		LoadSurface();
	}
	if(m_BodySurface)
	{
		int nx = dx + m_nPx + m_nShiftX;
		int ny = dy + m_nPy + m_nShiftY;
		layer->addChild(m_BodySurface->GetImage(nx,ny));
	}

	return true;
}
THumActor::THumActor(void)
{

	m_WeaponSurface = nullptr;
	m_boWeaponEffect = false;
	m_nCurWeaponEffect = 0;
	m_nCurBubbleStruck = 0;
	m_dwWeaponpEffectTime = 0;
	m_boHideWeapon = false;
	m_nFrame = 0;
	m_dwFrameTick = GetTickCount();
	m_dwFrameTime = 150;
	m_dwHitFrameTimeTime = 0;
	m_bo2D0 = false;

}

THumActor::~THumActor(void)
{

}


void THumActor::LoadSurface()
{
	//人物身体图片	
	if( m_btDress >= 0)
	{
		m_BodySurface	= GetHumImg(m_btDress, m_btSex, m_nCurrentFrame, m_nPx, m_nPy, m_btDressColor, m_btHorse);
		//人物身体影子图片
		m_BodySSurface = GetHumSImg(0, m_btSex, m_nCurrentFrame, m_nSpx, m_nSpy, m_btDressColor);
	}
	//如果身体图片前面没有加载到,则加载没有衣服的裸体
	if(! m_BodySurface )
	{
		m_BodySurface = GetHumImg(0, m_btSex, m_nCurrentFrame, m_nPx, m_nPy, m_btDressColor, m_btHorse);
	}
	//如果有马匹，加载马匹
	if(m_btHorse > 0)
	{
		m_HorseBodySurface = GetMonImage(m_btHorse, m_nCurrentFrame , m_nHopx, m_nHopy);
	}
	//翅膀图片
	if( m_bWings > 0)
	{
		m_WringsSurface = GetHumWringsImg(m_bWings, m_btSex, m_nCurrentFrame, m_nWx, m_nWy, m_btDressColor, m_btHorse);
	}
	if (m_btWeapon > 1 && m_nCurrentAction != SM_SITDOWN)
	{
		m_WeaponSurface = GetWWeaponImg(m_btWeapon,
			m_btSex, m_nCurrentFrame, m_nWpx, m_nWpy);
	}





}
void THumActor::RunFrameAction(int frame)
{
	m_boHideWeapon = false;
	if(m_nCurrentAction == SM_HEAVYHIT)
	{
		if(frame == 5 && m_boDigFragment)
		{
			m_boDigFragment = false;
			//meff := TMapEffect.Create(8 * m_btDir, 3, m_nCurrX, m_nCurrY);
			//meff.NextFrameTime := 80;
			//PlaySound(s_strike_stone);

			//g_PlayScene.m_EffectList.Add(meff);
			//event := EventMan.GetEvent(m_nCurrX, m_nCurrY, ET_PILESTONES);
			//If event <> Nil Then
			//	event.m_nEventParam := event.m_nEventParam + 1;
		}
	}
	if(m_nCurrentAction == SM_THROW)
	{
		if(frame == 3 && m_boThrow)
		{
			//m_boThrow := FALSE;
			//mfly := TFlyingAxe(g_PlayScene.NewFlyObject(Self,
			// m_nCurrX,
			// m_nCurrY,
			// m_nTargetX,
			// m_nTargetY,
			// m_nTargetRecog,
			// mtFlyAxe));
			//If mfly <> Nil Then
			// Begin
			// TFlyingAxe(mfly).ReadyFrame := 40;
			//mfly.FlyImageBase := FLYOMAAXEBASE;
			//End;
		}
		if(frame >= 3)
		{
			m_boHideWeapon = true;
		}
	}
}

int THumActor::GetDefaultFrame(bool wmode)
{
	int cf = 0,dr = 0,Result = 0;
	if(m_boDeath)
	{
		Result = HA.ActDie.start + m_btDir * (HA.ActDie.frame + HA.ActDie.skip) + (HA.ActDie.frame - 1);
	}else if(m_boSitDownMode)
	{
		m_nDefFrameCount = 1;
		if(m_nCurrentDefFrame < 0)
		{
			cf = 0;
		}else if(m_nCurrentDefFrame >= 1)
		{
			cf = 0;
		}else
		{
			cf = m_nCurrentDefFrame;
		}
		Result = HA.ActSitdown.start + m_btDir * (HA.ActSitdown.frame + HA.ActSitdown.skip) + cf;
	}else if(wmode) ///待攻击模式
	{
		m_nDefFrameCount = HA.ActWarMode.frame;
		if( m_nCurrentDefFrame < 0 )
		{
			cf = 0;
		}else if( m_nCurrentDefFrame >= HA.ActWarMode.frame)
		{
			cf = 0;
		}else
		{
			cf = m_nCurrentDefFrame;
		}
		Result = HA.ActWarMode.start + m_btDir * (HA.ActWarMode.frame + HA.ActWarMode.skip) + cf;
	}else if(m_bMeditation) //打坐
	{
		m_nDefFrameCount = HA.ActMeditation.frame;
		if( m_nCurrentDefFrame < 0 )
		{
			cf = 0;
		}else if( m_nCurrentDefFrame >= HA.ActMeditation.frame)
		{
			cf = 0;
		}else cf = m_nCurrentDefFrame;
		Result = HA.ActMeditation.start + m_btDir * (HA.ActMeditation.frame + HA.ActMeditation.skip) + cf;
	}else //默认
	{
		m_nDefFrameCount = HA.ActStand.frame;
		if( m_nCurrentDefFrame < 0 )
		{
			cf = 0;
		}else if(m_nCurrentDefFrame >= HA.ActStand.frame)
		{
			cf = 0;
		}else 
		{
			cf = m_nCurrentDefFrame;	
		}
		Result = HA.ActStand.start + m_btDir * (HA.ActStand.frame + HA.ActStand.skip) + cf;
	}
	return Result;
}
void THumActor::Run()
{
	int prv, ndir;
	unsigned int m_dwFrameTimetime;
	bool bofly = false;
	//pm                : PTClientMagic;
	//计算魔法盾等身上效果的时间和帧数
	if(GetTickCount() - m_dwGenAnicountTime > 120)
	{
		m_dwGenAnicountTime = GetTickCount();
		m_nGenAniCount++;
		if( m_nGenAniCount > 100000)
		{
			m_nGenAniCount = 0;
		}
		
		m_nCurBubbleStruck++;
	}
	if(m_boWeaponEffect)
	{
		if(GetTickCount() - m_dwWeaponpEffectTime > 120)
		{
			m_dwWeaponpEffectTime = GetTickCount();
			m_nCurWeaponEffect++;
			if(m_nCurWeaponEffect >= MAXWPEFFECTFRAME )
			{
				m_boWeaponEffect = false;
			}
		}
	}

	if (m_nCurrentAction == SM_WALK ||
		m_nCurrentAction == SM_BACKSTEP ||
		m_nCurrentAction == SM_RUN ||
		m_nCurrentAction == SM_HORSERUN ||
		m_nCurrentAction == SM_RUSH ||
		m_nCurrentAction == SM_RUSHKUNG)
	{
		return;
	}
	m_boMsgMuch = false;
	if( this != g_MySelf)
	{
		if(m_MsgList.size() >= 2)
		{
			m_boMsgMuch = true;
		}
	}
	RunActSound(m_nCurrentFrame - m_nStartFrame);
	RunFrameAction(m_nCurrentFrame - m_nStartFrame);
	prv = m_nCurrentFrame;
	if(m_nCurrentAction != 0)
	{
		if(m_nCurrentFrame < m_nStartFrame || m_nCurrentFrame > m_nEndFrame)
		{
			if(!m_boReverseFrame)
			{
				m_nCurrentFrame = m_nStartFrame;
			}else
			{
				m_nCurrentFrame = m_nEndFrame - 1;
			}
		}
		if (this != g_MySelf && m_boUseMagic)
		{
			m_dwFrameTimetime = int(m_dwFrameTime / 1.8);
		}else
		{
			if( m_boMsgMuch)
			{
				m_dwFrameTimetime = int(m_dwFrameTime * 2 / 3);
			}else
			{
				m_dwFrameTimetime = m_dwFrameTime ;
			}
		}
		if(GetTickCount() - m_dwStartTime > m_dwFrameTimetime)
		{
			if(!m_boReverseFrame)
			{
				if(m_nCurrentFrame < m_nEndFrame)
				{
					if(m_boUseMagic)
					{
						if(m_nCurEffFrame == m_nSpellFrame - 2 || MagicTimeOut())
						{
							if(m_CurMagic.ServerMagicCode >= 0 || MagicTimeOut())
							{
								//m_spell[1]=3表示第二张图片要画三次。。。用来表示动作停顿
								if(m_Spell[1] > 0 && m_nCurrentFrame - m_nStartFrame == 1)
								{
									m_Spell[1]--;
								}else if(m_Spell[3] > 0 && m_nCurrentFrame - m_nStartFrame == 3)
								{
									m_Spell[3] -- ;
								}else
								{
									m_nCurrentFrame++;
								}
								
								m_nCurEffFrame++;
								m_dwStartTime = GetTickCount();
							}
						}else
						{
							if(m_nCurrentFrame < m_nEndFrame)
							{
								if(m_Spell[1] > 0 && m_nCurrentFrame - m_nStartFrame == 1)
								{
									m_Spell[1]--;
								}else if(m_Spell[3] > 0 && m_nCurrentFrame - m_nStartFrame == 3)
								{
									m_Spell[3]--;
								}else
								{
									m_nCurrentFrame ++;
								}
							}
							m_nCurEffFrame++;
							m_dwStartTime = GetTickCount();
						}
					}else
					{
						m_nCurrentFrame++;
						m_dwStartTime = GetTickCount();
						m_btIdx = 0;
					}
				}else
				{
					if(this == g_MySelf)
					{
						if(FrmMain::GetInstance()->ServerAcceptNextAction())
						{
							m_nCurrentAction = 0;
							m_boUseMagic = false;
						}
					}else
					{
						m_nCurrentAction = 0;
						m_boUseMagic = false;
					}
					m_boHitEffect = false;
				}

			}else
			{
				if(m_nCurrentFrame > m_nStartFrame)
				{
					m_nCurrentFrame--;
					m_dwStartTime = GetTickCount();
					m_btIdx = 0;
				}else
				{
					m_nCurrentAction = 0;
				}
			}
			if(m_nCurrentAction == SM_REMOTEHIT && m_nCurrentFrame == m_nEndFrame - 1)
			{
				bool bofly;
				TPlayScene::GetInstance()->NewMagic(this,  //人物飞标攻击
					111,g_FocusCret->m_nGold,m_nCurrX,m_nCurrY,g_focuscret1->m_nCurrX,
					g_focuscret1->m_nCurrY,(int)g_focuscret1,TMagicType::mtExploBujauk,false,0,bofly);

			}
			if(m_boUseMagic)
			{
				if(m_nCurEffFrame == m_nSpellFrame - 1)
				{
					if(m_CurMagic.EffectNumber == 15 ||
						m_CurMagic.EffectNumber == 28)
					{
						switch (m_btDir)
						{
						case 0:
							{
								m_CurMagic.targx = m_nCurrX;
								m_CurMagic.targy = m_nCurrY - 1;
								break;
							}
						case 1:
							{
								m_CurMagic.targx = m_nCurrX + 1;
								m_CurMagic.targy = m_nCurrY - 1;
								break;
							}
						case 2:
							{
								m_CurMagic.targx = m_nCurrX + 1;
								m_CurMagic.targy = m_nCurrY;
								break;
							}
						case 3:
							{
								m_CurMagic.targx = m_nCurrX + 1;
								m_CurMagic.targy = m_nCurrY + 1;
								break;
							}
						case 4:
							{
								m_CurMagic.targx = m_nCurrX;
								m_CurMagic.targy = m_nCurrY + 1;
								break;
							}
						case 5:
							{
								m_CurMagic.targx = m_nCurrX - 1;
								m_CurMagic.targy = m_nCurrY + 1;
								break;
							}
						case 6:
							{
								m_CurMagic.targx = m_nCurrX - 1;
								m_CurMagic.targy = m_nCurrY;
								break;
							}
						case 7:
							{
								m_CurMagic.targx = m_nCurrX - 1;
								m_CurMagic.targy = m_nCurrY - 1;
								break;
							}
						}

					}
					if( m_CurMagic.ServerMagicCode > 0 )
					{
						TPlayScene::GetInstance()->NewMagic(this,m_CurMagic.ServerMagicCode,
							m_CurMagic.EffectNumber,m_nCurrX,m_nCurrY,m_CurMagic.targx,m_CurMagic.targy
							,m_CurMagic.target,m_CurMagic.EffectType,m_CurMagic.Recusion,m_CurMagic.anitime,bofly);
						if(m_CurMagic.MagicSerial == 110)
						{
							 ndir = m_btDir - 1;
							int targx = m_nCurrX;
						
							int targy = m_nCurrY;
							if(ndir < 0)
							{
								ndir = 7;
							}
							GetNextPosXY(ndir, targx, targy);
							TPlayScene::GetInstance()->NewMagic(this,m_CurMagic.ServerMagicCode,
								m_CurMagic.EffectNumber,m_nCurrX,m_nCurrY,m_CurMagic.targx,m_CurMagic.targy,m_CurMagic.target,
								m_CurMagic.EffectType,m_CurMagic.Recusion,m_CurMagic.anitime,bofly);
							targx =m_nCurrX;
							targy = m_nCurrY;
							ndir = m_btDir + 1;
							if(ndir > 7) ndir = 0;
							GetNextPosXY(ndir, targx, targy);
							TPlayScene::GetInstance()->NewMagic(this,m_CurMagic.ServerMagicCode,
								m_CurMagic.EffectNumber,m_nCurrX,m_nCurrY,m_CurMagic.targx,m_CurMagic.targy,m_CurMagic.target,
								m_CurMagic.EffectType,m_CurMagic.Recusion,m_CurMagic.anitime,bofly);
						}
					}
					if(bofly)
					{
						PlaySound_(m_nMagicFireSound);
					}else
					{
						if(m_CurMagic.EffectNumber == 20)
						{
							PlaySound_(m_nMagicExplosionSound, 
								m_CurMagic.targx, m_CurMagic.targy, true);
						}else
						{
							PlaySound_(m_nMagicExplosionSound, m_CurMagic.targx, m_CurMagic.targy);
						}
					}
					m_CurMagic.ServerMagicCode = 0;
				}
				
			}
		}
		if( m_btRace == 0)
		{
			m_nCurrentDefFrame = 0;
		}else
		{
			m_nCurrentDefFrame = -10;
			m_dwDefFrameTime = GetTickCount();
		}
	}else
	{
		m_btIdx = 0;
		if(GetTickCount() - m_dwSmoothMoveTime > 200)
		{
			if(GetTickCount() - m_dwDefFrameTime > 500)
			{
				m_dwDefFrameTime = GetTickCount();
				m_nCurrentDefFrame++;
				if( m_nCurrentDefFrame >= m_nDefFrameCount )
				{
					m_nCurrentDefFrame = 0;
				}
			}
			DefaultMotion();
		}
	}

	if(prv != m_nCurrentFrame)
	{
		m_dwLoadSurfaceTime = GetTickCount();
		LoadSurface();	
	}

}
void THumActor::CalcActorFrame()
{
	int haircount = 0;
	m_boUseMagic = false;
	m_boHitEffect = false;
	m_boMagicEff = false;
	m_nCurrentFrame = -1;

	m_btHair = HAIRfeature(m_nFeature);
	m_btDress = DRESSfeature(m_nFeature);
	m_btWeapon = WEAPONfeature(m_nFeature);
	m_btHorse = Horsefeature(m_nFeatureEx);
	m_btEffect = Effectfeature(m_nFeatureEx);
	m_btDressColor = Colorfeature(m_nFeatureEx);
	m_nBodyOffset = HUMANFRAME * (m_btDress / 2);

	m_btHair = (m_btHair - m_btDress % 2) / 2;
	haircount = -1;
	switch(m_btDress % 2)
	{
	case 0:
		{
			haircount = m_btHair * 2;
			break;
		}
	case 1:
		{
			haircount = m_btHair + 1;
			break;
		}
	}
	if( haircount > 0 )
	{
		m_nHairOffset = HUMANFRAME * (haircount + m_btSex);
	}else
	{
		m_nHairOffset = -1;
	}
	m_nWeaponOffset = HUMANFRAME * m_btWeapon;
	if (m_btEffect == 50) 
	{
		m_nHumWinOffset = 352;
	}else if(m_btEffect != 0)
	{
		m_nHumWinOffset = (m_btEffect - 1) * HUMANFRAME;
	}

	switch(m_nCurrentAction)
	{
	case SM_TURN:
		{
			m_nStartFrame = HA.ActStand.start + m_btDir * (HA.ActStand.frame + HA.ActStand.skip);
			m_nEndFrame = m_nStartFrame + HA.ActStand.frame - 1;
			Shift(m_btDir, 0, 0, m_nEndFrame - m_nStartFrame + 1);
			break;
		}
	case SM_MEDITATION:
		{
			m_nStartFrame = HA.ActMeditation.start + m_btDir * (HA.ActMeditation.frame + HA.ActMeditation.skip);
			m_nEndFrame = m_nStartFrame + HA.ActMeditation.frame - 1;
			m_dwFrameTime = HA.ActMeditation.ftime;
			m_dwStartTime = GetTickCount();
			m_nDefFrameCount = HA.ActMeditation.frame;
			Shift(m_btDir, 0, 0, m_nEndFrame - m_nStartFrame + 1);
			break;
		}
	case SM_BACKSTEP:
		{
			m_nStartFrame = HA.ActWalk.start + m_btDir * (HA.ActWalk.frame + HA.ActWalk.skip);
			m_nEndFrame = m_nStartFrame;
			m_dwFrameTime = HA.ActWalk.ftime;
			m_dwStartTime = GetTickCount();
			m_nMaxTick = HA.ActWalk.usetick;
			m_nCurTick = 0;

			m_nMoveStep = 1;
			Shift(GetBack(m_btDir), m_nMoveStep, 0, m_nEndFrame - m_nStartFrame + 1);
			break;
		}
	case SM_WALK:
		{
			m_nStartFrame = HA.ActWalk.start + m_btDir * (HA.ActWalk.frame + HA.ActWalk.skip);
			m_nEndFrame = m_nStartFrame + HA.ActWalk.frame - 1;
			m_dwFrameTime = HA.ActWalk.ftime;
			m_dwStartTime = GetTickCount();
			m_nMaxTick = HA.ActWalk.usetick;
			m_nCurTick = 0;
			m_nMoveStep = 1;
			if( m_nCurrentAction == SM_BACKSTEP )
			{
				Shift(GetBack(m_btDir), 2, 0, m_nEndFrame - m_nStartFrame + 1);
			}else
			{
				Shift(m_btDir, m_nMoveStep, 0, m_nEndFrame - m_nStartFrame + 1);
			}


			break;
		}
	case SM_RUSH:
		{
			m_nStartFrame = HA.ActRush.start + m_btDir * (HA.ActRush.frame + HA.ActRush.skip);
			m_nEndFrame = m_nStartFrame + HA.ActRush.frame - 1;
			m_dwFrameTime = HA.ActRush.ftime;
			m_dwStartTime = GetTickCount();
			m_nMaxTick = HA.ActRush.usetick;
			m_nCurTick = 0;
			m_nMoveStep = 1;

			m_boHitEffect = true;
			m_nMagLight = 2;
			m_nHitEffectNumber = 25;

			Shift(m_btDir, m_nMoveStep, 0, m_nEndFrame - m_nStartFrame + 1);
			break;
		}
	case SM_RUSHKUNG:
		{
			m_nStartFrame = HA.ActRun.start + m_btDir * (HA.ActRun.frame + HA.ActRun.skip);
			m_nEndFrame = m_nStartFrame + HA.ActRun.frame - 1;
			m_dwFrameTime = HA.ActRun.ftime;
			m_dwStartTime = GetTickCount();
			m_nMaxTick = HA.ActRun.usetick;
			m_nCurTick = 0;
			m_nMoveStep = 1;  
			Shift(m_btDir, m_nMoveStep, 0, m_nEndFrame - m_nStartFrame + 1);
			break;
		}
	case SM_SITDOWN:
		{
			m_nStartFrame = HA.ActSitdown.start + m_btDir * (HA.ActSitdown.frame + HA.ActSitdown.skip);
			m_nEndFrame = m_nStartFrame + HA.ActSitdown.frame - 1;
			m_dwFrameTime = HA.ActSitdown.ftime;
			m_boSitDownMode = true;
			m_dwSitDownModeTime = GetTickCount();
			m_dwStartTime = GetTickCount();
			break;
		}
	case SM_BUTCH:
		{
			m_nStartFrame = HA.ActSitdown.start + m_btDir * (HA.ActSitdown.frame + HA.ActSitdown.skip);
			m_nEndFrame = m_nStartFrame + HA.ActSitdown.frame - 1;
			m_dwFrameTime = HA.ActSitdown.ftime;
			m_boSitDownMode = true;
			m_dwSitDownModeTime = GetTickCount();
			m_dwStartTime = GetTickCount();
			break;
		}
	case SM_RUN:
		{
			m_nStartFrame = HA.ActRun.start + m_btDir * (HA.ActRun.frame + HA.ActRun.skip);
			m_nEndFrame = m_nStartFrame + HA.ActRun.frame - 1;
			m_dwFrameTime = HA.ActRun.ftime;
			m_dwStartTime = GetTickCount();
			m_nMaxTick = HA.ActRun.usetick;
			m_nCurTick = 0;
			if( m_nCurrentAction == SM_RUN )
			{
				m_nMoveStep = 2;
			}else m_nMoveStep = 1;
			Shift(m_btDir, m_nMoveStep, 0, m_nEndFrame - m_nStartFrame + 1);
			break;
		}
	case SM_HORSERUN:
		{
			m_nStartFrame = HA.ActRun.start + m_btDir * (HA.ActRun.frame + HA.ActRun.skip);
			m_nEndFrame = m_nStartFrame + HA.ActRun.frame - 1;
			m_dwFrameTime = HA.ActRun.ftime;
			m_dwStartTime = GetTickCount();
			m_nMaxTick = HA.ActRun.usetick;
			m_nCurTick = 0;

			if( m_nCurrentAction == SM_HORSERUN)
			{
				m_nMoveStep = 3;
			}else
			{
				m_nMoveStep = 1;
			}
			Shift(m_btDir, m_nMoveStep, 0, m_nEndFrame - m_nStartFrame + 1);
			break;
		}
	case SM_THROW:
		{
			m_nStartFrame = HA.ActHit.start + m_btDir * (HA.ActHit.frame + HA.ActHit.skip);
			m_nEndFrame = m_nStartFrame + HA.ActHit.frame - 1;
			m_dwFrameTime = HA.ActHit.ftime;
			m_dwStartTime = GetTickCount();
			m_boWarMode = true;
			m_dwWarModeTime = GetTickCount();
			m_boThrow = true;
			Shift(m_btDir, 0, 0, 1);
			break;
		}
	case SM_HIT:
	case SM_POWERHIT:
	case SM_LONGHIT:
	case SM_WIDEHIT:
	case SM_FIREHIT:
	case SM_CRSHIT:
	case SM_TWINHIT:
	case SM_REMOTEHIT:
	case SM_34SKILLHIT:
	case SM_35SKILLHIT: 
	case SM_103SKILLHIT:
		{
			m_nStartFrame = HA.ActHit.start + m_btDir * (HA.ActHit.frame + HA.ActHit.skip);
			m_nEndFrame = m_nStartFrame + HA.ActHit.frame - 1;
			m_dwFrameTime = HA.ActHit.ftime;
			m_boWarMode = true;    
			m_boSitDownMode = false;
			m_dwSitDownModeTime = GetTickCount();
			m_dwStartTime = GetTickCount();
			m_dwWarModeTime = GetTickCount();
			if (m_nCurrentAction == SM_POWERHIT)
			{
				m_boHitEffect = true;
				m_nMagLight = 2;
				m_nHitEffectNumber = 5;
			}

			if (m_nCurrentAction == SM_LONGHIT) 
			{
				m_boHitEffect = true;
				m_nMagLight = 2;
				m_nHitEffectNumber = 13;
			}


			if (m_nCurrentAction == SM_WIDEHIT) 
			{
				m_boHitEffect = true;
				m_nMagLight = 2;
				m_nHitEffectNumber = 23;
			}

			if (m_nCurrentAction == SM_FIREHIT) 
			{
				m_boHitEffect = true;
				m_nMagLight = 2;
				m_nHitEffectNumber = 24;
			}


			if (m_nCurrentAction == SM_CRSHIT)
			{
				m_boHitEffect = true;
				m_nMagLight = 2;
				m_nHitEffectNumber = 6;
			}

			if (m_nCurrentAction == SM_TWINHIT) 
			{
				m_boHitEffect = true;
				m_nMagLight = 2;
				m_nHitEffectNumber = 7;
			}


			if (m_nCurrentAction == SM_34SKILLHIT) 
			{
				m_nStartFrame = HA.Act34Hit.start + m_btDir * (HA.Act34Hit.frame + HA.Act34Hit.skip);
				m_nEndFrame = m_nStartFrame + HA.Act34Hit.frame - 1;
				m_dwFrameTime = HA.Act34Hit.ftime;
				m_dwStartTime = GetTickCount();
				m_boWarMode = true;
				m_dwWarModeTime = GetTickCount();
				m_boHitEffect = true;
				m_nMagLight = 2;
				m_nHitEffectNumber = 8;
			}
			if (m_nCurrentAction == SM_35SKILLHIT)
			{
				m_nStartFrame = HA.Act35Hit.start + m_btDir * (HA.Act35Hit.frame + HA.Act35Hit.skip);
				m_nEndFrame = m_nStartFrame + HA.Act35Hit.frame - 1;
				m_dwFrameTime = HA.Act35Hit.ftime;
				m_dwStartTime = GetTickCount();
				m_boWarMode = true;
				m_dwWarModeTime = GetTickCount();
				m_boHitEffect = true;
				m_nMagLight = 2;
				m_nHitEffectNumber = 9;
			}
			if (m_nCurrentAction == SM_103SKILLHIT) 
			{
				m_nStartFrame = HA.Act103Hit.start + m_btDir * (HA.Act103Hit.frame + HA.Act103Hit.skip);
				m_nEndFrame = m_nStartFrame + HA.Act103Hit.frame - 1;
				m_dwFrameTime = HA.Act103Hit.ftime;
				m_dwStartTime = GetTickCount();
				m_boWarMode = true;
				m_dwWarModeTime = GetTickCount();
				m_boHitEffect = true;
				m_nMagLight = 2;
				m_nHitEffectNumber = 10;
			}
			Shift(m_btDir, 0, 0, 1);

			break;
		}
	case SM_HEAVYHIT:
		{
			m_nStartFrame = HA.ActHeavyHit.start + m_btDir * (HA.ActHeavyHit.frame + HA.ActHeavyHit.skip);
			m_nEndFrame = m_nStartFrame + HA.ActHeavyHit.frame - 1;
			m_dwFrameTime = HA.ActHeavyHit.ftime;
			m_dwStartTime = GetTickCount();
			m_boSitDownMode = true;
			m_dwSitDownModeTime = GetTickCount(); 
			m_dwStartTime = GetTickCount();
			Shift(m_btDir, 0, 0, 1);
			break;
		}
	case SM_BIGHIT:
		{
			m_nStartFrame = HA.ActBigHit.start + m_btDir * (HA.ActBigHit.frame + HA.ActBigHit.skip);
			m_nEndFrame = m_nStartFrame + HA.ActBigHit.frame - 1;
			m_dwFrameTime = HA.ActBigHit.ftime;
			m_dwStartTime = GetTickCount();
			m_boWarMode = true;
			m_dwWarModeTime = GetTickCount();
			Shift(m_btDir, 0, 0, 1);
			break;
		}
	case SM_MONSPELL:
		{
			break;
		}
	case SM_SPELL:
		{
			m_boUseMagic = true;
			if ((m_CurMagic.EffectNumber >=60 && m_CurMagic.EffectNumber >= 62) &&
				(m_btJob == 0) )
			{
				m_nStartFrame = HA.ActHit.start + m_btDir * (HA.ActHit.frame + HA.ActHit.skip);
				m_nEndFrame = m_nStartFrame + HA.ActHit.frame - 1;
				m_dwFrameTime = HA.ActFSpell.ftime;
				m_dwStartTime = GetTickCount();
				m_nDefFrameCount = HA.ActStand.frame;
				m_nCurEffFrame = 0;
				m_nMagLight = 2;
				if( m_CurMagic.EffectNumber == 62 )
				{
					m_nCurrentFrame = 0;
					m_boHitEffect = true;
					m_nHitEffectNumber = 10;
				}

				m_dwWaitMagicmode1 = 1000;
				m_dwWaitMagicmode2 = 1000;
			}else
			{
				if(m_CurMagic.EffectNumber == 1 ||
					m_CurMagic.EffectNumber == 3 ||
					m_CurMagic.EffectNumber == 7 ||
					m_CurMagic.EffectNumber == 8 ||
					m_CurMagic.EffectNumber == 10 || m_CurMagic.EffectNumber == 11 ||
					m_CurMagic.EffectNumber == 12 || m_CurMagic.EffectNumber == 17 ||
					m_CurMagic.EffectNumber == 28 || m_CurMagic.EffectNumber == 35 ||
					m_CurMagic.EffectNumber == 36 || m_CurMagic.EffectNumber == 37 ||
					m_CurMagic.EffectNumber == 38 || m_CurMagic.EffectNumber == 39 ||
					m_CurMagic.EffectNumber == 41 || m_CurMagic.EffectNumber == 51 ||
					m_CurMagic.EffectNumber == 55 || m_CurMagic.EffectNumber == 65 ||
					m_CurMagic.EffectNumber == 87 || m_CurMagic.EffectNumber == 92)
				{
					if(m_CurMagic.EffectNumber == 1 || m_CurMagic.EffectNumber == 7 ||
						m_CurMagic.EffectNumber == 10 || m_CurMagic.EffectNumber == 11 ||
						m_CurMagic.EffectNumber == 12 || m_CurMagic.EffectNumber == 17 ||
						m_CurMagic.EffectNumber == 28 || m_CurMagic.EffectNumber == 35 ||
						m_CurMagic.EffectNumber == 36 || m_CurMagic.EffectNumber == 37 ||
						m_CurMagic.EffectNumber == 38 || m_CurMagic.EffectNumber == 39 ||
						m_CurMagic.EffectNumber == 87 || m_CurMagic.EffectNumber == 92)
					{
						m_Spell[1] = 3;
					}
					if(m_CurMagic.EffectNumber == 3 || m_CurMagic.EffectNumber == 65)
					{
						m_Spell[1] = 4;
					}
					if(m_CurMagic.EffectNumber == 8 || m_CurMagic.EffectNumber == 41 ||
						m_CurMagic.EffectNumber == 51 || m_CurMagic.EffectNumber == 52 ||
						m_CurMagic.EffectNumber == 55)
					{
						m_Spell[1] = 5;
					}
					m_nStartFrame = HA.ActTSpell.start + m_btDir * (HA.ActTSpell.frame + HA.ActTSpell.skip);
					m_nEndFrame = m_nStartFrame + HA.ActTSpell.frame - 1;
					m_dwFrameTime = HA.ActTSpell.ftime;
				}
				int ia[] = {2, 4, 6, 9, 14, 15, 16, 18, 19, 20, 21, 22, 23, 27, 29, 30, 31, 40, 53, 54, 70, 71, 72, 75, 120, 121, 122, 123,203};
				int nLen = sizeof(ia) / sizeof(ia[0]);
				for(int i = 0;i < nLen;i++)
				{
					if(m_CurMagic.EffectNumber == ia[i])
					{
						int ib[] = {2, 4, 14, 15, 16, 18, 19, 20, 21, 27, 30, 31, 40, 75, 120, 122, 123};
						for(int j = 0;j < sizeof(ib) / sizeof(ib[0]);j++)
						{
							if(m_CurMagic.EffectNumber == ib[j])
							{
								m_Spell[3] = 5;
								break;
							}
						}

						if(m_CurMagic.EffectNumber == 121)
						{
							m_Spell[3] = 2;
						}
						if(m_CurMagic.EffectNumber == 6 || m_CurMagic.EffectNumber == 29 ||
							m_CurMagic.EffectNumber == 9 || m_CurMagic.EffectNumber == 22 ||
							m_CurMagic.EffectNumber == 53 || m_CurMagic.EffectNumber == 203)
						{
							m_Spell[3] = 3;
						}
						if(m_CurMagic.EffectNumber == 23 || m_CurMagic.EffectNumber == 54 ||
							m_CurMagic.EffectNumber == 70 || m_CurMagic.EffectNumber == 71 ||
							m_CurMagic.EffectNumber == 72)
						{
							m_Spell[3]  = 7;
						}
						m_nStartFrame = HA.ActFSpell.start + m_btDir * (HA.ActFSpell.frame + HA.ActFSpell.skip);
						m_nEndFrame = m_nStartFrame + HA.ActFSpell.frame - 1;
						m_dwFrameTime = HA.ActFSpell.ftime;
						break;
					}
				}
				if(m_CurMagic.EffectNumber == 34) 
				{
					m_nStartFrame = HA.ActKQStruck.start + m_btDir * (HA.ActKQStruck.frame + HA.ActKQStruck.skip);
					m_nEndFrame = m_nStartFrame + HA.ActKQStruck.frame - 1;
					m_dwFrameTime = HA.ActKQStruck.ftime;
					m_boUseMagic = false;
				}
				m_dwStartTime = GetTickCount();
				m_nCurEffFrame = 0;
				m_dwWaitMagicmode1 = 3000;
				m_dwWaitMagicmode2 = 2000;
			}
			switch(m_CurMagic.EffectNumber)//得到表现在人物身上的魔法效果图片数
			{
			case 4:
				{
					m_nSpellFrame = 8;
					break;
				}
			case 11:
			case 12:
			case 17:
			case 28:
			case 35:
			case 36:
			case 37:
			case 38:
			case 39:
			case 87:
			case 92:
				{
					m_nSpellFrame = 6;
					break;
				}
			case 1:
			case 6:
			case 7:
			case 121:
				{
					m_nSpellFrame = 8;
					break;
				}
			case 29:
				{
					m_dwWaitMagicmode1 = 3000 * 2;
					m_dwWaitMagicmode2 = 2000 * 2;
					m_nSpellFrame = 16;
					break;
				}
			case 3:
			case 53:
				{
					m_nSpellFrame = 9;
					break;
				}
			case 26:
				{
					m_nMagLight = 2;
					m_nSpellFrame = 20;
					m_dwFrameTime = m_dwFrameTime / 2;
					break;
				}
			case 43:
				{
					m_nMagLight = 2;
					m_nSpellFrame = 20;
					break;
				}
			case 60:
				{
					m_nMagLight = 2;
					m_nSpellFrame = 20;
					break;
				}
			case 8:
				{
					m_nMagLight = 2;
					m_nSpellFrame = 8;
					break;
				}
			case 9:
				{
					m_nMagLight = 2;
					m_nSpellFrame = 3;
					break;
				}
			case 10:
				{
					m_nMagLight = 2;
					m_nSpellFrame = 8;
					break;
				}
			case 31:
				{
					m_nMagLight = 2;
					m_nSpellFrame = 8;
					break;
				}
			case 203:
				{
					m_nMagLight = 2;
					m_nSpellFrame = 11;
					m_dwFrameTime = 70;
					break;
				}
			default:
				{
					m_nMagLight = 2;
					m_nSpellFrame = DEFSPELLFRAME;
				}

			}

			m_dwWaitMagicRequest = GetTickCount();
			m_boWarMode = true;
			m_dwWarModeTime = GetTickCount();
			Shift(m_btDir, 0, 0, 1);

			break;
		}
	case SM_STRUCK:
		{
			m_nStartFrame = HA.ActStruck.start + m_btDir * (HA.ActStruck.frame + HA.ActStruck.skip);
			m_nEndFrame = m_nStartFrame + HA.ActStruck.frame - 1;
			m_dwFrameTime = m_dwStruckFrameTime;
			m_dwStartTime = GetTickCount();
			Shift(m_btDir, 0, 0, 1);
			m_dwGenAnicountTime = GetTickCount();
			m_nCurBubbleStruck = 0;
			break;
		}
	case SM_NOWDEATH:
		{
			m_nStartFrame = HA.ActDie.start + m_btDir * (HA.ActDie.frame + HA.ActDie.skip);
			m_nEndFrame = m_nStartFrame + HA.ActDie.frame - 1;
			m_dwFrameTime = HA.ActDie.ftime;
			m_dwStartTime = GetTickCount();
			break;
		}
	case SM_ALIVE:
		{
			m_nStartFrame = HA.ActDie.start + m_btDir * (HA.ActDie.frame + HA.ActDie.skip);
			m_nEndFrame = m_nStartFrame + HA.ActDie.frame - 1;
			m_dwFrameTime = HA.ActDie.ftime;
			m_dwStartTime = GetTickCount();
			m_boReverseFrame = true;
		}
	}

}
bool THumActor::DrawChr(int dx, int dy, bool blend,bool boFlag,cocos2d::Layer* layer,bool ismask)
{
	int chkCode = 0;
	if (((m_nState & 0x40000) != 0) && (this != g_MySelf)) //妙影无踪隐身
		return true;
	TVDImage* AgeImg = GetUIImage(35); //人物未加载时的蛋蛋造型
	//DrawEatItem(dx,dy);
	// If Not (m_btDir In [0..7]) Then Exit;
	if(!(m_btDir >= 0 && m_btDir <= 7))
	{
		if(!m_BodySSurface || GetTickCount() - m_dwLoadSurfaceTime > 60 * 1000)
		{
			m_dwLoadSurfaceTime = GetTickCount();
			LoadSurface();
		}
	}
	chkCode = 1;
	//	ceff = GetDrawEffectValue();
	if(m_btRace == 0)
	{
		if(m_nCurrentFrame >= 0 && m_nCurrentFrame <= 2999)
		{
			m_nWpord = WORDER[m_btSex][m_nCurrentFrame];
		}
		//马匹
		chkCode = 2;
		if(m_btHorse > 0)
		{
			if(m_HorseBodySurface && m_HorseBodySurface->Image_)
			{
				layer->addChild(m_HorseBodySurface->GetImage(dx + m_nHopx + m_nShiftX,
					dy + m_nHopy + m_nShiftY));
			}
		}else
		{//画影子  没骑马的画影子
			if(m_BodySSurface && m_BodySSurface->Image_)
			{
				layer->addChild(m_BodySSurface->GetImage(dx + m_nSpx + m_nShiftX,
					dy + m_nSpy + m_nShiftY));
			}
		}

		//画翅膀
		if(m_btDir ==  DR_DOWNRIGHT )
		{
			if(m_bWings > 0 && g_UseItems[U_FASHIONDRESS].s.Weight == 0/*雪人时装不画翅膀*/ &&
				m_WringsSurface && m_WringsSurface->Image_)
			{
				int nx = dx + m_nWx + m_nShiftX;
				int ny = dy + m_nWy + m_nShiftY;
				cocos2d::Sprite* img = m_WringsSurface->GetImage(nx,ny);
				img->setOpacity(255);
				if(ismask)img->setOpacity(150);
				layer->addChild(img);
			}
		}

		//2013.6.26  层次修改 文艺青年
		if(m_btDir == DR_UP || m_btDir == DR_DOWNLEFT || m_btDir == DR_LEFT || m_btDir == DR_UPLEFT)
		{
			chkCode = 6;
			//画武器吧
			if (m_btHorse == 0 //And (m_nWpord{20111229 某些帧不带武器 暂时不用} = 0)
				&& m_btWeapon >= 2
				&& m_WeaponSurface   
				&& m_WeaponSurface->Image_
				&& !m_boHideWeapon
				&& m_nCurrentAction != SM_MEDITATION 
				&& m_nCurrentAction != SM_SITDOWN)/*{打坐和采集不画武器}*/ 
			{
				int nx = dx + m_nWpx + m_nShiftX;
				int ny = dy + m_nWpy + m_nShiftY;
				cocos2d::Sprite* img = m_WeaponSurface->GetImage(nx,ny);
				img->setOpacity(255);
				if(ismask)img->setOpacity(150);
				layer->addChild(img);
			}
			chkCode = 3;
			//身体
			if(m_BodySurface && m_BodySurface->Image_)
			{
				chkCode  = 4;
				int nx = dx + m_nPx + m_nShiftX;
				int ny = dy + m_nPy + m_nShiftY;
				cocos2d::Sprite* img = m_BodySurface->GetImage(nx,ny);
				if(ismask)
				{
					img->setOpacity(150);
				}else
				{
					img->setOpacity(255);
				}
				layer->addChild(img);
			}else
			{
				if(AgeImg)
				{
					layer->addChild(AgeImg->GetImage(dx + m_nShiftX,
						dy + m_nShiftY - (AgeImg->pHeight - 5)));
				}
				CCLOG("load body surface error!");
			}
		}else
		{
			chkCode = 3;
			if(m_BodySurface && m_BodySurface->Image_)
			{
				int nx = dx + m_nPx + m_nShiftX;
				int ny = dy + m_nPy + m_nShiftY;
				cocos2d::Sprite* img = m_BodySurface->GetImage(nx,ny);
				if(ismask)
				{
					img->setOpacity(150);
				}else
				{
					img->setOpacity(255);
				}
				layer->addChild(img);

			}else
			{
				if(AgeImg && AgeImg->Image_)
				{
					layer->addChild(AgeImg->GetImage(dx + m_nShiftX,
						dy + m_nShiftY - (AgeImg->pHeight - 5)));
				}
				CCLOG("load body surface error!");
			}

			//画武器吧
			if (m_btHorse == 0 //And (m_nWpord{20111229 某些帧不带武器 暂时不用} = 0)
				&& m_btWeapon >= 2
				&& m_WeaponSurface  
				&& m_WeaponSurface->Image_
				&& !m_boHideWeapon
				&& m_nCurrentAction != SM_MEDITATION 
				&& m_nCurrentAction != SM_SITDOWN)/*{打坐和采集不画武器}*/ 
			{
				int nx = dx + m_nWpx + m_nShiftX;
				int ny = dy + m_nWpy + m_nShiftY;
				cocos2d::Sprite* img = m_WeaponSurface->GetImage(nx,ny);
				img->setOpacity(255);
				if(ismask)img->setOpacity(150);
				layer->addChild(img);
			}
		}
		//画翅膀
		if(m_btDir !=  DR_DOWNRIGHT )
		{
			if(m_bWings > 0 && g_UseItems[U_FASHIONDRESS].s.Weight == 0/*雪人时装不画翅膀*/ &&
				m_WringsSurface && m_WringsSurface->Image_)
			{
				int nx = dx + m_nWx + m_nShiftX;
				int ny = dy + m_nWy + m_nShiftY;
				cocos2d::Sprite* img = m_WringsSurface->GetImage(nx,ny);
				img->setOpacity(255);
				if(ismask)img->setOpacity(150);
				layer->addChild(img);
			}
		}


	}
	//打坐特效
	int ax = 0,ay = 0;
	
	if(m_bMeditation)
	{
		TVDImage* img = GetEffectImage(200, m_nGenAniCount % 10, ax,ay);
		if(img && img->Image_)
		{
			layer->addChild(img->GetImage(dx + ax + m_nShiftX,
				dy + ay + m_nShiftY));
		}
	}
	//绘制魔法盾
	int idx = 0;
	if((m_nState & 0x00100000) != 0)
	{
		 //被攻击时有变化效果
		if(m_nCurrentAction == SM_STRUCK && m_nCurBubbleStruck < 3)
		{
			idx = 12 + m_nCurBubbleStruck;
		}else
		{
			idx = 9 + (m_nGenAniCount % 3);
		}
		TVDImage* img = GetEffectImage(28/*魔法盾技能编号*/ , idx, ax,ay);
		if(img && img->Image_)
		{
			layer->addChild(img->GetImage(dx + ax + m_nShiftX,
				dy + ay + m_nShiftY));
		}
	}

	//阴阳法环 什么鬼
	TVDImageDatas* wimg = nullptr;
	//有攻击对象，且对象为植物矿石
	if(m_boSitDownMode)
	{
		//不画效果
	}else//不是挖矿采集，正常绘制攻击效果魔法效果等
	{
		//人物魔法开始动作     技能释放时的聚气效果
		idx = 0;
		if(m_boUseMagic && m_CurMagic.EffectNumber > 0)
		{
			if(m_nCurEffFrame >= 0 && m_nCurEffFrame < m_nSpellFrame)
			{
				
				if(m_CurMagic.EffectNumber == 11 || m_CurMagic.EffectNumber == 15 ||
					m_CurMagic.EffectNumber == 17)
				{
					wimg = GetEffectBase(10 - 1, 0);
					idx = m_nCurEffFrame;
				}else if(m_CurMagic.EffectNumber == 21)//爆裂聚气效果用火墙的聚气
				{
					wimg = GetEffectBase(20 - 1, 0);
					idx = m_nCurEffFrame;
				}else if(m_CurMagic.EffectNumber == 19)// //瞬移效果用圣言的聚气
				{
					wimg =GetEffectBase(30 - 1, 0);
					idx = m_nCurEffFrame;
				}else if(m_CurMagic.EffectNumber == 2 ||  //治愈术和群疗术
					m_CurMagic.EffectNumber == 27)
				{
					wimg = GetEffectBase(2 - 1, 0);
					idx = m_nCurEffFrame;
				}else if(m_CurMagic.EffectNumber == 4 ||  //施毒术和群体施毒术公用
					m_CurMagic.EffectNumber == 36)
				{
					wimg = GetEffectBase(4 - 1, 0);
					idx = m_nCurEffFrame;
				}else
				{
					wimg = GetEffectBase(m_CurMagic.EffectNumber - 1, 0);
					idx = m_nCurEffFrame;
				}
				if(wimg)
				{
					TVDImage* d = wimg->GetImage(idx);
					if(d && d->Image_)
					{
						BlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
						cocos2d::Sprite* s = d->GetImage(dx + d->nx + m_nShiftX,dy + d->ny + m_nShiftY);
						s->setBlendFunc(cbl);
						layer->addChild(s);
					}
				}
			}
		}
	}

	//攻击效果的绘制 比如刺杀效果
	if(m_boHitEffect && m_nHitEffectNumber > 0)
	{
		wimg = GetEffectBase(m_nHitEffectNumber - 1, 1);
		if(m_nHitEffectNumber != 10)
		{
			 idx = m_btDir * 10 + (m_nCurrentFrame - m_nStartFrame);
		}else
		{
			idx = (m_nCurrentFrame - m_nStartFrame);
		}
		if(wimg)
		{
			TVDImage* d = wimg->GetImage(idx);
			if(d && d->Image_)
			{
				BlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
				cocos2d::Sprite* s = d->GetImage(dx + d->nx + m_nShiftX,dy + d->ny + m_nShiftY);
				s->setBlendFunc(cbl);
				layer->addChild(s);
			}
		}
	}
	return false;
}



TNpcActor::TNpcActor(void)
{
	m_nEffX = 0;
	m_nEffY = 0;
	m_bo248 = false;
	m_dwUseEffectTick = GetTickCount();
	m_boNpcWalkEffect = false;
	m_nNpcWalkEffectPx = GetTickCount();
	m_nNpcWalkEffectPy = GetTickCount();
	g_boNpcWalk = false;
}

TNpcActor::~TNpcActor(void)
{

}

void TNpcActor::Run()
{
	TActor::Run();
	if(m_wAppearance == 81 && g_boNpcWalk)
	{
		if(!m_boNpcWalkEffect)
		{
			if(m_nCurrentFrame == 4297)
			{
				m_boNpcWalkEffect =  true;
			}
		}
		if(m_nCurrentFrame >= m_nEndFrame)
		{
			g_boNpcWalk  = false;
			m_boNpcWalkEffect = false;
			SendMsg(SM_TURN, m_nCurrX, m_nCurrY, m_btDir, m_nFeature, m_nState, "", 0);
		}
	}

	int nEffectFrame = m_nEffectFrame;
	unsigned long dwEffectFrameTime;
	if(m_boUseEffect)
	{
		if(m_boUseMagic)
		{
			dwEffectFrameTime = int(m_dwEffectFrameTime / 3);
		}else
		{
			dwEffectFrameTime = m_dwEffectFrameTime;
		}
		if(GetTickCount() - m_dwEffectStartTime > dwEffectFrameTime)
		{
			m_dwEffectStartTime = GetTickCount();
			if(m_nEffectFrame < m_nEffectEnd)
			{
				m_nEffectFrame++;
			}else
			{
				if(m_bo248)
				{
					if( GetTickCount() > m_dwUseEffectTick )
					{
						m_boUseEffect = false;
						m_bo248 = false;
						m_dwUseEffectTick = GetTickCount();
					}
					m_nEffectFrame = m_nEffectStart;
				}else
				{
					m_nEffectFrame = m_nEffectStart;
				}
				m_dwEffectStartTime = GetTickCount();
			}
		}

	}

	if(nEffectFrame != m_nEffectFrame)
	{
		m_dwLoadSurfaceTime = GetTickCount();
		LoadSurface();
	}
}
void TNpcActor::CalcActorFrame()
{
	m_boUseMagic = false;
	m_nCurrentFrame = -1;
	m_nBodyOffset = GetNpcOffset(m_wAppearance);

	TMonsterAction* pm = GetRaceByPM(m_btRace, m_wAppearance);
	if(!pm)
	{
		return;
	}
	m_btDir = 0;

	m_nStartFrame = pm->ActStand.start;
	m_nEndFrame = m_nStartFrame + pm->ActStand.frame - 1;
	m_dwFrameTime = pm->ActStand.ftime;
	m_dwStartTime = GetTickCount();
	m_nDefFrameCount = pm->ActStand.frame;
	Shift(m_btDir, 0, 0, 1);
}
int TNpcActor::GetDefaultFrame(bool wmode)
{
	int cf;
	TMonsterAction* pm;
	pm = GetRaceByPM(m_btRace, m_wAppearance);
	if(!pm)
	{
		return 0;
	}
	m_btDir = m_btDir % 3;
	if(m_nCurrentDefFrame < 0)
	{
		cf = 0;
	}else if(m_nCurrentDefFrame >= pm->ActStand.frame)
	{
		cf = 0;
	}else
	{
		cf = m_nCurrentDefFrame;
	}
	//int s[] = {54,55,56,57,58,59,70,71,72,73,74,75,90,91,92,65,66,62,82,83,84,100};
	//for(int i = 0;i < sizeof(s) / sizeof(int);i++)
	//{
	//	if(m_wAppearance == s[i])
	//	{
	//		return pm->ActStand.start + cf;
	//	}
	//}
	return pm->ActStand.start + cf;
}

void TNpcActor::LoadSurface()
{
	m_BodySurface = GetNPCImageAndPXY(m_wAppearance, m_nCurrentFrame,
		m_nPx, m_nPy);
}
bool TNpcActor::DrawChr(int dx, int dy, bool blend,bool boFlag,cocos2d::Layer* layer,bool ismask)
{
	m_btDir = m_btDir % 3;
	if(GetTickCount() - m_dwLoadSurfaceTime > 60 * 1000)
	{
		m_dwLoadSurfaceTime = GetTickCount();
		LoadSurface();
	}
	if(m_BodySurface && m_BodySurface->Image_ )
	{
		int nx = dx + m_nPx + m_nShiftX;
		int ny = dy + m_nPy + m_nShiftY;
		//m_BodySurface->SetSpritePostion(nx,ny);

		if(m_wAppearance != 10000)
		{
			layer->addChild(m_BodySurface->GetImage(nx,ny));
			//绘制特效 待定
		}else
		{
			layer->addChild(m_BodySurface->GetImage(nx,ny));
		}
	}
	return true;
}
void TNpcActor::DrawEff(int dx,int dy)
{

}


TSkeletonOma::TSkeletonOma()
{
	ax = ay = 0;
}

TSkeletonOma::~TSkeletonOma()
{

}

void TSkeletonOma::CalcActorFrame()
{
	m_nCurrentFrame = -1;
	m_boReverseFrame = false;
	m_boUseEffect = false;

	m_nBodyOffset = GetOffset(m_wAppearance);
	TMonsterAction* pm = GetRaceByPM(m_btRace, m_wAppearance);
	if(!pm)return;
	switch(m_nCurrentAction)
	{
	case SM_TURN:
		{
			m_nStartFrame = pm->ActStand.start + m_btDir * (pm->ActStand.frame + pm->ActStand.skip);
			m_nEndFrame = m_nStartFrame + pm->ActStand.frame - 1;
			m_dwFrameTime = pm->ActStand.ftime;
			m_dwStartTime = GetTickCount();
			m_nDefFrameCount = pm->ActStand.frame;
			Shift(m_btDir, 0, 0, 1);
			break;
		}
	case  SM_WALK:
	case SM_BACKSTEP:
		{
			m_nStartFrame = pm->ActWalk.start + m_btDir * (pm->ActWalk.frame + pm->ActWalk.skip);
			m_nEndFrame = m_nStartFrame + pm->ActWalk.frame - 1;
			m_dwFrameTime = pm->ActWalk.ftime;
			m_dwStartTime = GetTickCount();
			m_nMaxTick = pm->ActWalk.usetick;
			m_nCurTick = 0;
			m_nMoveStep = 1;
			if( m_nCurrentAction == SM_WALK)
			{
				Shift(m_btDir, m_nMoveStep, 0, m_nEndFrame - m_nStartFrame + 1);
			}else
			{
				Shift(GetBack(m_btDir), m_nMoveStep, 0, m_nEndFrame - m_nStartFrame + 1);
			}

			break;
		}
	case SM_DIGUP:
		{
			if(m_btRace == 55)
			{
				m_nStartFrame = pm->ActCritical.start + m_btDir * (pm->ActCritical.frame + pm->ActCritical.skip);
				m_nEndFrame = m_nStartFrame + pm->ActCritical.frame - 1;
				m_dwFrameTime = pm->ActCritical.ftime;
				m_dwStartTime = GetTickCount();
				Shift(m_btDir, 0, 0, 1);
				return;
			}
			if(m_btRace == 54)
			{
				m_nStartFrame = pm->ActCritical.start + m_btDir * (pm->ActCritical.frame + pm->ActCritical.skip);
				m_nEndFrame = m_nStartFrame + pm->ActCritical.frame - 1;
				m_dwFrameTime = pm->ActCritical.ftime;
				m_dwStartTime = GetTickCount();
				Shift(m_btDir, 0, 0, 1);
				return;
			}

			if(m_btRace == 23)
			{
				m_nStartFrame = pm->ActDeath.start;
			}else
			{
				m_nStartFrame = pm->ActDeath.start + m_btDir 
					* (pm->ActDeath.frame + pm->ActDeath.skip);
			}
			m_nEndFrame = m_nStartFrame + pm->ActDeath.frame - 1;
			m_dwFrameTime = pm->ActDeath.ftime;
			m_dwStartTime = GetTickCount();
			Shift(m_btDir, 0, 0, 1);
			break;
		}
	case SM_DIGDOWN:
		{
			if(m_btRace == 55)
			{
				m_nStartFrame = pm->ActCritical.start + m_btDir * (pm->ActCritical.frame + pm->ActCritical.skip);
				m_nEndFrame = m_nStartFrame + pm->ActCritical.frame - 1;
				m_dwFrameTime = pm->ActCritical.ftime;
				m_dwStartTime = GetTickCount();
				m_boReverseFrame = true;
				Shift(m_btDir, 0, 0, 1);
			}
			break;
		}
	case  SM_HIT:
	case SM_FLYAXE:
	case SM_LIGHTING:
		{
			if( m_nCurrentAction == SM_FLYAXE && m_wAppearance == 160)//守卫狮子)
			{
				m_nStartFrame = pm->ActSpell.start + m_btDir * (pm->ActSpell.frame + pm->ActSpell.skip);
				m_nEndFrame = m_nStartFrame + pm->ActSpell.frame - 1;
				m_dwFrameTime = pm->ActSpell.ftime;
				m_dwStartTime = GetTickCount();
				return;
			}

			m_nStartFrame = pm->ActAttack.start + m_btDir * (pm->ActAttack.frame + pm->ActAttack.skip);
			m_nEndFrame = m_nStartFrame + pm->ActAttack.frame - 1;
			m_dwFrameTime = pm->ActAttack.ftime;
			m_dwStartTime = GetTickCount();
			m_dwWarModeTime = GetTickCount();
			if( m_btRace == 16 || m_btRace == 54)
			{
				m_boUseEffect = true;
			}
			Shift(m_btDir, 0, 0, 1);
			break;
		}
	case SM_STRUCK:
		{
			m_nStartFrame = pm->ActStruck.start + m_btDir * (pm->ActStruck.frame + pm->ActStruck.skip);
			m_nEndFrame = m_nStartFrame + pm->ActStruck.frame - 1;
			m_dwFrameTime = m_dwStruckFrameTime;
			m_dwStartTime = GetTickCount();
			m_nEffStruckFrame = 0;
			break;
		}
	case SM_DEATH:
		{
			m_nStartFrame = pm->ActDie.start + m_btDir * (pm->ActDie.frame + pm->ActDie.skip);
			m_nEndFrame = m_nStartFrame + pm->ActDie.frame - 1;
			m_nStartFrame = m_nEndFrame;
			m_dwFrameTime = pm->ActDie.ftime;
			m_dwStartTime = GetTickCount();
			break;
		}
	case SM_NOWDEATH:
		{
			m_nStartFrame = pm->ActDie.start + m_btDir * (pm->ActDie.frame + pm->ActDie.skip);
			m_nEndFrame = m_nStartFrame + pm->ActDie.frame - 1;
			m_dwFrameTime = pm->ActDie.ftime;
			m_dwStartTime = GetTickCount();
			if( m_btRace != 22)
			{
				m_boUseEffect = true;
			}
			break;
		}
	case SM_SKELETON:
		{
			m_nStartFrame = pm->ActDeath.start;
			m_nEndFrame = m_nStartFrame + pm->ActDeath.frame - 1;
			m_dwFrameTime = pm->ActDeath.ftime;
			m_dwStartTime = GetTickCount();
			break;
		}
	case SM_ALIVE:
		{
			m_nStartFrame = pm->ActDeath.start + m_btDir * (pm->ActDeath.frame + pm->ActDeath.skip);
			m_nEndFrame = m_nStartFrame + pm->ActDeath.frame - 1;
			m_dwFrameTime = pm->ActDeath.ftime;
			m_dwStartTime = GetTickCount();
			break;
		}
	case SM_MONSPELLEFF:
		{
			m_nCurrentAction = 0;
			break;
		}
	case SM_MONSPELL:
		{
			switch(m_btSpellAct)
			{
			case 0:
				{
					m_nStartFrame = pm->ActStand.start + m_btDir * (pm->ActStand.frame + pm->ActStand.skip);
					m_nEndFrame = m_nStartFrame + pm->ActStand.frame - 1;
					m_dwFrameTime = pm->ActStand.ftime;
					break;
				}
			case 1:
				{
					m_nStartFrame = pm->ActAttack.start + m_btDir * (pm->ActAttack.frame + pm->ActAttack.skip);
					m_nEndFrame = m_nStartFrame + pm->ActAttack.frame - 1;
					m_dwFrameTime = pm->ActAttack.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 2:
				{
					m_nStartFrame = pm->ActAttack1.start + m_btDir * (pm->ActAttack1.frame + pm->ActAttack1.skip);
					m_nEndFrame = m_nStartFrame + pm->ActAttack1.frame - 1;
					m_dwFrameTime = pm->ActAttack1.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 3:
				{
					m_nStartFrame = pm->ActAttack2.start + m_btDir * (pm->ActAttack2.frame + pm->ActAttack2.skip);
					m_nEndFrame = m_nStartFrame + pm->ActAttack2.frame - 1;
					m_dwFrameTime = pm->ActAttack2.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 4:
				{
					m_nStartFrame = pm->ActAttack3.start + m_btDir * (pm->ActAttack3.frame + pm->ActAttack3.skip);
					m_nEndFrame = m_nStartFrame + pm->ActAttack3.frame - 1;
					m_dwFrameTime = pm->ActAttack3.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 5:
				{
					m_nStartFrame = pm->ActAttack4.start + m_btDir * (pm->ActAttack4.frame + pm->ActAttack4.skip);
					m_nEndFrame = m_nStartFrame + pm->ActAttack4.frame - 1;
					m_dwFrameTime = pm->ActAttack4.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 6:
				{
					m_nStartFrame = pm->ActAttack5.start + m_btDir * (pm->ActAttack5.frame + pm->ActAttack5.skip);
					m_nEndFrame = m_nStartFrame + pm->ActAttack5.frame - 1;
					m_dwFrameTime = pm->ActAttack5.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}
			case 7:
				{
					m_nStartFrame = pm->ActAttack6.start + m_btDir * (pm->ActAttack6.frame + pm->ActAttack6.skip);
					m_nEndFrame = m_nStartFrame + pm->ActAttack6.frame - 1;
					m_dwFrameTime = pm->ActAttack6.ftime;
					m_dwWarModeTime = GetTickCount();
					break;
				}

			}
			m_dwStartTime = GetTickCount();
			Shift(m_btDir, 0, 0, 1);
			break;
		}
	}
}

int TSkeletonOma::GetDefaultFrame(bool wmode)
{
	int Result = 0;
	TMonsterAction*	pm = GetRaceByPM(m_btRace, m_wAppearance);
	if(!pm)return Result;
	if(m_boDeath)
	{
		if(m_wAppearance == 30 || m_wAppearance == 31 || m_wAppearance == 32 || m_wAppearance == 33
			|| m_wAppearance == 34 || m_wAppearance == 151)
		{
			m_nDownDrawLevel = 1;
		}

		if(m_boSkeleton)
		{
			Result = pm->ActDeath.start;
		}else
		{
			Result = pm->ActDie.start + m_btDir * (pm->ActDie.frame + pm->ActDie.skip) 
				+ (pm->ActDie.frame - 1);
		}
	}else
	{
		int cf = 0;
		m_nDefFrameCount = pm->ActStand.frame;
		if( m_nCurrentDefFrame < 0 )
		{
			cf = 0;
		}else if(m_nCurrentDefFrame >= pm->ActStand.frame)
		{
			cf = 0;
		}else 
		{
			cf = m_nCurrentDefFrame;
		}

		Result = pm->ActStand.start + m_btDir * (pm->ActStand.frame + pm->ActStand.skip) + cf;
	}

	return Result;
}

void TSkeletonOma::LoadSurface()
{
	TActor::LoadSurface();
}

void TSkeletonOma::Run()
{
	int prv;
	unsigned long  m_dwFrameTimetime;
	bool bofly;
	if (m_nCurrentAction == SM_WALK || m_nCurrentAction == SM_BACKSTEP ||
		m_nCurrentAction == SM_RUN || m_nCurrentAction == SM_HORSERUN)
	{
		return;
	}
	m_boMsgMuch = false;
	if( m_MsgList.size() >= 2 )
	{
		m_boMsgMuch = true;
	}

	RunActSound(m_nCurrentFrame - m_nStartFrame);
	RunFrameAction(m_nCurrentFrame - m_nStartFrame);
	prv = m_nCurrentFrame;
	if(m_nCurrentAction != 0)
	{
		if(m_nCurrentFrame < m_nStartFrame || m_nCurrentFrame > m_nEndFrame)
		{
			m_nCurrentFrame = m_nStartFrame;
		}
		if( m_boMsgMuch )
		{
			m_dwFrameTimetime = int(m_dwFrameTime * 2 / 3);
		}else
		{
			m_dwFrameTimetime = m_dwFrameTime;
		}
		if(GetTickCount() - m_dwStartTime > m_dwFrameTimetime)
		{
			if(m_nCurrentFrame < m_nEndFrame )
			{
				m_nCurrentFrame++;
				m_dwStartTime = GetTickCount();
			}else
			{
				m_boUseMagic = false;
				m_nCurrentAction = 0;
				m_boUseEffect = false;
			}
		}
		if(m_nCurrentAction == SM_FLYAXE && m_nCurrentFrame - m_nStartFrame == 5)
		{
			//meff := TFlyingFireBall(g_PlayScene.NewFlyObject(Self,
			// m_nCurrX,
			// m_nCurrY,
			// m_nTargetX,
			// m_nTargetY,
			// m_nTargetRecog,
			// mtFly));
		}
		if(m_nCurrentAction == SM_MONSPELL && m_nEndFrame - m_nCurrentFrame == 0)
		{
			if(m_CurMagic.ServerMagicCode != 0 )
			{
				TPlayScene::GetInstance()->NewMagic(this,m_CurMagic.ServerMagicCode,m_CurMagic.EffectNumber,
					m_nCurrX,m_nCurrY,m_CurMagic.targx,m_CurMagic.targy,m_CurMagic.target,m_CurMagic.EffectType,
					m_CurMagic.Recusion,m_CurMagic.anitime,bofly);
				m_CurMagic.ServerMagicCode = 0;
			}
		}
		m_nCurrentDefFrame = 0;
		m_dwDefFrameTime = GetTickCount();
	}else
	{
		if(GetTickCount() - m_dwSmoothMoveTime > 200)
		{
			if(GetTickCount() - m_dwDefFrameTime > 500)
			{
				m_dwDefFrameTime = GetTickCount();
				m_nCurrentDefFrame++;
				if( m_nCurrentDefFrame >= m_nDefFrameCount)
				{
					m_nCurrentDefFrame = 0;
				}
				TActor::DefaultMotion();
			}
		}
	}

	if(prv != m_nCurrentFrame)
	{
		m_dwLoadSurfaceTime = GetTickCount();
		LoadSurface();
	}


}

bool TSkeletonOma::DrawChr(int dx, int dy, bool blend,bool boFlag,cocos2d::Layer* layer,bool ismask)
{
	if(m_btDir < 0 && m_btDir > 7)
	{
		return false;
	}
	if(!m_BodySurface  && GetTickCount() - m_dwLoadSurfaceTime > 60 * 1000)
	{
		m_dwLoadSurfaceTime = GetTickCount();
		LoadSurface();
	}

	//待定
	if(m_BodySurface)
	{
		m_BodySurface->SetSpritePostion(dx + m_nPx + m_nShiftX,dy + m_nPy + m_nShiftY);
		layer->addChild(m_BodySurface->GetImage());
	}
	return true;
}

TCatMon::TCatMon()
{

}

TCatMon::~TCatMon()
{

}

bool TCatMon::DrawChr(int dx, int dy, bool blend,bool boFlag,cocos2d::Layer* layer,bool ismask)
{
//	CCLOG("action: %d",m_nCurrentAction);

	if(m_btDir < 0 && m_btDir > 7)
	{
		return false;
	}
	if(!m_BodySurface  && GetTickCount() - m_dwLoadSurfaceTime > 60 * 1000)
	{
		m_dwLoadSurfaceTime = GetTickCount();
		LoadSurface();
	}

	//待定
	if(m_BodySurface && m_BodySurface->Image_)
	{
		int nx= dx + m_nPx + m_nShiftX;
		int ny = dy + m_nPy + m_nShiftY;
		cocos2d::Sprite* img = m_BodySurface->GetImage(nx,ny);
		img->setOpacity(255);
		if(ismask)img->setOpacity(150);
		layer->addChild(img);
	}
	if(m_boDeath)
	{
		return true;
	}
	int n,nLib,nType,nStartframe,nFrame,idx;
	if(m_boFightEff)
	{
		n = m_nFightEffNum;
		nFrame = n % 100;
		n = n / 100;
		nStartframe = n % 10000;
		n = n / 10000;
		nLib = n % 100;
		nType = n / 100;                 //是否分方向

		idx = nStartframe + m_nFightEffFrame + m_btDir * nType;
		if( GetTickCount() - m_nFightEffTime > 120 )
		{
			m_nFightEffFrame++;
			if( m_nFightEffFrame >= nFrame )
			{
				m_nFightEffFrame = 0;
				m_nFightEffTime = GetTickCount();
			}
		}
	}
	if(m_boUseMagic)
	{
		if( m_btMagicNum > 10000)
		{
			n = m_btMagicNum;
			nFrame = n % 100;              //图片张数
			n = n / 100;
			nStartframe = n % 10000;       //图片起始位置
			n = n / 10000;
			nType = n % 10;                //魔法效果ID
			nLib = n / 10;                 //库
		}
		idx = nStartframe + m_nCurrentFrame - m_nStartFrame + m_btDir * nFrame;
	}
	return true;
}


void TPlant::LoadSurface()
{
	if(m_boDeath) //植物，死亡只有一帧
	{
		m_BodySurface = GetMonImage(m_wAppearance, PLANT.ActDeath.start, m_nPx, m_nPy);
	}else
	{
		m_BodySurface = GetMonImage(m_wAppearance, m_nCurrentFrame % 10, m_nPx, m_nPy);
	}
}



void TMine::LoadSurface()
{
	if(m_boDeath)//植物，死亡只有一帧
	{
		m_BodySurface = GetMonImage(m_wAppearance, MINEDEF.ActDeath.start, m_nPx, m_nPy);
	}else
	{
		 m_BodySurface = GetMonImage(m_wAppearance, m_nCurrentFrame % MINEDEF.ActStand.frame, m_nPx, m_nPy);
	}
}

void TArcherMon::Run()
{
	if(m_nCurrentAction == SM_WALK || m_nCurrentAction == SM_BACKSTEP
		|| m_nCurrentAction == SM_RUN)
	{
		return;
	}
	m_boMsgMuch = false;
	if(m_MsgList.size() >= 2)
	{
		m_boMsgMuch = true;
	}
	RunActSound(m_nCurrentFrame - m_nStartFrame);
	RunFrameAction(m_nCurrentFrame - m_nStartFrame);
	int prv = m_nCurrentFrame;
	unsigned long m_dwFrameTimetime = 0;
	if(m_nCurrentAction != 0)
	{
		if(m_nCurrentFrame < m_nStartFrame || m_nCurrentFrame > m_nEndFrame)
		{
			m_nCurrentFrame = m_nStartFrame;
		}
		if(m_boMsgMuch)
		{
			m_dwFrameTimetime = int(m_dwFrameTime * 2 / 3);
		}else
		{
			m_dwFrameTimetime = m_dwFrameTime;
		}

		if(GetTickCount() - m_dwStartTime > m_dwFrameTimetime)
		{
			if(m_nCurrentFrame < m_nEndFrame)
			{
				m_nCurrentFrame ++;
				m_dwStartTime = GetTickCount();
			}else
			{
				m_nCurrentAction = 0;
				m_boUseEffect = false;
			}

			if(m_nCurrentAction == SM_FLYAXE &&
				m_nCurrentFrame - m_nStartFrame == 4)
			{
				//待定---
			}

			m_nCurrentDefFrame = 0;
			m_dwDefFrameTime = GetTickCount();

		}
	}else
	{
		if( GetTickCount() - m_dwSmoothMoveTime > 200)
		{
			if( GetTickCount() - m_dwDefFrameTime > 500)
			{
				m_dwDefFrameTime = GetTickCount();
				m_nCurrentDefFrame++;
				if(m_nCurrentDefFrame >= m_nDefFrameCount)
				{
					m_nCurrentDefFrame = 0;
				}
			}
			DefaultMotion();
		}
	}
	if(prv != m_nCurrentFrame)
	{
		m_dwLoadSurfaceTime =  GetTickCount();
		LoadSurface();
	}
}