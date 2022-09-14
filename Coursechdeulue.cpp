#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
vector<ll>g[100005];
bool visited[100005];
vector<ll>tps;
const int s=1e9+7;
void dfs(int node){
    for (int u:g[node]){
        if (!visited[u]){
            visited[u]=1;
            dfs(u);
        } 
    } tps.push_back(node);
}
int main(){
    int n,m;
    cin>>n>>m;
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
    } for (int i=1;i<=n;i++){
        if(!visited[i]){
            visited[i]=true;
            dfs(i);
        }
    } 
    bool k=true;
    ll ind[100005];
    for (int i=0;i<tps.size();i++){
        ind[tps[i]]=i;
    } for(int i=1;i<=n;i++){
        for (int u:g[i]){
            if (ind[i]<=ind[u]){
                cout <<"IMPOSSIBLE";
                k=false;
                break;
            }
        } if (!k){
            break;
        }
    } if (k){
        for (int i=tps.size()-1;i>=0;i--){
            cout << tps[i]<< " ";
        }
    }
}
