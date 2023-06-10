#include <bits/stdc++.h>
#include <iostream>
#include<queue>
#include<vector>
#include<utility>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n,m;
int ans=0;
int cnt;
vector<int>g[sz];
int f[sz];
int a[sz];
int d[sz];
bool p[sz];
int get(int x){
    if (f[x]<0) return x;
    else return get(f[x]);
}
int main(){
    cin>>n>>m;
    cnt=0;
    for (int i=0;i<m;i++){
        int u,v;
        cin>>u>>v;
        g[u].push_back(v);
        g[v].push_back(u);
    }  
    for(int i=1;i<=n;i++){
        cin>>a[i]; f[i]=i;
    } 
    for (int i=n;i>0;i--){
           int x=a[i];
           cnt++;
           for (auto v:g[x]){
                int y=v;
                if (!p[y]) continue;
                x=get(x),y=get(y);
                if (x==y) continue;
                f[x]=y;
                cnt--;
           } 
            d[i]=cnt;
            p[a[i]]=1;
    } 
     for (int i=1;i<=n;i++){
        if (d[i]==1) cout <<"YES"<<endl;
        else cout <<"NO"<<endl;
    }
}    