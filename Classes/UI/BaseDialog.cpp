#include "BaseDialog.h"

namespace VD_UI
{
	CBaseDialog::CBaseDialog(void)
	{
		m_bVisible = false;
	}


	CBaseDialog::~CBaseDialog(void)
	{
	}

	void CBaseDialog::Show(cocos2d::Layer* layer)
	{
		m_bVisible = true;
	}

	void CBaseDialog::Hide()
	{
		m_bVisible = false;
	}

	void CBaseDialog::SetRect(TRect_ size)
	{
		m_Size =  size;
	}
	void CBaseDialog::SetRect(int x,int y,int width,int height)
	{
		m_Size.Left = x;
		m_Size.Right =  width;
		m_Size.Top = y;
		m_Size.Bottom = height;
	}

	cocos2d::Rect CBaseDialog::GetRect()
	{
		cocos2d::Rect r = cocos2d::Rect(m_Size.Left,m_Size.Top,m_Size.Right,m_Size.Bottom);
		return r;
	}
}

