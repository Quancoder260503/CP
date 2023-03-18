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
int d1[1005][1005];
int d2[1005][1005];
int x2,y2;
void bfs(vector<pair<int,int>>&a, int d[1005][1005]){
    queue<pair<int,int>>q;
    for (auto i:a){
        q.push(i);
        visited[i.first][i.second]=true;
    }
    while (!q.empty()){
        int x1=q.front().first;
        int y1=q.front().second;
        q.pop();
        if (x1==0 or x1==n-1 or y1==0 or y1==m-1){
            if (d[x1][y1]>0){
                x2=x1;
                y2=y1;
            }
        }
        for (int i=0;i<4;i++){
            int x=x1+dx[i];
            int y=y1+dy[i];
            if (x<0 or x>=n) continue;
            if (y<0 or y>=m) continue;
            if (c[x][y]!='#' and !visited[x][y]){
                visited[x][y]=1;
                d[x][y]=d[x1][y1]+1;
                q.push({x,y});
                parent[x][y]={x1,y1};
            } 
        }
    } 
}
void print (int corx,int cory ,int x1,int  y1){
        vector<pair<int,int>>res;
        res.push_back({corx,cory});
        res.push_back(parent[corx][cory]);
        while (res.back().first!=x1 and res.back().second!=y1){
            int u=res.back().first;
            int v=res.back().second;
            res.push_back(parent[u][v]);
        } while(res.back().second!=y1){
            int v=res.back().second;
            res.push_back(parent[res.back().first][v]);
        } 
        while(res.back().first!=x1){
            int u=res.back().first;
            res.push_back(parent[u][res.back().second]);
        } while(res.back().second!=y1){
            int v=res.back().second;
            res.push_back(parent[res.back().first][v]);
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
int main(){
    cin>>n>>m;
    int x1,y1;
    vector<pair<int,int>>mons;
    for (int i=0;i<n;i++){
        for(int j=0;j<m;j++){
            cin>>c[i][j];
            if (c[i][j]=='A'){
                x1=i;
                y1=j;
                c[i][j]='.';
            } if (c[i][j]=='M'){
                  mons.push_back({i,j});
                  c[i][j]='.';
            }
        }
    } bfs(mons,d1);
      for (int i=0;i<n;i++){
          for (int j=0;j<m;j++){
              visited[i][j]=0;
          }
      }
      vector<pair<int,int>>mons1;
      mons1.push_back({x1,y1});
      bfs(mons1,d2);
      int corx,cory;
      bool flag=false;
      bool flag2=false;
      for (int i=0;i<n;i++){
          if (d1[i][0]>0 or d1[i][m-1]>0) flag2=1;
          if (d1[i][0]>d2[i][0] and d1[i][0]>0){
              corx=i;
              cory=0;
              flag=true;
              break;
          } if (d1[i][m-1]>d2[i][m-1] and d1[i][m-1]>0){
              corx=i;
              cory=m-1;
              flag=true;
              break;
          }
     }      
    for (int i=0;i<m;i++){ 
              if (d1[n-1][i]>0 or d1[0][i]>0) flag2=1;
              if (d1[n-1][i]>d2[n-1][i] and d1[n-1][i]>0){
                corx=n-1;
                cory=i;
                flag=true;
                break;
             } if (d1[0][i]>d2[0][i] and d1[0][i]>0){
                cory=i;
                corx=0;
                flag=true;
                break;
            }   
    } 
    if (!flag){
          corx=x1;cory=y1;
          if (mons.size()==1 and !flag2){
              cout <<"YES"<<endl;
              print(x2,y2,x1,y1);
              exit(0);
          }
          if (corx==0 or cory==0 or corx==n-1 or cory==m-1){
               cout <<"YES"<<endl;
               cout <<0;
               exit(0);
            } else cout <<"NO";     
      }else {
         cout <<"YES"<<endl;
         print(corx,cory,x1,y1);
     }
}
