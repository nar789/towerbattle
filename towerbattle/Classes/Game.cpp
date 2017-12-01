#include "Game.h"
#include "Login.h"

using namespace std;
USING_NS_CC;


Scene* Game::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
	auto layer = Game::create();
	layer->setContentSize(Size(Director::getInstance()->getWinSize().width,Director::getInstance()->getWinSize().height*10));
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}


void Game::outline(){

	b2Vec2 gravity;
		gravity.Set(0.0f,-30.0f);
		_world=new b2World(gravity);
		_world->SetAllowSleeping(true);
		_world->SetContinuousPhysics(true);

		b2BodyDef groundBodyDef;
		groundBodyDef.position.Set(0,0);

		b2Body *groundBody = _world->CreateBody(&groundBodyDef);

		b2EdgeShape groundEdge;
		b2FixtureDef boxShapeDef;
		boxShapeDef.shape=&groundEdge;
		//bottom
		groundEdge.Set(b2Vec2(0,0),b2Vec2(winSize.width/PTM_RATIO,0));
		groundBody->CreateFixture(&boxShapeDef);
		//left
		//groundEdge.Set(b2Vec2(0,0),b2Vec2(0,winSize.height/PTM_RATIO));
		//groundBody->CreateFixture(&boxShapeDef);
		//top
		//groundEdge.Set(b2Vec2(0,winSize.height/PTM_RATIO),b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO));
		//groundBody->CreateFixture(&boxShapeDef);
		//right
		//groundEdge.Set(b2Vec2(winSize.width/PTM_RATIO,0),b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO*2));
		//groundBody->CreateFixture(&boxShapeDef);

}

// on "init" you need to initialize your instance
bool Game::init()
{
    //////////////////////////////
    // 1. super init first
	if ( !LayerColor::initWithColor(Color4B(255,255,255,255)))
    {
        return false;
    }
	

	node=ParallaxNode::create();
	this->addChild(node,0);
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(Game::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

	

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
	
	
	Size visible=Director::getInstance()->getWinSize();
	cp_height=visible.height;
	stage_number=1;
	makelabel(stage_number);
	makebglayer(stage_number);
	drawpoint();
	stopmenuvisible=false;
	end=false;


	homebutton=MenuItemImage::create("home.png","home_press.png",this,menu_selector(Game::menuHomebuttonCallback));
	homebutton->setScaleX(this->getContentSize().width/1080);
	homebutton->setScaleY(this->getContentSize().height/1920);
	homebutton->setPosition(homebutton->getContentSize().width*(this->getContentSize().width/1080),start_pointlabel_height);
	homebutton->setOpacity(180);

    // create menu, it's an autorelease object
    auto menu = Menu::create(homebutton, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 5);





	topHeight=0;
	prevtopHeight=0;
	
	srand(time(NULL));
	sort=rand()%2;
	
	stop=true;
	uptiming=false;

	poly_info[0].setPoint(216,216);
	poly_info[1].setPoint(72,432);

    // add "Game" splash screen"
    auto sprite = Sprite::create("bg.png");

    // position the sprite on the center of the screen
	sprite->setAnchorPoint(Vec2(0.5,0));
    sprite->setPosition(Vec2(0,0));
	sprite->setScale(3,3);
	bg=sprite;
    // add the sprite as a child to this layer
    //this->addChild(bg, 0);
	//node->addChild(bg,0,ccp(0,2.0),ccp(0,0));
	

	

	line=Sprite::create("line.png");
	line->setPosition(ccp(winSize.width/2,0));
	this->addChild(line,2);
	

	movePolygon[0]=Sprite::create("box0.png");
	movePolygon[1]=Sprite::create("box1.png");
	movePolygon[0]->setVisible(false);
	movePolygon[1]->setVisible(false);

    

	winSize=Director::sharedDirector()->getWinSize();
	texture[0]=Director::getInstance()->getTextureCache()->addImage("box0.png");
	texture[1]=Director::getInstance()->getTextureCache()->addImage("box1.png");
	
	m_diff=winSize.height/3;
	polygon_height=winSize.height/3*2;
	outline();


	for(int i=1;i<=10;i++){
		
		String str;
		str.appendWithFormat("%d",i);
		str.append(".png");
		
		
		number[i]=Sprite::create(str.getCString());
		number[i]->setVisible(false);
		number[i]->setPosition(ccp(winSize.width/2,polygon_height+400));
		this->addChild(number[i],3);
		
	}
	counter=10;

	
	this->schedule(schedule_selector(Game::tick));
	this->schedule(schedule_selector(Game::isLine),1.0f);
	this->schedule(schedule_selector(Game::upper));
	this->schedule(schedule_selector(Game::autoTouch),10.0f);
	
	
	
	

	
	
	this->addChild(movePolygon[0],2);
	this->addChild(movePolygon[1],2);
	movingPolygon();
	


	auto listener=EventListenerTouchOneByOne::create();
	this->setSwallowsTouches(true);
	listener->setSwallowTouches(true);

	listener->onTouchBegan=[=](Touch* touch , Event* event){
		//Scene* pScene=Login::createScene();
		//Director::getInstance()->replaceScene(pScene);
			if(end)
			{
				auto scene=CCTransitionFade::create(1.0f,Info::createScene());
				Director::getInstance()->replaceScene(scene);
			}
			else if(stop)
			{
				if(stopmenuvisible)
				{
					stopmenu->setVisible(false);
					stopmenuvisible=false;
				}
				movePolygon[sort]->stopAllActions();
				//Point p=this->convertToNodeSpace(touch->getLocation());
				Point p=movePolygon[sort]->getPosition();
				movePolygon[sort]->setVisible(false);
				addSprite(p);
				
				stop=false;
				uptiming=true;
				this->unschedule(schedule_selector(Game::autoTouch));
				this->unschedule(schedule_selector(Game::count));
				for(int i=1;i<=10;i++)
					number[i]->setVisible(false);
				counter=10;
				
			}
			/*
			int hh=this->getContentSize().height;
			int mm=prevtopHeight;
			String ss;
			ss.initWithFormat("%d %d",hh,mm);
			MessageBox(ss.getCString(),ss.getCString());*/
			return false;
		};

	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);
	

			
			

    return true;
}

