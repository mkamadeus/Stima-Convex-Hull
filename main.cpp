#include <GL/glut.h>
#include <windows.h>
#include <bits/stdc++.h>
#include <chrono>

#define OFFSET_X 40
#define OFFSET_Y 0

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

void resize(int width, int height)
{
    GLfloat aspect = (GLfloat)width / (GLfloat)height;
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    if (width >= height) {
        // aspect >= 1, set the height from -1 to 1, with larger width
        gluOrtho2D(-1.0 * aspect, 1.0 * aspect, -1.0, 1.0);
    } else {
        // aspect < 1, set the width to -1 to 1, with larger height
        gluOrtho2D(-1.0, 1.0, -1.0 / aspect, 1.0 / aspect);
    }
}

void render(void)
{
	glClear(GL_COLOR_BUFFER_BIT);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH | GLUT_MULTISAMPLE);
    glEnable(GLUT_MULTISAMPLE);

	// Make Convex Hull Lines
    glLineWidth(1.2f);
    glColor3f(1.0, 0.941, 0.0);
    glEnable(GL_LINE_SMOOTH);
    int prevX=result[0].first,prevY=result[0].second;
    for(int i=1;i<result.size();i++)
    {
        glBegin(GL_LINES);
            glVertex2i(prevX + OFFSET_X,prevY + OFFSET_Y);
            glVertex2i(result[i].first + OFFSET_X,result[i].second + OFFSET_Y);
        glEnd();
        prevX=result[i].first;
        prevY=result[i].second;
    }
    glBegin(GL_LINES);
        glVertex2i(prevX + OFFSET_X,prevY + OFFSET_Y);
        glVertex2i(result[0].first + OFFSET_X,result[0].second + OFFSET_Y);
    glEnd();

	// Make the points
    glPointSize(5.0f);
	glColor3f(0.2111, 0.5025, 0.2864);
    glEnable(GL_POINT_SMOOTH);
	glBegin(GL_POINTS);
	for(int i = 0; i < pointList.size(); i++)
		glVertex2i(pointList[i].first + OFFSET_X,pointList[i].second + OFFSET_Y);

	glEnd();

	glFlush();
}

int main()
{
    // Initialization
    int n;
    char modeInput;

    // Initialize seed for pseudo-random number generator
    srand (time(NULL));

    std::printf("Randomize input?(y/n): ");
    scanf("%c", &modeInput);
    bool randomize = (modeInput=='y' || modeInput == 'Y');
    
    std::printf("Enter points count: ");
    scanf("%d", &n);

    for(int i=1;i<=n;i++)
    {
        int x,y;
        if(randomize)
        {
            x = rand() % 151;
            y = rand() % 151;
        }
        else 
        {
            std::printf("Enter point %d: ", i);
            scanf("%d %d", &x, &y);
        }
        pointList.push_back({x,y});
    }

    printPointList(pointList);

    // Start Timer
    auto start = std::chrono::steady_clock::now();

    // Convex Hull 1: Find furthest left point
    int pivotIndex=0;
    
    // Find minimum index
    for(int i=1;i<pointList.size();i++) if(pointList[pivotIndex].first > pointList[i].first) pivotIndex = i;

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

    auto stop = std::chrono::steady_clock::now();
    auto duration  = std::chrono::duration_cast<std::chrono::nanoseconds>(stop-start);

    std::cout << '\n' << "Time taken: " << duration.count() << " ns\n";

    std::printf("Convex Hull:\n");
    printPointList(result);
    
    int argc = 1;
    glutInit(&argc, NULL);

    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800,800);
    glutCreateWindow("Convex Hull");
    gluOrtho2D (0.0, 200.0, 0.0, 150.0);
    glClearColor(0.0,0.0,0.0,1.0);
    glutDisplayFunc(render);
    glutReshapeFunc(resize);

    glutMainLoop();

}