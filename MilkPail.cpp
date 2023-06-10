#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
int x,y,m,k;
ll d[101][101];
exp:we can use the array to count the number of operation
void bfs(){
    queue<pair<int,int>>q;
    d[0][0]=0;
    q.push({0,0});
    while (q.size()){
        int i,j;
        tie(i,j)=q.front();
        q.pop();
        int p=d[i][j]+1;
        int pourx=min(i,y-j);
        int poury=min(x-i,j);
        int mX[]={i,0,i,x,i-pourx,i+poury};
        int mY[]={0,j,y,j,j+pourx,j-poury};
        for (int i=0;i<6;i++){
            if (p>k or d[mX[i]][mY[i]]!=LLONG_MAX) continue;
            d[mX[i]][mY[i]]=p;
            q.push({mX[i],mY[i]});
        }
    }
}
int main() {
   cin>>x>>y>>k>>m;
   for(int i=0;i<=x;i++){
       for (int j=0;j<=y;j++){
           d[i][j]=LLONG_MAX;
       }
   } bfs();
    int ans=1e5;
    for (int i=0;i<=x;i++){
        for(int j=0;j<=y;j++){
            if (d[i][j]!=LLONG_MAX){
                ans=min(ans,abs(m-i-j));
           }
       } 
    }cout <<ans;     
}
