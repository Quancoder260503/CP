#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
int n,m;
bool visited[1005][1005];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
string c[1005];
void bfs(int sx,int sy){
    visited[sx][sy]=1;
    queue<pair<int,int>>q;
    q.push({sx,sy});
    while (!q.empty()){
        int x1=q.front().first;
        int y1=q.front().second;
        q.pop();
        for (int i=0;i<4;i++){
            int x=x1+dx[i];
            int y=y1+dy[i];
            if (x<0 or x>=n) continue;
            if (y<0 or y>=m) continue;
            if (c[x][y]=='.' and !visited[x][y]){
                visited[x][y]=true;
                q.push({x,y});
            }   
          }
       }
    }
 }   
int main(){
    cin>>n>>m;
    for(int i=0;i<n;i++){
            cin>>c[i];
    }
    int count=0;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            if (c[i][j]=='.' and !visited[i][j]){
                count=count+1;
                bfs(i,j);
            }
        }
    } cout <<count;
}


 
