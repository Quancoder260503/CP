#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+5;
ll n,k,m,q,T,p,start,ans;
int par[sz];
int compsz;
int spe[sz];
ll dp[sz];
ll val[sz];
bool a[sz];
vector<array<ll,3>>edge;
vector<array<ll,2>>point;
set<ll>adj[sz];
vector<ll>adj1[sz];
vector<ll>res;
set<ll>szval;
void bfs(int x){
    if(!szval.count(x)) return ;
    szval.erase(x); 
    queue<ll>q;
    q.push(x);
    while(q.size()){
        int t=q.front();
        q.pop();
        vector<ll>add;
        for(auto x:szval)  if(!adj[t].count(x)) add.push_back(x);
        for(auto x:add){
            q.push(x);
            szval.erase(x);
            adj1[t].push_back(x);
            adj1[x].push_back(t);
        }
    }
}
void dfs(int x){
    a[x]=1; compsz++;
    for(auto v:adj1[x]){
        if(a[v]) continue;
        dfs(v);
    }
}
int main(){
    cin>>n>>m;
    for(int i=1;i<=m;i++){
        ll u,v;cin>>u>>v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    for(int i=1;i<=n;i++) szval.insert(i);
    for(int i=1;i<=n;i++) bfs(i);
    for(int i=1;i<=n;i++){
        if(!a[i]){
             compsz=0; dfs(i);
             ans++;
             res.push_back(compsz);
        }
    }
    cout<<ans<<endl;
    sort(res.begin(),res.end());
    for(auto r:res) cout<<r<<" ";
}
