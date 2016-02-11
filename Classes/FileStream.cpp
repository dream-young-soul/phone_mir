#include "FileStream.h"


CFileStream::CFileStream()
{

}
CFileStream::~CFileStream(void)
{

}

bool CFileStream::Init(const unsigned char* pData,const long nLen)
{
	if(!pData) return false;
	m_nOffSet = 0;
	m_pData = pData;
	if(nLen == 0)
	{
		m_nLen = strlen((const char*)m_pData);
	}else m_nLen = nLen;
	if(!pData || !m_nLen) 
	{
		return false;
	}
	return true;
	
}
char CFileStream::readByte()
{
	if(m_nOffSet >= m_nLen)return 0;
	m_nOffSet ++;
	return (char)m_pData[m_nOffSet];
	
}

short CFileStream::readShort()
{
	short* ret = 0;
	char sBuf[2] = {0,0};
	sBuf[0] = m_pData[m_nOffSet];
	sBuf[1] = m_pData[m_nOffSet + 1];
	
	ret = (short*) &sBuf;
	m_nOffSet += sizeof(short);
	return *ret;
}

int CFileStream::readInt()
{
	int* ret;
	char sBuf[4];
	sBuf[0] = m_pData[m_nOffSet];
	sBuf[1] = m_pData[m_nOffSet + 1];
	sBuf[2] = m_pData[m_nOffSet + 2];
	sBuf[3] = m_pData[m_nOffSet + 3];
	ret = (int*) &sBuf;
	
	
	m_nOffSet += sizeof(int);
	return *ret;
}

double CFileStream::readDouble()
{
	double* ret;
	char sBuf[8];
	sBuf[0] = m_pData[m_nOffSet];
	sBuf[1] = m_pData[m_nOffSet + 1];
	sBuf[2] = m_pData[m_nOffSet + 2];
	sBuf[3] = m_pData[m_nOffSet + 3];
	sBuf[4] = m_pData[m_nOffSet + 4];
	sBuf[5] = m_pData[m_nOffSet + 5];
	sBuf[6] = m_pData[m_nOffSet + 6];
	sBuf[7] = m_pData[m_nOffSet + 7];
	m_nOffSet += sizeof(double);
	ret = (double*)&sBuf;
	return *ret;
}
long CFileStream::readLong()
{
	long* ret;
	char sBuf[8];
	sBuf[0] = m_pData[m_nOffSet];
	sBuf[1] = m_pData[m_nOffSet + 1];
	sBuf[2] = m_pData[m_nOffSet + 2];
	sBuf[3] = m_pData[m_nOffSet + 3];
	sBuf[4] = m_pData[m_nOffSet + 4];
	sBuf[5] = m_pData[m_nOffSet + 5];
	sBuf[6] = m_pData[m_nOffSet + 6];
	sBuf[7] = m_pData[m_nOffSet + 7];
	m_nOffSet += sizeof(long);
	ret = (long*)&sBuf;
	return *ret;
}
void* CFileStream::readData(const int nLen)
{
	return nullptr;
}
std::string CFileStream::readString(const int nLen)
{
	std::string ret;
	char* str = new char[nLen];
	memcpy(str,&m_pData[m_nOffSet],nLen);
	ret = (const char*)str;
	m_nOffSet += nLen;
	return ret;
}
