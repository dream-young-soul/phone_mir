#include "MagicEff.h"

#include "GameStruct.h"
#include "MShare.h"
#include "./Common/SoundUtil.h"
#include "PlayScene.h"
#include "VDImage.h"
#include "./Common/VDImageDatas.h"
#ifdef WIN32
#include <windows.h>
#endif


const int MG_READY   = 10;
const int MG_FLY            = 6;
const int MG_EXPLOSION      = 10;
const int READYTIME         = 120;
const int EXPLOSIONTIME     = 100;
const int FLYBASE           = 10;
const int EXPLOSIONBASE     = 170;


const int FLYOMAAXEBASE     = 447;
const int THORNBASE         = 2967;
const int ARCHERBASE        = 2607;
const int ARCHERBASE2       = 272;
//const int MAXMAGIC     = 10;
const int FLYFORSEC         = 500;
const int FIREGUNFRAME      = 30;
const int ICEGUNFRAME       = 20;

const int MAXHITEFFECT      = 10;
const int HitEffectBase[10] = {1350,320,230,1470,3390,40,220,740,10,310};

TMagicEff::TMagicEff()
{
	m_boActive = false;
	ServerMagicId = 0;
	MagOwner = nullptr;
	TargetActor = nullptr;
	ImgLib = nullptr; 
	ImgLib1 = nullptr; 
	useImgLib1 = false;
	EffectBase = 0;
	temp = 0;
	MagExplosionBase = 0;
	py = 0;
	rx = 0;
	ry = 0;
	Dir16 = 0;
	OldDir16 = 0;
	Dir8 = 0;
	use16dir = false;
	targetx = 0;
	targety = 0;
	TargetRx = 0;
	TargetRy = 0;
	FlyX = 0;
	FlyY = 0;
	OldFlyX = 0;
	OldFlyY = 0;
	FlyXf = 0;
	FlyYf = 0;
	Repetition = false;
	FixedEffect = false;
	MagicType = 0;
	NextEffect = nullptr;
	ExplosionFrame = 0;
	NextFrameTime = GetTickCount();
	Light = 0;
	n7C = 0;
	bt80 = 0;
	bt81 = 0;
	start = 0;
	curframe = 0;
	frame = 0;
	bo8 = false; 

	m_dwFrameTime = GetTickCount();
	m_dwStartTime = GetTickCount();
	repeattime = GetTickCount();
	steptime = GetTickCount();
	fireX = 0;
	fireY = 0;
	firedisX = 0;
	firedisY = 0;
	newfiredisX = 0;
	newfiredisY = 0;
	FireMyselfX = 0;
	FireMyselfY = 0;
	prevdisx = 0;
	prevdisy = 0;
	m_nOldx = 0;
	m_nOldY = 0;
	nCount = 0;
	Lzidx = 0;
	boLz = false;
}
void TMagicEff::Create(int id,int effnum,int sx,int sy,int tx,int ty,TMagicType mtype,
	bool Recusion,int anitime)
{
	ImgLib = nullptr;
	use16dir = false;
	useImgLib1 = false;
	switch(mtype)
	{
	case TMagicType::mtFly:
	case TMagicType::mtBujaukGroundEffect:
	case TMagicType::mtExploBujauk:
		{
			start = 0;
			frame = 6;
			curframe = start;
			FixedEffect = false;
			Repetition = Recusion;
			ExplosionFrame = 10;
			if(id == 38)
			{
				frame = 10;
			}
			if(id == 39)
			{
				frame = 4;
				ExplosionFrame = 8;
			}
			if(id == 63)
			{
				MagExplosionBase = 780;
				ExplosionFrame = 36;
			}
			if(id - 81 - 3 < 0)
			{
				bt80 = 1;
				Repetition = true;
				if(id == 81)
				{
					if(g_MySelf->m_nCurrX >= 84)
					{
						EffectBase = 130;
					}else
					{
						EffectBase = 140;
					}
					bt81 = 1;
				}
				if(id == 82)
				{
					if(g_MySelf->m_nCurrX >= 78 &&
						g_MySelf->m_nCurrY >= 48)
					{
						EffectBase = 150;
					}else
					{
						EffectBase = 160;
					}
					bt81 = 2;
				}
				if(id == 83)
				{
					EffectBase = 180;
					bt81 = 3;
				}
				start = 0;
				frame = 10;
				MagExplosionBase = 190;
				ExplosionFrame = 10;
			}
			break;
		}
	case TMagicType::mt12:
		{
			start = 0;
			frame = 6;
			curframe = start;
			FixedEffect = false;
			Repetition = Recusion;
			ExplosionFrame = 1;
			break;
		}
	case TMagicType::mt13:
		{
			start = 0;
			frame = 20;
			curframe = start;
			FixedEffect = true;
			Repetition = false;
			ExplosionFrame = 20;
			break;
		}
	case mtExplosion:
	case mtThunder:
	case mtLightingThunder:
		{
			start = 0;
			frame = -1;
			ExplosionFrame = 10;
			curframe = start;
			FixedEffect = true;
			Repetition = false;
			if(id == 80)
			{
				bt80 = 2;
				switch(Random_Int(0,6))
				{
				case 0:
				case 3:
					{
						EffectBase = 230;
						break;
					}
				case 1:
				case 4:
					{
						EffectBase = 240;
						break;
					}
				case 2:
				case 5:
					{
						EffectBase = 250;
						break;
					}
				}
				Light = 4;
				ExplosionFrame = 5;
			}
			if(id == 70)
			{
				bt80 = 3;
				switch(Random_Int(0,3))
				{
				case 0:
					{
						EffectBase = 400;
						break;
					}
				case 1:
					{
						EffectBase = 410;
						break;
					}
				case 2:
					{
						EffectBase = 420;
						break;
					}
				}
				Light = 4;
				ExplosionFrame = 5;
			}
			if(id == 71)
			{
				bt80 = 3;
				ExplosionFrame = 20;
			}
			if(id == 72)
			{
				bt80 = 3;
				Light = 3;
				ExplosionFrame = 10;
			}
			if(id == 73)
			{
				bt80 = 3;
				Light = 5;
				ExplosionFrame = 20;
			}
			if(id == 74)
			{
				bt80 = 3;
				Light = 4;
				ExplosionFrame = 35;
			}
			if(id == 90)
			{
				MagExplosionBase = 350;
				ExplosionFrame = 30;
			}
			break;
		}
	case TMagicType::mt14:
		{
			start = 0;
			frame = -1;
			curframe = start;
			FixedEffect = true;
			Repetition = false;
			break;
		}
	case TMagicType::mtFlyAxe:
		{
			start = 0;
			frame = 3;
			curframe = start;
			FixedEffect = false;
			Repetition = Recusion;
			ExplosionFrame = 3;
			break;
		}
	case TMagicType::mtFlyArrow:
		{
			start = 0;
			frame = 1;
			curframe = start;
			FixedEffect = false;
			Repetition = Recusion;
			ExplosionFrame = 1;
			break;
		}
	case TMagicType::mt15:
		{
			start = 0;
			frame = 6;
			curframe = start;
			FixedEffect = false;
			Repetition = Recusion;
			ExplosionFrame = 2;
			break;
		}
	case TMagicType::mt16:
		{
			start = 0;
			frame = 1;
			curframe = start;
			FixedEffect = false;
			Repetition = Recusion;
			ExplosionFrame = 1;
			break;
		}
	}
	int n7c = 0;
	ServerMagicId = id;
	EffectBase = effnum;
	targetx = tx;
	targety = ty;
	if(bt80 == 1)
	{
		if(id == 81)
		{
			sx -= 14; sy += 20;
		}
		if(id == 81)
		{
			sx -= 70; sy -= 10;
		}
		if(id == 83)
		{
			sx -= 60; sy -= 70;
		}
		PlaySound_(8208);
	}
	int tax,tay;
	fireX = sx;
	fireY = sy;
	FlyX = sx;
	FlyY = sy;
	OldFlyX = sx;
	OldFlyY = sy;
	FlyXf = sx;
	FlyYf = sy;
	FireMyselfX = g_MySelf->m_nRx * UNITX + g_MySelf->m_nShiftX;
	FireMyselfY = g_MySelf->m_nRy * UNITY + g_MySelf->m_nShiftY;
	if( bt80 == 0 )
	{
		MagExplosionBase = EffectBase + EXPLOSIONBASE;
	}
	Light = 1;
	if(fireX != targetx)
	{
		tax = abs(targetx - fireX);
	}else tax = 1;
	if(fireY != targety)
	{
		tay = abs(targety - fireY);
	}else tay = 1;
	if(abs(fireX - targetx) > abs(fireY - targety))
	{
		firedisX = int((targetx - fireX) * (500 / tax));
		firedisY = int((targety - fireY) * (500 / tax));
	}else
	{
		firedisX = int((targetx - fireX) * (500 / tay));
		firedisY = int((targety - fireY) * (500 / tay));
	}
	NextFrameTime = 50;
	m_dwFrameTime = GetTickCount();
	m_dwStartTime = GetTickCount();
	steptime = GetTickCount();
	repeattime = anitime;
	Dir16 = GetFlyDirection16(sx, sy, tx, ty);
	Dir8 = GetNextDirection(sx, sy, tx, ty);
	OldDir16 = Dir16;
	NextEffect = nullptr;
	m_boActive = true;
	prevdisx = 99999;
	prevdisy = 99999;

}


