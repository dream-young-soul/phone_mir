//ÎÄ¼þ¶ÁÐ´Á÷
//time 2015.5.23 0:16                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                   
#ifndef FILESTREAM_H_
#define FILESTREAM_H_
#include <string>

class CFileStream
{
public:
	CFileStream();
	~CFileStream(void);
private: 
	const unsigned char* m_pData;
	int m_nLen;
	long m_nOffSet;
public:
	bool Init(const unsigned char* pData,const long nLen);
	char readByte();
	short readShort();
	int readInt();
	long readLong();
	double readDouble();
	void* readData(const int nLen);

	std::string readString(const int nLen);
};

#endif
