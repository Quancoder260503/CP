#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
int fld[501][501];
const int dx[]={1,-1,0,0};
const int dy[]={0,0,-1,1};
bool visited[501][501];
vector<ll>comp;
using T=tuple<int,int,int,int>;
set<T>road;
int cows,n;
void bfs(int sx,int sy){
    cows=fld[sx][sy];
    visited[sx][sy]=1;
    queue<pair<int,int>>q;
    q.push({sx,sy});
    while (q.size()){
        int i,j;
        tie(i,j)=q.front();
        q.pop();
        for (int k=0;k<4;k++){
            int x=i+dx[k];
            int y=j+dy[k];
            if (x<0 or x>=n or y<0 or y>=n) continue;
            if (road.count({i,j,x,y}) or visited[x][y]) continue;
            visited[x][y]=1;
            cows+=fld[x][y];
            q.push({x,y});
        }
    }
}
int main(){
    int k,r;
    cin>>n>>k>>r;
    for (int i=0;i<r;i++){
        int u,v,u1,v1;
        cin>>u>>v>>u1>>v1;
        road.insert({u-1,v-1,u1-1,v1-1});
        road.insert({u1-1,v1-1,u-1,v-1});
    } for(int i=0;i<k;i++){
        int u,v;
        cin>>u>>v;
        fld[u-1][v-1]++;
    } ll ans=0;
      for(int i=0;i<n;i++){
          for (int j=0;j<n;j++){
              if (visited[i][j]) continue;
              bfs(i,j);
              comp.push_back(cows);
          }
      } for (int i=0;i<comp.size();i++){
          for (int j=i+1;j<comp.size();j++){
              ans+=comp[i]*comp[j];
          }
      } cout <<ans;
}   
