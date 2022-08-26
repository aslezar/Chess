#include "Check.hpp"

/*********************************************POSSIBLE MOVE****************************************************/
void pawn::possiblemove()
{
    if (getpreviousmove() != n_move)
    {
        Node->erase(Node->begin(), Node->end());
        int i = getcolor() ? 1 : -1;
        if (ispossible({getposition().x + i, getposition().y}))
        {
            Node->push_back({getposition().x + i, getposition().y});
            if ((ispossible({getposition().x + 2 * i, getposition().y})) && getfirstMove())
            {
                Node->push_back({getposition().x + 2 * i, getposition().y});
            }
        }
        bool useless = 1;
        if (ispossible({getposition().x + i, getposition().y + 1}, useless))
        {
            Node->push_back({getposition().x + i, getposition().y + 1});
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
                for (int j = -1; j < 2; j += 2)
                {
                    if (lastmove.initial.y == getposition().y + j && lastmove.initial.x == ((i == 1) ? 6 : 1) && lastmove.final.x == ((i == 1) ? 4 : 3))
                    {
                        Node->push_back({getposition().x + i, getposition().y + j});
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
        if (getcolor())
        {
            // Node = wking.ifCheckchecker(Node);
        }
        else
        {
            // Node = bking.ifCheck(Node);
        }
        setpreviousmove(n_move);
        ifCheckCaller();
    }
}
void bishop::possiblemove()
{
    if (getpreviousmove() != n_move)
    {
        Node->erase(Node->begin(), Node->end());
        possiblediagonally();
        setpreviousmove(n_move);
        ifCheckCaller();
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
        ifCheckCaller();
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
                    // if (isCheck({getposition().x + i, getposition().y + j}))
                    // {
                    //     continue;
                    // }
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
// void knight::possiblemove(bool a)
// {
//     if (getpreviousmove() != n_move)
//     {
//         // Castling remaining
//         Node->erase(Node->begin(), Node->end());
//         bool useless = 1;
//         possiblemove();
//         setpreviousmove(n_move);
//     }
// }
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