#include "Possiblemove.hpp"
using namespace std;

/*************************************FUNCTIONS*********************************************/

void DisplayBoard()
{
    // cout << "\033[2J\033[1;1H";
    cout << "r\\c ";
    for (int i = 0; i < 8; i++)
        cout << setw(4) << i;
    cout << "\n"
         << "    ";
    for (int i = 0; i < 8; i++)
        cout << "----";
    cout << "\n";
    for (int i = 0; i < 8; i++)
    {
        cout << i << "  | ";
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != 0)
            {
                cout << setw(3) << board[i][j]->getname() << ((board[i][j]->getcolor()) ? 'w' : 'b');
            }
            else
            {
                cout << setw(4) << 0;
            }
        }
        cout << endl;
    }
    for (int i = 0; i < n_move; i++)
    {
        cout << pgn.at(i);
    }
    cout << "\n";
}

bool move(int a[4])
{
    for (auto &&i : board[a[0]][a[1]]->Node)
    {
        if (i == {a[2], a[3]})
        {
            board[a[0]][a[1]]->move({a[2], a[3]});
            return 0;
        }
    }
    cout << "Not a valid position\n";
    return 0;
}

bool show_poss_move(int a[])
{
    if (board[a[0]][a[1]] != 0)
    {
        // if (n_move % 2 == board[a[0]][a[1]]->getcolor())
        // {
        //     cout << "Not your turn.\n";
        //     return false;
        // }

        board[a[0]][a[1]]->possiblemove();
        for (auto p : *(board[a[0]][a[1]]->Node))
            cout << p << "\n";
        return true;
    }
    else
    {
        cout << "Not a valid position.\n";
        return false;
    }
}

int main()
{
    cout << "Hello World\n";
    DisplayBoard();
    bool n = 1;
    int a[4];
    do
    {
        cout << "Enter the position from which you want to move the piece : ";
        cin >> a[0] >> a[1];
        cin.clear();
        if (!show_poss_move(a))
        {
            continue;
        }
        cout << "Enter the position where you want to move the piece : ";
        cin >> a[2] >> a[3];
        cin.clear();
        move(a);
        DisplayBoard();
        boardcopier();
        if ((n_move & 1) ? (bking.ifCheck()) : (wking.ifCheck()))
        {
            cout << "************CHECK***************\n";
        }
        cout << "Do you want to make another move(0/1) : ";
        cin >> n;
        cin.clear();
    } while (n);

    return 0;
}

/**********************************************************************/
/*

0 1 0 2 1 0 2 1 3 1 1 3 5 5 1 7 4 2 4 1
*/