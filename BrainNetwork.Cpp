#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 5;
const int M = 1e6 + 5;
const int mod = (1 << 32); 
long long n,m,k,q,x;
long long dp[N + 1]; 
long long bit[N + 1];
int up[21][N + 1]; 
int lca(int a,int b){
     if(dp[a] < dp[b]) swap(a,b);
     int d = dp[a] - dp[b];
     for(int i = 0; i < 21; i++){
         if(d & (1 << i)) a = up[i][a]; 
     }
     if(a == b) return a; 
     for(int i = 20; i >= 0; i--){
         int ta = up[i][a]; int tb = up[i][b];
         if(ta != tb){
              a = ta;
              b = tb; 
         }
     }
     return up[0][a]; 
}
int main(){
     scanf("%d",&n);
     pair<int,int>cur;  
     int ans = 0; 
     cur.first = cur.second = 1;
     for(int i = 2; i <= n; i++){
           int x; scanf("%d",&x);
           up[0][i] = x;
           for(int j = 1; j < 21; j++){
                 up[j][i] = up[j - 1][up[j - 1][i]]; 
           } 
           dp[i] = dp[x] + 1; 
           // if the distance from the newly added node from 1 to 2 end points of the diameter is greater than diameter simply it's the new endpoint. 
           int dis0 = dp[i] + dp[cur.first] - 2 * dp[lca(i,cur.first)];
           int dis1 = dp[i] + dp[cur.second] - 2 * dp[lca(i,cur.second)]; 
           if(dis0 > ans){
                ans = dis0;
                cur.second = i; 
           }
           else if(dis1 > ans){
                ans = dis1; 
                cur.first = i;
           }
           printf("%d ",ans); 
     }
     return 0; 
}
