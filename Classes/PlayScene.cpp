#include "PlayScene.h"


#include "VDImage.h"
#include "VD_Share.h"
#include "MapUnit.h"
#include "MShare.h"
#include "./Net/NetClient.h"
#include "./Net/NetRecvMsg.h"
#include "./Net/NetSendMsg.h"
#include "./Common/VDImageDatas.h"
#include "./Common/Grobal2.h"
#include "./Common/SoundUtil.h"
#include "FrmMain.h"
#include "./Common/IconvString.h"
#include "./UI/UIManager.h"
#include "./UI/ShortcutsDialog.h"
#include "MagicEff.h"
#include "clEvent.h"
#include "DScreen.h"
#include "GuaJiHelper.h"
using namespace VD_UI;
using namespace VD_Net;
TPlayScene* m_Instance = nullptr;

TPlayScene* TPlayScene::GetInstance()
{
	if(!m_Instance)
	{
		m_Instance = new TPlayScene();
	}
	return m_Instance;
}
TPlayScene::TPlayScene(void)
{
	m_LayerTitle = Layer::create();
	m_LayerTitle->retain();
	m_LayerActor = Layer::create();
	m_LayerActor->retain();
	m_LayerUI = Layer::create();
	m_LayerUI->retain();
	//m_LayerActor->setGLProgram(GLProgramCache::getInstance()->
	//	getGLProgram(GLProgram::SHADER_NAME_POSITION_COLOR));
	m_nLastTime = GetTickCount();
	m_ActorList.clear();
	m_dwAniTime = m_dwMoveTime = 0;
	m_nMoveStepCount = 0;
	m_nAniCount = 0;
	m_dwFrameTime = 0;
	m_dwFrameCount = 0;
	m_dwDrawFrameCount = 0;
	m_LabelList.clear();
	m_ShowImgMsgIdx = -1;
	m_ShowImgMsgTick = GetTickCount();
	m_ShowImgMsgTop = -1;
}


TPlayScene::~TPlayScene(void)
{
}

void TPlayScene::PlayScene()
{
	std::string slog = "playscene error ! g_myself = null";
	if(!g_MySelf)
	{	
		return; //还没创建角色嘛。。
	}
	if(!VDMap::GetInstance()->m_Loaded )
	{
		if(VDMap::GetInstance()->m_sOldMap.length() <= 0)
		{
			return;
		}
		if(!VDMap::GetInstance()->LoadMapAllArr())
		{
			return;
		}
	}

	bool movetick = false,movetickRush = false;
	if(GetTickCount() - m_dwMoveTime >= 85/*{这里可以控制移动速度越小越快默认是95} */)
	{
		m_dwMoveTime = GetTickCount();
		movetick = true;
		m_nMoveStepCount ++ ;
		if(m_nMoveStepCount > 1)
		{
			m_nMoveStepCount = 0;
		}
	}
	if(GetTickCount() - m_dwAniTime >= 50)
	{
		m_dwAniTime = GetTickCount();
		m_nAniCount ++;
		if(m_nAniCount > 100000)
		{
			m_nAniCount = 0;
		}
	}
	int i = 0;
	int j = 0;
	TActor* actor;
	while(true)
	{
		if(i >= (int)m_ActorList.size()) break;
		actor = m_ActorList[i];
		if(movetick)
		{
			actor->m_boLockEndFrame = false;
		}
		if(!actor->m_boLockEndFrame)
		{
			actor->ProcMsg();
			if(movetick)
			{
				if(actor->Move(m_nMoveStepCount))
				{
					i++;
					continue;
				}
			}
			actor->Run();
			if(actor != g_MySelf)
			{
				actor->ProcHurryMsg();
			}
		}
		if(actor == g_MySelf)
		{
			actor->ProcHurryMsg();
		}
		if(actor->m_nWaitForRecogId != 0)
		{
			if(actor->IsIdle())
			{
				DelChangeFace(actor->m_nWaitForRecogId);
				NewActor(actor->m_nWaitForRecogId,actor->m_nCurrX,actor->m_nCurrY,actor->m_btDir,
					actor->m_nWaitForFeature, actor->m_nWaitForStatus);
				actor->m_nWaitForRecogId = 0;
				actor->m_boDelActor = true;
			}
		}
		if(actor->m_boDelActor)
		{
			DelActor(actor);
			if(g_TargetCret == actor)g_TargetCret = nullptr;
			if(g_FocusCret == actor)g_FocusCret = nullptr;
			if(g_MagicTarget == actor)g_MagicTarget = nullptr;


		}else
		{
			i++;
		}

	}

	//效果 魔法等 run，计算魔法，已经结束的要删掉了

	std::vector<TMagicEff*> templist;templist.clear();
	i = 0;
	TMagicEff* meff;
	while(true)
	{
		if(i >= (int)m_EffectList.size()) break;
		meff = m_EffectList[i];
		if(meff->m_boActive)
		{
			if(!meff->Run())
			{
				delete meff;
				m_EffectList.erase(m_EffectList.begin() + i);

				i++;
				continue;
			}
		}
		i++;
	}
	//事件
	i = 0;
	TEvent* evn;
	while(true)
	{
		if(i >= (int)TClEventManager::GetInstance()->EventList.size())break;
		evn = TClEventManager::GetInstance()->EventList[i];
		if(abs(evn->m_nX - g_MySelf->m_nCurrX) > 30 &&
			abs(evn->m_nY - g_MySelf->m_nCurrY > 30))
		{
			TClEventManager::GetInstance()->EventList.erase(
				TClEventManager::GetInstance()->EventList.begin() + i);
			delete evn;
			i ++;
			continue;
		}
		i++;
	}
	TClEventManager::GetInstance()->Execute();



	//计算绘制区域

	TRect_* clientRect = &VDMap::GetInstance()->m_ClientRect;
	i = SCREENWIDTH / UNITX + 6;
	j = i / 2;
	if(i % 2 > 0) j++;
	clientRect->Left = g_MySelf->m_nRx - j;
	clientRect->Right = g_MySelf->m_nRx + j;

	i = SCREENHEIGHT / UNITY + 6;
	j = i / 2;
	if(i % 2 > 0) j ++;
	clientRect->Top = g_MySelf->m_nRy - j;
	clientRect->Bottom = g_MySelf->m_nRy + j;
	//计算基础坐标- 左上角，坐标已在屏幕外
	int defx = -UNITX * 4 - g_MySelf->m_nShiftX + AAX + 14;
	int defy = -UNITY * 4 - g_MySelf->m_nShiftY;

	//////////////屏幕边缘处理////////////
	i = (-clientRect->Left) * UNITX + defx;
	if(i > 0)//最左边了
	{
		defx = defx - i;
		clientRect->Right =  clientRect->Right + i / UNITX;
	}
	i = ((VDMap::GetInstance()->Header.Width - 1) - clientRect->Left) * 
		UNITX + defx + UNITX;
	if(i < SCREENWIDTH)
	{
		clientRect->Left = VDMap::GetInstance()->Header.Width - 
			(SCREENWIDTH / UNITX + 4);
		defx = SCREENWIDTH - (VDMap::GetInstance()->Header.Width - clientRect->Left) * UNITX;
	}

	//最上边
	i = (- clientRect->Top) * UNITY + defy;
	if(i > 0)
	{
		defy = defy - i;
		clientRect->Bottom = clientRect->Bottom + i / UNITY;
	}
	i = ((VDMap::GetInstance()->Header.Height)-clientRect->Top) * UNITY + defy;
	if(i < SCREENHEIGHT)//最下边
	{
		clientRect->Top = VDMap::GetInstance()->Header.Height - (SCREENHEIGHT / UNITY + 4);
		defy = SCREENHEIGHT - (VDMap::GetInstance()->Header.Height - clientRect->Top) * UNITY;
	}

	m_nDefXX = defx;
	m_nDefYY = defy;
	//画地砖
	DrawTileMap();

	m_LayerActor->removeAllChildrenWithCleanup(true);

	//画地图连接点-
	if(g_CurLocalMap)
	{
		for(int i = 0;i < (int)g_CurLocalMap->Gates.size();i++)
		{
			TMapGateInfo* p = (TMapGateInfo*)g_CurLocalMap->Gates[i];
			if(p->SX > clientRect->Left && p->SX < clientRect->Right
				&& p->SY > clientRect->Top && p->SY < clientRect->Bottom)
			{
				if(GetTickCount() > g_MapGateTick)
				{
					g_MapGateFrame++;
					if(g_MapGateFrame >= 10)
					{
						g_MapGateFrame = 0;
					}
					g_MapGateTick = GetTickCount() + 100;
				}

				TVDImage* img = GetUIImage(400 + g_MapGateFrame);
				if(img && img->Image_)
				{
					//外传增加地图传送点偏移点和传送点地图名称- 2013.4.2
					int ix = (p->SX - clientRect->Left) * UNITX + m_nDefXX  + img->nx ;
					int iy = (p->SY - clientRect->Top) * UNITY + m_nDefYY + img->ny;
					if (ix < SCREENWIDTH && ix + img->pWidth > 0
						&& iy < SCREENHEIGHT && iy + img->pHeight > 0)
					{
						cocos2d::Sprite* s  = img->GetImage(ix,iy);
						//资源需要统一调整
						//if(img->btType == 2) //类型判断
						//{
						//	ccBlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
						//	s->setBlendFunc(cbl);
						//}
						BlendFunc cbl = {GL_SRC_ALPHA, GL_ONE};
						s->setBlendFunc(cbl);
						m_LayerActor->addChild(s);
					}
					std::string mapTitle = p->DMapTitle + "入口";
					char dest[1024]={};
					GBKToUTF8((char*)mapTitle.c_str(),mapTitle.length(),dest,sizeof(dest));
					mapTitle = dest;
					DrawFontEx(mapTitle,(p->SX - clientRect->Left) * UNITX + m_nDefXX + HALFX - 
						mapTitle.length() / 2,(p->SY - clientRect->Top) * UNITY + m_nDefYY - 75,
						0xFF00CCFF,true);
				}
			}

		}
	}

	//画角色- 掉落物品- 
	bool bDraw = false;

	int m = defy - UNITY;
	for(int j = clientRect->Top;j < clientRect->Bottom + LONGHEIGHT_IMAGE;j++)
	{
		if(j < 0)
		{
			m += UNITY;
			continue;
		}
		int n =  defx - UNITX * 2;
		for(int i = clientRect->Left - VDMap::GetInstance()->m_nBlockLeft - 2;
			i < clientRect->Right - VDMap::GetInstance()->m_nBlockLeft + 2;i++)
		{
			if(i >= 0 && i < LOGICALMAPUNIT * 3 && j >= 0
				&& j < LOGICALMAPUNIT * 3)
			{
				if(j >= VDMap::GetInstance()->Header.Height || i >= VDMap::GetInstance()->Header.Width)
				{
					continue;
				}
			}
			n += UNITX;
		}

		//(j <= Map.m_ClientRect.Bottom) And (Not g_boServerChanging) 
		if(j <= clientRect->Bottom && !g_boServerChanging)
		{

			//画事件--
			for(int i = 0; i < (int)TClEventManager::GetInstance()->EventList.size();i++)
			{
				evn = TClEventManager::GetInstance()->EventList[i];
				if(j == evn->m_nY - VDMap::GetInstance()->m_nBlockTop)
				{
					evn->DrawEvent(m_LayerActor,(evn->m_nX - clientRect->Left) * UNITX + defx,m);
				}
			}
			//死的对象--
			for(int k = m_ActorList.size() - 1;k >= 0;k-- )
			{
				actor = m_ActorList[k];
				if(j == actor->m_nRy - actor->m_nDownDrawLevel)
				{
					if (! Shared.boClearBody && actor->m_boDeath) 
					{
						//头顶文字坐标计算 没加载到图片时用固定的，加载到了用图片的来计算
						actor->m_nSayX = (actor->m_nRx - clientRect->Left) * UNITX +
							defx + actor->m_nShiftX + 24;
						if( actor->m_boDeath)
						{
							actor->m_nSayY = m + UNITY + actor->m_nShiftY + 16 - 60 +
								(actor->m_nDownDrawLevel * UNITY);
						}else
						{
							actor->m_nSayY = m + UNITY + actor->m_nShiftY + 16 - 96 +
								(actor->m_nDownDrawLevel * UNITY);
						}
						//画不透明角色，包括自己
						bDraw = true;
						if((Shared.boHideActor && actor->m_sUserName != g_MySelf->m_sUserName) &&
							(actor->m_btRace = RC_PLAYOBJECT || actor->m_btRace == RC_HORSE)) //隐藏其他角色和坐骑
						{
							bDraw =  false;
						}
						if(bDraw)
						{
							int nx = (actor->m_nRx - clientRect->Left) * UNITX + defx;
							int ny = (actor->m_nRy - clientRect->Top) * UNITY + defy + (actor->m_nDownDrawLevel * UNITY);
							bool ret = IsMapMask(actor);
							actor->DrawChr(nx,ny,false, true,m_LayerActor,ret); //画不透明角色，包括自己
						}


					}
				}

			}

		}
		int ix,iy;
		//掉落物品绘制
		TDropItem* pDropItem;
		for(int k = 0;k < (int)g_DropedItemList.size();k++)
		{
			pDropItem = g_DropedItemList[k];
			if(pDropItem)
			{
				if(j == pDropItem->y)
				{
					ix = (pDropItem->x - clientRect->Left) * UNITX + defx ;
					iy = (pDropItem->y - clientRect->Top) * UNITY + defy ;
					TVDImage* drop_img = GetBagImage(pDropItem->Looks);
					if(drop_img && drop_img->Image_)
					{
						m_LayerActor->addChild(drop_img->GetImage(ix + HALFX - (drop_img->pWidth / 2 ),
							iy + HALFY - (drop_img->pHeight / 2 )));
						//if(pDropItem == g_FocusItem)
						/*	{
						if(pDropItem->sName == g_sGoldName ||
						pDropItem->sName == g_sGamePointName ||
						pDropItem->stdmode == 5 ||
						pDropItem->stdmode == 6 ||
						pDropItem->stdmode == 10 ||
						pDropItem->stdmode == 11)
						{
						m_LayerActor->addChild(drop_img->GetImage(ix + HALFX - (drop_img->pWidth / 2 ),
						iy + HALFY - (drop_img->pHeight / 2 )));
						}else
						{
						cocos2d::Sprite* sprite = drop_img->GetImage(ix + HALFX - (drop_img->pWidth / 2 / 2),
						iy + HALFY - (drop_img->pHeight / 2 / 2));
						sprite->setScale(0.5,0.5);
						m_LayerActor->addChild(sprite);
						}

						}*/
						if(GetTickCount() - pDropItem->FlashTime > g_dwDropItemFlashTime)
						{
							pDropItem->FlashTime = GetTickCount();
							pDropItem->boFlash = true;
							pDropItem->FlashStepTime = GetTickCount();
							pDropItem->FlashStep = 0;
						}
						/// 掉落物品闪光
						if(Shared.boItemFlash)
						{
							if(GetTickCount() - pDropItem->FlashStepTime >= 30)
							{
								pDropItem->FlashStepTime = GetTickCount();
								pDropItem->FlashStep ++;
							}
							if(pDropItem->FlashStep >= 0 && pDropItem->FlashStep < 10)
							{
								TVDImage* img_flash = GetUIImage(50 + pDropItem->FlashStep);
								if(img_flash && img_flash->Image_)
								{
									m_LayerActor->addChild(img_flash->GetImage( ix + HALFX - (img_flash->pWidth / 2),
										iy + HALFY - (img_flash->pHeight / 2)));
								}
							}else
							{
								pDropItem->boFlash = false;
							}

						}

					}
				}
			}
		}

		//没死的对象
		for(int k = m_ActorList.size() - 1;k >= 0;k--)
		{
			actor = m_ActorList[k];
			if(j == actor->m_nRy - actor->m_nDownDrawLevel)
			{
				if(!actor->m_boDeath)
				{
					//头顶文字坐标计算 没加载到图片时用固定的，加载到了用图片的来计算
					actor->m_nSayX = (actor->m_nRx - clientRect->Left)
						* UNITX + defx + actor->m_nShiftX + 24;
					if(actor->m_boDeath)
					{
						actor->m_nSayY = m + UNITY + actor->m_nShiftY 
							+ 16 - 60 +  (actor->m_nDownDrawLevel * UNITY);
					}else
					{
						actor->m_nSayY = m + UNITY + actor->m_nShiftY 
							+ 16 - 96 + (actor->m_nDownDrawLevel * UNITY);
					}
					bDraw = true;
					if((Shared.boHideActor && actor->m_sUserName != g_MySelf->m_sUserName) &&
						(actor->m_btRace == RC_PLAYOBJECT || actor->m_btRace == RC_HORSE))
					{
						bDraw = false;
					}
					if(bDraw)
					{
						int nx = (actor->m_nRx - clientRect->Left) * UNITX + defx;
						int ny = (actor->m_nRy - clientRect->Top) * UNITY + defy + (actor->m_nDownDrawLevel * UNITY);
						bool ret = IsMapMask(actor);
						actor->DrawChr(nx,ny,false, false,m_LayerActor,ret); //画不透明角色，包括自己
					}

				}
			}
		}
		m += UNITY;	
	}

	//画魔法效果 雾

	for(int i = 0;i < (int)m_EffectList.size();i++)
	{
		meff = m_EffectList[i];
		meff->DrawEff(m_LayerActor);
	}
	//地图遮罩蒙板
	//DrawMapMask();

	//绘制文件 血条-
	DrawScreen();

	//绘制顶层UI
	VD_UI::CUIManager::GetInstance()->Draw(m_LayerActor);

	//清除内存多余资源
	ClearMemoryObject();
}

