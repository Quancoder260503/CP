#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=1e5+5;
ll n,k,m,q,T,p,start;
ld res;
int par[sz];
int compsz[sz];
int spe[sz];
ll dp[sz];
ll val[sz];
ll ans[sz];
bool a[sz];
vector<array<ll,3>>edge;
void init(int n){
    for(int i=1;i<=n;i++){
        par[i]=i;
        compsz[i]=1;
    }
}
int find(int x){
    if(x==par[x]) return x;
    else return find(par[x]);
}
void unite(int x,int y, ll w){
    x=find(x);y=find(y);
    if(x==y) return;
    if(compsz[x]<compsz[y]) swap(x,y);
    ans[x]=ans[y]+ans[x]+(ll)w*compsz[x]*compsz[y];
    compsz[x]+=compsz[y];
    par[y]=x;
}  
int main(){
     cin>>n>>m;
     init(n);
     for(int i=1;i<=n;i++) cin>>val[i];
     for(int i=1;i<=m;i++){
         ll u,v; cin>>u>>v;
         edge.push_back({min(val[u],val[v]),u,v});
     }
     sort(edge.rbegin(),edge.rend());
     for(auto e:edge){
         if(find(e[1])==find(e[2])) continue;
         unite(e[1],e[2],e[0]);
     }
    for(int i=1;i<=n;i++){
         if(a[find(i)]) continue;
         res+=ans[find(i)];a[find(i)]=1;
    }
    ld div=(ld) (n*(n-1))/(ld) 2;
    res=res/div;
    cout<<setprecision(8)<<res<<endl;
} 