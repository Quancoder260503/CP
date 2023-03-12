#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
#define block 467
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = 2e5 + 10;
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,m,k,q,x;
vector<pii>adj[N + 1];
vector<pair<string,pii>>query; 
int timer = 1;
int in[N + 1],out[N + 1];
long long dp[N + 1]; 
long long blk[N + 1];
long long to[N + 1]; 
template<class T> struct Trie {
    struct Node {
        Node *c[2];
    };
    Node *root = new Node(); 
    void insert(int x){
      Node *cur = root;
      for(int i = 30; i >= 0; i--){
        if(x&(1<<i)){
            if(!cur->c[1])  cur->c[1] = new Node();
            cur = cur->c[1];
        } else {
            if(!cur->c[0])  cur->c[0] = new Node();
            cur = cur->c[0];
           }
       }
   } 
   long long query(int x){
      long long res = 0;
      Node *cur = root;
      for(int i = 30; i >= 0; i--){
         if(x&(1<<i)){
            if(cur->c[0]){
                res += (1<<i);
                cur = cur->c[0];
            } 
           else cur = cur->c[1];
        } else {
            if(cur->c[1]){
                res += (1<<i);
                cur = cur->c[1];
            } 
            else cur = cur->c[0];
        }
    }
    return res;
   }
};

Trie<long long>trie[block + 1];
void dfs(int u,int p){
      in[u] = timer++; 
      for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i].first;
            if(v == p) continue;   
            dfs(v,u); 
      } 
      out[u] = timer - 1;
}
int main(){
     scanf("%d",&q);
     int node = 1;
     for(int i = 1; i <= q; i++){
          string s; int u,w; 
          cin >> s >> u >> w;
          if(s == "Add"){
              adj[u].push_back({++node,w}); 
              dp[node] = dp[u] xor w; 
              query.push_back({s,{u,node}}); 
          }
          else{
              query.push_back({s,{u,w}}); 
          }
     }
     dfs(1,0); 
     for(int i = 1; i <= n; i++){
           blk[i] = i / block;
     }
     memset(to, -1, sizeof(to)); 
     to[1] = 0; 
     for(int i = 0; i < query.size(); i++){
            pii v = query[i].second;
            string s = query[i].first; 
            if(s == "Add"){ 
                  trie[blk[v.second]].insert(dp[v.second]); 
                  to[in[v.second]] = dp[v.second]; 
            }
            else{
                 int start = in[v.second];
                 int end = out[v.second];
                 if(start == end){
                      printf("%lld\n",(dp[v.first] xor dp[v.second]));
                      continue; 
                 }
                 if(blk[start] == blk[end]){
                       long long ans = 0; 
                       for(int j = start; j <= end; j++){         
                              if(to[j] < 0) continue;
                              ans = max(ans, dp[v.first] xor to[j]);
                 
                       }
                       printf("%lld\n",ans);
                 }
                 else{
                      long long ans = 0; 
                      for(int j = blk[start] + 1; j < blk[end]; j++){
                             ans = max(ans, trie[j].query(dp[v.first]));
                      }
                      for(int j = start; j / block == blk[start]; j++){
                             if(to[j] < 0) continue;
                             ans = max(ans, dp[v.first] xor to[j]); 
                      }
                      for(int j = end; j / block == blk[end]; j--){
                             if(to[j] < 0) continue; 
                             ans = max(ans, dp[v.first] xor to[j]); 
                      }
                      printf("%lld\n",ans); 
                 }
            }
     }
     return 0; 
}
//AC 
#include <bits/stdc++.h>
#pragma GCC target("popcnt")
using namespace std;
typedef long long ll;
#define block 467
typedef pair<int,int> pii;
const int sz = 4e5 + 1;
const int N = 2e5 + 10;
const int M = 1e6 + 10;
const int mod = (1 << 32);
long long n,m,k,q,x;
vector<pii>adj[N + 1];
vector<pair<string,pii>>queries; 
int timer = 0;
int in[N + 1],out[N + 1];
long long dp[N + 1]; 
long long blk[N + 1];
long long to[N + 1]; 
bool vis[N + 1];
struct Node {
        set<int>s;
        Node *c[2];
};
Node *root = new Node(); 
void insert(Node *node,int x,int bit,int id){
      node -> s.insert(id); 
      if(bit < 0) return;
      if(x & (1 << bit)){
           if(!node -> c[1]) node -> c[1] = new Node();
           insert(node -> c[1],x,bit - 1,id); 
      }
      else{
           if(!node -> c[0]) node -> c[0] = new Node();
           insert(node -> c[0],x,bit - 1,id); 
      }
} 
long long query(Node *node, int x,int bit, int from, int to){
       if(bit < 0) return 0;
       if(x & (1 << bit)){
            if(!node -> c[0]){
                 return query(node -> c[1],x,bit - 1,from,to); 
            }
            if(node -> c[0] -> s.lower_bound(from) == node -> c[0] -> s.upper_bound(to)){
                 return query(node -> c[1],x,bit - 1,from,to); 
            }
            return (1 << bit) + query(node -> c[0], x, bit - 1, from, to); 
       }
       else{
            if(!node -> c[1]){
                 return query(node -> c[0],x,bit - 1,from,to); 
            }
            if(node -> c[1] -> s.lower_bound(from) == node -> c[1] -> s.upper_bound(to)){
                 return query(node -> c[0],x,bit - 1,from,to); 
            }
            return (1 << bit) + query(node -> c[1], x, bit - 1, from, to); 
       }
     
}
void dfs(int u,int p){
      in[u] = ++timer; 
      for(int i = 0; i < adj[u].size(); i++){
            int v = adj[u][i].first;
            if(v == p) continue;   
            dfs(v,u); 
      } 
      out[u] = timer;
}
int main(){
     scanf("%d",&q);
     int node = 1;
     for(int i = 1; i <= q; i++){
          string s; int u,w; 
          cin >> s >> u >> w;
          if(s == "Add"){
              adj[u].push_back({++node,w}); 
              dp[node] = dp[u] xor w; 
              queries.push_back({s,{u,node}}); 
          }
          else{
              queries.push_back({s,{u,w}}); 
          }
     }
     dfs(1,0); 
     insert(root,0,30,in[1]);
     for(int i = 0; i < queries.size(); i++){
            pii v = queries[i].second;
            string s = queries[i].first;
            if(s == "Add"){
                insert(root,dp[v.second],30,in[v.second]);     
            }
            else{
                long long ans = query(root,dp[v.first],30,in[v.second],out[v.second]);
                printf("%lld\n",ans); 
            }
     }
     return 0; 
}
