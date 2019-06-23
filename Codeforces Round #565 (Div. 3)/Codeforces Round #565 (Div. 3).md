# Codeforces Round #565 (Div. 3)

# A

直接照题意写即可。

显然1操作优于2操作，2操作也优于3操作。

如果同时不是2、3、5的倍数就无法继续操作，这个时候就无解了。

# B

显然$a_i$到底多大我们并不关心，我们只关心它跟3差多少。可以通过取膜体现。

所以接下来，问题转化为一堆0、一堆1和一堆2如何合并成最多个3的倍数。

- 0直接就是3的倍数，不需要合并，不然答案变劣。
- 接下来最优的就是一个1和一个2合并，二合一。
- 之后会把1或2用光，剩下的能合并就合并即可。两种都是三合一。

# C

这里有两种解法，一种是$O(n\log n)$，一种是$O(n)$。

### 法一

显然我们暴力从左到右遍历这些数，暴力找到这个子序列，最后找不到的就要被删。

但是用数组删除数字很麻烦啊！

用`std::set`能够暴力地解决这个问题。

用6个`std::set`来存这些数字的下标，然后一直在下一个`set`中找到比现在下标更大的下标，如果能成功在第6个`set`找到，就找到一组了。

最多所有数都被删除，也不会大于$O(n\log  n)$。代码：

```cpp

```

### 法二

第二种方法一次遍历就完事了。

边读入边维护，用$b[1]$到$b[6]$维护当前出现了多少个。

显然当$b[1]>b[2]$时，后面多的那些是要被删的。$b[i+1]>b[i]$的情况也同理。

之后看看最多能够匹配多少对，$b[1]$到$b[6]$中不能匹配的也删了就完事了。

~~讲道理我没有想到，我太菜了~~

代码：

```cpp
// code from xy
#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
int n,a[500001],b[7],min=0x3f3f3f3f,ans;

int main()
{
    cin>>n;
    for(int i=1;i<=n;i++)
    {
        cin>>a[i];
        if(a[i]==4) b[1]++;
        if(a[i]==8)
        {
            if(b[1]==b[2]) ans++;
            else b[2]++;
        }
        if(a[i]==15)
        {
            if(b[3]==b[2]) ans++;
            else b[3]++;
        }
        if(a[i]==16)
        {
            if(b[4]==b[3]) ans++;
            else b[4]++;
        }
        if(a[i]==23)
        {
            if(b[5]==b[4]) ans++;
            else b[5]++;
        }
        if(a[i]==42)
        {
            if(b[6]==b[5]) ans++;
            else b[6]++;
        }
    }
    for(int i=1;i<=6;i++) min=std::min(min,b[i]);
    for(int i=1;i<=6;i++) ans+=(b[i]-min);
    cout<<ans;
    return 0;
}
```

# D

前置技能：线性筛。

可以发现$a$中的一个质数会导致多一个更大的质数，而一个合数会导致多一个更小的质数或合数。

我们先把$b$中的数按质数和合数分类，然后顺便排个序。

如何排序？质数从小到大排，合数从大到小排。原因就在上面。

然后先从大到小处理合数，找到了一个合数就意味着它的次大因子要被删除。

之后再从小到大处理质数，找到了一个质数$a$就意味着第$a$个质数要被删除。

重点来了：如何维护这种删除操作？~~我就卡在这里了~~

可以使用一个`std::map`，要删除的数字就打上即可，而如果遍历到的数字正是要被删除的，就抵消掉一个标记，然后转换到下一个数字。

如何求一个数的次大因子？可以在线性筛的时候顺便求出一个数的最小素因子，除掉这个数就是次大因子了。~~学到了~~

~~我本来想用`std::set`再水一水，没想到T了~~

代码：

```cpp
#include<bits/stdc++.h>
using std::cin;
using std::cout;
using std::endl;
const int maxn = 200005;
bool notprime[2750132];
int prime[maxn], tot;
int minv[2750132];
int n;
std::map<int,int> mmp;
std::vector<int> a, b;
void init() {
    notprime[1] = true;
    for(int i = 2; i <= 2750131; i++) {
        if(!notprime[i]) {
            prime[++tot] = i; minv[i] = i;
        }
        for(int j = 1; j <= tot && i * prime[j] <= 2750131; j++) {
            notprime[i * prime[j]] = true;
            minv[i * prime[j]] = std::min(minv[i], prime[j]);
            if(i % prime[j] == 0) break;
        }
    }
}
bool cmp(int A, int B) {
    return A > B;
}
int main() {
    init();
    cin >> n;
    for(int i = 1, temp; i <= n * 2; i++) {
        cin >> temp;
        if(!notprime[temp]) a.push_back(temp);
        else b.push_back(temp);
    }
    std::sort(a.begin(), a.end());
    std::sort(b.begin(), b.end(), cmp);
    for(auto x: b) {
        if(mmp[x]) mmp[x]--;
        else {
            cout << x << ' ';
            mmp[x / minv[x]]++;
        }
    }
    for(auto x: a) {
        if(mmp[x]) mmp[x]--;
        else {
            cout << x << ' ';
            mmp[prime[x]]++;
        }
    }
    cout << endl;
    return 0;
    
}
```

# E

Div.3 的sb图论题。

有手就能写bfs跑一个01染色，找到最少的染色方法即可。显然不会超过$\lfloor \frac{n}{2} \rfloor$。

代码太简单就不给了。

然后有一个奇怪的地方：$t ,n,m\leq 2 \times 10^5$，而bfs居然能过？！

实现的时候注意一点：因为$t \leq 2 \times 10^5$，所以千万不要写`memset`！！！不然你会哭的。





