// Section: Geometry
// Topic:   Co-ordinate Geo

typedef double T;
typedef complex<T> pt;
#define X real()
#define Y imag()
const double eps = 1e-12;

bool isZero(T v){return abs(v)<eps;}
bool operator<(const pt& a, const pt& b) {
    if (abs(a.X - b.X) > eps) return a.X < b.X;
    return a.Y < b.Y - eps;
}

T sq(pt p) { return p.X*p.X + p.Y*p.Y; }
double abs(pt p) { return sqrt(sq(p)); }

pt translate(pt v, pt p) { return p + v; }
pt scale(pt c, T factor, pt p) { return c + (p - c) * factor; } // scale point p by factor with center c
pt rot(pt p, T a) { return p * polar(1.0, a); } // rotate a radian wrt origin
pt perp(pt p) { return pt(-p.Y, p.X); }

// p goes to fp, q goes to fq. Where does r go?
pt linearTransfo(pt r, pt p, pt fp, pt q, pt fq) { return fp + (r - p) * (fq - fp) / (q - p); }

T dot(pt v, pt w) { return (conj(v) * w).X; }
bool isPerp(pt v, pt w) { return isZero(dot(v, w)); }
double angle(pt v, pt w) { return acos(clamp(dot(v, w) / abs(v) / abs(w), -1.0, 1.0)); }
T cross(pt v, pt w) { return (conj(v) * w).Y; }

// is a,b,c clockwise
T orient(pt a, pt b, pt c) { return cross(b - a, c - a); }

// is p inside the angle <BAC
bool inAngle(pt a, pt b, pt c, pt p) {
    assert(!isZero(orient(a, b, c)));
    if (orient(a, b, c) < 0) swap(b, c);
    return orient(a, b, p) >= 0 && orient(a, c, p) <= 0;
}

bool isConvex(vector<pt> p) {
    bool hasPos = false, hasNeg = false;
    for (int i = 0, n = (int)p.size(); i < n; i++) {
        T o = orient(p[i], p[(i + 1) % n], p[(i + 2) % n]);
        if (o > eps) hasPos = true;
        if (o < -eps) hasNeg = true;
    }
    return !(hasPos && hasNeg);
}

//Polar sort with center and start in the direction 1,0
bool half(pt p, pt v = {1,0}) {
    return cross(v,p) < 0 || (cross(v,p) == 0 && dot(v,p) <0);
}

void polarSort(vector<pt> &v, pt center = {0,0}) {
    sort(v.begin(), v.end(), [center](pt v, pt w) {
        return (make_tuple(half(v-center), 0)) <
        make_tuple(half(w-center), cross(v-center, w-center));
});
}

struct line {
    pt v; T c;
    // From direction vector v and offset c
    line(pt v_, T c_) : v(v_), c(c_) {}
    // From equation ax+by=c
    line(T a, T b, T c_) : v(pt(b, -a)), c(c_) {}
    // From points P and Q
    line(pt p, pt q) : v(q - p), c(cross(v, p)) {}
    
    // - these work with T = int
    T side(pt p) const { return cross(v, p) - c; } // evaluate p in ax+by+c
    double dist(pt p) const { return abs(side(p)) / abs(v); } // point to line
    double sqDist(pt p) const { return side(p) * side(p) / (double)sq(v); }
    line perpThrough(pt p) const { return line(p, p + perp(v)); }
    bool cmpProj(pt p, pt q) const { return dot(v, p) < dot(v, q); } // use this to sort points on a line
    line translate(pt t) const { return line(v, c + cross(v, t)); } // translate by a vector t

    // - these require T = double
    line shiftLeft(double dist) const { return line(v, c + dist * abs(v)); } // translate left by a distance
    pt proj(pt p) const { return p - perp(v) * side(p) / sq(v); } // orthogonal projection
    pt refl(pt p) const { return p - perp(v) * 2.0 * side(p) / sq(v); } // reflection
};

// returns whether they intersect. saves ans in out
bool inter(line l1, line l2, pt &out) {
    T d = cross(l1.v, l2.v);
    if (isZero(d)) return false;
    out = (l2.v * l1.c - l1.v * l2.c) / d; // requires floating-point coordinates
    return true;
}

