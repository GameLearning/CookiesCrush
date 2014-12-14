/* 
 * File:   Cookie.cpp
 * Author: mohammedheader
 * 
 * Created on December 14, 2014, 1:57 PM
 */

#include "Cookie.h"

void Cookie::init(int column, int row, CookieType cookieType) {
    this.column = column;
    this.row = row;
    this.cookieType = cookieType;
}
