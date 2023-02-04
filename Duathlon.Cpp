#include<bits/stdc++.h>
#include<iostream>
using namespace std;
typedef long long ll;
typedef long double ld;
const int N = 5e5 + 5;
int up[21][N + 1];
int dp[N + 1];
int a[N + 1];
int n,m,q;
long long res; 
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
int trs,dsz,psz;
bool vis[N + 1]; 
int st[N + 1],low[N + 1];
int comsize = 0; 
void dfs(int u,int p){
    a[u] = low[u] = ++dsz;
    st[++psz] = u;
    comsize++; 
    for(int i = 0; i < tadj[u].size(); i++){
        int v = tadj[u][i];
        if(v == p) continue;
        if(!a[v]){
            dfs(v,u);
            low[u] = min(low[u] , low[v]);
            if( low[v] >= a[u]){
                int j = u;
                trs++;
                adj[u].push_back(trs);
               // adj[trs].push_back(u);
                while(j != v){
                    j = st[psz--];
                    adj[trs].push_back(j);
                   // adj[j].push_back(trs);
               } 
            }
        }
        else low[u] = min(a[v] , low[u]);
    }
}
void dfs_calc(int u){
     dp[u] = (u <= n);
     for(int i = 0; i  < adj[u].size(); i++){ 
          int v = adj[u][i];
           dfs_calc(v);
           dp[u] += dp[v];
           if(u > n) res = res - (long long) adj[u].size() * (dp[v] - 1) * dp[v]; 
     }
     if(u > n) res = res - (long long) adj[u].size() * (comsize - dp[u] - 1) * (comsize - dp[u]);
} 
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         tadj[u].push_back(v);
         tadj[v].push_back(u); 
     }
     trs = n;
     for(int i = 1; i <= n; i++){
          if(!a[i]){
             comsize = 0;
             dfs(i,0); 
             res += (long long) comsize * (comsize - 1) * (comsize - 2); 
             dfs_calc(i); 
          }
     }
     cout<<res<<endl; 
}
