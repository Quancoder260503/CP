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
vector<ll>c[sz];
char ch[sz];
ll comp[sz];
#experience: we can divide node of the graph into connected component by their characteristics (G and H etc)
if two endpoints in different connected component or one of the endpoints 
have the same character of the farmers then the endpoint of such path satisfy farmer.
int n;
int num=0;
void dfs(int node){
    if (comp[node]>0) return;
    comp[node]=num;
    for (auto u:c[node]){
        if (ch[u]==ch[node]){
           dfs(u);
        }     
    }
}
int main(){
    int n,m;
    cin>>n>>m;
    for(int i=1;i<=n;i++){
           char s;cin>>s;
           ch[i]=s;
       } for ( int i=0;i<n-1;i++){
            int u,v;
            cin>>u>>v;
            c[u].push_back(v);
            c[v].push_back(u);
    }
    for (int i=1;i<=n;i++){
           if (comp[i]==0){
              num++;
              dfs(i);
         }     
    } for (int i=0;i<m;i++){
        int u,v; char d;
        cin>>u>>v>>d;
        if (ch[v]==d or comp[u]!=comp[v]) cout <<1;
        else cout <<0;
    }
} 