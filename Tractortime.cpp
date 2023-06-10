#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=501;
const int sz1=sz*sz;
int n,res;
int sta;
int c[sz][sz];
int parent[sz1];
int compsize[sz1];
void init(int n){
	for (int i = 1; i <= n*n; i++){
		parent[i] = i;
		compsize[i] = 1;
	}
}
int find(int a){
	if (a == parent[a]) return a;
	return parent[a] = find(parent[a]);
}
void unite(int a, int b){
	int roota = find(a), rootb = find(b);
	if (roota == rootb) return ;
	if (compsize[roota] > compsize[rootb]) swap(roota, rootb);
	parent[roota] = rootb;
	compsize[rootb] += compsize[roota];
    res=max(res,compsize[rootb]);
}
bool ok(int k){
    init(n); res=0;
    for (int i=1;i<=n;i++){
        for(int j=1;j<=n;j++){
            if(j+1<=n and abs(c[i][j+1]-c[i][j])<=k) unite(j+(i-1)*n,j+1+(i-1)*n);
            if(i+1<=n and abs(c[i+1][j]-c[i][j])<=k) unite(j+(i-1)*n,j+i*n);
            if(i-1>=1 and abs(c[i-1][j]-c[i][j])<=k) unite(j+(i-1)*n,j+(i-2)*n);
            if(j-1>=1 and abs(c[i][j-1]-c[i][j])<=k) unite(j+(i-1)*n,j-1+(i-1)*n);
        }
    }
    if(res>=sta) return 1;
    else return 0;
}
int main(){
      cin>>n;
      sta=(n*n)/2;
      if(n%2==1) sta++;
      for(int i=1;i<=n;i++){
          for(int j=1;j<=n;j++){
              cin>>c[i][j];
          }
      }
      int high=1e7;
      int low=1;
      while(high>low){
          int mid=low+(high-low)/2;
          if(ok(mid)) high=mid;
          else low=mid+1;
      }
     cout<<low<<endl;
}