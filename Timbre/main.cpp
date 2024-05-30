#include<fstream>
#include<algorithm>
#include<set>
using namespace std;
ifstream fin("timbre.in");
ofstream fout("timbre.out");
const int NMAX = 10005;
int n, m, k, lim, cost;
multiset<int> mul;
pair<int,int> v[NMAX];
int main()
{
    fin >> n >> m >> k;
    for (int i=1;i<=m;i++){
        fin >> lim >> cost;
        v[i] = {lim, cost};
    }
    sort(v+1, v+m+1);
    int i = m;
    int ans = 0;
    while(n > 0){
        while(i>=1 && v[i].first >= n)
            mul.insert(v[i--].second);

        ans += *mul.begin();
        mul.erase(mul.begin());
        n -= k;
    }
    fout << ans << '\n';
    return 0;
}
