#ifndef NPCDIALOG_H_
#define NPCDIALOG_H_
#include "cocos2d.h"
#include <string>
#include <vector>
#include "GameStruct.h"
#include "BaseDialog.h"
#include "ui/CocosGUI.h"
//NPC∂‘ª∞øÚ¿‡ 2015.6.28
using namespace cocos2d;
class TVDImage;
namespace VD_UI 
{

	class CNpcDialog : public CBaseDialog
	{
	public:
		//static CNpcDialog* GetInstance();
		CNpcDialog(void);
		~CNpcDialog(void);
		void Show(std::string npcname,std::string saying,cocos2d::Layer* layer);
		void Hide();
		void MouseDown(cocos2d::Vec2 pos);
		void SetRect(int x,int y,int width,int height);
		void Render();
	private:
		void ProcessScripte();
		std::string m_sNpcName;
		std::string m_sSaying;
		cocos2d::Layer* m_Layer;
		void DrawFontEx(std::string str,int nx,int ny,
			unsigned long Color = 0xFFFFFFFF,bool HaveStroke = false,unsigned long StrokeColor = 0xFF000000,
			bool underline = false,bool HaveBackGround= false, unsigned long BackGroundColor = 0xFF000000);

		bool RequireAddPoints;
		std::vector<TClickPoint*> MDlgPoints;

		void DestoryClickPoint();
		std::string SelectMenuStr;
		void btn_Close_click(Ref* pSender,ui::Widget::TouchEventType type);

		unsigned long LastestClickTime;
		void DoLocalTaskCMD(int nTaskID,std::string sCMD);
		cocos2d::Vec2 mBtnCloseXY;
		TRect_ mOldSize;
		std::vector<TVDImage*> m_ListImg;
	};

}

#endif