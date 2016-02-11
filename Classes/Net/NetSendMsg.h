#ifndef NETSENDMSG_H_
#define NETSENDMSG_H_
#include <string>
namespace VD_Net
{
	class CNetClient;
	class CNetSendMsg
	{
	public:
		CNetSendMsg(CNetClient* net);
		~CNetSendMsg(void);

	private:
		CNetClient* m_NetClient;
		unsigned long m_GetIconsTick; //获取人物属性图标面板
	public:
		void Login(const char* username,const char* paswd);
		void selectServer(const char* servername);
		void QuestChr();
		void SelectChr(const char* chrname);
		void SendNewChr(const char* uname,const char* sjob,const char* ssex);
		void SendDelChr(const char* sChrname);
		void RunLogin();
		void SendHeartPacket();
		void SendLogon();
		void SendPickup(int x,int y);
		void SendMerchantDlgSelect(int merchant,std::string rstr);
		void SendQueryUserName(int targetid,int x,int y);
		void SendTaskSelect(int nTaskId,std::string rstr);
		void SendGetIcons();
	};
}


#endif