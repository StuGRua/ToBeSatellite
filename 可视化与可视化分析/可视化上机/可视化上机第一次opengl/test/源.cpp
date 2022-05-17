#include <stdio.h>  
#define GLUT_DISABLE_ATEXIT_HACK  
#include <gl/glut.h>  

GLfloat AngleX;
GLfloat AngleY;

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);//模型和视图变换
    glLoadIdentity();

    glPushMatrix();
    {
        glRotatef(AngleX, 1.0f, 0.0f, 0.0f);
        glRotatef(AngleY, 0.0f, 1.0f, 0.0f);

        glBegin(GL_POLYGON); //前表面  
        glVertex3f(70.0f, 50.0f, 50.0f);

        glVertex3f(70.0f, -50.0f, 50.0f);

        glVertex3f(-70.0f, -50.0f, 50.0f);

        glVertex3f(-70.0f, 50.0f, 50.0f);
        glBegin(GL_LINE_LOOP);

        glColor3ub(10, 160, 240);
        glEnd();



        glBegin(GL_POLYGON); //后表面  
        glVertex3f(70.0f, 50.0f, -50.0f);

        glVertex3f(70.0f, -50.0f, -50.0f);

        glVertex3f(-70.0f, -50.0f, -50.0f);

        glVertex3f(-70.0f, 50.0f, -50.0f);
        glEnd();
        glBegin(GL_LINE_LOOP);

        glColor3ub(1, 20, 180);
        glEnd();

        glBegin(GL_POLYGON); //上表面  
        glVertex3f(70.0f, 50.0f, -50.0f);

        glVertex3f(70.0f, 50.0f, 50.0f);

        glVertex3f(-70.0f, 50.0f, 50.0f);

        glVertex3f(-70.0f, 50.0f, -50.0f);
        glEnd();

        glBegin(GL_LINE_LOOP);

      //  glVertex3f(50.0f, 50.0f, -50.0f);
        glColor3ub(60, 120, 80);
    ////    glVertex3f(50.0f, 50.0f, 50.0f);
    //    glColor3ub(80, 220, 0);
    //   // glVertex3f(-50.0f, 50.0f, 50.0f);
    //    glColor3ub(180, 20, 200);
    // //   glVertex3f(-50.0f, 50.0f, -50.0f);
    //    glColor3ub(180, 20, 200);
        glEnd();


        glBegin(GL_POLYGON); //下表面  

        glVertex3f(70.0f, -50.0f, -50.0f);

        glVertex3f(70.0f, -50.0f, 50.0f);

        glVertex3f(-70.0f, -50.0f, 50.0f);

        glVertex3f(-70.0f, -50.0f, -50.0f);
        glEnd();

        glBegin(GL_LINE_LOOP);

     // // glVertex3f(50.0f, -50.0f, -50.0f);
     //   glColor3ub(120, 120, 80);
     ////   glVertex3f(50.0f, -50.0f, 50.0f);
     //   glColor3ub(20, 20, 180);
     // //  glVertex3f(-50.0f, -50.0f, 50.0f);
     //   glColor3ub(150, 150, 150);
     // //  glVertex3f(-50.0f, -50.0f, -50.0f);
        glColor3ub(100, 50, 50);
        glEnd();

        glBegin(GL_POLYGON); //左表面  
        glVertex3f(70.0f, 50.0f, 50.0f);

        glVertex3f(70.0f, 50.0f, -50.0f);

        glVertex3f(70.0f, -50.0f, -50.0f);

        glVertex3f(70.0f, -50.0f, 50.0f);
        glColor3ub(255, 0, 100);
        glEnd();

        //glBegin(GL_LINE_LOOP);

        //glVertex3f(50.0f, 50.0f, 50.0f);
        //glColor3ub(255, 0, 100);
        //glVertex3f(50.0f, 50.0f, -50.0f);
        //glColor3ub(255, 120, 100);
        //glVertex3f(50.0f, -50.0f, -50.0f);
        //glColor3ub(255, 0, 255);
        //glVertex3f(50.0f, -50.0f, 50.0f);
        //glColor3ub(255, 0, 100);
        //glEnd();

        glBegin(GL_POLYGON); //右表面  

        glVertex3f(-70.0f, 50.0f, 50.0f);


        glVertex3f(-70.0f, 50.0f, -50.0f);


        glVertex3f(-70.0f, -50.0f, -50.0f);
          glColor3ub(255, 255, 0);

        glVertex3f(-70.0f, -50.0f, 50.0f);
        glEnd();

    
    }
    glPopMatrix();


    glutSwapBuffers();
}

void reshape(int w, int h)
{
    GLfloat aspect = (GLfloat)w / (GLfloat)h;
    GLfloat nRange = 100.0f;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION); //将当前矩阵指定为投影模式  
    glLoadIdentity();

    //设置三维投影区  

    if (w <= h)
    {
        glOrtho(-nRange, nRange, -nRange * aspect, nRange * aspect, -nRange, nRange);
    }
    else
    {
        glOrtho(-nRange, nRange, -nRange / aspect, nRange / aspect, -nRange, nRange);
    }
}

void key_board(GLint key, GLint x, GLint y)
{
    if (key == GLUT_KEY_UP)
    {
        AngleX -= 5.0f;
    }
    if (key == GLUT_KEY_DOWN)
    {
        AngleX += 5.0f;
    }
    if (key == GLUT_KEY_LEFT)
    {
        AngleY -= 5.0f;
    }
    if (key == GLUT_KEY_RIGHT)
    {
        AngleY += 5.0f;
    }
    if (AngleX > 355.0f)
    {
        AngleX = 0.0f;
    }
    if (AngleX < 0.0f)
    {
        AngleX = 355.0f;
    }
    if (AngleY > 355.0f)
        AngleY = 0.0f;

    if (AngleY < 0.0f)
    {
        AngleY = 355.0f;
    }
    glutPostRedisplay();
}

void init()
{
    AngleX = 0.0f;
    AngleY = 0.0f;
    glEnable(GL_DEPTH_TEST);//启动深度测试
    glEnable(GL_DITHER);//启用抖动
    glShadeModel(GL_SMOOTH);//
}
void main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(900, 900);
    glutCreateWindow("test");

    glutReshapeFunc(reshape);
    glutDisplayFunc(display);
    glutSpecialFunc(key_board); //设置处理特殊击键的回调函数  

    init();

    glutMainLoop();
}