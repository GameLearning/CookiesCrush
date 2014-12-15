/* 
 * File:   Cookie.h
 * Author: mohammedheader
 *
 * Created on December 14, 2014, 1:57 PM
 */

#ifndef COOKIE_H
#define	COOKIE_H

#include "../cocos2d.h"
#include "CookieType.h"
class Cookie {
    
public:
    int column;
    int row;
    CookieType cookieType;
    cocos2d::Sprite* sprite;
    Cookie();
    const char* toString();
 
  void init(int column, int row, CookieType cookieType);
private:

};

#endif	/* COOKIE_H */

