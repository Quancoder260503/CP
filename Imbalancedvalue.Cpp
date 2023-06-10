#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
using namespace std;
typedef long long ll;
const int sz=4e5+1;
const int N =1e6 + 100;
const int mod = 1e9 + 7;
const int INF =1e17+1;
bool prime[sz];
long long pw[sz];
long long n,m,k,t,p,ans;
long long fa[N];
long long a[N];
long long compsz[N];
vector<int>adj[N];
vector<pair<int,int>>val;
int trs[N];
bool vis[N];
void init(int n){
     for(int i = 1; i <= n; i++){
          fa[i] = i;
          compsz[i] = 1;
     }
}
int find(int x){
     if(x == fa[x]) return x; 
     else return fa[x] = find(fa[x]);
}
int main(){
       scanf("%lld",&n);
       for(int i = 1; i <= n; i++){
            scanf("%d",&a[i]);
            val.push_back({a[i],i});
       }
       for(int i = 1; i < n; i++){
             int u,v;  scanf("%d%d",&u,&v);
             adj[u].push_back(v);
             adj[v].push_back(u);
       }
       init(n);
       sort(val.begin(),val.end());
       for(int i = 0; i < val.size(); i++){
             int u = val[i].second;
             for(int i = 0; i < adj[u].size();i++){
                   int v = adj[u][i];
                   if(a[u] < a[v]) continue;
                   if(a[u] == a[v] and u < v) continue;
                   int rootu = find(u); int rootv = find(v);
                   ans = ans + (1ll)* a[rootu] * compsz[rootu] * compsz[rootv];
                   fa[rootv] = rootu; compsz[rootu] += compsz[rootv];
             }
       }
       reverse(val.begin(),val.end()); 
       init(n);
       for(int i = 0; i < val.size(); i++){
             int u = val[i].second;
             for(int i = 0; i < adj[u].size();i++){
                   int v = adj[u][i];
                   if(a[u] > a[v]) continue;
                   if(a[u] == a[v] and u < v) continue;
                   int rootu = find(u); int rootv = find(v);
                   ans = ans - (1ll) * a[rootu] * compsz[rootu] * compsz[rootv];
                   fa[rootv] = rootu; compsz[rootu] += compsz[rootv];
             }
       }
       cout<<ans<<endl;
} 
