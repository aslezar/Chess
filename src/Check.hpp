#include "DerivedClass.hpp"

/*****************Global variables*********************/
pawn wpawn[] = {pawn(1, 0), pawn(1, 1), pawn(1, 2), pawn(1, 3), pawn(1, 4), pawn(1, 5), pawn(1, 6), pawn(1, 7)};// white pawns
pawn bpawn[] = {pawn(0, 0), pawn(0, 1), pawn(0, 2), pawn(0, 3), pawn(0, 4), pawn(0, 5), pawn(0, 6), pawn(0, 7)};// black pawns
queen bqueen(0), wqueen(1);// black queen, white queen
king bking(0), wking(1);// black king, white king
knight blknight(0, 1), brknight(0, 0), wlknight(1, 1), wrknight(1, 0);// black left knight, black right knight, white left knight, white right knight
bishop blbishop(0, 1), brbishop(0, 0), wlbishop(1, 1), wrbishop(1, 0);// black left bishop, black right bishop, white left bishop, white right bishop
rook blrook(0, 1), brrook(0, 0), wlrook(1, 1), wrrook(1, 0);// black left rook, black right rook, white left rook, white right rook

pieces *boardcpy[8][8];// copy of board
int is(coordinates a, bool clr)// 0: empty, 1: enemy, 2: out of board, 3: friend
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
        check_pos.x--;
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
bool knightcheck(coordinates check_pos, bool clr)
{
    for (int i = -2; i <= 2; i += 4)
    {
        for (int j = -1; j <= 1; j += 2)
        {
            if (is({check_pos.x + i, check_pos.y + j}, clr) == 1 && (boardcpy[check_pos.x + i][check_pos.y + j]->getname() == knight_))
            {
                return true;
            }
            if (is({check_pos.x + j, check_pos.y + i}, clr) == 1 && (boardcpy[check_pos.x + j][check_pos.y + i]->getname() == knight_))
            {
                return true;
            }
        }
    }
    return 0;
}
bool pawncheck(coordinates check_pos, bool clr)
{
    int i = clr ? 1 : -1;
    if (is({check_pos.x + i, check_pos.y + 1}, clr) == 1 && (boardcpy[check_pos.x + i][check_pos.y + 1]->getname() == pawn_))
    {
        return true;
    }
    if (is({check_pos.x + i, check_pos.y - 1}, clr) == 1 && (boardcpy[check_pos.x + i][check_pos.y - 1]->getname() == pawn_))
    {
        return true;
    }
    return 0;
}
bool kingcheck(coordinates check_pos, bool clr)
{
    for (int i = -1; i < 2; i++)
    {
        for (int j = -1; j < 2; j++)
        {
            if ((i != 0 || j != 0) && (is({check_pos.x + i, check_pos.y + j}, clr) == 1 && (boardcpy[check_pos.x + i][check_pos.y + j]->getname() == king_)))
            {
                return true;
            }
        }
    }
    return 0;
}
bool king::ifCheck(bool isking = 0, coordinates kpos = {0, 0})
{
    coordinates check_pos;// position of king
    if (!isking)
    {
        check_pos = getposition();
    }
    else
    {
        check_pos = kpos;
    }
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
    if (knightcheck(check_pos, getcolor()))
        return 1;
    if (pawncheck(check_pos, getcolor()))
        return 1;
    if (kingcheck(check_pos, getcolor()))
        return 1;
    return 0;
}
void boardcopier() {
    // Copying board
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            boardcpy[i][j] = board[i][j];
        }
    }
}
void pieces::ifCheckCaller()
{
    vector<coordinates> *newNode = new vector<coordinates>;
    boardcopier();// Copying board
    for (auto &&i : *Node)// for each possible move
    {
        // position = i;
        boardcpy[getposition().x][getposition().y] = NULL;
        boardcpy[i.x][i.y] = this;// moving piece
        // DisplayBoardcpy();
        if (getcolor())// if white
        {
            if (!wking.ifCheck(getname() == king_, i))
            {
                newNode->push_back(i);// if not check, add to newNode
            }
        }
        else
        {
            if (!bking.ifCheck(getname() == king_, i))
            {
                newNode->push_back(i);// if not check, add to newNode
            }
        }
        boardcpy[getposition().x][getposition().y] = this;
        boardcpy[i.x][i.y] = NULL;// moving piece back
    }

    swap(newNode, Node);
    newNode->~vector();// delete newNode;
}