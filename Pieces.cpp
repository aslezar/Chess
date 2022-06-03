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
    // void possiblemove();
    virtual void move(coordinates) {}
};

/***************************************DERIVED CLASSES**********************************/

class pawn : public pieces
{
    bool firstMove;

public:
    pawn(bool, int);
    void move(coordinates);
    // void possiblemove();
    // pawn();
};
class queen : public pieces
{
public:
    queen(bool);
    void move(coordinates);
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
};
class bishop : public pieces
{
    bool isleft;

public:
    bishop(bool, bool);
    void move(coordinates);
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
