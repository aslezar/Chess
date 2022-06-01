
#include "Pieces.h"
#include <iomanip>
using namespace std;

void DisplayBoard()
{
    cout << "\033[2J\033[1;1H";
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
            cout << setw(3) << A[i][j];
        cout << endl;
    }
}

int main(int argc, char **argu)
{
    cout << "Hello World\n";
    pawn wpawn[] = {pawn(1, 0), pawn(1, 1), pawn(1, 2), pawn(1, 3), pawn(1, 4), pawn(1, 5), pawn(1, 6), pawn(1, 7)};
    pawn bpawn[] = {pawn(0, 0), pawn(0, 1), pawn(0, 2), pawn(0, 3), pawn(0, 4), pawn(0, 5), pawn(0, 6), pawn(0, 7)};
    queen bqueen(0), wqueen(1);
    king bking(0), wking(1);
    knight blknight(0, 1), brknight(0, 0), wlknight(1, 1), wrknight(1, 0);
    bishop blbishop(0, 1), brbishop(0, 0), wlbishop(1, 1), wrbishop(1, 0);
    rook blrook(0, 1), brrook(0, 0), wlrook(1, 1), wrrook(1, 0);

    // for(int i=0;i<8;i++)
    // {
    //     wpawn[i].setposition(i);
    // }
    DisplayBoard();
    bool n = 0;
    int a[4];
    do
    {
        cout << "Enter the position from which you want to move the piece : ";
        cin >> a[0] >> a[1];
        cout << "Enter the position where you want to move the piece : ";
        cin >> a[2] >> a[3];
        DisplayBoard();
        cout << "Do you want to make another move(1/0) : ";
        cin >> n;
    } while (n);

    return 0;
}

/**********************************************************************/
