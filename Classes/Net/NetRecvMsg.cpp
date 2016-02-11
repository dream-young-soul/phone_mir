
#include "NetRecvMsg.h"
#include "NetClient.h"

#include "NetSendMsg.h"

#include "../MShare.h"
#include "../Common/Grobal2.h"
#include "cocos2d.h"

#ifdef WIN32
#include <windows.h>
#endif

namespace VD_Net
{
	CNetRecvMsg::CNetRecvMsg(CNetClient* net)
	{
		m_NetClient = net;
		memset(&m_RecvData[0],0,sizeof(m_RecvData));
		m_nPos = 0;
		m_NetEventList.resize(MAX_NETEVENT_COUNT);
	}


	CNetRecvMsg::~CNetRecvMsg(void)
	{
	}




	void CNetRecvMsg::OnMessage(const char* msg,int Size)
	{
		//粘包处理
		memcpy(&m_RecvData[m_nPos],msg,Size);
		m_nPos += Size;
		char* pData = &m_RecvData[0];
		int nStartPos = -1;
		int nEndPos = 0;
		int i;
		for(i = 0;i < m_nPos;i++)
		{
			if(pData[i] == '*')//心跳包
			{
				m_NetClient->GetSendMsg()->SendHeartPacket();
				continue;
			}
			if(pData[i] == '#')
			{
				if(nStartPos != -1)
				{
					CCLOG("process netpack error #");
				}

				nStartPos = i;
			}
			if(pData[i] == '!')
			{
				nEndPos = i;
				if(nStartPos == -1) 
				{
					CCLOG("process netpack error! !");
					continue;
				}
				if(pData[nStartPos + 1] == '+')
				{

					int nLen = nEndPos - nStartPos - 2;
					memcpy(m_NetClient->mEncodeBuf,&pData[nStartPos + 2],nLen);
					ProcessSpecialMsg(m_NetClient->mEncodeBuf);
					nStartPos = -1;
					continue;
				}

				int nLen = nEndPos - nStartPos - 1;
				memcpy(m_NetClient->mEncodeBuf,&pData[nStartPos + 1],nLen);
				DEFAULTMESSAGE defmsg;
				m_NetClient->mEncodeBuf[nLen] = 0;
				int n = DecodeDefMessage(&defmsg, m_NetClient->mEncodeBuf);
				procMessage(&defmsg, &m_NetClient->mEncodeBuf[DEFBLOCKSIZE], nLen -DEFBLOCKSIZE);
				nStartPos = -1;
			}
		}
		//有多余的数据
		nEndPos ++;
		if(nEndPos  != m_nPos)
		{
			int nLen = m_nPos - nEndPos;
			memcpy(m_RecvData,&pData[nEndPos],nLen);
			memset(&m_RecvData[nLen],0,sizeof(m_RecvData) - nLen);
			m_nPos = nLen;
		}else
		{
			memset(m_RecvData,0,sizeof(m_RecvData));
			m_nPos = 0;
		}
		//心跳包--
		//char *star = strchr((char*)msg, '*');
		//char* pData = (char*)msg;
		//int nSize = Size;
		//if (star > 0)
		//{
		//	m_NetClient->GetSendMsg()->SendHeartPacket();
		//	pData++;
		//	nSize--;
		//}
		//char *sp = strchr(pData, '#');
		//int fixsize = nSize - (sp - pData);
		//if (fixsize > 0 && sp && sp[0] == '#' && sp[fixsize-1] == '!')
		//{
		//	if (pData[1] == '+')
		//	{
		//		memcpy(m_NetClient->mEncodeBuf, &sp[2], fixsize - 3);
		//		if (strstr(m_NetClient->mEncodeBuf, "FAIL") != NULL ) //== mEncodeBuf
		//		{
		//			//actFail();
		//		}
		//		else if (strstr(m_NetClient->mEncodeBuf, "GOOD")!= NULL) // == mEncodeBuf
		//		{
		//			//actOK();				
		//		}
		//		return;
		//	}
		//	if (fixsize < sizeof(m_NetClient->mDecodeBuf))
		//	{
		//		DEFAULTMESSAGE defmsg;
		//		memcpy(m_NetClient->mEncodeBuf, &sp[1], fixsize - 2);
		//		m_NetClient->mEncodeBuf[fixsize-2] = 0;
		//		int n = DecodeDefMessage(&defmsg, m_NetClient->mEncodeBuf);
		//		procMessage(&defmsg, &m_NetClient->mEncodeBuf[DEFBLOCKSIZE], fixsize -DEFBLOCKSIZE-2);			
		//	}
		//}else
		//{
		//	CCLOG("netpacket process error data:%s",pData);
		//}
	}