void Game::menuHomebuttonCallback(cocos2d::Ref* pSender)
{
	auto scene=CCTransitionFade::create(1.0f,Info::createScene());
	Director::getInstance()->replaceScene(scene);

}

void Game::drawpoint()
{
	httpgetpoint();
	point=0;
	pointlabel=LabelTTF::create("PIONT Initialize..","Arial",40);
	start_pointlabel_height=this->getContentSize().height-pointlabel->getContentSize().height;
	start_pointlabel_width=this->getContentSize().width-(pointlabel->getContentSize().width/2);
	pointlabel->setPosition(this->getContentSize().width-(pointlabel->getContentSize().width/2),start_pointlabel_height);
	this->addChild(pointlabel,4);
}


void Game::httpgetpoint()
{

	HttpRequest* request=new HttpRequest();
	String srctail=Bus::getInstance()->src+"getpoint.php";
	request->setUrl(srctail.getCString());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this,httpresponse_selector(Game::httpgetpointCallback));

	//write post Data
	Bus* b=Bus::getInstance();
	string email=b->email.c_str();
	
	string data="email="+email;



	request->setRequestData(data.c_str(),data.length());
	request->setTag("POST Point");

	HttpClient::getInstance()->send(request);
	request->release();


}



void Game::httpgetpointCallback(HttpClient* sender,HttpResponse* response)
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
		updatepoint(b->point);
		
	}
}



