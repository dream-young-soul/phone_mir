#include "HitDialog.h"
#include "../MShare.h"
#include "../Common/Grobal2.h"
#include "../VD_Share.h"
#include "../PlayScene.h"
#include "../VDImage.h"
namespace VD_UI
{
	CHitDialog::CHitDialog(void)
	{
		m_Layer = nullptr;
	}


	CHitDialog::~CHitDialog(void)
	{
	}
	
	void CHitDialog::ClearHint()
	{
		HintList.clear();
		HintListRight.clear();
	}
	void CHitDialog::MouseDown(cocos2d::Vec2 pos)
	{

	}
	void CHitDialog::ShowHint(cocos2d::Layer* layer,int x,int y,std::string str,unsigned long Color, bool drawUp,
		unsigned long bColor /* = 0 */,std::string RightStr/* ="" */)
	{
		
		if(m_Layer)Hide();
		CBaseDialog::Show(layer);
		m_Layer = cocos2d::Layer::create();
		m_Layer->retain();
		layer->addChild(m_Layer);
		ClearHint();
		HintX = x;
		HintY = y;
		HintWidth = 0;
		HintWidthLeft = 0;
		HintHeight = 0;
		HintUp = drawUp;
		HintColor = Color;
		BackColor = bColor;

		int n = 0;
		std::string data;
		//计算左边文字宽高
		while(true)
		{
			n++;
			if(n > 2000)break;
			if(str.length() == 0)break;
			if((int)str.find("\\") >= 0)
			{
				str = GetValidStr3Ex(str,data,'\\');
			}else if((int)str.find("^") >= 0)
			{
				str = GetValidStr3Ex(str,data,'^');
			}else //无法解析道具说明的\\符号
			{
				HintList.push_back(str);
				break;
			}
			int w = GetStrWidth(data) + 8;
			if(w > HintWidth) HintWidth = w;
			if(data.length() > 1)
			{
				HintList.push_back(data);
			}
		}
		HintWidthLeft = HintWidth;
		HintHeight = (TextWidth("A") + 3) * (int)HintList.size() + 3 * 2;
		 //计算右边文字宽高 并更新整体宽度高度
		n = 0;
		int leftWidth =0;
		while(true)
		{
			n++;
			if(n > 2000)break;
			if(RightStr.length() == 0)break;
			if((int)RightStr.find("\\") >= 0)
			{
				RightStr = GetValidStr3Ex(RightStr,data,'\\');
			}else if((int)RightStr.find("^") >= 0)
			{
				RightStr = GetValidStr3Ex(RightStr,data,'^');
			}	
			int w = GetStrWidth(data) + 8;
			if(w > leftWidth) leftWidth = w;
			if(data.length() > 0)
			{
				HintListRight.push_back(data);
			}
		}
		n = (TextWidth("A") + 3) * (int)HintListRight.size() + 3 * 2;
		if(leftWidth > 0) HintWidth = HintWidthLeft + leftWidth + 10;
		if(n > HintHeight) HintHeight = n;
		if(HintUp) HintY = HintY - HintHeight;
		//超出屏幕范围的处理 2013.9.24
		if(HintY + HintHeight > SCREENHEIGHT)
		{
			HintY = SCREENHEIGHT  - HintHeight;
		}
		DrawHint();

	}
	void CHitDialog::Hide()
	{
		if(!m_Layer)return;
		m_Layer->removeAllChildrenWithCleanup(true);
		m_Layer->release();
		m_Layer = nullptr;
		CBaseDialog::Hide();
	}

	int CHitDialog::GetStrWidth(std::string str)
	{
		std::string tmp,odd;
		int s = 0,e = 0,r = 0;
		int result =0;
		odd = str;
		if((int)odd.find("[") >= 0)
		{
			while(odd.length() > 0)
			{
				tmp = "";
				odd = GetBeforeStr(odd,tmp,"[");
				r += TextWidth(tmp);
				if(odd.length() > 0)
				{
					odd = GetBeforeStr(odd,tmp,"]");
					if(tmp.length() > 0)
					{
						if((int)tmp.find("img:") == 0)
						{
							r += 16;
						}else if((int)tmp.find("item:") == 0)
						{
							r += 16;
						}else if((int)tmp.find("color:") == 0 ||
							(int)tmp.find("/color") == 0 ||
							(int)tmp.find("bold:") == 0 ||
							(int)tmp.find("/bold") == 0)
						{

						}else
						{
							std::string a = "[" +tmp + "]";
							r += TextWidth( a);
						}
					}
				}
			}
		}
		return result;
	}

