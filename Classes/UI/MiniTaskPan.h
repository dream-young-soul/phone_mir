#ifndef MINITASKPAN_H_
#define MINITASKPAN_H_
#include "cocos2d.h"
#include "BaseDialog.h"
//√‘ƒ„»ŒŒÒ¿∏- 
//2015.8.8
class TVDImage;
namespace VD_UI
{
	class CMiniTaskPan : public CBaseDialog
	{
	public:
		CMiniTaskPan(void);
		~CMiniTaskPan(void);
		void Show(cocos2d::Layer* layer /* = nullptr */);
		void Hide();
		void Render();
		void MouseDown(cocos2d::Vec2 pos);
		bool DMiniTaskPanelClickFun(cocos2d::Vec2 pos);
		void ProcessTask();
		void DestoryClickPoint();
	private:
		cocos2d::Layer* m_Layer;
		std::vector<TVDImage*> m_ListImg;
		bool RequireAddPoints;
		std::vector<TClickPoint*> MDlgPoints;
		std::string SelectMenuStr;
		unsigned long LastestClickTime;
	};
}

#endif
