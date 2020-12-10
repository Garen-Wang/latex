#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
#define ll long long
const int maxn = 105;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
int col[maxn][maxn];
int n, m;
struct Nodes {
    int x, y, color, dis;
    Nodes(int x, int y, int color, int dis): x(x), y(y), color(color), dis(dis){}
};
std::queue<Nodes> q;
int main() {
    cin >> n >> m;
    for(int i = 1; i <= m; i++) {
        int x, y, c; cin >> x >> y >> c;
        col[x][y] = c + 1;
    }
    q.push(Nodes(1, 1, col[1][1], 0));
    int cnt = 0;
    while(!q.empty()) {
        Nodes sb = q.front(); q.pop();
        if(sb.x == n && sb.y == n) {
            cout << sb.dis << endl;
            return 0;
        }
        if(++cnt == 1000000) {
            cout << -1 << endl;
            return 0;
        }
        for(int dir = 0; dir < 4; dir++) {
            int newx = sb.x + dx[dir], newy = sb.y + dy[dir];
            if(newx >= 1 && newx <= n && newy >= 1 && newy <= n) {
                if(col[sb.x][sb.y]) {// 现在没用膜法
                    if(col[newx][newy] == col[sb.x][sb.y]) {
                        q.push(Nodes(newx, newy, col[newx][newy], sb.dis));
                    } else {
                        if(col[newx][newy] == 0) {
                            q.push(Nodes(newx, newy, col[sb.x][sb.y], sb.dis + 2));
                        } else {
                            q.push(Nodes(newx, newy, col[newx][newy], sb.dis + 1));
                        }
                    }
                } else {// 现在用了膜法
                    if(col[newx][newy] == sb.color) {
                        q.push(Nodes(newx, newy, col[newx][newy], sb.dis));
                    } else {
                        if(col[newx][newy]) q.push(Nodes(newx, newy, col[newx][newy], sb.dis + 1));
                    }
                }
            }
        }
    }
    return 0;
}