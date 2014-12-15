/* 
 * File:   Cookie.cpp
 * Author: mohammedheader
 * 
 * Created on December 14, 2014, 1:57 PM
 */

#include "Cookie.h"
USING_NS_CC;
void Cookie::init(int column, int row, CookieType cookieType) {
    this->column = column;
    this->row = row;
    this->cookieType = cookieType;
}

Cookie::Cookie() {

}

const char* Cookie::toString() {
    return CCString::createWithFormat("type:%d square:(%d,%d)",cookieType.type,column,row)->_string.c_str();
}