// angle bisector. internal or external
line bisector(line l1, line l2, bool interior) {
    assert(!isZero(cross(l1.v, l2.v))); // l1 and l2 cannot be parallel!
    T sign = interior ? 1 : -1;
    pt v = l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign;
    double cc = l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign;
    return line(v, cc);
}

// ------SEGMENTS------

bool inDisk(pt a, pt b, pt p) {
    return dot(a - p, b - p) <= 0;
}

bool onSegment(pt a, pt b, pt p) { return isZero(orient(a, b, p)) && inDisk(a, b, p); } // is p on the segment ab

// Do segments ab and cd intersect at 1 point? Saved in out
bool properInter(pt a, pt b, pt c, pt d, pt &out) {
    T oa = orient(c, d, a),
        ob = orient(c, d, b),
        oc = orient(a, b, c),
        od = orient(a, b, d);
    // Proper intersection exists iff opposite signs
    if (oa * ob < 0 && oc * od < 0) {
        out = (a * ob - b * oa) / (ob - oa);
        return true;
    }
    return false;
}

// set of intersection points. if infinite, return two endpoints
struct cmpX {
    bool operator()(pt a, pt b) {
        return make_pair(a.X, a.Y) < make_pair(b.X, b.Y);
    }
};
set<pt,cmpX> inters(pt a, pt b, pt c, pt d) {
    pt out;
    if (properInter(a,b,c,d,out)) return {out};
    set<pt,cmpX> s;
    if (onSegment(c,d,a)) s.insert(a);
    if (onSegment(c,d,b)) s.insert(b);
    if (onSegment(a,b,c)) s.insert(c);
    if (onSegment(a,b,d)) s.insert(d);
    return s;
}

// distance from p to segment ab
double segPoint(pt a, pt b, pt p) {
    if (a != b) {
        line l(a, b);
        if (l.cmpProj(a, p) && l.cmpProj(p, b)) return l.dist(p); // output distance to line
    }
    return min(abs(p - a), abs(p - b));
}

// min distance between segment ab and cd
double segSeg(pt a, pt b, pt c, pt d) {
    pt dummy;
    if (properInter(a, b, c, d, dummy)) return 0;
    return min({ segPoint(a, b, c), segPoint(a, b, d), segPoint(c, d, a), segPoint(c, d, b) });
}

// ------POLYGON-------

double areaTriangle(pt a, pt b, pt c) { return abs(cross(b - a, c - a)) / 2.0; }
double areaPolygon(vector<pt> p) {
    double area = 0.0;
    for (int i = 0, n = (int)p.size(); i < n; i++) area += cross(p[i], p[(i + 1) % n]); // wrap back to 0 if i == n-1
    return abs(area) / 2.0;
}

// true if P at least as high as A (blue part)
bool above(pt a, pt p) { return p.Y >= a.Y; }
// check if [PQ] crosses ray from A
bool crossesRay(pt a, pt p, pt q) { return (above(a, q) - above(a, p)) * orient(a, p, q) > 0; }

// is point a inside the polygon? If strict, false when on the boundary
bool inPolygon(vector<pt> p, pt a, bool strict = true) {
    int numCrossings = 0;
    for (int i = 0, n = (int)p.size(); i < n; i++) {
        if (onSegment(p[i], p[(i + 1) % n], a)) return !strict;
        numCrossings += crossesRay(a, p[i], p[(i + 1) % n]);
    }
    return numCrossings & 1; // inside if odd number of crossings
}

// -------CIRCLES----------

template <typename U> int sgn(U x) { return (U(0) < x) - (x < U(0)); } // returns 1 if pos, 0 if 0, -1 if neg

pt circumCenter(pt a, pt b, pt c) {
    b = b - a; c = c - a; // consider coordinates relative to A
    assert(!isZero(cross(b, c))); // no circumcircle if A,B,C aligned
    return a + perp(b * sq(c) - c * sq(b)) / cross(b, c) / 2.0;
}

// return number of intersections, store in out
int circleLine(pt o, double r, line l, pair<pt, pt> &out) {
    double h2 = r * r - l.sqDist(o);
    if (h2 >= 0) { // the line touches the circle
        pt p = l.proj(o); // point P
        pt h = l.v * sqrt(h2) / abs(l.v); // vector parallel to l, of length h
        out = { p - h, p + h };
    }
    return 1 + sgn(h2);
}

