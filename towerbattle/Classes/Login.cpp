#include "Login.h"
#include "extensions/cocos-ext.h"




using namespace cocos2d::extension;
using namespace std;



Scene* Login::createScene()
{
	auto scene=Scene::create();
	auto layer=Login::create();
	
	scene->addChild(layer);
	return scene;
}
void Login::MakeEdit(Layer* dhis){

	Size editsize;
	editsize.setSize(600,140);
	medit=EditBox::create(editsize,Scale9Sprite::create("button.png"));
	medit->setScaleX(this->getContentSize().width/1080);
	medit->setScaleY(this->getContentSize().height/1920);
	medit->setPosition(ccp(visiable.width/2,visiable.height/2+visiable.height/10*1));
	medit->setFontColor(ccc3(255,255,255));
	medit->setFontSize(10);
	medit->setPlaceholderFontSize(10);
	medit->setPlaceHolder("E-mail");
	medit->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	medit->setInputMode(cocos2d::extension::EditBox::InputMode::EMAIL_ADDRESS);
	medit->setMaxLength(30);
	
	loginlayer->addChild(medit,1);


	editsize.setSize(600,140);
	pedit=EditBox::create(editsize,Scale9Sprite::create("button.png"));
	pedit->setScaleX(this->getContentSize().width/1080);
	pedit->setScaleY(this->getContentSize().height/1920);
	pedit->setPosition(ccp(visiable.width/2,visiable.height/2-visiable.height/10*1));
	pedit->setFontColor(ccc3(255,255,255));
	pedit->setFontSize(10);
	pedit->setPlaceholderFontSize(10);
	pedit->setPlaceHolder("Password");
	pedit->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	pedit->setInputMode(cocos2d::extension::EditBox::InputMode::SINGLE_LINE);
	pedit->setInputFlag(cocos2d::extension::EditBox::InputFlag::PASSWORD);
	pedit->setMaxLength(20);
	
	loginlayer->addChild(pedit,1);


		
	auto loginitem=MenuItemImage::create("login.png","login_press.png",this,menu_selector(Login::menuloginCallback));
	
	
	loginitem->setScaleX(this->getContentSize().width/1080);
	loginitem->setScaleY(this->getContentSize().height/1920);
	float width=(this->getContentSize().width/1080)*loginitem->getContentSize().width;
	float height=(this->getContentSize().height/1920)*loginitem->getContentSize().height;
	
	loginitem->setPosition(ccp(visiable.width/2+width/2,height));

	auto joinitem=MenuItemImage::create("join.png","join_press.png",this,menu_selector(Login::menujoinCallback));
	
	joinitem->setScaleX(this->getContentSize().width/1080);
	joinitem->setScaleY(this->getContentSize().height/1920);
	width=(this->getContentSize().width/1080)*joinitem->getContentSize().width;
	height=(this->getContentSize().height/1920)*joinitem->getContentSize().height;

	joinitem->setPosition(ccp(visiable.width/2-width/2,height));
	
	auto pMenu=Menu::create(loginitem,joinitem,NULL);
	pMenu->setPosition(ccp(0,0));
	
	
	loginlayer->addChild(pMenu);

	

}


void Login::menujoinCallback(cocos2d::Ref* pSender){

	MovingEdit();
	
	MovingJoin();

}

