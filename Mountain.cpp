#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
const int sz=1e3+1;
const int sz1=sz*sz;
int n,k,m,q,hmax;
int timer=1;
int par=1;
int dx[]={0,0,-1,1};
int dy[]={1,-1,0,0};
int c[sz][sz];
int res[sz][sz];
int parent[sz][sz];
int to[sz1];
vector<ll>point[sz1];
vector<array<ll,2>>height[sz1];
list<pair<int,int>>sub[sz1];
int find(int i,int j){
    int t=parent[i][j];
    while (t!=to[t]) t=to[t];
    int t1=parent[i][j];
    while(t1!=t){
        to[t1]=t;
        t1=to[t1];
    }
    parent[i][j]=t;
    return t;
}
int highest(int x){
     return c[sub[x].begin()->first][sub[x].begin()->second];
}
void unite(int x1,int y1,int x2,int y2,int h){
    int c1=find(x1,y1);
    int c2=find(x2,y2);
    if(c1==c2) return;
    if( highest(c2)>highest(c1)) swap(x2,x1),swap(y2,y1),swap(c1,c2);
    to[c2]=c1;
    if(highest(c1)==highest(c2)){
        sub[c1].splice(sub[c1].begin(),sub[c2]);
        sub[c2].clear(); 
        return;
    }
    for(auto v:sub[c2]){
        res[v.first][v.second]=c[v.first][v.second]-h;
    }
    sub[c2].clear();
    return;
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cin>>c[i][j];
            hmax=max(hmax,c[i][j]);
            height[c[i][j]].push_back({i,j});
            parent[i][j]=par;
            to[par]=par;
            sub[par].push_back({i,j});
            par++;
        }
    }
     for(int j=hmax;j>=0;j--){
        for(auto v:height[j]){
            for(int i=0;i<4;i++){
                if(v[0]+dx[i]<1 or v[0]+dx[i]>n) continue;
                if(v[1]+dy[i]<1 or v[1]+dy[i]>m) continue;
                if(c[v[0]][v[1]]<=c[v[0]+dx[i]][v[1]+dy[i]]){
                unite(v[0],v[1],v[0]+dx[i],v[1]+dy[i],c[v[0]][v[1]]);
                }
            }
        }
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
             int t=find(i,j);
             for(auto x:sub[t]) res[x.first][x.second]=c[x.first][x.second];
             sub[t].clear();
         } 
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            cout<<res[i][j]<<" ";
        } 
        cout<<endl;
    }
}