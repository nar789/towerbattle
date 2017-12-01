#include "Info.h"


Scene* Info::createScene()
{
	auto scene=Scene::create();
	auto layer=Info::create();
	scene->addChild(layer);
	return scene;
}


void Info::Makeinfolayer()
{
	infolayer=LayerColor::create(Color4B(108,208,240,150));
	
	infolayer->setContentSize(Size(this->getContentSize().width,this->getContentSize().height));
	this->addChild(infolayer,1);
}

void Info::DrawBg()
{
	int n=rand()%2;
	String txt;
	txt.initWithFormat("box%d.png",n);
	auto b=Sprite::create(txt.getCString());
	b->setPosition(0,0);
	this->addChild(b,0);


	auto j=JumpBy::create(4.0f,Vec2(this->getContentSize()),300,4);
	auto f=FadeOut::create(1.0f);
	auto m=MoveTo::create(0.1f,Vec2(0,0));
	auto m2=MoveTo::create(0.1f,Vec2(0,this->getContentSize().height/2));
	auto fi=FadeIn::create(0.1f);
	auto j2=JumpBy::create(4.0f,Vec2(this->getContentSize().width,0),300,4);
	auto s=Sequence::create(j,f,m2,fi,j2,f,m,fi,NULL);
	b->runAction(RepeatForever::create(s));
}

void Info::DrawPoint()
{
	String txt;
	txt.initWithFormat("%dP",point);
	pointlab=LabelTTF::create(txt.getCString(),"Arial",200);
	
	pointlab->setPosition(this->getContentSize().width/2,this->getContentSize().height-300);
	infolayer->addChild(pointlab,1);
	
	
}

void Info::httpgetpoint()
{
	HttpRequest* request=new HttpRequest();
	String srctail=Bus::getInstance()->src+"getpoint.php";
	request->setUrl(srctail.getCString());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this,httpresponse_selector(Info::httpgetpointCallback));

	//write post Data
	Bus* b=Bus::getInstance();
	string email=b->email.c_str();
	
	string data="email="+email;



	request->setRequestData(data.c_str(),data.length());
	request->setTag("POST Point");

	HttpClient::getInstance()->send(request);
	request->release();
}

void Info::httpgetpointCallback(HttpClient* sender,HttpResponse* response)
{
	if(!response)
		return;

	if(0!=strlen(response->getHttpRequest()->getTag()))
	{
		
		long code=response->getResponseCode();

		std::vector<char>* buffer=response->getResponseData();

		string str;
		string number;
		for(int i=0;i<buffer->size();i++)
		{
			str.push_back((*buffer)[i]);
			
			if((*buffer)[i]==']')
				break;

			if(i>=86)
				number.push_back((*buffer)[i]);
		}

		Bus* b=Bus::getInstance();
		b->point=atoi(number.c_str());
		point=b->point;
		DrawPoint();
		MovePoint();
		MakeButton();
	}

}

void Info::MakeButton()
{
	auto cashitem=MenuItemImage::create("cash.png","cash_press.png",this,menu_selector(Info::menucashCallback));
	float width=this->getContentSize().width/2;
	float height=pointlab->getPositionY()-(this->getContentSize().height/10*2);
	cashitem->setScaleX(this->getContentSize().width/1080);
	cashitem->setScaleY(this->getContentSize().height/1920);
	cashitem->setPosition(width,height);
	
	auto startitem=MenuItemImage::create("start.png","start_press.png",this,menu_selector(Info::menustartCallback));
	startitem->setScaleX(this->getContentSize().width/1080);
	startitem->setScaleY(this->getContentSize().height/1920);
	height-=this->getContentSize().height/10;
	startitem->setPosition(width,height);

	auto updateitem=MenuItemImage::create("update.png","update_press.png",this,menu_selector(Info::menuupdateCallback));
	updateitem->setScaleX(this->getContentSize().width/1080);
	updateitem->setScaleY(this->getContentSize().height/1920);
	height-=this->getContentSize().height/10;
	updateitem->setPosition(width,height);


	auto logoutitem=MenuItemImage::create("logout.png","logout_press.png",this,menu_selector(Info::menulogoutCallback));
	logoutitem->setScaleX(this->getContentSize().width/1080);
	logoutitem->setScaleY(this->getContentSize().height/1920);
	height-=this->getContentSize().height/10;
	logoutitem->setPosition(width,height);

	

	auto exititem=MenuItemImage::create("exit.png","exit_press.png",this,menu_selector(Info::menuexitCallback));
	exititem->setScaleX(this->getContentSize().width/1080);
	exititem->setScaleY(this->getContentSize().height/1920);
	height-=this->getContentSize().height/10;
	exititem->setPosition(width,height);



	auto menu=Menu::create(cashitem,startitem,updateitem,logoutitem,exititem,NULL);
	menu->setPosition(0,0);

	infolayer->addChild(menu,1);

}

