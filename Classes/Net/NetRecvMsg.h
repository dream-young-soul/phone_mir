#ifndef NETRECVMSG_H_
#define NETRECVMSG_H_
//#include "../Common/Grobal2.h"
#include "../GameStruct.h"
#include <string>
#include <vector>
namespace VD_Net
{
	class CNetClient;
	class CNetRecvMsg
	{
	public:
		CNetRecvMsg(CNetClient* net);
		~CNetRecvMsg(void);


		void OnMessage(const char* msg,int Size);
		void procMessage(DEFAULTMESSAGE *msg, char * data, int datasize);
	private:
		char m_RecvData[65535]; //数据缓冲
		int m_nPos;
		//std::vector<> m_DataList; //数据队列

	private:
		CNetClient* m_NetClient;
		std::vector<TNetEvent> m_NetEventList;
	private:
		void ClientSelectServer(DEFAULTMESSAGE* msg,std::string str);
		void ClientSelectServerOK(DEFAULTMESSAGE* msg,std::string str);
		void ClientQuertChr(DEFAULTMESSAGE* msg,std::string str);
		void ClientStartPlay(DEFAULTMESSAGE* msg,std::string str);
		void ClientSendNotice(DEFAULTMESSAGE* msg,std::string str);
		void ClientNewMap(DEFAULTMESSAGE* msg,std::string str);
		void ClientLogon(DEFAULTMESSAGE* msg,std::string str);

		void ProcessSpecialMsg(const char* msg);

	public:
		TNetEvent* GetNetEventData(int pos);
		void ClearNetEventData();
		void AddNetEventData(TNetEvent* e);
	};

}



#endif
