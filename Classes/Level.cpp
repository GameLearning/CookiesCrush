/* 
 * File:   Level.cpp
 * Author: mohammedheader
 * 
 * Created on December 14, 2014, 2:30 PM
 */

#include "Level.h"

Cookie Level::cookieAt(int col, int row) {
     return _cookies[col][row];
}

std::set Level::shuffle() {
    return this->createInitialCookies();
}

std::set Level::createInitialCookies() {
    std::set<Cookie> set;
    for(int c = 0; c < NumColumns; c++) {
        for(int r = 0; r < NumRows; r++) {
            CookieType type = CookieType::random();
            Cookie cookie = this->createCookie(c,r,type);
            set.insert(cookie);
        }
    }
    return set;
}

Cookie Level::createCookie(int col, int row, CookieType type){
    Cookie cookie = new Cookie(col,row,type);
    _cookies[col][row] = cookie;
    return cookie;
}