TMagicEff::~TMagicEff(void)
{
}

void TMagicEff::GetFlyXY(int ms,int &fx,int &fy)
{
	int rrx,rry,stepx,stepy;
	rrx = targetx - fireX;
	rry = targety - fireY;

	stepx = int((firedisX / 900) * ms);
	stepy = int((firedisY / 900) * ms);
	fx = fireX + stepx;
	fy = fireY + stepy;
}
bool TMagicEff::Run()
{
	bool result = Shift();
	if(result)
	{
		if(GetTickCount() - m_dwStartTime > 10000)
		{
			result = false;
		}else
		{
			result = true;
		}
	}
	return result;
}

bool TMagicEff::Shift()
{
	int  rrx, rry, ms1, stepx, stepy;
	int tax, tay, shx, shy, passdir16;
	bool crash;
	int stepxf, stepyf;
	bool result = true;
	if(Repetition)
	{
		if(GetTickCount() - steptime > NextFrameTime)
		{
			steptime = GetTickCount();
			curframe++;
			if( curframe > start + frame - 1 )
			{
				curframe = start;
			}
		}
	}else
	{
		if(frame > 0 && GetTickCount() - steptime > NextFrameTime)
		{
			steptime = GetTickCount();
			curframe++;
			if( curframe > start + frame - 1)
			{
				curframe = start + frame - 1;
				result = false;
			}
		}
	}
	if(!FixedEffect)
	{
		crash = false;
		if(TargetActor)
		{
			 ms1 = GetTickCount() - m_dwFrameTime;
			 if(ms1 == 0)
			 {
				 ms1 = 15; 
				 m_dwFrameTime = m_dwFrameTime + 15;
			 }
			 m_dwFrameTime = GetTickCount();
			 TPlayScene::GetInstance()->ScreenXYfromMCXY(TargetActor->m_nRx,TargetActor->m_nRy,
				 targetx,targety);
			 shx = (g_MySelf->m_nRx * UNITX + g_MySelf->m_nShiftX) - FireMyselfX;
			 shy = (g_MySelf->m_nRy * UNITY + g_MySelf->m_nShiftY) - FireMyselfY;
			 targetx = targetx + shx;
			 targety = targety + shy;
			 if( FlyX != targetx )
			 {
				 tax = abs(targetx - FlyX);
			 }else tax = 1;
			 if( FlyY != targety)
			 {
				 tay = abs(targety - FlyY);
			 }else tay = 1;
			if(abs(FlyX - targetx) > abs(FlyY - targety))
			{
				newfiredisX = int((targetx - FlyX) * (500 / tax));
				newfiredisY = int((targety - FlyY) * (500 / tax));
			}else
			{
				newfiredisX = int((targetx - FlyX) * (500 / tay));
				newfiredisY = int((targety - FlyY) * (500 / tay));
			}

			if( firedisX < newfiredisX)
			{
				firedisX = firedisX + MAX(1, (newfiredisX - firedisX) / 10);
			}

			if( firedisX > newfiredisX)
			{
				firedisX = firedisX - MAX(1, (firedisX - newfiredisX) / 10);
			}

			if( firedisY < newfiredisY)
			{
				firedisY = firedisY + MAX(1, (newfiredisY - firedisY) / 10);
			}
			if( firedisY > newfiredisY )
			{
				firedisY = firedisY - MAX(1, (firedisY - newfiredisY) / 10);
			}
			float v = (float)firedisX / 700;
			stepxf = (int)float(v * ms1);
			v = (float)firedisY / 700;
			stepyf = (int)float(v * ms1);

			FlyXf = FlyXf + stepxf;
			FlyYf = FlyYf + stepyf;

			FlyX = FlyXf;
			FlyY = FlyYf;

			OldFlyX = FlyX;
			OldFlyY = FlyY;
			passdir16 = GetFlyDirection16(FlyX, FlyY, targetx, targety);
			if (((abs(targetx - FlyX) <= 15) && (abs(targety - FlyY) <= 15)) ||
				((abs(targetx - FlyX) >= prevdisx) && (abs(targety - FlyY) >= prevdisy)) ||
				OverThrough(OldDir16, passdir16)) 
			{
				crash = true;
			}else 
			{
				prevdisx = abs(targetx - FlyX);
				prevdisy = abs(targety - FlyY);
			}

			OldDir16 = passdir16;
		}else
		{
			ms1 = GetTickCount() - m_dwFrameTime;
			rrx = targetx - fireX;
			rry = targety - fireY;
			float v = (float)firedisX / 900;
			stepx = (int)float(v * ms1);
			v = (float)firedisY / 900;
			stepy = (int)float(v * ms1);
			FlyX = fireX + stepx;
			FlyY = fireY + stepy;
		}
		TPlayScene::GetInstance()->CXYfromMouseXY(FlyX, FlyY, rx, ry);
		if(crash && TargetActor)
		{
			FixedEffect = true;
			start = 0;
			frame = ExplosionFrame;
			curframe = start;
			Repetition = false;
			PlaySound_(MagOwner->m_nMagicExplosionSound); //技能效果爆炸音效声音
		}
	}
	if(FixedEffect)
	{
		if(frame == -1)
		{
			frame = ExplosionFrame;
		}
		if(!TargetActor)
		{
			FlyX = targetx - ((g_MySelf->m_nRx * UNITX + g_MySelf->m_nShiftX) - FireMyselfX);
			FlyY = targety - ((g_MySelf->m_nRy * UNITY + g_MySelf->m_nShiftY) - FireMyselfY);
			TPlayScene::GetInstance()->CXYfromMouseXY(FlyX, FlyY, rx, ry);
		}else
		{
			rx = TargetActor->m_nRx;
			ry = TargetActor->m_nRy;
			TPlayScene::GetInstance()->ScreenXYfromMCXY(rx, ry, FlyX, FlyY);
			FlyX = FlyX + TargetActor->m_nShiftX;
			FlyY = FlyY + TargetActor->m_nShiftY;
		}
	}
	return result;
}

