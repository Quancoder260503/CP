#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
typedef long double ld;
const int sz1=5e6+1;
const int sz=2e5+1;
int n,q;
bool yes=0;
ll res=0;
int dp[sz];
int up[31][sz];
vector<int>adj[sz];
const int mod=1e9+7;
int jump(int x, int d){
    for(int i=0;i<=30;i++){
        if((d>>i)&1) x=up[i][x];
    } return x;
}
int main(){   
    cin>>n>>q;
    for(int i=1;i<=n;i++){
         ll a;cin>>a;
         up[0][i]=a;
    } 
       for(int i=1;i<=30;i++){
         for(int j=1;j<=n;j++){
            up[i][j]=up[i-1][up[i-1][j]];
        }
    }
    for(int i=0;i<q;i++){
        ll u,v;cin>>u>>v;
        cout<<jump(u,v)<<endl;
    } 
}    