	void CNetRecvMsg::procMessage(DEFAULTMESSAGE *msg, char * data, int datasize)
	{

		std::string str = "";
		//char sLog[1024]={0};
		//sprintf(sLog,"procmessage ident:%d",msg->Ident);
		//str = sLog;
		//g_AnroidLog.push_back(str);
		int n;
		m_NetClient->mDecodeBuf[0] = 0;
		if (datasize > 0)
		{
			n = fnDecode6BitBuf(data, m_NetClient->mDecodeBuf, sizeof(m_NetClient->mDecodeBuf));
			if (n > 0)
			{
				m_NetClient->mDecodeBuf[n] = 0;
				//printf(mDecodeBuf );
				str = m_NetClient->mDecodeBuf;
			}
		}
		TNetEvent e;
		e.event_type = TNETEVENTTYPE::NETPACKET;
		memcpy(&e.msg,msg,sizeof(tagDefaultMessage));

		e.Body = "";

		switch(msg->Ident)
		{
		case SM_PASSOK_SELECTSERVER:
			{
				ClientSelectServer(msg,str);
				break;
			}
		case SM_SELECTSERVER_OK:
			{
				ClientSelectServerOK(msg,str);
				break;
			}
		//case  SM_QUERYCHR:
		//	{
		//		ClientQuertChr(msg,str);
		//		break;
		//	}
		case  SM_STARTPLAY:
			{
				ClientStartPlay(msg,str);
				break;
			}
		case SM_STARTFAIL:
			{
				break;
			}
		case SM_SENDNOTICE:
			{
				ClientSendNotice(msg,str);

				break;
			}
		case SM_NEWMAP:
		case SM_CHANGEMAP:
			{
				ClientNewMap(msg,str);

				//curx = msg->Param;
				//cury = msg->Tag;
				//dir = GetTickCount() % 8;
				break;
			}
		case SM_LOGON:
			{
				e.Body = data;

				ClientLogon(msg,str);
				break;
			}
		case SM_WALK:
		case SM_RUSH:
		case SM_RUSHKUNG:
		case SM_RUN:
		case SM_HORSERUN:
		case SM_TURN:
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
		case SM_DEATH:
		case SM_NOWDEATH:
		case SM_STRUCK:
		case SM_ACTORHP:
		case SM_ABILITY:
		case SM_SPELL: 
		case SM_SUBABILITY:
		case SM_ADJUST_BONUS:
		case SM_SHOWPACKAGE:
		case SM_PACKS:
		case SM_MAGICFIRE:
		case SM_ADDMAGIC:
		case SM_SENDMYMAGIC:
		case SM_SHOWEVENT:
		case SM_BAGITEMS:
		case SM_SENDUSEITEMS:
		case SM_TAKEON_OK:
		case SM_SHOWIMGMSG:
		case SM_ADDITEM:
		case SM_GETICONS:
		case SM_TASK:
			{
				e.Body = data;
				break;
			}
		case SM_CLEAROBJECTS:
		case SM_DISAPPEAR:
		case SM_FEATURECHANGED:
		case SM_CHARSTATUSCHANGED:
		case SM_HEALTHSPELLCHANGED:
		case SM_SYSMESSAGE:
		case SM_CHANGELIGHT:
		case SM_SERVERCONFIG:
		case SM_AREASTATE:
		case SM_USERNAME:
		case SM_MAPDESCRIPTION:
		case SM_GAMEGOLDNAME:
		case SM_HIDEEVENT:
		case SM_MERCHANTSAY:
		case SM_QUERYCHR:
		case SM_QUERYCHR_FAIL:
		case SM_DELCHR_SUCCESS:
		case SM_DELCHR_FAIL:
		case SM_ITEMSHOW:
		case SM_ITEMHIDE:
		case SM_WALKTO:
		case SM_MERCHANTDLGCLOSE:
		case SM_UPDATEITEM:
		case SM_WINEXP:
		case SM_LEVELUP:
		case SM_WEIGHTCHANGED:
		case SM_SENDJINGMAI:
		case SM_CHANGENAMECOLOR:
		case SM_MAGICEFF:
		case SM_DURACHANGE:
		case SM_MISS:
		case SM_MAGIC_LVEXP:
		case SM_KILLMON:
		case SM_SPELLNEED:
			{
				break;
			}
		default:
			{
				CCLOG("default Ident:%d",msg->Ident);
				break;
			}
		}
		if(e.Body.length() <= 0)
		{
			e.Body = str;
		}
		AddNetEventData(&e);

	}