void TPlayScene::ClearMemoryObject()
{
	if(GetTickCount() - m_nLastTime > 10000)
	{
		ClearMapImage();
		ClearMonsterImage();
		ClearHumImage();
		ClearUIImage();
		ClearSound();
		m_nLastTime = GetTickCount();
	}



}
bool TPlayScene::IsMapMask(TActor* actor)
{
	int x =actor->m_nRx;
	int y =actor->m_nRy;
	int nx = 0;
	int ny = 0;
	TRect_* clientrect = &VDMap::GetInstance()->m_ClientRect;
	TRect_ PixesClientrect;
	PixesClientrect.Rect(clientrect->Left * UNITX - m_nDefXX, clientrect->Top * UNITY - m_nDefYY,
		clientrect->Right * UNITX - m_nDefXX,clientrect->Bottom * UNITY - m_nDefYY);
	for(int i = 0; i < (int)VDMap::GetInstance()->m_MaskList.size();i++)
	{
		TMapMaskInfo* MaskInfo = &VDMap::GetInstance()->m_MaskList[i];
		int startx = 0;int starty = 0;
		int endx = 0; int endy = 0;
		if(MaskInfo->InClientRect(PixesClientrect))
		{
			for(int j = 0;j < (int)MaskInfo->Points.size() ;j++)
			{
				TPoint p = MaskInfo->Points[j];
				nx = p.x / UNITX;
				ny = p.y / UNITY;

				if(j == 0) 
				{
					startx = nx;
					starty = ny;
					endx = nx;
					endy = ny;
				}else 
				{
					if( nx < startx ) startx = nx;
					if( ny < starty ) starty = ny;
					if( nx > endx ) endx = nx;
					if( ny > endy ) endy = ny;
				}
			}
			if(x > startx && x < endx &&
				y > starty && y < endy)
			{
				return true;
			}
		}
	}
	return false;
}

