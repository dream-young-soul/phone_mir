#ifndef MAPMINITITLE_H_
#define MAPMINITITLE_H_
//迷你地图框，绘制地图名称与坐标
#include "BaseDialog.h"
#include "cocos2d.h"
namespace VD_UI
{
	class CMapMiniTitle : public CBaseDialog
	{
	public:
		CMapMiniTitle(void);
		~CMapMiniTitle(void);
		void Show(cocos2d::Layer* layer /* = nullptr */);
		void Hide();
		void Render();
		void MouseDown(cocos2d::Vec2 pos);
	private:
		cocos2d::Layer* m_Layer;
		cocos2d::Label* m_LabelName; //地图名称标签
		cocos2d::Label* m_LabelPoint; //地图坐标
	};
}

#endif
