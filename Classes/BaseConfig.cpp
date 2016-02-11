#include "BaseConfig.h"
#include <string>
#include "cocos2d.h"
#include "./Common/ZipUnit.h"
#include "filestream.h"
#include "MShare.h"
static CBaseConfig* m_Instance = nullptr;
CBaseConfig::CBaseConfig(void)
{
}


CBaseConfig::~CBaseConfig(void)
{
}

CBaseConfig* CBaseConfig::GetInstance()
{
	if(!m_Instance)
	{
		m_Instance =new CBaseConfig();
	}
	return m_Instance;
}

bool CBaseConfig::LoadConfig()
{
	if(!LoadClientStdItemsData())
	{
		return false;
	}
	if(!LoadClientAdditionItemsData())
	{
		return false;
	}
	return true;
}
bool CBaseConfig::LoadClientStdItemsData()
{
	g_StdItemList.clear();
	g_MItemArray.clear();
	const std::string sFileName = "data/i.dat";
	std::string filepath = cocos2d::FileUtils::getInstance()->fullPathForFilename(sFileName);
	if(!cocos2d::FileUtils::getInstance()->isFileExist(filepath))
	{
		return false;
	}
	ssize_t nSize;
	cocos2d::Data fdata = cocos2d::FileUtils::getInstance()->getDataFromFile(filepath);
	nSize = fdata.getSize();
	unsigned char* pData = fdata.getBytes();
	//unsigned char* pData = cocos2d::FileUtils::getInstance()->getFileData(filepath,"rb",&nSize);
	if(nSize > 0 && pData)
	{
		int nLen = 0;
		unsigned char* pDecData = UnCompression(pData,nSize,nLen);
		if(!pDecData)
		{
			return false;
		}
		CFileStream stream;
		stream.Init(pData,nLen);
		int nCount = nLen / sizeof(TStdItem);
		TStdItem* item = nullptr;
		for(int i = 0;i < nCount;i++)
		{
			item = new TStdItem;
			memcpy(item,&pDecData[i * sizeof(TStdItem) + sizeof(int)/*版本号*/ ],
				sizeof(TStdItem));
			//直接移植的delphi版本，delphi的string数据类型
			unsigned char nNameLen = item->Name[0];
			memcpy(&item->Name,&item->Name[1],nNameLen);
			item->Name[nNameLen] = 0;
			g_StdItemList.push_back(item);
			//镶嵌类物品
			if(item->CharLooks >= 0 && item->CharLooks <= 256 && item->StdMode >= 0)
			{
				g_MItemArray[item->CharLooks] = item;
			}
		}
		if(pDecData)delete []pDecData;

	}else
	{
		
	}
	return true;
}

bool CBaseConfig::LoadClientAdditionItemsData()
{
	g_AdditionItemList.clear();
	const std::string sFileName = "data/ai_.dat";
	std::string filepath = cocos2d::FileUtils::getInstance()->fullPathForFilename(sFileName);
	if(!cocos2d::FileUtils::getInstance()->isFileExist(filepath))
	{
		return false;
	}
	ssize_t nSize;
	cocos2d::Data fdata = cocos2d::FileUtils::getInstance()->getDataFromFile(filepath);
	nSize = fdata.getSize();
	unsigned char* pData = fdata.getBytes();
	
	if(nSize > 0 && pData)
	{
		int nLen = 0;
		unsigned char* pDecData = UnCompression(pData,nSize,nLen);
		if(!pDecData)
		{
			return false;
		}
		TAdditionItem* item;
		TStdItem* stditem;
		int size = (int)nLen /sizeof(TAdditionItem);
		for(int i = 0;i < size;i++)
		{
			item = new TAdditionItem();
			memcpy(item,&pDecData[i * sizeof(TAdditionItem)],sizeof(TAdditionItem));
			stditem =GetStdItemInfo(item->id);
			if(!stditem)
			{
				delete item;
				continue;
			}
			g_AdditionItemList[stditem->Name] = item;
		}
		delete []pDecData;
	}
	return true;
}