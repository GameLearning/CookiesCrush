#include "HelloWorldScene.h"
#include "Objects/CookieType.h"
#include "Level.h"

USING_NS_CC;

static const int TileWidth = 64;
static const int TileHeight = 72;

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
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    
    Sprite* bg = Sprite::create("Background.png");
    bg->setPosition(visibleSize.width/2,visibleSize.height/2);
    this->addChild(bg);

    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cookies_sprites.plist");
    cookiesLayer = SpriteBatchNode::create("cookies_sprites.png",100);
    cookiesLayer->setAnchorPoint(Vec2(0,0));
    
    this->addChild(cookiesLayer);
    
    Level* level = Level::createWithFile("levels/Level_3.json");
    std::set<Cookie*> cookies = level->shuffle();
    addSpritesForCookies(cookies);
    cookiesLayer->setPosition(visibleSize.width/2 - (TileWidth * Level::NumColumns) /2,visibleSize.height/2- (TileHeight * Level::NumRows) /2);
    return true;
}

void HelloWorld::addSpritesForCookies(std::set<Cookie*> cookies) {
    for (Cookie *cookie : cookies) {
        Sprite *sprite = Sprite::createWithSpriteFrameName(cookie->cookieType.getSpriteName());
        sprite->setPosition(pointFor(cookie->column, cookie->row));
        cookiesLayer->addChild(sprite);
        cookie->sprite = sprite;
    }
}

Vec2 HelloWorld::pointFor(int col, int row) {
    return Vec2(col*TileWidth + TileWidth/2, row*TileHeight + TileHeight/2);
}
