#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"

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

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    TMXTiledMap* tiledMap = TMXTiledMap::create("tiledMap/test.tmx");
    tiledMap->setAnchorPoint(Vec2(0.5, 0.5));
    tiledMap->setPosition(Vec2(getContentSize().width/2, getContentSize().height/2));
    TMXObjectGroup* objectGroup = tiledMap->getObjectGroup("hero");
    ValueMap objectValueMap = objectGroup->getObject("pa");
    Sprite* sprite = Sprite::create("CloseSelected.png");
    sprite->setPosition(Vec2(objectValueMap.at("x").asFloat(), objectValueMap.at("y").asFloat()));
    addChild(tiledMap);
    tiledMap->addChild(sprite);
    
    
    auto tiledMapListener = EventListenerTouchOneByOne::create();
    tiledMapListener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    tiledMapListener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    tiledMap->getEventDispatcher()->addEventListenerWithSceneGraphPriority(tiledMapListener, tiledMap);
    return true;
}
bool HelloWorld::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
    TMXTiledMap* tiledMap = static_cast<TMXTiledMap*>(event->getCurrentTarget());
    auto location = touch->getLocation();
    auto size = tiledMap->getContentSize();
    auto rect = Rect(0, 0, size.width, size.height);
    auto locationInNode = tiledMap->convertToNodeSpace(location);
    if(rect.containsPoint(locationInNode))
    {
        return true;
    }
    return false;
}

void HelloWorld::onTouchMoved(Touch* touch, Event* event)
{
    TMXTiledMap* tiledMap = static_cast<TMXTiledMap*>(event->getCurrentTarget());
    auto diff = touch->getDelta();
    auto currentPos = tiledMap->getPosition();
    auto pos = currentPos+diff;
    if((currentPos+diff).x > tiledMap->getContentSize().width/2) {
        pos = Vec2(tiledMap->getContentSize().width/2, currentPos.y + diff.y);
    }
    tiledMap->setPosition(pos);
}


void HelloWorld::menuCloseCallback(Ref* pSender)
{
    //Close the cocos2d-x game scene and quit the application
    Director::getInstance()->end();

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
    
    /*To navigate back to native iOS screen(if present) without quitting the application  ,do not use Director::getInstance()->end() and exit(0) as given above,instead trigger a custom event created in RootViewController.mm as below*/
    
    //EventCustom customEndEvent("game_scene_close_event");
    //_eventDispatcher->dispatchEvent(&customEndEvent);
    
    
}
