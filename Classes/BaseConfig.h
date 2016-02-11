//本地基本数据库-
#ifndef BASECONFIG_H_
#define BASECONFIG_H_
#include "GameStruct.h"
#include <vector>
#include <map>
class CBaseConfig
{
public:
	CBaseConfig(void);
	~CBaseConfig(void);
	static CBaseConfig* GetInstance();

	bool LoadConfig();
	bool LoadClientStdItemsData(); //加载基本物品数据库
	bool LoadClientAdditionItemsData(); //加载物品附加数据库,里面暂时只有品质
private:

};

#endif

