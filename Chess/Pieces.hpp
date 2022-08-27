#include <vector>
#include <list>
#include <iostream>
#include <iomanip>
using namespace std;

int n_move = 0;
class pieces;
pieces *board[8][8] = {0};

/****************************COORDINATES***************************/
struct coordinates
{
    int x; // row
    int y; // column
};
ostream &operator<<(ostream &os, coordinates &a)
{
    os << '(' << a.x << ',' << a.y << ')';
    return os;
}
bool operator==(coordinates &left, coordinates &right)
{
    return left.x == right.x && left.y == right.y;
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

/***********************************PGN*********************************/
struct PGN
{
    int moveno;
    int name;
    coordinates initial;
    coordinates final;
};
ostream &operator<<(ostream &os, PGN &a)
{
    os << a.moveno << ". " << a.name << " " << a.initial << " --> " << a.final << "    ";
    return os;
}

/***************************Global Variables*******************************/
vector<PGN> pgn;

/**********************************PIECES************************************/
class pieces
{
    int name;
    coordinates position;
    bool iswhite; // Black for 0 , white:1
    int previous_move;
    bool firstMove;

public:
    vector<coordinates> *Node;
    // Functions of pieces
    pieces(bool);
    void setposition(coordinates);
    coordinates getposition();
    void setname(int);
    int getname();
    void setpreviousmove(int);
    int getpreviousmove();
    bool getcolor();
    void setcolor(bool);
    virtual void possiblemove() {}
    virtual bool ispossible(coordinates, bool &);
    virtual bool ispossible(coordinates);
    void possiblestraight();
    void possiblediagonally();
    virtual void move(coordinates);
    bool getfirstMove();
    void setfirstMove(bool);
    void ifCheckCaller();

    // void removecheckpoints();
    //     void ischeck();
};

pieces ::pieces(bool c)
{
    Node = new vector<coordinates>;
    setcolor(c);
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
bool pieces::getfirstMove()
{
    return firstMove;
}
void pieces::setfirstMove(bool firstMove)
{
    this->firstMove = firstMove;
}
bool pieces::ispossible(coordinates a)
{
    if (board[a.x][a.y] != 0 || (a.x > 7 || a.x < 0 || a.y > 7 || a.y < 0))
        return false;
    return true;
}
bool pieces::ispossible(coordinates a, bool &find)
{
    if (a.x > 7 || a.x < 0 || a.y > 7 || a.y < 0)
        return false;
    if (board[a.x][a.y] != 0)
    {
        if (board[a.x][a.y]->getcolor() != iswhite)
        {
            find = false;
            return true;
        }
        return false;
    }
    return (name != pawn_);
}
void pieces::move(coordinates a)
{
    n_move++;
    board[getposition().x][getposition().y] = 0;
    if (board[a.x][a.y] != 0)
        board[a.x][a.y]->~pieces();

    pgn.push_back({n_move, name, getposition(), a});
    setposition(a);
}

void pieces::possiblestraight()
{
    int i = 1;
    bool right, left, up, down;
    bool find1, find2, find3, find4;
    right = left = up = down = 1;
    find1 = find2 = find3 = find4 = 1;
    coordinates pos = getposition();
    while (right || left || up || down)
    {
        if (find1 && ispossible({pos.x + i, pos.y}, find1) && right)
        {
            Node->push_back({pos.x + i, pos.y});
        }
        else
            right = 0;

        if (find2 && ispossible({pos.x - i, pos.y}, find2) && left)
        {
            Node->push_back({pos.x - i, pos.y});
        }
        else
            left = 0;

        if (find3 && ispossible({pos.x, pos.y + i}, find3) && up)
        {
            Node->push_back({pos.x, pos.y + i});
        }
        else
            up = 0;

        if (find4 && ispossible({pos.x, pos.y - i}, find4) && down)
        {
            Node->push_back({pos.x, pos.y - i});
        }
        else
            down = 0;
        i++;
    }
}
void pieces::possiblediagonally()
{
    int i = 1;
    bool se, nw, sw, ne;
    bool find1, find2, find3, find4;
    se = nw = sw = ne = 1;  //  nw=>north west
    find1 = find2 = find3 = find4 = 1;
    while (se || nw || sw || ne)
    {
        if (find1 && ispossible({getposition().x + i, getposition().y + i}, find1) && se)
        {
            Node->push_back({getposition().x + i, getposition().y + i});
        }
        else
            se = 0;
        if (find2 && ispossible({getposition().x - i, getposition().y - i}, find2) && nw)
        {
            Node->push_back({getposition().x - i, getposition().y - i});
        }
        else
            nw = 0;
        if (find3 && ispossible({getposition().x - i, getposition().y + i}, find3) && sw)
        {
            Node->push_back({getposition().x - i, getposition().y + i});
        }
        else
            sw = 0;
        if (find4 && ispossible({getposition().x + i, getposition().y - i}, find4) && ne)
        {
            Node->push_back({getposition().x + i, getposition().y - i});
        }
        else
            ne = 0;
        i++;
    }
}
/**********************************SETPOSITION******************************************/
void pieces ::setposition(coordinates a)
{
    position = a;
    board[a.x][a.y] = this;
}