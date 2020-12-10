#include<bits/stdc++.h>
const int maxn = 105;
const int dx[] = {0, 0, -1, 1};
const int dy[] = {-1, 1, 0, 0};
int dist[maxn][maxn][2];
bool vis[maxn][maxn][2];
int G[maxn][maxn];
struct Nodes {
	int x, y, col;
	Nodes(int x, int y, int col): x(x), y(y), col(col){}
};
std::queue<Nodes> q;
int n, m;

void add(int x, int y, int col, int res) {
	if(res < dist[x][y][col]) {
		dist[x][y][col] = res;
		if(!vis[x][y][col]) {
			q.push(Nodes(x, y, col));
			vis[x][y][col] = true;
		}
	}
}
int main() {
	scanf("%d %d", &n, &m);
	memset(G, -1, sizeof G);
	while(m--) {
		int x, y, c; scanf("%d %d %d", &x, &y, &c);
		G[x][y] = c;
	}
	memset(dist, 0x3f, sizeof dist);
	dist[1][1][G[1][1]] = 0;
	q.push(Nodes(1, 1, G[1][1])); vis[1][1][G[1][1]] = true;
	while(!q.empty()) {
		Nodes sb = q.front(); q.pop();
		for(int i = 0; i < 4; i++) {
			int newx = sb.x + dx[i], newy = sb.y + dy[i];
			if(newx >= 1 && newx <= n && newy >= 1 && newy <= n) {
				if(G[newx][newy] == sb.col) {
					add(newx, newy, G[newx][newy], dist[sb.x][sb.y][sb.col]);
				} else if(G[newx][newy] != -1) {
					add(newx, newy, G[newx][newy], dist[sb.x][sb.y][sb.col] + 1);
				} else {
					if(G[sb.x][sb.y] != sb.col) continue;
					add(newx, newy, sb.col, dist[sb.x][sb.y][sb.col] + 2);
				}
			}
		}
	}
	int ans;
	if(G[n][n] == -1) ans = std::min(dist[n][n][0], dist[n][n][1]);
	else ans = dist[n][n][G[n][n]];
	if(ans == 0x3f3f3f3f) printf("-1\n");
	else printf("%d\n", ans);
	return 0;
}
