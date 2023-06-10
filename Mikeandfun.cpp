#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+5;
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
vector<array<ll,2>>point;
vector<ll>szval;
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
void unite(int x,int y){
    x=find(x); y=find(y);
    if(x==y) return;
    if(compsz[x]<compsz[y]) swap(x,y);
    compsz[x]+=compsz[y];
    par[y]=x;
}  
int main(){
    cin>>n;
    init(n);
    for (int i=1;i<=n;i++){ cin>>val[i];point.push_back({val[i],i});}
    sort(point.rbegin(),point.rend());
    int cur=1;
    for (auto p:point){
        int j=p[1]; int at=p[0];
        if(j+1<=n and val[j]<=val[j+1]) unite(j,j+1); 
        if(j-1>=0 and val[j]<=val[j-1]) unite(j,j-1);
        int x=compsz[find(j)];
        while (cur<=x) ans[cur++]=at;
    } 
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
}
