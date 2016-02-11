#include "Grobal2.h"

#include "cocos2d.h"
#include "IconvString.h"


tagDefaultMessage::tagDefaultMessage()
{
	reset();
}
void tagDefaultMessage::reset(void)
{
	Recog = 0;
	Ident = 0;
	Param = 0;
	Tag = 0;
	Serise = 0;
}





unsigned char RACEfeature(int cfeature)
{
	return (unsigned char)cfeature;
}

unsigned char HAIRfeature(int cfeature)
{

	return LOBYTE_(HIWORD_(cfeature));
}
unsigned char DRESSfeature(int cfeature)
{
	return HIBYTE_(HIWORD_(cfeature));
}
unsigned char WEAPONfeature(int cfeature)
{
	return HIBYTE_(LOWORD_(cfeature));
}

unsigned char Horsefeature(int cfeature)
{
	return LOBYTE_(LOWORD_(cfeature));
}
unsigned char Effectfeature(int cfeature)
{
	return HIBYTE_(LOWORD_(cfeature));
}

unsigned char Colorfeature(int cfeature)
{
	return LOBYTE_(HIWORD_(cfeature));
}
unsigned short APPRfeature(int cfeature)
{
	return HIWORD_(cfeature);
}
std::string ArrestStringEx(std::string Source,std::string SearchAfter,std::string ArrestBefore,std::string& ArrestStr)
{
	std::string ret = "";
	ArrestStr = "";
	if(Source.length() <= 0)
	{
		return ret;
	}
	int nStart = (int)Source.find(SearchAfter);
	if(nStart >= 0)
	{
		int nEnd = (int)Source.find(ArrestBefore);
		if(nEnd >= 0)
		{
			ArrestStr = Source.substr(nStart + SearchAfter.length() ,nEnd - ArrestBefore.length());
		}
		ret = Source.substr(nEnd + ArrestBefore.length(),Source.length() - nEnd + ArrestBefore.length());
	}
	return ret;
}
std::string GetValidStr3Ex(std::string src,std::string &dest,char divider,bool utf8)
{
	dest = "";
	char* pstr;
	char* ptmp;
	int n;
	pstr = (char*)src.c_str();
	ptmp = strchr(pstr, divider);
	std::string  ret = "";
	if(ptmp)
	{
		n = ptmp - pstr;
		dest = src.substr(0, ptmp - pstr);
		n++;
		ret = src.substr(n,src.length() - n);
	}else
	{
		dest = src;
	}

	if(utf8)
	{
		char buf[1024] = {0};
		if(sizeof(buf) < dest.length())
		{
			CCLOG("GetValidStr3Ex error code ! : %d",dest.length());
		}
		GBKToUTF8((char*)dest.c_str(),dest.length(),buf,sizeof(buf));
		dest = buf;
	}
	return ret;
}

int GetBack(int dir)
{
	int Result = DR_UP;
	switch(dir)
	{
	case DR_UP: 
		{
			Result = DR_DOWN;
			break;
		}
	case DR_DOWN: 
		{
			Result = DR_UP;
			break;
		}
	case DR_LEFT:
		{
			Result = DR_RIGHT;
			break;
		}
	case DR_RIGHT: 
		{
			Result = DR_LEFT;
			break;
		}
	case DR_UPLEFT:
		{
			Result = DR_DOWNRIGHT;
			break;
		}
	case DR_UPRIGHT:
		{
			Result = DR_DOWNLEFT;
			break;
		}
	case DR_DOWNLEFT: 
		{
			Result = DR_UPRIGHT;
			break;
		}
	case DR_DOWNRIGHT:
		{
			Result = DR_UPLEFT;
			break;
		}
	}
	return Result;
}

int PrivDir(int ndir)
{
	if( ndir - 1 < 0)
	{
		return 7;
	}
	return ndir - 1;

}
int NextDir(int ndir)
{
	if( ndir + 1 > 7)
	{
		return 0;
	}
	return ndir + 1;

}

int GetDistance(int sx, int sY, int dx, int dy)
{
	int x =abs(sx - dx);
	int y = abs(sY - dy);
	int ret = MAX_(x,y );
	return ret;
}

int GetNpcOffset(int nAppr)
{
	return nAppr * 100;
}

int GetCodeMsgSize(double x)
{
	if(int(x) < x)
	{
		return int(x) + 1;
	}
	return int(x);
}

int GetFlyDirection(int sx,int sy,int ttx,int tty)
{
	int fx,fy;
	fx = ttx - sx;
	fy = tty - sy;
	sx = 0;
	sy = 0;
	int Result = DR_DOWN;
	if( fx == 0 )
	{
		if(fy < 0)
		{
			Result = DR_UP;
		}else
		{
			Result = DR_DOWN;
		}
		return Result;
	}

	if(fy==0)
	{
		if(fx < 0)
		{
			Result = DR_LEFT;
		}else
		{
			Result = DR_RIGHT;
		}
		return Result;
	}
	if(fx > 0 && fy < 0)
	{
		if(-fy > fx * 2.5)
		{
			Result = DR_UP;
		}else
		{
			Result =  DR_RIGHT;
		}
		
	}
	if(fx > 0 && fy > 0)
	{
		if(fy < fx / 3)
		{
			Result = DR_RIGHT;
		}else if(fy > fx * 2.5)
		{
			Result = DR_DOWN;
		}else
		{
			Result = DR_DOWNRIGHT;
		}
	}
	if(fx < 0 && fy > 0)
	{
		if(fy < -fx / 3)
		{
			Result = DR_LEFT;
		}else if(fy > -fx * 2.5)
		{
			Result = DR_DOWN;
		}else Result = DR_DOWNLEFT;
	}
	if(fx < 0 && fy < 0)
	{
		if(-fy > -fx * 2.5)
		{
			Result = DR_UP;
		}else if(-fy < -fx / 3)
		{
			Result =DR_LEFT;
		}else
		{
			Result = DR_UPLEFT;
		}
	}
	return Result;
}