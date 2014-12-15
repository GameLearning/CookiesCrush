#include "HelloWorldScene.h"
#include "Objects/CookieType.h"

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
    
    level = Level::createWithFile("levels/Level_3.json");
    std::set<Cookie*> cookies = level->shuffle();

    SpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("cookies_sprites.plist");
    
    cookiesLayer = SpriteBatchNode::create("cookies_sprites.png",100);
    cookiesLayer->setAnchorPoint(Vec2(0,0));
    cookiesLayer->setPosition(visibleSize.width/2 - (TileWidth * Level::NumColumns) /2,visibleSize.height/2- (TileHeight * Level::NumRows) /2);
    
    tilesLayer = SpriteBatchNode::create("cookies_sprites.png",100);
    tilesLayer->setAnchorPoint(Vec2(0,0));
    tilesLayer->setPosition(cookiesLayer->getPosition());
    
    this->addChild(tilesLayer);
    this->addChild(cookiesLayer);
    
    addTiles();
    addSpritesForCookies(cookies);
    return true;
}

void HelloWorld::addTiles() {
    for(int c = 0; c < Level::NumColumns; c++) {
        for(int r = 0; r < Level::NumRows; r++) {
            if(level->tileAt(c,r) != nullptr){
                Sprite *sprite = Sprite::createWithSpriteFrameName("Tile.png");
                sprite->setPosition(pointFor(c, r));
                tilesLayer->addChild(sprite);
            }
        }
    }
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
