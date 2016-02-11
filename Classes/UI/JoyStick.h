//摇杆类 2015.7.1
#ifndef JOYSTICK_H_
#define  JOYSTICK_H_
#include "cocos2d.h"
using namespace cocos2d;
class CJoyStick : public Node
{
public:
	CJoyStick(void);
	~CJoyStick(void);
	static CJoyStick* GetInstance();

	void Show(cocos2d::Layer* layer);
	void Hide();
	bool IsMove(){return m_IsMove;}
	int GetDir(){return m_nDir;}
	cocos2d::Vec2 GetMovePos(){return cocos2d::Vec2(m_nX,m_nY);}
private:
	cocos2d::Sprite* m_joystick;
	cocos2d::Layer* m_Layer;
	float m_R;
	cocos2d::Vec2 m_O;
	bool m_IsMove;
	int m_nDir;
	void _Update(float dt);

	bool onTouchesBegan(Touch *touch, Event *unused_event);
	void onTouchesMove(Touch *touch, Event *unused_event);
	void onTouchesEnded(Touch *touch, Event *unused_event);
	
	//求三角形面积的函数  
	float heronsformula(float x1,float y1,float x2,float y2,float x3,float y3);  

	//判断三个新三角形面积和是否等于原先三角形面积的函数  
	bool triangleContainPoint(float x1,float y1,float x2,float y2,float x3,float y3,float px,float py);  
	int m_nX;
	int m_nY;
};

#endif