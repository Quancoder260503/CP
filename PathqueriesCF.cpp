#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
const int sz=2e5+5;
ll n,k,m,q,T,p;
ll ans[sz];
ll cnt[sz];
int par[sz];
ll compsize[sz];
vector<array<int,3>>edge;
vector<array<int,2>>queries;
void init(int n){
    for(int i=1;i<=n;i++){
        compsize[i]=1;
        par[i]=i;
    }
}
int find(int x){
    if(x==par[x]) return x;
    else return x=find(par[x]);
}
void unite(int x,int y){
    x=find(x);y=find(y);
    if(x==y) return;
    if(compsize[x]<compsize[y]) swap(x,y);
    compsize[x]+=compsize[y];
    par[y]=x;
}
int main(){
    cin>>n>>q;
    init(n);
    for(int i=1;i<n;i++){
        int u,v,w;cin>>u>>v>>w;
        edge.push_back({w,u,v});
    }
    sort(edge.begin(),edge.end());
    for(int i=1;i<=q;i++){
        int x;cin>>x;
        queries.push_back({x,i});
    }
    sort(queries.begin(),queries.end());
    int pre=0;
    for(auto q:queries){
        int j=pre;
        while(j<n-1 and edge[j][0]<=q[0]){
            int u=edge[j][1]; int v=edge[j][2];
            ans[q[1]]+=compsize[find(u)]*compsize[find(v)];
            unite(u,v); j++;
        } 
        pre=j;
    }
    for(int i=1;i<q;i++) ans[queries[i][1]]+=ans[queries[i-1][1]];
    for(int i=1;i<=q;i++) cout<<ans[i]<<" ";
}