//void TPlayScene::DrawMapMask(cocos2d::GLProgram* gl)
//{
//	if(!g_MySelf || !VDMap::GetInstance()->m_Loaded) return;
//	TRect_* clientrect = &VDMap::GetInstance()->m_ClientRect;
//	TRect_ PixesClientrect;
//
//	PixesClientrect.Rect(clientrect->Left * UNITX - m_nDefXX, clientrect->Top * UNITY - m_nDefYY,
//		clientrect->Right * UNITX - m_nDefXX,clientrect->Bottom * UNITY - m_nDefYY);
//	for(int i = 0; i < VDMap::GetInstance()->m_MaskList.size();i++)
//	{
//		TMapMaskInfo* MaskInfo = &VDMap::GetInstance()->m_MaskList[i];
//		if(MaskInfo->InClientRect(PixesClientrect))
//		{
//			float* vertercies = new float[MaskInfo->Points.size() * 2];
//			float* pVertercies = vertercies;
//			
//			float* color = new float[MaskInfo->Points.size() * 4];
//			float * pColor = color;
//			for(int j = 0;j < MaskInfo->Points.size() ;j++)
//			{
//				TPoint p = MaskInfo->Points[j];
//				Vec2 pos;
//				pos.x = p.x - PixesClientrect.Left;
//				pos.y = p.y - PixesClientrect.Top;
//				pos = Director::sharedDirector()->convertToGL(pos);
//				*pVertercies = pos.x;pVertercies++;
//				*pVertercies = pos.y;pVertercies++;
//				*pColor = 0;pColor++;
//				*pColor = 0;pColor++;
//				*pColor = 0;pColor++;
//				*pColor = 150;pColor++;
//			}
//
//			GLProgram* glProgram = gl;
//			//使用此shader
//			glProgram->use();
//			//设置该shader的一些内置uniform,主要是MVP，即model-view-project矩阵
//			glProgram->setUniformsForBuiltins();
//			auto size = Director::getInstance()->getWinSize();
//			//指定将要绘制的三角形的三个顶点，分别位到屏幕左下角，右下角和正中间的顶端
//			float vertercies_[] = { 0,0,   //第一个点的坐标
//				size.width, 0,   //第二个点的坐标
//				size.width / 2, size.height};  //第三个点的坐标
//			//指定每一个顶点的颜色，颜色值是RGBA格式的，取值范围是0-1
//			float color_[] = { 0, 1,0, 1,    //第一个点的颜色，绿色
//				1,0,0, 1,  //第二个点的颜色, 红色
//				0, 0, 1, 1};  //第三个点的颜色， 蓝色
//			//激活名字为position和color的vertex attribute
//			GL::enableVertexAttribs(GL::VERTEX_ATTRIB_FLAG_POSITION | GL::VERTEX_ATTRIB_FLAG_COLOR);
//			//分别给position和color指定数据源
//			
//			glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_POSITION, 2, GL_FLOAT, GL_FALSE, 0, vertercies);
//			glVertexAttribPointer(GLProgram::VERTEX_ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, color);
//			//绘制三角形，所谓的draw call就是指这个函数调用
//			// DrawPrimitives::drawSolidPoly()
//			glDrawArrays(GL_TRIANGLES, 0, MaskInfo->Points.size() - 2);
//			
//			//通知cocos2d-x 的renderer，让它在合适的时候调用这些OpenGL命令
//			CC_INCREMENT_GL_DRAWN_BATCHES_AND_VERTICES(1, MaskInfo->Points.size() - 2);
//			//如果出错了，可以使用这个函数来获取出错信息
//			CHECK_GL_ERROR_DEBUG();
//			delete [] vertercies;
//			delete [] color;
//			
//		}
//	}
//}
void TPlayScene::DrawScreen()
{
	int nx,ny;
	if(GetTickCount() - m_dwFrameTime > 1000)
	{
		m_dwFrameTime = GetTickCount();
		m_dwDrawFrameCount = m_dwFrameCount;
		m_dwFrameCount = 0;
	}
	m_dwFrameCount ++;
	cocos2d::Sprite* sprite;
	if(!g_MySelf)return;
	int n,gn,dearnamey;
	TActor* actor;
	//画所有人物、怪物、npc 等角色头顶文字
	for(int k =m_ActorList.size() - 1;k >= 0;k--)
	{
		actor = m_ActorList[k];
		//妙影无踪隐身，故不显示
		if((actor->m_nState && 0x40000 != 0) && actor != g_MySelf )
		{
			continue;
		}
		if(actor->m_btHorse > 0)n = 28;
		else n = 0;
		if((int)actor->m_sGuildName.length() > 0) gn = 12;
		else gn = 0;
		if((int)actor->m_sDearName.length() > 0) dearnamey = 12;
		else dearnamey = 0;
		if(!actor->m_boDeath &&  ((actor == g_MySelf) || (actor->m_btRace == 98)) ||
			(actor->m_Abil.HP < actor->m_Abil.MaxHP))
		{
			// 血条绘制
			if(actor->m_noInstanceOpenHealth)
			{
				if(GetTickCount() - actor->m_dwOpenHealthStart > actor->m_dwOpenHealthTime)
				{
					actor->m_noInstanceOpenHealth = false;
				}
			}
			//空条
			TVDImage* img = GetUIImage(28);
			if(img && img->Image_ && actor->m_nSayY - 10 < 400 && actor->m_btRace != 50)
			{
				nx = actor->m_nSayX - img->pWidth / 2;
				ny = actor->m_nSayY - 6 - n - gn - dearnamey;
				m_LayerActor->addChild(img->GetImage(nx,ny));
			}
			//显示血量标签
			if(actor->m_Abil.MaxHP > 0 && Shared.boShowNumBlood)
			{
				char sShowBlood[1024] = {0}; 
				sprintf(sShowBlood,"%d/%d",actor->m_Abil.HP,actor->m_Abil.MaxHP);
				DrawFontEx(sShowBlood,actor->m_nSayX - TextWidth(sShowBlood) / 2,
					actor->m_nSayY - 18 - n - gn - dearnamey,0xFFFFFFFF,true);
			}

			//红条
			img = GetUIImage(29);
			if(img && img->Image_)
			{
				float fWidth = (float)img->pWidth * ((float)actor->m_Abil.HP / (float)actor->m_Abil.MaxHP);
				cocos2d::Rect r = cocos2d::Rect(0,0,(int)fWidth,img->pHeight);
				sprite = img->GetImage(actor->m_nSayX - img->pWidth / 2,
					actor->m_nSayY - 6 - n - gn - dearnamey);
				sprite->setTextureRect(r);
				m_LayerActor->addChild(sprite);
			}
		}

		//名字
		std::string uname = actor->m_sRankName + actor->m_sUserName;
		std::string gbk_uname = UTF8ToGBK_string(uname.c_str(),uname.length());
		if(uname.length() <= 0)continue;
		if(actor->m_btRace == RCC_MERCHANT) //NPC名字 一直显示绿色
		{
			DrawFontEx(uname,
				actor->m_nSayX - TextWidth(gbk_uname) / 2,
				actor->m_nSayY - n, GetRGB(250), true);

		}else if(actor->m_btRace == RCC_USERHUMAN) //人物 自己 焦点 或者内挂设置了，就显示名字
		{
			if(actor == g_MySelf || actor == g_FocusCret || Shared.boShowUserName)
			{
				DrawFontEx(uname,
					actor->m_nSayX - TextWidth(gbk_uname) / 2,
					actor->m_nSayY - n, actor->m_nNameColor, true);
			}

		}else //怪物
		{
			if(actor == g_FocusCret)
			{
				DrawFontEx(uname,
					actor->m_nSayX - TextWidth(gbk_uname) / 2,
					actor->m_nSayY - n, actor->m_nNameColor, true);
			}

		}

		//封号图
		int imgidx;
		TVDImage* img;
		if(actor->m_btRace == RCC_USERHUMAN)
		{
			if(!g_boMapAnonymous)
			{
				if(actor->m_btHorse > 0) n = 25;
				else n= 0;
				nx = actor->m_nSayX;
				ny  =actor->m_nSayY - 23 - n - gn - dearnamey;
				for(int i = 0;i < sizeof(actor->m_NameImg) / sizeof(int);i++)
				{
					if(actor->m_NameImg[i] > 0)
					{
						img = GetBagImage(actor->m_NameImg[i]);
						if(img && img->Image_)
						{
							ny -= img->pHeight;
							m_LayerActor->addChild(img->GetImage(nx - img->pWidth / 2,ny));
						}
					}
				}

			}
		}
		//自动走路和打怪  的标题
		if(actor == g_MySelf && !actor->m_boDeath)
		{
			imgidx = -1;
			if(FrmMain::GetInstance()->m_bAutoTimer)
			{
				imgidx = GetTickCount() / 150 % 4 + 820;

			}else if(TGuaJiHelper::GetInstance()->IsStart())
			{
				imgidx = GetTickCount() / 150 % 4 + 830;
			}
			if(imgidx != -1)
			{
				img = GetUIImage(imgidx);
				if(img && img->Image_)
				{
					m_LayerActor->addChild(img->GetImage(actor->m_nSayX - img->pWidth / 2,
						actor->m_nSayY - 30 - img->pHeight));
				}
			}

		}
		//绘制飘血 加减血
		actor->DrawAddBlood(actor->m_nSayX,actor->m_nSayY + 80,m_LayerActor);
	}

	DrawImgMsg();
}

void TPlayScene::DrawImgMsg()
{
	if(m_ShowImgMsgIdx >= 0)
	{
		TVDImage* img = GetUIImage(310 + m_ShowImgMsgIdx);
		if(img && img->Image_)
		{
			unsigned long i =GetTickCount() - m_ShowImgMsgTick;
			if(i > 3000)
			{
				m_ShowImgMsgIdx = -1;
			}
			i = 50 + i / 5;
			int nx;
			int ny;
			//这里有缩放效果的- 再来改吧
			//if(i < 100)
			//{
			//	
			//}else
			//{

			//}
			nx = g_MySelf->m_nSayX - img->pWidth / 2;
			ny = (SCREENHEIGHT - img->pHeight) / 2 - 90; /*补偿下面的主控*/

			m_LayerActor->addChild(img->GetImage(nx,ny));
		}
	}
}
int TPlayScene::FindTargetXYCount(int nX,int nY,int nRange)
{
	int ret = 0;
	int n10 = nRange;
	TActor* actor;
	for(int i = 0;i< (int)m_ActorList.size();i++)
	{
		actor = m_ActorList[i];
		if(!actor->m_boDeath)
		{
			if(actor->m_btRace > RCC_USERHUMAN && actor->m_btRace != RCC_MERCHANT)
			{
				int nC = abs(nX - actor->m_nCurrX) + abs(nY - actor->m_nCurrY);
				if(nC <= n10)
				{
					ret ++;
				}
			}
		}
	}
	return ret;
}

