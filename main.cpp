#include <GL/glut.h>
#include <windows.h>
#include <bits/stdc++.h>

using namespace std;

vector<pair<int,int>> pointList;
vector<pair<int,int>> result;

void printPoint(pair<int,int> p)
{
    printf("<%d,%d>\n", p.first, p.second);
}
    
void printPointList(vector<pair<int,int>> v)
{
    for(vector<pair<int,int>>::iterator ii=v.begin(); ii!=v.end(); ii++) printPoint((*ii));
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GLUT_MULTISAMPLE);
	//draw a line

    glLineWidth(1.2f);
    glColor3f(0.0, 1.0, 0.0);
    glEnable(GL_LINE_SMOOTH);
    int prevX=result[0].first,prevY=result[0].second;
    for(int i=1;i<result.size();i++)
    {
        
        glBegin(GL_LINES);
            glVertex2i(prevX,prevY);
            glVertex2i(result[i].first,result[i].second);
        glEnd();
        prevX=result[i].first;
        prevY=result[i].second;
    }
    glBegin(GL_LINES);
        glVertex2i(prevX,prevY);
        glVertex2i(result[0].first,result[0].second);
    glEnd();

	glColor3f(1.0, 0.0, 0.0);

	//draw two points
    glPointSize(7.5f);
    glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	for(int i = 0; i < pointList.size(); i++)
	{
		glVertex2i(pointList[i].first,pointList[i].second);
	}
	glEnd();

	glFlush();		/* Complete any pending operations */
}

DWORD WINAPI startLoop(LPVOID param)
{
    int argc = 1;
    glutInit(&argc, NULL);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Convex Hull");

    glClearColor(0.5,0.5,0.5,1.0);
    glutDisplayFunc(render);

    glutMainLoop();
}

int main()
{
    // Initialization
    int n;
    char modeInput;

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
            x = rand() % 101 + 50 ;
            y = rand() % 101 + 20;
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
    
    for(int i=1;i<pointList.size();i++) if(pointList[pivotIndex].first > pointList[i].first)
        pivotIndex = i;

    pivot = pointList[pivotIndex];

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

    } while(pivotIndex!=startingIndex);

    

    printf("Convex Hull:\n");
    printPointList(result);
    
    int argc = 1;
    glutInit(&argc, NULL);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600,600);
    glutCreateWindow("Convex Hull");
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
    glClearColor(0.1,0.1,0.1,1.0);
    glutDisplayFunc(render);

    glutMainLoop();

}