#include "Possiblemove.hpp"
using namespace std;

/*************************************FUNCTIONS*********************************************/
string printname(int n) {
    switch (n)
    {
    case 1:
        return "P";
    case 2:
        return "R";
    case 3:
        return "N";
    case 4:
        return "B";
    case 5:
        return "K";
    case 6:
        return "Q";
    }
    return "Error: 404";
}
void DisplayBoard()
{
    // cout << "\033[2J\033[1;1H";
    system("clear");
    cout << "r\\c ";
    for (int i = 0; i < 8; i++)
        cout << setw(4) << char('a'+i);
    cout << "\n"
         << "    ";
    for (int i = 0; i < 8; i++)
        cout << "----";
    cout << "\n";
    for (int i = 7; i >= 0; i--)
    {
        cout << i+1 << "  | ";
        for (int j = 7; j >= 0; j--)
        {
            if (board[i][j] != 0)
            {
                cout << setw(3) << printname(board[i][j]->getname()) << ((board[i][j]->getcolor()) ? 'w' : 'b');
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
        cout << pgn[i];
    }
    cout << "\n";
}
bool isCheckmate() {
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (board[i][j] != 0&&board[i][j]->getcolor()!=(n_move%2))
            {
                board[i][j]->possiblemove();
                if (board[i][j]->Node->size())
                {
                    return 0;
                }
            }
        }
    }
    return 1;
}
bool move(int a[4])
{
    for (coordinates i : *(board[a[0]][a[1]]->Node))
    {
        if (i.x == a[2]&&i.y==a[3])
        {
            board[a[0]][a[1]]->move({a[2], a[3]});
            return 1;
        }
    }
    cout << "Not a valid position\n";
    return 0;
}

bool show_poss_move(int a[])
{
    if (board[a[0]][a[1]] != 0)
    {
        if (n_move % 2 == board[a[0]][a[1]]->getcolor())
        {
            cout << "Not your turn.\n";
            return false;
        }

        board[a[0]][a[1]]->possiblemove();
        if (board[a[0]][a[1]]->Node->size()==0)
        {
            cout<<"No possible move\n";
            return false;
        }
        
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
    // cout << "Hello World\n";
    DisplayBoard();
    // bool n = 1;
    int a[4];
    char x;
    do
    {
        cout<<"******************"<<((n_move%2)?"Black":"White")<<"'s Turn*********************\n";
        cout << "Enter the position from which you want to move the piece : ";
        cin >> x>> a[0] ;
        a[1]='h'-x;
        a[0]--;
        cin.clear();
        if (!show_poss_move(a))
        {
            continue;
        }
        cout << "Enter the position where you want to move the piece : ";
        cin >> x >> a[2];
        a[3]='h'-x;
        a[2]--;
        cin.clear();
        if(!move(a)){
            continue;
        }
        DisplayBoard();
        boardcopier();
        if ((n_move & 1) ? (bking.ifCheck()) : (wking.ifCheck()))
        {
            if(isCheckmate()) {
                cout<<"******************CHECKMATE**********************\n";
                cout<<"******************"<<((n_move%2)?"White":"Black")<<" Wins*********************\n";
                exit(0);
            }
            cout << "************CHECK***************\n";
        }
        // cout << "Do you want to make another move(0/1) : ";
        // cin >> n;
        cin.clear();
    } while (1);

    return 0;
}

/**********************************************************************/
/*

0 1 0 2 1 0 2 1 3 1 1 3 5 5 1 7 4 2 4 1

1 2 2 2 1
6 3 5 3 1
1 1 3 1 1
7 4

3 0
*/
