#ifndef MAGICEFF_H_
#define MAGICEFF_H_
#include "GameStruct.h"
#include "cocos2d.h"
class TVDImageDatas;
class TActor;
class TMagicEff
{
public:
	TMagicEff();
	void Create(int id,int effnum,int sx,int sy,int tx,int ty,TMagicType mtype,
		bool Recusion,int anitime);
	~TMagicEff(void);
public:
	bool m_boActive;
	int ServerMagicId;
	TActor* MagOwner;
	TActor* TargetActor;
	TVDImageDatas* ImgLib; //TVDImageDatas
	TVDImageDatas* ImgLib1; //TVDImageDatas
	bool useImgLib1;
	int EffectBase;
	int temp;
	int MagExplosionBase;
	int py;
	int rx;
	int ry;
	unsigned char Dir16;
	unsigned char OldDir16;
	unsigned char Dir8;
	bool use16dir;
	int targetx;
	int targety;
	int TargetRx;
	int TargetRy;
	int FlyX;
	int FlyY;
	int OldFlyX;
	int OldFlyY;
	int FlyXf;
	int FlyYf;
	bool Repetition;
	bool FixedEffect;
	int MagicType;
	void* NextEffect;
	int ExplosionFrame;
	unsigned long NextFrameTime;
	int Light;
	int n7C;
	unsigned char bt80;
	unsigned char bt81;
	int start;
	int curframe;
	int frame;
	bool bo8; //八个方向的动画，不是16个方向的动画
protected:
	unsigned long m_dwFrameTime;
	unsigned long m_dwStartTime;
	unsigned long repeattime;
	unsigned long steptime;
	int	fireX;
	int fireY;
	int	firedisX;
	int firedisY;
	int	newfiredisX;
	int newfiredisY;
	int	FireMyselfX;
	int FireMyselfY;
	int prevdisx;
	int prevdisy;
	int	m_nOldx;
	int m_nOldY;
	int nCount;
	int Lzidx;
	bool boLz;
public:
	void GetFlyXY(int ms,int &fx,int &fy);
	virtual bool Run();
	virtual bool Shift();
	virtual void DrawEff(cocos2d::Layer* layer);
private:
	bool OverThrough(int olddir,int newdir);

};

//火球术
class TExploBujaukEffect : public TMagicEff
{
public:
	TExploBujaukEffect(int effbase,int sx,int sy,int tx,int ty,TActor* target);
	virtual void DrawEff(cocos2d::Layer* layer);
};
//雷电术
class TThuderEffect : public TMagicEff
{
public:
		TThuderEffect(int effbase,int tx,int ty,TActor* target);
		virtual void DrawEff(cocos2d::Layer* layer);
};

//幽灵盾/魔防术
class TBujaukGroundEffect: public TMagicEff
{
public:
	TBujaukGroundEffect(int effbase,int magicnumb,int sx,int sy,int tx,int ty);
	virtual bool Run();
	virtual void DrawEff(cocos2d::Layer* layer);
	int MagicNumber;
	bool BoGroundEffect;

};

class TLightingThunder : public TMagicEff
{
public:
	TLightingThunder(int effbase,int sx,int sy,int tx,int ty,TActor* target);
	virtual void DrawEff(cocos2d::Layer* layer);
};

class TObjectEffects : public TMagicEff
{
public:
	TObjectEffects(TActor* ObjectiD2,TVDImageDatas* WmImage,int effbase,int nX,unsigned long frmTime,bool boFlag);
	virtual bool Run();
	virtual void DrawEff(cocos2d::Layer* layer);
	TActor* ObjectId;
	bool boC8;

};

#endif
