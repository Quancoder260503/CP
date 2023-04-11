#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500
#define f first
#define s second
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long double ld; 
const int N = 3e5 + 10;
const int inf = 1e7 + 5;
const int mod = 1e9 + 7;
const double eps = 3e-14; 
long long n,m,l,r,da,dw,h;
long long A[N + 1];
int fa[N + 1]; 
set<int>adj[N + 1]; 
struct edge{
     int u,v,id,w;
} edges[N + 1];
signed main(){
      scanf("%d%d",&n,&m);
      for(int i = 0; i < m; i++){
           int u,v; scanf("%d%d",&u,&v);
           if(u > v) swap(u,v);
           adj[u].insert(v); 
      }
      long long ans = 0; 
      for(int i = 1; i <= n; i++){
           ans += (int) adj[i].size(); 
           if(adj[i].size()){
                 int u = *adj[i].begin();
                 adj[i].erase(u);
                 if(adj[u].size() < adj[i].size()){
                       swap(adj[u],adj[i]); 
                 }
                 for(auto it : adj[i]){
                      adj[u].insert(it); 
                 }
           }
      }
      cout << ans - m << endl; 
      return 0;
}
