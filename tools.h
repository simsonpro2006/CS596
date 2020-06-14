#ifndef tools_h
#define tools_h
#include <windows.h>  // for MS Windows
#include <GL/glut.h>  // GLUT, include glu.h and gl.h
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#include <iterator>
#include <GL/glu.h>
#include <gl/GL.h>
using namespace std;
const int screenWidth = 900; // width of screen window in pixels
const int screenHeight = 760; // height of screen window in pixels
const int AXIS_X_MAX = 43;
const int AXIS_X_MIN = -1;
const int AXIS_Y_MAX = 23;
const int AXIS_Y_MIN = -21;
enum class cancerPlotState
{
    benign, malignent, none, bothMalignentFirst,bothBenignFirst, opposite, single, singleline
};
enum class pointstate
{
    inside, outside
};
struct boxAttribute
{
    float x1;
    float y1;
    float x2;
    float y2;
};
template <class Container>
void split2(const std::string& str, Container& cont, char delim = ',')
{
    std::stringstream ss(str);
    std::string token;
    while (std::getline(ss, token, delim)) {
        cont.push_back(token);
    }
}



class CancerVisual
{   
    static cancerPlotState currentState;
    static vector<vector<float>> a1;
    static vector<vector<float>> a2;
    static boxAttribute *box; 
    static const int INSIDE = 0; // 0000 
    static const int LEFT = 1; // 0001 
    static const int RIGHT = 2; // 0010 
    static const int BOTTOM = 4; // 0100 
    static const int TOP = 8; // 1000 
    
    
    public:
    static vector<vector<float>> *getVectora1()
    {
        return &a1;
    }
    static vector<vector<float>> *getVectora2()
    {
        return &a2;
    }
    
