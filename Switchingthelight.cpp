#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
bool visited[501][501];
const int dx[]={1,-1,0,0};
const int dy[]={0,0,-1,1};
int n,m;
vector<pair<int,int>>lit[501][501];
bool act[501][501];
int cnt;
void bfs(int sx,int sy){
    cnt=1;
    act[sx][sy]=1;
    visited[sx][sy]=1;
    queue<pair<int,int>>q;
    q.push({sx,sy});
    while(q.size()){
        int x1,y1;
        tie(x1,y1)=q.front();
        q.pop();
        if (!act[x1][y1]) continue;
        for (auto adj:lit[x1][y1]){
                int i=adj.first;
                int j=adj.second;
                if (act[i][j]) continue;
                if (visited[i][j]) q.push({i,j});
                act[i][j]=1;
                cnt++;
         }
        for (int i=0;i<4;i++){
            int x=x1+dx[i];
            int y=y1+dy[i];
            if (x<0 or x>=n) continue;
            if (y<0 or y>=n) continue;
            if (visited[x][y]) continue;
            visited[x][y]=1;
            q.push({x,y});
        }    
    } 
}
int main(){
   cin>>n>>m;
       for (int i=0;i<m;i++){
        int u,v,u1,v1;
        cin>>u>>v>>u1>>v1;
        lit[u-1][v-1].push_back({u1-1,v1-1});
    } bfs(0,0);
    cout <<cnt;
}  
