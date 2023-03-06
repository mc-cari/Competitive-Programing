#include "../Header.cpp"

//#define double long long //Para usar enteros

db DEG_to_RAD(db d) { return d * PI / 180.0; }
db RAD_to_DEG(db r) { return r * 180.0 / PI; }



//sweepline rotating a circle around a point
// how many points are in circle radius r
// alpha = atan2(point - center) +- acos(dist/2r)


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

ll insideCircle(point p, point c, ll r) { // all integer version
    ll dx = p.x - c.x, dy = p.y - c.y;
    ll Euc = dx * dx + dy * dy, rSq = r * r;             // all integer
    return Euc < rSq ? 0 : Euc == rSq ? 1 : 2; } //inside/border/outside

// P1 an d P2 intersections of circles and radius r -> pos of centers of circles of intersection
bool circle2PtsRad(point p1, point p2, db r, point &c) {
    db d2 = (p1.x - p2.x) * (p1.x - p2.x) +
                (p1.y - p2.y) * (p1.y - p2.y);
    db det = r * r / d2 - 0.25;
    if (det < 0.0) return false;
    db h = sqrt(det);
    c.x = (p1.x + p2.x) * 0.5 + (p1.y - p2.y) * h;
    c.y = (p1.y + p2.y) * 0.5 + (p2.x - p1.x) * h;
    return true; }         // to get the other center, reverse p1 and p2

db dist(point& p1, point& p2) {                // Euclidean distance
    return sqrt((p1.x-p2.x)*(p1.x-p2.x)+ (p1.y-p2.y)*(p1.y-p2.y)); } 
db dist_sq(point p1, point p2) {
    return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y); }


// a = max x, b = max y from the center, AREA
db A_elipse(db a,db b)
{
    return a*b*PI;
}

// Length of segment with two points on the circunference
// separated by an angle
db chord(db r, db angle)
{
    return sqrt(2*r*r*(1-cos(angle)));
}

//Triangles
db perimeter(db ab, db bc, db ca) {
    return ab + bc + ca; }

db perimeter(point a, point b, point c) {
    return dist(a, b) + dist(b, c) + dist(c, a); }

db area(db ab, db bc, db ca) {
  // Heron's formula, split sqrt(a * b) into sqrt(a) * sqrt(b); in implementation
    db s = 0.5 * perimeter(ab + bc + ca);
    return sqrt(s) * sqrt(s - ab) * sqrt(s - bc) * sqrt(s - ca); }

db area(point a, point b, point c) {
    return area(dist(a, b), dist(b, c), dist(c, a)); }


// Area of the circle enclosed by an arc and a chord defined by an angle
db segment(db r, db angle)
{
    return  angle/2.0*r*r-area(chord(r,angle),r,r);
}

// And overlaping rectangle area > 0
bool rectangles_intersect(point a1,point a2,point b1,point b2,point& ans1, point& ans2)
{
    if(b1<a1)
    {
        swap(a1,b1);
        swap(a2,b2);
    }
    if(b1.x>=a2.x||b1.y>=a2.y||b2.y<=a1.y)return 0;
    ans1.x=b1.x;
    ans1.y=max(b1.y,a1.y);
    ans2.x=min(b2.x,a2.x);
    ans2.y=min(b2.y,a2.y);
    return 1;

}

struct line { db a, b, c; };

void pointsToLine(point p1, point p2, line &l) {
    if (fabs(p1.x - p2.x) < EPS) {              // vertical line is fine
        l.a = 1.0;   l.b = 0.0;   l.c = -p1.x;           // default values
    } else {
        l.a = -(db)(p1.y - p2.y) / (p1.x - p2.x);
        l.b = 1.0;              // IMPORTANT: we fix the value of b to 1.0
        l.c = -(db)(l.a * p1.x) - p1.y;
} }

bool areParallel(line l1, line l2) {        // check coefficient a + b
    return (fabs(l1.a-l2.a) < EPS) && (fabs(l1.b-l2.b) < EPS); }

bool areSame(line l1, line l2) {           // also check coefficient c
    return areParallel(l1 ,l2) && (fabs(l1.c-l2.c) < EPS); }

// returns true (+ intersection point) if two lines are intersect
bool areIntersect(line l1, line l2, point &p) {
    if (areParallel(l1, l2)) return false;            // no intersection
    // solve system of 2 linear algebraic equations with 2 unknowns
    p.x = (l2.b * l1.c - l1.b * l2.c) / (l2.a * l1.b - l1.a * l2.b);
    // special case: test for vertical line to avoid division by zero
    if (fabs(l1.b) > EPS) p.y = -(l1.a * p.x + l1.c);
    else                  p.y = -(l2.a * p.x + l2.c);
    return true; }

db rInCircle(db ab, db bc, db ca) {
    return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca)); }

db rInCircle(point a, point b, point c) {
    return rInCircle(dist(a, b), dist(b, c), dist(c, a)); }

// assumption: the required points/lines functions have been written
// returns 1 if there is an inCircle center, returns 0 otherwise
// if this function returns 1, ctr will be the inCircle center
// and r is the same as rInCircle
ll inCircle(point p1, point p2, point p3, point &ctr, db &r) {
    r = rInCircle(p1, p2, p3);
    if (fabs(r) < EPS) return 0;                   // no inCircle center

    line l1, l2;                    // compute these two angle bisectors
    db ratio = dist(p1, p2) / dist(p1, p3);
    point p = p2 + (p3 - p2) * (ratio / (1 + ratio));
    pointsToLine(p1, p, l1);

    ratio = dist(p2, p1) / dist(p2, p3);
    p = p1 + (p3 - p1) * (ratio / (1 + ratio));
    pointsToLine(p2, p, l2);

    areIntersect(l1, l2, ctr);           // get their intersection point
    return 1; }

