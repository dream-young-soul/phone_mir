#ifndef CJoyVirtualKey_H_
#define CJoyVirtualKey_H_
//ÐéÄâ°´¼ü-2015.8.10
#include "cocos2d.h"
#include "../GameStruct.h"
#include <vector>
#include "ui/CocosGUI.h"
using namespace cocos2d;
class CJoyVirtualKey
{
public:
	CJoyVirtualKey(void);
	~CJoyVirtualKey(void);
	void Show(cocos2d::Layer* layer);
	void Hide();

	static CJoyVirtualKey* GetInstance();
private:
	cocos2d::Layer* m_Layer;
	cocos2d::Texture2D* m_BGTex;
	cocos2d::Image* m_BGImage;
	std::vector<TClientMagic*> m_HotKeyList;
	void CreateBGSprite(cocos2d::Vec2 pos);

	void btn_key1_click(cocos2d::Ref* pSender,ui::Widget::TouchEventType type);
};


#endif 