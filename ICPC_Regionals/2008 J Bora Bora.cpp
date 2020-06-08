#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef vector<ll> vl;
typedef pair<ll,ll> pll;
typedef double db;
#define INF 1e9
#define EPS 1e-9
#define ALL(x) x.begin() , x.end()
#define ALLR(x) x.rbegin() , x.rend()
#define UNIQUE(c) (c).resize(unique(ALL(c)) - (c).begin())
#define PI acos(-1.0) 
double DEG_to_RAD(double d) { return d*PI / 180.0; }
double RAD_to_DEG(double r) { return r*180.0 / PI; }
 
 //https://www.urionlinejudge.com.br/judge/es/problems/view/1439
 
int32_t main() {

    ios_base::sync_with_stdio(0);
    cin.tie();
    int P, M, N;
    map<char, int>chars;
    chars['C'] = 1;
    chars['D'] = 2;
    chars['H'] = 3;
    chars['S'] = 4;
    while(cin >> P >> M >> N && (P + M + N))
    {
      int x, jugador = 0, num = 0;
      multiset<pll > m;
      vector<multiset<pll > >mazos(P, m);
      stack<pll>s;
      queue<pll>p;
      for(int i = 0; i < N; i++)
      {
        char ch;
        cin >> x >> ch;
        if (jugador <  P)
        {
          mazos[jugador].insert({-x, -chars[ch]});
        }
        else
        {
          p.push({-x, -chars[ch]});
        }
        num++;
        if(num == M)
        {
          num = 0;
          jugador++;
        }
        
      }
      ll dir = 1, pos = 0;
      pll c1 = p.front();
      p.pop();
      s.push(c1);
      if (c1.first == -12)dir = -1;
      if (c1.first == -1)
      {
        mazos[pos].insert(p.front());
        p.pop();
        pos++;
      }
      if (c1.first == -7)
      {
        mazos[pos].insert(p.front());
        p.pop();
        mazos[pos].insert(p.front());
        p.pop();
        pos++;
      }
      if (c1.first == -11)
      {
        pos++;
      }
      int win = -1;
      while (win == -1)
      {
        bool jugada = false;
        ll aux = pos;
        for (auto it : mazos[pos])
        {
          if(it.first == s.top().first || it.second == s.top().second)
          {
            jugada = 1;
            s.push(it);
            if (it.first == -12)dir = -dir;
            if (it.first == -1)
            {
              pos = (pos + dir + P)%P;
              mazos[pos].insert(p.front());
              p.pop();
            }
            if (it.first == -7)
            {
              pos = (pos + dir + P)%P;
              mazos[pos].insert(p.front());
              p.pop();
              mazos[pos].insert(p.front());
              p.pop();
            }
            if (it.first == -11)
            {
              pos = (pos + dir + P)%P;
            }
            mazos[aux].erase(mazos[aux].find(it));
            break;
          }
        }
        if (!jugada)
        {
          c1 = p.front();
          p.pop();
          if(c1.first == s.top().first || c1.second == s.top().second)
          {
            s.push(c1);
            if (c1.first == -12)dir = -dir;
            if (c1.first == -1)
            {
              pos = (pos + dir + P)%P;
              mazos[pos].insert(p.front());
              p.pop();
            }
            if (c1.first == -7)
            {
              pos = (pos + dir + P)%P;
              mazos[pos].insert(p.front());
              p.pop();
              mazos[pos].insert(p.front());
              p.pop();
            }
            if (c1.first == -11)
            {
              pos = (pos + dir + P)%P;
            } 
          }
          else
          {
            mazos[pos].insert(c1);
          }
        }
        pos = (pos + dir + P)%P;
        if(mazos[aux].empty())win = aux + 1;
      }
      cout << win << "\n";
    }
 
  return 0;
}
