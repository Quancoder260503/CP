#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=5e5+1;
const long long bignum = 1e18;
int n,x,k,i,j,w,m;
int movex[4]={0,0,1,-1};
int movey[4]={-1,1,0,0};
map<long long,long long>dpx[sz];
long long dp[sz];
map<long long,long long>col[sz];
map<long long,vector<pair<pair<int,int>,long long>>>adj[sz];
void dijsktra(int src){
     using T = pair<long long,pair<int,int>>;
     priority_queue<T,vector<T>,greater<T>>pq; 
     pq.push({0,{src,0}});
     for(int i = 1; i <= n; i++) dp[i] = bignum;
     dp[src] = 0;
     while(pq.size()){
            long long x; pair<int,int>v;
            tie(x,v) = pq.top(); pq.pop();
            if(v.second){
                if(dpx[v.first][v.second] != x) continue;
                for(auto c : adj[v.first][v.second]){
                         long long cost = x + col[v.first][v.second] - c.second;
                         if(cost < dp[c.first.first]){
                              dp[c.first.first] = cost ;
                              pq.push({dp[c.first.first],{c.first.first,0}});
                         }
                   }
            }
            else{
               if(dp[v.first] != x ) continue;
               for(auto it: adj[v.first]){
                   for(auto cur: it.second){
                       int des = cur.first.first;
                       int color = cur.first.second;
                       if(dp[des] > dp[v.first] + cur.second){
                            dp[des] = dp[v.first] + cur.second;
                            pq.push({dp[des],{des,0}});
                       }
                       if(dp[des] > dp[v.first]+ col[v.first][color] - cur.second){
                            dp[des] = dp[v.first] + col[v.first][color]- cur.second;
                            pq.push({dp[des],{des,0}});
                       }
                       long long val = dp[v.first];
                       if(!dpx[des].count(color) or dpx[des][color] > val){
                            dpx[des][color] = val;
                            pq.push({dpx[des][color],{des,color}});
                       }  
                   }
                }
          }
     }
}
int main(){
      cin>>n>>m;
      for(int i = 1; i <= m; i++){
           long long u,v,c,p; cin>>u>>v>>c>>p;
           adj[u][c].push_back({{v,c},p});
           adj[v][c].push_back({{u,c},p});
           col[u][c]+=p; 
           col[v][c]+=p;
      }
      dijsktra(1);
      if(dp[n] != bignum) cout<<dp[n]<<endl;
      else cout<<-1<<endl;
}
