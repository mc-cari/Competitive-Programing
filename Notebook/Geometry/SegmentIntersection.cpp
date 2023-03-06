#include "../Header.cpp"

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
    db ang()
    {
        double a = atan2(y, x);
        if (a < 0) a += 2.0 * PI;
        return a;
    }

  };

db dist(const point& p1,const point& p2) {             
  return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); }


//Constant values to be returned
constexpr int Colinear = -1, NoIntersect = 0, Intersect = 1;
constexpr int CW = 2, CCW = 3;

int orientation(point& p, point& q, point& r) {
    ll tmp = (q - p)^(r - p);
    return tmp < 0 ? CW : tmp == 0 ? Colinear : CCW; // sign
}

struct segment { point p1, p2; 
  segment(point _p1, point _p2) : p1(_p1), p2(_p2) {}
};

//Returns of list of intersection points between segments s1, and s2
//If they do not intersect, the result is an empty vector
//If they intersect at exactly 1 point, the result contains that point
//If they overlap for non-0 distance, the left and right points of that intersection
//  are returned
bool onSegment(const point& p, const segment& s)
{
    bool x = (abs(s.p1.x - s.p2.x) < EPS && abs(p.x - s.p2.x) < EPS) || (p.x <= max(s.p1.x, s.p2.x) && p.x >= min(s.p1.x, s.p2.x));
    bool y = (abs(s.p1.y - s.p2.y) < EPS && abs(p.y - s.p2.y) < EPS) || (p.y <= max(s.p1.y, s.p2.y) && p.y >= min(s.p1.y, s.p2.y));
    return x && y;
}

vector<point> intersect(const segment& s1, const segment& s2)
{

    point a = s1.p1, b = s1.p2, c = s2.p1, d = s2.p2;

    if(orientation(a, b, c) == Colinear && orientation(a, b, d) == Colinear &&
        orientation(c, d, a) == Colinear && orientation(c, d, b) == Colinear)
    {
        point min_s1 = min(a, b), max_s1 = max(a, b);
        point min_s2 = min(c, d), max_s2 = max(c, d);

        if(max_s1 < min_s2 || max_s2 < min_s1) return {};

        point start = max(min_s1, min_s2), end = min(max_s1, max_s2);
        if(start == end)
            return {start};
        else
            return {min(start, end), max(start, end)};
    }

    db a1 = b.y - a.y, a2 = d.y - c.y;
    db b1 = a.x - b.x, b2 = c.x - d.x;
    db c1 = a1*a.x + b1*a.y, c2 = a2*c.x + b2*c.y;
    db det = a1*b2 - a2*b1;
    if(abs(det) > EPS)
    {
        point inter((b2*c1 - b1*c2)/det, (a1*c2 - a2*c1)/det), aux;
        //if(distToLineSegment(inter, s1.p1, s1.p2, aux) <= EPS && distToLineSegment(inter, s2.p1, s2.p2, aux) <= EPS)
        if(onSegment(inter, s1) && onSegment(inter, s2))
            return {inter};
    }
    return {};
}