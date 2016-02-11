#include "SoundUtil.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"
#include <stdio.h>
#include <string>
#include "../MShare.h"
#include <vector>

void ClearSound()
{
	
	TSoundInfo* info;
	int i =0;
	while(true)
	{
		if(i >= (int)g_SoundList.size()) break;
		info = g_SoundList[i];
		if(GetTickCount() - info->dwLastTick > 1000 * 60) //大于一分钟没播放过的音乐清理掉
		{
			delete info;
			g_SoundList.erase(g_SoundList.begin() + i);
			i ++;
			continue;;

		}
		i++;
	}
	
	
}
void PlaySound_(int idx,int x,int y,bool Loop)
{
	//CocosDenshion::SimpleAudioEngine::sharedEngine()->preloadEffect()
	if(idx <= 0)return;
	char fn[1024] = {0};
	sprintf(fn,S_SoundFile,idx);
	std::string sFileName = fn;
	sFileName = cocos2d::FileUtils::getInstance()->fullPathForFilename(sFileName);
	if(!cocos2d::FileUtils::getInstance()->isFileExist(sFileName))
	{
		CCLOG("PlaySound_ file find error! %s",sFileName.c_str());
		return;
	}
	bool bFind = false;
	TSoundInfo* info;
	std::vector<TSoundInfo*>::iterator it;
	for(it = g_SoundList.begin();it != g_SoundList.end();it++)
	{
		info = (TSoundInfo*)*it;
		if(info->sFileName == sFileName)
		{
			bFind = true;
			info->dwLastTick = GetTickCount();
			break;
		}
	}

	if(!bFind)
	{
		CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(sFileName.c_str());
		info = new TSoundInfo;
		info->sFileName = sFileName;
		info->dwLastTick = GetTickCount();
		g_SoundList.push_back(info);
	}
	
	CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(sFileName.c_str());

}
void PlayMp3(const char* wavname,bool boFlag)
{

}

void PlayMapMusic(std::string sOldMusic,std::string sNewMusic)
{
	//有待修改- 比如播放完背景音乐后-  间隔多少秒才再次播放，现在是播放完之后就立即播放背景音乐
	//服务端发的音乐地址是网址-- 需要修改-
	
	CocosDenshion::SimpleAudioEngine::getInstance()->stopBackgroundMusic(true);
	std::string sPath = "data/bgm/" + sNewMusic;
	std::string sFileName = cocos2d::FileUtils::getInstance()->fullPathForFilename(sPath);
	if(!cocos2d::FileUtils::getInstance()->isFileExist(sFileName))
	{
	CCLOG("PlayMapMusic file find error! %s",sFileName.c_str());
	return;
	}
	CocosDenshion::SimpleAudioEngine::getInstance()->preloadBackgroundMusic(sFileName.c_str());
	CocosDenshion::SimpleAudioEngine::getInstance()->playBackgroundMusic(sFileName.c_str(),true);

}