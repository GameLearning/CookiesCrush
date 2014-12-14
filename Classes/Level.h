/* 
 * File:   Level.h
 * Author: mohammedheader
 *
 * Created on December 14, 2014, 2:30 PM
 */

#ifndef LEVEL_H
#define	LEVEL_H
#include "Objects/Cookie.h"

class Level {
public:
    std::set<Cookie*> shuffle();
    Cookie* cookieAt(int col, int row);
    static const int NumColumns = 9;
    static const int NumRows = 9;
    Cookie *_cookies[NumColumns][NumRows];
private:
    std::set<Cookie*> createInitialCookies();
    Cookie* createCookie(int col, int row, CookieType type);
};

#endif	/* LEVEL_H */

