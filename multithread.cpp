#include <GL/glut.h>
#include <bits/stdc++.h>
#include <windows.h>

using namespace std;

vector<pair<int,int>> pointList;
vector<pair<int,int>> result;

void printPoint(pair<int,int> p)
{
    std::printf("<%d,%d>", p.first, p.second);
}
    
void printPointList(vector<pair<int,int>> v)
{
    for(vector<pair<int,int>>::iterator ii=v.begin(); ii!=v.end(); ii++)
    {
        printPoint((*ii));
        std::printf(" ");
    }
    printf("\n");
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

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

DWORD WINAPI console(LPVOID param)
{
    // Initialization
    int n;
    char modeInput;

    srand (time(NULL));

    std::printf("Randomize input?(y/n): ");
    // scanf("%c", &modeInput);
    cin >> c
    bool randomize = (modeInput=='y' || modeInput == 'Y');
    
    std::printf("Enter points count: ");
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
            std::printf("Enter point %d: ", i);
            scanf("%d %d", &x, &y);
        }
        pointList.push_back({x,y});
    }

    printPointList(pointList);

    // Convex Hull 1: Find furthest left point
    int pivotIndex=0;
    
    // Find minimum index
    for(int i=1;i<pointList.size();i++) if(pointList[pivotIndex].first > pointList[i].first)
        pivotIndex = i;

     pair<int,int> pivot = pointList[pivotIndex];

    // Convex Hull 2 : Making the convex hull itself

    // Store the starting index
    int startingIndex = pivotIndex;
    int lastIndex;
    
    // Loop until meets the starting index
    int count=0;
    do
    {
        int i=0;
        bool found=false;
        while(!found && i<n)
        {
            // If a line is created (two different points are selected)..
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
                    std::printf("Convex Hull Point-%d: ", ++count);
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

    std::printf("Convex Hull:\n");
    printPointList(result);
}

DWORD WINAPI display(LPVOID param)
{
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

int main()
{
    int data1 = 1;
    int data2 = 2;

    HANDLE handle1 = 0;
    HANDLE handle2 = 0;
    HANDLE handleArray[3];

    handle1 = CreateThread(NULL, 0 , console, NULL , 0, NULL);
    if(handle1 == NULL) ExitProcess(0);
    handle2 = CreateThread(NULL, 0 , display, &data2 , 0, NULL);
    if(handle2 == NULL) ExitProcess(0);

    handleArray[0] = handle1;
    handleArray[1] = handle2;

    WaitForMultipleObjects(2,handleArray, TRUE, INFINITE);
    CloseHandle(handle1);
    CloseHandle(handle2);
}