#include "HelloWorldScene.h"
#include "Login.h"

USING_NS_CC;

Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();
	
    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

void HelloWorld::outline(){

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

		groundEdge.Set(b2Vec2(0,0),b2Vec2(winSize.width/PTM_RATIO,0));
		groundBody->CreateFixture(&boxShapeDef);

		//groundEdge.Set(b2Vec2(0,0),b2Vec2(0,winSize.height/PTM_RATIO));
		//groundBody->CreateFixture(&boxShapeDef);

		//groundEdge.Set(b2Vec2(0,winSize.height/PTM_RATIO),b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO));
		//groundBody->CreateFixture(&boxShapeDef);

		//groundEdge.Set(b2Vec2(winSize.width/PTM_RATIO,0),b2Vec2(winSize.width/PTM_RATIO,winSize.height/PTM_RATIO));
		//groundBody->CreateFixture(&boxShapeDef);

}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
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
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));
    
	closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    //this->addChild(menu, 1);

    /////////////////////////////
    // 3. add your codes below...

    // add a label shows "Hello World"
    // create and initialize a label
    
    auto label = LabelTTF::create("10M", "Arial", 40);
    
    // position the label on the center of the screen
    label->setPosition(Vec2(origin.x + visibleSize.width/2,
                            origin.y + visibleSize.height - label->getContentSize().height));

    // add the label as a child to this layer
    this->addChild(label, 1);



	topHeight=0;
	prevtopHeight=0;
	
	srand(time(NULL));
	sort=rand()%2;
	
	stop=true;
	uptiming=false;

	poly_info[0].setPoint(216,216);
	poly_info[1].setPoint(72,432);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("bg.png");

    // position the sprite on the center of the screen
	sprite->setAnchorPoint(Vec2(0.5,0));
    sprite->setPosition(Vec2(0,0));
	sprite->setScale(3,3);
	bg=sprite;
    // add the sprite as a child to this layer
    //this->addChild(bg, 0);
	node->addChild(bg,0,ccp(0,2.0),ccp(0,0));
	

	

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

	
	this->schedule(schedule_selector(HelloWorld::tick));
	this->schedule(schedule_selector(HelloWorld::isLine),1.0f);
	this->schedule(schedule_selector(HelloWorld::upper));
	this->schedule(schedule_selector(HelloWorld::autoTouch),10.0f);
	
	
	
	

	
	
	this->addChild(movePolygon[0],2);
	this->addChild(movePolygon[1],2);
	movingPolygon();
	


	auto listener=EventListenerTouchOneByOne::create();
	this->setSwallowsTouches(true);
	listener->setSwallowTouches(true);

	listener->onTouchBegan=[=](Touch* touch , Event* event){
		Scene* pScene=Login::createScene();
		Director::getInstance()->replaceScene(pScene);
			if(stop)
			{	
				movePolygon[sort]->stopAllActions();
				//Point p=this->convertToNodeSpace(touch->getLocation());
				Point p=movePolygon[sort]->getPosition();
				movePolygon[sort]->setVisible(false);
				addSprite(p);
				
				stop=false;
				uptiming=true;
				this->unschedule(schedule_selector(HelloWorld::autoTouch));
				this->unschedule(schedule_selector(HelloWorld::count));
				for(int i=1;i<=10;i++)
					number[i]->setVisible(false);
				counter=10;
				
			}
			
			return false;
		};

	
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener,this);

			
			

    return true;
}



void HelloWorld::count(float dt){
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


void HelloWorld::autoTouch(float dt)
{
	if(stop)
	{	
		movePolygon[sort]->stopAllActions();
		//Point p=this->convertToNodeSpace(touch->getLocation());
		Point p=movePolygon[sort]->getPosition();
		movePolygon[sort]->setVisible(false);
		addSprite(p);
				
		stop=false;
		uptiming=true;
		
	}
	this->unschedule(schedule_selector(HelloWorld::autoTouch));
	this->unschedule(schedule_selector(HelloWorld::count));
	for(int i=1;i<=10;i++)
		number[i]->setVisible(false);
	counter=10;

}

void HelloWorld::movingPolygon(){

	
	this->schedule(schedule_selector(HelloWorld::count),1.0f);
	sort=rand()%2;
	movePolygon[sort]->setVisible(true);
	movePolygon[sort]->setPosition(ccp(poly_info[sort].x/2,polygon_height));
	
	MoveBy *right=MoveBy::create(2,ccp(winSize.width-poly_info[sort].x,0));
	MoveBy *left=MoveBy::create(2,ccp(-(winSize.width-poly_info[sort].x),0));
	Sequence *seq=Sequence::create(right,left,NULL);
	movePolygon[sort]->runAction(RepeatForever::create(seq));

	
	

}


void HelloWorld::menuCloseCallback(Ref* pSender)
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

void HelloWorld::pageup(){



	

	float diff;
	
	
	if((line->getPositionY()) >=m_diff)
	{
		
		diff=(line->getPositionY()) -m_diff;
		//char ss[50];
		//sprintf(ss,"line:%f md:%f d:%f",line->getPositionY(),m_diff,diff);

		//MessageBox(ss,"A");
		

	
	
		MoveBy* act=MoveBy::create(1,Point(0,-diff));
		EaseOut* act2=EaseOut::create(act,2.5f);
		
		//bg->runAction(Repeat::create(act2,1));
		//node->runAction(Repeat::create(act2,1));
		//node->runAction(Repeat::create(act3,1));
		this->runAction(Repeat::create(act2,1));
		//node->setPositionY(0);
		
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
		
	}


	


}

void HelloWorld::upper(float dt){

	if(uptiming&&stop)
	{
		pageup();
		uptiming=false;
		
		movingPolygon();
		this->schedule(schedule_selector(HelloWorld::autoTouch),10.0f);
	}

	

	

}


void HelloWorld::isLine(float dt){
	
	
		
	if(topHeight==prevtopHeight)
	{
		line->setPosition(ccp(winSize.width/2,topHeight));
		stop=true;
		
		
	}
	prevtopHeight=topHeight;

}

void HelloWorld::tick(float dt){

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


void HelloWorld::addSprite(Point location){

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
		fixtureDef.density=1.0f;
		fixtureDef.friction=0.2f;
		fixtureDef.restitution=0.4f;
		
		
		body->CreateFixture(&fixtureDef);
	}

}


