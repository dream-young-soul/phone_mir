#ifndef UI_BASE_H_
#define UI_BASE_H_

namespace VD_UI
{
	class CUIBase
	{
	public:
		CUIBase(void);
		~CUIBase(void);
	public:
		int _x;
		int _y;
		int _width;
		int _height;
		int BKImageIndex;



	};
}


#endif