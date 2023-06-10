#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
ll d[101][101];
ll c[101][101];
const int inf=1e9;
int n,T;
const int moveX[]={3,-3,0,0,1,1,-1,-1,2,2,-2,-2,1,-1,0,0};
const int moveY[]={0,0,3,-3,2,-2,2,-2,1,-1,1,-1,0,0,1,-1};
void dijisktra(int n){
  using Q=pair<ll,pair<int,int>>;
  priority_queue<Q,vector<Q>,greater<Q>>pq;
  d[0][0]=0;
  pq.push({0,{0,0}});
  while (pq.size()){
      ll val;int x1,y1 ;pair<int,int>t;
      tie(val,t)=pq.top();
      x1=t.first;
      y1=t.second;
      pq.pop();
      if (d[x1][y1]!=val) continue;
      int d2=(n-1-x1)+(n-1-y1);
      if (d2<3 and d2>0) d[n-1][n-1]=min(d[n-1][n-1],val+d2*T);
      for (int i=0;i<16;i++){
          int x=x1+moveX[i];
          int y=y1+moveY[i];
          if (x<0 or x>=n or y<0 or y>=n) continue;
          int d1=3*T+val+c[x][y];
          if (d1<d[x][y]){
              d[x][y]=d1;
              pq.push({d[x][y],{x,y}});
          }
      }
    } 
}
int main() {
   cin>>n>>T;
    for (int i=0;i<n;i++){
        for (int j=0;j<n;j++){
            cin>>c[i][j];
            d[i][j]=inf;
        }
    } dijisktra(n);
    cout <<d[n-1][n-1];
}
