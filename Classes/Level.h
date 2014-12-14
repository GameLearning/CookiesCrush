/* 
 * File:   Level.h
 * Author: mohammedheader
 *
 * Created on December 14, 2014, 2:30 PM
 */

#ifndef LEVEL_H
#define	LEVEL_H
#include "Objects/Cookie.h"
#include "Objects/Tile.h"

class Level {
public:
    static const int NumColumns = 9;
    static const int NumRows = 9;
    
    static Level* createWithFile(std::string filename);
    std::set<Cookie*> shuffle();
    
    Cookie* cookieAt(int col, int row);
    Game::Tile* tileAt(int col, int row);
    
    Cookie *_cookies[NumColumns][NumRows];
    Game::Tile *_tiles[NumColumns][NumRows];
private:
    std::set<Cookie*> createInitialCookies();
    Cookie* createCookie(int col, int row, CookieType type);
};

#endif	/* LEVEL_H */

