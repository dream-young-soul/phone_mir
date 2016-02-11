
#include "NetSendMsg.h"
#include <string>
#include "NetClient.h"
#include "../Common/Grobal2.h"
#include "../MShare.h"
namespace VD_Net
{
	CNetSendMsg::CNetSendMsg(CNetClient* net)
	{
		m_NetClient = net;
		m_GetIconsTick = GetTickCount();
	}


	CNetSendMsg::~CNetSendMsg(void)
	{
	}


	void CNetSendMsg::Login(const char* username,const char* paswd)
	{
		std::string text = username;
		text += "/";
		text += paswd;
		m_NetClient->username = username;
		m_NetClient->sendDefMsg(CM_IDPASSWORD,0,0,0,0,text.c_str());
	}

	void CNetSendMsg::selectServer(const char* servername)
	{
		m_NetClient->sendDefMsg(CM_SELECTSERVER,0,0,0,0,servername);
	}

	void CNetSendMsg::QuestChr()
	{
		char buf[10];
		memset(buf, 0, sizeof(buf));
		std::string str = m_NetClient->username;
		str += "/";
		sprintf(buf,"%d",m_NetClient->Certification);
		//	itoa(m_NetClient->Certification, buf, 10);
		str += buf;
		m_NetClient->sendDefMsg(CM_QUERYCHR, 0, 0, 0, 0, str.c_str());

	}

	void CNetSendMsg::SelectChr(const char* chrname)
	{
		std::string str = m_NetClient->username;
		str += "/";
		str += chrname;
		m_NetClient->sendDefMsg(CM_SELCHR, 0, 0, 0, 0, str.c_str());
	}
	void CNetSendMsg::SendNewChr(const char* uname,const char* sjob,const char* ssex)
	{
		std::string str ;
		char c[128]; sprintf(c,"%s/%s/0/%s/%s",m_NetClient->username.c_str(),uname,sjob,ssex);
		str = c;
		m_NetClient->sendDefMsg(CM_NEWCHR, 0, 0, 0, 0, str.c_str());
	}

	void CNetSendMsg::SendDelChr(const char* sChrname)
	{
		m_NetClient->sendDefMsg(CM_DELCHR, 0, 0, 0, 0, sChrname);
	}
	void CNetSendMsg::RunLogin()
	{
		char buf[512];
		sprintf(buf, "**%s/%s/%d/%d/%d", m_NetClient->username.c_str(), m_NetClient->chrname.c_str(), m_NetClient->Certification, CLIENT_VERSION_NUMBER, 0);
		m_NetClient->sendSocket(buf, strlen(buf), true);
	}

	void CNetSendMsg::SendHeartPacket()
	{
		char bf ='*';
		m_NetClient->sendSocket(&bf,1);
	}

	void CNetSendMsg::SendLogon()
	{
		const char LOGON_STR[]   = "亲爱的玩家，您好，你还未通过防沉迷认证，您的游戏体验可能会受到影响，请及时点击右下角防沉迷按钮填写认证信息。持续游戏时间超过3小时后，将被强制下线休息。休息时间满5小时后才可以继续游戏。";
		int CRC = -1898912658;
		int n =	CLIENT_VERSION_NUMBERFIX ^ CRC;
		m_NetClient->sendDefMsg(CM_LOGON,CRC, 0,0, n);


	}

	void CNetSendMsg::SendPickup(int x,int y)
	{
		m_NetClient->sendDefMsg(CM_PICKUP,0,x,y,0);
	}

	void CNetSendMsg::SendMerchantDlgSelect(int merchant,std::string rstr)
	{
		//购买啊 寄售啊 - 暂时不写
		// 20120630前面的处理中，会将字符串中的下划线_变为空格，造成这里
		//某些带下划线的命令参数无法正确请求，故此处重新把空格
		//替换为下划线  比如命令s_repair

		std::string str = rstr;
		StringReplace(str," ","_");
		m_NetClient->sendDefMsg(CM_MERCHANTDLGSELECT,merchant,0,0,0,str.c_str());

	}
	void CNetSendMsg::SendQueryUserName(int targetid,int x,int y)
	{
		m_NetClient->sendDefMsg(CM_QUERYUSERNAME,targetid,x,y,0);
	}

	void CNetSendMsg::SendTaskSelect(int nTaskId,std::string rstr)
	{
		m_NetClient->sendDefMsg(CM_TASKSELECT,nTaskId,0,0,0,rstr.c_str());
	}

	void CNetSendMsg::SendGetIcons()
	{
		if(m_GetIconsTick < GetTickCount())
		{
			m_NetClient->sendDefMsg(CM_GETICONS,0,0,0,0);
			m_GetIconsTick = GetTickCount() + 600000;

		}
	}
}
