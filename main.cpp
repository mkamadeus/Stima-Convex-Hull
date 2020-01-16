#include<bits/stdc++.h>

using namespace std;

void printPoint(pair<int,int> p)
{
    printf("<%d,%d>\n", p.first, p.second);
}

void printPointList(vector<pair<int,int>> v)
{
    printf("Points in list:\n");
    for(vector<pair<int,int>>::iterator ii=v.begin(); ii!=v.end(); ii++) printPoint((*ii));
}

int main()
{
    // Initialization
    int n;
    vector<pair<int,int>> pointList;
    vector<pair<int,int>> result;

    printf("Enter points count: ");
    scanf("%d", &n);

    for(int i=1;i<=n;i++)
    {
        int x,y;
        printf("Enter point %d: ", i);
        scanf("%d %d", &x, &y);
        pointList.push_back({x,y});
    }

    bool hull[pointList.size()+5];
    memset(hull, 0, sizeof(hull));

    printPointList(pointList);

    // Convex Hull 1: Find furthest left point
    int pivotIndex=0;
    pair<int,int> pivot = pointList[pivotIndex];
    
    for(int i=1;i<pointList.size();i++) if(pivot.first > pointList[i].first)
    {
        pivotIndex = i;
        pivot = pointList[pivotIndex];
    }

    hull[pivotIndex] = true;

    // Convex Hull 2 : Making the convex hull itself

    


}