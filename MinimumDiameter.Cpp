#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 3e5 + 5;
const long long INF = 1e16 + 5;
long long n,m,k,q;
vector<int>adj[N + 1]; 
int main(){
    scanf("%d%d",&n,&k); 
    for(int i = 0; i < n - 1; i++){
         int u,v; scanf("%d%d",&u,&v);
         adj[u].push_back(v);
         adj[v].push_back(u); 
    }
    int cnt = 0; 
    for(int i = 1; i <= n; i++){
          if(adj[i].size() == 1) cnt++; 
    }
    long double ans = (long double) 2 * k / (long double) cnt;
    couy << setprecision(9) << ans << endl;  
    return 0; 
}
