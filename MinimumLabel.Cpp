#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = (1 << 19);
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,l,r,ans,x,m;
vector<int>adj[N + 1];
vector<int>res;
bool vis[N + 1];
long long a[N + 1]; 
long long b[N + 1]; 
long long bit[N + 1];
int deg[N + 1];
int re[N + 1]; 
int main(){
     scanf("%d%d",&n,&m);
     for(int i = 0; i < m; i++){
           int u,v; scanf("%d%d",&u,&v);
           adj[v].push_back(u);
           deg[u]++;
     }
     priority_queue<int>pq;
     for(int i = 1; i <= n; i++) if(!deg[i]) pq.push(i);
     while(pq.size()){
            int ver = pq.top();
            res.push_back(ver); 
            pq.pop();
            for(int i = 0; i < adj[ver].size(); i++){
                  int v = adj[ver][i];
                  deg[v]--;
                  if(!deg[v]) pq.push(v); 
            }
     }
     for(int i = 0; i < res.size(); i++){
          re[res[i]] = n - i;
     }
     //  cout << re[1] << endl; 
     for(int i = 1; i <= n; i++) printf("%d ",re[i]); 
     return 0; 
}
