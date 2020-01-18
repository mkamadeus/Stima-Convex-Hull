#include<bits/stdc++.h>

using namespace std;

void printPoint(pair<int,int> p)
{
    printf("<%d,%d>\n", p.first, p.second);
}
    
void printPointList(vector<pair<int,int>> v)
{
    for(vector<pair<int,int>>::iterator ii=v.begin(); ii!=v.end(); ii++) printPoint((*ii));
}

int main()
{
    // Initialization
    int n;
    char modeInput;
    vector<pair<int,int>> pointList;
    vector<pair<int,int>> result;

    srand (time(NULL));

    printf("Randomize input?(y/n): ");
    scanf("%c", &modeInput);
    bool randomize = (modeInput=='y' || modeInput == 'Y');
    
    printf("Enter points count: ");
    scanf("%d", &n);

    for(int i=1;i<=n;i++)
    {
        int x,y;
        if(randomize)
        {
            x = rand() % 101 ;
            y = rand() % 101 ;
        }
        else 
        {
            printf("Enter point %d: ", i);
            scanf("%d %d", &x, &y);
        }
        pointList.push_back({x,y});
    }

    printPointList(pointList);

    // Convex Hull 1: Find furthest left point
    int pivotIndex=0;
    pair<int,int> pivot = pointList[pivotIndex];
    
    for(int i=1;i<pointList.size();i++) if(pivot.first > pointList[i].first)
    {
        pivotIndex = i;
        pivot = pointList[pivotIndex];
    }

    // Convex Hull 2 : Making the convex hull itself

    int startingIndex = pivotIndex;
    int lastIndex;
    
    do
    {
        int i=0;
        bool found=false;
        while(!found && i<n)
        {
            if(i!=pivotIndex)
            {
                // Constructing the line equation
                int x1 = pointList[i].first, y1 = pointList[i].second;
                int x2 = pivot.first , y2 = pivot.second;
                int a = y2-y1, b = x1-x2, c = x1*y2-y1*x2;
                
                // Check if onesided
                bool oneSided = true;
                int last = 0;
                int j=0;
                while(oneSided && j<n)
                {
                    if(j!=i && j!=pivotIndex)
                    {
                        int x = pointList[j].first, y=pointList[j].second;
                        int calc = a*x + b*y - c;

                        if((last==1 && calc<0) || (last==-1 && calc>0)) oneSided=false;    
                        else if(last==0) last = (calc>0) ? 1 : -1; // First point found
                    }

                    j++;
                }
                if(lastIndex!=i && oneSided)
                {
                    printf("Ke sini gan: ");
                    printPoint(pointList[i]);
                    result.push_back(pointList[i]);
                    lastIndex = pivotIndex;
                    pivot = pointList[i];
                    pivotIndex = i;
                    found = true;
                }

            }
            i++;
        }
        // break;

    } while(pivotIndex!=startingIndex);

    printf("Convex Hull:\n");


}