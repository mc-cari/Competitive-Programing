#include "../Header.cpp"

db DEG_to_RAD(db d) { return d*PI / 180.0; }

db RAD_to_DEG(db r) { return r*180.0 / PI; }

struct point { db x, y;   
    point() { x = y = 0.0; }                      
    point(db _x, db _y) : x(_x), y(_y) {}        
    bool operator <(const point& p) const { return (x < p.x ? true : (x == p.x && y < p.y)); }
    bool operator == (const point& p) const { return abs(p.x - x) < EPS && abs(p.y - y) < EPS; }
    point operator + (const point& p) const { return point(x + p.x, y + p.y); }
    point operator - (const point& p) const { return point(x - p.x, y - p.y); }
    point operator * (db p) const { return point(x * p, y * p); }
    point operator / (db p) const { return point(x / p, y / p); }
    db operator^(const point &p) const {return x * p.y - y * p.x; }
    db operator*(const point &p) const {return x * p.x + y * p.y; }
    db norm_sq() const{ return x*x + y*y; }
    point rot(){ return point(-y, x); }
    
    // by angles but with cross
    bool half() const { return y > 0 || (y == 0 && x > 0); }
    bool operator<(const point &p) const
    {
        int h1 = half(), h2 = p.half();
        return h1 != h2 ? h1 > h2 : ((*this) ^ p) > 0;
    }

    db ang()
    {
        double a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }

  };


db dist(point& p1, point& p2) {                
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 
db dist_sq(point p1, point p2) {
  return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }


// returns the perimeter, which is the sum of Euclidian distances
// of consecutive line segments (polygon edges)
db perimeter(vector<point> &P) {
  db result = 0.0;
  for (ll i = 0; i < (ll)P.size()-1; i++)  // remember that P[0] = P[n-1]
    result += dist(P[i], P[i+1]);
  return result; }

// returns the area
db area(const vector<point> &P) {
  db result = 0.0;
  for (ll i = 0; i < (ll)P.size()-1; i++)             // Shoelace formula
    result += P[i]^P[i+1]; // if all points are ll
  return fabs(result)/2.0; }     // result can be ll(eger) until last step

db seg_integrate(point& a, point& b, db t1, db t2)
{
  // area
  point p1 = a + (b-a) * t1;
  point p2 = a + (b-a) * t2;
  return (p1^p2) / 2.0;
}

db param(point p1, point p2, point a)
{
  if(p1.x != p2.x)
  {
    db sgn = 1;
    if(p1.x > p2.x)sgn = -1;
    return (a.x - p1.x) / abs(p2.x - p1.x) * sgn;
  }
  db sgn = 1;
  if(p1.y > p2.y)sgn = -1;
  return (a.y - p1.y) / abs(p2.y - p1.y) * sgn;
}

// note: to accept collinear points, we have to change the `> 0'
// returns true if point r is on the left side of line pq
bool ccw(point p, point q, point r) {
  return ((q - p)^(r - p)) > 0; }

int orientation(point p, point q, point r) {
    ll tmp = ((q - p)^(r - p));
    return tmp < 0 ? -1 : tmp == 0 ? 0 : 1; // sign
}
/*bool do_rectangles_intersect(point dl1, point ur1, point dl2, point ur2) {
    return max(dl1.x, dl2.x) <= min(ur1.x, ur2.x) && max(dl1.y, dl2.y) <= min(ur1.y, ur2.y);
}*/

bool do_segments_intersect(point p1, point q1, point p2, point q2) {
    int o11 = orientation(p1, q1, p2);
    int o12 = orientation(p1, q1, q2);
    int o21 = orientation(p2, q2, p1);
    int o22 = orientation(p2, q2, q1);
    // oxx != 0 means cross intersection, no T intersection
    if (o11 != o12 && o21 != o22 && o11 != 0 && o12 != 0 && o21 != 0 && o22 != 0) // general case -> non-collinear intersection
        return true;
    return false;
}

// returns true if point r is on the same line as the line pq
bool collinear(point p, point q, point r) {
  return fabs(((q - p)^(r - p))) < EPS; }

// angle from 0 to 2*PI
db anglet(point a, point o, point b) {  // returns angle aob in rad
  point oa = (a - o), ob = (b - o);
  db ang = acos(oa * ob / sqrt(oa.norm_sq()*ob.norm_sq()));
  if(ang!=0&&!collinear(a,o,b)&&ccw(a,o,b))ang = 2*PI - ang;
  return ang; }  // better

db angle(point a, point o, point b) {  // returns angle aob in rad
  point oa = (a - o), ob = (b - o);
  return acos(oa * ob / sqrt(oa.norm_sq()*ob.norm_sq())); }
// returns true if we always make the same turn while examining
// all the edges of the polygon one by one
bool isConvex(const vector<point> &P) {
  ll sz = (ll)P.size();
  if (sz <= 3) return false;   // a point/sz=2 or a line/sz=3 is not convex
  bool firstTurn = ccw(P[0], P[1], P[2]);            // remember one result
  for (ll i = 1; i < sz-1; i++)            // then compare with the others
    if (ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2]) != firstTurn)
      return false;            // different sign -> this polygon is concave
  return true; }                                  // this polygon is convex

// returns true if point p is in either convex/concave polygon P
bool inPolygon(point pt, const vector<point> &P) {
  if ((ll)P.size() < 3) return false;               // avoid point or line
  db sum = 0;    // assume the first vertex is equal to the last vertex
  for (ll i = 0; i < (ll)P.size()-1; i++) {
    if (((P[i] - pt)^(P[i+1] - pt)) > 0) //CCW check collinear
         sum += angle(P[i], pt, P[i+1]);                   // left turn/ccw
    else sum -= angle(P[i], pt, P[i+1]); }                 // right turn/cw
  return fabs(sum) > PI; }   // 360d -> in, 0d -> out, we have large margin

// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q, point A, point B) {
  db a = B.y - A.y;
  db b = A.x - B.x;
  db c = B.x * A.y - A.x * B.y;
  db u = fabs(a * p.x + b * p.y + c);
  db v = fabs(a * q.x + b * q.y + c);
  return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v)); }

// cuts polygon Q along the line formed by point a -> point b
// (note: the last point must be the same as the first point)
// to cut the other side, swap (a,b)
vector<point> cutPolygon(point a, point b, const vector<point> &Q) {
  vector<point> P;
  for (ll i = 0; i < (ll)Q.size(); i++) {
    db left1 = (b - a)^(Q[i] - a), left2 = 0;
    if (i != (ll)Q.size()-1) left2 = (b - a)^(Q[i+1] - a);
    if (left1 > -EPS) P.push_back(Q[i]);       // Q[i] is on the left of ab
    if (left1 * left2 < -EPS)        // edge (Q[i], Q[i+1]) crosses line ab
      P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
  }
  if (!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front());        // make P's first point = P's last point
  return P; }

vector<point> CH_Andrew(vector<point> &Pts) {
  ll n = Pts.size(), k = 0;
  vector<point> H(2*n);
  sort(Pts.begin(), Pts.end());        // sort the points lexicographically
  for (ll i = 0; i < n; i++) {                         // build lower hull
    while (k >= 2 && ccw(H[k-2], H[k-1], Pts[i]) <= 0) k--;
    H[k++] = Pts[i];
  }
  for (ll i = n-2, t = k+1; i >= 0; i--) {             // build upper hull
    while (k >= t && ccw(H[k-2], H[k-1], Pts[i]) <= 0) k--;
    H[k++] = Pts[i];
  }
  H.resize(k);
  return H;
}

point pivot(0, 0);
vector<point> CH_Graham(vector<point> &Pts) {
  vector<point> P(Pts);      // copy all points so that Pts is not affected
  ll i, j, n = (ll)P.size();
  if (n <= 3) {          // corner cases: n=1=point, n=2=line, n=3=triangle
    if (!(P[0] == P[n-1])) P.push_back(P[0]); // safeguard from corner case
    return P; }                                       // the CH is P itself

  // first, find P0 = point with lowest Y and if tie: rightmost X
  ll P0 = 0;
  for (i = 1; i < n; i++)                                           // O(n)
    if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
      P0 = i;
  swap(P[0], P[P0]);                                // swap P[P0] with P[0]

  // second, sort points by angle w.r.t. pivot P0, O(n log n) for this sort
  pivot = P[0];                    // use this global variable as reference
  sort(++P.begin(), P.end(), [](point a, point b) {  // we do not sort P[0]
    if (collinear(pivot, a, b))                             // special case
      return dist(pivot, a) < dist(pivot, b);  // check which one is closer
    db d1x = a.x-pivot.x, d1y = a.y-pivot.y;
    db d2x = b.x-pivot.x, d2y = b.y-pivot.y;
    return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0; }); // compare 2 angles

  // third, the ccw tests, although complex, it is just O(n)
  vector<point> S;
  S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]);   // initial S
  i = 2;                                         // then, we check the rest
  while (i < n) {     // note: n must be >= 3 for this method to work, O(n)
    j = (ll)S.size()-1;
    if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]);  // left turn, accept
    else S.pop_back(); }   // or pop the top of S until we have a left turn
  return S; } // return the result, overall O(n log n) due to angle sorting

point center_of_mass(vector <point>& Q)
{
    point ctr(0,0);
    for (ll i=0;i<Q.size()-1;i++)
    {
        ctr = ctr + Q[i];
    }
    ctr.x/=Q.size()-1;
    ctr.y/=Q.size()-1;
    return ctr;
}
// Pick's theorem
// A = i + b/2 -1
// A: Area poligon with integer coords
// i: Interior points, b: points in the segments 

// with vector form of integer segment
// (x0,y0) + t(dx,dy)
ll points_in_segment(point a, point b)
{
  ll absx=abs(a.x-b.x),absy=abs(a.y-b.y);
  return __gcd(absx,absy) + 1;
  
}

ll memo[101][101][101];

// Dp that pass all possible convex poligons
// from the shortest in(in.y < p.y)
// p si counter cw from in, p
ll all_convex(ll in, ll p, ll q, vector<point>& Q)
{
    if(memo[in][p][q] != -1) return memo[in][p][q];
    ll ans = 0;

    for(int i = in + 1; i < Q.size(); i++)
    {
        if(i != p && i != q && ccw(Q[in], Q[q], Q[i]) && ccw(Q[p], Q[q], Q[i]))
        {
            ans += (all_convex(in, q, i, Q) + 1);
        }
    }
    return memo[in][p][q] = ans;
}
bool comp(point& a, point& b)
{
    return a.y < b.y;
}
//..
vector<point>Q;
sort(ALL(Q), comp);
ll ans = 0;
for(int i = 0; i < n; i++)
{
    for(int p = i + 1;p < n; p++) for(int q = p + 1; q < n; q++)
    {
        if(ccw(Q[i], Q[p], Q[q]))
            ans += all_convex(i, p, q, Q) + 1;
        else
            ans += all_convex(i, q, p, Q) + 1;
        ans %= m;
    }
}