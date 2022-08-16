#include "Possiblemove.hpp"

int is(coordinates a, bool clr)
{
    if (a.x > 7 || a.x < 0 || a.y > 7 || a.y < 0)
        return 2;
    if (board[a.x][a.y] != 0)
    {
        if (board[a.x][a.y]!=clr)
        {return 1;}
        return 3;
    }
    return 0;
}

bool east(coordinates check_pos)
{
    check_pos.x++;
    int st;
    while (!(st = is(check_pos, getcolor())))
    {
        check_pos.x++;
    }
    if (st == 2)
        return 0;
    if (st == 1&&(board[check_pos.x][check_pos.y]->getname()==queen_||board[check_pos.x][check_pos.y]->getname()==rook_))
    {
        return true;
    }
    return 0;
}
bool west(coordinates check_pos)
{
    check_pos.x--;
    int st;
    while (!(st = is(check_pos, getcolor())))
    {
        check_pos.x--;
    }
    if (st == 2)
        return 0;
    if (st == 1&&(board[check_pos.x][check_pos.y]->getname()==queen_||board[check_pos.x][check_pos.y]->getname()==rook_))
    {
        return true;
    }
    return 0;
}
bool north(coordinates check_pos)
{
    check_pos.y--;
    int st;
    while (!(st = is(check_pos, getcolor())))
    {
        check_pos.y--;
    }
    if (st == 2)
        return 0;
    if (st == 1&&(board[check_pos.x][check_pos.y]->getname()==queen_||board[check_pos.x][check_pos.y]->getname()==rook_))
    {
        return true;
    }
    return 0;
}
bool north(coordinates check_pos)
{
    check_pos.y--;
    int st;
    while (!(st = is(check_pos, getcolor())))
    {
        check_pos.y--;
    }
    if (st == 2)
        return 0;
    if (st == 1&&(board[check_pos.x][check_pos.y]->getname()==queen_||board[check_pos.x][check_pos.y]->getname()==rook_))
    {
        return true;
    }
    return 0;
}
bool south(coordinates check_pos)
{
    check_pos.y++;
    int st;
    while (!(st = is(check_pos, getcolor())))
    {
        check_pos.y++;
    }
    if (st == 2)
        return 0;
    if (st == 1&&(board[check_pos.x][check_pos.y]->getname()==queen_||board[check_pos.x][check_pos.y]->getname()==rook_))
    {
        return true;
    }
    return 0;
}
bool swest(coordinates check_pos)
{
    check_pos.x--;
    check_pos.y--;
    int st;
    while (!(st = is(check_pos, getcolor())))
    {
        check_pos.x--;
        check_pos.y--;
    }
    if (st == 2)
        return 0;
    if (st == 1&&(board[check_pos.x][check_pos.y]->getname()==queen_||board[check_pos.x][check_pos.y]->getname()==bishop_))
    {
        return true;
    }
    return 0;
}

bool king::ifCheck()
{
    coordinates check_pos = getposition();
    // bool find = 1;
    if (east(check_pos))
        return 1;
    if (west(check_pos))
        return 1;
    if (north(check_pos))
        return 1;
    if (south(check_pos))
        return 1;
    return 0;
}