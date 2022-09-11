#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
const int block=500;
ll timer=1;
ll curr=0;
int n,q,m,k,r;
ll st[sz],en[sz];
ll a[sz];
vector<array<ll,2>>to[25001];
vector<ll>cmp[25001];
ll ans[501][25001];
ll dp[sz];
vector<ll>adj[sz];
struct compare {
 bool operator()(const array<ll,2>& value,
        const int& key)
 {
  return (value[0] < key);
 }
 bool operator()(const int& key,
     const array<ll,2>& value)
 {
  return (key < value[0]);
 }
};
const int mod=1e9+7;
void dfs(int u){
    to[a[u]].push_back({timer,u});
    st[u]=timer++;
    for(auto v:adj[u]) dfs(v);
     en[u]=timer-1;
}
void dfs1(int u,int tar,int x){
    if(a[u]==tar) x++;
    ans[dp[tar]][a[u]]+=x;
    for(auto v:adj[u]) dfs1(v,tar,x);
}
int main(){
   cin>>n>>r>>q; 
   cin>>a[1];
   cmp[a[1]].push_back(1);
   for(int i=2;i<=n;i++){
       int x;cin>>x>>a[i];
       adj[x].push_back(i);
       cmp[a[i]].push_back(i);
    } 
   dfs(1);
   for(int i=1;i<=r;i++){
       if(cmp[i].size()<501) continue;
       dp[i]=++curr;
       dfs1(1,i,0);
   }
   for(int i=0;i<q;i++){
    ll u,w,res;cin>>u>>w;
    if(dp[u]>0) cout<<ans[dp[u]][w]<<endl;
    else{
    const auto &p=to[w];res=0;  
    for(auto v:to[u]){
      int x=upper_bound(p.begin(),p.end(),en[v[1]],compare())-lower_bound(p.begin(),p.end(),st[v[1]],compare());
      res+=x;
       } cout<<res<<endl;
    }
  }
}