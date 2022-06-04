#include <vector>
#include <iostream>
using namespace std;
class pieces;
pieces *board[8][8] = {0};
struct coordinates
{
    int x; // row
    int y; // column
};

enum piecenames
{
    pawn_ = 1,
    rook_,
    knight_,
    bishop_,
    king_,
    queen_,
};

class pieces
{
    // char name[2];
    int name;
    coordinates position;
    bool iswhite; // Black for 0 , white:1
public:
    void setposition(coordinates a);
    coordinates getposition();
    void setname(int);
    int getname();
    bool getcolor();
    void setcolor(bool);
    virtual vector<coordinates> possiblemove()
    {
        cout << "Sed";
        coordinates a({1, 2});
        vector<coordinates> p;
        return p;
    }
    bool ispossible(coordinates);
    virtual void move(coordinates) {}
    vector<coordinates> possiblestraight();
    vector<coordinates> possiblediagonally();
};

/***************************************DERIVED CLASSES**********************************/

class pawn : public pieces
{
    bool firstMove;

public:
    pawn(bool, int);
    void move(coordinates);
    vector<coordinates> possiblemove();
    // void possiblemove();
    // pawn();
};
class queen : public pieces
{
public:
    queen(bool);
    void move(coordinates);
    vector<coordinates> possiblemove();
};

class king : public pieces
{
    bool firstMove;

public:
    king(bool);
    void move(coordinates);
};
class knight : public pieces
{
    bool isleft; // 0 for right and 1 for isleft
public:
    knight(bool, bool);
    void move(coordinates);
};
class rook : public pieces
{
    bool firstMove;
    bool isleft;

public:
    vector<coordinates> possiblemove();
    rook(bool, bool);
    void move(coordinates);
};
class bishop : public pieces
{
    bool isleft;

public:
    bishop(bool, bool);
    void move(coordinates);
    vector<coordinates> possiblemove();
};

/***********************************PIECES FUNCTIONS**************************/
void pieces::setcolor(bool a)
{
    iswhite = a;
}

bool pieces ::getcolor()
{
    return iswhite;
}

coordinates pieces::getposition()
{
    return position;
}
void pieces::setname(int a)
{
    name = a;
}
int pieces::getname()
{
    return name;
}
bool pieces::ispossible(coordinates a)
{
    // if (board[a.x][a.y] != 0 && a.x<8 &&a.x>-1&& a.y<8 &&a.y>-1)
    if (board[a.x][a.y] != 0 || (a.x > 7 || a.x < 0 || a.y > 7 || a.y < 0))
        return false;
    // if (board[a.x][a.y] != 0 )
    return true;
}