cocos2d::Label* TPlayScene::DrawFontEx(cocos2d::Layer* layer,std::string str,int nx,int ny, 
									  unsigned long Color /* = 0xFFFFFFFF */,bool HaveStroke /* = false */,unsigned long StrokeColor /* = 0xFF000000 */, bool underline /* = false */,
									  bool HaveBackGround/* = false */, unsigned long BackGroundColor /* = 0xFF000000 */)
{

	std::string utf_str = GBKToUTF8_string(str.c_str(),str.length());
	static cocos2d::TTFConfig font("fonts/fangzheng_simsun.ttf");
	cocos2d::Label* label = cocos2d::Label::createWithTTF(font,"");
	cocos2d::Color4B c = HexColorToColor4B(Color);

	label->setTextColor(c);
	label->setString(utf_str);
	cocos2d::Vec2 pos; pos.x = nx; pos.y = ny;
	pos = Director::getInstance()->convertToGL(pos);
	pos.y = pos.y - 12;
	label->setAnchorPoint(cocos2d::Vec2(0,0));
	label->setPosition(pos);
	//画横线
	if(underline)
	{
		cocos2d::DrawNode* node = cocos2d::DrawNode::create();
		node->setAnchorPoint(cocos2d::Vec2(0,0));
		//
		cocos2d::Vec2 endpos = cocos2d::Vec2(nx + TextWidth(str),ny);
		endpos = Director::getInstance()->convertToGL(endpos);
		endpos.y  = endpos.y - 12;

		pos = cocos2d::Vec2(nx,ny);
		pos = Director::getInstance()->convertToGL(pos);
		pos.y = pos.y - 12;
		//node->setPosition(pos);
		node->drawSegment(pos,endpos,0.5,Color4F(0, 1, 0, 1));//Color4F(c.r,c.g,c.b,c.a));
		layer->addChild(node);
	}
	//描边
	//if(HaveStroke)
	//{
	//c = HexColorToColor4B(StrokeColor);
	//label->enableOutline(c,1);
	//阴影效果
	//label->enableGlow(c);

	//}
	layer->addChild(label);
	return label;
}
void TPlayScene::DrawFontEx(std::string str,int nx,int ny,unsigned long color /* = 0xFFFFFFFF */, bool HaveStroke /* = false */,int StrokeColor /* = 0xFF000000 */)
{

	std::vector<cocos2d::Label*>::iterator  it;
	bool bFind = false;
	Label* label = nullptr;
	for(it = m_LabelList.begin();it != m_LabelList.end();it++)
	{
		label = *it;
		if(!label->getParent())
		{
			bFind = true;
			break;
		}
	}
	std::string text = str;

	if(!bFind)
	{
		static cocos2d::TTFConfig font("fonts/fangzheng_simsun.ttf",12);
		label = cocos2d::Label::createWithTTF(font,"");

		label->retain();
		m_LabelList.push_back(label);
	}


	cocos2d::Color4B c = HexColorToColor4B(color);

	label->setTextColor(c);
	label->setString(text);
	Vec2 pos;
	pos.x = nx;pos.y = ny;
	pos = Director::getInstance()->convertToGL(pos);
	pos.y = pos.y - 12;
	label->setAnchorPoint(Vec2(0,0));
	label->setPosition(pos.x,pos.y);
	m_LayerActor->addChild(label);
}

//cocos2d::Color4B TPlayScene::HexColorToColor4B(unsigned long color)
//{
//	Color4B ret;
//	ret.r = color & 255;
//	ret.a = color >> 24;
//	ret.b = (color>> 16) & 255;
//	ret.g = (color>>8) & 255;
//
//	return ret;
//}
void TPlayScene::DrawTileMap()
{

	m_LayerTitle->removeAllChildrenWithCleanup(true);
	int tx,ty;
	tx = UNITX * 3 + g_MySelf->m_nShiftX;
	ty = UNITY * 3 + g_MySelf->m_nShiftY;
	VDMap* map = VDMap::GetInstance();
	TRect_* clientRect = &map->m_ClientRect;

	///绘制底层贴图
	int nx,ny,nw,nh,sx,sy;
	TVDImage* img = GetMiniMapImage(map->m_sOldMap);
	if(img)
	{
		nx = int(clientRect->Left / map->Header.Width * img->pWidth);
		ny = int(clientRect->Top / map->Header.Height * img->pHeight);
		nw = int(clientRect->Right - clientRect->Left) / map->Header.Width * img->pWidth;
		nh = int(clientRect->Bottom - clientRect->Top) / map->Header.Height * img->pHeight;
		sx = int((clientRect->Bottom - clientRect->Top) / map->Header.Width * img->pWidth);
		sy = int(abs(MIN(0,ny)) * map->Header.Height * UNITY / img->pHeight);
		nx = MAX(0,nx);
		ny = MAX(0,ny);
		nw = MIN(img->pWidth,nw);
		ny = MIN(img->pHeight,ny);
		//画图
		//cocos2d::Sprite* sprite = cocos2d::Sprite::createWithTexture(img->TEX);
		//sprite->initWithTexture(img->TEX);

		//m_LayerTitle->addChild(sprite);

	}
	//地砖
	for(int j = (clientRect->Top - 12);j < (clientRect->Bottom + 3);j++)
	{
		for(int i = (clientRect->Left - 12);i < clientRect->Right + 3;i++)
		{
			if((i % 2 == 0) && (j % 2 == 0))
			{
				if((i >= 0) && (j >= 0) && (i < map->Header.Width) &&
					(j < map->Header.Height))
				{
					//计算绘制屏幕像素坐标
					nx = (i - clientRect->Left) * UNITX + m_nDefXX;
					ny = (j - clientRect->Top) * UNITY + m_nDefYY;
					int nImgNumber = map->m_MArr[i][j].BkImg & 0x7FFF;
					if(nImgNumber > 0)
					{
						nImgNumber --;
						TVDImage* tileimg = GetMapImage(map->m_MArr[i][j].BkAree,nImgNumber);
						if(tileimg)
						{
							//判断图片会绘制到屏幕以内，才进行绘制，减少浪费
							if(nx < SCREENWIDTH && ny < SCREENHEIGHT
								&& nx + tileimg->pWidth > 0 && ny + tileimg->pHeight > 0)
							{
								//dx坐标转换到gl坐标
								//Vec2 pos;
								//pos.x = nx;
								//pos.y = ny;
								//pos = Director::getInstance()->convertToGL(pos);
								//pos.y = pos.y - tileimg->TexHeight;
								//tileimg->Image_->setPosition(pos);
								//tileimg->SetSpritePostion(nx,ny);
								m_LayerTitle->addChild(tileimg->GetImage(nx,ny));
							}	
						}
					}
				}
			}
		}
	}

}

void TPlayScene::CXYfromMouseXY(int x,int y,int &ccx,int &ccy)
{
	VDMap* map = VDMap::GetInstance();
	ccx = int((x - m_nDefXX) / UNITX) + map->m_ClientRect.Left;
	ccy = int((y - m_nDefYY) / UNITY) + map->m_ClientRect.Top;
}
void TPlayScene::ClearHumImage()
{

	std::vector<std::string> dellist;
	dellist.clear();
	std::map<std::string,TVDImageDatas*> ::iterator it;
	for(it = g_HumImagesHash.begin(); it != g_HumImagesHash.end();it++)
	{

		if(it->second->FreeOldMemorys())
		{
			dellist.push_back(it->first);
		}
		//if(GetTickCount() - curTime > 500) //只给五百毫秒时间清除
		//{
		//	break;
		//}
	}
	if(dellist.size() > 0)
	{
		std::vector<std::string>::iterator _it;
		for(_it = dellist.begin(); _it != dellist.end();_it++)
		{
			std::string key = *_it;
			it = g_HumImagesHash.find(key);
			if(it != g_HumImagesHash.end())
			{

				it->second->Destory();
				g_HumImagesHash.erase(it);
			}

		}
	}
}

void TPlayScene::ClearUIImage()
{
	std::vector<std::string> dellist;
	dellist.clear();
	std::map<std::string,TVDImageDatas*> ::iterator it;
	for(it = g_UIImageHash.begin(); it != g_UIImageHash.end();it++)
	{

		if(it->second->FreeOldMemorys())
		{
			dellist.push_back(it->first);
		}
		//if(GetTickCount() - curTime > 500) //只给五百毫秒时间清除
		//{
		//	break;
		//}
	}
	if(dellist.size() > 0)
	{
		std::vector<std::string>::iterator _it;
		for(_it = dellist.begin(); _it != dellist.end();_it++)
		{
			std::string key = *_it;
			it = g_UIImageHash.find(key);
			if(it != g_UIImageHash.end())
			{
				it->second->Destory();
				g_UIImageHash.erase(it);
			}

		}
	}
}
void TPlayScene::ClearMonsterImage()
{
	std::vector<std::string> dellist;
	dellist.clear();
	std::map<std::string,TVDImageDatas*> ::iterator it;
	for(it = g_WMonImagesHash.begin(); it != g_WMonImagesHash.end();it++)
	{

		if(it->second->FreeOldMemorys())
		{
			dellist.push_back(it->first);
		}
		//if(GetTickCount() - curTime > 500) //只给五百毫秒时间清除
		//{
		//	break;
		//}
	}
	if(dellist.size() > 0)
	{
		std::vector<std::string>::iterator _it;
		for(_it = dellist.begin(); _it != dellist.end();_it++)
		{
			std::string key = *_it;
			it = g_WMonImagesHash.find(key);
			if(it != g_WMonImagesHash.end())
			{

				it->second->Destory();
				g_WMonImagesHash.erase(it);
			}

		}
	}


}
void TPlayScene::ClearMapImage()
{
	std::vector<std::string> dellist;
	dellist.clear();
	//int curTime = GetTickCount();
	std::map<std::string,TVDImageDatas*> ::iterator it;
	for(it = g_MapVDDHash.begin(); it != g_MapVDDHash.end();it++)
	{
		if(it->second->FreeOldMemorys())
		{
			dellist.push_back(it->first);
		}
		//if(GetTickCount() - curTime > 500) //只给五百毫秒时间清除
		//{
		//	break;
		//}
	}
	if(dellist.size() > 0)
	{
		std::vector<std::string>::iterator _it;
		for(_it = dellist.begin(); _it != dellist.end();_it++)
		{
			std::string key = *_it;
			it = g_MapVDDHash.find(key);
			if(it != g_MapVDDHash.end())
			{

				it->second->Destory();
				g_MapVDDHash.erase(it);
			}

		}
	}


}

TActor* TPlayScene::NewActor(int chrid,unsigned short cx,unsigned short cy,
							 unsigned short cdir, int cfeature,int cstate, int featureEx)
{
	TActor* Actor = FindActor(chrid);
	if(Actor) 
	{
		return Actor;
	}

	if(IsChangingFace(chrid))
	{
		return nullptr;
	}
	unsigned char bfeature =  RACEfeature(cfeature);
	switch(bfeature)
	{
	case 0:
		{
			Actor = new THumActor;
			break;
		}
	case 17:
	case 19:
	case 20:
		{
			Actor = new TCatMon;
			break;
		}
	case 45:
		{
			Actor = new TArcherMon;
			break;
		}
	case 50:
		{
			Actor = new TNpcActor;
			break;
		}
	case 200:
		{
			Actor = new TPlant;
			break;
		}
	case 201:
		{
			Actor = new TMine;
			break;
		}
	default:
		{
			Actor = new TActor;
		}
	}
	{
		Actor->m_nRecogId = chrid;
		Actor->m_nCurrX = cx;
		Actor->m_nCurrY = cy - 1;
		Actor->m_nRx = Actor->m_nCurrX;
		Actor->m_nRy = Actor->m_nCurrY;
		Actor->m_btDir = cdir;
		Actor->m_nFeature = cfeature;
		Actor->m_btRace = RACEfeature(cfeature);
		char nbHair = HAIRfeature(cfeature);
		Actor->m_btHair = nbHair >> 7;
		Actor->m_bWings = nbHair & 0x7F;
		Actor->m_btDress = DRESSfeature(cfeature);
		Actor->m_btWeapon = WEAPONfeature(cfeature);
		Actor->m_wAppearance = APPRfeature(cfeature);
		Actor->m_nFeatureEx = featureEx;

		/////// 20120401 头发数据用作他用/////////////
		if(Actor->m_btHair > 0)
		{
			Actor->m_bMeditation = true;
		}else Actor->m_bMeditation = false;
		///  ////////////////
		if(Actor->m_btRace > 0 && Actor->m_bWings == 0)
		{
			if(Actor->m_wAppearance > 10000)
			{
				Actor->m_btDir = (Actor->m_wAppearance - 10000) / 100;
				Actor->m_btDress = Actor->m_wAppearance % 100;
				Actor->m_wAppearance = 10000;
			}
		}

		Actor->m_Action = nullptr;
		if(Actor->m_btRace == 0)
		{
			Actor->m_btSex = Actor->m_btDress % 2;
		}else Actor->m_btSex = 0;
		Actor->m_nState = cstate;
		Actor->m_SayingArr = "";

		if(g_MySelf && Actor->m_sUserName != g_MySelf->m_sUserName 
			&& Actor->m_btRace != 50)
		{
			CNetClient::GetInstance()->sendDefMsg(CM_ACTORHP,Actor->m_nRecogId,0,0,0);
		}
		m_ActorList.push_back(Actor);
		return Actor;
	}
}


