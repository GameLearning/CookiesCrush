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
    
    std::string content;
    ssize_t size = 0;
    unsigned char* fileData = FileUtils::getInstance()->getFileData(filename.c_str(), "r", &size);
    content.append((char*)fileData);
    delete[] fileData;

    Json::Value jsonresult;
    Json::Reader reader;
    bool parsingSuccessful = reader.parse( content, jsonresult );
    
    const Json::Value tilesJson = jsonresult["tiles"];
    for ( int c = 0; c < tilesJson.size(); ++c ){
        for(int r = 0; r < tilesJson[c].size(); ++r){
            if (tilesJson[c][r].asInt() == 1){
                Game::Tile* title = new Game::Tile();
                level->_tiles[c][r] = title;
            }
        }
    }

    return level;
}


Cookie* Level::cookieAt(int col, int row) {
    return _cookies[col][row];
}

Game::Tile* Level::tileAt(int col, int row) {
    return _tiles[col][row];
}

std::set<Cookie*> Level::shuffle() {
    return this->createInitialCookies();
}

std::set<Cookie*> Level::createInitialCookies() {
    std::set<Cookie*> set;
    for(int c = 0; c < NumColumns; c++) {
        for(int r = 0; r < NumRows; r++) {
            if(_tiles[c][r] != nullptr){
                CookieType type;
                int c1,c2,r1,r2 = 0;
                if((c >= 2 &&  r >= 2)){
                    if( _cookies[c - 1][r] != nullptr ) c1 = _cookies[c - 1][r]->cookieType.type;
                    if( _cookies[c - 2][r] != nullptr ) c2 = _cookies[c - 2][r]->cookieType.type;
                    
                    if(_cookies[c][r - 1] != nullptr ) r1 = _cookies[c][r - 1]->cookieType.type;
                    if(_cookies[c][r - 2] != nullptr ) r2 = _cookies[c][r - 2]->cookieType.type;
                }
                do{
                    type = CookieType::random();
                }while
                (
                    (c > 2 &&  r > 2) && (
                        (c1 == type.type && c2 == type.type/*&& _cookies[c - 2][r]->cookieType.type == type.type*/) ||
                        (r1 == type.type && r2 == type.type /*&& _cookies[c][r - 2]->cookieType.type == type.type*/ )
                    )
                );
                Cookie* cookie = this->createCookie(c,r,type);
                set.insert(cookie);
            }
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
