/* 
 * File:   CookieType.h
 * Author: mohammedheader
 *
 * Created on December 14, 2014, 2:08 PM
 */

#ifndef COOKIETYPE_H
#define	COOKIETYPE_H
#include "../cocos2d.h"

enum Type {
  Unknown = 0, Croissant, Cupcake, Danish, Donut, Macaroon, SugarCookie
};

class CookieType {
public:
    Type type;
    CookieType();
    CookieType(int type);
    static CookieType random();
    std::string getSpriteName();
    std::string getHighlightedSpriteName();
private:
    
};

#endif	/* COOKIETYPE_H */

