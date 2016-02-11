//time: 2015.5.22 23:44
#ifndef TVDIMAGEDATAS_H_
#define TVDIMAGEDATAS_H_



#include "../GameStruct.h"

#include <map>
#include "cocos2d.h"
//#include "VDImage.h"
class TVDImage;

class TVDImageDatas
{
private:
	std::string FileName;
	TVDDataHeader Header;
	std::map<int,TVDImage*> m_Images;
	cocos2d::Data m_fData;

	unsigned long m_dwMemChecktTick;
public:
	TVDImageDatas(std::string sFileName);
	~TVDImageDatas(void);

	static TVDImageDatas* Create(const std::string sFileName);

	void Initialize();
	bool FreeOldMemorys();//释放无用纹理
	TVDImage* GetImage(int idx);
	void Destory();
	const char* GetFileName(){return FileName.c_str();}

	
};
#endif
