#include "DerivedClass.hpp"

/*****************Gloabal variales*********************/
pawn wpawn[] = {pawn(1, 0), pawn(1, 1), pawn(1, 2), pawn(1, 3), pawn(1, 4), pawn(1, 5), pawn(1, 6), pawn(1, 7)};
pawn bpawn[] = {pawn(0, 0), pawn(0, 1), pawn(0, 2), pawn(0, 3), pawn(0, 4), pawn(0, 5), pawn(0, 6), pawn(0, 7)};
queen bqueen(0), wqueen(1);
king bking(0), wking(1);
knight blknight(0, 1), brknight(0, 0), wlknight(1, 1), wrknight(1, 0);
bishop blbishop(0, 1), brbishop(0, 0), wlbishop(1, 1), wrbishop(1, 0);
rook blrook(0, 1), brrook(0, 0), wlrook(1, 1), wrrook(1, 0);

pieces *boardcpy[8][8];
int is(coordinates a, bool clr)
{
    if (a.x > 7 || a.x < 0 || a.y > 7 || a.y < 0)
        return 2;
    if (boardcpy[a.x][a.y] != 0)
    {
        if (boardcpy[a.x][a.y]->getcolor() != clr)
        {
            return 1;
        }
        return 3;
    }
    return 0;
}
bool east(coordinates check_pos, bool color)
{
    check_pos.x++;
    int state;
    while (!(state = is(check_pos, color)))
    {
        check_pos.x++;
    }
    if (state == 2)
        return 0;
    if (state == 1 && (boardcpy[check_pos.x][check_pos.y]->getname() == queen_ || boardcpy[check_pos.x][check_pos.y]->getname() == rook_))
    {
        return true;
    }
    return 0;
}
bool west(coordinates check_pos, bool color)
{
    check_pos.x--;
    int state;
    while (!(state = is(check_pos, color)))
    {
        check_pos.x--;
    }
    if (state == 2)
        return 0;
    if (state == 1 && (boardcpy[check_pos.x][check_pos.y]->getname() == queen_ || boardcpy[check_pos.x][check_pos.y]->getname() == rook_))
    {
        return true;
    }
    return 0;
}
bool north(coordinates check_pos, bool color)
{
    check_pos.y--;
    int state;
    while (!(state = is(check_pos, color)))
    {
        check_pos.y--;
    }
    if (state == 2)
        return 0;
    if (state == 1 && (boardcpy[check_pos.x][check_pos.y]->getname() == queen_ || boardcpy[check_pos.x][check_pos.y]->getname() == rook_))
    {
        return true;
    }
    return 0;
}
bool south(coordinates check_pos, bool color)
{
    check_pos.y++;
    int state;
    while (!(state = is(check_pos, color)))
    {
        check_pos.y++;
    }
    if (state == 2)
        return 0;
    if (state == 1 && (boardcpy[check_pos.x][check_pos.y]->getname() == queen_ || boardcpy[check_pos.x][check_pos.y]->getname() == rook_))
    {
        return true;
    }
    return 0;
}
bool swest(coordinates check_pos, bool color)
{
    check_pos.x--;
    check_pos.y++;
    int state;
    while (!(state = is(check_pos, color)))
    {
        check_pos.y++;
    }
    if (state == 2)
        return 0;
    if (state == 1 && (boardcpy[check_pos.x][check_pos.y]->getname() == queen_ || boardcpy[check_pos.x][check_pos.y]->getname() == bishop_))
    {
        return true;
    }
    return 0;
}
bool nwest(coordinates check_pos, bool color)
{
    check_pos.x--;
    check_pos.y--;
    int state;
    while (!(state = is(check_pos, color)))
    {
        check_pos.x--;
        check_pos.y--;
    }
    if (state == 2)
        return 0;
    if (state == 1 && (boardcpy[check_pos.x][check_pos.y]->getname() == queen_ || boardcpy[check_pos.x][check_pos.y]->getname() == bishop_))
    {
        return true;
    }
    return 0;
}
bool neast(coordinates check_pos, bool color)
{
    check_pos.x++;
    check_pos.y--;
    int state;
    while (!(state = is(check_pos, color)))
    {
        check_pos.x++;
        check_pos.y--;
    }
    if (state == 2)
        return 0;
    if (state == 1 && (boardcpy[check_pos.x][check_pos.y]->getname() == queen_ || boardcpy[check_pos.x][check_pos.y]->getname() == bishop_))
    {
        return true;
    }
    return 0;
}
bool seast(coordinates check_pos, bool color)
{
    check_pos.x++;
    check_pos.y++;
    int state;
    while (!(state = is(check_pos, color)))
    {
        check_pos.x++;
        check_pos.y++;
    }
    if (state == 2)
        return 0;
    if (state == 1 && (boardcpy[check_pos.x][check_pos.y]->getname() == queen_ || boardcpy[check_pos.x][check_pos.y]->getname() == bishop_))
    {
        return true;
    }
    return 0;
}
bool king::ifCheck()
{
    coordinates check_pos = getposition();
    // bool find = 1;
    if (east(check_pos, getcolor()))
        return 1;
    if (west(check_pos, getcolor()))
        return 1;
    if (north(check_pos, getcolor()))
        return 1;
    if (south(check_pos, getcolor()))
        return 1;
    if (swest(check_pos, getcolor()))
        return 1;
    if (nwest(check_pos, getcolor()))
        return 1;
    if (neast(check_pos, getcolor()))
        return 1;
    if (seast(check_pos, getcolor()))
        return 1;
    return 0;
}
void pieces::ifCheckCaller()
{
    vector<coordinates> *newNode = new vector<coordinates>;

    // Copying board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            boardcpy[i][j] = board[i][j];
        }
    }

    for (auto &&i : *Node)
    {
        // position = i;
        boardcpy[getposition().x][getposition().y] = NULL;
        boardcpy[i.x][i.y] = this;
        if (getcolor())
        {
            if (!wking.ifCheck())
            {
                newNode->push_back(i);
            }
        }
        else
        {
            if (!bking.ifCheck())
            {
                newNode->push_back(i);
            }
        }
    }
    cout << "new NODE\n";
    for (auto &&i : *newNode)
    {
        cout << i << '\n';
    }
    cout << " OLD NODE\n";

    swap(newNode, Node);
    // delete newNode;
    newNode->~vector();
}
//KNIGHT CHECK
//PAWN CHECK