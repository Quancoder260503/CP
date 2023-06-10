#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+1;
int p,n,mx_d,q;
int trs[sz];
vector<int>adj[sz];
vector<array<int,2>>que[sz];
int ans[sz];
int cnt[sz];
int col[sz];
bool vis[sz];
int bit[sz];
int dfs(int u, int p) {
  trs[u] = 1;
  for(auto v : adj[u]) if(v != p and !vis[v]) {
        trs[u] += dfs(v, u);
    }
  return trs[u];
}
int sum(int i)
{
	int c=0;
	for(++i; i > 0 ; i -= (i & -i))
		c+= bit[i];
	return c;
}
int query(int l,int r){
    return sum(r)-sum(l-1);
}
void upd(int i,int dif)
{
	for(++i; i < sz ; i += (i & -i))
		bit[i] += dif;
}
void dfs_add(int u,int p,int add){
    upd(cnt[col[u]],-1);
    cnt[col[u]]+=add;
    upd(cnt[col[u]],1);
    for(auto v:adj[u]){
        if(v==p or vis[v]) continue;
        dfs_add(v,u,add);
    }
}
void dfs_hld(int u,int p,bool c){
    int mx=-1;
    int big=-1;
    for(auto v:adj[u]){
        if(v==p) continue;
        if(mx<trs[v]){
            mx=trs[v];
            big=v;
        }
    }
    for(auto v:adj[u]){
        if(v==p or v==big) continue;
        dfs_hld(v,u,0);
    }
    if(big!=-1){
        dfs_hld(big,u,1);
        vis[big]=1;
    }
    dfs_add(u,p,1);
    if(big!=-1) vis[big]=0;
    for(auto v:que[u]){
        ans[v[1]]=query(v[0],n);
    }
    if(!c) dfs_add(u,p,-1);
}
int main(){
     cin>>n>>q;
     for(int i=1;i<=n;i++) cin>>col[i];
     for(int i=1;i<n;i++){
         int u,v;cin>>u>>v;
         adj[u].push_back(v);
         adj[v].push_back(u);
     }
     for(int i=1;i<=q;i++){
         int v,k;cin>>v>>k;
         que[v].push_back({k,i});
     }
     dfs(1,0);
     dfs_hld(1,0,1);
     for(int i=1;i<=q;i++) cout<<ans[i]<<endl;
}
