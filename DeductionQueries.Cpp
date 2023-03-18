#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = (1 << 19);
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,m,k,q,x,ans,t;
long long na,nb,nc; 
vector<pii>adj[N + 1];
long long a[N + 1]; 
char s[N + 1]; 
map<long long,long long>parent;
map<long long,long long>dp;
pair<long long,long long>find(int u){
     if(parent.count(u)){
          pair<long long,long long> info = find(parent[u]);
          return {parent[u] = info.first,dp[u] = dp[u] xor info.second}; 
     }
     return {u,0}; 
}
void unite(long long u,long long v,long long w){
      pair<int,int>pu = find(u);
      pair<int,int>pv = find(v);
      if(pu.first == pv.first) return; 
      parent[pu.first] = pv.first; 
      dp[pu.first] = pv.second xor pu.second xor w; 
}
long long query(long long u, long long v){
      pair<int,int>pu = find(u);
      pair<int,int>pv = find(v);
      if(pu.first != pv.first) return -1;
    //  cout << pv.first << ' ' << pv.second << endl; 
      return pu.second xor pv.second; 
}
int main(){
      scanf("%d",&q);
      long long last = 0;  
      for(int i = 1;  i <= q; i++){
            long long u,v,w; int t; 
            scanf("%d",&t);
            if(t == 2){
                 scanf("%lld%lld",&u,&v); 
                 u = u xor last; v = v xor last;
                 //cout << t <<' ' << u <<' ' << v << endl; 
                 if(u > v) swap(u,v); 
                 long long ans = query(u,v + 1);
                 printf("%lld\n",ans);
                 if(ans == -1) last = 1; 
                 else last = ans; 
            }
            else{
                  scanf("%lld%lld%lld",&u,&v,&w);
                  u = u xor last; v = v xor last; w = w xor last;
                  if(u > v) swap(u,v); 
                 // cout << t <<' ' << u <<' ' << v << ' ' << w << endl; 
                  unite(u,v + 1,w); 
            }
      }
      return 0; 
}
