#include<iostream>
#include<vector>
#include<utility>
#include<algorithm>
#include<queue>
using namespace std;
typedef long long ll;
int n,m;
bool visited[1005][1005];
int dx[4]={-1,1,0,0};
int dy[4]={0,0,-1,1};
char c[1002][1002];
pair<ll,ll>parent[1002][1002];
int bfs(int sx,int sy,int x2,int y2){
    visited[sx][sy]=1;
    queue<pair<int,int>>q;
    q.push({sx,sy});
    while (!q.empty()){
        int x1=q.front().first;
        int y1=q.front().second;
        q.pop();
        for (int i=0;i<4;i++){
            int x=x1+dx[i];
            int y=y1+dy[i];
            if (x<0 or x>=n) continue;
            if (y<0 or y>=m) continue;
            if  (x==x2 and y==y2){
                parent[x][y]={x1,y1};
                return 1;
            }
            if (c[x][y]!='#' and !visited[x][y]){
                visited[x][y]=1;
                q.push({x,y});
                parent[x][y]={x1,y1};
            } 
          }
        } return 0;
     }
int main(){
    cin>>n>>m;
    int x1,x2,y1,y2;
    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>c[i][j];
            if (c[i][j]=='A'){
                x1=i;
                y1=j;
            } if (c[i][j]=='B'){
                x2=i;
                y2=j;
            }
        }
    }if (bfs(x1,y1,x2,y2)){
        cout<<"YES"<<endl;
        vector<pair<int,int>>res;
        res.push_back({x2,y2});
        res.push_back(parent[x2][y2]);
        while (res.back().first!=x1 and res.back().second!=y1){
            int u=res.back().first;
            int v=res.back().second;
            res.push_back(parent[u][v]);
        }
        while(res.back().second!=y1){
            int v=res.back().second;
            res.push_back(parent[res.back().first][v]);
        } 
        while(res.back().first!=x1){
            int u=res.back().first;
            res.push_back(parent[u][res.back().second]);
        } 
        cout <<res.size()-1<<endl;
        ll k=res.size();
             for (int i=k-1;i>0;i--){
            if (res[i].second-1==res[i-1].second){
                cout<<'L';
                continue;
            }
            else if (res[i].second+1==res[i-1].second){
                cout<<'R';
                continue;
            }
            if (res[i].first==1+res[i-1].first){
                cout<<'U';
                continue;
            } else if (res[i].first+1==res[i-1].first){
                cout<<'D';
            }
    }
}        
    else{
        cout <<"NO";
    }
}
