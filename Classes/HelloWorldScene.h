#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Objects/Cookie.h"
#include "Level.h"
class HelloWorld : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);
    

    virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchMoved(cocos2d::Touch* touch, cocos2d::Event* unused_event);
    virtual void onTouchEnded(cocos2d::Touch* touch, cocos2d::Event* unused_event);
private:
    void initTouchSystem();
    void addSpritesForCookies(std::set<Cookie*> cookies);
    cocos2d::Vec2 pointFor(int col, int row);
    void addTiles();
    bool setGridPostion(cocos2d::Vec2 loc,int& column, int& row);
    void trySwap(int horzDelta, int vertDelta);
    
    cocos2d::SpriteBatchNode* cookiesLayer;
    cocos2d::SpriteBatchNode* tilesLayer;
    Level* level;
    int fromColumn, fromRow;
};

#endif // __HELLOWORLD_SCENE_H__
