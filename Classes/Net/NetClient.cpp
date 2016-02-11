
#include "NetClient.h"
#include "TcpSocket.h"
#include "NetRecvMsg.h"
#include "NetSendMsg.h"
#include "../Common/Grobal2.h"
#include <string>

namespace VD_Net
{
	static CNetClient* m_Instance = nullptr;

	CNetClient::CNetClient(void)
	{
		msgCode = 1;
		m_bCon = false;
		memset(m_Data,0,sizeof(m_Data));
	}


	CNetClient::~CNetClient(void)
	{
	}

	CNetClient* CNetClient::GetInstance()
	{
		if(!m_Instance)
		{
			m_Instance = new CNetClient();
			m_Instance->m_Socket = new CTcpSocket();
			m_Instance->m_NetRecvMsg = new CNetRecvMsg(m_Instance);
			m_Instance->m_NetSendMsg = new CNetSendMsg(m_Instance);
		}
		return m_Instance;
	}

	bool CNetClient::Connect(const char* szServerIP,int nServerPort,bool isReconnect /* = false */)
	{
		if(isReconnect)
		{
			m_Socket->Destroy();
		}
		m_bCon = m_Socket->Create(szServerIP,nServerPort);
		return m_bCon;
	}

	bool CNetClient::ProcessMsg()
	{
		if(!m_bCon)return false;
		int nSize = sizeof(m_Data);
		int ret = m_Socket->ReceiveMsg(&m_Data[0],nSize);
		if(!ret) return false;
		m_NetRecvMsg->OnMessage(&m_Data[0],ret);
		return true;

	}

	void CNetClient::sendDefMsg(int mIdent, int mRecog, int mParam, int  mTag,int mSeries, const char *str, bool strEncode,const char* adddata)
	{
		memset(&m_SendData[0],0,sizeof(m_SendData));
		char buf[8];
		char bf = '#';
		char ef = '!';
		DEFAULTMESSAGE msg;
		MAKEDEFMSG(&msg, mIdent,mRecog, mParam, mTag,mSeries);
		int n = EncodeDefMessage(mEncodeBuf, &msg);
		int nLen = 0;
		char* pSendData = &m_SendData[0];
		pSendData[0] = bf; nLen ++;
		sprintf(buf,"%d",msgCode);
		//itoa(msgCode, buf, 10);
		pSendData[1] = buf[0];
		nLen ++;
		//pSendData[1] = msgCode;nLen ++;
		pSendData += 2;
		memcpy(pSendData,mEncodeBuf,n);
		pSendData += n;
		nLen += n;

		if (str != NULL)
		{
			if (strlen(str) > 0)
			{
				if (strEncode)
				{
					n = fnEncode6BitBuf((char*)str, mEncodeBuf, strlen(str), sizeof(mEncodeBuf) - n);
					memcpy(pSendData,mEncodeBuf,n);
					pSendData += n;
					nLen += n;

				}
				else
				{
					memcpy(pSendData,str,strlen(str));
					pSendData += strlen(str);
					nLen += strlen(str);
				}
			}
		}
		if(adddata)
		{
			int len = strlen(adddata);
			memcpy(pSendData,adddata,len);
			pSendData += len;
			nLen += len;
		}
		*pSendData = ef;
		nLen ++;
		m_Socket->SendMsg(&m_SendData[0],nLen);
		msgCode ++;
		if (msgCode >= 10) msgCode = 1;
	}

	void CNetClient::sendSocket(char *buf, int size, bool strEncode)
	{
		memset(m_SendData,0,sizeof(m_SendData));
		int n;
		if (buf == NULL || size < 3) return;
		char* pSendData = &m_SendData[0];
		int nLen = 0;
		char bf = '#';
		char ef = '!';
		pSendData[0] = bf;nLen ++;
		char buf_[8];
		sprintf(buf_,"%d",msgCode);
		//itoa(msgCode, buf_, 10);
		pSendData[1] = buf_[0];
		nLen++;
		pSendData += 2;
		if (size > 0)
		{
			if (strEncode)
			{
				n = fnEncode6BitBuf((char*)buf, mEncodeBuf, size, sizeof(mEncodeBuf));
				memcpy(pSendData,mEncodeBuf,n);
				pSendData += n; nLen += n;
			}
			else
			{
				memcpy(pSendData,buf,size);
				pSendData += size;nLen += size;

			}
		}
		*pSendData = ef; nLen ++;
		m_Socket->SendMsg(&m_SendData[0],nLen);
		msgCode ++;
		if (msgCode >= 10) msgCode = 1;
	}
}
