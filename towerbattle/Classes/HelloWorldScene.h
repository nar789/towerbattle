#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Box2D/Box2D.h"

#define PTM_RATIO 192
#define POLYGON_SORT 2


class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    b2World* _world;
	cocos2d::Sprite* bg;
	cocos2d::Sprite* line;
	cocos2d::Texture2D *texture[POLYGON_SORT];
    cocos2d::Size winSize;
	cocos2d::ParallaxNode* node;
	cocos2d::Point poly_info[POLYGON_SORT];

	cocos2d::Sprite* movePolygon[POLYGON_SORT];
	cocos2d::Sprite* number[10+1];
	
	int topHeight;
	int prevtopHeight;
	float m_diff;

	bool stop;
	bool uptiming;
	float polygon_height;
	int sort;
	int counter;

	int point; // point ! 500point/km
	
	

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    

	void tick(float dt);
	void isLine(float dt);
	void upper(float dt);
	void autoTouch(float dt);
	void count(float dt);
	void movingPolygon();
	
	void addSprite(cocos2d::Point location);
	void outline();
	void pageup();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
};

#endif // __HELLOWORLD_SCENE_H__
