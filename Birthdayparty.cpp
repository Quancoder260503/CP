#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+5;
int n,x,k,i,j,w,q,y;
int cnt[sz];
int par[sz];
int vis[sz];
vector<array<ll,2>>adj[sz];
void dfs(int u,int anc){
     vis[u]=1;
     for(auto v:adj[u]){
         if(v[1]==anc or vis[v[0]]) continue;
         dfs(v[0],anc);
     }
}
void solve(){
    for(int i=1;i<=n;i++) adj[i].clear();
    for(int i=1;i<=q;i++){
        ll u,v;cin>>u>>v;
        u++;v++;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    }
    bool ans=1;
    for(int i=1;i<=q;i++){
        int comp=0;
        for(int j=1;j<=n;j++) vis[j]=0;
        for(int j=1;j<=n;j++){
            if(!vis[j]){
                comp++;
                dfs(j,i);
            }
        } 
        if(comp==1) ans&=1;
        else ans&=0;
    } if(!ans) cout<<"Yes"<<endl;
      else cout<<"No"<<endl;
}
int main(){
    while (cin >> n >> q && (n || q)) {
		solve();
	}
} 