	void CNetRecvMsg::ClientSelectServer(DEFAULTMESSAGE* msg,std::string str)
	{
		std::string servername = str.substr(0, strchr(str.c_str(),'/') - str.c_str());
		m_NetClient->GetSendMsg()->selectServer(servername.c_str());
	}
	void CNetRecvMsg::ClientSelectServerOK(DEFAULTMESSAGE* msg,std::string str)
	{
		char* pstr;
		char* ptmp;
		int n;
		std::string s1,s2,s3;
		pstr = (char*)str.c_str();
		ptmp = strchr(pstr, '/');
		n = ptmp - pstr;
		s1 = str.substr(0, ptmp - pstr);

		ptmp++;
		pstr = ptmp;
		ptmp = strchr(ptmp, '/');
		n = pstr - str.c_str();
		s2 = str.substr(n, ptmp - pstr);

		ptmp++;
		pstr = ptmp;
		ptmp = strchr(ptmp, '/');
		n = pstr - str.c_str();
		s3 = str.substr(n, ptmp - pstr);

		m_NetClient->Certification = atoi(s3.c_str());
		if (m_NetClient->serverhost.length() == 0)
		{
			m_NetClient->serverhost = s1;
		}
		int serverport = atoi(s2.c_str());
		if(m_NetClient->Connect(s1.c_str(),serverport,true))
		{
			m_NetClient->GetSendMsg()->QuestChr();
		}else
		{
			TNetEvent e;
			e.event_type = TNETEVENTTYPE::SOCKET_CONNECT_SELGATE;
			AddNetEventData(&e);
			//sCCLOG("connect selgate error %s:%d",s1.c_str(),serverport);
		}
	}
	void CNetRecvMsg::ClientQuertChr(DEFAULTMESSAGE* msg,std::string str)
	{
		char* pstr;
		char* ptmp;
		pstr = (char*)str.c_str();
		ptmp = strchr(pstr, '/');
		m_NetClient->chrname = str.substr(0, ptmp - pstr);

		//m_NetClient->GetSendMsg()->SelectChr(m_NetClient->chrname.c_str());
	}
	void CNetRecvMsg::ClientStartPlay(DEFAULTMESSAGE* msg,std::string str)
	{
		char* pstr;
		char* ptmp;
		std::string s2;
		pstr = (char*)str.c_str();
		ptmp = strchr(pstr, '/');

		ptmp ++;
		s2 = ptmp;
		int serverport = atoi(s2.c_str());
		if(m_NetClient->Connect(m_NetClient->serverhost.c_str(),serverport,true))
		{
			m_NetClient->GetSendMsg()->RunLogin();
		}else
		{
			TNetEvent e;
			e.event_type = TNETEVENTTYPE::SOCKET_CONNECT_RUNGATE;
			AddNetEventData(&e);
			//	CCLOG("connect rungate error! %s:%d",m_NetClient->serverhost,serverport);
		}

	}
	void CNetRecvMsg::ClientSendNotice(DEFAULTMESSAGE* msg,std::string str)
	{
		m_NetClient->sendDefMsg(CM_LOGINNOTICEOK, GetTickCount(), 0, 0, 0);
	}
	void CNetRecvMsg::ClientNewMap(DEFAULTMESSAGE* msg,std::string str)
	{
		//CCLOG("start new map success");
	}
	void CNetRecvMsg::ClientLogon(DEFAULTMESSAGE* msg,std::string str)
	{
		int sn = msg->Recog;	
		m_NetClient->sendDefMsg(CM_LOGON, 0, 0, 0, 0);
		m_NetClient->sendDefMsg(CM_WANTMINIMAP, 0, 0, 0, 0);
		//Sleep(2);
		m_NetClient->sendDefMsg(CM_QUERYBAGITEMS, 0, 0, 0, 0); //查询背包数据
		m_NetClient->sendDefMsg(CM_QUERYUSERNAME, 0, 0, 0, 0); 
	}