void TMagicEff::DrawEff(cocos2d::Layer* layer)
{
	int shx,shy,img;
	TVDImage* d;
	if(m_boActive && (abs(FlyX - fireX) > 15 && abs(FlyY - fireY) > 15 || FixedEffect))
	{
		shx = (g_MySelf->m_nRx * UNITX + g_MySelf->m_nShiftX) - FireMyselfX;
		shy = (g_MySelf->m_nRy * UNITY + g_MySelf->m_nShiftY) - FireMyselfY;
		if(!FixedEffect) //运行效果
		{
			if(use16dir)
			{
				img = EffectBase + FLYBASE + Dir16 * 10;
			}else
			{
				img = EffectBase + FLYBASE + Dir16 / 2 * 10;
			}

			if(useImgLib1)
			{
				d = ImgLib1->GetImage(img + curframe);
			}else
			{
				d = ImgLib->GetImage(img + curframe);
			}
			if(d && d->Image_)
			{
				layer->addChild(d->GetImage(FlyX + d->nx - UNITX / 2 - shx,
					FlyY + d->ny - UNITY / 2 - shy));
			}
		}else //爆炸
		{
			if(ImgLib)
			{
				img = MagExplosionBase + curframe;
				d = ImgLib->GetImage(img);
				if(d && d->Image_)
				{
					layer->addChild(d->GetImage( FlyX + d->nx- UNITX / 2,
						FlyY + d->ny - UNITY / 2));
				}
			}
		}
	}
}
bool TMagicEff::OverThrough(int olddir,int newdir)
{
	bool result = false;
	if(abs(olddir - newdir) >= 2)
	{
		result = true;
		if ((olddir == 0 && newdir == 15) || (olddir == 15 && newdir == 0))
		{
			result = false;
		}
	}
	return result;
}