bool TPlayScene::IsChangingFace(int recogid)
{

	std::vector<int>::iterator it;
	for(it = g_ChangeFaceReadyList.begin();it != g_ChangeFaceReadyList.end();it++)
	{
		if(*it == recogid)
		{
			return true;
		}
	}
	return false;

}


void TPlayScene::ProcessNetEvent()
{
	TNetEvent* e;
	for(int i = 0;i < MAX_NETEVENT_COUNT;i ++)
	{
		e = CNetClient::GetInstance()->GetRecvMsg()->GetNetEventData(i);
		if(!e)
		{
			break;
		}
		//处理特殊封包
		if(e->event_type == NETPACKET_SPECIAL)
		{

			FrmMain::GetInstance()->ProcessSpecialMsg(e->Body.c_str());
			continue;;
		}
		tagDefaultMessage* msg;
		msg = &e->msg;
		switch(msg->Ident)
		{
		case SM_NEWMAP:
		case SM_CHANGEMAP:
			{
				SendMsg(SM_NEWMAP,0,msg->Param,msg->Tag,msg->Serise,0,0,e->Body.c_str());
				break;
			}
		case SM_LOGON:
			{

				TMessageBodyWL wl;
				fnDecode6BitBufA((char*)e->Body.c_str(),(char*)&wl,sizeof(TMessageBodyWL));
				//fnEncode6BitBufA(, , 
				//	strlen(e->Body.c_str()),);
				SendMsg(SM_LOGON,msg->Recog,msg->Param/*x*/,msg->Tag/*y*/,
					msg->Serise/*dir*/,wl.lParam1,wl.lParam2,"");
				//切换到游戏状态
				TDScreen::GetInstance()->ChangeScene(stPlayGame);
				break;
			}
		case SM_SPELL:
			{
				//UseMagicSpell(Msg.Recog {who}, Msg.series {effectnum}, Msg.param {tx}, Msg.tag {y}, Str_ToInt(body, 0));
				int magic_id = 0;
				magic_id = atoi(e->Body.c_str());
				FrmMain::GetInstance()->UseMagicSpell(msg->Recog/*who*/,msg->Serise/*effectnum*/,msg->Param/*tx*/,msg->Tag/*y*/,magic_id);
				break;
			}
		case SM_WALK:
		case SM_RUSH:
		case SM_RUSHKUNG:
			{

				if(e->Body.length() < sizeof(TCharDesc))
				{
					CCLOG("sm_walk net error ! length%d",e->Body.length());
					break;
				}
				TCharDesc desc;
				fnDecode6BitBufA((char*)e->Body.c_str(),(char*)&desc,sizeof(TCharDesc));
				if(msg->Ident == SM_RUSH)
				{
					g_dwLatestRushRushTick = GetTickCount();
				}
				//会出现g_MySelf的情况-
				if(!g_MySelf || (g_MySelf && msg->Recog == g_MySelf->m_nRecogId))
				{
					break;
				}
				if(msg->Recog != g_MySelf->m_nRecogId || msg->Ident == SM_RUSH
					|| msg->Ident == SM_RUSHKUNG)
				{
					int nx = LOWORD_(msg->Param);
					int ny = HIWORD_(msg->Param);
					SendMsg(msg->Ident, msg->Recog,nx,ny,msg->Serise /*{dir+light}*/,desc.feature,msg->Tag,
						"",
						desc.featureEx
						);
				}

				break;

			}
		case SM_RUN:
		case SM_HORSERUN:
			{
				TCharDesc desc;
				fnDecode6BitBufA((char*)e->Body.c_str(),(char*)&desc,sizeof(TCharDesc));
				int nx = LOWORD_(msg->Param);
				int ny = HIWORD_(msg->Param);
				if(!g_MySelf || (g_MySelf && msg->Recog == g_MySelf->m_nRecogId))
				{
					break;
				}
				if(msg->Recog != g_MySelf->m_nRecogId)
				{
					SendMsg(msg->Ident,msg->Recog,nx,ny,msg->Serise,desc.feature,msg->Tag,
						"",desc.featureEx);
				}
				break;
			}
		case SM_HIT:                             //14
		case SM_HEAVYHIT:                     //15
		case SM_POWERHIT:                      //18
		case SM_LONGHIT:                       //19
		case SM_WIDEHIT:                       //24
		case SM_BIGHIT:                        //16
		case SM_FIREHIT:                       //8
		case SM_CRSHIT: 
		case SM_34SKILLHIT:
		case SM_REMOTEHIT:
		case SM_35SKILLHIT: 
		case SM_103SKILLHIT:
		case SM_TWINHIT:
			{
				char dest[2048] = {0};
				if(!g_MySelf || (g_MySelf && msg->Recog == g_MySelf->m_nRecogId))
				{
					break;
				}
				if(msg->Ident != g_MySelf->m_nRecogId)
				{
					TActor* actor = FindActor(msg->Recog);
					if(actor)
					{
						if(msg->Ident == SM_REMOTEHIT)
						{
							//待定
							DecodeString((char*)e->Body.c_str(),dest,sizeof(dest));
							std::string str = dest;

						}
						actor->SendMsg(msg->Ident,msg->Param,msg->Tag,msg->Serise,0,0,"",0);
						if(msg->Ident == SM_HEAVYHIT)
						{
							if(e->Body.length() > 0)
							{
								actor->m_boDigFragment = true;
							}
						}
					}

				}
				break;
			}
		case SM_SYSMESSAGE:
			{
				char src[1024]= {0};
				GBKToUTF8((char*)e->Body.c_str(),e->Body.length(),src,sizeof(src));
				CCLOG("system message: %s",src);
				break;
			}
		case SM_TURN:
			{
				std::string str = e->Body.c_str();
				TCharDesc desc;
				std::string data = "";

				if((int)e->Body.length() > GetCodeMsgSize(sizeof(TCharDesc) * 4 / 3))
				{
					char _data[1024]={0};
					char* pData = (char*)&e->Body.c_str()[GetCodeMsgSize(sizeof(TCharDesc) * 4 / 3) + 1];
					memcpy(_data,pData
						,e->Body.length());
					char dest[1024]={0};
					fnDecode6BitBufA(_data,dest,sizeof(dest));
					std::string data1 =dest;
					str = GetValidStr3Ex(data1,data1,'/');
					data = data1;
				}
				fnDecode6BitBufA((char*)e->Body.c_str(),(char*)&desc,sizeof(TCharDesc));
				int nx = LOWORD_(msg->Param);
				int ny = HIWORD_(msg->Param);
				SendMsg(SM_TURN,msg->Recog,nx,ny,msg->Serise,desc.feature,msg->Tag,"",desc.featureEx);
				if(data.length() > 0)
				{
					TActor* actor = FindActor(msg->Recog);
					if(actor)
					{
						actor->ProcName(data.c_str());
						if(str.find('/') < 0)
						{
							actor->m_nNameColor = GetRGB(atoi(str.c_str()));
						}else
						{
							std::string rdstr;
							str = GetValidStr3Ex(str,rdstr,'/');
							actor->m_nNameColor = GetRGB(atoi(rdstr.c_str()));
							actor->m_nHalo = atoi(str.c_str());
						}

					}
				}
				break;
			}
		case SM_FEATURECHANGED:
			{

				SendMsg(msg->Ident,msg->Recog,0,0,0,MAKELONG_(msg->Param,msg->Tag),msg->Serise,e->Body.c_str());
				break;
			}
		case SM_HIDE:
		case SM_GHOST:
		case SM_DISAPPEAR:
			{
				if(!g_MySelf || (g_MySelf && msg->Recog == g_MySelf->m_nRecogId))
				{
					break;
				}
				if(g_MySelf->m_nRecogId != msg->Recog)
				{
					SendMsg(SM_HIDE,msg->Recog,msg->Param/*x*/,msg->Tag/*y*/,0,0,0,"");
				}
				break;
			}
		case SM_USERNAME:
			{
				TActor* actor =FindActor(msg->Recog);
				if(actor)
				{
					actor->m_nNameColor = GetRGB(msg->Param);
					actor->ProcName(e->Body.c_str());
					if(actor == g_MySelf)
					{
						memcpy(Shared.name,g_MySelf->m_sUserName.c_str(),
							g_MySelf->m_sUserName.length());
					}
				}

				break;
			}
		case SM_DEATH:
		case SM_NOWDEATH:
			{
				std::string str;
				std::string str1;
				str = GetValidStr3Ex(e->Body.c_str(),str1,'/');
				TCharDesc desc;
				fnDecode6BitBufA((char*)str1.c_str(),(char*)&desc,sizeof(TCharDesc));
				TActor* actor = FindActor(msg->Recog);
				int nx = LOWORD_(msg->Param);
				int ny = HIWORD_(msg->Param);
				if(actor)
				{
					actor->SendMsg(msg->Ident,nx,ny,msg->Serise,desc.feature,msg->Tag,"",0);
					actor->m_Abil.HP = 0;
					if(actor == g_MySelf)
					{
						if(str.length() > 0)
						{
							str = GetValidStr3Ex(str,str1,'/');
							if(str.length() > 0 && str1.length() > 0 &&
								IsStringNumber(str.c_str()) && IsStringNumber(str1.c_str()))
							{
								g_ReAliveFreeCount = atoi(str1.c_str());
								g_ReAliveNeedGameGold = atoi(str.c_str());
							}
						}
					}
				}else
				{
					SendMsg(SM_DEATH,
						msg->Recog, nx,ny,
						msg->Serise /*{damage}*/, desc.feature, msg->Tag , "");
				}
				break;
			}
		case SM_HEALTHSPELLCHANGED: //hp /mp 变化
			{
				FrmMain::GetInstance()->ClientGetHealthSpellChanged(msg);
				break;
			}
		case SM_MISS: //躲避
			{
				TActor* actor = FindActor(msg->Recog);
				if(actor)
				{
					FrmMain::GetInstance()->ShowAddBlood(actor,999999999);
				}
				break;
			}
		case SM_STRUCK: //也会变化hp mp
			{
				FrmMain::GetInstance()->ClientGetSTRUCK(msg,e->Body);
				break;
			}
		case SM_ACTORHP: //周围血量信息
			{
				FrmMain::GetInstance()->ClientGetActorHP(msg,e->Body);
				break;
			}
		case SM_CLEAROBJECTS: //清空所有对象- 用于地图传送
			{
				CleanObjects();
				//		g_boMapMoving = true;
				break;
			}
		case SM_CHARSTATUSCHANGED:
			{
				SendMsg(msg->Ident,msg->Recog,0,0,0,MAKELONG_(msg->Param,msg->Tag),msg->Serise,"");
				break;
			}
		case SM_ABILITY:
			{
				g_MySelf->m_nGold = msg->Recog;
				g_MySelf->m_btJob = LOBYTE_(msg->Param);
				g_MySelf->m_nGameGold = MAKELONG_(msg->Tag,msg->Serise);
				fnDecode6BitBufA((char*)e->Body.c_str(),(char*)&g_MySelf->m_Abil,sizeof(TAbility));
				break;
			}
		case SM_SUBABILITY:
			{
				unsigned long recog = msg->Recog;
				g_nMyAntiMagic = LOBYTE_(LOWORD_(recog));
				g_nCrit = HIBYTE_(LOWORD_(recog));
				g_nMyHitPoint = LOBYTE_(HIWORD_(recog));
				g_nMySpeedPoint = HIBYTE_(HIWORD_(recog));
				g_nMyAntiPoison = LOBYTE_(LOWORD_(msg->Param));
				g_nMyPoisonRecover = HIBYTE_(LOWORD_(msg->Param));
				g_nMyHealthRecover = LOBYTE_(HIWORD_(msg->Param));
				g_nMySpellRecover = HIBYTE_(HIWORD_(msg->Param));
				g_nPKPoint = LOWORD_(msg->Tag);
				g_nProtect = HIWORD_(msg->Tag);
				g_VIPLevel = LOWORD_(msg->Serise);
				fnDecode6BitBufA((char*)e->Body.c_str(),(char*)&g_SubAbil,sizeof(TSubAbilityExt));
				break;
			}
		case SM_ADJUST_BONUS:
			{
				FrmMain::GetInstance()->ClientGetAdjustBonus(msg,e->Body);
				break;
			}
		case SM_CHANGELIGHT:
			{
				TActor* actor = FindActor(msg->Recog);
				if(actor)
				{
					actor->m_nChrLight = msg->Param;
				}
				break;
			}
		case SM_SERVERCONFIG:
			{
				FrmMain::GetInstance()->Client_ServerConfig(msg);
				break;
			}
		case SM_AREASTATE:
			{
				g_nAreaStateValue = msg->Recog;
				break;
			}
		case SM_MAPDESCRIPTION:
			{
				FrmMain::GetInstance()->Client_MapDescription(msg,e->Body);
				break;
			}
		case SM_GAMEGOLDNAME:
			{
				FrmMain::GetInstance()->Client_GameGoldName(msg,e->Body);
				break;
			}
		case SM_MAGICFIRE:
			{
				int param;
				fnDecode6BitBufA((char*)e->Body.c_str(),(char*)&param,sizeof(int));

				FrmMain::GetInstance()->Client_MagicFire(msg->Recog,LOBYTE_(msg->Serise),HIBYTE_(msg->Serise),
					msg->Param,msg->Tag,param);
				break;
			}
		case SM_ADDMAGIC:
			{
				FrmMain::GetInstance()->Client_AddMagic(e->Body);
				break;
			}
		case SM_SENDMYMAGIC:
			{
				FrmMain::GetInstance()->Client_SendMyMagic(e->Body);
				break;
			}
		case SM_SHOWEVENT:
			{
				FrmMain::GetInstance()->Client_ShowEvent(msg,e->Body);
				break;
			}
		case SM_HIDEEVENT:
			{
				TClEventManager::GetInstance()->DelEventById(msg->Recog);
				break;
			}
		case SM_MERCHANTSAY:
			{
				FrmMain::GetInstance()->Client_MerchantSay(msg,e->Body);

				break;
			}
		case SM_QUERYCHR:
			{
				FrmMain::GetInstance()->Client_QueryChr(msg,e->Body);
				break;
			}
		case SM_NEWCHR_SUCCESS:
			{
				std::string sname = TCreateScreen::GetInstance()->tempUserInfo.name;
				CNetClient::GetInstance()->chrname = sname;
				CNetClient::GetInstance()->GetSendMsg()->SelectChr(sname.c_str());
				break;
			}
		case SM_NEWCHR_FAIL:
			{
				TCreateScreen::GetInstance()->SetTips(msg->Recog);
				break;
			}
		case SM_DELCHR_SUCCESS:
			{
				CNetClient::GetInstance()->GetSendMsg()->QuestChr();
				break;
			}
		case SM_DELCHR_FAIL:
			{
				//TLoginScene::GetInstance()->SetDelChrFailTips();
				break;
			}
		case SM_ITEMSHOW:
			{
				FrmMain::GetInstance()->Client_ItemShow(msg,e->Body);
				break;
			}
		case SM_ITEMHIDE:
			{
				FrmMain::GetInstance()->Client_ItemHide(msg,e->Body);
				break;
			}
		case SM_BAGITEMS:
			{
				FrmMain::GetInstance()->Client_BagItems(msg,e->Body);
				break;
			}
		case SM_SENDUSEITEMS:
			{
				FrmMain::GetInstance()->Client_SendUseItems(msg,e->Body);
				break;
			}
		case SM_WALKTO:
			{
				FrmMain::GetInstance()->Client_WalkTo(msg,e->Body);
				break;
			}
		case SM_MERCHANTDLGCLOSE:
			{
				FrmMain::GetInstance()->HideDialog(DIALOG_TYPE::NPC);
				break;
			}
		case SM_TAKEON_OK:
			{
				FrmMain::GetInstance()->Client_TakeOnOK(msg,e->Body);
				break;
			}
		case SM_UPDATEITEM:
			{
				FrmMain::GetInstance()->Client_UpdateItem(msg,e->Body);
				break;
			}
		case SM_KILLMON:
			{
				FrmMain::GetInstance()->Client_KillMon(msg,e->Body);
				break;
			}
		case SM_WINEXP:
			{
				g_MySelf->m_Abil.Exp = msg->Recog;
				break;
			}
		case SM_LEVELUP:
			{
				FrmMain::GetInstance()->Client_LevelUp(msg,e->Body);
				break;
			}
		case SM_WEIGHTCHANGED:
			{
				g_MySelf->m_Abil.Weight = msg->Recog;
				g_MySelf->m_Abil.WearWeight = msg->Param;
				g_MySelf->m_Abil.HandWeight = msg->Tag;
				break;
			}
		case SM_ADDITEM:
			{
				FrmMain::GetInstance()->Client_AddItem(msg,e->Body);
				break;
			}
		case SM_SENDJINGMAI:
			{
				FrmMain::GetInstance()->Client_SendJingMai(msg,e->Body);
				break;
			}
		case SM_CHANGENAMECOLOR:
			{
				FrmMain::GetInstance()->Client_ChangeNameColor(msg,e->Body);
				break;
			}
		case SM_MAGICEFF:
			{
				FrmMain::GetInstance()->Client_MagicEff(msg,e->Body);
				break;
			}
		case SM_DURACHANGE:
			{
				FrmMain::GetInstance()->Client_DuraChange(msg,e->Body);
				break;
			}
		case SM_MAGIC_LVEXP:
			{
				FrmMain::GetInstance()->Client_MagicLvExp(msg,e->Body);
				break;
			}
		case SM_GETICONS:
			{
				FrmMain::GetInstance()->Client_GetIcons(msg,e->Body);
				break;
			}
		case SM_TASK:
			{
				FrmMain::GetInstance()->Client_Task(msg,e->Body);
				break;
			}
		case SM_SHOWIMGMSG:
			{
				m_ShowImgMsgIdx = msg->Recog;
				m_ShowImgMsgTick = GetTickCount();
				m_ShowImgMsgTop = 0;
				break;
			}
		case SM_SPELLNEED:
			{
				FrmMain::GetInstance()->Client_SpeelNeed(msg,e->Body);
				break;
			}
		}

	}

}

