#include <iostream>
using namespace std;

int A[8][8] = {0};
struct coordinates
{
    int x; // row
    int y; // column
};

enum piecenames{
    pawnb,
    rookb,
    knightb,
    bishopb,
    queenb,
    kingb,
    pawnw,
    rookw,
    knightw,
    bishopw,
    queenw,
    kingw,
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
};

class pawn : public pieces
{
    bool firstMove;
public:
    pawn(bool, int);
    void setposition(coordinates);
    // pawn();
};

class queen: public pieces
{
    queen(bool);
};

class king : public pieces
{
    king(bool);
};
class knight : public pieces
{
    bool left;  //0 for right and 1 for left
    knight(bool);
};
class rook : public pieces
{
    bool left;  
    rook(bool);
};
class bishop : public pieces
{
    bool left;  
    bishop(bool);
};


int main(int argc, char **argu)
{
    cout << "Hello World\n";
    pawn wpawn[] = {pawn(1, 0), pawn(1, 1), pawn(1, 2), pawn(1, 3), pawn(1, 4), pawn(1, 5), pawn(1, 6), pawn(1, 7)};
    pawn bpawn[] = {pawn(0, 0), pawn(0, 1), pawn(0, 2), pawn(0, 3), pawn(0, 4), pawn(0, 5), pawn(0, 6), pawn(0, 7)};

    // for(int i=0;i<8;i++)
    // {
    //     wpawn[i].setposition(i);
    // }

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << A[i][j];
        cout << endl;
    }
    return 0;
}

/**********************************************************************/
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
    setposition(a);
    if (getcolor())
        A[a.x][a.y]=pawnw;
    else
        A[a.x][a.y]=pawnb;
}
coordinates pieces::getposition()
{
    return position;
}
pawn ::pawn(bool c, int y)
{
    setcolor(c);
    firstMove=true;
    if (c)
        setposition({1, y});
    else
        setposition({6, y});
}
queen ::queen(bool c)
{
    setcolor(c);
    if (c)
        setposition({0, 4});
    else
        setposition({7, 4});
}
king ::king(bool c)
{
    setcolor(c);
    if (c)
        setposition({0, 3});
    else
        setposition({7, 3});
}
knight ::knight(bool c)
{
    setcolor(c);
    if (c && left)
        setposition({0, 1});
    else if (c)
        setposition({0, 6});
    else if (left)
        setposition({7, 1});
    else
        setposition({7, 6});
}
bishop ::bishop(bool c)
{
    setcolor(c);
    if (c && left)
        setposition({0, 2});
    else if (c)
        setposition({0, 5});
    else if (left)
        setposition({7, 2});
    else
        setposition({7, 5});
}
rook ::rook(bool c)
{
    setcolor(c);
    if (c && left)
        setposition({0, 0});
    else if (c)
        setposition({0, 7});
    else if (left)
        setposition({7, 0});
    else
        setposition({7, 7});
}
