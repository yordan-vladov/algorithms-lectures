#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

bool isValid(vector<int>& positions, int row, int col) {
    for (int prevRow = 0; prevRow < row; prevRow++) {
        int prevCol = positions[prevRow];

        if (prevCol == col) return false;                      // same column
        if (abs(prevCol - col) == abs(prevRow - row)) return false;  // same diagonal
    }
    return true;
}

void printBoard(vector<int>& positions, int n) {
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < n; col++)
            cout << (positions[row] == col ? "Q " : ". ");
        cout << endl;
    }
    cout << endl;
}

void solveNQueens(vector<int>& positions, int row, int n, int& count, bool printAll) {
    if (row == n) {
        count++;
        if (printAll) printBoard(positions, n);
        return;
    }

    for (int col = 0; col < n; col++) {
        if (isValid(positions, row, col)) {
            positions[row] = col;
            solveNQueens(positions, row + 1, n, count, printAll);
        }
    }
}

int main() {
    int n = 4;
    vector<int> positions(n);
    int count = 0;

    solveNQueens(positions, 0, n, count, true);
    cout << "Брой решения за N=" << n << ": " << count << endl;

    return 0;
}
