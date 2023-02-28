#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q;
vector<int>adj[N + 1]; 
int up[21][N + 1];
int in[N + 1];
int out[N + 1];
int dp[N + 1];
int timer = 1; 
void dfs(int u,int p){
     in[u] = timer++;
     for(int i = 1; i < 21; i++){
        up[i][u] = up[i - 1][up[i - 1][u]];
     }
     for(int i = 0; i < adj[u].size(); i++){
           int v = adj[u][i];
           if(v == p) continue;
           dp[v] = dp[up[0][v] = u] + 1;
           dfs(v,u);
     }
     out[u] = timer - 1;
}
long long jump(int x,int d){
    for(int i = 0; i < 21 ; i++){
        if( (d >> i) & 1) x = up[i][x];
    } 
    return x;
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
bool insubtree(int a,int b){
     return (in[a] <= in[b] and in[b] <= out[a]); 
}
int main(){
     scanf("%d%d",&n,&q);
     for(int i = 1; i < n; i++){
          int u,v; scanf("%d%d",&u,&v); 
          adj[u].push_back(v);
          adj[v].push_back(u); 
     }
     dfs(1,0);
     for(int i = 0; i < q; i++){ 
          int a,b,c,d; scanf("%d%d%d%d",&a,&b,&c,&d);
          int anc = lca(a,c);
          int dis = dp[a] + dp[c] - 2 * dp[anc];
          if(dis & 1){
               printf("%d\n",-1); 
               continue; 
          }
          int to = dis / 2; int mid;  
          if(anc == a) mid = jump(c,to);  
          else if(anc == c) mid = jump(a,to); 
          else{
               if(dp[a] < dp[c]) mid = jump(c,to);
               else if(dp[a] > dp[c]) mid = jump(a,to);
               else mid = anc; 
          }
          if(mid == b or mid == d){
               printf("%d\n",-1);
               continue; 
          }
          bool onab,oncd;  onab = oncd = 0; 
          int anc0 = lca(a,b);
          if(anc0 == a){
              if(insubtree(a,mid) and insubtree(mid,b)) onab = 1;
          }
          else if(anc0 == b){
              if(insubtree(b,mid) and insubtree(mid,a)) onab = 1; 
          }
          else{
               if(insubtree(anc0,mid) and (insubtree(mid,a) or insubtree(mid,b))) onab = 1; 
          }
          int anc1 = lca(c,d);
          if(anc1 == c){
              if(insubtree(c,mid) and insubtree(mid,d)) oncd = 1;
          }
          else if(anc1 == d){
              if(insubtree(d,mid) and insubtree(mid,c)) oncd = 1; 
          }
          else{
              if(insubtree(anc1,mid) and (insubtree(mid,c) or insubtree(mid,d))) oncd = 1;
          }
          if(onab and oncd) printf("%d\n",to);
          else printf("%d\n",-1); 
     }  
}
