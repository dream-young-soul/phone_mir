#ifndef HITDIALOG_H_
#define HITDIALOG_H_
#include "BaseDialog.h"
#include <vector>
//道具tips对话框
//2015.7.18
namespace VD_UI
{
	class CHitDialog : public CBaseDialog
	{
	public:
		CHitDialog(void);
		~CHitDialog(void);
		void ShowHint(cocos2d::Layer* layer,int x,int y,std::string str,unsigned long Color,
			bool drawUp,unsigned long bColor = 0,std::string RightStr="");
		void Hide();
		void MouseDown(cocos2d::Vec2 pos);
	private:
		cocos2d::Layer* m_Layer;
		int GetStrWidth(std::string str);
		void ClearHint();
		void DrawHint();
		std::vector<std::string> HintList;
		std::vector<std::string> HintListRight;
		int HintX,HintY,HintWidth,HintWidthLeft,HintHeight;
		bool HintUp;
		unsigned long HintColor,BackColor;
	};
}


#endif 