#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
const int sz=1e5+1;
typedef long long ll;
ll l,r,mod,n,q;
int cnt;
vector<int>adj[sz];
int dp[sz];
int chldcnt[sz];
vector<int>leaf[sz];
int par[sz];
vector<int>lfs;
bool a[sz];
bool t=1;
void dfs(int u,int p){
    if(p==1 and adj[1].size()==1) par[p]=u;
    if(adj[u].size()==1 and u!=1){
        lfs.push_back(u);
        leaf[u].push_back(u); 
    }
    int odd=0 ; int even=0;
    for(int v:adj[u]){
        if(v==p) continue;
        dp[v]=dp[u]+1; 
        par[v]=u;
        dfs(v,u);
        for(int x:leaf[v]) leaf[u].push_back(x);
    }
    for(int v:leaf[u]){
        int dis=dp[v]-dp[u];
        if(dis%2==0) even++;
        else odd++;
    }
    if(even!=leaf[u].size() and odd!=leaf[u].size()) t=0;
}
int main(){
    
    freopen("Input.txt", "r", stdin);
    freopen("Output.txt", "w", stdout);
    cin>>n;
    for(int i=0;i<n-1;i++){
        int u,v;cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1,0);
    lfs.push_back(1);
    for(int lf:lfs){
        if(a[par[lf]]) continue;
        a[par[lf]]=1;
        cnt++;
    }
    bool p=1;
    for(int i=2;i<=n;i++){
        if(par[i]!=i-1){p=0;break;}
    }
    int res=n-1+cnt-lfs.size();
    if(p and dp[n]-dp[1]==n-1){cout<<3<<" "<<res<<endl;exit(0);}
    if(t) cout<<1<<" "<<res<<endl;
    else cout<<3<<" "<<res<<endl;
}