	void CNetRecvMsg::ProcessSpecialMsg(const char* msg)
	{


		//	data := Copy(datablock, 2, Length(datablock) - 1);
		//std::string tagstr= "";
		std::string src = msg;
		//if(src.find('/'))
		//std::string data = GetValidStr3Ex(src,tagstr,'/');

		TNetEvent e;
		e.reset();
		e.event_type = NETPACKET_SPECIAL;
		e.Body = src.c_str();
		AddNetEventData(&e);
		//	If tagstr = 'PWR' Then
		//g_boNextTimePowerHit := True;     //打开攻杀
		//	If tagstr = 'LNG' Then
		//g_boCanLongHit := True;           //打开刺杀
		//	If tagstr = 'ULNG' Then
		//g_boCanLongHit := FALSE;          //关闭刺杀
		//	If tagstr = 'WID' Then
		//g_boCanWideHit := True;           //打开半月
		//	If tagstr = 'UWID' Then
		//g_boCanWideHit := FALSE;          //关闭半月
		//	If tagstr = 'CRS' Then
		//g_boCanCrsHit := True;            //打开双龙    抱月刀法
		//	If tagstr = 'UCRS' Then
		//g_boCanCrsHit := FALSE;           //关闭双龙  抱月刀法
		//	If tagstr = 'TWN' Then
		//g_boCanTwnHit := True;            //打开狂风斩
		//	If tagstr = 'UTWN' Then
		//g_boCanTwnHit := FALSE;           //关闭狂风斩
		//	If tagstr = 'STN' Then
		//g_boCanStnHit := True;            //打开狂风斩;
		//	If tagstr = 'USTN' Then
		//g_boCanStnHit := FALSE;
		//	If tagstr = 'FIR' Then
	}


	void CNetRecvMsg::AddNetEventData(TNetEvent* e)
	{

		bool is = false;
		std::vector<TNetEvent>::iterator it;
		for(it = m_NetEventList.begin();it != m_NetEventList.end();it++)
		{
			if(it->event_type == TNETEVENTTYPE::NORMAL)
			{
				it->event_type = e->event_type;
				it->msg = e->msg;
				it->Body = e->Body;
				is = true;
				break;
			}
		}
		if(!is)
		{
			//五十个队列都放不下了。。网络是有多阻塞啊。。
			CCLOG("netevent --overflow~ %d",e->event_type);
		}
	}
	TNetEvent* CNetRecvMsg::GetNetEventData(int pos)
	{
		if(pos >= MAX_NETEVENT_COUNT || pos < 0) return nullptr;
		TNetEvent* ret = (TNetEvent*)&m_NetEventList[pos];
		if(ret->event_type != TNETEVENTTYPE::NORMAL)
		{
			return ret;
		}

		//std::vector<TNetEvent>::iterator it;
		//for(it = m_NetEventList.begin();it != m_NetEventList.end();it++)
		//{
		//	if(it->event_type != TNETEVENTTYPE::NORMAL)
		//	{
		//		return (TNetEvent*)&it;
		//	}
		//}
		return nullptr;
	}

	void CNetRecvMsg::ClearNetEventData()
	{
		std::vector<TNetEvent>::iterator it;
		for(it = m_NetEventList.begin();it != m_NetEventList.end();it++)
		{
			if(it->event_type != TNETEVENTTYPE::NORMAL)
			{
				it->reset();
			}else break;

		}
	}
}