int circleCircle(pt o1, double r1, pt o2, double r2, pair<pt, pt> &out) {
    pt d = o2 - o1; double d2 = sq(d);
    if (isZero(d2)) { assert(r1 != r2); return 0; } // concentric circles
    double pd = (d2 + r1 * r1 - r2 * r2) / 2; // = |O_1P| * d
    double h2 = r1 * r1 - pd * pd / d2; // = h^2
    if (h2 >= 0) {
        pt p = o1 + d * pd / d2, h = perp(d) * sqrt(h2 / d2);
        out = { p - h, p + h };
    }
    return 1 + sgn(h2);
}

/*
Tangents of 2 circles. 
Inner or outer tangents possible.
If 1 tangent, output tangency point.
If 2 tangents, each pair has the tangency point for one tangent.
To get tangent from point to circle, set r2=0
*/
int tangents(pt o1, double r1, pt o2, double r2, bool inner, vector<pair<pt, pt>> &out) {
    if (inner) r2 = -r2;
    pt d = o2 - o1;
    double dr = r1 - r2, d2 = sq(d), h2 = d2 - dr * dr;
    if (isZero(h2)) h2 = 0; 
    if (isZero(d2) || h2 < 0) return 0;
    for (double sign : { -1.0, 1.0 }) {
        pt v = (d * dr + perp(d) * sqrt(h2) * sign) / d2;
        out.push_back({ o1 + v * r1, o2 + v * r2 });
    }
    return 1 + (h2 > 0);
}

//-----------3D-----------//
struct p3 {
    T x,y,z;
    // Basic vector operations
    p3 operator+(p3 p) {return {x+p.x, y+p.y, z+p.z};}
    p3 operator-(p3 p) {return {x-p.x, y-p.y, z-p.z};}
    p3 operator*(T d) {return {x*d, y*d, z*d};}
    p3 operator/(T d) {return {x/d, y/d, z/d};} // only for floating-point
    // Some comparators
    bool operator==(const p3& p) const { return abs(x-p.x)<eps && abs(y-p.y)<eps && abs(z-p.z)<eps; }
    bool operator!=(p3 p) {return !operator==(p);}
};

bool operator<(const p3& a, const p3& b) {
    if (abs(a.x - b.x) > eps) return a.x < b.x;
    if (abs(a.y - b.y) > eps) return a.y < b.y;
    return a.z < b.z - eps;
}

p3 zero{0,0,0};

T operator|(p3 v, p3 w) {return v.x*w.x + v.y*w.y + v.z*w.z;}
p3 operator*(p3 v, p3 w) {
    return {v.y*w.z - v.z*w.y,
    v.z*w.x - v.x*w.z,
    v.x*w.y - v.y*w.x};
}

T sq(p3 v) {return v|v;}
double abs(p3 v) {return sqrt(sq(v));}
p3 unit(p3 v) {
    if(isZero(abs(v))) return v;
    return v/abs(v);
}

double angle(p3 v, p3 w) {
    double cosTheta = (v|w) / abs(v) / abs(w);
    return acos(max(-1.0, min(1.0, cosTheta)));
}

T orient(p3 p, p3 q, p3 r, p3 s) {return (q-p)*(r-p)|(s-p);} //pos if s on side of pq*pr, 0 if on same plane, neg if on diff side
T orientByNormal(p3 p, p3 q, p3 r, p3 n) {return (q-p)*(r-p)|n;}

// Rotate point p around axis k by angle theta (k must be unit vector)
p3 rotate(p3 p, p3 k, double theta) {
    return p * cos(theta) + (k * p) * sin(theta) + k * (k | p) * (1 - cos(theta));
}

struct plane {
    p3 n; T d;
    // From normal n and offset d
    plane(p3 n, T d) : n(n), d(d) {}
    // From normal n and point P
    plane(p3 n, p3 p) : n(n), d(n|p) {}
    // From three non-collinear points P,Q,R
    plane(p3 p, p3 q, p3 r) : plane((q-p)*(r-p), p) {}
    
    // - these work with T = int
    T side(p3 p) {return (n|p)-d;}
    double dist(p3 p) {return abs(side(p))/abs(n);}
    plane translate(p3 t) {return {n, d+(n|t)};}
    // - these require T = double
    plane shiftUp(double dist) {return {n, d + dist*abs(n)};}
    p3 proj(p3 p) {return p - n*side(p)/sq(n);}
    p3 refl(p3 p) {return p - n*2*side(p)/sq(n);}
};

