#include<iostream>
#include<vector>
#include<array>
#include <utility>
using namespace std;
typedef long long ll;
const int sz=2e5+5;
ll n,k,m,q,T,ans,p,anc;
ll a[sz];
ll  par[sz];
ll nxt[sz];
void init(int n){
    for(int i=1;i<=n;i++){
        par[i]=i;
        nxt[i]=i+1;
    }
}
int find(int x){
    if(x==par[x]) return x;
    else return par[x]=find(par[x]);
}
void unite(int x,int y){
    par[y]=par[find(y)]=find(x);
}
int main(){
    cin>>n>>q;
    init(n);
    for(int i=1;i<=q;i++){
         int t,u,v;cin>>t>>u>>v;
         if(t==1) unite(u,v);
         else if(t==2){
            if(u>v) swap(u,v);
            while(u<v){
                unite(u,v);
                int anc=nxt[u];
                nxt[u]=nxt[v];
                u=anc;
            }
         }
         else{
             if(find(u)==find(v)) cout<<"YES"<<endl;
             else cout<<"NO"<<endl;
         }
    }
}