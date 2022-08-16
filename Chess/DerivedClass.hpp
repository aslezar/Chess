#include "Pieces.hpp"

/***************************************DERIVED CLASSES**********************************/
class pawn : public pieces
{
public:
    pawn(bool, int);
    void move(coordinates);
    void possiblemove();
    void promote(coordinates);
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
    void possiblemove(bool);
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

/*************************************CONSTRUCTORS******************************/
pawn ::pawn(bool c, int y) : pieces(c)
{
    setname(pawn_);
    setcolor(c);
    setfirstMove(true);
    if (c)
        setposition({1, y});
    else
        setposition({6, y});
}
queen ::queen(bool c) : pieces(c)
{
    setname(queen_);
    if (c)
        setposition({0, 4});
    else
        setposition({7, 4});
}
king ::king(bool c) : pieces(c)
{
    setname(king_);
    setfirstMove(true);
    if (c)
        setposition({0, 3});
    else
        setposition({7, 3});
}
knight ::knight(bool c, bool d) : pieces(c)
{
    setname(knight_);
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
bishop ::bishop(bool c, bool d) : pieces(c)
{
    setname(bishop_);
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
rook ::rook(bool c, bool d) : pieces(c)
{
    setname(rook_);
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

/****************************************MOVE*******************************************************/
void pawn::move(coordinates a)
{
    setfirstMove(false);
    if (n_move > 1)
    {
        PGN lastmove = pgn.at(n_move - 1);
        if (abs(lastmove.initial.y - getposition().y) == 1 && lastmove.initial.x == (getcolor() ? 6 : 1) && lastmove.final.x == (getcolor() ? 4 : 3))
        {
            board[lastmove.final.x][lastmove.initial.y]->~pieces();
            board[lastmove.final.x][lastmove.initial.y] = 0;
        }
    }
    if (a.x == (getcolor() ? 7 : 0))
    {
        promote(a);
        return;
    }
    pieces::move(a);
}
void pawn::promote(coordinates a)
{
    char PromotedPiece;
    do
    {
        cout << "Into which piece you want to promote your pawn to?\n(r/q/b/k)";
        cin >> PromotedPiece;
        board[a.x][a.y] = 0;
    } while (PromotedPiece != 'q' && PromotedPiece != 'r' && PromotedPiece != 'b' && PromotedPiece != 'k');
    
    switch (PromotedPiece)
    {
    case 'r':
    {
        rook *r = new rook(getcolor(), true);
        r->setposition({a.x, a.y});
        this->~pawn();
        return;
    }
    case 'q':
    {
        queen *q = new queen(getcolor());
        q->setposition({a.x, a.y});
        this->~pawn();
        return;
    }
    case 'b':
    {
        bishop *b = new bishop(getcolor(), true);
        b->setposition({a.x, a.y});
        this->~pawn();
        return;
    }
    case 'k':
    {
        knight *k = new knight(getcolor(), true);
        k->setposition({a.x, a.y});
        this->~pawn();
        return;
    }
    default:
        break;
    }
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
