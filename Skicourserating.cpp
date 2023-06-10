#include <bits/stdc++.h>
#include <utility>
using namespace std;
typedef long long ll;
const int sz=501;
const int sz1=sz*sz;
ll n,k,m,q,T,ans,curval;
ll  timer=1;
ll par=1;
ll  dx[]={0,0,-1,1};
ll  dy[]={1,-1,0,0};
ll c[sz][sz];
ll to[sz1];
ll parent[sz][sz];
ll compsize[sz1];
ll vis[sz][sz];
vector<array<ll,3>>dis;
ll start[sz1];
ll remain;
void init(int n,int m){
    int par=1;
    for(int i=1;i<=n;i++){
         for(int j=1;j<=m;j++){
             parent[i][j]=par++;
             vis[i][j]=0;
         }
     }
    for(int i=1;i<=n*m;i++){
        to[i]=i;
        compsize[i]=1;
    }
}
int find(int x){
   if(x==to[x]) return x;
   else return find(to[x]);
}
void unite(int x,int y){
    int c0=find(x);
    int c1=find(y);
    if(c0==c1) return;
    if(compsize[c0]<compsize[c1]) swap(c0,c1);
    if(compsize[c0]+compsize[c1]>=T){
        ans+=curval*(start[c0]+start[c1]);
        start[c0]=start[c1]=0;
    }
    start[c0]+=start[c1];
    compsize[c0]+=compsize[c1];
    to[c1]=c0;
}
int main(){
    cin>>n>>m>>T;
    init(n,m);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
             cin>>c[i][j];
             parent[i][j]=par++;
        } 
    }
    for(int i=1;i<=n;i++){
        for(int j=1;j<=m;j++){
            if(j+1<=m) dis.push_back({abs(c[i][j]-c[i][j+1]),parent[i][j],parent[i][j+1]});
            if(i+1<=n) dis.push_back({abs(c[i][j]-c[i+1][j]),parent[i][j],parent[i+1][j]});
        }
    }
    for(int i=1;i<=n*m;i++) cin>>start[i];
    sort(dis.begin(),dis.end());
    for(auto v:dis){
        curval=v[0];
        unite(v[1],v[2]);
    }
    cout<<ans<<endl;
}