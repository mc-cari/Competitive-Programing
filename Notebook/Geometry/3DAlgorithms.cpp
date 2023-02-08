#include "../Header.cpp"


struct point { db x, y, z;   
    point() { x = y = z = 0.0; }                      
    //point(db r, db u, db v) : x(r*cos(u)*cos(v)), y(r*cos(u)*sin(v)), z(r*sin(u)) {}
	point(db _x, db _y, db _z) : x(_x), y(_y), z(_z) {}     
	point operator^(const point &p) const {
		return { y*p.z - z*p.y, z*p.x - x*p.z, x*p.y - y * p.x};
	}
	db dot(point& p) { return x*p.x + y*p.y + z*p.z; }
    db norm() { return sqrt(x*x + y*y + z*z); }
	
	bool operator == (const point& p) const
    {
        return abs(p.x - x) < EPS && abs(p.y - y) < EPS && abs(p.z - z) < EPS;
    }
    point operator + (const point& p) const
    {
        return point(x + p.x, y + p.y, z + p.z);
    }
    point operator - (const point& p) const
    {
        return point(x - p.x, y - p.y, z - p.z);
    }
    point operator * (db a) const
    {
        return point(x * a, y * a, z * a);
    }
    point operator / (db a) const
    {
        return point(x / a, y / a, z / a);
    }
	point unit() {
        db d = norm();
        return {x/d,y/d,z/d};
    }

};
db angle2(point& x, point& y)
{
	return acos(x.dot(y) / (R*R));
}

bool in_arc(point& p1, point& p2, point& n, point& inter)
{
	db ab = angle2(p1, p2);
	db ap = angle2(p1, inter);
	point d = (p1 * cos(ap) + (n ^ p1) * sin(ap));
	return ab > ap && inter == d;
}
bool do_intersect_circles()
{
    point a1 = g[j][z], a2 = g[j][0];
    if(z < g[j].size() - 1)
        a2 = g[j][z+1];
    point p1 = route[i], p2 = route[i+1];
    point n1 = (p1^p2).unit(), n2 = (a1^a2).unit();
    point inter = n1^n2;
    if(inter.norm() < EPS)continue;
    inter = inter.unit() * R;
    
    if(in_arc(p1, p2, n1, inter) && in_arc(a1, a2, n2, inter))
    {	
        ag.push_back(angle2(p1, inter));
        continue;
    }
    inter = inter * -1.0;
    if(in_arc(p1, p2, n1, inter) && in_arc(a1, a2, n2, inter))
    {	
        ag.push_back(angle2(p1, inter));
        continue;
    }
}