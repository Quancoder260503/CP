#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int p,n,mx_d,q,k1,k2;
ll ans;
int trs[sz];
vector<int>adj[sz];
int cnt[sz];
int col[sz];
bool vis[sz];
ll bit[sz];
int dfs(int u, int p) {
  trs[u] = 1;
  for(auto v : adj[u]) if(v != p and !vis[v]) {
        trs[u] += dfs(v, u);
    }
  return trs[u];
}
int centroid(int u, int p, int n) {
    for(auto v : adj[u]){
        if(v != p and !vis[v]) {
            if(trs[v] > n / 2){
                return centroid(v, u, n);
            }
        }
    }
    return u;
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
int point(int l){
    return sum(l)-sum(l-1);
}
void upd(int i,int dif)
{
	for(++i; i < sz ; i += (i & -i))
		bit[i] += dif;
}
void path(int u,int p,bool c,int d=1){
    if(d>k2) return;
    mx_d=max(d,mx_d);
    if(c) upd(d,1);
    else ans+=query(k1-d,k2-d);
    for(auto v:adj[u]){
        if(v==p or vis[v]) continue;
        path(v,u,c,d+1);
    }
}
void build(int u,int p){
    int n=dfs(u,p);
    int c=centroid(u,p,n);
    vis[c]=1;
    mx_d=0;
    for(auto v:adj[c]){
        if(vis[v]) continue;
        path(v,c,0);
        path(v,c,1);
    }
    for(int i=1;i<=mx_d+1;i++) upd(i,-query(i,i));
    for(auto v:adj[c]){
        if(!vis[v]) build(v,c);
    }
}
int main(){
     cin>>n>>k1>>k2;
     for(int i=0;i<n-1;i++){
         int u,v;
         cin>>u>>v;
         adj[u].push_back(v);
         adj[v].push_back(u);
     }
     upd(0,1);
     build(1,0);
     cout<<ans<<endl;
}
