#include "IconvString.h"
#include "cocos2d.h"
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
#include "iconv.h"
#pragma comment(lib, "libiconv.lib")  
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID)
#include "../../cocos2d/iconv/include/iconv.h"
#endif




static void Convert(char* from_charset, char* to_charset, char* inbuf, size_t inlen, char* outbuf, size_t outlen)  
{ 

	iconv_t iconvH = iconv_open(to_charset, from_charset);  
	if(!iconvH)  
		return;  
	memset(outbuf, 0, outlen);  
#if(CC_TARGET_PLATFORM == CC_PLATFORM_WIN32)
	const char* pTemp = inbuf;  
	const char** pIn = &pTemp;  
	char** pOut = &outbuf;  
	if(!iconv(iconvH, pIn, &inlen, pOut, &outlen))  
	{  
		iconv_close(iconvH);  
		return;  
	}  
#elif(CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID) 
	char* pTemp = inbuf;  
	char** pIn = &pTemp;  
	char** pOut = &outbuf; 
	bool ret = iconv(iconvH, pIn, &inlen, pOut, &outlen);
	if(!ret)  
	{  
		iconv_close(iconvH);  
		return;  
	}  
#endif  
}  

void GBKToUTF8(char* srcbuf, int srclen, char* destbuf, int destlen)  
{  
	Convert("gb2312", "utf-8", srcbuf, srclen, destbuf, destlen);  
}  

std::string GBKToUTF8_string(const char* srcbuf,int srclen)
{
	std::string str;
	char destchar[4196]={0};
	GBKToUTF8((char*)srcbuf,srclen,destchar,sizeof(destchar));
	str = destchar;
	return str;
}

void UTF8ToGBK(char* srcbuf, int srclen, char* destbuf, int destlen)
{
	Convert( "utf-8","gb2312", srcbuf, srclen, destbuf, destlen);  
}
std::string UTF8ToGBK_string(const char* srcbuf,int srclen)
{
	std::string str;
	char destchar[4196]={0};
	UTF8ToGBK((char*)srcbuf,srclen,destchar,sizeof(destchar));
	str = destchar;
	return str;
}