void Info::menulogoutCallback(cocos2d::Ref* pSender)
{
	auto scene=CCTransitionProgressRadialCW::create(1,Login::createScene());
	Director::getInstance()->replaceScene(scene);

}

void Info::menuupdateCallback(cocos2d::Ref* pSender)
{
	MakeUpdateLayer();
	MovingInfoLayer();
	Movingupdatelayer();
	DrawUpdateLayer();

}

void Info::MovingInfoLayer()
{
	
	auto m=MoveBy::create(1.0f,Vec2(this->getContentSize().width,0));
	infolayer->runAction(Repeat::create(m,1));

}

void Info::DrawUpdateLayer()
{
	string email_str=Bus::getInstance()->email.c_str();
	auto emaillabel=LabelTTF::create(email_str.c_str(),"Arial",this->getContentSize().height/20);
	emaillabel->setPosition(updatelayer->getContentSize().width/2,updatelayer->getContentSize().height-400);

	updatelayer->addChild(emaillabel,1);

	Size editsize;
	Size visiable;
	visiable=updatelayer->getContentSize();

	editsize.setSize(visiable.width/2,visiable.height/15);
	update_password=EditBox::create(editsize,Scale9Sprite::create("button.png"));
	update_password->setScaleX(this->getContentSize().width/1080);
	update_password->setScaleY(this->getContentSize().height/1920);
	update_password->setPosition(ccp(visiable.width/2,visiable.height-800));
	update_password->setFontColor(ccc3(255,255,255));
	update_password->setFontSize(10);
	update_password->setPlaceholderFontSize(10);
	update_password->setPlaceHolder("Password");
	update_password->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	update_password->setInputMode(cocos2d::extension::EditBox::InputMode::SINGLE_LINE);
	update_password->setInputFlag(cocos2d::extension::EditBox::InputFlag::PASSWORD);
	update_password->setMaxLength(20);
	update_password->setText(Bus::getInstance()->password.c_str());
	
	updatelayer->addChild(update_password,1);


	editsize.setSize(visiable.width/2,visiable.height/15);

	update_account=EditBox::create(editsize,Scale9Sprite::create("button.png"));
	update_account->setScaleX(this->getContentSize().width/1080);
	update_account->setScaleY(this->getContentSize().height/1920);
	update_account->setPosition(ccp(visiable.width/2,visiable.height-1000));
	update_account->setFontColor(ccc3(255,255,255));
	update_account->setFontSize(10);
	update_account->setPlaceholderFontSize(10);
	update_account->setPlaceHolder("Account");
	update_account->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	update_account->setInputMode(cocos2d::extension::EditBox::InputMode::EMAIL_ADDRESS);
	update_account->setMaxLength(30);
	update_account->setText(Bus::getInstance()->account.c_str());
	
	updatelayer->addChild(update_account,1);



	auto backitem=MenuItemImage::create("back.png","back_press.png",this,menu_selector(Info::infoCallback));
	backitem->setScaleX(this->getContentSize().width/1080);
	backitem->setScaleY(this->getContentSize().height/1920);
	backitem->setPosition(ccp(visiable.width/2+(backitem->getContentSize().width/2),visiable.height/2-800));

	auto registitem=MenuItemImage::create("alter.png","alter_press.png",this,menu_selector(Info::alterCallback));
	registitem->setPosition(ccp(visiable.width/2-(registitem->getContentSize().width/2),visiable.height/2-800));
	registitem->setScaleX(this->getContentSize().width/1080);
	registitem->setScaleY(this->getContentSize().height/1920);
	
	auto pMenu=Menu::create(backitem,registitem,NULL);
	pMenu->setPosition(ccp(0,0));
	
	
	updatelayer->addChild(pMenu);


}