void TPlayScene::SendMsg(int ident,int chrid,int x,int y,int cdir,int Feature,int State,const char* str,int Fetureex /* = 0 */)
{
	std::string str_ = str;
	std::string str1 = "";
	switch(ident)
	{
	case SM_NEWMAP:
	case SM_CHANGEMAP:
		{
			VDMap::GetInstance()->ChangeMap(str);

			FrmMain::GetInstance()->reCurMapGate(); //重新加载当前地图连接点

			//清理地上效果- 火墙
			TClEventManager::GetInstance()->ClearEvents();
			if(ident == SM_NEWMAP && g_MySelf )
			{
				g_MySelf->m_nCurrX = x;
				g_MySelf->m_nCurrY = y;
				g_MySelf->m_nRx = x;
				g_MySelf->m_nRy = y;
				//DelActor(g_MySelf);

			}
			break;
		}
	case SM_LOGON:
		{
			std::string sLog = "recv SM_LOGON";
			g_AnroidLog.push_back(sLog);
			TActor* actor = FindActor(chrid);
			if(!actor)
			{
				actor = NewActor(chrid,x,y,LOBYTE_(cdir),Feature,State);
				actor->m_nChrLight = HIBYTE_(cdir);
				int cdir_ = LOBYTE_(cdir);		
				actor->SendMsg(SM_TURN,x,y,cdir,Feature,State,"",0);

			}
			if(g_MySelf)
			{
				delete g_MySelf;
				g_MySelf = nullptr;
			}
			g_MySelf = (THumActor*)actor;
			CNetClient::GetInstance()->GetSendMsg()->SendLogon();

			break;
		}
	case SM_HIDE:
		{
			TActor* actor = FindActor(chrid);
			if(actor)
			{
				if(actor->m_boDelActionAfterFinished || actor->m_nWaitForRecogId != 0)
				{
					return;
				}

				DelActor(actor);
			}
			break;
		}

	default: //出现其他对象
		{
			TActor* actor = FindActor(chrid);
			if(ident == SM_TURN || ident == SM_RUN || ident == SM_HORSERUN || ident == SM_WALK
				|| ident == SM_BACKSTEP || ident == SM_DEATH || ident == SM_SKELETON || ident == SM_DIGUP
				|| ident == SM_ALIVE || ident == SM_CREATEHERO)
			{
				if(!actor)
				{

					str_ = GetValidStr3Ex(str_,str1,'/');
					if(str_.length() <= 0)
					{
						actor = NewActor(chrid, x, y, LOBYTE_(cdir), Feature, State, Fetureex);
					}else
					{
						actor = NewActor(chrid,x,y,LOBYTE_(cdir),Feature,State,Fetureex);
					}
					if(actor)
					{
						if(ident == SM_WALK || ident == SM_RUN || ident == SM_HORSERUN
							|| ident == SM_TURN)
						{
							actor->m_btJob = HIBYTE_(cdir);
						}else
						{
							actor->m_nChrLight = HIBYTE_(cdir);
						}
						cdir = LOBYTE_(cdir);
						if(ident == SM_SKELETON)
						{
							actor->m_boDeath = true;
							actor->m_boSkeleton = true;
						}
					}
				}
			}
			if(!actor)
			{
				return;
			}
			switch(ident)
			{
			case SM_FEATURECHANGED:
				{
					actor->m_nFeature = Feature;
					actor->m_nFeatureEx = State;
					actor->FeatureChanged();
					if(str_.length() > 0)
					{
						if(str_.find('/') >= 0)
						{
							str_ = GetValidStr3Ex(str_,str1,'/');
							actor->m_btSex = atoi(str1.c_str());
							actor->m_nHalo = atoi(str_.c_str());

						}else
						{
							actor->m_btSex = atoi(str_.c_str());
						}
					}
					break;
				}
			case SM_CHARSTATUSCHANGED:
				{
					actor->m_nState = Feature;
					actor->m_nHitSpeed = State;
					break;
				}
			case SM_EATITEM:
				{
					actor->m_nEatItemIndex = State;
					actor->IsEatItem = true;
					actor->EatItemTime = GetTickCount();
					actor->EatItemNum = 0;
					break;
				}
			default:
				{
					actor->SendMsg(ident, x, y, cdir, Feature, State, "", 0);
				}
			}

		}
	}
}
TActor* TPlayScene::FindNPC(std::string sName)
{
	std::vector<TActor*>::iterator it;
	std::string sName_Utf8 = GBKToUTF8_string(sName.c_str(),sName.length());
	for(it = m_ActorList.begin();it != m_ActorList.end();it++)
	{
		TActor* actor = (TActor*)*it;
		if(actor->m_sUserName == sName_Utf8)
		{
			return actor;
		}
	}
	return nullptr;
}
TActor* TPlayScene::FindActor(int id)
{
	std::vector<TActor*>::iterator it;
	for(it = m_ActorList.begin();it != m_ActorList.end();it++)
	{
		TActor* actor = (TActor*)*it;
		if(actor->m_nRecogId == id)
		{
			return *it;
		}
	}
	return nullptr;
}

