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
    initTouchSystem();
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

bool HelloWorld::setGridPostion(Vec2 loc, int& column, int& row) {
//    CCASSERT(column != nullptr && row != nullptr, "Invalid parameters.");
    
    if (loc.x >= 0 && loc.x < Level::NumColumns*TileWidth &&
        loc.y >= 0 && loc.y < Level::NumRows*TileHeight)
    {
        column = loc.x / TileWidth;
        row = loc.y / TileHeight;
        return true;

      } else {
        column = -1;
        row = -1;
        return false;
      }
}

void HelloWorld::initTouchSystem() {
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    listener->onTouchEnded = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    listener->onTouchCancelled = CC_CALLBACK_2(HelloWorld::onTouchEnded, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool HelloWorld::onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event) {
    Vec2 position = cookiesLayer->convertToNodeSpace(touch->getLocation());
    int col,row;
    if (setGridPostion(position,col,row)){
        if ( level->cookieAt(col,row) != nullptr){
            fromColumn = col;
            fromRow = row;
        }
    }
    return true;
}

void HelloWorld::onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event) {
    if (fromColumn == -1 || fromRow == -1 ) return;
    Vec2 newPosition = cookiesLayer->convertToNodeSpace(touch->getLocation());
    int column, row;
    if (setGridPostion(newPosition,column, row)){
        int horzDelta = 0, vertDelta = 0;
        if (column < fromColumn) {          // swipe left
          horzDelta = -1;
        } else if (column > fromColumn) {   // swipe right
          horzDelta = 1;
        } else if (row < fromRow) {         // swipe down
          vertDelta = -1;
        } else if (row > fromRow) {         // swipe up
          vertDelta = 1;
        }
        
        if (horzDelta != 0 || vertDelta != 0) {
            trySwap(horzDelta, vertDelta);

            fromColumn = -1;
            fromRow = -1;
        }
    }
}

void HelloWorld::onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event) {
    fromColumn = -1;
    fromRow = -1;
}

void HelloWorld::trySwap(int horzDelta, int vertDelta) {
    
    int toColumn = fromColumn + horzDelta;
    int toRow = fromRow + vertDelta;
    
    if ( toRow < 0 || toRow >= Level::NumRows) return;
    if ( toColumn < 0 || toColumn >= Level::NumColumns) return;
    
    
    Cookie* toCookie = level->cookieAt(toColumn, toRow);
    if ( toCookie == nullptr) return;
    
    
    Cookie* fromCookie = level->cookieAt(fromColumn, fromRow);
     
    CCLog("Swape %s with %s",fromCookie->toString() , toCookie->toString());
}
