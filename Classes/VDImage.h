#ifndef VDIMAGE_H_
#define VDIMAGE_H_
#include "cocos2d.h"
#include <vector>
#include "GameStruct.h"
using namespace cocos2d;

class TVDImage
{
public:
	TVDImage(void);
	 ~TVDImage(void);
	 static TVDImage* Create();
public:
	int nx;
	int ny;
	char btType;
	int pWidth;
	int pHeight;
	int TexWidth;
	int TexHeight;
	int DataOffset;
	unsigned long dwLatestTime;
	Texture2D* TEX;
	cocos2d::Sprite* Image_;
	cocos2d::Image* im;
	void Destory();
	void ClearImage();
	bool CreateImage(unsigned char* pData,TVDDataInfo* imginfo);
	void SetSpritePostion(int x,int y); //已废弃

	unsigned long getPixels(int x,int y);
	cocos2d::Sprite* GetImage(int x= -1,int y =-1);

	//复用后的精灵
	std::vector<cocos2d::Sprite*> m_ImageList;
};

#endif