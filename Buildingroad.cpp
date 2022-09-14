#include<iostream>
#include<vector>
#include<algorithm>
using namespace std;
typedef long long ll;
const int k=1e9+7;
bool visited[10000000];
vector<int>g[1000000];
int rep[100000];
void dfs(int node){
    visited[node]=true;
    for (int u: g[node])
          if (!visited[u])
              dfs(u);      
}
int components(int n){
    int count=0;
    for(int i=1;i<=n;i++){
        if (!visited[i]){
            rep[count++]=i;
            dfs(i);
        }
    } return count;
}
int main(){
     int n,m;
    cin>>n>>m;
    int u,v;
    for (int i=0;i<m;i++){
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    } ll ans=components(n);
    cout <<ans-1<<endl;
    for(int i=1;i<ans;i++){
        cout <<rep[i-1]<<" "<<rep[i]<<endl;
    }
}