TExploBujaukEffect::TExploBujaukEffect(int effbase,int sx,int sy,int tx,int ty,TActor* target)
{
	TMagicEff::Create(111,effbase,sx,sy,tx,ty,TMagicType::mtExploBujauk,true,0);
	frame = 3;
	TargetActor = target;
	NextFrameTime = 50;
	Lzidx = 0;
}
void TExploBujaukEffect::DrawEff(cocos2d::Layer* layer)
{
	if(!ImgLib) return;
	int shx = 0; int shy = 0;
	if(m_boActive && (abs(FlyX - fireX) > 30 || abs(FlyY - fireY) > 30 ||
		FixedEffect))
	{
		shx = (g_MySelf->m_nRx * UNITX + g_MySelf->m_nShiftX) - FireMyselfX;
		shy = (g_MySelf->m_nRy * UNITY + g_MySelf->m_nShiftY) - FireMyselfY;
		int img;
		TVDImage* d;
		if(!FixedEffect)
		{
			if(use16dir)
			{
				img = EffectBase + Dir16 * frame;
			}else
			{
				img = EffectBase + Dir16 / 2 * 10;
			}
			if(useImgLib1)
			{
				d = ImgLib1->GetImage(img + curframe);
			}else
			{
				d = ImgLib->GetImage(img + curframe);
			}
			if(d && d->Image_)
			{
				layer->addChild(d->GetImage(FlyX + d->nx - UNITX / 2 - shx,
					FlyY + d->ny- UNITY / 2 - shy));
			}
		}else
		{
			img = MagExplosionBase + curframe;
			d = ImgLib->GetImage(img);
			if(d && d->Image_)
			{
				layer->addChild(d->GetImage( FlyX + d->nx - UNITX / 2,
					FlyY + d->ny - UNITY / 2));
			}
		}
	}

}