void TPlayScene::DelActor(TActor* actor)
{
	std::vector<TActor*>::iterator it;
	for(it = m_ActorList.begin();it != m_ActorList.end();it++)
	{
		TActor* a = (TActor*)*it;
		if(a == actor)
		{
			a->m_dwDeleteTime = GetTickCount();
			g_FreeActorList.push_back(a);
			m_ActorList.erase(it);
			break;
		}
	}

}

bool TPlayScene::CanRun(int sx,int sy,int ex,int ey)
{
	bool Result = false;
	int  ndir = GetNextDirection(sx, sy, ex, ey);
	int rx = sx;
	int ry = sy;
	GetNextPosXY(ndir, rx, ry);
	if(VDMap::GetInstance()->CanMove(rx,ry) && VDMap::GetInstance()->CanMove(ex,ey))
	{
		Result = true;
	}else
	{
		Result = false;
	}

	if(CanWalkEx(rx,ry) && CanWalkEx(ex,ey))
	{
		Result = true;
	}else Result = false;
	return Result;
}
bool TPlayScene::CanWalk(int mx,int my)
{

	if(VDMap::GetInstance()->CanMove(mx,my))
	{
		return  !CrashManEx(mx,my);
	}
	return false;

}

bool TPlayScene::CanWalkEx(int mx,int my)
{
	bool Result = false;
	if(VDMap::GetInstance()->CanMove(mx,my))
	{
		Result = !CrashManEx(mx,my);
	}
	return Result;
}

bool TPlayScene::CrashMan(int mx,int my)
{
	TActor* a = nullptr;
	for(int i  = 0;i < (int)m_ActorList.size();i++)
	{
		a = m_ActorList[i];
		if(a->m_boVisible && a->m_boHoldPlace
			&& !a->m_boDeath && a->m_nCurrX == mx 
			&& a->m_nCurrY == my)
		{
			return true;
		}
	}
	return false;
}
bool TPlayScene::CrashManEx(int mx,int my )
{

	TActor* Actor;
	for(int i = 0;i < (int)m_ActorList.size();i++)
	{
		Actor = m_ActorList[i];
		if (Actor->m_boVisible && Actor->m_boHoldPlace && !Actor->m_boDeath && 
			Actor->m_nCurrX == mx && Actor->m_nCurrY == my) 
		{
			if (Actor->m_btRace == RCC_USERHUMAN && g_boCanRunHuman)
			{
				continue;
			}
			if(Actor->m_btRace == RCC_MERCHANT && g_boCanRunNpc)
			{
				continue;;
			}
			if((Actor->m_btRace > RCC_USERHUMAN && Actor->m_btRace != RCC_MERCHANT) && 
				g_boCanRunMon)
			{
				continue;;
			}
			return true;
		}


	}
	return false;
}

void TPlayScene::ActorDied(TActor* Actor)
{
	std::vector<TActor*>::iterator it;
	for(it = m_ActorList.begin();it != m_ActorList.end();it++)
	{
		if((TActor*)*it == Actor)
		{
			m_ActorList.erase(it);
			break;
		}
	}
	bool flag = false;
	for(it = m_ActorList.begin();it != m_ActorList.end();it++)
	{
		TActor* a = (TActor*)*it;
		if(! a->m_boDeath)
		{
			m_ActorList.insert(it,Actor);
			flag = true;
			break;
		}
	}
	if(!flag)
	{
		m_ActorList.push_back(Actor);
	}
}
TActor* TPlayScene::GetCharacter(int X,int Y,int wantsel, int &nowsel,bool liveonly)
{
	TActor* result = nullptr;
	nowsel = -1;
	int ccx,ccy;
	CXYfromMouseXY(X,Y,ccx,ccy);
	for(int k = ccy + 8;k >= ccy - 1;k--)
	{
		for(int i = m_ActorList.size()-1;i >= 0;i--)
		{
			TActor* a = m_ActorList[i];
			if((!liveonly || !a->m_boDeath) && a->m_boHoldPlace && a->m_boVisible)
			{
				if(a->m_nCurrY == k)
				{

					int dx = (a->m_nRx - VDMap::GetInstance()->m_ClientRect.Left) * 
						UNITX + m_nDefXX + a->m_nPx + a->m_nShiftX;
					int dy = (a->m_nRy - VDMap::GetInstance()->m_ClientRect.Top) * 
						UNITY + m_nDefYY + a->m_nPy + a->m_nShiftY;
					if(a->CheckSelect(X - dx,Y - dy))
					{
						result = a;
						nowsel ++;
						if(nowsel >= wantsel)
						{
							return result;
						}
					}
				}
			}
		}
	}
	return result;
}
TActor* TPlayScene::GetAttackFocusCharacter(int X,int Y,int wantsel,int &nowsel,bool liveonly)
{
	int ccx,ccy;
	int centx,centy;
	int dx,dy;
	TRect_ clientrect = VDMap::GetInstance()->m_ClientRect;
	TActor* result =GetCharacter(X, Y, wantsel, nowsel, liveonly);
	TActor* a;
	if(!result)
	{
		nowsel = -1;
		CXYfromMouseXY(X,Y,ccx,ccy);
		for(int k = ccy + 8;k >= ccy - 1;k--)
		{
			for(int i = m_ActorList.size() - 1;i >= 0;i--)
			{
				a = m_ActorList[i];
				if((!liveonly || !a->m_boDeath) && a->m_boHoldPlace && a->m_boVisible)
				{
					if(a->m_nCurrY == k)
					{
						dx = (a->m_nRx - clientrect.Left) * UNITX + m_nDefXX + a->m_nPx + a->m_nShiftX;
						dy = (a->m_nRy - clientrect.Top) * UNITY + m_nDefYY + a->m_nPy + a->m_nShiftY;
						if( a->CharWidth() > 40)
						{
							centx = (a->CharWidth() - 40) / 2;
						}else
						{
							centx = 0;
						}
						if( a->CharWidth() > 70)
						{
							centy = (a->CharWidth() - 70) / 2;
						}else
						{
							centy = 0;
						}

						if(X - dx >= centx && X -dx <= a->CharWidth() - centx
							&& Y - dy >= centy && Y - dy <= a->CharWidth() - centy)
						{
							result = a;
							nowsel++;
							if(nowsel >= wantsel)
							{
								return result;
							}
						}
					}
				}

			}

		}

	}
	return result;
}

TActor* TPlayScene::FindActorXY(int nX,int nY)
{
	TActor* actor;
	TActor* ret;
	ret = nullptr;
	for(int i = 0;i < (int)m_ActorList.size();i++)
	{
		actor = m_ActorList[i];
		if(actor->m_nCurrX == nX && actor->m_nCurrY == nY)
		{
			ret = actor;
			if(!ret->m_boDeath && ret->m_boVisible && ret->m_boHoldPlace)
			{
				break;
			}

		}
	}
	return ret;
}

void TPlayScene::ScreenXYfromMCXY(int cx,int cy,int &sx,int &sy)
{
	sx = (cx - VDMap::GetInstance()->m_ClientRect.Left) * UNITX + m_nDefXX;
	sy = (cy - VDMap::GetInstance()->m_ClientRect.Top) * UNITY + m_nDefYY;
}

bool TPlayScene::IsValidActor(TActor* actor)
{
	for(int i = 0;i < (int)m_ActorList.size();i++)
	{
		TActor* t = m_ActorList[i];
		if(t == actor)
		{
			return true;
		}
	}
	return false;
}

void TPlayScene::CleanObjects()
{

	for(int i = m_ActorList.size() - 1;i >= 0;i --)
	{
		TActor* actor = m_ActorList[i];
		if(actor != g_MySelf)
		{
			DelActor(actor);
		}
	}
	g_TargetCret = nullptr;
	g_FocusCret = nullptr;

}

