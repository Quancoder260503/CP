#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 4e5 + 1;
long long  n,q,l,r,m,bridges,lca_itr;
vector<int>adj[N + 1];
vector<int>tadj[N + 1]; 
int vis[N + 1];
int fa_cc[N + 1];
int par[N + 1];
int fa_2ecc[N + 1];
int comp[N + 1]; 
void init(int n){
    for(int i = 1; i <= n; i++){
         vis[i] = 0; 
         fa_2ecc[i] = fa_cc[i] = i; 
         par[i] = -1; 
         comp[i] = 1;
    } 
    lca_itr = 0;
    bridges = 0; 
}
int find_2ecc(int u){
    if(u == -1) return -1;
    return fa_2ecc[u] == u ? u : fa_2ecc[u] = find_2ecc(fa_2ecc[u]);  
}
int find_cc(int u){
    u = find_2ecc(u);
    return fa_cc[u] == u ? u : fa_cc[u] = find_cc(fa_cc[u]); 
}
void make_root(int u){
    u = find_2ecc(u); 
    int root = u; 
    int child = -1;
    while(u != -1){
        int pa = find_2ecc(par[u]);
        par[u] = child;
        fa_cc[u] = root; 
        child = u;
        u = pa; 
    }
    comp[root] = comp[child]; 
} 
void merge(int a,int b){
     lca_itr++;
     vector<int>patha,pathb; 
     int lca = -1;
     while(lca == - 1){
         if(a != -1){
              a = find_2ecc(a);
              patha.push_back(a);
              if(vis[a] == lca_itr){
                   lca = a; 
                   break; 
              }
              vis[a] = lca_itr; 
              a = par[a]; 
         }
         if(b != -1){
             b = find_2ecc(b);
             pathb.push_back(b);
             if(vis[b] == lca_itr){
                  lca = b;
                  break; 
             }
             vis[b] = lca_itr;
             b = par[b]; 
         }
     }
     for(int i = 0; i < patha.size(); i++){
          fa_2ecc[patha[i]] = lca;
          if(patha[i] == lca) break;
          bridges--; 
     }
     for(int i = 0; i < pathb.size(); i++){
           fa_2ecc[pathb[i]] = lca; 
           if(pathb[i] == lca) break;
           bridges--;
     }
}
void solve(){
    for(int i = 1; i <= m; i++){
         int a,b; scanf("%d%d",&a,&b); 
         ++a; ++b;
         a = find_2ecc(a);
         b = find_2ecc(b);
         int compa = find_cc(a);
         int compb = find_cc(b); 
         if(compa != compb){
              ++bridges; 
              if(comp[compa] > comp[compb]){
                   swap(compa,compb);
                   swap(a,b); 
              }
              make_root(a); 
              par[a] = fa_cc[a] = b;
              comp[compb] += comp[a];
         }
         else merge(a,b); 
         cout<<bridges<<endl; 
    }
}
int main(){
     int t; scanf("%d",&t);
     while(t--){
          scanf("%d%d",&n,&m); 
          init(n); 
          solve(); 
     }
}