vector<coordinates> pieces::possiblestraight()
{
    vector<coordinates> PM;
    int i = 1;
    bool a, b, c, d;
    a = b = c = d = 1;
    while (a || b || c || d)
    {
        if (ispossible({getposition().x + i, getposition().y}) && a)
        {
            PM.push_back({getposition().x + i, getposition().y});
        }
        else
            a = 0;
        if (ispossible({getposition().x - i, getposition().y}) && b)
        {
            PM.push_back({getposition().x - i, getposition().y});
        }
        else
            b = 0;
        if (ispossible({getposition().x, getposition().y + i}) && c)
        {
            PM.push_back({getposition().x, getposition().y + i});
        }
        else
            c = 0;
        if (ispossible({getposition().x, getposition().y - i}))
        {
            PM.push_back({getposition().x, getposition().y - i});
        }
        else
            d = 0;
        i++;
    }
    return PM;
}
vector<coordinates> pieces::possiblediagonally()
{
    vector<coordinates> PM;
    int i = 1;
    bool a, b,c,d;
    a = b = c = d = 1;
    while (a || b || c || d)
    {
        if (ispossible({getposition().x + i, getposition().y+i}) && a)
        {
            PM.push_back({getposition().x + i, getposition().y+i});
        }
        else
            a = 0;
        if (ispossible({getposition().x - i, getposition().y-i}) && b)
        {
            PM.push_back({getposition().x - i, getposition().y-i});
        }
        else
            b = 0;
        if (ispossible({getposition().x - i, getposition().y+i}) && c)
        {
            PM.push_back({getposition().x - i, getposition().y+i});
        }
        else
            c = 0;
        if (ispossible({getposition().x + i, getposition().y-i}) && d)
        {
            PM.push_back({getposition().x + i, getposition().y-i});
        }
        else
            d = 0;
        i++;
    }
    return PM;
}
/*************************************CONSTRUCTORS******************************/
pawn ::pawn(bool c, int y)
{
    setname(pawn_);
    setcolor(c);
    firstMove = true;
    if (c)
        setposition({1, y});
    else
        setposition({6, y});
}
// bool pawn::possiblemove()
// {
//     if(firstMove)
//     {
//         if(A[a.x+2][y])
//         {
//             //Highlight
//         }
//     }
// }
queen ::queen(bool c)
{
    setname(queen_);
    setcolor(c);
    if (c)
        setposition({0, 4});
    else
        setposition({7, 4});
}
king ::king(bool c)
{
    setname(king_);
    setcolor(c);
    firstMove = true;
    if (c)
        setposition({0, 3});
    else
        setposition({7, 3});
}
knight ::knight(bool c, bool d)
{
    setname(knight_);
    setcolor(c);
    isleft = d;
    if (c && isleft)
        setposition({0, 1});
    else if (c)
        setposition({0, 6});
    else if (isleft)
        setposition({7, 1});
    else
        setposition({7, 6});
}
bishop ::bishop(bool c, bool d)
{
    setname(bishop_);
    setcolor(c);
    isleft = d;
    if (c && isleft)
        setposition({0, 2});
    else if (c)
        setposition({0, 5});
    else if (isleft)
        setposition({7, 2});
    else
        setposition({7, 5});
}
rook ::rook(bool c, bool d)
{
    setname(rook_);
    setcolor(c);
    isleft = d;
    firstMove = true;
    if (c && isleft)
        setposition({0, 0});
    else if (c)
        setposition({0, 7});
    else if (isleft)
        setposition({7, 0});
    else
        setposition({7, 7});
}

/**********************************SETPOSITION******************************************/
void pieces ::setposition(coordinates a)
{
    position = a;
    board[a.x][a.y] = this;
}

/****************************************MOVE*******************************************************/
void pawn::move(coordinates a)
{
    firstMove = false;
    board[getposition().x][getposition().y] = 0;
    setposition(a);
}
void queen::move(coordinates a)
{
    board[getposition().x][getposition().y] = 0;
    setposition(a);
}
void king::move(coordinates a)
{
    firstMove = false;
    board[getposition().x][getposition().y] = 0;
    setposition(a);
}
void knight::move(coordinates a)
{
    board[getposition().x][getposition().y] = 0;
    setposition(a);
}
void bishop::move(coordinates a)
{
    board[getposition().x][getposition().y] = 0;
    setposition(a);
}
void rook::move(coordinates a)
{
    firstMove = false;
    board[getposition().x][getposition().y] = 0;
    setposition(a);
}
/***********************************/
vector<coordinates> pawn::possiblemove()
{
    vector<coordinates> PM;
    if (ispossible({getposition().x + 1, getposition().y}))
    {
        PM.push_back({getposition().x + 1, getposition().y});
        if (firstMove)
        {
            if (ispossible({getposition().x + 2, getposition().y}))
            {

                PM.push_back({getposition().x + 2, getposition().y});
            }
        }
    }

    return PM;
}
vector<coordinates> rook::possiblemove() {
    return possiblestraight();
}

vector<coordinates> bishop::possiblemove()
{
    return possiblediagonally();
}
vector<coordinates> queen::possiblemove() {
    vector<coordinates> PM(possiblestraight());
    vector<coordinates> pm2(possiblediagonally());
    for (unsigned i=0; i<pm2.size(); i++)
    PM.push_back(pm2.at(i));
    
    return PM;
}
//MOVES CHANGE THE FNXS
