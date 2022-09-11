#include <bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
const int sz=2e5+5;
int a[sz];
int bit[sz];
int parent[sz];
int n,m;
int compsize[sz];
vector<int>adj[sz];
int up[19][sz];
int dp[sz];
int timer=0;
struct node{
    int v,u;
} query[sz];
void init(int n){
	for (int i = 0; i < n; i++){
		parent[i] = i;
		compsize[i] = 1;
	}
}
int find(int a){
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}
void unite(int a, int b){
    int roota=find(a); int rootb=find(b);
	if (compsize[roota] > compsize[rootb]) swap(roota, rootb);
	parent[roota] = rootb; 
    compsize[rootb] += compsize[roota];
}
int jump(int x, int d){
    for(int i=0;i<=18;i++){
        if((d>>i)&1) x=up[i][x];
    } return x ;
}
void dfs(int u){
    for(int i=1;i<=18;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        dp[v]=dp[up[0][v]=u]+1;
        dfs(v);
    }
}
int lca(ll a, ll b){
    if(dp[a]<dp[b]) swap(a,b);
    a=jump(a,dp[a]-dp[b]);
    if(a==b) return a;
    for(int i=18;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) {a=tA; b=tB;}
    } return up[0][a];
} 
void dfs_calc(int u){
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        a[v]+=a[u];
        dfs_calc(v);
    }
}
int main(){
    cin>>n>>m;
    init(n);
    int cnt=0;
    for(int i=1; i<=m;i++){
       int u,v;cin>>u>>v;
       if(find(u)==find(v)){
            cnt++;
            query[cnt].u=u;
            query[cnt].v=v;
            continue;
        }
        unite(u,v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    //for(int i=1;i<=n;i++) a[i]=1;
    for(int i=1;i<=cnt;i++){
        int u=query[i].u; int v=query[i].v;
        if(dp[u]>dp[v]) swap(u,v);
        int anc=lca(u,v);
        if(u==anc){
            a[v]--;
            a[jump(v,dp[v]-dp[u]-1)]++;
        }
        else{
            a[1]++;
            a[u]--;
            a[v]--;
        }
    }
    dfs_calc(1);
    for(int i=1;i<=n;i++){
        if(a[i]==0) cout<<1;
        else cout<<0;
    }
}