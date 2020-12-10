# Codeforces Round #560 (Div. 3)前4题文字题解

# A

给你一个很大的数，一次操作可以把1变0，把0变1，问最少需要多少次操作才能使这个数膜上$10^y$的结果是$10^x$。

直接用字符串存。除了后$y$位，其他位全都不用管。

后$y$位就需要保证：只有倒数第$x$位为$1$，其他全为$0$。

# B

这道题甚至比A简单。

直接排序然后遍历，用一个变量储存现在是第几天，大于这个变量就加1。

我的代码最后输出答案的时候要减1，看看你们的需不需要。

# C

有思维难度。这道题是贪心的。

把整个字符读下来，然后遍历字符，维护答案字符。

如果当前答案字符长度为奇数，则需要满足跟最后一个字符不相同才能加入。

如果为偶数，直接加入。

最后长度可能是奇数，如果是奇数，把最后一个弹出去即可。

代码不用给了。很清晰了。

# D

题目意思是给你几乎所有的因数，除了1和这个数本身，然后让你这个数到底是多少。

这道题我讲讲我自己的做法。

首先我们注意到：因数应该是一对一对的，但如果是完全平方数的话就会少一个。

显然，当$n$为奇数时答案就**应该**是完全平方数。此时我们把答案对应的因子找出，再次添加使凑成一对，再排个序，方便下面操作。

显然，左右两边其实是对应的一对因数，正常情况下所有配对的因数相乘应该是同一个数，**即答案**。

但是，这样还不够。考虑下面这个例子：

```
1
4
```

给他凑一对，就是两个4，按照上面的依据，答案是16。

但是不是。因为1 4 16不是16的所有因数，还有2和8。

所以我们应该还要再来一轮检验，检验答案的**不去重**因数个数与题目是否对应。

其实这步检验非常简单：从$1$枚举到$\sqrt{ans}$，如果能整除就加2。如果计算出来的结果减2等于目前得到的所有因数个数（奇数时凑上的那个数也算），那么就正确。

给大家看看我的代码：

```cpp
#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int maxn = 305;
int n, T;
#define ll long long
std::vector<ll> a;
bool check(ll ans) {
	ll temp = sqrt(ans);
	ll res = 0;
	for(ll i = 1; i <= temp; i++) {
		if(ans % i == 0) {
			res += 2;
		}
	}
	//cout << "res is " << res << endl;
	if(res - 2 != a.size()) return false;
	return true;
}
int main() {
	cin >> T;
	while(T--) {
		a.clear();
		cin >> n;
		for(ll i = 1; i <= n; i++) {
			ll temp; cin >> temp;
			a.push_back(temp);
		}
		std::sort(a.begin(), a.end());
		if(n % 2) {
			ll temp = (n + 1) / 2 - 1;
			a.push_back(a[temp]);
		}
		std::sort(a.begin(), a.end());
		// print
		//for(auto it: a) cout << it << ' ';
		//cout << endl;
		
		ll len = a.size();
		ll temp = a[0] * a[len - 1];
		ll i = 1, j = len - 2;
		bool flag = false;
		while(i <= j) {
			if(a[i] * a[j] != temp) {
				flag = true;
				break;
			}
			i++, j--;
		}
		if(flag) {
			cout << -1 << endl; continue;
		}
		if(check(temp)) {
			cout << temp << endl;
		} else {
			cout << -1 << endl;
		}
	}
	return 0;
}
```

