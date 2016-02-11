#include "GuaJiHelper.h"
#include "Actor.h"
#include "MShare.h"
#include "FrmMain.h"
#include "PlayScene.h"
#include "./Net/NetClient.h"
#include "./Net/NetSendMsg.h"
#include "./Common/IconvString.h"
#include "MapUnit.h"
static TGuaJiHelper* m_Instance = nullptr;

TGuaJiHelper::TGuaJiHelper(void)
{
	m_TargetCret = nullptr;
	m_nTargetX = -1; 
	m_nTargetY = -1;
	m_KillMonName = "";
	boAvoid = false;
	FPathPoisonIndex = 0;
	FStarted = false;
	FRunTick = GetTickCount();
	FAttackTick = GetTickCount();
	SingldAttack = nullptr;
	GroupAttack = nullptr;
}


TGuaJiHelper::~TGuaJiHelper(void)
{
}

TGuaJiHelper* TGuaJiHelper::GetInstance()
{
	if(!m_Instance)
	{
		m_Instance = new TGuaJiHelper;
	}
	return m_Instance;
}

void TGuaJiHelper::Started(bool val)
{
	SetStarted(val);
}

void TGuaJiHelper::Start()
{
	if(g_MySelf && !g_MySelf->m_boDeath && !FStarted)
	{
		FStarted = true;
		FRunTick =  GetTickCount();
	}

}
void TGuaJiHelper::Stop()
{
	if(FStarted)
	{
		FStarted = false;
		m_TargetCret = nullptr;
	}
}
void TGuaJiHelper::Run()
{
	TClientMagic* pm;
	int nTargetX,nTargetY;

	if(FStarted)
	{
		if(!g_MySelf)Stop();
		if(g_MySelf && g_MySelf->m_boDeath)
		{
			Stop();
		}
	}
	if(FStarted && GetTickCount() - FRunTick > 200)
	{
		FRunTick = GetTickCount();
		if(!TPlayScene::GetInstance()->IsValidActor(m_TargetCret)) m_TargetCret = nullptr;
		if(m_TargetCret && (m_TargetCret->m_boDeath || m_TargetCret->m_Abil.HP == 0))
		{
			if(g_nAutoPickUpX < 0)
			{
				g_nAutoPickUpX = m_TargetCret->m_nCurrX;
				g_nAutoPickupY = m_TargetCret->m_nCurrY;          
				g_nAutoPickPos = 12;
				m_TargetCret = nullptr;
				return;
			}
			m_TargetCret = nullptr;
		}
		if(m_TargetCret)
		{
			//不小心锁定了宝宝和马，取消，不攻击宝宝
			if((int)m_TargetCret->m_sUserName.find("(") >= 0)
			{
				m_TargetCret = nullptr;
			}
		}
		//没有合适目标 搜索新目标
		if(!m_TargetCret)SearchTarget();
		//有目标
		if(m_TargetCret)
		{
			pm = nullptr;
			//法师和道士，可以使用魔法攻击  远距离攻击
			if(g_MySelf->m_btJob > 0 && m_TargetCret->m_btRace != RC_MINE 
				&& m_TargetCret->m_btRace != RC_PLANT)
			{
				//群攻技能
				if(GetRangeTargetCount(m_TargetCret->m_nCurrX,m_TargetCret->m_nCurrY,4) > 1)
				{
					pm = GroupAttack;
				}
				//单体攻击技能
				if(!pm && SingldAttack)pm = SingldAttack;

				if(pm && g_MySelf->m_Abil.MP > 0)
				{
					g_TargetCret = nullptr;
					g_FocusCret = m_TargetCret;
					TPlayScene::GetInstance()->ScreenXYfromMCXY(m_TargetCret->m_nCurrX,m_TargetCret->m_nCurrY,
						g_nMouseX,g_nMouseY);

					if(GetTickCount() - FAttackTick > 1000 && FrmMain::GetInstance()->ActionKey == 0)
					{
						FAttackTick = GetTickCount();
					}
					FrmMain::GetInstance()->UseMagic(g_nMouseX,g_nMouseY,pm);
					if(boAvoid)//是否躲避
					{
						if(GetRangeTargetCount(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, 2) > 0 )
						{
							Avoid();
							return;
						}
					}

				}else
				{
					g_TargetCret = m_TargetCret;
				}
			}else //战士使用物理攻击
			{
				g_TargetCret = m_TargetCret;
			}
			// 20121110 为了避免挂机时遇到残影怪物造成卡住，这里判断
			//如果怪物名字查询已经2分钟以前，就重新查询名字，以便更新怪物。
			if(GetTickCount() - m_TargetCret->m_dwSendQueryUserNameTime > 120 * 1000)
			{
				m_TargetCret->m_dwSendQueryUserNameTime = GetTickCount();
				VD_Net::CNetClient::GetInstance()->GetSendMsg()->SendQueryUserName(m_TargetCret->m_nRecogId,m_TargetCret->m_nCurrX,
					m_TargetCret->m_nCurrY);  //获取对象名字

			}

		}else
		{
			if(g_nTargetX > 0 && g_nTargetY > 0)
			{
				if(abs(g_MySelf->m_nCurrX - g_nTargetX) >= 1 || abs(g_MySelf->m_nCurrY - g_nTargetY) >= 1)
				{
					GetAutoWalkXY(nTargetX, nTargetY);
					if(abs(g_MySelf->m_nCurrX - nTargetX) >=2 || abs(g_MySelf->m_nCurrY - nTargetY) >= 2)
					{
						g_ChrAction = caRun;
					}else
					{
						g_ChrAction = caWalk;
					}
					g_nTargetX = nTargetX;
					g_nTargetY = nTargetY;
					m_nTargetX = nTargetX;
					m_nTargetY = nTargetY;
				}
			}else
			{
				GetAutoWalkXY(nTargetX, nTargetY);
				if (abs(g_MySelf->m_nCurrX - nTargetX) >= 2 || abs(g_MySelf->m_nCurrY - nTargetY) >= 2)
				{
					g_ChrAction = caRun;
				}else g_ChrAction = caWalk;
				g_nTargetX = nTargetX;
				g_nTargetY = nTargetY;
				m_nTargetX = nTargetX;
				m_nTargetY = nTargetY;
			}
		}
	}

}