	void CHitDialog::DrawHint()
	{

		//内容
		unsigned long mColor;
		int nx = 0, ny = 0, n = 0, hx = 0, hy = 0, ay = 0;
		std::string str,str1;
		std::string odd,tmp;
		TVDImage* img;
		unsigned char bbold;
		std::string utf8_str;

		img = GetUIImage(510);
		if(img && img->Image_)
		{
			m_Layer->addChild(img->GetImage(m_Size.Left,m_Size.Top));
		}
		if((int)HintList.size() > 0)
		{
			mColor = HintColor & 0xFF000000;
			ay = 0;
			ny = ay + hy + 3;
			for(int i = 0;i < (int)HintList.size();i++)
			{
				nx  = hx + 4;
				str = HintList[i];
				if(str[0] == 'R')
				{
					str = str.substr(1,str.length() - 1);
					mColor = 0xFFFF0000;
				}
				if(str[0] == 'Y')
				{
					str = str.substr(1,str.length() - 1);
					mColor = 0xFF00FFFF;
				}
				if(str[0] == 'B')
				{
					str = str.substr(1,str.length() - 1);
					mColor = 0xFF0000FF;
				}
				if(str[0] == 'G')
				{
					str = str.substr(1,str.length() - 1);
					mColor = 0xFF00FF00;
				}
				if(str[0] == 'F')
				{
					str = str.substr(1,str.length() - 1);
					mColor = 0xFFFF00FF;
				}
				if(str[0] == 'Q')
				{
					str = str.substr(1,str.length() - 1);
					mColor = 0xFFFFFF00;
				}
				if(str[0] == 'Z')
				{
					str = str.substr(1,str.length() - 1);
					mColor = 0xFFCC2277;
				}
				if(str[0] == 'H')
				{
					str = str.substr(1,str.length() -1);
					mColor = 0xFF808080;
				}
				if((int)str.find("[") >= 0)
				{
					odd =str;
					while(odd.length() > 0)
					{
						odd = GetBeforeStr(odd, tmp, "[");
						if(tmp.length() > 0)
						{
							TPlayScene::GetInstance()->DrawFontEx(m_Layer,tmp,
								m_Size.Left + nx,m_Size.Top +  ny,mColor,false);
							nx += TextWidth(tmp);
						}
						if(odd.length() > 0)
						{
							odd = GetBeforeStr(odd, tmp, "]");
							if((int)tmp.find("img:") == 0)
							{
								str1 = tmp.substr(4);
								n = atoi(str1.c_str());
								img = GetUIImage(n);
								if(img && img->Image_)
								{
									m_Layer->addChild(img->GetImage(m_Size.Left + nx,m_Size.Top + ny));
								}
								nx += 16;
							}else if((int)tmp.find("item:") == 0)
							{
								str1 = tmp.substr(5);
								n = atoi(str1.c_str());
								img = GetBagImage(n);
								if(img && img->Image_)
								{
									m_Layer->addChild(img->GetImage(m_Size.Left + nx,m_Size.Top + ny));
								}
								nx += 16;
							}else if((int)tmp.find("line:") == 0)
							{
								//画线
							}else if((int)tmp.find("color:") == 0)
							{
								str1 = tmp.substr(6);	
								mColor = 0xffffffff;
								//mColor = str_to_hex(str1);
							}else if((int)tmp.find("/color") == 0)
							{
								mColor = HintColor | 0xFF000000;
							}else if((int)tmp.find("bold:") == 0)
							{
								bbold = 1;
							}else if((int)tmp.find("/bold") == 0)
							{
								bbold = 0;
							}else
							{
								tmp = "[" + tmp + "]";
								TPlayScene::GetInstance()->DrawFontEx(m_Layer,tmp,
									m_Size.Left + nx,m_Size.Top + ny,mColor,false);
								n = TextWidth(tmp);
								nx += n;
							}
						}
					}
				}else
				{
					TPlayScene::GetInstance()->DrawFontEx(m_Layer,str,
						m_Size.Left + nx,m_Size.Top + ny,mColor,false);
				}
				ny += TextWidth("A") + 10;
			}
		}
	}
}

