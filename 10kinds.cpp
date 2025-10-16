#include <iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

void explore(int x, int y, int ID, vector<vector<int>> &box, vector<vector<int>> &visited){
    int numRows = box.size();
    int numCols = box[0].size();

    int type = box[x][y];
    stack<pair<int, int>> temp;
    temp.push({x,y});
    
    int moveRow[4] = {-1, 1, 0, 0};
    int moveCol[4] = {0, 0, -1, 1};
    
    visited[x][y] = ID;

    while(!temp.empty()){
        auto curr = temp.top();
        temp.pop();
        int row = curr.first;
        int col = curr.second;

        for(int i = 0; i < 4; i++){
            int newRow = row + moveRow[i];
            int newCol = col + moveCol[i];

            if(newRow >= 0 && newRow < numRows && newCol >= 0 && newCol < numCols){
                if(box[newRow][newCol] == type && visited[newRow][newCol] == -1){
                    visited[newRow][newCol] = ID;
                    temp.push({newRow, newCol});
                }
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false); std::cin.tie(NULL);
    int r, c;
    cin >> r >> c;
    
    vector<vector<int>> visited(r, vector<int>(c, -1));
    vector<vector<int>> box(r, vector<int>(c));

    string line;
    getline(cin, line);
    for(int i = 0; i < r; i++){
        getline(cin, line);
        for(int j = 0; j < c; j++){
            box[i][j] = line[j] - '0';
            visited[i][j] = -1;
        }
    }
    
    vector<int> compType;
    int visitComp = 0;

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            if(visited[i][j] == -1){
                explore(i, j, visitComp, box, visited);
                compType.push_back(box[i][j]);
                visitComp++;
            }
        }
    }

    int queries;
    cin >> queries;
    
    while(queries--){
        int r1, c1, r2, c2;
        cin >> r1 >> c1 >> r2 >> c2;
        r1--;
        c1--;
        r2--;
        c2--;

        if(visited[r1][c1] == visited[r2][c2]){
            if(compType[visited[r1][c1]] == 0){
                cout << "binary\n";
            }else{
                cout << "decimal\n";
            }
        }else{
            cout << "neither\n";
        }
    }

    return 0;
}