void Game::makebglayer(int number){
	switch(number)
	{ 
		case 1://stage1
			bglayer=LayerGradient::create(Color4B(0,0,0,255),Color4B(23,73,84,255));
			bglayer->setAnchorPoint(Vec2(0,0));
			bglayer->setContentSize(Size(Director::getInstance()->getVisibleSize().width,this->getContentSize().height));
			bglayer->setPosition(Vec2(0,this->getContentSize().height));
			this->addChild(bglayer,0);
			bglayer=LayerGradient::create(Color4B(23,73,84,255),Color4B(0,210,255,30));
			bglayer->setAnchorPoint(Vec2(0,0));
			bglayer->setContentSize(Size(Director::getInstance()->getVisibleSize().width,this->getContentSize().height));
			bglayer->setPosition(Vec2(0,0));
			this->addChild(bglayer,0);
			break;
		case 2://stage2
			bglayer=LayerGradient::create(Color4B(255,192,0,255),Color4B(0,0,0,255));
			bglayer->setPosition(Vec2(0,cp_height*number));
			this->addChild(bglayer,0);
			
			break;
		case 3://stage3
			bglayer=LayerGradient::create(Color4B(149,0,167,255),Color4B(255,192,0,255));
			bglayer->setPosition(Vec2(0,cp_height*number));
			this->addChild(bglayer,0);
			
			break;
		case 4://stage4
			bglayer=LayerGradient::create(Color4B(25,26,27,255),Color4B(149,0,167,255));
			bglayer->setPosition(Vec2(0,cp_height*number));
			this->addChild(bglayer,0);
			
			break;
	}



}

void Game::makelabel(int number){
	String txt;
	txt.initWithFormat("STAGE%d CLEAR POINT",number);
	Size visible=Director::getInstance()->getVisibleSize();
	label = LabelTTF::create(txt.getCString(), "Arial", 40);
	label->setColor(Color3B(255,255,255));
    
    label->setPosition(Vec2(visible.width/2,cp_height*number));
    this->addChild(label, 1);



}

void Game::count(float dt){
	number[counter]->setPosition(ccp(winSize.width/2,polygon_height+400));
	for(int i=1;i<=10;i++)
		number[i]->setVisible(false);
	number[counter]->setVisible(true);
	if(counter!=1)
		counter--;
	else
	{
		number[1]->setVisible(false);
		counter=10;

	}
}


void Game::autoTouch(float dt)
{
	if(stop)
	{
		if(stopmenuvisible)
		{
					stopmenu->setVisible(false);
					stopmenuvisible=false;
		}
		movePolygon[sort]->stopAllActions();
		//Point p=this->convertToNodeSpace(touch->getLocation());
		Point p=movePolygon[sort]->getPosition();
		movePolygon[sort]->setVisible(false);
		addSprite(p);
				
		stop=false;
		uptiming=true;
		
	}
	this->unschedule(schedule_selector(Game::autoTouch));
	this->unschedule(schedule_selector(Game::count));
	for(int i=1;i<=10;i++)
		number[i]->setVisible(false);
	counter=10;

}

void Game::movingPolygon(){

	
	this->schedule(schedule_selector(Game::count),1.0f);
	sort=rand()%2;
	//sort=0;
	movePolygon[sort]->setVisible(true);
	movePolygon[sort]->setPosition(ccp(poly_info[sort].x/2,polygon_height));
	
	MoveBy *right=MoveBy::create(2,ccp(winSize.width-poly_info[sort].x,0));
	MoveBy *left=MoveBy::create(2,ccp(-(winSize.width-poly_info[sort].x),0));
	Sequence *seq=Sequence::create(right,left,NULL);
	movePolygon[sort]->runAction(RepeatForever::create(seq));

	
	

}


void Game::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Game::pageup(){


	float diff;
	
	
	if((line->getPositionY()) >=m_diff)
	{
		
		diff=(line->getPositionY()) -m_diff;
		//char ss[50];
		//sprintf(ss,"line:%f md:%f d:%f",line->getPositionY(),m_diff,diff);

		//MessageBox(ss,"A");
		

	
	
		MoveBy* act=MoveBy::create(1,Point(0,-diff));
		EaseOut* act2=EaseOut::create(act,2.5f);
		
		
		this->runAction(Repeat::create(act2,1));
		
		auto mm=MoveBy::create(0.2f,Point(0,diff));
		auto ee=EaseOut::create(mm,2.5f);
		pointlabel->runAction(Repeat::create(ee,1));
		auto hmm=MoveBy::create(0.2f,Point(0,diff));
		auto hee=EaseOut::create(hmm,2.5f);
		homebutton->runAction(Repeat::create(hee,1));
		
		m_diff+=diff;
		polygon_height+=diff;
	}
	else
	{

		if(m_diff>(winSize.height/3)){

			MoveBy* act=MoveBy::create(1,Point(0,m_diff-(winSize.height/3)));
			EaseOut* act2=EaseOut::create(act,2.5f);
			this->runAction(Repeat::create(act2,1));
		}
		
		m_diff=winSize.height/3;
		polygon_height=winSize.height/3*2;

		auto mm=MoveTo::create(0.2,Point(start_pointlabel_width,start_pointlabel_height));
		auto ee=EaseOut::create(mm,2.5f);
		pointlabel->runAction(Repeat::create(ee,1));

		auto hmm=MoveTo::create(0.2,Point(homebutton->getContentSize().width*(this->getContentSize().width/1080),start_pointlabel_height));
		auto hee=EaseOut::create(hmm,2.5f);
		homebutton->runAction(Repeat::create(hee,1));

		
	}



			


}