db rCircumCircle(db ab, db bc, db ca) {
    return ab * bc * ca / (4.0 * area(ab, bc, ca)); }

db rCircumCircle(point a, point b, point c) {
    return rCircumCircle(dist(a, b), dist(b, c), dist(c, a)); }

// assumption: the required points/lines functions have been written
// returns 1 if there is a circumCenter center, returns 0 otherwise
// if this function returns 1, ctr will be the circumCircle center
// and r is the same as rCircumCircle
ll circumCircle(point p1, point p2, point p3, point &ctr, db &r){
    db a = p2.x - p1.x, b = p2.y - p1.y;
    db c = p3.x - p1.x, d = p3.y - p1.y;
    db e = a * (p1.x + p2.x) + b * (p1.y + p2.y);
    db f = c * (p1.x + p3.x) + d * (p1.y + p3.y);
    db g = 2.0 * (a * (p3.y - p2.y) - b * (p3.x - p2.x));
    if (fabs(g) < EPS) return 0;

    ctr.x = (d*e - b*f) / g;
    ctr.y = (a*f - c*e) / g;
    r = dist(p1, ctr);  // r = distance from center to 1 of the 3 points
    return 1; }

// https://www.nayuki.io/res/smallest-enclosing-circle/computational-geometry-lecture-6.pdf
// O(N) expected time

void smallest_enclosing_circle(vector<point>& pts, point& center, db& r) {
    random_shuffle(pts.begin(), pts.end());
    center = pts[0]; r = 0;
    ll N = pts.size();
    for(ll i=1;i<N;i++) {
        if (dist(pts[i] , center) > r + EPS) {
            center = pts[i];
            r = 0;
            for(ll j=0;j<i;j++) {
                if (dist(pts[j] , center) > r + EPS) {
                    center = (pts[i] + pts[j]) * 0.5;
                    r = dist(pts[i] , center);
                    for(ll k=0;k<j;k++) {
                        if (dist(pts[k] , center) > r + EPS) {
                            db rr;
                            circumCircle(pts[i], pts[j], pts[k],center,rr);
                            r = dist(pts[k] , center);
                        }
                    }
                }
            }
        }
    }
}

// returns true if point d is inside the circumCircle defined by a,b,c
ll inCircumCircle(point a, point b, point c, point d) {
    return (a.x - d.x) * (b.y - d.y) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) +
        (a.y - d.y) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.x - d.x) +
        ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.x - d.x) * (c.y - d.y) -
        ((a.x - d.x) * (a.x - d.x) + (a.y - d.y) * (a.y - d.y)) * (b.y - d.y) * (c.x - d.x) -
        (a.y - d.y) * (b.x - d.x) * ((c.x - d.x) * (c.x - d.x) + (c.y - d.y) * (c.y - d.y)) -
        (a.x - d.x) * ((b.x - d.x) * (b.x - d.x) + (b.y - d.y) * (b.y - d.y)) * (c.y - d.y) > 0 ? 1 : 0;
}

bool canFormTriangle(db a, db b, db c) {
     return (a + b > c) && (a + c > b) && (b + c > a); }


/*
Si un punto tiene un ángulo >= 60, el lado opuesto no es el menor del triangulo
*/

// Function to find the circle on 
// which the given three points lie
// better CIRCUMCENTER
tuple<db, db, db> findCircle(db x1, db y1, db x2, db y2, db x3, db y3) 
{ 
    db x12 = x1 - x2; 
    db x13 = x1 - x3; 
  
    db y12 = y1 - y2; 
    db y13 = y1 - y3; 
  
    db y31 = y3 - y1; 
    db y21 = y2 - y1; 
  
    db x31 = x3 - x1; 
    db x21 = x2 - x1; 
  
    db sx13 = x1*x1 - x3*x3; 
    db sy13 = y1*y1 - y3*y3; 
  
    db sx21 = x2*x2 - x1*x1; 
    db sy21 = y2*y2 - y1*y1; 
  
    db f = ((sx13) * (x12) 
             + (sy13) * (x12) 
             + (sx21) * (x13) 
             + (sy21) * (x13)) 
            / (2 * ((y31) * (x12) - (y21) * (x13))); 
    db g = ((sx13) * (y12) 
             + (sy13) * (y12) 
             + (sx21) * (y13) 
             + (sy21) * (y13)) 
            / (2 * ((x31) * (y12) - (x21) * (y13))); 
  
    db c = -x1*x1 - y1*y1 - 2 * g * x1 - 2 * f * y1; 
  
    // eqn of circle be x^2 + y^2 + 2*g*x + 2*f*y + c = 0 
    // where centre is (h = -g, k = -f) and radius r 
    // as r^2 = h^2 + k^2 - c 
    db h = -g; 
    db k = -f; 
    db sqr_of_r = h * h + k * k - c; 
  
    // r is the radius 
    db r = sqrt(sqr_of_r); 
  
    //cout << "Centre = (" << h << ", " << k << ")" << endl; 
    //cout << "Radius = " << r; 
    return make_tuple(h, k, r);
} 