void Login::MakeJoinEdit()
{
		Size editsize;
		editsize.setSize(visiable.width/2,visiable.height/15);
	join_email=EditBox::create(editsize,Scale9Sprite::create("button.png"));
	join_email->setScaleX(this->getContentSize().width/1080);
	join_email->setScaleY(this->getContentSize().height/1920);
	float height=visiable.height-(visiable.height/10*2);
	join_email->setPosition(ccp(visiable.width/2,height));
	join_email->setFontColor(ccc3(255,255,255));
	join_email->setFontSize(10);
	join_email->setPlaceholderFontSize(10);
	join_email->setPlaceHolder("E-mail");
	join_email->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	join_email->setInputMode(cocos2d::extension::EditBox::InputMode::EMAIL_ADDRESS);
	join_email->setMaxLength(30);
	
	joinlayer->addChild(join_email,1);


	editsize.setSize(visiable.width/2,visiable.height/15);
	join_password=EditBox::create(editsize,Scale9Sprite::create("button.png"));
	join_password->setScaleX(this->getContentSize().width/1080);
	join_password->setScaleY(this->getContentSize().height/1920);
	height-=visiable.height/10*2;
	join_password->setPosition(ccp(visiable.width/2,height));
	join_password->setFontColor(ccc3(255,255,255));
	join_password->setFontSize(10);
	join_password->setPlaceholderFontSize(10);
	join_password->setPlaceHolder("Password");
	join_password->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	join_password->setInputMode(cocos2d::extension::EditBox::InputMode::SINGLE_LINE);
	join_password->setInputFlag(cocos2d::extension::EditBox::InputFlag::PASSWORD);
	join_password->setMaxLength(20);
	
	joinlayer->addChild(join_password,1);


	editsize.setSize(visiable.width/2,visiable.height/15);
	join_account=EditBox::create(editsize,Scale9Sprite::create("button.png"));
	join_account->setScaleX(this->getContentSize().width/1080);
	join_account->setScaleY(this->getContentSize().height/1920);
	height-=visiable.height/10*2;
	join_account->setPosition(ccp(visiable.width/2,height));
	join_account->setFontColor(ccc3(255,255,255));
	join_account->setFontSize(10);
	join_account->setPlaceholderFontSize(10);
	join_account->setPlaceHolder("Account");
	join_account->setReturnType(cocos2d::extension::EditBox::KeyboardReturnType::DONE);
	join_account->setInputMode(cocos2d::extension::EditBox::InputMode::EMAIL_ADDRESS);
	join_account->setMaxLength(50);
	
	joinlayer->addChild(join_account,1);


	auto backitem=MenuItemImage::create("login.png","login_press.png",this,menu_selector(Login::menuBackCallback));
	
	
	backitem->setScaleX(this->getContentSize().width/1080);
	backitem->setScaleY(this->getContentSize().height/1920);

	float width=(this->getContentSize().width/1080)*backitem->getContentSize().width;
	float heightt=(this->getContentSize().height/1920)*backitem->getContentSize().height;

	backitem->setPosition(ccp(visiable.width/2+width/2,heightt));

	auto registitem=MenuItemImage::create("join.png","join_press.png",this,menu_selector(Login::menuRegistCallback));
	
	registitem->setScaleX(this->getContentSize().width/1080);
	registitem->setScaleY(this->getContentSize().height/1920);

	width=(this->getContentSize().width/1080)*registitem->getContentSize().width;
	heightt=(this->getContentSize().height/1920)*registitem->getContentSize().height;

	registitem->setPosition(ccp(visiable.width/2-width/2,heightt));
	
	auto pMenu=Menu::create(backitem,registitem,NULL);
	pMenu->setPosition(ccp(0,0));
	
	
	joinlayer->addChild(pMenu);

}

void Login::menuRegistCallback(cocos2d::Ref* pSender)
{
	string email=join_email->getText();
	string password=join_password->getText();
	string account=join_account->getText();
	if(email.compare("")==0 || password.compare("")==0)
		MessageBox("No Blank!","Error!!");
	else
		httpjoin();
	
}

void Login::menuBackCallback(cocos2d::Ref* pSender)
{

	// enter loginlayer
	MovingBackJoin();
	MovingBackEdit();
}

void Login::httpjoin()
{
	HttpRequest* request=new HttpRequest();
	String srctail=Bus::getInstance()->src+"join_process.php";
	request->setUrl(srctail.getCString());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this,httpresponse_selector(Login::httpjoinCallback));

	//write post Data

	string email=join_email->getText();
	string password=join_password->getText();
	string account=join_account->getText();
	
	string data="email="+email+"&password="+password+"&account="+account;

	request->setRequestData(data.c_str(),data.length());
	request->setTag("POST Join");

	HttpClient::getInstance()->send(request);
	request->release();

	
}

void Login::httpjoinCallback(HttpClient* sender,HttpResponse* response)
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
		
		switch((*buffer)[86])
		{
		case '1':// incorrect email
			MessageBox("Success","Congraturation!");		
			// enter loginlayer
			MovingBackJoin();
			MovingBackEdit();
			break;
		case '0':
			MessageBox("Already Email!!!","Error!");
			break;
			
		case '3':
			MessageBox("Not E-Mail Form!","Error!");
			break;

		}



	}

}

void Login::httplogin()
{
	HttpRequest* request=new HttpRequest();
	String srctail=Bus::getInstance()->src+"login_process.php";
	request->setUrl(srctail.getCString());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this,httpresponse_selector(Login::httploginCallback));

	//write post Data

	string email=medit->getText();
	string password=pedit->getText();
	
	string data="email="+email+"&password="+password+"";

	
	Bus* b=Bus::getInstance();
	b->email=email;
	b->password=password;


	request->setRequestData(data.c_str(),data.length());
	request->setTag("POST Login");

	HttpClient::getInstance()->send(request);
	request->release();

	

}