//Change coordinate system. Make PQR points the xy-plane. PQ = x axis.
struct coords {
    p3 o, dx, dy, dz;
    // From three points P,Q,R on the plane:
    // build an orthonormal 3D basis
    coords(p3 p, p3 q, p3 r) : o(p) {
        dx = unit(q-p);
        dz = unit(dx*(r-p));
        dy = dz*dx;
    }
    // From four points P,Q,R,S:
    // take directions PQ, PR, PS as is
    coords(p3 p, p3 q, p3 r, p3 s) :
    o(p), dx(q-p), dy(r-p), dz(s-p) {}
    //pt pos2d(p3 p) {return {(p-o)|dx, (p-o)|dy};} //gives the projection of p3 on PQR plane for this coordinate system
    p3 pos3d(p3 p) {return {(p-o)|dx, (p-o)|dy, (p-o)|dz};} //get the new coordinates of p
};

// line equation, P = o+Kd for all real k
struct line3d {
    p3 d, o;
    // From two points P, Q
    line3d(p3 p, p3 q) : d(q-p), o(p) {}
    // From two planes p1, p2 (requires T = double), also used for finding intersection of planes
    line3d(plane p1, plane p2) {
        d = p1.n*p2.n;
        o = (p2.n*p1.d - p1.n*p2.d)*d/sq(d);
    }
    // - these work with T = int
    double sqDist(p3 p) {return sq(d*(p-o))/sq(d);}
    double dist(p3 p) {return sqrt(sqDist(p));}
    bool cmpProj(p3 p, p3 q) {return (d|p) < (d|q);} //sort along line
    // - these require T = double
    p3 proj(p3 p) {return o + d*(d|(p-o))/sq(d);}
    p3 refl(p3 p) {return proj(p)*2 - p;}
    p3 inter(plane p) {return o - d*p.side(o)/(p.n|d);} //line plane intersection
};

//closest distance of 2 lines
double dist(line3d l1, line3d l2) {
    p3 n = l1.d*l2.d;
    if (n == zero) // parallel
    return l1.dist(l2.o);
    return abs((l2.o-l1.o)|n)/abs(n);
}

//Point on L1 closest to L2
p3 closestOnL1(line3d l1, line3d l2) {
    p3 n2 = l2.d*(l1.d*l2.d);
    return l1.o + l1.d*((l2.o-l1.o)|n2)/(l1.d|n2);
}

double smallAngle(p3 v, p3 w) {return acos(min(abs(v|w)/abs(v)/abs(w), 1.0));} //angle between vectors
//planes
double angle(plane p1, plane p2) {return smallAngle(p1.n, p2.n);} 
bool isParallel(plane p1, plane p2) {return p1.n*p2.n == zero;}
bool isPerpendicular(plane p1, plane p2) {return isZero(p1.n|p2.n);}
//lines
double angle(line3d l1, line3d l2) {return smallAngle(l1.d, l2.d);}
bool isParallel(line3d l1, line3d l2) {return l1.d*l2.d == zero;}
bool isPerpendicular(line3d l1, line3d l2) {return isZero(l1.d|l2.d);}
//line-plane
double angle(plane p, line3d l) {return M_PI/2 - smallAngle(p.n, l.d);}
bool isParallel(plane p, line3d l) {return isZero(p.n|l.d);}
bool isPerpendicular(plane p, line3d l) {return p.n*l.d == zero;}

line3d perpThrough(plane p, p3 o) {return line3d(o, o+p.n);} //perp from point to plane
plane perpThrough(line3d l, p3 o) {return plane(l.d, o);}


//------------Polyhedrons------------
p3 vectorArea2(vector<p3> p) { // vector area * 2 (to avoid divisions)
    p3 S = zero;
    for (int i = 0, n = p.size(); i < n; i++)
    S = S + p[i]*p[(i+1)%n];
    return S;
}
double area(vector<p3> p) {return abs(vectorArea2(p)) / 2.0;} //area of face by points p.

double volume(vector<vector<p3>> fs) {
    double vol6 = 0.0;
    for (vector<p3> f : fs)
        vol6 += (vectorArea2(f)|f[0]);
    return abs(vol6) / 6.0;
}