void TPlayScene::NewMagic(TActor* aowner,int magid,int magnumb,int cx,int cy,int tx,int ty,int targetcode
						  ,TMagicType mtype,bool Recusion,int anitime,bool &bofly)
{
	int i = 0,j = 0,scx = 0,scy = 0,sctx = 0,scty = 0,sctx1 = 0,scty1 = 0,effnum = 0,effbase = 0;
	int sctx2 = 0,scty2 = 0,sctx3 = 0,scty3 = 0,sctx4 = 0;
	int scty4 = 0,sctx5 = 0,scty5 = 0,sctx6 = 0,scty6 = 0,sctx7 = 0,scty7 = 0;
	TMagicEff* meff = nullptr, *meff1 = nullptr, *meff2 = nullptr;
	TMagicEff *meff3 = nullptr, *meff4 = nullptr, *meff5 = nullptr, *meff6 = nullptr, *meff7 = nullptr;
	TActor* target = nullptr;
	TVDImageDatas* wimg = nullptr;
	int nDir = 0,nId = 0,nFrame = 0, nStartFrame = 0, nType = 0, nLib = 0;
	bofly = false;
	if(magnumb > 10000)
	{
		nFrame = magnumb % 100;          //图片张数
		magnumb = magnumb / 100;
		nStartFrame = magnumb % 10000;   //图片起始位置
		magnumb = magnumb / 10000;
		nType = magnumb % 10;            //魔法效果ID
		nLib = magnumb / 10;             //库
		magnumb = nType;
	}
	if(magid == 0)return;
	ScreenXYfromMCXY(cx, cy, scx, scy);  //施法对象所在格子位置转换屏幕坐标
	ScreenXYfromMCXY(tx, ty, sctx, scty);  //攻击目标坐标转化屏幕坐标
	if(magnumb > 0)
	{
		wimg = GetEffectBase(magnumb - 1, 0 );
	}else
	{
		effnum = -magnumb;
	}

	//目标对象
	target = FindActor(targetcode);
	meff = nullptr;
	meff1 = nullptr;
	switch(mtype)
	{
	case TMagicType::mtThunder:  //雷电术
		{
			if(magnumb== 9)
			{
				meff =  new TThuderEffect(3, sctx, scty, nullptr);
				meff->ImgLib = wimg;
				meff->frame = 6;
				meff->MagExplosionBase = 8;
				meff->ExplosionFrame = 6;
				meff->NextFrameTime = 100;
			}




			break;
		}
	case TMagicType::mtBujaukGroundEffect: //幽灵盾, 魔防术
		{
			meff = new TBujaukGroundEffect(0, magnumb, scx, scy, sctx, scty);
			meff->ImgLib1 = GetEffectBase(10 - 1, 0); // 飞行和施法用灵魂火符的
			meff->useImgLib1 = true;// 飞行和施法用灵魂火符的
			meff->EffectBase = 8;
			meff->MagExplosionBase = 0;
			meff->ExplosionFrame = 10;
			meff->TargetActor = nullptr; //target;
			meff->NextFrameTime = 80;
			meff->ExplosionFrame = 10;
			meff->Light = 3;
			meff->ImgLib = wimg;
			meff->frame = 5;
			break;
		}
	case TMagicType::mtLightingThunder:
		{
			meff = new TLightingThunder(10, scx, scy, sctx, scty, target);
			meff->ImgLib = wimg; 
			meff->NextFrameTime = 80;
			meff->frame = 4;
			break;
		}
	case TMagicType::mtExploBujauk:
		{
			switch(magnumb)
			{
			case 3:
				{
					meff = new TExploBujaukEffect(1640, scx, scy, sctx, scty, target);
					meff->ImgLib = wimg;
					meff->MagExplosionBase = 1800;
					meff->frame = 6;
					break;
				}
			case 10://灵魂火符
				{
					//980符起点位置，1140符爆炸位置
					meff = new TExploBujaukEffect(8, scx, scy, sctx, scty, target);
					meff->use16dir = true;
					meff->ImgLib = wimg;
					meff->MagExplosionBase = 88;
					meff->ExplosionFrame = 10;
					meff->frame = 5;
					break;
				}
			case 17://群体隐身术
				{
					meff = new TBujaukGroundEffect(0, magnumb, scx, scy, sctx, scty);
					meff->ImgLib1 = GetEffectBase(10 - 1, 0); // 飞行和施法用灵魂火符的
					meff->useImgLib1 = true;// 飞行和施法用灵魂火符的
					meff->EffectBase = 8;
					meff->MagExplosionBase = 0;
					meff->ExplosionFrame = 10;
					meff->TargetActor = nullptr; //target;
					meff->NextFrameTime = 80;
					meff->ExplosionFrame = 10;
					meff->Light = 3;
					meff->ImgLib = wimg;
					meff->frame = 5;
					break;
				}
			case 36: //群毒
				{
					meff = new TMagicEff();
					meff->Create(magid, effnum, scx, scy, sctx, scty, 
						TMagicType::mtExplosion, Recusion, anitime);
					meff->MagExplosionBase = 0;//为wil里的idx
					meff->ExplosionFrame = 9;
					meff->TargetActor = nullptr;//是目标
					meff->NextFrameTime = 70; //时间
					meff->ExplosionFrame = 10; //往后播放的帧数
					if(wimg)
					{
						meff->ImgLib = wimg;
					}

					break;
				}
			default: //火球术
				{
					meff = new TExploBujaukEffect(10, scx, scy, sctx, scty, target);
					meff->ImgLib = wimg;
					meff->MagExplosionBase = 90;
					meff->bo8 = true;
					meff->frame = 5;
				}
			}
			bofly = true;
			break;
		}
	case TMagicType::mtExplosion:
		{
			switch(magnumb)
			{
			case 2://治愈术
				{
					meff = new TMagicEff();
					meff->Create(magid, effnum, scx, scy, sctx, scty, 
						mtype, Recusion, anitime);
					meff->MagExplosionBase = 10;
					meff->TargetActor = nullptr; //target;
					meff->NextFrameTime = 80;
					meff->ExplosionFrame = 20;
					meff->Light = 3;
					meff->ImgLib = wimg;  
					break;
				}
			case 4://道士 施毒术
				{
					meff = new TMagicEff();
					meff->Create(magid, effnum, scx, scy, sctx, scty, mtype, Recusion, anitime);
					meff->MagExplosionBase = 8;
					meff->TargetActor = nullptr; //target;
					meff->NextFrameTime = 80;
					meff->ExplosionFrame = 15;
					meff->Light = 3;
					meff->ImgLib = wimg; 
					break;
				}
			case 18: //诱惑之光
				{
					meff = new TMagicEff();
					meff->Create(magid, effnum, scx, scy, sctx, 
						scty, mtype, Recusion, anitime);
					meff->MagExplosionBase = 10;
					meff->MagExplosionBase = 10;
					meff->NextFrameTime = 80;
					meff->ImgLib = wimg;
					meff->TargetActor = target;
					meff->Light = 3;
					break;
				}
			case 21: //爆裂火焰
				{
					meff = new TMagicEff();
					meff->Create(magid, effnum, scx, scy, sctx, scty, 
						mtype, Recusion, anitime);
					meff->MagExplosionBase = 0;
					meff->TargetActor = nullptr; //target;
					meff->NextFrameTime = 80;
					meff->ExplosionFrame = 10;
					meff->Light = 3;
					meff->ImgLib = wimg;
					break;
				}
			case 27: //群疗术
				{
					meff = new TMagicEff();
					meff->Create(magid, effnum, scx, scy, sctx, scty, 
						mtype, Recusion, anitime);
					meff->MagExplosionBase = 0;
					meff->TargetActor = nullptr; //target;
					meff->NextFrameTime = 80;
					meff->ExplosionFrame = 10;
					meff->Light = 3;
					meff->ImgLib = wimg;
					break;
				}
			case 30: //圣言术
				{
					meff = new TMagicEff();
					meff->Create(magid, effnum, scx, scy, sctx, scty, 
						mtype, Recusion, anitime);
					meff->MagExplosionBase = 10;
					meff->TargetActor = target;
					meff->NextFrameTime = 80;
					meff->ExplosionFrame = 10;
					meff->Light = 3; 
					meff->ImgLib = wimg;
					break;
				}
			case 31: //冰咆哮
				{
					meff = new TMagicEff();
					meff->Create(magid, effnum, scx, scy, sctx, scty, mtype, Recusion, anitime);
					meff->MagExplosionBase = 8;
					meff->TargetActor = nullptr; //target;
					meff->NextFrameTime = 80;
					meff->ExplosionFrame = 10;
					meff->Light = 3;
					meff->ImgLib = wimg;
					break;
				}
			}
			break;
		}
	case TMagicType::mtFireWind:
		{
			if(magnumb == 35)
			{
				meff = new TMagicEff ();
				meff->Create(magid, effnum, scx, scy, sctx, scty, 
					TMagicType::mtExplosion, Recusion, anitime);
				meff->MagExplosionBase = 165;//为wil里的idx
				meff->TargetActor = aowner; //nil;//是目标
				meff->NextFrameTime = 60; //时间
				meff->ExplosionFrame = 10; //往后播放的帧数
				if( wimg )
				{
					meff->ImgLib = wimg;
				}

			}else
			{
				meff = nullptr;
			}
			break;
		}

	}
	if(!meff) return;
	meff->TargetRx = tx;
	meff->TargetRy = ty;
	if( meff->TargetActor)
	{
		meff->TargetRx = meff->TargetActor->m_nCurrX;
		meff->TargetRy = meff->TargetActor->m_nCurrY;
	}

	meff->MagOwner = aowner;
	m_EffectList.push_back(meff);
}

void TPlayScene::Show_Dialog(DIALOG_TYPE type)
{

	switch(type)
	{
	case DIALOG_TYPE::SHORTCUTS:
		{
			VD_UI::CShortcutsDialog* t = VD_UI::CShortcutsDialog::GetInstance();
			t->Show(m_LayerUI);
			//VD_UI::CShortcutsDialog::GetInstance->Show(m_LayerUI);
		}

	}
}

void TPlayScene::Hide_Dialog(DIALOG_TYPE type)
{
	cocos2d::Node* node;
	node = m_LayerUI->getChildByTag(type);
	if(node)
	{
		//CShortcutsDialog::GetInstance()->Show(m_LayerUI);
		m_LayerUI->removeChild(node);
		node->release();
	}
	//switch(type)
	//{
	//case DIALOG_TYPE::SHORTCUTS:
	//	{
	//		
	//	}
	//}
}