void Info::alterCallback(cocos2d::Ref* pSender)
{
	httpinfo();
}

void Info::httpinfo()
{

		HttpRequest* request=new HttpRequest();
		String srctail=Bus::getInstance()->src+"alter_process.php";
		request->setUrl(srctail.getCString());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this,httpresponse_selector(Info::httpinfoCallback));

	//write post Data
	Bus* b=Bus::getInstance();
	string email=b->email.c_str();
	string password=update_password->getText();
	string account=update_account->getText();
	
	string data="email="+email+"&password="+password+"&account="+account;



	request->setRequestData(data.c_str(),data.length());
	request->setTag("POST Info");

	HttpClient::getInstance()->send(request);
	request->release();

}

void Info::httpinfoCallback(HttpClient* sender,HttpResponse* response)
{

	
	if(!response)
		return;

	if(0!=strlen(response->getHttpRequest()->getTag()))
	{
		
		long code=response->getResponseCode();

		std::vector<char>* buffer=response->getResponseData();

		string str;
		for(int i=0;i<buffer->size();i++)
		{
			str.push_back((*buffer)[i]);
		}


		MessageBox("Update Success!!","Congraturation!");

		
	}





}

void Info::infoCallback(cocos2d::Ref* pSender)
{
	auto m=MoveBy::create(1.0f,Vec2(-this->getContentSize().width,0));

	MovingBackUpdateLayer();

	infolayer->runAction(Repeat::create(m,1));


}
void Info::MovingBackUpdateLayer()
{
	auto m=MoveBy::create(1.0f,Vec2(-this->getContentSize().width,0));
	updatelayer->runAction(Repeat::create(m,1));
}

void Info::Movingupdatelayer()
{
	auto m=MoveBy::create(1.0f,Vec2(this->getContentSize().width,0));
	updatelayer->runAction(Repeat::create(m,1));
}
void Info::MakeUpdateLayer()
{
	updatelayer=LayerColor::create(Color4B(108,208,240,150));
	updatelayer->setPosition(-infolayer->getContentSize().width,0);
	updatelayer->setContentSize(infolayer->getContentSize());
	this->addChild(updatelayer,1);

}

void Info::menuexitCallback(cocos2d::Ref* pSender)
{
	exit(1);

}

void Info::menustartCallback(cocos2d::Ref* pSender)
{
	auto scene=CCTransitionProgressRadialCW::create(1,Game::createScene());
	Director::getInstance()->replaceScene(scene);
}


void Info::menucashCallback(cocos2d::Ref* pSender)
{
	httpcash();

}


void Info::httpcash()
{
	HttpRequest* request=new HttpRequest();
	String srctail=Bus::getInstance()->src+"cash.php";
	request->setUrl(srctail.getCString());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this,httpresponse_selector(Info::httpcashCallback));

	//write post Data
	Bus* b=Bus::getInstance();
	string email=b->email.c_str();
	
	string data="email="+email;



	request->setRequestData(data.c_str(),data.length());
	request->setTag("POST Cash");

	HttpClient::getInstance()->send(request);
	request->release();
}

void Info::httpcashCallback(HttpClient* sender,HttpResponse* response)
{

		if(!response)
		return;

	if(0!=strlen(response->getHttpRequest()->getTag()))
	{
		
		long code=response->getResponseCode();

		std::vector<char>* buffer=response->getResponseData();

		string str;
		for(int i=0;i<buffer->size();i++)
		{
			str.push_back((*buffer)[i]);
		}


		MessageBox("Cashable Success!","Congraturation!");

		
	}


}


void Info::MovePoint()
{

	auto s=ScaleBy::create(0.5f,1.1f,1.1f);
	auto s2=ScaleTo::create(0.5f,1.f,1.f);
	auto seq=Sequence::create(s,s2,NULL);
	pointlab->runAction(RepeatForever::create(seq));
}

bool Info::init()
{
	if(!LayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		return false;
	}
	
	
	//initialize
	point=0;
	pointlab=NULL;
	
	//Draw
	httpgetpoint();
	Makeinfolayer();
	DrawBg();
	



	//touch//
	auto listener=EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	
	listener->onTouchBegan=[=](Touch* touch , Event* event){


		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	/////////
	return true;
}