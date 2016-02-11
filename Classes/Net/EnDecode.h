
#ifndef _ENDECODE
#define _ENDECODE


#define _DEFBLOCKSIZE		27



int memlen(const char *str);
char * strchr_ex(char *str, char ch, int len = 10240);

#define fnEncode6BitBuf	fnEncode6BitBufA
#define fnDecode6BitBuf fnDecode6BitBufA
//#define fnEncodeMessage fnEncodeMessageA
//#define fnDecodeMessage fnDecodeMessageA
//#define fnMakeDefMessage fnMakeDefMessageA


int   fnEncode6BitBufA(char *pszSrc, char *pszDest, int nSrcLen, int nDestLen);
int   fnDecode6BitBufA(char *pwszSrc, char *pszDest, int nDestLen,bool zipbuf = false);
/*int  WINAPI fnEncodeMessageA(PDEFAULTMESSAGE lptdm, char *pszBuf, int nLen);
__inline void  WINAPI fnDecodeMessageA(PDEFAULTMESSAGE lptdm, char *pszBuf)
	{ fnDecode6BitBufA(pszBuf, (char *)lptdm, sizeof(DEFAULTMESSAGE)); }

__inline void WINAPI fnMakeDefMessageA(PDEFAULTMESSAGE lptdm, WORD wIdent, int nRecog, WORD wParam, WORD wTag, WORD wSeries)
	{ lptdm->wIdent	= wIdent; lptdm->nRecog	= nRecog; lptdm->wParam	= wParam; lptdm->wTag = wTag; lptdm->wSeries = wSeries; }*/


int DecodeString(char * src, char * des, int deslen);


#endif 