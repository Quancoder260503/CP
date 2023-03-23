#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const long long INF = 1e16 + 5;
long long n,m,k,q;
long long a[N + 1];
vector<pair<long long,long long>>adj[N + 1]; 
vector<pair<pair<int,int>,int>>queries[N + 1];
int in[N + 1];
int out[N + 1];
long long ans[N + 1];
long long dp[N + 1];
int timer = 1; 
struct node{
    long long val;
    long long mval;
    long long lzadd;
} tree[N << 2];
void dfs(int u,int p){
     in[u] = timer++;
     for(int i = 0; i < adj[u].size(); i++){
           auto v = adj[u][i];
           if(v.first == p) continue;
           dp[v.first] = dp[u] + v.second;
           dfs(v.first,u);
     }
     out[u] = timer - 1;
}
void push_down(int p,int l,int mid,int r){
    if(tree[p].lzadd != 0){
        tree[2*p].mval += tree[p].lzadd; 
        tree[2*p+1].mval += tree[p].lzadd;
        tree[2*p].lzadd += tree[p].lzadd;
        tree[2*p+1].lzadd += tree[p].lzadd;
        tree[p].lzadd = 0;
    }
}
void update(long long x,int L,int R,int l = 1,int r = n,int p = 1){
    if(L > r or R < l) return;
    if(L <= l and r <= R){
        tree[p].mval += x;
        tree[p].lzadd += x;
        return;
    }
      int mid = (l + r)>>1;
      push_down(p,l,mid,r);
      update(x,L,R,l,mid,2*p);
      update(x,L,R,mid+1,r,2*p+1);
      tree[p].mval = min(tree[2*p].mval , tree[2*p + 1].mval);
}
long long querymin(int L,int R,int l = 1,int r = n,int p = 1){
     if(L > r or R < l) return INF;
     if(L <= l and r <= R) return tree[p].mval;
     int mid = (l + r)>>1;
     push_down(p,l,mid,r);
     return min(querymin(L,R,l,mid,2*p),querymin(L,R,mid+1,r,2*p + 1));   
}
void dfs1(int u,int p){
    for(int i = 0; i < queries[u].size();i++){
         auto v = queries[u][i];
         ans[v.second] = querymin(v.first.first,v.first.second);
    }
    for(int i = 0; i < adj[u].size();i++){
         auto v = adj[u][i];
         if(v.first == p) continue;
         update(-v.second,in[v.first],out[v.first]); 
         update(v.second,1,in[v.first] - 1); 
         update(v.second,out[v.first] + 1, n);
         dfs1(v.first,u);
         update(v.second,in[v.first],out[v.first]);
         update(-v.second,1,in[v.first] - 1); 
         update(-v.second,out[v.first] + 1, n);
    }
}
int main(){
    scanf("%d%d",&n,&q); 
    for(int i = 2; i <= n; i++){
        int u,w; scanf("%d%d",&u,&w);
        adj[u].push_back({i,w});
        adj[i].push_back({u,w});
    }
    for(int i = 0; i < q; i++){
        int u,v,w; scanf("%d%d%d",&w,&u,&v);
        queries[w].push_back({{u,v},i});       
    }
    dfs(1,0);
    for(int i = 1; i <= n; i++){
        if(i == 1 or adj[i].size() > 1){
            update(INF,in[i],in[i]);
            continue;
        }
        update(dp[i],in[i],in[i]);
    }
    dfs1(1,0);
    for(int i = 0; i < q; i++) cout<<ans[i]<<endl;
}
