#include "pieces.cpp"
#include <iomanip>
using namespace std;

void DisplayBoard()
{
    cout << "\033[2J\033[1;1H"
         << "r\\c ";
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
}

bool move(int a[4])
{
    // vector<coordinates>::iterator it;
    // it = find (board[a[0]][a[1]]->Node->begin()+1, board[a[0]][a[1]]->Node->end(), {a[2],a[3]});
    // if(it!= board[a[0]][a[1]]->Node->end())
    //     board[a[0]][a[1]]->move({a[2],a[3]});
    // }
    // else
    //     cout<<"das baj gye kya>\n";
    if (board[a[0]][a[1]] != 0)
    {
        board[a[0]][a[1]]->move({a[2], a[3]});
    }
    n_move++;
    return 0;
}

void show_poss_move(int a[])
{
    board[a[0]][a[1]]->possiblemove();
    if (board[a[0]][a[1]] != 0)
    {
        for (auto p : *(board[a[0]][a[1]]->Node))
            cout << p << "\n";
    }
}

int main()
{
    cout << "Hello World\n";
    pawn wpawn[] = {pawn(1, 0), pawn(1, 1), pawn(1, 2), pawn(1, 3), pawn(1, 4), pawn(1, 5), pawn(1, 6), pawn(1, 7)};
    pawn bpawn[] = {pawn(0, 0), pawn(0, 1), pawn(0, 2), pawn(0, 3), pawn(0, 4), pawn(0, 5), pawn(0, 6), pawn(0, 7)};
    queen bqueen(0), wqueen(1);
    king bking(0), wking(1);
    knight blknight(0, 1), brknight(0, 0), wlknight(1, 1), wrknight(1, 0);
    bishop blbishop(0, 1), brbishop(0, 0), wlbishop(1, 1), wrbishop(1, 0);
    rook blrook(0, 1), brrook(0, 0), wlrook(1, 1), wrrook(1, 0);
    DisplayBoard();
    bool n = 0;
    int a[4];
    do
    {
        cout << "Enter the position from which you want to move the piece : ";
        cin >> a[0] >> a[1];
        cin.clear();
        show_poss_move(a);
        cout << "Enter the position where you want to move the piece : ";
        cin >> a[2] >> a[3];
        cin.clear();
        move(a);
        DisplayBoard();
        cout << "Do you want to make another move(0/1) : ";
        cin >> n;
        cin.clear();
    } while (n);

    return 0;
}

/**********************************************************************/