    static void gettingData()
    {
        ifstream read("cancer.txt");
        string line = "";
        //read>>lines;
        while (getline(read, line))
        {
            vector<string> temp;
            split2<vector<string>>(line, temp);
            if (temp.size() < 11)
                continue;
            vector<float> temp2;
            for (size_t i = 0; i < temp.size(); i++)
                temp2.push_back(stof(temp[i]));
            if (temp2[10] == 2)
            {
                a1.push_back(temp2);
            }
            else if (temp2[10] == 4)
            {
                a2.push_back(temp2);
            }

        }
    }
    static void Setup()
    {
        currentState = cancerPlotState::none;
        gettingData();
        box = new boxAttribute();
    }
    static void graphing(vector<vector<float>>& a1)
    {
        for (int i = 0; i < a1.size(); i++)
        {
            for (int j = 1; j < a1[0].size() - 1; j++)
            {
                glBegin(GL_LINE_STRIP);
                glVertex2f(a1[i][1], 0);
                glVertex2f(a1[i][1], a1[i][2]);
                glVertex2f(10, a1[i][3]);
                glVertex2f(a1[i][4] + 10, 0);
                glVertex2f(a1[i][5] + 20, 0);
                //glVertex2f(a1[0][4], a1[0][5]+20);
                glVertex2f(a1[i][5] + 20, a1[i][6]);
                glVertex2f(a1[i][7] + 30, 0);
                glVertex2f(a1[i][7] + 30, a1[i][8]);
                glVertex2f(40, a1[i][9]);
                glEnd();
                glBegin(GL_LINES);
                glVertex2f(10, 0);
                glVertex2f(10, a1[i][3]);
                glEnd();

            }
        }
    }
    static void AboveGraphOrderly(vector<vector<float>>& a1)
    {
        for (int i = 0; i < a1.size(); i++)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2f(a1[i][1], 0);
            glVertex2f(a1[i][1], a1[i][2]);
            glVertex2f(a1[i][4] + 10, a1[i][3]);
            glVertex2f(a1[i][4] + 10, a1[i][5]);
            glVertex2f(a1[i][7] + 20, a1[i][6]);
            glVertex2f(a1[i][7] + 20, a1[i][8]);
            glVertex2f(a1[i][9] + 30, a1[i][9]);
            glVertex2f(a1[i][9] + 30, 0);
            glEnd();

 
        }
    }
    static void BelowGraphOrderly(vector<vector<float>>& a1)
    {
        for (int i = 0; i < a1.size(); i++)
        {
            glBegin(GL_LINE_STRIP);
            glVertex2f(a1[i][1], 0);
            glVertex2f(a1[i][1], 0-a1[i][2]);
            glVertex2f(a1[i][4] + 10, 0-a1[i][3]);
            glVertex2f(a1[i][4] + 10, 0-a1[i][5]);
            glVertex2f(a1[i][7] + 20, 0-a1[i][6]);
            glVertex2f(a1[i][7] + 20, 0-a1[i][8]);
            glVertex2f(a1[i][9] + 30, 0-a1[i][9]);
            glVertex2f(a1[i][9] + 30, 0);
            glEnd();


        }
    }
    static void Reversegraphing(vector<vector<float>>& a1)
    {
        for (int i = 0; i < a1.size(); i++)
        {
            for (int j = 1; j < a1[0].size() - 1; j++)
            {
                glBegin(GL_LINE_STRIP);
                glVertex2f(a1[i][1], 0);
                glVertex2f(a1[i][1], 0-a1[i][2]);
                glVertex2f(10, 0-a1[i][3]);
                glVertex2f(a1[i][4] + 10, 0);
                glVertex2f(a1[i][5] + 20, 0);
                //glVertex2f(a1[0][4], a1[0][5]+20);
                glVertex2f(a1[i][5] + 20, 0-a1[i][6]);
                glVertex2f(a1[i][7] + 30, 0);
                glVertex2f(a1[i][7] + 30, 0-a1[i][8]);
                glVertex2f(40, 0-a1[i][9]);
                glEnd();
                glBegin(GL_LINES);
                glVertex2f(10, 0);
                glVertex2f(10, 0-a1[i][3]);
                glEnd();

            }
        }
    }
    static void myKeyboard(unsigned char theKey, int mouseX, int mouseY)
    {
        switch (theKey)
        {
        case 'a':
            currentState = cancerPlotState::benign;
            glutPostRedisplay();
            break;
        case 'b':
            currentState = cancerPlotState::malignent;
            glutPostRedisplay();
            break;
        case 'c':
            currentState = cancerPlotState::bothMalignentFirst;
            glutPostRedisplay();
            break;
        case 'd':
            currentState = cancerPlotState::bothBenignFirst;
            glutPostRedisplay();
            break;
        case 'e':
            currentState = cancerPlotState::opposite;
            glutPostRedisplay();
            break;
        case 'f':
            currentState = cancerPlotState::single;
            glutPostRedisplay();
            break;
        case 'g':
            currentState = cancerPlotState::singleline;
            glutPostRedisplay();
            break;

        case 'z':
            exit(-1); //terminate the program
        default:
            break;
        }
    }
    static void drawingArrow(float a, float b)
    {
        glBegin(GL_LINE_STRIP);
        glVertex2f(a - 0.2, 0.2);
        glVertex2f(a, 0);
        glVertex2f(a - 0.2, -0.2);
        glEnd();
    }
    static void drawingBox(float x1, float  y1, float x2, float y2)
    {
        glColor3f(0.0f, 0.0f, 1.0f);
        glLineWidth(2);
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glRectf(x1,y1,x2,y2);
    }
    static void checkBoxp1(float px, float py, float b1x, float b1y, float b2x, float b2y, pointstate &p)
    {
        if (px >= b1x && px <= b2x && py >= b1y && py <= b2y)
        {
            p = pointstate::inside;
            return;
        }
        p = pointstate::outside;
    }
    
    static void myMouse(int button, int state, int x, int y)
    {
        float xscreen = x / (float)screenWidth
            * (AXIS_X_MAX - AXIS_X_MIN) + AXIS_X_MIN;
        float yscreen = (1 - y / (float)screenHeight)
            * (AXIS_Y_MAX - AXIS_Y_MIN) + AXIS_Y_MIN;
        static int stateofMouse = 0;
        if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
        {
            if (stateofMouse == 0)
            {
                box->x1 = xscreen;
                box->y1 = yscreen;
                stateofMouse = 1;
                glutPostRedisplay();
                
            }
            else
            {
                box->x2 = xscreen;
                box->y2 = yscreen;
                stateofMouse = 0;
                glutPostRedisplay();
                
            }
            if (box->x1 > box->x2)
            {
                float temp = box->x1;
                box->x1 = box->x2;
                box->x2 = temp;
            }
            if (box->y1 > box->y2)
            {
                float temp = box->y1;
                box->y1 = box->y2;
                box->y2 = temp;
            }
            int howmanylinesa1 = 0;
            int howmanylinesa2 = 0;
            howmanylinesa1 = CancerVisual::Howmanylines(*CancerVisual::getVectora1());
            howmanylinesa2 = CancerVisual::Howmanylines(*CancerVisual::getVectora2());
            
            cout <<"number of line in box 1: "<< howmanylinesa1 << endl;
            cout << "number of line in box 2: " << howmanylinesa2 << endl;

            
        } 
        else if (button == GLUT_RIGHT_BUTTON && state == GLUT_DOWN)
            exit(-1);
    }
    static int computeCode(double x, double y)
    {
        // initialized as being inside 
        int code = INSIDE;

        if (x < box->x1) // to the left of rectangle 
            code |= LEFT;
        else if (x > box->x2) // to the right of rectangle 
            code |= RIGHT;
        if (y < box->y1) // below the rectangle 
            code |= BOTTOM;
        else if (y > box->y2) // above the rectangle 
            code |= TOP;

        return code;
    }

    // Implementing Cohen-Sutherland algorithm 
    // Clipping a line from P1 = (x2, y2) to P2 = (x2, y2) 
    static bool cohenSutherlandClip(double x1, double y1,
        double x2, double y2)
    {
        // Compute region codes for P1, P2 
        int code1 = computeCode(x1, y1);
        int code2 = computeCode(x2, y2);

        // Initialize line as outside the rectangular window 
        bool accept = false;

        while (true) {
            if ((code1 == 0) && (code2 == 0)) {
                // If both endpoints lie within rectangle 
                accept = true;
                break;
            }
            else if (code1 & code2) {
                // If both endpoints are outside rectangle, 
                // in same region 
                break;
            }
            else {
                // Some segment of line lies within the 
                // rectangle 
                int code_out;
                double x, y;

                // At least one endpoint is outside the 
                // rectangle, pick it. 
                if (code1 != 0)
                    code_out = code1;
                else
                    code_out = code2;

                // Find intersection point; 
                // using formulas y = y1 + slope * (x - x1), 
                // x = x1 + (1 / slope) * (y - y1) 
                if (code_out & TOP) {
                    // point is above the clip rectangle 
                    x = x1 + (x2 - x1) * (box->y2 - y1) / (y2 - y1);
                    y = box->y2;
                }
                else if (code_out & BOTTOM) {
                    // point is below the rectangle 
                    x = x1 + (x2 - x1) * (box->y1 - y1) / (y2 - y1);
                    y = box->y1;
                }
                else if (code_out & RIGHT) {
                    // point is to the right of rectangle 
                    y = y1 + (y2 - y1) * (box->x2 - x1) / (x2 - x1);
                    x = box->x2;
                }
                else if (code_out & LEFT) {
                    // point is to the left of rectangle 
                    y = y1 + (y2 - y1) * (box->x1 - x1) / (x2 - x1);
                    x = box->x1;
                }

                // Now intersection point x, y is found 
                // We replace point outside rectangle 
                // by intersection point 
                if (code_out == code1) {
                    x1 = x;
                    y1 = y;
                    code1 = computeCode(x1, y1);
                }
                else {
                    x2 = x;
                    y2 = y;
                    code2 = computeCode(x2, y2);
                }
            }
        }
        if (accept) {
            return true;
        }
        else
            return false;
    }

    static void myDisplay(void)
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glColor3f(0.0, 0.0, 0.0);
        glLineWidth(2);
        glBegin(GL_LINE_STRIP);

        glVertex2f(0, 10);
        glVertex2f(0, 0);
        glVertex2f(10, 0);
        glVertex2f(20, 0);
        glVertex2f(30, 0);
        glVertex2f(40, 0);
        glEnd();
        drawingArrow(10, 0);
        drawingArrow(20, 0);
        drawingArrow(30, 0); //drawing arrow for x coordinate
        drawingArrow(40, 0);
 
        glBegin(GL_LINE_STRIP);
        glVertex2f(-0.2, 9.8);
        glVertex2f(0, 10);
        glVertex2f(0.2, 9.8);
        glEnd();// drawing arrow for y coordinate
        drawingBox(box->x1, box->y1, box->x2, box->y2);
        if (currentState == cancerPlotState::benign)
        {
           
            glColor3f(1.0, 0.0, 1.0);
            AboveGraphOrderly(a1);
        }
        else if (currentState == cancerPlotState::malignent)
        {
            
            glColor3f(0.0, 1.0, 0.0);
            AboveGraphOrderly(a2);
        }
        else if (currentState ==cancerPlotState::bothMalignentFirst)
        {
            glColor3f(1.0, 0.0, 1.0);
            AboveGraphOrderly(a1);
            glColor3f(0.0, 1.0, 0.0);
            AboveGraphOrderly(a2);
        }
        else if (currentState == cancerPlotState::bothBenignFirst)
        {
            glColor3f(0.0, 1.0, 0.0);
            AboveGraphOrderly(a2);
            glColor3f(1.0, 0.0, 1.0);
            AboveGraphOrderly(a1);
            
        }
        else if (currentState == cancerPlotState::opposite)
        {
            
            glColor3f(0.0, 1.0, 0.0);
            BelowGraphOrderly(a2);
            glColor3f(1.0, 0.0, 1.0);
            AboveGraphOrderly(a1);
            

        }
        else if (currentState == cancerPlotState::single)
        {

            //glColor3f(1.0, 0.0, 1.0);
            //SingleGraph(a1);
            glColor3f(0.0, 1.0, 0.0);
            BelowGraphOrderly(a2);
            glColor3f(1.0, 0.0, 1.0);
            AboveGraphOrderly(a1);
            
        }
        drawingBox(box->x1, box->y1, box->x2, box->y2);



        glFlush(); // send all output to display

    }
    static int Howmanylines(vector<vector<float>>& a1)
    {
        int howmanylines = 0;
       
        for (int i = 0; i < a1.size(); i++)
        {
            pointstate p1 = pointstate::outside;
            pointstate p2 = pointstate::outside;
            pointstate p3 = pointstate::outside;
            pointstate p4 = pointstate::outside;
            pointstate p5 = pointstate::outside;
            pointstate p6 = pointstate::outside;
            pointstate p7 = pointstate::outside;
            pointstate p8 = pointstate::outside;
            pointstate p9 = pointstate::outside;
            pointstate p10 = pointstate::outside;
            checkBoxp1(a1[i][1], 0, box->x1, box->y1, box->x2, box->y2,p1);//1
            checkBoxp1(a1[i][1], a1[i][2], box->x1, box->y1, box->x2, box->y2, p2);//2
            checkBoxp1(a1[i][4] + 10, a1[i][3], box->x1, box->y1, box->x2, box->y2, p3);//3
            checkBoxp1(a1[i][4] + 10, 0, box->x1, box->y1, box->x2, box->y2, p4);//4
            checkBoxp1(a1[i][4] + 10, a1[i][5], box->x1, box->y1, box->x2, box->y2, p5);//5
            checkBoxp1(a1[i][7] + 20, a1[i][6], box->x1, box->y1, box->x2, box->y2, p6);//6
            checkBoxp1(a1[i][7] + 20, 0, box->x1, box->y1, box->x2, box->y2, p7);//7
            checkBoxp1(a1[i][7] + 20, a1[i][8], box->x1, box->y1, box->x2, box->y2, p8);//8
            checkBoxp1(a1[i][9] + 30, a1[i][9], box->x1, box->y1, box->x2, box->y2, p9);//9
            checkBoxp1(a1[i][9] + 30, 0, box->x1, box->y1, box->x2, box->y2, p10);//10
            if (p1 == pointstate::inside || p2 == pointstate::inside || p3 == pointstate::inside || p4 == pointstate::inside || p5 == pointstate::inside || p6 == pointstate::inside || p7 == pointstate::inside || p8 == pointstate::inside || p9 == pointstate::inside || p10 == pointstate::inside)
            {
                howmanylines += 1;
            }
        }
        return howmanylines;

    }
};

vector<vector<float>> CancerVisual::a2;
boxAttribute *CancerVisual::box = nullptr;

cancerPlotState CancerVisual::currentState= cancerPlotState::none;
vector<vector<float>> CancerVisual::a1;




#endif