void Game::upper(float dt){

	if(uptiming&&stop)
	{
		pageup();
		uptiming=false;
		
		movingPolygon();
		this->schedule(schedule_selector(Game::autoTouch),10.0f);
	}


	

}


void Game::isLine(float dt){
	
	
		
	if(topHeight==prevtopHeight)
	{
		line->setPosition(ccp(winSize.width/2,topHeight));
		stop=true;
		if(prevtopHeight>=this->getContentSize().height/10*stage_number)
		{
			drawcoin();
			updatepoint(500);
			drawstop();
			//clear Line add point 500point;
			stage_number++;
			makelabel(stage_number);
			makebglayer(stage_number);
		}
		
	}
	prevtopHeight=topHeight;

}
void Game::menustopCallback(cocos2d::Ref* pSender)
{
	drawpointlayer();
		//STop yes!!
}

void Game::drawpointlayer(){
	pointlayer=LayerColor::create(Color4B(0,0,0,200));
	pointlayer->setContentSize(this->getContentSize());
	
	pointlayer->setPosition(this->getPosition());
	this->addChild(pointlayer,5);
	drawcoinupdown();
	drawending();
	httpsavepoint();
	
}
void Game::httpsavepoint()
{
	HttpRequest* request=new HttpRequest();
	String srctail=Bus::getInstance()->src+"savepoint.php";
	request->setUrl(srctail.getCString());
	request->setRequestType(HttpRequest::Type::POST);
	request->setResponseCallback(this,httpresponse_selector(Game::httpsavepointCallback));

	//write post Data
	Bus* b=Bus::getInstance();
	string email=b->email.c_str();
	String txt;
	txt.initWithFormat("%d",point);
	
	string data="email="+email+"&point="+txt.getCString();



	request->setRequestData(data.c_str(),data.length());
	request->setTag("POST SavePoint");

	HttpClient::getInstance()->send(request);
	request->release();

}

void Game::httpsavepointCallback(HttpClient* sender,HttpResponse* response)
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
				
		}



		end=true;
		
	}


}

void Game::drawending(){
	auto ttxt=LabelTTF::create("Congratulation!","Arial",150);
	ttxt->setPosition(ccp(this->getContentSize().width/2,stopmenu->getPositionY()));
	this->addChild(ttxt,6);
	String abc;
	abc.initWithFormat("%dP",point);
	auto ptxt=LabelTTF::create(abc.getCString(),"Arial",200);
	ptxt->setRotation(15.0f);
	ptxt->setPosition(ccp(this->getContentSize().width/2,prevtopHeight));
	this->addChild(ptxt,6);
	
}
void Game::drawcoinupdown()
{
	/*
	for(int i=0;i<20;i++)
	{
		auto coin=Sprite::create("coin.png");
		int wid=this->getContentSize().width;
		int xx=rand()%wid;
		coin->setPosition(ccp(xx,0));
		pointlayer->addChild(coin,4);
		auto m=MoveBy::create(0.2f,ccp(0,200));
		auto f=FadeOut::create(0.5f);
		auto s=Sequence::create(m,f,NULL);
		coin->runAction(Repeat::create(s,1));
	}
	*/
	
	for(int i=0;i<30;i++)
	{
		auto coin=Sprite::create("coin.png");
		int wid=this->getContentSize().width;
		int xx=rand()%wid;
		int ff=rand()%5;
		
		coin->setPosition(xx,stopmenu->getPositionY()+300);
		this->addChild(coin,5);
		auto m=MoveBy::create(ff,ccp(0,-(prevtopHeight+300)));
		auto f=FadeOut::create(0.5f);
		auto m2=MoveBy::create(0.1f,ccp(0,+(prevtopHeight+300)));
		auto f2=FadeIn::create(0.5f);
		auto s=Sequence::create(m,f,m2,f2,NULL);
		coin->runAction(RepeatForever::create(s));
	}
	

}
void Game::drawstop()
{
	
	stopmenu=MenuItemImage::create("stop.png","stop_press.png",this,menu_selector(Game::menustopCallback));
	stopmenu->setPosition(stopmenu->getContentSize().width/2,pointlabel->getPositionY());
	auto menu=Menu::create(stopmenu,NULL);
	menu->setPosition(0,0);
	this->addChild(menu,4);
	stopmenuvisible=true;

	auto r1=RotateBy::create(0.05f,15.0f);
	auto r2=RotateBy::create(0.1f,-30.0f);
	auto d=DelayTime::create(0.2f);
	auto ss=Sequence::create(r1,r2,r1,d,NULL);
	stopmenu->runAction(RepeatForever::create(ss));

}

