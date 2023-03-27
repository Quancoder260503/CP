#include <bits/stdc++.h>
#include <iostream> 
#include<vector>
#define blksz 500
using namespace std;
typedef long long ll;
const int sz = 4e5 + 1;
const int N = 1e6 + 10;
const long long INF = 1e7 + 5;
const int mod = 1e9 + 7;
long long n,m,k,q,p;
vector<int>adj[N + 1];
long long A[N + 1]; 
char s[N + 1]; 
long long B[N + 1]; 
long long a[N + 1];
long long b[N + 1]; 
int in[N + 1];
int out[N + 1]; 
int timer = 1;
bool _Line_Comp_State; 
struct Line {
	// k is slope, m is intercept, p is intersection point
	mutable long long k, m, p;
	bool operator<(const Line& o) const {
		return _Line_Comp_State ? p < o.p : k < o.k;
	}
};
 
struct LineContainer : multiset<Line> {
	long long div(long long a, long long b) { return a / b - ((a ^ b) < 0 && a % b); }
 
	bool isect(iterator x, iterator y) {
		if (y == end()) { 
			x->p = LLONG_MAX; 
			return false; 
		}
		if (x->k == y->k) {
			x->p = x->m > y->m ? LLONG_MAX : -LLONG_MAX;
		} else {
			x->p = div(y->m - x->m, x->k - y->k);
		}
		return x->p >= y->p;
	}
	void add(long long k, long long m) {
		auto z = insert({k, m, 0}), y = z++, x = y;
		while (isect(y, z)) {
			z = erase(z);
		}
		if (x != begin() && isect(--x, y)) {
			isect(x, y = erase(y));
		}
		while ((y = x) != begin() && (--x)->p >= y->p) {
			isect(x, erase(y));
		}
	}
 
	long long query(long long x) {
		assert(!empty());
		_Line_Comp_State = 1; 
		auto l = *lower_bound({0, 0, x}); 
		_Line_Comp_State = 0;
		return l.k * x + l.m;
	}
} opt[blksz + 1];
long long addblock[blksz + 1]; 
int block[N + 1]; 
void dfs(int u,int p){
     A[u] += a[u]; B[u] += b[u];
     in[u] = timer++; 
     opt[block[in[u]]].add(-B[u],- (long long) A[u] * B[u]);
     for(int i = 0; i < adj[u].size(); i++){
          int v = adj[u][i];
          if(v == p) continue; 
          A[v] += A[u];
          B[v] += B[u];
          dfs(v,u); 
     }
     out[u] = timer - 1;
}
int main(){
      scanf("%d%d",&n,&q);
      for(int i = 2; i <= n; i++){
           int u; scanf("%d",&u); 
           adj[u].push_back(i); 
      }
      for(int i = 1; i <= n; i++) block[i] = i / blksz;
      for(int i = 1; i <= n; i++) scanf("%lld",a + i);
      for(int i = 1; i <= n; i++) scanf("%lld",b + i); 
      dfs(1,0); 
      for(int i = 1; i <= q; i++){
           int type; scanf("%d",&type);
           if(type == 2){
                int pos; scanf("%d",&pos); 
                int start = in[pos];
                int end = out[pos];
                long long ans = -INF;
                if(block[start] == block[end]){
                  for(int j = start; j <= end; j++){
                    ans = max(ans, (1ll) * addblock[block[j]] * B[j] + (1ll) * A[j] * B[j]); 
                  }
                }
                else{ 
                  for(int j = start; block[j] == block[start]; j++){
                    ans = max(ans, (1ll) * addblock[block[j]] * B[j] + (1ll) * A[j] * B[j]);  
                  }
                  for(int j = end; block[j] == block[end]; j--){
                    ans = max(ans, (1ll) * addblock[block[j]] * B[j] + (1ll) * A[j] * B[j]);   
                  }
                  for(int j = block[start] + 1; j < block[end]; j++){
                     ans = max(ans, (1ll) * opt[j].query(addblock[j])); 
                  }
               }
           }
           else{
                int pos; long long val;  scanf("%d%lld",&pos,&val); 
                int start = in[pos];
                int end = out[pos];
                if(block[start] == block[end]){
                  for(int j = start; j <= end; j++){
                      A[j] += val;
                      opt[block[j]].add(-B[j], -(1ll) * A[j] * B[j]); 
                  }
                }
                else{ 
                  for(int j = start; block[j] == block[start]; j++){
                      A[j] += val; 
                      opt[block[j]].add(-B[j], -(1ll) * A[j] * B[j]); 
                  }
                  for(int j = end; block[j] == block[end]; j--){
                      A[j] += val; 
                      opt[block[j]].add(-B[j], -(1ll) * A[j] * B[j]); 
                  }
                  for(int j = block[start] + 1; j < block[end]; j++){
                      addblock[j] += val; 
                  }
               }   
           }
      }
      return 0;
}
