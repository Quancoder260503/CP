#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
bool visited[1001][1001];
const int dx[]={1,-1,0,0};
const int dy[]={0,0,-1,1};
int n;
char c[1001][1001];
int ans,cnt;
void bfs(int sx,int sy){
    ans=1;  
    cnt=0;
    visited[sx][sy]=true;
    queue<pair<int,int>>q;
    q.push({sx,sy});
    while (q.size()){
        int x;int y;
        tie(x,y)=q.front();
        q.pop();
        for (int i=0;i<4;i++){
            int x1=x+dx[i];
            int y1=y+dy[i];
            if (x1<0 or x1>=n or y1<0 or y1>=n) {
                cnt++;
                continue;
            }        
            if (c[x1][y1]=='.') {
                cnt++;
                continue;
            } if (visited[x1][y1]) continue;    
            visited[x1][y1]=1;
            ans++;
            q.push({x1,y1});
        }
    } 
}
int main() {
   cin>>n;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cin>>c[i][j];
        }
    } int max=0;
      int per=0;
    for (int i=0;i<n;i++){
        for(int j=0;j<n;j++){
            if (visited[i][j] or c[i][j]=='.') continue;
               bfs(i,j);
               if (ans==max){
                   per=min(per,cnt);
               }
               if (ans>max){
                   max=ans;
                   per=cnt;
             }
        }
    } cout <<max<<" "<<per;
}
