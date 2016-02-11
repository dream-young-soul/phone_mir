#include "VDImage.h"
#include "MShare.h"

TVDImage::TVDImage(void)
{
	nx = ny = 0;
	TEX = nullptr;
	btType = 0;
	pWidth = 0;
	pHeight = 0;
	TexWidth = 0;
	TexHeight = 0;
	DataOffset = 0;
	dwLatestTime = 0;
	m_ImageList.clear();

	Image_ = nullptr;
}


TVDImage::~TVDImage(void)
{

}

bool TVDImage::CreateImage(unsigned char* pData,TVDDataInfo* imginfo)
{
	im = new Image();
	if(!im->initWithImageData(pData,imginfo->nSize))
	{
	//	CCLOG("TVDImage::CreateImage error %d %s code:1",idx,FileName.c_str());
		delete im;
		im = nullptr;
		return nullptr;
	}
	//im->retain();
	TEX = new Texture2D;
	if(!TEX->initWithImage(im,Texture2D::PixelFormat::AUTO))
	{
		delete TEX;
		TEX = nullptr;
		return nullptr;
	}

	
	//img->TEX->retain(); //不能加啊，大兄弟，后面的createWithTexture会给这个tex retain
	nx = imginfo->px;
	ny = imginfo->py;
	btType = imginfo->nType;
	TexWidth = im->getWidth();
	TexHeight = im->getHeight();
	pWidth = TEX->getPixelsWide();
	pHeight = TEX->getPixelsHigh();

	Image_ = Sprite::createWithTexture(TEX);
	Image_->retain();
	//设置描点坐标-
	//img->Image_ = new Sprite();

	//img->Image_->setTexture(img->TEX);
	Vec2 pos;
	Image_->setAnchorPoint(pos);
	return true;
}
void TVDImage::ClearImage()
{
	if(TEX && Image_ && im)
	{
		Image_->release();
		std::vector<cocos2d::Sprite*>::iterator it;
		for(it = m_ImageList.begin();it != m_ImageList.end();it++)
		{
			cocos2d::Sprite* sprite = *it;
			sprite->release();
		}
		TEX->release();
		m_ImageList.clear();
		im->release();
		TEX = nullptr;
		Image_ = nullptr;
	
		im = nullptr;
	}
}
void TVDImage::Destory()
{
	ClearImage();
	delete this;
}
TVDImage* TVDImage::Create()
{
	TVDImage* c = new(std::nothrow) TVDImage();
	return c;
}
unsigned long TVDImage::getPixels(int x,int y)
{
	if(Image_)
	{
		dwLatestTime = GetTickCount();
		if(x > pWidth || x < 0)
		{
			return 0;
		}
		if(y > pHeight || y < 0)
		{
			return 0;
		}
		unsigned char *data_=im->getData(); 
		unsigned int *pixel = (unsigned int *)data_;
		pixel = pixel + (y * TexWidth) + x;      
		Color4B c;
		c.r = *pixel & 0xff;
		c.g = (*pixel >> 8) & 0xff;
		c.b = (*pixel >> 16) & 0xff;
		c.a = (*pixel >> 24) & 0xff;    
		//转换成十进制颜色值
		return 16777216 * c.r + 65536 * c.b + 256 * c.g + c.r;
	}
	return 0;
}
void TVDImage::SetSpritePostion(int x,int y)
{
	if(Image_)
	{
		cocos2d::Vec2 pos;
		pos.x = x;
		pos.y = y;
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y - TexHeight;
		Image_->setPosition(pos);
	}
}

cocos2d::Sprite* TVDImage::GetImage(int x,int y)
{
	cocos2d::Sprite* sprite = nullptr;
	Vec2 pos;
	bool bFind = false;
	//如果已经被加入到了场景，则取复用后的精灵
	if(Image_->getParent())
	{
		std::vector<cocos2d::Sprite*>::iterator it;
		for(it = m_ImageList.begin();it != m_ImageList.end();it++)
		{
			sprite = *it;
			if(!sprite->getParent())
			{
				bFind = true;
				break;
			}
		}
		if(!bFind) sprite = nullptr;
	}else
	{
		
		sprite = Image_;
	}
	
	if(!bFind && !sprite)
	{
		sprite = cocos2d::Sprite::createWithTexture(TEX);
		sprite->retain();
		sprite->setAnchorPoint(pos);
		m_ImageList.push_back(sprite);
	}


	if(x != -1 || y != -1)
	{
		pos.x = x;
		pos.y = y;
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y - TexHeight;
		sprite->setPosition(pos);

	}else
	{
		pos = Image_->getPosition();
		sprite->setPosition(pos.x,pos.y);
	}
	dwLatestTime = GetTickCount();
	return sprite;

}