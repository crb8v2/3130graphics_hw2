#include <iostream>
#include <GL/glut.h>
#include <ctime>

#define MAXOBJS 10

float cam_theta = 45.0;
float xAngle = 0.0;
float yAngle = 0.0;
float h = 0;

struct teapot {
    float color[2];
    float translation[2];
} teapots[MAXOBJS];

void initTeapots(){
    GLint ii;

    srand(time(NULL));

    for(ii = 0; ii < MAXOBJS; ii++){
        teapots[ii].color[0] = (rand() % RAND_MAX) / (float) RAND_MAX;
        teapots[ii].color[1] = (rand() % RAND_MAX) / (float) RAND_MAX;
        teapots[ii].color[2] = (rand() % RAND_MAX) / (float) RAND_MAX;

        teapots[ii].translation[0] = ((float(rand()) / float(RAND_MAX)) * (1 - (-1))) + (-1);
        teapots[ii].translation[1] = ((float(rand()) / float(RAND_MAX)) * (1 - (-1))) + (-1);
        teapots[ii].translation[2] = (rand() % RAND_MAX) / (float) RAND_MAX * 1;
    }
}

void idle() {
    cam_theta += 0.05;

    float xSpeed = 0.5;
    float ySpeed = 1.0;

    xAngle += xSpeed;  yAngle += ySpeed;

    h += 1;
    if (h > 360) h -= 360;

    glutPostRedisplay();
}

void lightsAndCamera(){
    // set the light source properties
    GLfloat lightIntensity[] = {0.7f, 0.7f, 0.7f, 1.0f};
    GLfloat light_position[] = {2.0f, 6.0f, 2.0f, 1.0f};
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightIntensity);


    // set the camera
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0, 640.0 / 480, 1.0, 30.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0, 0.0, 4.0, 0.0, 0.0, 0.0, 0, 1, 0);

}

void drawTeapot(GLint ii){
    glPushMatrix();
    glTranslated(teapots[ii].translation[0], teapots[ii].translation[1], teapots[ii].translation[2] += 0.005);
    glRotated(xAngle,1,0,0);
    glRotated(yAngle,0,1,0);
    glutSolidTeapot(0.08);  // draw the teapot
    glPopMatrix();

//    std::cout << teapots[ii].translation[0] << "  " << teapots[ii].translation[1] << "  " << teapots[ii].translation[1] << std:: endl;

    if(teapots[ii].translation[0] > 4.4 || teapots[ii].translation[1] > 4.4 || teapots[ii].translation[2] > 4.4){
        teapots[ii].translation[0] = ((float(rand()) / float(RAND_MAX)) * (1 - (-1))) + (-1);
        teapots[ii].translation[1] = ((float(rand()) / float(RAND_MAX)) * (1 - (-1))) + (-1);
        teapots[ii].translation[2] = (rand() % RAND_MAX) / (float) RAND_MAX * 2;

            std::cout << teapots[ii].translation[0] << "  " << teapots[ii].translation[1] << "  " << teapots[ii].translation[1] << std:: endl;


    }
}

void wall(double thickness) { // draw thin wall with top = xz-plane, corner at origin
//    glPushMatrix();
//    glTranslated(0.5, 0.5 * thickness,  0.5);
//    glScaled(1.0, thickness, 1.0);
//    glutSolidCube(1.0);
//    glPopMatrix();
}

void drawBackground(){
//    wall(0.02);                  // wall #1: in xz-plane
//    glPushMatrix();
//    glRotated(90.0, 0.0, 0.0, 1.0);
//    wall(0.02);                  // wall #2: in yz-plane
//    glPopMatrix();
//    glPushMatrix();
//    glRotated(-90.0,1.0, 0.0, 0.0);
//    wall(0.02);                  // wall #3: in xy-plane
//    glPopMatrix();
//    glPushMatrix();
//    glRotated(90,0.0, 0.0, 1.0);
//    glTranslated(0.0, -1.0, 0.0);
//    wall(0.02);
//    glPopMatrix();
//    glPushMatrix();
//    glTranslated(0.0, 1.0, 0.0);
//    wall(0.02);                  // wall #2: in yz-plane
//    glPopMatrix();

}

void displaySolid(void) {

    GLint ii;

    //set properties of the surface material
    GLfloat mat_ambient[] = {0.7f, 0.7f, 0.7f, 1.0f}; // gray
    GLfloat mat_diffuse[] = {1.0f, 1.0f, 0.3f, 1.0f};
    GLfloat mat_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat mat_shininess[] = {50.0f};
    glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // lights and camera config
    lightsAndCamera();

    // start drawing
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // clear the screen

    //teapots
    for(ii = 0; ii < MAXOBJS; ii++) {
        mat_diffuse[0] = teapots[ii].color[0], mat_diffuse[1] = teapots[ii].color[1],
            mat_diffuse[2] = teapots[ii].color[2], mat_diffuse[3] = 0.0f;
        glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
        drawTeapot(ii);
    }

    //background
    mat_diffuse[0] = 0.5f, mat_diffuse[1] = 0.5f, mat_diffuse[2] = 0.5f, mat_diffuse[3] = 0.0f;
    glMaterialfv(GL_FRONT,GL_DIFFUSE,mat_diffuse);
    drawBackground();

    glFlush();
    glutSwapBuffers();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE| GLUT_RGB| GLUT_DEPTH);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Shaded 3D scene");


    initTeapots();
    glutIdleFunc(idle);   // causes display func to be called over and over
    glutDisplayFunc(displaySolid);

    glEnable(GL_LIGHTING); // enable the light source
    glEnable(GL_LIGHT0);
    glShadeModel(GL_SMOOTH);
    //glShadeModel(GL_FLAT);
    glEnable(GL_DEPTH_TEST); // for hidden surface removal
    glEnable(GL_NORMALIZE); // normalize vectors for proper shading
    glClearColor(0.1f,0.1f,0.1f,0.0f);  // background is light gray
    glViewport(0, 0, 640, 480);
    glutMainLoop();
}