bool TGuaJiHelper::CanRunEx(int sx,int sy,int ex,int ey,bool flag)
{
	bool result = false;
	int nDir,rx,ry;
	nDir = GetNextDirection(sx, sy, ex, ey);
	rx = sx;
	ry = sy;
	GetNextPosXY(nDir, rx, ry);
	if(VDMap::GetInstance()->CanMove(rx,ry) && VDMap::GetInstance()->CanMove(ex,ey))
	{
		result = true;
	}
	if(flag)
	{
		if(CanWalkEx(rx, ry, flag) && CanWalkEx(ex, ey, flag) )
		{
			result = true;
		}
	}
	return result;
}
bool TGuaJiHelper::CanWalkEx(int nTargetX,int nTargetY,bool flag)
{
	bool Result = VDMap::GetInstance()->CanMove(nTargetX, nTargetY);
	if(flag)
	{
		Result = !TPlayScene::GetInstance()->CrashMan(nTargetX,nTargetY);
	}
	return Result;
}
bool TGuaJiHelper::CanWalk(int nTargetX,int nTargetY,bool flag)
{
	int nDir,nX,nY,nX1,nY1;
	bool Result= true;
	nDir = GetNextDirection(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, nTargetX, nTargetY);
	nX = g_MySelf->m_nCurrX;
	nY = g_MySelf->m_nCurrY;
	nX1 = nTargetX;
	nY1 = nTargetY;

	if(abs(nX - nX1) >= 2 || abs(nY - nY1) >= 2)
	{
		while(true)
		{
			if(nDir != GetNextDirection(nX, nY, nTargetX, nTargetY)) break;

			if(abs(nX - nX1) >= 2 || abs(nY - nY1)>=2)
			{
				if(GetNextPosition(nX, nY, nDir, 2, nX1, nY1))
				{
					if(CanRunEx(nX, nY, nX1, nY1, flag))
					{
						nX = nX1;
						nY = nY1;
						nX1 = nTargetX;
						nY1 = nTargetY;
					}else
					{
						Result = false;
						break;
					}
				}else
				{
					Result = false;
					break;
				}
			}else
			{
				if(GetNextPosition(nX, nY, nDir, 1, nX1, nY1) )
				{
					if( CanWalkEx(nX1, nY1, flag))
					{
						nX = nX1;
						nY = nY1;
						nX1 = nTargetX;
						nY1 = nTargetY;
					}else
					{
						Result = false;
						break;
					}
				}else
				{
					Result = false;
					break;
				}
			}
		}
	}else
	{
		Result = CanWalkEx(nX1, nY1, flag);
	}
	return Result;
}
void TGuaJiHelper::SetStarted(bool Value)
{
	if(FStarted != Value)
	{
		if(FStarted)
		{
			Stop();
		}else
		{
			Start();
			FrmMain::GetInstance()->StopAutoRun();
		}
	}

}
void TGuaJiHelper::Avoid()
{

	TMapWalkXY* MapWalkXY;
	TMapWalkXY RunCount[8];
	TMapWalkXY WalkCount[8];
	int n10,i,nX,nY;
	for(n10 = 0;n10 < 7;n10++)
	{
		if(GetNextPosition(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, n10, 2, nX, nY))
		{
			if(TPlayScene::GetInstance()->CanRun(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, nX, nY))
			{
				RunCount[n10].boWalk = true;
				RunCount[n10].nMonCount = GetRangeTargetCount(nX, nY, 2);
				RunCount[n10].nX = nX;
				RunCount[n10].nY = nY;
			}
		}
	}
	MapWalkXY = nullptr;
	n10 = 9999;
	for(i = 0;i < 7;i++)
	{
		if(RunCount[i].boWalk)
		{
			if(RunCount[i].nMonCount < n10)
			{
				n10 = RunCount[i].nMonCount;
				MapWalkXY = &RunCount[i];
			}
		}
	}
	if(MapWalkXY)
	{
		g_ChrAction = caRun;
		g_nTargetX = MapWalkXY->nX;
		g_nTargetY = MapWalkXY->nY;
		return;
	}


	//--------------------
	for(n10 = 0;n10 < 7;n10++)
	{
		if(GetNextPosition(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, n10, 1, nX, nY))
		{
			if(TPlayScene::GetInstance()->CanRun(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, nX, nY))
			{
				WalkCount[n10].boWalk = true;
				WalkCount[n10].nMonCount = GetRangeTargetCount(nX, nY, 2);
				WalkCount[n10].nX = nX;
				WalkCount[n10].nY = nY;
			}
		}
	}
	MapWalkXY = nullptr;
	n10 = 9999;
	for(i = 0;i < 7;i++)
	{
		if(WalkCount[i].boWalk)
		{
			if(WalkCount[i].nMonCount < n10)
			{
				n10 = WalkCount[i].nMonCount;
				MapWalkXY = &WalkCount[i];
			}
		}
	}
	if(MapWalkXY)
	{
		g_ChrAction = caWalk;
		g_nTargetX = MapWalkXY->nX;
		g_nTargetY = MapWalkXY->nY;
		return;
	}
}
bool TGuaJiHelper::UseMagic()
{
	TClientMagic* pm = nullptr;
	bool result = false;
	if(g_MySelf->m_btJob > 0)
	{

	}
	return pm != nullptr;
}
int TGuaJiHelper::GetNearTargetCount()
{
	int n10,nX,nY;
	TActor* Actor;
	int result = 0;
	for(n10 = 0;n10 < 7;n10 ++)
	{
		if( GetNextPosition(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, n10, 1, nX, nY))
		{
			Actor = TPlayScene::GetInstance()->FindActorXY(nX, nY);
			if(Actor && !Actor->m_boDeath &&
				Actor != g_MySelf && Actor->m_btRace > RCC_USERHUMAN &&
				Actor->m_btRace != RCC_GUARD && Actor->m_btRace != RC_ARCHERGUARD &&
				Actor->m_btRace != 52 && Actor->m_btRace != 81 &&
				Actor->m_btRace != 12 && Actor->m_btRace != RCC_MERCHANT)
				//(Pos('(', Actor.m_sUserName) = 0
			{
				result++;
			}
		}
	}
	return 0;
}
int TGuaJiHelper::GetRangeTargetCount(int nx,int ny,int nRange)
{
	return TPlayScene::GetInstance()->FindTargetXYCount(nx, ny, nRange);
}
void TGuaJiHelper::SearchTarget()
{

	TActor* Actor,*Actor18;
	int nC,n10,tDir,dx,dy,n;
	bool bb;
	Actor18 = nullptr;
	std::string sUserName;
	n10 = 9999;
	for(int i = 0;i < (int)TPlayScene::GetInstance()->m_ActorList.size();i++)
	{
		Actor = TPlayScene::GetInstance()->m_ActorList[i];
		sUserName = Actor->m_sUserName;
		std::string sgbk = UTF8ToGBK_string(sUserName.c_str(),sUserName.length());
		//目标已死，并且相对自己位置大于7格 下一个
		if(Actor->m_boDeath || Actor->m_Abil.HP == 0) continue;	//死了的
		if(abs(Actor->m_nCurrX - g_MySelf->m_nCurrX) > 6		//太远的
			|| abs(Actor->m_nCurrY - g_MySelf->m_nCurrY) > 6) continue;
		if(m_KillMonName.length() > 0 && m_KillMonName != "*" &&
			m_KillMonName != sgbk)continue;	//不是指定攻击对象名字
		if (Actor->m_btRace <= RCC_USERHUMAN) continue;     //人
		if (Actor->m_btRace == RCC_GUARD) continue;        //守卫
		if (Actor->m_btRace == RC_ARCHERGUARD)  continue;
		if (Actor->m_btRace == 52)  continue;
		if (Actor->m_btRace == 81)  continue;
		if (Actor->m_btRace == 12)  continue;
		if (Actor->m_btRace == RCC_MERCHANT)  continue;     //npc
		//--------
		if (Actor->m_boDeath)  continue; //死了的不攻击
		if (Actor == g_MySelf)  continue;        //自己不攻击

		if  ((int)sgbk.find("(") > -1)  continue;//宝宝不打
		//找到目标相对自己的方向，然后找到到达目标的最近坐标
		tDir = GetNextDirection(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, Actor->m_nCurrX, Actor->m_nCurrY);
		// 20120628新增，检测和目标之间是否有阻挡物
		bb = true;
		n = 0;
		while(true)
		{
			if(n > 7)break;
			GetNextPosition(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, tDir, 1, dx, dy);
			if(!TPlayScene::GetInstance()->CanWalkEx(dx,dy))
			{
				bb = false;
				break;
			}
			if (abs(Actor->m_nCurrX - dx) <= 1 && abs(Actor->m_nCurrY - dy) <= 1)break;
			n++;
		}
		if(!bb) continue;

		if(this->CanWalk(dx,dy,!UseMagic()))
		{
			nC = abs(g_MySelf->m_nCurrX - Actor->m_nCurrX) + abs(g_MySelf->m_nCurrY - Actor->m_nCurrY);
			if(nC < n10) ////找到最近的那个作为目标
			{
				n10 = nC;
				Actor18 = Actor;
			}
		}
	}
	if(Actor18)
	{
		m_TargetCret = Actor18;
	}

}

