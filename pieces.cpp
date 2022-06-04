#include <vector>
#include <iostream>
using namespace std;
int n_move = 0;
class pieces;
pieces *board[8][8] = {0};
class coordinates
{
public:
    int x; // row
    int y; // column
    friend ostream &operator<<(ostream &os, coordinates &a);
};
ostream &operator<<(ostream &os, coordinates &a)
{
    os << a.x << " " << a.y;
    return os;
}

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
    int name;
    coordinates position;
    bool iswhite; // Black for 0 , white:1
    int previous_move;

public:
    vector<coordinates> *Node;
    //Functions of pieces
    pieces();
    void setposition(coordinates a);
    coordinates getposition();
    void setname(int);
    int getname();
    void setpreviousmove(int);
    int getpreviousmove();
    bool getcolor();
    void setcolor(bool);
    virtual void possiblemove() {}
    virtual bool ispossible(coordinates);
    // virtual void move(coordinates) {}
    void possiblestraight();
    void possiblediagonally();
    virtual void move(coordinates);
};

/***************************************DERIVED CLASSES**********************************/

class pawn : public pieces
{
    bool firstMove;
public:
    pawn(bool, int);
    void move(coordinates);
    void possiblemove();
};

class queen : public pieces
{
public:
    queen(bool);
    void move(coordinates);
    void possiblemove();
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
    rook(bool, bool);
    void move(coordinates);
    void possiblemove();
};

class bishop : public pieces
{
    bool isleft;
public:
    bishop(bool, bool);
    void move(coordinates);
    void possiblemove();
};

/***********************************PIECES FUNCTIONS*****************************************/
pieces ::pieces()
{
    previous_move = -1;
}
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
void pieces::setpreviousmove(int x)
{
    previous_move = x;
}
int pieces::getpreviousmove()
{
    return previous_move;
}
bool pieces::ispossible(coordinates a)
{
    if (board[a.x][a.y] != 0 || (a.x > 7 || a.x < 0 || a.y > 7 || a.y < 0))
        return false;
    return true;
}
void pieces::move(coordinates a) {
    board[getposition().x][getposition().y] = 0;
    setposition(a);
}

void pieces::possiblestraight()
{
    int i = 1;
    bool a, b, c, d;
    a = b = c = d = 1;
    while (a || b || c || d)
    {
        if (ispossible({getposition().x + i, getposition().y}) && a)
        {
            Node->push_back({getposition().x + i, getposition().y});
        }
        else
            a = 0;
        if (ispossible({getposition().x - i, getposition().y}) && b)
        {
            Node->push_back({getposition().x - i, getposition().y});
        }
        else
            b = 0;
        if (ispossible({getposition().x, getposition().y + i}) && c)
        {
            Node->push_back({getposition().x, getposition().y + i});
        }
        else
            c = 0;
        if (ispossible({getposition().x, getposition().y - i}))
        {
            Node->push_back({getposition().x, getposition().y - i});
        }
        else
            d = 0;
        i++;
    }
}
void pieces::possiblediagonally()
{
    int i = 1;
    bool a, b, c, d;
    a = b = c = d = 1;
    while (a || b || c || d)
    {
        if (ispossible({getposition().x + i, getposition().y + i}) && a)
        {
            Node->push_back({getposition().x + i, getposition().y + i});
        }
        else
            a = 0;
        if (ispossible({getposition().x - i, getposition().y - i}) && b)
        {
            Node->push_back({getposition().x - i, getposition().y - i});
        }
        else
            b = 0;
        if (ispossible({getposition().x - i, getposition().y + i}) && c)
        {
            Node->push_back({getposition().x - i, getposition().y + i});
        }
        else
            c = 0;
        if (ispossible({getposition().x + i, getposition().y - i}) && d)
        {
            Node->push_back({getposition().x + i, getposition().y - i});
        }
        else
            d = 0;
        i++;
    }
}
/*************************************CONSTRUCTORS******************************/
pawn ::pawn(bool c, int y)
{
    Node = new vector<coordinates>;
    setname(pawn_);
    setcolor(c);
    firstMove = true;
    if (c)
        setposition({1, y});
    else
        setposition({6, y});
}

queen ::queen(bool c)
{
    Node = new vector<coordinates>;
    setname(queen_);
    setcolor(c);
    if (c)
        setposition({0, 4});
    else
        setposition({7, 4});
}
king ::king(bool c)
{
    Node = new vector<coordinates>;
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
    Node = new vector<coordinates>;
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
    Node = new vector<coordinates>;
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
    Node = new vector<coordinates>;
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
    pieces::move(a);
}
void queen::move(coordinates a)
{
    pieces::move(a);
}
void king::move(coordinates a)
{
    firstMove = false;
    pieces::move(a);
}
void knight::move(coordinates a)
{
    pieces::move(a);
}
void bishop::move(coordinates a)
{
    pieces::move(a);
}
void rook::move(coordinates a)
{
    firstMove = false;
    pieces::move(a);
}
/*********************************************POSSIBLE MOVE****************************************************/
void pawn::possiblemove()
{
    if (getpreviousmove() != n_move)
    {
        Node->erase(Node->begin(), Node->end());
        int i = getcolor() ? 1 : -1;
        if (ispossible({getposition().x + 1 * i, getposition().y}))
        {
            Node->push_back({getposition().x + 1 * i, getposition().y});
            if ((ispossible({getposition().x + 2 * i, getposition().y})) && firstMove)
            {
                Node->push_back({getposition().x + 2 * i, getposition().y});
            }
        }
        setpreviousmove(n_move);
    }
}
void rook::possiblemove()
{
    if (getpreviousmove() != n_move)
    {
        Node->erase(Node->begin(), Node->end());
        possiblestraight();
        setpreviousmove(n_move);
    }
}

void bishop::possiblemove()
{
    if (getpreviousmove() != n_move)
    {
        Node->erase(Node->begin(), Node->end());
        possiblediagonally();
        setpreviousmove(n_move);
    }
}
void queen::possiblemove()
{
    if (getpreviousmove() != n_move)
    {
        Node->erase(Node->begin(), Node->end());
        possiblestraight();
        possiblediagonally();
        setpreviousmove(n_move);
    }
}
//Knight, King
