/* 
 * File:   Level.cpp
 * Author: mohammedheader
 * 
 * Created on December 14, 2014, 2:30 PM
 */

#include "Level.h"
#include "libs/json/json/json.h"
USING_NS_CC;
Level* Level::createWithFile(std::string filename) {
    Level* level = new Level();
    
//    unsigned ssize_t filesize = 0;
    std::string content;
    std::string fullPath = "levels/Level_3.json";

    unsigned char* fileData = FileUtils::getInstance()->getFileData(fullPath.c_str(), "r", 0);
    content.append((char*)fileData);
    delete[] fileData;

    Json::Value jsonresult;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( content, jsonresult );

    return level;
}


Cookie* Level::cookieAt(int col, int row) {
     return _cookies[col][row];
}

std::set<Cookie*> Level::shuffle() {
    return this->createInitialCookies();
}

std::set<Cookie*> Level::createInitialCookies() {
    std::set<Cookie*> set;
    for(int c = 0; c < NumColumns; c++) {
        for(int r = 0; r < NumRows; r++) {
            CookieType type = CookieType::random();
            Cookie* cookie = this->createCookie(c,r,type);
            set.insert(cookie);
        }
    }
    return set;
}

Cookie* Level::createCookie(int col, int row, CookieType type){
    Cookie* cookie = new Cookie();
    cookie->init(col,row,type);
    _cookies[col][row] = cookie;
    return cookie;
}
