#include<bits/stdc++.h>
#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz=2e5+1;
bool on_stack[sz];
bool on_stack1[sz];
vector<ll>c[sz];
char ch[sz];
ll sub_size[sz];
int n;
int day=0;
void dfs(int node,int p){
    int opt=0;
    int z=1;
    sub_size[node]=1;
    for (int u:c[node]){
        if (u==p) continue;
        dfs(u,node);
        opt=opt+1;
        sub_size[node]+=sub_size[u];
    } while (z<opt+1){
         z=z*2;
         day+=1;
    }
}
int main(){
   cin>>n;
    for (int i=0;i<n-1;i++){
        int u,v;
        cin>>u>>v;
        c[v].push_back(u);
        c[u].push_back(v);
  }  dfs(1,0);
    cout <<sub_size[1]-1+day;
} 
  