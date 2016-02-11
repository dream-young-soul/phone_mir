#ifndef GUAJIHELPER_H_
#define GUAJIHELPER_H_
#include <string>
#include "GameStruct.h"
//挂机单元文件- 2015.7.11
class TActor;
class TGuaJiHelper
{
public:
	TGuaJiHelper(void);
	~TGuaJiHelper(void);
	static TGuaJiHelper* GetInstance();
public:
	TActor* m_TargetCret;
	int m_nTargetX; 
	int m_nTargetY;
	std::string m_KillMonName;
	bool boAvoid;
	void Started(bool val);
	void Start();
	void Stop();
	void Run();
	bool IsStart(){return FStarted;}
	TActor* SearchTargetEx();
	TClientMagic* SingldAttack; //单体攻击
	TClientMagic* GroupAttack;  //群体攻击
	void SelectMagicLise();//选择挂机技能
private:
	int FPathPoisonIndex;
	bool FStarted;
	unsigned long FRunTick;
	unsigned long FAttackTick;
	bool CanRunEx(int sx,int sy,int ex,int ey,bool flag);
	bool CanWalkEx(int nTargetX,int nTargetY,bool flag);
	bool CanWalk(int nTargetX,int nTargetY,bool flag);
	void SetStarted(bool Value);
	void Avoid();
	bool UseMagic();
	int GetNearTargetCount();
	int GetRangeTargetCount(int nx,int ny,int nRange);
	void SearchTarget();
	void GetAutoWalkXY(int &nTargetX,int &nTargetY);
	bool GetNextPosition(int sx,int sy,int nDir,int nFlag,int &snx,int &sny);


	//--
	bool GetRandXY(int &nx,int &ny);
	unsigned char GetNextDir(unsigned char btDir);
	
};

#endif

