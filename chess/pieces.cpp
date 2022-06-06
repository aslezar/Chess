#include <vector>
#include <list>
#include <iostream>
using namespace std;
int n_move = 0;
class pieces;
pieces *board[8][8] = {0};
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
vector<PGN> pgn;

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
    bool firstMove;

public:
    vector<coordinates> *Node;
    // Functions of pieces
    pieces();
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
    // virtual void move(coordinates) {}
    void possiblestraight();
    void possiblediagonally();
    virtual void move(coordinates);
    bool getfirstMove();
    void setfirstMove(bool);
};

/***************************************DERIVED CLASSES**********************************/

class pawn : public pieces
{
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
public:
    king(bool);
    void move(coordinates);
    void possiblemove();
};

class knight : public pieces
{
    bool isleft; // 0 for right and 1 for isleft
public:
    knight(bool, bool);
    void move(coordinates);
    void possiblemove();
};

class rook : public pieces
{
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
    return (name == pawn_) ? false : true;
}
void pieces::move(coordinates a)
{
    n_move++;
    board[getposition().x][getposition().y] = 0;
    pgn.push_back({n_move, name, getposition(), a});
    setposition(a);
}

void pieces::possiblestraight()
{
    int i = 1;
    bool a, b, c, d;
    bool a1, b1, c1, d1;
    a = b = c = d = 1;
    a1 = b1 = c1 = d1 = 1;
    coordinates pos = getposition();
    while (a || b || c || d)
    {
        if (a1 && ispossible({pos.x + i, pos.y}, a1) && a)
        {
            Node->push_back({pos.x + i, pos.y});
        }
        else
            a = 0;

        if (b1 && ispossible({pos.x - i, pos.y}, b1) && b)
        {
            Node->push_back({pos.x - i, pos.y});
        }
        else
            b = 0;

        if (c1 && ispossible({pos.x, pos.y + i}, c1) && c)
        {
            Node->push_back({pos.x, pos.y + i});
        }
        else
            c = 0;

        if (d1 && ispossible({pos.x, pos.y - i}, d1) && d)
        {
            Node->push_back({pos.x, pos.y - i});
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
    bool a1, b1, c1, d1;
    a = b = c = d = 1;
    a1 = b1 = c1 = d1 = 1;
    while (a || b || c || d)
    {
        if (a1 && ispossible({getposition().x + i, getposition().y + i}, a1) && a)
        {
            Node->push_back({getposition().x + i, getposition().y + i});
        }
        else
            a = 0;
        if (b1 && ispossible({getposition().x - i, getposition().y - i}, b1) && b)
        {
            Node->push_back({getposition().x - i, getposition().y - i});
        }
        else
            b = 0;
        if (c1 && ispossible({getposition().x - i, getposition().y + i}, c1) && c)
        {
            Node->push_back({getposition().x - i, getposition().y + i});
        }
        else
            c = 0;
        if (d1 && ispossible({getposition().x + i, getposition().y - i}, d1) && d)
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
    setfirstMove(true);
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
    setfirstMove(true);
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
    setfirstMove(true);
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
    setfirstMove(false);
    pieces::move(a);
}
void queen::move(coordinates a)
{
    pieces::move(a);
}
void king::move(coordinates a)
{
    setfirstMove(false);
    if (a.y == getposition().y - 2)
    {
        board[a.x][0]->move({a.x, 2});
    }
    if (a.y == getposition().y + 2)
    {
        board[a.x][7]->move({a.x, 4});
    }
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
    setfirstMove(false);
    pieces::move(a);
}
/*********************************************POSSIBLE MOVE****************************************************/
void pawn::possiblemove()
{
    if (getpreviousmove() != n_move)
    {
        Node->erase(Node->begin(), Node->end());
        int i = getcolor() ? 1 : -1;
        if (ispossible({getposition().x + i, getposition().y}))
        {
            Node->push_back({getposition().x +i, getposition().y});
            if ((ispossible({getposition().x + 2 * i, getposition().y})) && getfirstMove())
            {
                Node->push_back({getposition().x + 2 * i, getposition().y});
            }
        }
        bool useless = 1;
        if (ispossible({getposition().x + i, getposition().y + 1}, useless))
        {
            Node->push_back({getposition().x +  i, getposition().y + 1});
        }
        if (ispossible({getposition().x + i, getposition().y - 1}, useless))
        {
            Node->push_back({getposition().x + i, getposition().y - 1});
        }
        if (getposition().x == ((i == 1) ? 4 : 3))
        {
            PGN lastmove = pgn.at(n_move - 1);
            if (lastmove.name == pawn_)
            {
                for (int j = -1; j < 2; j+=2)
                {
                    if (lastmove.initial.y == getposition().y + j && lastmove.initial.x == ((i == 1) ? 6 : 1)&& lastmove.final.x == ((i == 1) ? 4 : 3))
                    {
                        Node->push_back({getposition().x + i , getposition().y + j});
                    }
                }
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
void king::possiblemove()
{
    if (getpreviousmove() != n_move)
    {
        // Castling remaining
        Node->erase(Node->begin(), Node->end());
        // int a,b;
        bool useless = 1;
        for (int i = -1; i < 2; i++)
        {
            for (int j = -1; j < 2; j++)
            {
                if ((i != 0 || j != 0) && (ispossible({getposition().x + i, getposition().y + j}, useless)))
                {
                    Node->push_back({getposition().x + i, getposition().y + j});
                }
            }
        }
        // Castling
        if (getfirstMove())
        {
            bool emptybetween1 = 1, emptybetween2 = 1;
            int x = getposition().x;
            if (board[x][0] != 0 && board[x][0]->getname() == rook_ && board[x][0]->getfirstMove())
            {
                for (int i = 1; i < 3; i++)
                {
                    if (board[x][i] != 0)
                    {
                        emptybetween1 = false;
                        break;
                    }
                }
                // Check if there's check in between
                if (emptybetween1)
                {
                    Node->push_back({getposition().x, 1});
                }
            }
            if (board[x][7] != 0 && board[x][7]->getname() == rook_ && board[x][7]->getfirstMove())
            {
                for (int i = 4; i < 7; i++)
                {
                    if (board[x][i] != 0)
                    {
                        emptybetween2 = false;
                        break;
                    }
                }
                // Check if there's check in between
                if (emptybetween2)
                {
                    Node->push_back({getposition().x, 5});
                }
            }
        }

        setpreviousmove(n_move);
    }
}
void knight::possiblemove()
{
    if (getpreviousmove() != n_move)
    {
        // Castling remaining
        Node->erase(Node->begin(), Node->end());
        bool useless = 1;
        for (int i = -2; i <= 2; i += 4)
        {
            for (int j = -1; j <= 1; j += 2)
            {
                if (ispossible({getposition().x + i, getposition().y + j}, useless))
                {
                    Node->push_back({getposition().x + i, getposition().y + j});
                }
                if (ispossible({getposition().x + j, getposition().y + i}, useless))
                {
                    Node->push_back({getposition().x + j, getposition().y + i});
                }
            }
        }
        setpreviousmove(n_move);
    }
}
// Check for checks everywhere everytime
//En Passant Move
//Castling Check
