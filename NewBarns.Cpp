#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e5 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q,x;
long long dp[N + 1]; 
int up[17][N + 1]; 
int fa[N + 1];
pair<int,int>cur[N + 1]; 
int lca(int a,int b){
     if(dp[a] < dp[b]) swap(a,b);
     int d = dp[a] - dp[b];
     for(int i = 0; i < 17; i++){
         if(d & (1 << i)) a = up[i][a]; 
     }
     if(a == b) return a; 
     for(int i = 16; i >= 0; i--){
         int ta = up[i][a]; int tb = up[i][b];
         if(ta != tb){
              a = ta;
              b = tb; 
         }
     }
     return up[0][a]; 
}
int calc_dis(int a,int b){
    return dp[a] + dp[b] - 2 * dp[lca(a,b)];
}
int main(){
     scanf("%d",&n); 
     int v = 0; 
     for(int i = 1; i <= n; i++){
           char c; int x; cin>>c>>x;
           if(c == 'B'){
               if(x == -1){
                    v++; 
                    cur[v].first = cur[v].second = v;
                    fa[v] = v; 
                    continue; 
               }           
               fa[++v] = fa[x];
               dp[v] = dp[up[0][v] = x] + 1;
               for(int j = 1; j < 17; j++){
                   up[j][v] = up[j - 1][up[j - 1][v]]; 
               } 
               int dis = calc_dis(cur[fa[v]].first,cur[fa[v]].second); 
               int dis0 = calc_dis(v,cur[fa[v]].first);
               int dis1 = calc_dis(v,cur[fa[v]].second); 
            ////   cout<<dis<<' '<<dis0<<' '<<dis1<<' '<<v<<' '<<cur[fa[v]].second<<endl; 
               if(dis0 > dis) cur[fa[v]].second = v; 
               else if(dis1 > dis) cur[fa[v]].first = v;
          }
          else{          
                int ans0 = calc_dis(x,cur[fa[x]].second);
                int ans1 = calc_dis(x,cur[fa[x]].first);
                printf("%d \n", max(ans0,ans1)); 
          }
     }
     return 0; 
}
