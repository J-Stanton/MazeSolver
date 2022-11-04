#include <iostream>
#include <queue>
#include <vector>
using namespace std;

vector<vector<char>> maze;/*={
    {'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'},
    {'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
    {'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
    {'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','S',' ',' ','x'},
    {'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
    {'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
    {'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
    {'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
    {'x',' ',' ','x','x','x','x','x','x','x','x','x',' ',' ',' ',' ','x'},
    {'x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x',' ',' ',' ',' ','x'},
    {'x',' ',' ','x',' ','x','x','x','x',' ',' ','x',' ',' ',' ',' ','x'},
    {'x',' ',' ','x',' ',' ',' ',' ',' ',' ','G','x',' ',' ',' ',' ','x'},
    {'x',' ',' ','x',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ',' ','x'},
    {'x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x','x'},
  };*/




int m,n;
bool goal=false;
pair<int,int> curr;
pair<int,int>goalC;

bool validMove(vector<vector<pair<int,int>>> parent,int row,int col);
bool visited(vector<vector<pair<int,int>>> parent,int row,int col);
pair<int,int>findstart(int row,int col);
void printMaze();


int main(){
    queue<pair<int,int>> q;
    vector<char>row;

    string line="";
    cin>>m>>n;
    vector<vector<pair<int,int>>> parent(m,vector<pair<int,int>>(n,{-2,-2}));
    cin.ignore();
    
    for (int k=0;k<m;k++){
        getline(cin,line);
        row.clear();

        for (int j=0;j<line.length();j++){
            row.push_back(line[j]);
            //cout<<"1";
        };//for j
        maze.push_back(row);
    };//for k

    //cout<<"LMAO";
    //printMaze();
    //return 0;

    pair<int,int>start=findstart(m,n);
    //cout<<start.first<<start.second;

    q.push({start.first,start.second});
    //cout<<"hmm";

    //int c1,c2;
    int n1,n2;
    parent[start.first][start.second]=start;

    //cout<<"b4loop";
    while(!q.empty()&&goal==false){
        curr = q.front();
        q.pop();
        //cout<<"here";
        //n1= curr.first;
        //n2=curr.second;
        for (int k =0;k<4;k++){
            n1= curr.first;
            n2=curr.second;

            if (k==0){
                n1 = curr.first +1;
                //n2=curr.second+1;
            }else if(k==1){
                n2 = curr.second-1;
                //n1=curr.first-1;
            }else if(k==2){
                n1 = curr.first-1;
                //n2=curr.second-1;
            }else{
                n2 = curr.second+1;
                //n1=curr.first+1;
            };

            //printMaze(parent);
            //cout<<n1<<n2;
            if (validMove(parent,n1,n2)/*&&!visited(n1,n2)*/){
                //dist[n1][n2]=dist[curr.first][curr.second]+1;
                //cout<<"cool";

                parent[n1][n2]= curr;
                q.push({n1,n2});

                if (goal==true){
                    break;
                };
                
            };//valid

            if (goal==true){
                    break;
                };
        };//for k
    };//while

    if(q.empty()&&(goal==false)){
        cout<<"No Path";
        return 0;
    }else{
        //initialise output list
        curr=goalC;

        while (curr!=start){
            maze[curr.first][curr.second] = '*';
            curr=parent[curr.first][curr.second];
        };//while

        maze[goalC.first][goalC.second]='G';
        printMaze();
    }

    //printMaze();

};

bool validMove(vector<vector<pair<int,int>>> parent,int row,int col){
    if (row>(m-1) || row<0||col>n-1 || col<0){
        return false;
    }
    else if (maze[row][col]=='x'){
        return false;
    }else if(parent[row][col].first == -2){
        //return true;
        if (maze[row][col]=='G'){
            goal = true;
            goalC = {row,col};
        };
        return true;
    };

    /*if (maze[row][col]=='G'){
        goal=true;
    };*/
    return false;
};

bool visited(vector<vector<pair<int,int>>> parent,int row,int col){
    
    if (parent[row][col].first != -2){
        return true;
    };
    return false;
};

pair<int,int>findstart(int row,int col){
    for(int i=0;i<row;i++){
      for(int j=0;j<col;j++){
           if(maze[i][j]=='S'){
               return make_pair(i,j);
           };
        };
    };
};

void printMaze(){
    for (auto row:maze){
        for (auto element:row){
            cout<<element;
        };
        cout<<endl;
    }
};