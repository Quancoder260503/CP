#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int sz=2e5+1;
int n,m,q,s,t,k,r,ans;
int timer=0;
ll  a[sz];
ll  up[21][sz];
ll dp[21][sz];
ll pref[sz];
ll len(int x,int y){
    ll rs=0;
    for(int i=0;i<=20;i++){
        if((y>>i)&1){
            rs+=dp[i][x];
            x=up[i][x];
        }
    } return rs;
}
bool solve(int z){
     for(int i=0;i<n;i++){
          if(len(i,z)>=n) return 1;
     } return 0;
}
int main(){
    cin>>n>>k;
    int sx=0;
    for(int i=0;i<n;i++) cin>>a[i];
    for(int i=0,r=0;i<n;i++){
        while(sx+a[r%n]<=k and r<=2*n) sx+=a[r%n],r++;
        up[0][i]=r%n;
        dp[0][i]=r-i;
        sx-=a[i];
    }
    for(int i=1;i<=20;i++){
        for(int j=0;j<n;j++){
            up[i][j]=up[i-1][up[i-1][j]];
            dp[i][j]=dp[i-1][up[i-1][j]]+dp[i-1][j];
        }
    }  
      int high=n;
      int low=1;
      while(high>low){
          int mid=low+(high-low)/2;
          if(solve(mid)) high=mid;
          else low=mid+1;
      }
      cout<<low<<endl;
} 