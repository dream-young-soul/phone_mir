//TCP异步客户端-- Time:2015.5.25
#ifndef TCPSOCKET_H_
#define TCPSOCKET_H_
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include <windows.h>
#include <WinSock.h>
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include <sys/socket.h>
#include <fcntl.h>
#include <errno.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define SOCKET int
#define SOCKET_ERROR -1
#define INVALID_SOCKET -1
#endif
#define BLOCKSECONDS	30			// INIT函数阻塞时间
namespace VD_Net
{
	class CTcpSocket
	{
	public:
		CTcpSocket(void);
		~CTcpSocket(void);

		bool Create(const char* pszServerIP,int nServerPort,int nBlockSec = BLOCKSECONDS, bool bKeepAlive = false);
		bool SendMsg(void* pBuf,int nSize);
		int ReceiveMsg(void* pBuf,int nSize); //成功返回被接收到的数据包大小
		bool Check(void);
		void Destroy(void);
	private:
		void closeSocket();
		bool hasError();

	private:
		SOCKET	m_sockClient;
		char m_pData[65535];
	};
}



#endif 