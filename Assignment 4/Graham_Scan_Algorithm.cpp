#include <bits/stdc++.h>
using namespace std;
 
struct Point
{
    int x, y;
};
Point p0;

Point nextToTop(stack<Point> &S)
{
    Point p = S.top();
    S.pop();
    Point rs = S.top();
    S.push(p);
    return rs;
}
int swap(Point &p1, Point &p2)
{
    Point temp = p1;
    p1 = p2;
    p2 = temp;
}
int distSq(Point p1, Point p2)
{
    return (p1.x - p2.x)*(p1.x - p2.x)+(p1.y - p2.y)*(p1.y - p2.y);
}

int orientation(Point p, Point q, Point r)
{
    int val = (q.y - p.y)*(r.x - q.x)-(q.x - p.x)*(r.y - q.y); 
    if (val == 0) 
    return 0; 
    if(val > 0)
    return 1;
    return 2; 
}
int compare(const void *vp1, const void *vp2)
{
   Point *p1 = (Point *)vp1;
   Point *p2 = (Point *)vp2;
   int o = orientation(p0, *p1, *p2);
   if (o == 0)
     return (distSq(p0, *p2) >= distSq(p0, *p1))? -1 : 1;
   return (o == 2)? -1: 1;
}
void convexHull(Point points[], int n)
{
   int ymin = points[0].y, min = 0;
   for (int i = 1; i < n; i++)
   {
     int y = points[i].y;
     if ((y < ymin) || (ymin == y &&
         points[i].x < points[min].x))
        ymin = points[i].y, min = i;
   }
   swap(points[0], points[min]);
   p0 = points[0];
   qsort(&points[1], n-1, sizeof(Point), compare);
   int m = 1; 
   for (int i=1; i<n; i++)
   {
       while (i < n-1 && orientation(p0, points[i],points[i+1]) == 0)
          i++;
       points[m] = points[i];
       m++;  
   }
   if (m < 3) return;
   stack<Point> S;
   S.push(points[0]);
   S.push(points[1]);
   S.push(points[2]);
   for (int i = 3; i < m; i++)
   {
      while (orientation(nextToTop(S), S.top(), points[i]) != 2)
         S.pop();
      S.push(points[i]);
   }
   //Output
   while (!S.empty())
   {
       Point p = S.top();
       cout << "(" << p.x << ", " << p.y <<")" << endl;
       S.pop();
   }
}
int main()
{
    int n;
    cin>>n;
    Point *P= new Point[n];
    for(int i=0;i<n;i++)
    {
       cin>>P[i].x>>P[i].y;
    }
    float t0 = clock();
    convexHull(P, n);
    float t1 = clock();
    cout<<"Total time is"<<(t1-t0)/CLOCKS_PER_SEC<<" seconds"<<endl;
    return 0;
}