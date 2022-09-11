#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=1e5+10;
ll n,q,m,t,f,x,k,cnt;
double ans;
vector<int>adj[sz];
double a[sz];
double sub[sz];
int par[sz];
void dfs(int u){
    ans+=a[par[u]]*(1-a[u]);
    for(auto v:adj[u]){
        if(v==par[u]) continue;
        par[v]=u;
        sub[u]+=(1-a[v]);
        dfs(v);
    }
}
int main(){
   scanf("%d", &n);
   for(int i=1;i<=n;i++) scanf("%lf", a+i);
   for(int i=0;i<n-1;i++){
       int u,v;
       scanf("%d%d", &u, &v);
       u++;v++;
       adj[u].push_back(v);
       adj[v].push_back(u);
   }
   scanf("%d", & q);
   a[0]=1;
   dfs(1);
   for(int i=1;i<=q;i++){
       int v; double x;
       scanf("%d%lf", &v, &x);
       v++;
       if(par[v]) sub[par[v]]=sub[par[v]]-(1-a[v]);
       ans-=a[par[v]]*(1-a[v]);
       ans-=a[v]*sub[v];
       a[v]=x;
       if(par[v]) sub[par[v]]=sub[par[v]]+(1-a[v]);
       ans+=a[par[v]]*(1-a[v]);
       ans+=a[v]*sub[v];
       printf("%.6f\n", (double) ans);
   }
}