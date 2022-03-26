#include <bits/stdc++.h>
using namespace std;

//https://www.acmicpc.net/status?user_id=mc_cari&problem_id=16995&from_mine=1

typedef long long ll;
typedef double db;

#define rep(i, j) for(int i = 0; i < j; i++)
#define repx(i, a, b) for(int i = a; i < b; i++)

db dist(db x1, db y1, db x2, db y2)
{
    return sqrt((x1 - x2)*(x1 - x2) + (y1 - y2)*(y1 - y2));
}
db area(db ab, db bc, db ca)
{
    db s = 0.5 * (ab + bc + ca);
    return sqrt(s) * sqrt(s - ab) * sqrt(s - bc) * sqrt(s - ca);
}



int main() {
    ll n, k;
    db x, y;
    vector<pair<db, db>>q;
    cin >> n >> k;


    for(int i = 0; i < n; i++)
    {
        cin >> x >> y;
        q.push_back({x, y});

    }
    db res = 0;

    for(int i = 0; i < 1; i++)
    {
        db x1 = q[i].first, y1 = q[i].second, x2, y2, ac = 0, x3, y3;
        for(int j = 2; j <= n - 1; j++)
        {
            x2 = q[(i + j) % n].first, y2 = q[(i + j) % n].second;
            x3 = q[(i + j - 1) % n].first, y3 = q[(i + j - 1) % n].second;

            ac += area(dist(x1, y1, x2, y2), dist(x2, y2, x3, y3), dist(x3, y3, x1, y1));
            res = ac;

        }
    }

    for(int i = 0; i < n; i++)
    {
        db x1 = q[i].first, y1 = q[i].second, x2, y2, ac = 0, x3, y3, mul = 1.0*k*(k-1)/(n*(n-1));
		
		mul *= 1.0*(n-2 - k + 2) / (n-2);
		
        for(int j = 2; j <= n - 2; j++)
        {
            x2 = q[(i + j) % n].first, y2 = q[(i + j) % n].second;
            x3 = q[(i + j - 1) % n].first, y3 = q[(i + j - 1) % n].second;
            ac += area(dist(x1, y1, x2, y2), dist(x2, y2, x3, y3), dist(x3, y3, x1, y1));

            db r = n - (j + 1);

            res -= ac * mul;

            mul *= 1.0*(r - k + 2) / r;

        }
    }

    cout <<fixed<<setprecision(8)<< res << endl;
}
