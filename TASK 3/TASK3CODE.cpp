#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

const int rows = 10, cols = 10;

char arr[rows][cols] = {
    {'S', '.', '.', '.', '.', '~', '.', '.', '^', '.'},
    {'#', '#', '#', '.', '.', '~', '#', '.', '^', '.'},
    {'.', '.', '.', '#', '.', '.', '#', '.', '.', '.'},
    {'.', '~', '~', '#', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '#', '#', '#', '#', '.'},
    {'^', '^', '.', '.', '.', '.', '.', '.', '~', '.'},
    {'#', '.', '.', '.', '.', '#', '~', '~', '~', '.'},
    {'.', '.', '#', '#', '.', '.', '.', '.', '.', '.'},
    {'.', '.', '.', '.', '.', '^', '^', '^', '^', 'G'},
    {'.', '#', '#', '#', '#', '#', '#', '.', '.', '.'}
};

int x[] = {-1, 1, 0, 0};
int y[] = {0, 0, -1, 1};
int cost[256];

struct Cell {
    int i, j, c;
    bool operator>(const Cell &other) const {
        return c > other.c;
    }
};

void allCosts() {
    for (int i = 0; i < 256; ++i) cost[i] = -1;
    cost['S'] = 0;
    cost['G'] = 0;
    cost['.'] = 1;
    cost['~'] = 3;
    cost['^'] = 5;
    cost['#'] = -1;
}

pair<int, int> findChar(char ch) {
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            if (arr[i][j] == ch) return {i, j};
    return {-1, -1};
}

void findLeastCostPath() {
    pair<int, int> start = findChar('S');
    pair<int, int> goal = findChar('G');

    vector<vector<int>> dist(rows, vector<int>(cols, INT_MAX));
    vector<vector<pair<int, int>>> parent(rows, vector<pair<int, int>>(cols, {-1, -1}));

    priority_queue<Cell, vector<Cell>, greater<Cell>> pq;
    pq.push({start.first, start.second, 0});
    dist[start.first][start.second] = 0;

    while (!pq.empty()) {
        Cell cur = pq.top();
        pq.pop();

        if (make_pair(cur.i, cur.j) == goal) break;

        for (int d = 0; d < 4; ++d) {
            int ni = cur.i + x[d];
            int nj = cur.j + y[d];

            if (ni < 0 || nj < 0 || ni >= rows || nj >= cols) continue;

            char path = arr[ni][nj];
            int moveCost = cost[path];
            if (moveCost == -1) continue;

            int newCost = dist[cur.i][cur.j] + moveCost;
            if (newCost < dist[ni][nj]) {
                dist[ni][nj] = newCost;
                parent[ni][nj] = {cur.i, cur.j};
                pq.push({ni, nj, newCost});
            }
        }
    }

    vector<pair<int, int>> pathList;
    for (pair<int, int> p = goal; p != start; p = parent[p.first][p.second])
        pathList.push_back(p);
    pathList.push_back(start);
    reverse(pathList.begin(), pathList.end());

    cout << "Execution steps:\n";
    for (auto [i, j] : pathList)
        cout << "" << i << ", " << j << "\n";

    cout << "Total Cost: " << dist[goal.first][goal.second] << endl;
}

void runPathFinder() {
    allCosts();
    findLeastCostPath();
}

int main() {
    runPathFinder();
    return 0;
}
