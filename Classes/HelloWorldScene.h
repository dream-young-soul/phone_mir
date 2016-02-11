#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
//#include "./Common/VDImageDatas.h"
//#include "MapUnit.h"

#include "cocos-ext.h"
//#include "cocostudio/CocoStudio.h"
USING_NS_CC_EXT;
#include "cocostudio/CocoStudio.h"
using namespace cocos2d;
class TPlayScene;
using namespace cocos2d::ui;

class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	//virtual void visit(Renderer* renderer, const Mat4 &parentTransform, uint32_t parentFlags) override;;

	//void onDraw();
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
private:
	CustomCommand _command;
private:
	bool onTouchesBegan(Touch *touch, Event *unused_event);
	void onTouchesMoved(Touch *touch, Event *unused_event);
	void onTouchesEnded(Touch *touch, Event *unused_event);
	void onTouchesCancelled(Touch *touch, Event *unused_event);

	TPlayScene* player;
	void _update(float fDelay);

	void Demo_click(CCObject* pSender,TouchEventType type);


};

#endif // __HELLOWORLD_SCENE_H__
