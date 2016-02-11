#ifndef _ICONVSTRING_H_
#define _ICONVSTRING_H_
#include <string>
void GBKToUTF8(char* srcbuf, int srclen, char* destbuf, int destlen);  
std::string GBKToUTF8_string(const char* srcbuf,int srclen);

void UTF8ToGBK(char* srcbuf, int srclen, char* destbuf, int destlen); 
std::string UTF8ToGBK_string(const char* srcbuf,int srclen);
#endif