#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

float kX = 0.f, kY = 0.f;
float mX = 0.f, mY = 0.f;
float k = 1;
GLenum mode = GL_FILL;



static struct vert
{
	float x, y, z;
	float r, g, b;
} vertices[8] =
{
		{ -0.6f, -0.4f, 0.6f, 1.f, 0.f, 0.f },
		{  0.6f, -0.4f, 0.6f, 1.f, 1.f, 0.f },
		{ -0.6f,  0.6f, 0.6f, 1.f, 1.f, 1.f },
		{  0.6f,  0.6f, 0.6f, 0.f, 1.f, 0.f },
		{ -0.6f, -0.4f, -0.6f, 0.f, 1.f, 1.f },
		{  0.6f, -0.4f, -0.6f, 0.f, 0.f, 0.f },
		{ -0.6f,  0.6f, -0.6f, 0.f, 0.f, 1.f },
		{  0.6f,  0.6f, -0.6f, 1.f, 0.f, 1.f },
};

static vert vertices_1[8] = {
{ -1.f, -0.7f, 0.f, 1.f, 0.f, 0.f },
{ -0.7f, -0.7f, 0.f, 1.f, 1.f, 0.f },
{ -1.f,  -0.45f, 0.f, 1.f, 1.f, 1.f },
{ -0.7f,  -0.45f, 0.f, 0.f, 1.f, 0.f },
{ -1.f, -0.7f, -0.3f, 0.f, 1.f, 1.f },
{ -0.7f, -0.7f, -0.3f, 0.f, 0.f, 0.f },
{ -1.f,  -0.45f, -0.3f, 0.f, 0.f, 1.f },
{ -0.7f,  -0.45f, -0.3f, 1.f, 0.f, 1.f },
};


void drawCube(vert vertices[]) {
	glBegin(GL_QUADS);

	//left
	glColor3f(0.56f, 0.23f, 0.63f);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

	glColor3f(0.56f, 0.23f, 0.63f);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);

	glColor3f(0.56f, 0.23f, 0.63f);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

	glColor3f(0.56f, 0.23f, 0.63f);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);
	//upper
	glColor3f(1, 1, 1);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	glColor3f(1, 1, 1);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

	glColor3f(1, 1, 1);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

	glColor3f(1, 1, 1);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);
	//right
	glColor3f(1, 1, 0);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);

	glColor3f(1, 1, 0);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	glColor3f(1, 1, 0);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

	glColor3f(1, 1, 0);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	//bottom
	glColor3f(1, 0, 0);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

	glColor3f(1, 0, 0);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

	glColor3f(1, 0, 0);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);

	glColor3f(1, 0, 0);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);
	//front
	glColor3f(0, 1, 0);
	glVertex3f(vertices[0].x, vertices[0].y, vertices[0].z);

	glColor3f(0, 1, 0);
	glVertex3f(vertices[2].x, vertices[2].y, vertices[2].z);

	glColor3f(0, 1, 0);
	glVertex3f(vertices[3].x, vertices[3].y, vertices[3].z);

	glColor3f(0, 1, 0);
	glVertex3f(vertices[1].x, vertices[1].y, vertices[1].z);

	//back
	glColor3f(0, 0, 1);
	glVertex3f(vertices[4].x, vertices[4].y, vertices[4].z);

	glColor3f(0, 0, 1);
	glVertex3f(vertices[6].x, vertices[6].y, vertices[6].z);

	glColor3f(0, 0, 1);
	glVertex3f(vertices[7].x, vertices[7].y, vertices[7].z);

	glColor3f(0, 0, 1);
	glVertex3f(vertices[5].x, vertices[5].y, vertices[5].z);

	glEnd();
}


void display(GLFWwindow * window)
{

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	float   ratio = screenWidth / (float)screenHeight;


	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // depth testing
	glDepthFunc(GL_LEQUAL);

	glViewport(0.0f, 0.0f, screenWidth, screenHeight); 

	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity(); 
	glOrtho(-ratio, ratio, -1.f, 1.f, 1.f * 3, -1.f * 3);// essentially set coordinate system

	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity(); 


	glScalef(1, 1, -1); //isometria
	glRotatef(35, 1, 0, 0);
	glRotatef(45, 0, 1, 0);


	drawCube(vertices_1); //little cube

	glTranslatef(mX, mY, 0);
	glRotatef(kX, 1, 0, 0);
	glRotatef(kY, 0, 1, 0);
	glScalef(k, k, k);

	glPolygonMode(GL_FRONT_AND_BACK, mode);
	
	drawCube(vertices); //big cube


	glfwSwapBuffers(window);
	glfwPollEvents();
}

void draw(GLFWwindow * window) {
	while (!glfwWindowShouldClose(window))
	{
		display(window);

	}
}

void error(int error, const char * description)
{
	fputs(description, stderr);
}
void key(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	const GLfloat rotation = 5;
	const GLfloat movement = 0.05f;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_UP:
			kX -= rotation;
			break;
		case GLFW_KEY_DOWN:
			kX += rotation;
			break;
		case GLFW_KEY_RIGHT:
			kY += rotation;
			break;
		case GLFW_KEY_LEFT:
			kY -= rotation;
			break;
		case GLFW_KEY_A:
			mX -= movement;
			break;
		case GLFW_KEY_D:
			mX += movement;
			break;
		case GLFW_KEY_W:
			mY += movement;
			break;
		case GLFW_KEY_S:
			mY -= movement;
			break;
		case GLFW_KEY_SPACE:
			k += 0.05;
			break;
		case GLFW_KEY_BACKSPACE:
			k -= 0.05;
			break;
		case GLFW_KEY_TAB:
			if (mode == GL_FILL) {
				mode = GL_LINE;
			}
			else mode = GL_FILL;
			break;
		}
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

int main()
{
	glfwSetErrorCallback(error);

	if (!glfwInit()) return -1;

	GLFWwindow * window = glfwCreateWindow(640, 480, "Simple example", NULL, NULL);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);


	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key);


	draw(window);

	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}