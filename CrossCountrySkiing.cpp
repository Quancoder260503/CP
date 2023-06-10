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
vector<pair<int,int>>wp;
int n,m;
ll a[501][501];
bool c[501][501];
void bfs(int sx,int sy,ll p){
    visited[sx][sy]=1;
    queue<pair<int,int>>q;
    q.push({sx,sy});
    while(q.size()){
        int i;int j;
        tie(i,j)=q.front();
        q.pop();
        for (int k=0;k<4;k++){
            int x=i+dx[k];
            int y=j+dy[k];
            if (x<0 or x>=n) continue;
            if (y<0 or y>=m) continue;
            if (visited[x][y] or abs(a[x][y]-a[i][j])>p) continue;
            visited[x][y]=true;
            q.push({x,y});
        }
    }
}
bool compute(ll p){
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            visited[i][j]=0;
        }
    }   bfs(wp[0].first,wp[0].second,p);
        for (auto v:wp){
          if (!visited[v.first][v.second]) return false;
    } return true;
}
int main(){
    cin>>n>>m;
    ll low1=1e9;
    ll high1=0;
    for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            cin>>a[i][j];
            high1=max(high1,a[i][j]);
            low1=min(low1,a[i][j]);
        }
    } for (int i=0;i<n;i++){
        for (int j=0;j<m;j++){
            cin>>c[i][j];
            if (c[i][j]==1) wp.push_back({i,j});
        }
    } ll high=high1-low1;
      ll low=0;
      while (high>low){
          ll mid=(high+low)/2;
          if (!compute(mid)) low=mid+1;
          else high=mid;
      } cout << low;  
}  
