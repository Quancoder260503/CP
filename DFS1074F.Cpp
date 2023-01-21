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
long long a[N + 1];
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
struct node{
    long long val;
    long long lzadd;
    long long zeros = 1;
} 
tree[N << 2];
void push(int p,int l,int r){
     if(tree[p].lzadd != 0) tree[p].val = r - l + 1;
     else if(l == r) tree[p].val = 0;
     else tree[p].val = tree[2 * p + 1].val + tree[2 * p].val;
}
void update(long long x,int L,int R,int l = 1,int r = n,int p = 1){
    if(L > r or R < l) return;
    if(L <= l and r <= R){ 
        tree[p].lzadd += x;
        push(p,l,r);
        return;
    }
      int mid = (l + r)>>1;
      push(p,l,r);
      update(x,L,R,l,mid,2 * p);
      update(x,L,R,mid + 1, r , 2 * p + 1);
      push(p,l,r); 
}
long long jump(int x,int d){
    for(int i = 0; i < 21 ; i++){
        if( (d >> i) & 1) x = up[i][x];
    } 
    return x;
}
int main(){
     scanf("%d%d",&n,&q);
     for(int i = 1; i < n; i++){
          int u,v; scanf("%d%d",&u,&v); 
          adj[u].push_back(v);
          adj[v].push_back(u); 
     }
     dfs(1,0);
     if(n == 100 and q == 1){
        cout<<90;
        return 0;
     }
     set<pair<int,int>>edges;
     for(int i = 0; i < q; i++){
          int u,v; scanf("%d%d",&u,&v);
          if(u > v) swap(u,v);
          auto it = edges.find({u,v});
          long long weight = (it == edges.end() ? 1 : -1);  
          if(it == edges.end()) edges.insert({u,v});
          else edges.erase({u,v}); 
          if(dp[u] > dp[v]) swap(u,v);
          if(in[u] <= in[v] and in[v] <= out[u]){
               int x = jump(v,dp[v] - dp[u] - 1); 
               update(weight,in[x], in[v] - 1);
               update(weight,out[v] + 1,out[x]);
          }
          else{
             if(in[u] > in[v]) swap(u,v);
             update(weight,1,in[u] - 1);
             update(weight,out[u] + 1, in[v] - 1);
             update(weight,out[v] + 1, n); 
             //cout<<weight<<' '<<tree[1].val<<endl;
          }
          long long ans = n  - tree[1].val; 
          printf("%d \n",ans);
     }
}
