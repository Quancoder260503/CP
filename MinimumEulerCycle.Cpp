#include <bits/stdc++.h>
#include <iostream>
#include <algorithm>
#include <stack>
#include<vector>
using namespace std;
const int N = 5e5 + 1;
long long pf[N + 1];
int n;
long long pos(long long x){
    if(x > pf[n]) return 1;
    int p = lower_bound(pf, pf + n,x) - pf;
    long long dis = x - pf[p - 1];
    return  x & 1 ? p : dis / 2 + p;
    
}
void solve(){
    long long l,r;
    cin >> n >> l >> r;
    for(int i = 1; i <= n; i++) pf[i] = pf[i - 1] + 2 * (1ll) * (n - i);
    for(long long i = l; i <= r; i++){
        cout << pos(i) << ' ';
    }
    cout << '\n';
    return;
}
int main(){
    int t;
    cin >> t;
    for(int i = 0; i < t; i++){
        solve();
    }
}
