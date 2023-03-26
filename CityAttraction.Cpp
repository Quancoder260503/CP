//O(NlogN) but Tle
#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 3e5 + 5;
const long long INF = 1e16 + 5;
long long n,m,k,q;
vector<int>adj[N + 1]; 
int in[N + 1];
int out[N + 1];
int to[N + 1]; 
long long a[N + 1];
long long dp[N + 1];
int up[2][N + 1]; 
int timer = 1; 
struct node{
    pair<long long,int> mval;
    long long lzadd;
} tree[N << 2];
void dfs(int u,int p){
     to[timer] = u; 
     in[u] = timer++;
     for(int i = 0; i < adj[u].size(); i++){
           auto v = adj[u][i];
           if(v == p) continue;
           dp[v] = dp[u] + 1;
           dfs(v,u);
     }
     out[u] = timer - 1;
}
void push_down(int p,int l,int mid,int r){
    if(tree[p].lzadd != 0){
        tree[2*p].mval.first += tree[p].lzadd; 
        tree[2*p+1].mval.first += tree[p].lzadd;
        tree[2*p].lzadd += tree[p].lzadd;
        tree[2*p+1].lzadd += tree[p].lzadd;
        tree[p].lzadd = 0;
    }
}
void update(long long x,int L,int R,int l = 1,int r = n,int p = 1){
    if(L > r or R < l) return;
    if(L <= l and r <= R){
        if(l == r) tree[p].mval.second = -to[l];
        tree[p].mval.first += x;
        tree[p].lzadd += x;
        return;
    }
      int mid = (l + r)>>1;
      push_down(p,l,mid,r);
      update(x,L,R,l,mid,2*p);
      update(x,L,R,mid+1,r,2*p+1);
      tree[p].mval = max(tree[2*p].mval , tree[2*p + 1].mval);
}
pair<long long,int> query(int L,int R,int l = 1,int r = n,int p = 1){
     if(L > r or R < l) return {-INF,-INF};
     if(L <= l and r <= R) return tree[p].mval;
     int mid = (l + r) >> 1;
     push_down(p,l,mid,r);
     return max(query(L,R,l,mid,2*p),query(L,R,mid+1,r,2*p + 1));   
}
void dfs1(int u,int p){ 
    auto far = max(query(1,in[u] - 1),query(in[u] + 1, n));
    up[0][u] = -far.second;
    for(int i = 0; i < adj[u].size();i++){
         int v = adj[u][i];
         if(v == p) continue;
         update(1,in[v],out[v]); 
         update(-1,1,in[v] - 1); 
         update(-1,out[v] + 1, n);
         dfs1(v,u);
         update(-1,in[v],out[v]);
         update(1,1,in[v] - 1); 
         update(1,out[v] + 1, n);
    }
}
int main(){
    scanf("%d%lld",&n,&k); 
    for(int i = 1; i <= n; i++) scanf("%lld",&a[i]);
    for(int i = 0; i < n - 1; i++){
         int u,v; scanf("%d%d",&u,&v);
         // cout << u << ' ' << v << endl; 
         adj[u].push_back(v);
         adj[v].push_back(u); 
    }
    dfs(1,0);
    for(int i = 1; i <= n; i++) update(a[i] - dp[i],in[i],in[i]); 
    dfs1(1,0);
    int root = (k & 1 ? up[0][1] : 1); 
    for(int i = 1; i < 63; i++){
          for(int j = 1; j <= n; j++){
                up[i & 1][j] = up[i - 1 & 1][up[i - 1 & 1][j]]; 
          }
          if(k & (1ll << i)){
               root = up[i & 1][root]; 
          }
    }
    printf("%lld\n",root);
    return 0; 

