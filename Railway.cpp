#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<map>
#include<vector>
#include<utility>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
ll n,m,q,s,t,k;
ll timer=1;
ll up[21][sz];
ll oc[21][sz];
ll dp[sz];
ll dir[sz];
ll st[sz];
ll en[sz];
vector<ll>ans;
vector<ll>val;
vector<ll>anc[sz];
vector<array<ll,2>>adj[sz];
ll bit[sz];
ll jump(ll x,ll d){
    for(int i=0;i<=20;i++){
        if((d>>i)&1) x=up[i][x];
    }return x;
}
void dfs(int u){
    for(int i=1;i<=20;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    st[u]=timer++;
    for(auto v:adj[u]){
        if(v[0]==up[0][u]) continue;
        dp[v[0]]=dp[up[0][v[0]]=u]+1;
        dir[v[0]]=v[1];
        dfs(v[0]);
    } en[u]=timer-1;
}
ll lca(int a, int b){
    if(dp[a]<dp[b]) swap(a,b);
    a=jump(a,dp[a]-dp[b]);
    if(a==b) return a;
    for(int i=20;i>=0;i--){
        ll xa=up[i][a]; ll xb=up[i][b];
        if(xa!= xb) {a=xa;b=xb;}
    } return up[0][a];
}
ll cmp(ll a,ll b){
    return st[a]<st[b];
}
void upd(int i, ll v) {
	for (; i<=n; i+=i&(-i)) bit[i]+=v;
}
int qry(int a, int b) {
	int ans = 0;
	for (; b; b -= b & (-b)) ans += bit[b];
	for (a--; a; a -= a & (-a)) ans -= bit[a];
	return ans;
}

int main(){
    cin>>n>>m>>k;
    for(int i=1;i<=n-1;i++){
        ll u,v;cin>>u>>v;
        adj[u].push_back({v,i});
        adj[v].push_back({u,i});
    } dfs(1);
      for(int j=1;j<=m;j++){
          ll p;cin>>p;
          val.clear();
          for(int i=0;i<p;i++){
              ll x;cin>>x;
              val.push_back(x);
          } sort(val.begin(),val.end(),cmp);
            val.push_back(val[0]);
            for(int i=0;i<val.size()-1;i++){
                 ll u=val[i];ll v=val[i+1];
                 ll z=lca(u,v);
                 upd(st[u],1);
                 upd(st[v],1);
                 upd(st[z],-2);
              }
     } 
       for(int i=1;i<=n;i++){
           if(qry(st[i],en[i])>=2*k) ans.push_back(dir[i]);
      } 
        cout<<ans.size()<<endl;
        sort(ans.begin(),ans.end());
        for(auto v:ans) cout<<v<<" ";
}