#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
#include<unordered_map>
using namespace std;
typedef long long ll;
int n,k;
const int sz=1e5+2;
pair<ll,ll>p[sz];
bool visited[sz];
ll d[sz];
experience: use map if the common val is too large(1e9);
unordered_map<ll,vector<ll>>hor;
unordered_map<ll,vector<ll>>vert;
void bfs(int src){
    using T=pair<int,bool>;
    queue<T>q;
    d[src]=0;
    q.push({src,0});
    q.push({src,1});
    while (q.size()){
        int node; bool dir;
        tie(node,dir)=q.front();
        q.pop();
        ll x=p[node].first;
        ll y=p[node].second;
        if (!dir){
             for(auto u:vert[x]){
              if (d[u]>d[node]+1){
                d[u]=d[node]+1;
                q.push({u,1});
                }
           }
        }else{
            for (auto v:hor[y]){
                if (d[v]>d[node]+1){
                    d[v]=d[node]+1;
                    q.push({v,0});
                }
             }
        }
    }     
}
int main(){
    int startx,starty,endx,endy;
    cin>>n>>startx>>starty>>endx>>endy;
    for (int i=0;i<=n+1;i++){
        d[i]=LLONG_MAX;
    }
    p[0]={startx,starty};
    vert[startx].push_back(0);
    hor[starty].push_back(0);
    vert[endx].push_back(n+1);
    hor[endy].push_back(n+1);
    p[n+1]={endx,endy};
    for (int i=1;i<=n;i++){
        ll u,v;
        cin>>u>>v;
        hor[v].push_back(i);
        vert[u].push_back(i);
        p[i]={u,v};
    } bfs(0);
    cout <<d[n+1]-1;
} 
