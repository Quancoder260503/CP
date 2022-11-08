#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
const int inf=1e7+5;
int n,m,src,cnt,ans;
int a[sz];
int ord[sz];
int timer;
int up[17][sz];
vector<int>adj1[sz];
vector<int>adj[sz];
bool vis[sz];
int at[sz];
int to[sz];
int trs[sz];
int d[sz],st[sz];
void dfs(int u,int p){
     trs[u]=1;
     st[timer++]=u;
     for(int i=0;i<adj[u].size();i++){
          int v=adj[u][i];
          if(v==p) continue;
          d[v]=d[up[0][v]=u]+1;
          dfs(v,u);
          trs[u]+=trs[v];
     }
}
int centroid(int u,int p){
     for(int i=0;i<adj[u].size();i++){
          int v = adj[u][i];
          if(v==p) continue;
          if( trs[v]*2 > n ) return centroid(v,u);
     }
     return u;
}
int jump(int x, int d){
    for(int i=0;i<=16;i++){
        if((d>>i)&1) x=up[i][x];
    } return x ;
}
int lca(int  a, int  b){
    if(d[a]<d[b]) swap(a,b);
    a=jump(a,d[a]-d[b]);
    if(a==b) return a;
    for(int i=16;i>=0;i--){
         int tA=up[i][a]; 
         int tB=up[i][b];
         if(tA!=tB) {a=tA; b=tB;}
    } return up[0][a];
} 
void dfs1(int u,int p){
     int cnt = 0; 
     queue<int>q;
     for(int i=0;i<adj[u].size();i++){
          int v = adj[u][i];
          if (v == p) continue;
          dfs1(v,u);
     }
     for(int i=0;i<adj[u].size();i++){
          int v=adj[u][i];
          if(v==p) continue;
          if(to[v]) q.push(v);
     }
     while (q.size()){
          int v=q.front();
          q.pop();
          auto it=find(adj[u].begin(),adj[u].end(),v);
          auto it1=find(adj[v].begin(),adj[v].end(),u);
          adj[u].erase(it);
          adj[v].erase(it1);
     }
     for(int i = 0; i < adj[u].size(); i++){
          int v = adj[u][i];
          if(v==p) continue;
          if(adj[v].size()==1) q.push(v),cnt++,ans+=2;
     }
     if(q.size()){
        to[u]=q.front();
        int cur=to[u];
        at[cur]=u;
        q.pop();
        q.push(u);
        while(q.size()){
             int  v = q.front(); 
             at[v]=cur;
             to[cur]=v;
             cur=v; 
             q.pop();
        }
     }
}
int main(){
      cin>>n;
      for(int i=1;i<n;i++){
           int u,v; cin>>u>>v;
           adj1[u].push_back(v);
           adj1[v].push_back(u);
           adj[u].push_back(v);
           adj[v].push_back(u);
      }
      dfs(1,0);
      for(int i=1;i<=16;i++){
          for(int j=1;j<=n;j++) up[i][j]=up[i-1][up[i-1][j]];
      }
      ll res=0;
      for(int i=0;i<n;i++){
          int u=st[i];
          int v=st[(i+n/2)%n];
          res+=d[u]+d[v]-2*d[lca(u,v)];
          ord[v]=u;
      }
      int c=centroid(1,0);
      dfs1(c,0);
      int l=0; 
      for(int i=1;i<=n;i++){
           if(!to[i]){
              l=i;
              ans+=2;
           }
      }
      if(adj1[l].size()>0){
          to[l]=adj1[l][0];
          int r=at[adj1[l][0]];
          to[r]=l;
      }
      cout<<ans<<' '<<res<<endl;
      for(int i=1;i<=n;i++) cout<<to[i]<<' ';
      cout<<endl;
      for(int i=1;i<=n;i++) cout<<ord[i]<<' ';
} 
