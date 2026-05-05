#include <iostream>
#include <vector>
#include <string>

using namespace std;

class NQueensSolver {
private:
    int n;
    
    // --- Variables for Standard Backtracking ---
    vector<string> boardBT;
    int solutionsCountBT;

    // --- Variables for Branch & Bound ---
    vector<string> boardBnB;
    int solutionsCountBnB;
    vector<bool> cols;
    vector<bool> mainDiag;
    vector<bool> antiDiag;

    // =========================================================
    // METHOD 1: STANDARD BACKTRACKING (O(N) Safety Check)
    // =========================================================
    bool isSafeBT(int row, int col) {
        // Check column above
        for (int i = 0; i < row; i++)
            if (boardBT[i][col] == 'Q') return false;

        // Check upper left diagonal
        for (int i = row, j = col; i >= 0 && j >= 0; i--, j--)
            if (boardBT[i][j] == 'Q') return false;

        // Check upper right diagonal
        for (int i = row, j = col; i >= 0 && j < n; i--, j++)
            if (boardBT[i][j] == 'Q') return false;

        return true;
    }

    void solveBT(int row) {
        if (row == n) {
            solutionsCountBT++;
            printBoard(boardBT, "Standard Backtracking");
            return;
        }

        for (int col = 0; col < n; col++) {
            if (isSafeBT(row, col)) {
                boardBT[row][col] = 'Q';     // Place Queen
                solveBT(row + 1);            // Recurse
                boardBT[row][col] = '.';     // Backtrack
            }
        }
    }

    // =========================================================
    // METHOD 2: BRANCH & BOUND (O(1) Safety Check via Arrays)
    // =========================================================
    void solveBnB(int row) {
        if (row == n) {
            solutionsCountBnB++;
            printBoard(boardBnB, "Branch & Bound");
            return;
        }

        for (int col = 0; col < n; col++) {
            int mdIdx = row - col + n - 1;
            int adIdx = row + col;

            // O(1) Pruning check
            if (cols[col] || mainDiag[mdIdx] || antiDiag[adIdx]) continue;

            // Place Queen and set bounds
            boardBnB[row][col] = 'Q';
            cols[col] = true; 
            mainDiag[mdIdx] = true; 
            antiDiag[adIdx] = true;

            solveBnB(row + 1); // Recurse

            // Backtrack and release bounds
            boardBnB[row][col] = '.';
            cols[col] = false; 
            mainDiag[mdIdx] = false; 
            antiDiag[adIdx] = false;
        }
    }

    // --- Utility: Print Board ---
    void printBoard(const vector<string>& board, string method) {
        cout << "Solution found using " << method << ":\n";
        for (int i = 0; i < n; i++) {
            cout << "  ";
            for (int j = 0; j < n; j++) {
                cout << board[i][j] << " ";
            }
            cout << "\n";
        }
        cout << "\n";
    }

public:
    NQueensSolver(int size) {
        n = size;
        
        boardBT.assign(n, string(n, '.'));
        solutionsCountBT = 0;

        boardBnB.assign(n, string(n, '.'));
        solutionsCountBnB = 0;
        cols.assign(n, false);
        mainDiag.assign(2 * n - 1, false);
        antiDiag.assign(2 * n - 1, false);
    }

    void runStandardBacktracking() {
        cout << "\n--- [ EXECUTING STANDARD BACKTRACKING ] ---\n";
        solveBT(0);
        cout << "Total solutions (Backtracking): " << solutionsCountBT << "\n";
    }

    void runBranchAndBound() {
        cout << "\n--- [ EXECUTING BRANCH & BOUND ] ---\n";
        solveBnB(0);
        cout << "Total solutions (Branch & Bound): " << solutionsCountBnB << "\n";
    }
};

int main() {
    int n;
    cout << "===========================================\n";
    cout << "   N-QUEENS (BACKTRACKING vs BRANCH & BOUND)\n";
    cout << "===========================================\n";
    cout << "Enter the board size (N) [Enter 4 for practical requirement]: ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid board size.\n";
        return 0;
    }

    NQueensSolver solver(n);
    
    // Execute both methods to satisfy the problem statement fully
    solver.runStandardBacktracking();
    cout << "-------------------------------------------\n";
    solver.runBranchAndBound();

    return 0;
}