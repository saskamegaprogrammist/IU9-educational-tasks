#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

float x_0 = 0.f, y_0 = 0.f, z_0 = 0.f;
float nOC = 2.f, nOP = 2.f;
float kX = 0.f, kY = 0.f, kZ = 0.f;
float mX = 0.f, mY = 0.f, mZ=0.f;
float k = 1;
GLenum mode = GL_LINE;

static struct vert
{
	float x, y, z;
	float r, g, b;
	vert() {
		x = y = z = r = b = g = 0;
	}
};

static struct face
{
	int c1, p1, c2, p2, c3, p3;
	face() {
		c1 = p1 = c2 = p2 = c3 = p3 = 0;
	}
};


class Sphere {
public:
	~Sphere() {
		for (auto i = 0; i < numberOfCircles; i++) {
			delete[] vertices[i];
		}
		delete[]vertices;
		delete[] faces;
		//return true;
		
	}
	float numberOfCircles;
	float numberOfPoints;
	float numberOfEdges;
	float radius = 1.f;
	struct vert ** vertices;
	struct face * faces;
	Sphere() {
		numberOfCircles = nOC + 1;
		numberOfPoints = nOP;
		numberOfEdges = 2 * numberOfPoints*numberOfCircles;
		vertices = new struct vert *[numberOfCircles];
		for (auto i = 0; i < numberOfCircles; i++) {
			vertices[i] = new struct vert[numberOfPoints];
			for (auto j = 0; j < numberOfPoints; j++) {
				vertices[i][j] = vert();
			}
		}
		faces = new struct face[numberOfEdges];
		for (auto i = 0; i < numberOfEdges; i++) {
			faces[i] = face();
		}
	}
	
};

void createVertices(Sphere* sphere) {
	for (auto i = 0; i < sphere->numberOfCircles; i++) {
		for (auto j = 0; j < sphere->numberOfPoints; j++) {
			sphere->vertices[i][j].x = x_0 + sphere->radius*sin(M_PI*i / (sphere->numberOfCircles- 1))*cos(2 * M_PI*j / (sphere->numberOfPoints));
			sphere->vertices[i][j].y = y_0 + sphere->radius*sin(M_PI*i / (sphere->numberOfCircles - 1))*sin(2 * M_PI*j / (sphere->numberOfPoints));
			sphere->vertices[i][j].z = z_0 + sphere->radius*cos(M_PI*i / (sphere->numberOfCircles - 1));
			sphere->vertices[i][j].r = 2.55f*(i+1) *(j+1)/ ((sphere->numberOfCircles)* sphere->numberOfPoints);
			sphere->vertices[i][j].g = 0.17f*(i + 1) *(j + 1) / ((sphere->numberOfCircles)* sphere->numberOfPoints);
			sphere->vertices[i][j].b = 2.39f*(i + 1) *(j + 1) / ((sphere->numberOfCircles)* sphere->numberOfPoints);
		}
	}

}

void createFaces(Sphere* sphere) {
	int k = 0;
	for (auto i = 1; i < sphere->numberOfCircles; i++) {
		for (auto j = 0; j < sphere->numberOfPoints; j++) {
			int z = j + 1;
			if (j == sphere->numberOfPoints - 1) z = 0;
			sphere->faces[k].c1 = i; //first face
			sphere->faces[k].p1 = z;
			sphere->faces[k].c2 = i;
			sphere->faces[k].p2 = j;
			sphere->faces[k].c3 = i-1;
			sphere->faces[k].p3 = j;
			k++;

			sphere->faces[k].c1 = i-1; //second face
			sphere->faces[k].p1 = j;
			sphere->faces[k].c2 = i - 1;
			sphere->faces[k].p2 = z;
			sphere->faces[k].c3 = i;
			sphere->faces[k].p3 = z;
			k++;

		}
	}
	sphere->numberOfEdges = k;
}

void drawFaces(Sphere* sphere) {
	glBegin(GL_TRIANGLES);
	for (auto k = 0; k < sphere->numberOfEdges; k++) {
		glColor3f(sphere->vertices[sphere->faces[k].c1][sphere->faces[k].p1].r, sphere->vertices[sphere->faces[k].c1][sphere->faces[k].p1].g, sphere->vertices[sphere->faces[k].c1][sphere->faces[k].p1].b);
		glVertex3f(sphere->vertices[sphere->faces[k].c1][sphere->faces[k].p1].x, sphere->vertices[sphere->faces[k].c1][sphere->faces[k].p1].y, sphere->vertices[sphere->faces[k].c1][sphere->faces[k].p1].z);
		
		glColor3f(sphere->vertices[sphere->faces[k].c2][sphere->faces[k].p2].r, sphere->vertices[sphere->faces[k].c2][sphere->faces[k].p2].g, sphere->vertices[sphere->faces[k].c2][sphere->faces[k].p2].b);
		glVertex3f(sphere->vertices[sphere->faces[k].c2][sphere->faces[k].p2].x, sphere->vertices[sphere->faces[k].c2][sphere->faces[k].p2].y, sphere->vertices[sphere->faces[k].c2][sphere->faces[k].p2].z);
		
		glColor3f(sphere->vertices[sphere->faces[k].c3][sphere->faces[k].p3].r, sphere->vertices[sphere->faces[k].c3][sphere->faces[k].p3].g, sphere->vertices[sphere->faces[k].c3][sphere->faces[k].p3].b);
		glVertex3f(sphere->vertices[sphere->faces[k].c3][sphere->faces[k].p3].x, sphere->vertices[sphere->faces[k].c3][sphere->faces[k].p3].y, sphere->vertices[sphere->faces[k].c3][sphere->faces[k].p3].z);
	}
	glEnd();
}


void drawSphere() {
	Sphere newSphere = Sphere();
	createVertices(&newSphere);
	createFaces(&newSphere);
	drawFaces(&newSphere);
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


	

	glTranslatef(mX, mY, mZ);
	glRotatef(kX, 1, 0, 0);
	glRotatef(kY, 0, 1, 0);
	glRotatef(kZ, 0, 0, 1);
	
	glScalef(k, k, k);

	drawSphere();

	glPolygonMode(GL_FRONT_AND_BACK, mode);


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
		case GLFW_KEY_Z:
			kZ -= rotation;
			break;
		case GLFW_KEY_X:
			kZ += rotation;
			break;
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
		case GLFW_KEY_Q:
			mZ += movement;
			break;
		case GLFW_KEY_E:
			mZ -= movement;
			break;
		case GLFW_KEY_SPACE:
			k += 0.05;
			break;
		case GLFW_KEY_BACKSPACE:
			k -= 0.05;
			break;
		case GLFW_KEY_J:
			if (nOP != 1.f) nOP--;
			break;
		case GLFW_KEY_K:
			nOP++;
			break;
		case GLFW_KEY_U:
			if (nOC!=1.f) nOC--;
			break;
		case GLFW_KEY_I:
			nOC++;
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