TThuderEffect::TThuderEffect(int effbase,int tx,int ty,TActor* target)
{
	TMagicEff::Create(111,effbase,tx,ty,tx,ty,TMagicType::mtThunder,false,0);
	TargetActor = target;
}
void TThuderEffect::DrawEff(cocos2d::Layer* layer)
{
	int img = EffectBase;
	if(ImgLib)
	{
		TVDImage* d = ImgLib->GetImage(img + curframe);
		if(d && d->Image_)
		{
			layer->addChild(d->GetImage(FlyX + d->nx - UNITX / 2,
				FlyY + d->ny - UNITY / 2));
		}
	}
}


TBujaukGroundEffect::TBujaukGroundEffect(int effbase,int magicnumb,
										 int sx,int sy,int tx,int ty)
{
	TMagicEff::Create(111,effbase,sx,sy,tx,ty,TMagicType::mtBujaukGroundEffect,true,0);
	frame = 3;
	MagicNumber = magicnumb;
	BoGroundEffect = false;
	NextFrameTime = 50;
}
bool TBujaukGroundEffect::Run()
{
	bool result = TMagicEff::Run();
	if(!FixedEffect)
	{
		if((abs(targetx - FlyX) <= 15 && abs(targety - FlyY) <= 15)
			|| (abs(targetx - FlyX) >= prevdisx && abs(targety - FlyY) >= prevdisy))
		{
			FixedEffect = true;
			start= 0;
			frame = ExplosionFrame;
			curframe = start;
			Repetition = false;

			PlaySound_(MagOwner->m_nMagicExplosionSound);

			result = true;
		}else
		{
			prevdisx = abs(targetx - FlyX);
			prevdisy = abs(targety - FlyY);
		}
	}
	return result;
}
void TBujaukGroundEffect::DrawEff(cocos2d::Layer* layer)
{
	int img = 0;
	TVDImage* d = nullptr;
	int shx= 0,shy = 0;
	
	if(m_boActive && (abs(FlyX - fireX) > 30 || abs(FlyY - fireY) > 30 ||FixedEffect))
	{
		shx = (g_MySelf->m_nRx * UNITX + g_MySelf->m_nShiftX) - FireMyselfX;
		shy = (g_MySelf->m_nRy * UNITY + g_MySelf->m_nShiftY) - FireMyselfY;
		if(!FixedEffect)
		{
			if(use16dir)
			{
				img = EffectBase + Dir16 * 10;
			}else
			{
				img = EffectBase + Dir16 / 2 * 10;
			}
			if(useImgLib1)
			{
				 d = ImgLib1->GetImage(img + curframe);
			}else
			{
				d = ImgLib->GetImage(img + curframe);
			}
			if(d && d->Image_)
			{
				layer->addChild(d->GetImage(FlyX + d->nx- UNITX / 2 - shx,
					FlyY + d->ny - UNITY / 2 - shy));
			}
		}else
		{
			 img = MagExplosionBase + curframe;
			 if(ImgLib)
			 {
				 d = ImgLib->GetImage(img);
				 if(d && d->Image_)
				 {
					 layer->addChild(d->GetImage(FlyX + d->nx - UNITX / 2,
						 FlyY + d->ny - UNITY / 2));
				 }
			 }
		}
	}
	
}

