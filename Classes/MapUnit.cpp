#include "MapUnit.h"

#include "FileStream.h"
#include "./Common/ZipUnit.h"

static VDMap* m_Instance = nullptr;
TMapMaskInfo::TMapMaskInfo(void)
{
	MaskRect.Rect(0,0,0,0);
	Points.clear();
}
TMapMaskInfo::~TMapMaskInfo(void)
{
	Points.clear();
}

void TMapMaskInfo::LoadPointsFromStream(const unsigned char* pData,int nCount)
{
	if(nCount <= 0)return;
	Points.resize(nCount);
	CFileStream stream;
	MaskRect.Rect(0,0,0,0);
	unsigned char* p = (unsigned char*)pData;
	for(int i = 0;i < nCount;i++)
	{
		stream.Init(p,sizeof(TPoint));
		Points[i].x = stream.readInt();
		Points[i].y = stream.readInt();

		if( Points[i].x < MaskRect.Left)  MaskRect.Left = Points[i].x;
		if (Points[i].y < MaskRect.Top)  MaskRect.Top = Points[i].y;
		if (Points[i].x > MaskRect.Right)  MaskRect.Right = Points[i].x;
		if (Points[i].y > MaskRect.Bottom)  MaskRect.Bottom = Points[i].y;    
		
		p += sizeof(TPoint);
	}
	
}

bool TMapMaskInfo::InClientRect(TRect_ clientrect)
{
	cocos2d::CCRect src;
	cocos2d::CCRect dest;
	src.setRect(MaskRect.Left,MaskRect.Top,MaskRect.Left + MaskRect.Right,
		MaskRect.Top + MaskRect.Bottom);
	dest.setRect(clientrect.Left,clientrect.Top,clientrect.Left + clientrect.Right,
		clientrect.Top + clientrect.Bottom);
	if(src.intersectsRect(dest))
	{
		return true;
	}
	return false;
	//src.intersectsRect
	if(clientrect.Left >= MaskRect.Left &&
		clientrect.Right <= MaskRect.Right &&
		clientrect.Top >= MaskRect.Top &&
		clientrect.Bottom <= MaskRect.Bottom)
	{
		return true;
	}
	return false;
}
VDMap* VDMap::GetInstance()
{
	if(!m_Instance)
	{
		m_Instance = new VDMap;
	}
	return m_Instance;
}
VDMap::VDMap(void)
{
	m_Loaded = false;
	m_ClientRect.Rect(0,0,0,0);
	m_boChange = false;
	m_sMapBase = "map/";
	m_sCurrentMap = "";
	m_boSegmented = false;
	m_nSegXCount = 0;
	m_nSegYCount = 0;
	m_nCurUnitX = -1;
	m_nCurUnitY = -1;
	m_nBlockLeft = -1;
	m_nBlockTop = -1;
	m_sOldMap = "";
	m_MaskList.clear();
	m_MArr.clear();

}


VDMap::~VDMap(void)
{
	ClearMasks();
	ClearMap();
	if(m_Instance)
	{
		delete m_Instance;
		m_Instance = nullptr;
	}
}


