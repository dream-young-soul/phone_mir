#include "VDImageDatas.h"

#include "cocos2d.h"
#include "../FileStream.h"
#include "../VDImage.h"
#include "../MShare.h"
using namespace cocos2d;
TVDImageDatas::TVDImageDatas(std::string sFileName)
{
	FileName = sFileName;
	m_Images.clear();
	m_dwMemChecktTick = 0;
}


TVDImageDatas::~TVDImageDatas(void)
{
	
}

void TVDImageDatas::Destory()
{

	if(m_Images.size() > 0)
	{
		std::map<int,TVDImage*>::iterator it;
		for(it = m_Images.begin();it != m_Images.end();it++)
		{
			it->second->Destory();
		}
	}
	m_fData.clear();
	m_Images.clear();
	CCLOG("remove vdd%s",FileName.c_str());
	delete this;
}

TVDImageDatas* TVDImageDatas::Create(const std::string sFileName)
{
	
	TVDImageDatas* c = new(std::nothrow) TVDImageDatas(sFileName);
	if(c)
	{
		return c;
	}
	return nullptr;
}

void TVDImageDatas::Initialize()
{
	std::string filepath = FileUtils::getInstance()->fullPathForFilename(FileName);
	if(!CCFileUtils::getInstance()->isFileExist(filepath))
	{
		filepath += "load vdds error!" ;
		g_AnroidLog.push_back(filepath);
		return;
	}
	ssize_t nLen = 0;
	m_fData = CCFileUtils::getInstance()->getDataFromFile(FileName);
	nLen = m_fData.getSize();
	
	unsigned char* m_pData = m_fData.getBytes();
	//m_pData = CCFileUtils::getInstance()->getFileData(filepath.c_str(),"rb",&nLen);
	CFileStream stream;
	if(stream.Init(m_pData,nLen))
	{
		std::string title =	stream.readString(sizeof(Header.Title));
		strcpy(Header.Title,title.c_str());
		Header.DBCount = stream.readInt();
		Header.VerFlag = stream.readInt();
		for(int i = 0;i < Header.DBCount; i++)
		{
			TVDImage* img = TVDImage::Create();
			img->DataOffset = stream.readInt();
			m_Images[i] = img;
		}
	}
	
//	if(nLen > 0 && data)
//	{
//		delete[] data;
//	}
}

TVDImage* TVDImageDatas::GetImage(int idx)
{
	unsigned char* m_pData = m_fData.getBytes();
	if(!m_pData)return nullptr;
	CFileStream stream;
	TVDImage* img = nullptr;
	if(idx >= 0 && idx < (int)m_Images.size())
	{
		img = m_Images[idx];
		if(img->TEX == nullptr)
		{
			TVDDataInfo imginfo;
			unsigned char* p = &m_pData[sizeof(TVDDataHeader) + Header.DBCount * sizeof(int)
				+ img->DataOffset];
			 stream.Init(p,sizeof(TVDDataInfo));
			 imginfo.nType = stream.readByte();
			 imginfo.n1 = stream.readByte();
			 imginfo.n2 = stream.readByte();
			 imginfo.n3 = stream.readByte();
			 imginfo.nSize = stream.readInt();
			 imginfo.px = stream.readShort();
			 imginfo.py = stream.readShort();
			 p += sizeof(TVDDataInfo);
			 if(imginfo.nSize > 0)
			 {
				 img->CreateImage(p,&imginfo);
			 }
		}
		img->dwLatestTime = GetTickCount();
	}
	//if(GetTickCount() - m_dwMemChecktTick > 10000)//十秒钟
	//{
	//	FreeOldMemorys();
	//	m_dwMemChecktTick = GetTickCount();
	//}
	return img;
}

bool TVDImageDatas::FreeOldMemorys()
{
	bool ret = false;
	int nCount = 0;
	if(GetTickCount() - m_dwMemChecktTick <  60 * 1000)/*一分钟检测一次无用纹理*/ return ret;
	std::map<int,TVDImage*>::iterator it;
	for(it = m_Images.begin(); it != m_Images.end();it++)
	{
		if(it->second->TEX && it->second->Image_)
		{
			if(GetTickCount() - it->second->dwLatestTime > 2 * 60 * 1000 )//二分钟没有用到过的纹理清除掉 2 * 60 * 1000
			{ 
				it->second->ClearImage();
				CCLOG("remove sprite:%s,idx:%d",GetFileName(),it->first);
				nCount++;
			}
		}

	}
	if(nCount == m_Images.size())
	{
		ret = true;
	}
	m_dwMemChecktTick = GetTickCount();
	return ret;
}