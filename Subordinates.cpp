#include<bits/stdc++.h>
#include<vector>
#include<set>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
vector<ll>c[sz];
const int M=1e9+7;
vector<ll>depth(sz);
vector<ll>sub(sz);
void dfs(int node){
    sub[node]=1;
    for(int u:c[node]){
        depth[u]=depth[node]+1;
        dfs(u);
        sub[node]+=sub[u];
    }
}
int main(){
    int n;
    cin>>n;
    for (int i=2;i<=n;i++){
        int parent;cin>>parent;
        c[parent].push_back(i);
    }
    dfs(1);
    for (int i=1;i<=n;i++){
        cout <<sub[i]-1<<" ";
    }
}
       