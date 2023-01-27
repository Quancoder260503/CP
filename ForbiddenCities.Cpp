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
vector<int>adj[N + 1];
vector<int>tadj[N + 1];
int trs,dsz,psz;
bool vis[N + 1]; 
int st[N + 1],low[N + 1];
void dfs(int u,int p){
    a[u] = low[u] = ++dsz;
    st[++psz] = u;
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
                adj[trs].push_back(u);
                while(j != v){
                    j = st[psz--];
                    adj[trs].push_back(j);
                    adj[j].push_back(trs);
               } 
            }
        }
        else low[u] = min(a[v] , low[u]);
    }
}
void dfs_calc(int u){
    vis[u] = 1;
    for(int i = 1; i < 21 ; i++){
        up[i][u] = up[i - 1][up[i - 1][u]];
    }
    for(int i = 0; i < adj[u].size(); i++){
        int v = adj[u][i]; 
        if(v == up[0][u] or vis[v]) continue;
        dp[v] = dp[up[0][v] = u] + 1;
        dfs_calc(v);
    }
}
int lca(int a, int b){
    if(dp[a] < dp[b]) swap(a,b);
    int d = dp[a] - dp[b];
    for(int i = 0; i < 21 ; i++){
        if( (d >> i) & 1) a = up[i][a];
    }
    if(a == b) return a;
    for(int i = 20; i >= 0; i--){
         int tA = up[i][a]; int tB = up[i][b];
         if(tA != tB) {
            a = tA; b = tB;
         }
    } 
    return up[0][a];
}   
int main(){
     scanf("%d%d%d",&n,&m,&q);
     for(int i = 0; i < m; i++){
         int u,v; scanf("%d%d",&u,&v);
         tadj[u].push_back(v);
         tadj[v].push_back(u); 
     }
     trs = n;
     for(int i = 1; i <= n; i++){
          if(!a[i]){
             dfs(i,0); 
          }
     } 
     for(int i = 1; i <= 2 * n; i++){
          if(!vis[i]) dfs_calc(i); 
     }
     for(int i = 1; i <= q; i++){
          int x,y,z; scanf("%d%d%d",&x,&y,&z); 
          int anc = lca(x,y); int ancx = lca(x,z); int ancy = lca(y,z);
          /////cout<<anc<<' '<<ancx<<' '<<ancy<<endl; 
          if(ancx == z or ancy == z){
               if(dp[anc] <= dp[z]) cout<<"NO"<<endl;
               else cout<<"YES"<<endl; 
          }
          else cout<<"YES"<<endl; 
     }
}
