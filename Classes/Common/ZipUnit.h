#ifndef ZIPUNIT_H_
#define ZIPUNIT_H_

#include <zlib/include/zlib.h>

unsigned char* UnCompression(const unsigned char* pSrcData,int nLen,int &Len);

unsigned char* CompressionStream(const unsigned char* pSrcData,int nLen);

#endif