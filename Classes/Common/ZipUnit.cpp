#include "ZipUnit.h"

unsigned char*  UnCompression(const unsigned char* pSrcData,int nLen,int &Len)
{
	uLongf nCurSize = 1048576; //每次一兆- 不满的话循环十次
	unsigned char* pDest = nullptr;
	for(int i = 0;i < 10;i++)
	{
		uLongf alen = nCurSize * (i + 1);
		pDest =  new unsigned char[alen];
		int ret = uncompress(pDest,&alen,pSrcData,nLen);
		if(ret == Z_OK)
		{
			Len = alen;

			return pDest;
		}else if(ret == Z_BUF_ERROR)
		{
			delete []pDest;
		}else
		{
			break;
		}
	}
	
	if(pDest) delete []pDest;

	return nullptr;
}

unsigned char* CompressionStream(const unsigned char* pSrcData,int nLen)
{
	unsigned char* pData = nullptr;
	return pData;
}