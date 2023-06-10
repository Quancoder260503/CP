#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+5;
ll n,k,m,q,T,p,start,cnt,res;
ll timer=1;
int compsz[sz];
int par[sz];
vector<ll>to1;
bool a[sz];
vector<array<int,2>>edge;
vector<array<int,2>>subedge[sz];
vector<array<int,2>>component;
vector<array<int,4>>ans;
vector<int>adj[sz];
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
    x=find(x);y=find(y);
    if(x==y) return;
    if(compsz[x]<compsz[y]) swap(x,y);
    compsz[x]+=compsz[y];
    par[y]=x;
}
int main(){
   cin>>n;
   init(n);
   for(int i=1;i<n;i++){
        int u,v;cin>>u>>v;
        edge.push_back({u,v});
   } 
   int at=-1;
   for(auto e:edge){
       at++;
       if(find(e[0])==find(e[1])) continue;
       a[at]=1;
       unite(e[0],e[1]);
   }
   if(compsz[find(1)]==n){
       cout<<0<<endl;
       exit(0);
   }
   at=-1;
   for(auto e:edge){
       at++;
       if(!a[at]) subedge[find(e[0])].push_back({e[0],e[1]});
   }
   for(int i=1;i<=n;i++) a[i]=0;
   for(int i=1;i<=n;i++){
       int anc=find(i);
       if(a[anc]) continue;
       a[anc]=1; int t=subedge[anc].size();
       component.push_back({t,anc});
    }
    sort(component.rbegin(),component.rend());
    int j=0;
    int nxt=j+1;
    while (j<component.size()){
        int at=component[j][1];
        int ed=component[j][0];
        int p=0;
        while(ed and nxt<component.size()){
            unite(component[nxt][1],at);
            ans.push_back({subedge[at][p][0],subedge[at][p][1],at,component[nxt][1]});
            p++; ed--; res++; nxt++;
        }
        j++;
    }
    cout<<res<<endl;
    for(auto v:ans) cout<<v[0]<<" "<<v[1]<<" "<<v[2]<<" "<<v[3]<<endl;
}