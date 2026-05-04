#include <iostream>
#include <vector>
#include <string>

using namespace std;

class NQueensCSP {
private:
    int n;
    int solutionsCount;
    vector<bool> cols;
    vector<bool> mainDiag; 
    vector<bool> antiDiag; 
    vector<string> board;
    vector<vector<string>> allSolutions;

    void solve(int row) {
        // Base Case: All queens are placed successfully
        if (row == n) {
            solutionsCount++;
            // Save the very first solution found for visual proof
            if (allSolutions.empty()) { 
                allSolutions.push_back(board);
            }
            return;
        }

        for (int col = 0; col < n; ++col) {
            int mdIdx = row - col + n - 1;
            int adIdx = row + col;

            // BRANCH AND BOUND: Prune invalid branches in O(1) time
            if (cols[col] || mainDiag[mdIdx] || antiDiag[adIdx]) {
                continue; 
            }

            // PLACE QUEEN (Update state and bounds)
            board[row][col] = 'Q';
            cols[col] = true;
            mainDiag[mdIdx] = true;
            antiDiag[adIdx] = true;

            // BRANCH (Move to the next row)
            solve(row + 1);

            // BACKTRACK (Undo the move and release bounds)
            board[row][col] = '.';
            cols[col] = false;
            mainDiag[mdIdx] = false;
            antiDiag[adIdx] = false;
        }
    }

public:
    NQueensCSP(int size) {
        n = size;
        solutionsCount = 0;
        cols.assign(n, false);
        mainDiag.assign(2 * n - 1, false);
        antiDiag.assign(2 * n - 1, false);
        board.assign(n, string(n, '.'));
    }

    void findSolutions() {
        solve(0);
        
        cout << "\n--- [ N-QUEENS CSP RESULTS ] ---\n";
        cout << "Board Size (N)   : " << n << " x " << n << "\n";
        cout << "Total Solutions  : " << solutionsCount << "\n";
        
        if (solutionsCount > 0) {
            cout << "\nVisual Proof (Solution 1):\n";
            for (int i = 0; i < n; ++i) {
                cout << "  ";
                for (int j = 0; j < n; ++j) {
                    cout << allSolutions[0][i][j] << " ";
                }
                cout << "\n";
            }
        } else {
            cout << "\nNo geometrically possible solutions exist for N = " << n << ".\n";
        }
        cout << "--------------------------------\n";
    }
};

int main() {
    int n;
    cout << "===========================================\n";
    cout << "   N-QUEENS (BRANCH & BOUND + BACKTRACK)   \n";
    cout << "===========================================\n";
    cout << "Enter the board size (N): ";
    cin >> n;

    if (n <= 0) {
        cout << "Invalid board size.\n";
        return 0;
    }

    NQueensCSP solver(n);
    solver.findSolutions();

    return 0;
}