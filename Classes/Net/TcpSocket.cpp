#include "TcpSocket.h"
#include <string>
using namespace VD_Net;
//namespace VD_Net
//{
	CTcpSocket::CTcpSocket(void)
	{
		memset(&m_pData[0],0,sizeof(m_pData));
	}


	CTcpSocket::~CTcpSocket(void)
	{
	}

	bool CTcpSocket::Create(const char* pszServerIP, int nServerPort, int nBlockSec, bool bKeepAlive /*= FALSE*/)
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		WSADATA wsaData;
		WORD version = MAKEWORD(2, 0);
		int ret = WSAStartup(version, &wsaData);//win sock start up
		if (ret != 0) {
			return false;
		}
#endif
		// 创建主套接字
		m_sockClient = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		if(m_sockClient == INVALID_SOCKET) {
			closeSocket();
			return false;
		}

		// 设置SOCKET为KEEPALIVE
		if(bKeepAlive)
		{
			int		optval=1;
			if(setsockopt(m_sockClient, SOL_SOCKET, SO_KEEPALIVE, (char *) &optval, sizeof(optval)))
			{
				closeSocket();
				return false;
			}
		}

#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		DWORD nMode = 1;
		int nRes = ioctlsocket(m_sockClient, FIONBIO, &nMode);
		if (nRes == SOCKET_ERROR) {
			closeSocket();
			return false;
		}
#else
		// 设置为非阻塞方式
		fcntl(m_sockClient, F_SETFL, O_NONBLOCK);
#endif

		unsigned long serveraddr = inet_addr(pszServerIP);
		if(serveraddr == INADDR_NONE)	// 检查IP地址格式错误
		{
			closeSocket();
			return false;
		}

		sockaddr_in	addr_in;
		memset((void *)&addr_in, 0, sizeof(addr_in));
		addr_in.sin_family = AF_INET;
		addr_in.sin_port = htons(nServerPort);
		addr_in.sin_addr.s_addr = serveraddr;

		if(connect(m_sockClient, (sockaddr *)&addr_in, sizeof(addr_in)) == SOCKET_ERROR) {
			if (hasError()) {
				closeSocket();
				return false;
			}
			else	// WSAWOLDBLOCK
			{
				timeval timeout;
				timeout.tv_sec	= nBlockSec;
				timeout.tv_usec	= 0;
				fd_set writeset, exceptset;
				FD_ZERO(&writeset);
				FD_ZERO(&exceptset);
				FD_SET(m_sockClient, &writeset);
				FD_SET(m_sockClient, &exceptset);

				int ret = select(FD_SETSIZE, NULL, &writeset, &exceptset, &timeout);
				if (ret == 0 || ret < 0) {
					closeSocket();
					return false;
				} else	// ret > 0
				{
					ret = FD_ISSET(m_sockClient, &exceptset);
					if(ret)		// or (!FD_ISSET(m_sockClient, &writeset)
					{
						closeSocket();
						return false;
					}
				}
			}
		}

		struct linger so_linger;
		so_linger.l_onoff = 1;
		so_linger.l_linger = 500;
		setsockopt(m_sockClient, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

		return true;
	}

	void CTcpSocket::closeSocket()
	{
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		closesocket(m_sockClient);
		WSACleanup();
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		//close(m_sockClient);
#endif
	}

	bool CTcpSocket::hasError()
	{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
		int err = WSAGetLastError();
		if(err != WSAEWOULDBLOCK) {
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
		int err = errno;
		if(err != EINPROGRESS && err != EAGAIN) {
#endif
			return true;
		}

		return false;

	}


	bool CTcpSocket::SendMsg(void* pBuf,int nSize)
	{
		if(!pBuf || nSize <= 0)
		{
			return false;
		}
		if (m_sockClient == INVALID_SOCKET) {
			return false;
		}
		int outsize = send(m_sockClient,(const char*)pBuf,nSize,0);
		if(outsize <= 0)
		{
			if(hasError())
			{
				Destroy();
				return false;
			}
		}
		return true;
	}

	bool CTcpSocket::Check(void)
	{
		if (m_sockClient == INVALID_SOCKET) {
			return false;
		}
		char buf[1];
		int	ret = recv(m_sockClient, buf, 1, MSG_PEEK);
		if(ret == 0) {
			Destroy();
			return false;
		} else if(ret < 0) {
			if (hasError()) {
				Destroy();
				return false;
			} else {	// 阻塞
				return true;
			}
		} else {	// 有数据
			return true;
		}

		return true;
	}

	int CTcpSocket::ReceiveMsg(void* pBuf,int nSize)
	{
		if(!pBuf || nSize <= 0)
		{
			return 0;
		}
		if(m_sockClient == INVALID_SOCKET)
		{
			return 0;
		}

		const int BUFFSIZE = 512;
		int nLen = 0;
		char* pData = &m_pData[0];
		while(true)
		{
			int nRetSize = recv(m_sockClient,pData,BUFFSIZE,0);
			if(nRetSize == 0)
			{
				Destroy();
				return 0;
			}else if(nRetSize < 0)
			{
				if (hasError()) 
				{
					Destroy();
					return 0;
				}
				break;
			}else
			{
				pData += BUFFSIZE; //还存在没有接收到的数据
				nLen += nRetSize;
			}
		}
		if(nLen == 0)
		{
			return false;
		}

		memcpy(pBuf,&m_pData[0],nLen);
		memset(&m_pData[0],0,sizeof(m_pData));//清除缓冲区
		return nLen;
	}

	void CTcpSocket::Destroy()
	{
		struct linger so_linger;
		so_linger.l_onoff = 1;
		so_linger.l_linger = 500;
		int ret = setsockopt(m_sockClient, SOL_SOCKET, SO_LINGER, (const char*)&so_linger, sizeof(so_linger));

		closeSocket();

		m_sockClient = INVALID_SOCKET;
		memset(m_pData,0,sizeof(m_pData));

	}
//}