//给摇杆用的接口
TActor* TGuaJiHelper::SearchTargetEx()
{

	TActor* Actor,*Actor18;
	int nC,n10,tDir,dx,dy,n;
	bool bb;
	Actor18 = nullptr;
	std::string sUserName;
	n10 = 9999;
	for(int i = 0;i < (int)TPlayScene::GetInstance()->m_ActorList.size();i++)
	{
		Actor = TPlayScene::GetInstance()->m_ActorList[i];
		sUserName = Actor->m_sUserName;
		std::string sgbk = UTF8ToGBK_string(sUserName.c_str(),sUserName.length());
		//目标已死，并且相对自己位置大于7格 下一个
		if(Actor->m_boDeath || Actor->m_Abil.HP == 0) continue;	//死了的
		if(abs(Actor->m_nCurrX - g_MySelf->m_nCurrX) > 15		//太远的
			|| abs(Actor->m_nCurrY - g_MySelf->m_nCurrY) > 15) continue;
		//if(m_KillMonName.length() > 0 && m_KillMonName != "*" &&
		//m_KillMonName != sUserName)continue;	//不是指定攻击对象名字
		if (Actor->m_btRace <= RCC_USERHUMAN) continue;     //人
		if (Actor->m_btRace == RCC_GUARD) continue;        //守卫
		if (Actor->m_btRace == RC_ARCHERGUARD)  continue;
		if (Actor->m_btRace == 52)  continue;
		if (Actor->m_btRace == 81)  continue;
		if (Actor->m_btRace == 12)  continue;
		if (Actor->m_btRace == RCC_MERCHANT)  continue;     //npc
		//--------
		if (Actor->m_boDeath)  continue; //死了的不攻击
		if (Actor == g_MySelf)  continue;        //自己不攻击

		if  (sUserName.find("(") > -1)  continue;//宝宝不打
		//找到目标相对自己的方向，然后找到到达目标的最近坐标
		tDir = GetNextDirection(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, Actor->m_nCurrX, Actor->m_nCurrY);
		// 20120628新增，检测和目标之间是否有阻挡物
		bb = true;
		n = 0;
		while(true)
		{
			if(n > 7)break;
			GetNextPosition(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, tDir, 1, dx, dy);
			if(!TPlayScene::GetInstance()->CanWalkEx(dx,dy))
			{
				bb = false;
				break;
			}
			if (abs(Actor->m_nCurrX - dx) <= 1 && abs(Actor->m_nCurrY - dy) <= 1)break;
			n++;
		}
		if(!bb) continue;

		if(this->CanWalk(dx,dy,!UseMagic()))
		{
			nC = abs(g_MySelf->m_nCurrX - Actor->m_nCurrX) + abs(g_MySelf->m_nCurrY - Actor->m_nCurrY);
			if(nC < n10) ////找到最近的那个作为目标
			{
				n10 = nC;
				Actor18 = Actor;
			}
		}
	}

	return Actor18;

}
void TGuaJiHelper::GetAutoWalkXY(int &nTargetX,int &nTargetY)
{
	int nStep;
	unsigned char btDir;
	int nCount;
	nTargetX = g_MySelf->m_nCurrX;
	nTargetY = g_MySelf->m_nCurrY;
	for(nStep = 2;nStep > 1;nStep--)
	{
		if(GetNextPosition(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, g_MySelf->m_btDir, nStep, nTargetX, nTargetY) )
		{
			if(GetRandXY(nTargetX,m_nTargetY))
			{
				return;
			}
		}
	}
	nCount= 0;
	btDir = g_MySelf->m_btDir;
	while(true)
	{
		nCount++;
		btDir = this->GetNextDir(btDir);
		for(nStep = 2;nStep > 1;nStep--)
		{
			if(GetNextPosition(g_MySelf->m_nCurrX, g_MySelf->m_nCurrY, g_MySelf->m_btDir, nStep, nTargetX, nTargetY) )
			{
				if(GetRandXY(nTargetX,m_nTargetY))
				{
					return;
				}
			}
		}
		if(nCount >= 8)break;
	}
} 
bool TGuaJiHelper::GetRandXY(int &nx,int &ny)
{
	bool Result = false;

	if(abs(g_MySelf->m_nCurrX - nx) >= 2 || abs(g_MySelf->m_nCurrY - ny) >= 2)
	{
		if(TPlayScene::GetInstance()->CanRun(g_MySelf->m_nCurrX,g_MySelf->m_nCurrY,nx,ny))
		{
			Result = nx != g_MySelf->m_nCurrX || ny != g_MySelf->m_nCurrY;
		}
	}else
	{
		if(TPlayScene::GetInstance()->CanWalkEx(nx,ny))
		{
			Result = nx != g_MySelf->m_nCurrX || ny != g_MySelf->m_nCurrY;
		}
	}
	return Result;
}
unsigned char TGuaJiHelper::GetNextDir(unsigned char btDir)
{
	unsigned char Result;
	switch(btDir)
	{
	case DR_UP: Result = DR_UPRIGHT;
	case DR_UPRIGHT: Result = DR_RIGHT;
	case DR_RIGHT: Result = DR_DOWNRIGHT;
	case DR_DOWNRIGHT: Result = DR_DOWN;
	case DR_DOWN: Result = DR_DOWNLEFT;
	case DR_DOWNLEFT: Result = DR_LEFT;
	case DR_LEFT: Result = DR_UPLEFT;
	case DR_UPLEFT: Result = DR_UP;
	}
	return Result;
}
bool TGuaJiHelper::GetNextPosition(int sx,int sy,int nDir,int nFlag,int &snx,int &sny)
{
	snx = sx;
	sny = sy;
	switch(nDir)
	{
	case DR_UP: if(sny > nFlag - 1) sny -= nFlag;
	case DR_DOWN: if (sny < (VDMap::GetInstance()->Header.Height - nFlag - 2/*{最下面会卡住}*/)) sny += nFlag;
	case DR_LEFT: if( snx > nFlag - 1) snx -= nFlag;
	case DR_RIGHT: if( snx < (VDMap::GetInstance()->Header.Width - nFlag - 2/*{最下面会卡住}*/)) snx += nFlag;
	case DR_UPLEFT: 
		{
			if(snx > nFlag - 1 && sny > nFlag - 1)
			{
				snx -= nFlag;
				sny -= nFlag;
			}
		}
	case DR_UPRIGHT: 
		{
			if (snx > nFlag - 1 && sny < (VDMap::GetInstance()->Header.Height - nFlag - 2/*{最下面会卡住}*/))
			{
				snx += nFlag;
				sny += nFlag;
			}
		}
	case DR_DOWNLEFT: 
		{
			if (snx < VDMap::GetInstance()->Header.Width - nFlag && sny > nFlag - 1)
			{
				snx -= nFlag;
				sny += nFlag;
			}
		}
	case DR_DOWNRIGHT: 
		{
			if (snx < (VDMap::GetInstance()->Header.Width - nFlag) && 
				sny < (VDMap::GetInstance()->Header.Height - nFlag - 2/*{最下面会卡住}*/)) 
			{
				snx += nFlag;
				sny += nFlag;
			}
		}
	}
	if (snx == sx && sny == sy) return false;
	return true;
}

void TGuaJiHelper::SelectMagicLise()
{
	TClientMagic* pcm;
	for(int i = 0;i < (int)g_MagicList.size();i++)
	{
		pcm = g_MagicList[i];
		if(pcm->Def.wMagicId == 1 ||
			pcm->Def.wMagicId == 11 ||
			pcm->Def.wMagicId == 13)
		{
			SingldAttack = pcm;
		}
		if(pcm->Def.wMagicId == 23)
		{
			GroupAttack = pcm;
		}
	}
	if(!GroupAttack)
	{
		GroupAttack = SingldAttack;
	}
}