TLightingThunder::TLightingThunder(int effbase,int sx,int sy,int tx,int ty,TActor* target)
{
	TMagicEff::Create(111, effbase,sx, sy,tx, 
		ty,TMagicType::mtLightingThunder,false,0);
	TargetActor = target;
}

void TLightingThunder::DrawEff(cocos2d::Layer* layer)
{
	int img = 0, sx = 0, sy = 0, px = 0, py = 0, shx = 0, shy = 0;
	TVDImage* d;
	img = EffectBase + Dir8 * 4;
	if(curframe < 4)
	{
		shx = (g_MySelf->m_nRx * UNITX + g_MySelf->m_nShiftX) - FireMyselfX;
		shy = (g_MySelf->m_nRy * UNITY + g_MySelf->m_nShiftY) - FireMyselfY;
		if(ImgLib)
		{
			d = ImgLib->GetImage(img + curframe);
			if(d && d->Image_)
			{
				TPlayScene::GetInstance()->ScreenXYfromMCXY(MagOwner->m_nRx,
					MagOwner->m_nRy,sx,sy);
				layer->addChild(d->GetImage(sx + d->nx - UNITX / 2,
					sy + d->ny - UNITY / 2));
			}
		}
	}
}


TObjectEffects::TObjectEffects(TActor* ObjectiD2,TVDImageDatas* WmImage,
							   int effbase,int nX,unsigned long frmTime,bool boFlag)
{
	TMagicEff::Create(111,effbase,0,0,0,0,TMagicType::mtReady,true,0);
	ImgLib = WmImage;
	EffectBase = effbase;
	start = 0;
	curframe = 0;
	frame = nX;
	NextFrameTime = frmTime;
	boC8 = boFlag;
	ObjectId = ObjectiD2;
}

bool TObjectEffects::Run()
{
	if(m_boActive && GetTickCount() - steptime > (unsigned long)NextFrameTime)
	{
		steptime = GetTickCount();
		curframe ++;
		if(curframe > start + frame - 1)
		{
			curframe = start;
			return false;
		}
	}

	return true;
}

void TObjectEffects::DrawEff(cocos2d::Layer* layer)
{
	int Rx,Ry,nRx,nRy;
	if(!ImgLib) return;
	TVDImage* d = ImgLib->GetImage(EffectBase + curframe);
	if(d && d->Image_ && ObjectId)
	{
		Rx = ObjectId->m_nRx;
		Ry = ObjectId->m_nRy;
		
		TPlayScene::GetInstance()->ScreenXYfromMCXY(Rx,Ry,nRx,nRy);
		nRx += ObjectId->m_nShiftX;
		nRy += ObjectId->m_nShiftY;
		layer->addChild(d->GetImage(nRx + d->nx - UNITX / 2,
			nRy + d->ny - UNITY / 2));
	}
}