bool VDMap::LoadMapAllArr()
{
	if(m_sOldMap.length() <= 0) return false;
	ClearMasks();
	ClearMap();
	std::string sFileName = m_sMapBase + m_sOldMap + ".vdm";
	std::string path = cocos2d::FileUtils::getInstance()->fullPathForFilename(sFileName);
	ssize_t nLen = 0;
	unsigned char* pData = cocos2d::FileUtils::getInstance()->getFileData(sFileName,"rb",&nLen);
	if(!pData || nLen <= 0)
	{
		return false;
	}
	bool ret = false;
	//读取地图头
	CFileStream stream;
	stream.Init(pData,nLen);
	std::string Title;
	Title = stream.readString(sizeof(Header.Title));
	strcpy(Header.Title,Title.c_str());
	Header.Width = stream.readShort();
	Header.Height = stream.readShort();
	Header.UpdateDate = stream.readDouble();
	Header.ZipSize = stream.readInt();
	std::string reserved;
	reserved = stream.readString(sizeof(Header.Reserved));
	strcpy(Header.Reserved,reserved.c_str());
	unsigned char* pDecData = nullptr;
	int declen = 0;
	pDecData = UnCompression(&pData[sizeof(TMapHeader)],Header.ZipSize,declen);
	
	if(pDecData)
	{
		m_MArr.resize(Header.Width);
		for(int i = 0;i < Header.Width;i++)
		{
			m_MArr[i].resize(Header.Height);
		}
		
		unsigned char* pTempDecData = pDecData;
		int count = 0;
		for(int i = 0;i < Header.Width;i++)
		{
			for(int j = 0;j < Header.Height;j++)
			{
				stream.Init(pTempDecData,sizeof(TMapInfo));
				m_MArr[i][j].reset();
				m_MArr[i][j].BkAree = stream.readShort();
				m_MArr[i][j].BkImg = stream.readShort();
				m_MArr[i][j].MidImg = stream.readShort();
				m_MArr[i][j].Area = stream.readShort();
				m_MArr[i][j].FrImg = stream.readShort();
				m_MArr[i][j].DoorIndex = stream.readByte();
				m_MArr[i][j].DoorOffset = stream.readByte();
				m_MArr[i][j].AniFrame = stream.readByte();
				m_MArr[i][j].AniTick = stream.readByte();
				m_MArr[i][j].light = stream.readByte();
				m_MArr[i][j].flags = stream.readByte();
				pTempDecData = pTempDecData + sizeof(TMapInfo);

			}
			
		}
		declen -= Header.Width * Header.Height * sizeof(TMapInfo);
		//读取蒙板信息
		if(declen > sizeof(int))
		{
			stream.Init(pTempDecData,declen);
			short maskcount = stream.readShort();
			short tw = stream.readShort();
			m_MaskList.resize(maskcount);
			pTempDecData += 4;
			for(int i = 0;i < maskcount;i ++)
			{
				stream.Init(pTempDecData,sizeof(int));
				int PointCount =stream.readInt();
				pTempDecData += 4;
				m_MaskList[i].LoadPointsFromStream(pTempDecData,PointCount);
				pTempDecData += PointCount * sizeof(TPoint);
			}
		}
		ret = true;
	}
	if(pData) delete [] pData;
	if(pDecData) delete [] pDecData;
	m_Loaded = true;
	return ret;
}

void VDMap::ClearMasks()
{
	m_MaskList.clear();
}

void VDMap::ClearMap()
{
	m_MArr.clear();
}

void VDMap::ChangeMap(const char* MpaStr)
{
	std::string mapstr;
	std::string sstr = "";
	mapstr = GetValidStr3Ex(MpaStr,sstr,'/');

	if(m_sOldMap != mapstr || m_sMapName != sstr)
	{
		m_sMapName = sstr;
		m_sOldMap = mapstr;
		m_Loaded = false;
	}
	m_OldClientRect.Top = -1;
	m_OldClientRect.Left = -1;
	VDMap::GetInstance()->LoadMapAllArr();//立即加载
}

bool VDMap::CanMove(int mx,int my)
{
	bool Result = false;
	int cx =mx;
	int cy = my;
	if (cx < 0 || cy < 0 || cx >= Header.Width || cy >= Header.Height)
	{
		return Result;
	}
	if(((m_MArr[cx][cy].BkImg & 0x8000) + (m_MArr[cx][cy].FrImg & 0x8000)) == 0)
	{
		Result = true;
	}

	if(Result)
	{
		if( (m_MArr[cx][cy].DoorIndex & 0x80) > 0)
		{
			if((m_MArr[cx][cy].DoorOffset & 0x80) == 0)
			{
				Result = false;
			}
		}
	}
	return Result;

}