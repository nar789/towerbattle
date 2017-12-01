#pragma once

#include "cocos2d.h"
#include "Game.h"
#include "Bus.h"
#include "extensions/cocos-ext.h"
#include "network/HttpClient.h"
#include "network/HttpRequest.h"
#include "network/HttpResponse.h"
#include "Info.h"

using namespace cocos2d;
using namespace cocos2d::extension;
using namespace cocos2d::network;


class Login : public cocos2d::LayerColor
{
public:
	//basic
	virtual bool init();  
	static cocos2d::Scene* createScene();
	CREATE_FUNC(Login);

	//add function
	void titleLayer(Layer* dhis);
	void MakeEdit(Layer* dhis);
	void MovingEdit();
	void MovingBackEdit();
	void MakeLoginLayer();
	void MakejoinLayer();
	void MovingJoin();
	void MakeJoinEdit();
	void MovingBackJoin();

	//http
	void httplogin();
	void httpjoin();
	void httpgetaccount();

	//http Callback
	void httploginCallback(HttpClient* sender,HttpResponse* response);
	void httpjoinCallback(HttpClient* sender,HttpResponse* response);
	void httpgetaccountCallback(HttpClient* sender,HttpResponse* response);

	
	// callback
	void menuloginCallback(cocos2d::Ref* pSender);
	void menujoinCallback(cocos2d::Ref* pSender);
	// join layer button callback
	void menuBackCallback(cocos2d::Ref* pSender);
	void menuRegistCallback(cocos2d::Ref* pSender);
	
	
	//add ver
	Size visiable;	
	EditBox* medit;
	EditBox* pedit;

	EditBox* join_email;
	EditBox* join_password;
	EditBox* join_account;


	bool firsttouch;


	//add layer
	LayerColor* loginlayer;
	LayerColor* joinlayer;
	

};

