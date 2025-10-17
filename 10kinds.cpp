#include <iostream>
#include<string>
#include<vector>
#include<stack>

using namespace std;

//connected components algorithm 
void explore(int x, int y, int ID, vector<vector<int>> &box, vector<vector<int>> &visited){
    //stores size of grid
    int numRows = box.size();
    int numCols = box[0].size();

    //tracks whether current cc is 0 or 1
    int type = box[x][y];
    stack<pair<int, int>> temp;
    temp.push({x,y});
    
    //tracks ID of current cc in 'visited' vector
    visited[x][y] = ID;

    while(!temp.empty()){
        //DFS traversal
        auto curr = temp.top();
        temp.pop();
        int row = curr.first;
        int col = curr.second;

        //test one row down
        if(row+1 < numRows && col >= 0 && col < numCols){
            if(box[row+1][col] == type && visited[row+1][col] == -1){
                visited[row+1][col] = ID;
                temp.push({row+1, col});
            }
        }
        //test one row up
        if(row-1 >= 0 && col >= 0 && col < numCols){
            if(box[row-1][col] == type && visited[row-1][col] == -1){
                visited[row-1][col] = ID;
                temp.push({row-1, col});
            }
        }
        //test one column right
        if(row >= 0 && row < numRows && col+1 < numCols){
            if(box[row][col+1] == type && visited[row][col+1] == -1){
                visited[row][col+1] = ID;
                temp.push({row, col+1});
            }
        }
        //test one column left
        if(row >= 0 && row < numRows && col-1 >= 0){
            if(box[row][col-1] == type && visited[row][col-1] == -1){
                visited[row][col-1] = ID;
                temp.push({row, col-1});
            }
        }
    }
}

int main()
{
    std::ios::sync_with_stdio(false); std::cin.tie(NULL);
    //gets input of grid size
    int r, c;
    cin >> r >> c;
    
    //creates two 2D vectors (given grid and one that checks traversals)
    vector<vector<int>> visited(r, vector<int>(c, -1));
    vector<vector<int>> box(r, vector<int>(c));

    //input grid
    string line;
    getline(cin, line);
    for(int i = 0; i < r; i++){
        getline(cin, line);
        for(int j = 0; j < c; j++){
            box[i][j] = line[j] - '0';
            visited[i][j] = -1;
        }
    }
    
    //stores cc type either 0 or 1
    //Keeps track of the current component num
    vector<int> compType;
    int currComp = 0;

    for(int i = 0; i < r; i++){
        for(int j = 0; j < c; j++){
            //-1 means not yet visited
            if(visited[i][j] == -1){
                explore(i, j, currComp, box, visited);
                compType.push_back(box[i][j]);
                currComp++;
            }
        }
    }

    //num of queries input
    int queries;
    cin >> queries;
    
    //assigns point 1 and point 2
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