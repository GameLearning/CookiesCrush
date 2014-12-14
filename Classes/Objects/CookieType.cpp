/* 
 * File:   CookieType.cpp
 * Author: mohammedheader
 * 
 * Created on December 14, 2014, 2:08 PM
 */

#include "CookieType.h"

CookieType::CookieType(int type) {
    this->type = Type(type);
}

CookieType CookieType::random() {
    int n = 1 + rand() % 6;
    return CookieType(n);
}

std::string CookieType::getSpriteName(){
    std::string sprites = [
    "Croissant",
    "Cupcake",
    "Danish",
    "Donut",
    "Macaroon",
    "SugarCookie"];
    
    return sprites[this->type - 1];
}
 
std::string CookieType::getHighlightedSpriteName() {
  return getSpriteName() + "-Highlighted";
}