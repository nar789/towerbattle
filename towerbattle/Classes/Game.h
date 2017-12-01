#pragma once

#include "cocos2d.h"
#include "Box2D/Box2D.h"
#include "Login.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"




#define PTM_RATIO 192
#define POLYGON_SORT 2

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::network;

class Game : public cocos2d::LayerColor
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
	int cp_height;
	bool end;

	float start_pointlabel_height;
	float start_pointlabel_width;
	
	
	
	//add var
	cocos2d::LabelTTF* label;
	int stage_number;
	cocos2d::LabelTTF* pointlabel;
	cocos2d::MenuItemImage* stopmenu;
	bool stopmenuvisible;
	cocos2d::LayerColor* pointlayer;

	MenuItemImage* homebutton;


	//func
	cocos2d::LayerGradient* bglayer;
	void makebglayer(int number);
	void makelabel(int number);
	void drawcoin();
	void drawpoint();
	void updatepoint(int add);
	void drawstop();
	void menustopCallback(cocos2d::Ref* pSender);
	void drawpointlayer();
	void drawcoinupdown();
	void drawending();

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




	
	//http request
	void httpgetpoint();
	void httpsavepoint();
	
	//http call back 
	void httpgetpointCallback(HttpClient* sender,HttpResponse* response);
	void httpsavepointCallback(HttpClient* sender,HttpResponse* response);

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
	void menuHomebuttonCallback(cocos2d::Ref* pSender);

	
    
    // implement the "static create()" method manually
    CREATE_FUNC(Game);
};