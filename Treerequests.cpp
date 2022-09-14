#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=5e5+1;
int n,q,timer;
vector<int>dp[sz];
vector<int>xr[sz];
int en[sz],st[sz];
vector<int>adj[sz];
char a[sz];
void dfs(int u,int d){
    dp[d].push_back(timer);
    xr[d].push_back(1<<(a[u]-'a'));
    st[u]=timer++;
    for(auto v:adj[u]) dfs(v,d+1);
    en[u]=timer-1;
}
bool check(int x){
    if(x==0) return 1;
    if(x==(x&-x)) return 1;
    return 0;
}
int main(){
    cin>>n>>q;
    for(int i=2;i<=n;i++){
        int x;cin>>x;
        adj[x].push_back(i);
    }
    for(int i=1;i<=n;i++) cin>>a[i];
    dfs(1,1);
    for(int i=1;i<=n;i++){
        for(int j=1;j<xr[i].size();j++) xr[i][j]^=xr[i][j-1];
    }
    for(int i=1;i<=q;i++){
         int u,v;cin>>u>>v;
         int x=lower_bound(dp[v].begin(),dp[v].end(),st[u])-dp[v].begin();
         int y=upper_bound(dp[v].begin(),dp[v].end(),en[u])-dp[v].begin()-1;
         if(y<0){
             cout<<"Yes"<<endl;
             continue;
         }
         else{
              bool t;
              if(x==0) t=check(xr[v][y]);
              else t=check(xr[v][y]^xr[v][x-1]);
              if(t) cout<<"Yes"<<endl;
              else cout<<"No"<<endl;
         }
    }
}