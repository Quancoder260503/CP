#include<iostream>
#include<vector>
#include<queue>
#include<utility>
using namespace std;
typedef long long ll;
bool visited[100005];
vector<ll>g[100005];
ll check[100005];
bool revisit=0;
void dfs(int node,bool teamA){
    visited[node]=true;
    check[node]=teamA;
    for (int u:g[node]){
         if (!visited[u]){
             check[u]=!teamA;
             dfs(u,!teamA);
         } else{
             if (check[u]==teamA){
                 revisit=1;
                 break;
             }
         }
    }
}
void countteam(int n){
    bool k=true;
    for (int i=1;i<=n;i++){
        if (!visited[i]){
            dfs(i,k);
        }
    }
} 
int main() {
    int n,m;
    cin>>n>>m;
    int u,v;
    for (int i=0;i<m;i++){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    } countteam(n);
    if (!revisit){
         for (int i=1;i<=n;i++){
           cout << check[i]+1<< " ";
    } 
    }    else{
           cout<<"IMPOSSIBLE"<<endl;
        }
    }   