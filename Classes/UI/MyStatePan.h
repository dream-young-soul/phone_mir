#ifndef MYSTATEPAN_H_
#define MYSTATEPAN_H_
//×óÉÏ½Ç¶Ô»°¿ò
//2017.7.14
#include "cocos2d.h"
#include "BaseDialog.h"
namespace VD_UI
{
	class CMyStatePan : public CBaseDialog
	{
	public:
		CMyStatePan(void);
		~CMyStatePan(void);
		void Show(cocos2d::Layer* layer /* = nullptr */);
		void Hide();
		void Render();
	private:
		cocos2d::Layer* m_Layer;
		cocos2d::Label* m_LabelName;
		cocos2d::Label* m_LabelLv;
	};
}
#endif
