#pragma once

#include "cocos2d.h"
#include "Login.h"
#include "Game.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::network;


class Info : public cocos2d::LayerColor
{
public:
	//basic
	virtual bool init();  
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Info);

	//var
	int point;
	LabelTTF* pointlab;


	//Layer
	LayerColor* infolayer;
	LayerColor* updatelayer;


	//func
	void Makeinfolayer();
	void DrawBg();
	void DrawPoint();
	void MovePoint();

	void MakeButton();

	void MovingInfoLayer();
	void MakeUpdateLayer();
	void MovingBackUpdateLayer();
	void Movingupdatelayer();
	void DrawUpdateLayer();


	//EditBox;
	EditBox* update_password;
	EditBox* update_account;


	//menu
	void menucashCallback(cocos2d::Ref* pSender);
	void menustartCallback(cocos2d::Ref* pSender);
	void menuupdateCallback(cocos2d::Ref* pSender);
	void menulogoutCallback(cocos2d::Ref* pSender);
	void menuexitCallback(cocos2d::Ref* pSender);


	//updateLayer menu Callback
	void alterCallback(cocos2d::Ref* pSender);
	void infoCallback(cocos2d::Ref* pSender);


	//http 
	void httpgetpoint();
	void httpcash();
	void httpinfo();

	//http callback
	void httpgetpointCallback(HttpClient* sender,HttpResponse* response);
	void httpcashCallback(HttpClient* sender,HttpResponse* response);
	void httpinfoCallback(HttpClient* sender,HttpResponse* response);
};

