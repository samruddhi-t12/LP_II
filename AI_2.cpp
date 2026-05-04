#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <stack>
#include <cfloat>

using namespace std;

// Pair to hold (x, y) coordinates
typedef pair<int, int> Pair;

// Pair to hold (f-value, (x, y)) for the priority queue
typedef pair<double, Pair> pPair;

// Structure to hold cell details
struct Cell {
    int parent_x, parent_y;
    double f, g, h;
};

class AStarPathfinder {
private:
    int ROW, COL;
    vector<vector<int>> grid;

    // A Utility Function to check whether given cell (row, col) is valid
    bool isValid(int row, int col) {
        return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
    }

    // A Utility Function to check whether the given cell is unblocked
    bool isUnBlocked(int row, int col) {
        return grid[row][col] == 0; // 0 means empty, 1 means wall
    }

    // A Utility Function to check whether destination cell has been reached
    bool isDestination(int row, int col, Pair dest) {
        return (row == dest.first && col == dest.second);
    }

    // A Utility Function to calculate the Manhattan Distance heuristic
    double calculateHValue(int row, int col, Pair dest) {
        return abs(row - dest.first) + abs(col - dest.second);
    }

    // A Utility Function to trace the path from the source to destination
    void tracePath(vector<vector<Cell>>& cellDetails, Pair dest) {
        cout << "\n--- [ GOAL REACHED! ] ---\n";
        cout << "The optimal path is: ";
        int row = dest.first;
        int col = dest.second;

        stack<Pair> Path;

        while (!(cellDetails[row][col].parent_x == row && cellDetails[row][col].parent_y == col)) {
            Path.push(make_pair(row, col));
            int temp_row = cellDetails[row][col].parent_x;
            int temp_col = cellDetails[row][col].parent_y;
            row = temp_row;
            col = temp_col;
        }

        Path.push(make_pair(row, col));
        
        vector<vector<char>> pathGrid(ROW, vector<char>(COL, '.'));
        for(int i=0; i<ROW; i++) {
            for(int j=0; j<COL; j++) {
                if(grid[i][j] == 1) pathGrid[i][j] = '#'; // Walls
            }
        }

        while (!Path.empty()) {
            pair<int, int> p = Path.top();
            Path.pop();
            cout << "-> (" << p.first << "," << p.second << ") ";
            pathGrid[p.first][p.second] = '*'; // Mark path
        }
        cout << "\n\nVisual Path Grid (* = path, # = wall, . = open):\n";
        for(int i=0; i<ROW; i++) {
            for(int j=0; j<COL; j++) {
                cout << pathGrid[i][j] << "  ";
            }
            cout << "\n";
        }
    }

public:
    AStarPathfinder(int r, int c, vector<vector<int>> g) {
        ROW = r;
        COL = c;
        grid = g;
    }

    // A Function to find the shortest path between a given source cell to a destination cell
    void aStarSearch(Pair src, Pair dest) {
        if (!isValid(src.first, src.second) || !isValid(dest.first, dest.second)) {
            cout << "Source or destination is invalid\n";
            return;
        }
        if (!isUnBlocked(src.first, src.second) || !isUnBlocked(dest.first, dest.second)) {
            cout << "Source or destination is blocked\n";
            return;
        }
        if (isDestination(src.first, src.second, dest)) {
            cout << "We are already at the destination\n";
            return;
        }

        vector<vector<bool>> closedList(ROW, vector<bool>(COL, false));
        vector<vector<Cell>> cellDetails(ROW, vector<Cell>(COL));

        for (int i = 0; i < ROW; i++) {
            for (int j = 0; j < COL; j++) {
                cellDetails[i][j].f = FLT_MAX;
                cellDetails[i][j].g = FLT_MAX;
                cellDetails[i][j].h = FLT_MAX;
                cellDetails[i][j].parent_x = -1;
                cellDetails[i][j].parent_y = -1;
            }
        }

        // Initialize parameters of the starting node
        int i = src.first, j = src.second;
        cellDetails[i][j].f = 0.0;
        cellDetails[i][j].g = 0.0;
        cellDetails[i][j].h = 0.0;
        cellDetails[i][j].parent_x = i;
        cellDetails[i][j].parent_y = j;

        priority_queue<pPair, vector<pPair>, greater<pPair>> openList;
        openList.push(make_pair(0.0, make_pair(i, j)));

        // Explore 4 directions (Up, Down, Left, Right)
        int rowDir[] = {-1, 1, 0, 0};
        int colDir[] = {0, 0, -1, 1};

        bool foundDest = false;

        while (!openList.empty()) {
            pPair p = openList.top();
            openList.pop();

            i = p.second.first;
            j = p.second.second;
            closedList[i][j] = true;

            for (int dir = 0; dir < 4; dir++) {
                int newRow = i + rowDir[dir];
                int newCol = j + colDir[dir];

                if (isValid(newRow, newCol)) {
                    if (isDestination(newRow, newCol, dest)) {
                        cellDetails[newRow][newCol].parent_x = i;
                        cellDetails[newRow][newCol].parent_y = j;
                        tracePath(cellDetails, dest);
                        foundDest = true;
                        return;
                    }
                    else if (!closedList[newRow][newCol] && isUnBlocked(newRow, newCol)) {
                        double gNew = cellDetails[i][j].g + 1.0;
                        double hNew = calculateHValue(newRow, newCol, dest);
                        double fNew = gNew + hNew;

                        if (cellDetails[newRow][newCol].f == FLT_MAX || cellDetails[newRow][newCol].f > fNew) {
                            openList.push(make_pair(fNew, make_pair(newRow, newCol)));
                            cellDetails[newRow][newCol].f = fNew;
                            cellDetails[newRow][newCol].g = gNew;
                            cellDetails[newRow][newCol].h = hNew;
                            cellDetails[newRow][newCol].parent_x = i;
                            cellDetails[newRow][newCol].parent_y = j;
                        }
                    }
                }
            }
        }
        if (!foundDest) cout << "Failed to find the Destination Cell\n";
    }
};

int main() {
    int ROW, COL;
    cout << "===========================================\n";
    cout << "  A* ALGORITHM (GRID PATHFINDING WITH WALLS)\n";
    cout << "===========================================\n";
    
    cout << "Enter Grid Rows and Columns (e.g., 5 5): ";
    cin >> ROW >> COL;

    vector<vector<int>> grid(ROW, vector<int>(COL));
    cout << "\nEnter the grid map (0 for empty, 1 for wall):\n";
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            cin >> grid[i][j];
        }
    }

    int startX, startY, endX, endY;
    cout << "\nEnter Start coordinates (row col) [0-indexed]: ";
    cin >> startX >> startY;
    
    cout << "Enter Goal coordinates (row col) [0-indexed]: ";
    cin >> endX >> endY;

    Pair src = make_pair(startX, startY);
    Pair dest = make_pair(endX, endY);

    AStarPathfinder astar(ROW, COL, grid);
    cout << "\nCalculating Path...";
    astar.aStarSearch(src, dest);

    return 0;
}