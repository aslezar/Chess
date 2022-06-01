#include <iostream>
int A[8][8] = {0};
struct coordinates
{
    int x; // row
    int y; // column
};

enum piecenames
{
    pawnb = 1,
    rookb,
    knightb,
    bishopb,
    kingb,
    queenb,
    pawnw,
    rookw,
    knightw,
    bishopw,
    kingw,
    queenw
};

class pieces
{
    coordinates position;
    bool color; // Black for 0 , white:1
public:
    void setposition(coordinates a);
    // void possiblemove();
    coordinates getposition();
    bool getcolor();
    void setcolor(bool);
    // void possiblemove();
};

class pawn : public pieces
{
    bool firstMove;

public:
    pawn(bool, int);
    void setposition(coordinates);
    //  void possiblemove();
    // pawn();
};

class queen : public pieces
{
public:
    queen(bool);
    void setposition(coordinates a);
};

class king : public pieces
{
public:
    king(bool);
    void setposition(coordinates a);
};
class knight : public pieces
{
    bool isleft; // 0 for right and 1 for isleft
public:
    knight(bool,bool);
    void setposition(coordinates a);
};
class rook : public pieces
{
    bool isleft;
public:
    rook(bool,bool);
    void setposition(coordinates a);
};
class bishop : public pieces
{
    bool isleft;

public:
    bishop(bool,bool);
    void setposition(coordinates a);
};
void pieces::setcolor(bool a)
{
    color = a;
}

bool pieces ::getcolor()
{
    return color;
}

void pieces ::setposition(coordinates a)
{
    position = a;
}

void pawn ::setposition(coordinates a)
{
    pieces::setposition(a);
    if (getcolor())
        A[a.x][a.y] = pawnw;
    else
        A[a.x][a.y] = pawnb;
}
coordinates pieces::getposition()
{
    return position;
}
pawn ::pawn(bool c, int y)
{
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
    setcolor(c);
    if (c)
        setposition({0, 4});
    else
        setposition({7, 4});
}
void queen::setposition(coordinates a)
{
    pieces::setposition(a);
    if (getcolor())
        A[a.x][a.y] = queenw;
    else
        A[a.x][a.y] = queenb;
}
king ::king(bool c)
{
    setcolor(c);
    if (c)
        setposition({0, 3});
    else
        setposition({7, 3});
}
knight ::knight(bool c, bool d)
{
    setcolor(c);
    isleft=d;
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
    setcolor(c);
    isleft=d;
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
    setcolor(c);
    isleft=d;
    if (c && isleft)
        setposition({0, 0});
    else if (c)
        setposition({0, 7});
    else if (isleft)
        setposition({7, 0});
    else
        setposition({7, 7});
}
void rook::setposition(coordinates a)
{
    pieces::setposition(a);
    if (getcolor())
        A[a.x][a.y] = rookw;
    else
        A[a.x][a.y] = rookb;
}
void knight::setposition(coordinates a)
{
    pieces::setposition(a);
    if (getcolor())
        A[a.x][a.y] = knightw;
    else
        A[a.x][a.y] = knightb;
}
void bishop::setposition(coordinates a)
{
    pieces::setposition(a);
    if (getcolor())
        A[a.x][a.y] = bishopw;
    else
        A[a.x][a.y] = bishopb;
}
void king::setposition(coordinates a)
{
    pieces::setposition(a);
    if (getcolor())
        A[a.x][a.y] = kingw;
    else
        A[a.x][a.y] = kingb;
}