void Login::httpgetaccount()
{
	HttpRequest* request=new HttpRequest();
	String srctail=Bus::getInstance()->src+"getaccount.php";
	request->setUrl(srctail.getCString());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this,httpresponse_selector(Login::httpgetaccountCallback));

	//write post Data
	Bus* b=Bus::getInstance();
	string email=b->email.c_str();
	
	string data="email="+email;



	request->setRequestData(data.c_str(),data.length());
	request->setTag("POST Account");

	HttpClient::getInstance()->send(request);
	request->release();


}


void Login::httpgetaccountCallback(HttpClient* sender,HttpResponse* response)
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

		
		Bus::getInstance()->account=number;
		//auto scene=CCTransitionProgressRadialCW::create(1,Game::createScene());
		auto scene=CCTransitionProgressRadialCW::create(1,Info::createScene());
		Director::getInstance()->replaceScene(scene);
		
	}


}

void Login::httploginCallback(HttpClient* sender,HttpResponse* response)// login http response;;;
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

		MessageBox(str.c_str(), "");

		switch(str[0])
		{
		case '1':// incorrect email
			MessageBox("No Email","Error");
			break;

		case '2':// incorrect passowrd
			MessageBox("No password","Error");
			break;

		case '3':// success login
			httpgetaccount();
			
			break;

		}



	}


	
	


	
}


void Login::menuloginCallback(cocos2d::Ref* pSender){  //login button click CallBack func

	
	httplogin();

	
	

}




void Login::titleLayer(Layer* dhis)
{

	//init var;
	visiable=Director::getInstance()->getVisibleSize();
	firsttouch=false;
	
	auto label=LabelTTF::create("TOWERBATTLE", "Arial",visiable.height/15);
	label->setColor(ccc3(0,0,0));
	label->setPosition(Vec2(visiable.width/2,visiable.height/2));
	dhis->addChild(label,0);



	auto please=LabelTTF::create(("Touch to continue..."),"Arial",50);
	please->setColor(ccc3(0,0,0));
	please->setPosition(Vec2(visiable.width/2,visiable.height/7));
	dhis->addChild(please,0);


	//Animation twinkle

	FadeOut *fo=FadeOut::create(0.5f);
	FadeIn  *fi=FadeIn::create(0.5f);
	Sequence *fseq=Sequence::create(fo,fi,NULL);
	please->runAction(RepeatForever::create(fseq));




}
void Login::MovingBackEdit(){

	auto mb=MoveBy::create(0.1f,ccp(-visiable.width,0));
	
	loginlayer->runAction(Repeat::create(mb,1));
}

void Login::MovingBackJoin()
{
	auto mb=MoveBy::create(0.1f,ccp(-visiable.width,0));
	
	joinlayer->runAction(Repeat::create(mb,1));

}

void Login::MovingJoin()
{
	auto mb=MoveBy::create(0.1f,ccp(visiable.width,0));
	
	joinlayer->runAction(Repeat::create(mb,1));

}

void Login::MovingEdit()
{

	auto mb=MoveBy::create(0.1f,ccp(visiable.width,0));
	
	loginlayer->runAction(Repeat::create(mb,1));
	
	
}
void Login::MakeLoginLayer(){

	loginlayer=LayerColor::create(Color4B(50,0,255,40));
	loginlayer->setContentSize(Size(visiable.width,visiable.height));
	loginlayer->setPosition(-visiable.width,0);
	this->addChild(loginlayer,3);

}

void Login::MakejoinLayer(){

	joinlayer=LayerColor::create(Color4B(255,253,0,40));
	joinlayer->setContentSize(Size(visiable.width,visiable.height));
	joinlayer->setPosition(-visiable.width,0);
	this->addChild(joinlayer,3);
}


bool Login::init()
{
	if(!LayerColor::initWithColor(ccc4(255,255,255,255)))
	{
		return false;
	}
	
	Bus::getInstance()->src="http://hume.co.kr/tower/";
	
	//topbattle & tocuh to continue;
	titleLayer(this); //


	//make login layer;
	MakeLoginLayer();
	

	//editbox Make LoginBox;
	MakeEdit(this);


	// Make JoinLayer;
	MakejoinLayer();


	//Make Edit In JoinLayer;
	MakeJoinEdit();








	//touch//
	auto listener=EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	
	listener->onTouchBegan=[=](Touch* touch , Event* event){
		if(!firsttouch){
			this->setOpacity(100);	
			MovingEdit();
			firsttouch=true;
		}


		return false;
	};
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	/////////
	return true;
}