void Game::updatepoint(int add)
{
	pointlabel->setVisible(false);
	float y;
	
	y=pointlabel->getPositionY();
	String tt;
	point+=add;
	tt.initWithFormat("POINT:%d",point);
	pointlabel=LabelTTF::create(tt.getCString(),"Arial",40);
	pointlabel->setPosition(this->getContentSize().width-(pointlabel->getContentSize().width/2),y);
	this->addChild(pointlabel,4);

}

void Game::drawcoin()
{
	
	for(int i=0;i<20;i++)
	{
		auto coin=Sprite::create("coin.png");
		int wid=this->getContentSize().width;
		int xx=rand()%wid;
		coin->setPosition(ccp(xx,prevtopHeight));
		this->addChild(coin,4);
		auto m=MoveBy::create(0.2f,ccp(0,100));
		auto f=FadeOut::create(0.5f);
		auto s=Sequence::create(m,f,NULL);
		coin->runAction(Repeat::create(s,1));
	}
	

	

}


void Game::tick(float dt){

	int velocityInterations=8;
	int positionInterations=3;
	int current=0;



	
	_world->Step(dt,velocityInterations,positionInterations);

	

	
	for(b2Body *b=_world->GetBodyList();b;b=b->GetNext()){
		if(b->GetUserData()!=NULL)
		{
			
			Sprite *spriteD=(Sprite *)b->GetUserData();
			spriteD->setPosition(ccp(b->GetPosition().x*PTM_RATIO,b->GetPosition().y*PTM_RATIO));
			spriteD->setRotation(-1* CC_RADIANS_TO_DEGREES(b->GetAngle()));

			if(current<(b->GetPosition().y*PTM_RATIO+poly_info[sort].y/2)){
				current=b->GetPosition().y*PTM_RATIO+poly_info[sort].y/2;
			}
		}//if
	}//for

	topHeight=current;

}


void Game::addSprite(Point location){

	if(texture)
	{
		Sprite* pSprite=Sprite::createWithTexture(texture[sort],CCRectMake(0,0,poly_info[sort].x,poly_info[sort].y));
		pSprite->setPosition(ccp(location.x,location.y));
		
		this->addChild(pSprite,1);
		

		//m_box.push_back(pSprite);


		b2BodyDef bodyDef;
		bodyDef.type=b2_dynamicBody;
		bodyDef.position.Set(location.x/PTM_RATIO,location.y/PTM_RATIO);
		bodyDef.userData=pSprite;
		
		b2Body* body= _world->CreateBody(&bodyDef);

		b2PolygonShape rect;
		
		rect.SetAsBox(poly_info[sort].x/PTM_RATIO/2,poly_info[sort].y/PTM_RATIO/2);
		

		b2FixtureDef fixtureDef;
		fixtureDef.shape=&rect;
		fixtureDef.density=0.5f;
		//fixtureDef.density=0.0f;
		fixtureDef.friction=0.2f;
		//fixtureDef.friction=0.1f;
		fixtureDef.restitution=0.4f;
		//fixtureDef.restitution=0.1f;
		
		
		body->CreateFixture(&fixtureDef);
	}

}


