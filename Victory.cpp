#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=5e5+10;
const int inf=1e6+1;
int n,k,m,q,add,dis;
ll timer=1;
vector<ll>adj[sz];
ll col[sz];
int dp[sz],up[20][sz];
int st[sz],en[sz];
set<array<int,2>>col_num[sz];
int bit[sz];
// for each color we are going to find the lca of (i,i+1) node the color order (Sort by DFS order). 
// add each lca by -1 and both color node by 1 
// how does this work --> assume st[i1]<=st[i2]<=st[i3]
/// --> lca(i1,i2) is the ancestor of lca(i2,i3) or lca(i2,i3) is the ancestor of lca(i1,i2)
// therefore by updating this way will give corret answer 
// the remain is just query processing. 
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=5e5+10;
const int inf=1e6+1;
int n,k,m,q,add,dis;
ll timer=1;
vector<ll>adj[sz];
ll col[sz];
int dp[sz],up[20][sz];
int st[sz],en[sz];
set<array<int,2>>col_num[sz];
int bit[sz];
int sum(int i)
{
	int c=0;
	for(++i; i > 0 ; i -= (i & -i))
		c+= bit[i];
	return c;
}
int query(int l,int r){
    return sum(r)-sum(l-1);
}
void update(int dif,int i)
{
	for(++i; i < sz ; i += (i & -i))
		bit[i] += dif;
}
void dfs(int u){
    st[u]=timer++;
    for(int i=1;i<=19;i++){
        up[i][u]=up[i-1][up[i-1][u]];
    }
    for(auto v:adj[u]){
        if(v==up[0][u]) continue;
        dp[v]=dp[up[0][v]=u]+1;
        dfs(v);
    }
    en[u]=timer-1;
}
int lca(int  a, int  b){
    if(dp[a]<dp[b]) swap(a,b);
    int d=dp[a]-dp[b];
    for(int i=0;i<=19;i++){
        if((d>>i)&1) a=up[i][a];
    }
    if(a==b) return a;
    for(int i=19;i>=0;i--){
         int tA=up[i][a]; int tB=up[i][b];
         if(tA!=tB) {a=tA; b=tB;}
    } 
    return up[0][a];
} 
void upd(int e,int add){
        auto it=col_num[col[e]].find({st[e],e});
        if(col_num[col[e]].size()!=1){
          if(it==col_num[col[e]].begin()){
                auto itr=++it; it--;
                array<int,2>rpos=(*itr);
                int anc=lca(rpos[1],e);
                update(add,st[anc]);
          }
          else if(++it==col_num[col[e]].end()){
                 it--;
                 auto itl=--it; it++;
                 array<int,2>lpos=(*itl);
                 int anc=lca(lpos[1],e);
                 update(add,st[anc]);
         }
         else if(it!=col_num[col[e]].begin() and it!=col_num[col[e]].end()){
                  auto itr=it; --it;
                  auto itl=--it;
                  array<int,2>lpos=(*itl);
                  array<int,2>rpos=(*itr);
                  int ancl=lca(e,lpos[1]);
                  int ancr=lca(e,rpos[1]);
                  int anclr=lca(lpos[1],rpos[1]);
                  update(-add,st[anclr]);
                  update(add,st[ancr]);
                  update(add,st[ancl]);
            }
      }
}  

int main(){
    scanf("%d%d%d",&n,&k,&q);
    for(int i=1;i<=n;i++){
          scanf("%lld",col+i);
    }
    for(int i=1;i<n;i++){
        int u,v; scanf("%d%d",&u,&v);
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    dfs(1);
    for(int i=1;i<=n;i++) col_num[col[i]].insert({st[i],i});
    for(int i=1;i<=k;i++){
         for(auto itr=col_num[i].begin();itr!=col_num[i].end();itr++){
             auto it=itr;
             array<int,2>go=*it; 
             update(1,st[go[1]]);
             if(++it==col_num[i].end()) break;
             array<int,2>vp=*(it); 
             int u=go[1]; int v=vp[1];
             int anc=lca(u,v);
             update(-1,st[anc]);
         }
    }
    for(int i=1;i<=q;i++){
        int t;scanf("%d",&t);
        if(t==1){
             int e,x;scanf("%d%d",&e,&x);
             upd(e,1);
             col_num[col[e]].erase({st[e],e});
             col[e]=x;
             col_num[col[e]].insert({st[e],e});
             upd(e,-1);   
        }
        else{
            int u; scanf("%d",&u);
            int ans=query(st[u],en[u]);
            printf("%d\n",ans);
        }
    }
}
