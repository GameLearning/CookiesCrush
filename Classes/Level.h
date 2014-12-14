/* 
 * File:   Level.h
 * Author: mohammedheader
 *
 * Created on December 14, 2014, 2:30 PM
 */

#ifndef LEVEL_H
#define	LEVEL_H

class Level {
public:
    std::set shuffle();
    Cookie cookieAt(int col, int row);
    static const int NumColumns = 9;
    static const int NumRows = 9;
    Cookie *_cookies[NumColumns][NumRows];
private:
    std::set createInitialCookies();
    Cookie createCookie(int col, int row, CookieType type);
};

#endif	/* LEVEL_H */

