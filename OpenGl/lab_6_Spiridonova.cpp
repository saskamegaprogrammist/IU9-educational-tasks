#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glaux.h>
#include <stdlib.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>

#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

float x_0 = 0.f, y_0 = 0.f, z_0 = 0.f;
float nOC = 2.f, nOP = 2.f;
float kX = 0.f, kY = 0.f, kZ = 0.f;
float mX = 0.f, mY = 0.f, mZ = 0.f;
float k = 1;
float t = 0;
GLuint texture;
GLenum mode = GL_LINE;
bool animation = false;
bool texturing = false;
bool increase = true;


static struct vert
{
	float x, y, z;
	float r, g, b;
	vert() {
		x = y = z = 0;
		r = 0.56f;
		g = 0.23f;
		b = 0.63f;
	}
	vert(float x, float y, float z) {
		this->x = x;
		this->y = y;
		this->z = z;
		r = 0.56f;
		g = 0.23f;
		b = 0.63f;
	}
};

static struct face
{
	int c1, p1, c2, p2, c3, p3;
	face() {
		c1 = p1 = c2 = p2 = c3 = p3 = 0;
	}
};

struct Cube {
	struct vert * vertices;
	Cube() {
		vertices = new struct vert[8];
		vertices[7] = vert(0.7f, 0.f, 0.5f);
		vertices[6] = vert(1.f, 0.f, 0.5f);
		vertices[3] = vert(0.7f, -0.25f, 0.5f);
		vertices[2] = vert(1.f, -0.25f, 0.5f);
		vertices[4] = vert(0.7f, 0.f, 0.8f);
		vertices[5] = vert(1.f, 0.f, 0.8f);
		vertices[0] = vert(0.7f, -0.25f, 0.8f);
		vertices[1] = vert(1.f, -0.25f, 0.8f);
	}
	~Cube() {
		delete[]vertices;
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
		createVertices();
	}


	void createVertices() {
		for (auto i = 0; i < this->numberOfCircles; i++) {
			for (auto j = 0; j < this->numberOfPoints; j++) {
				this->vertices[i][j].x = x_0 + this->radius*sin(M_PI*i / (this->numberOfCircles - 1))*cos(2 * M_PI*j / (this->numberOfPoints));
				this->vertices[i][j].y = y_0 + this->radius*sin(M_PI*i / (this->numberOfCircles - 1))*sin(2 * M_PI*j / (this->numberOfPoints));
				this->vertices[i][j].z = z_0 + this->radius*cos(M_PI*i / (this->numberOfCircles - 1));
			}
		}

	}


	void createFaces() {
		int k = 0;
		for (auto i = 1; i < this->numberOfCircles; i++) {
			for (auto j = 0; j < this->numberOfPoints; j++) {
				int z = j + 1;
				if (j == this->numberOfPoints - 1) z = 0;
				this->faces[k].c1 = i; //first face
				this->faces[k].p1 = z;
				this->faces[k].c2 = i;
				this->faces[k].p2 = j;
				this->faces[k].c3 = i - 1;
				this->faces[k].p3 = j;
				k++;

				this->faces[k].c1 = i - 1; //second face
				this->faces[k].p1 = j;
				this->faces[k].c2 = i - 1;
				this->faces[k].p2 = z;
				this->faces[k].c3 = i;
				this->faces[k].p3 = z;
				k++;

			}
		}
		this->numberOfEdges = k;
	}

	float getValue(float first, float last) {
		float middle = last + first / 2;
		float second = first + (2 * (middle - first)) / 3;
		float third = middle + (last - middle) / 3;
		return (1 - t)*(1 - t)*(1 - t)*first + 3 * t*(1 - t)*(1 - t)*second + 3 * t*t*(1 - t)*third + t * t*t*last;
	}

	void twinningVertices() {

		Cube cube = Cube();
		//std::cout << numberOfPoints << std::endl;
		for (auto i = 0; i <this->numberOfCircles ; i++) {
			for (auto j = 0; j< this->numberOfPoints; j++) {
				float delta_y = (0.25f / numberOfCircles)*i;
				int l;
				if ((int)numberOfPoints % 4== 0) {
					l = numberOfPoints / 4;
				}
				else l = numberOfPoints / 4 + 1;
				int sector = j / l;
				if (i > numberOfCircles / 2) {
					sector += 4;
					delta_y = -(delta_y * (numberOfCircles-i)/i);
				}
				int next = sector + 1;
				if (next == 8) next = 5;
				if (next == 4) next = 0;
				
				float delta_x = (cube.vertices[next].x - cube.vertices[sector].x) / l;
				float delta_z = (cube.vertices[next].z - cube.vertices[sector].z) / l;
				this->vertices[i][j].x = getValue(this->vertices[i][j].x, cube.vertices[sector].x + (j% l)*delta_x);
				this->vertices[i][j].y = getValue(this->vertices[i][j].y, cube.vertices[sector].y + delta_y);
				this->vertices[i][j].z = getValue(this->vertices[i][j].z, cube.vertices[sector].z + (j % l)*delta_z);
				//std::cout <<  delta_x << " " <<  delta_y << " " <<  delta_z << std::endl;
				/*this->vertices[i][j].x = getValue(this->vertices[i][j].x, cube.vertices[sector].x );
				this->vertices[i][j].y = getValue(this->vertices[i][j].y, cube.vertices[sector].y );
				this->vertices[i][j].z = getValue(this->vertices[i][j].z, cube.vertices[sector].z );*/
			}
		}
	}

	void texCoord() {
		for (auto i = 0; i < this->numberOfCircles; i++) {
			glBegin(GL_POLYGON);
			for (auto j = 0; j < this->numberOfPoints; j++) {
				glColor3f(this->vertices[i][j].r, this->vertices[i][j].g, this->vertices[i][j].b);
				glVertex3f(this->vertices[i][j].x, this->vertices[i][j].y, this->vertices[i][j].z);
				glNormal3f(-this->vertices[i][j].x, -this->vertices[i][j].y, -this->vertices[i][j].z);
				glTexCoord2f(-this->vertices[i][j].x, -this->vertices[i][j].y);
			}
			glEnd();
		}

	}

	void drawFaces() {
		glBegin(GL_TRIANGLES);
		for (auto k = 0; k < this->numberOfEdges; k++) {
			glColor3f(this->vertices[this->faces[k].c1][this->faces[k].p1].r, this->vertices[this->faces[k].c1][this->faces[k].p1].g, this->vertices[this->faces[k].c1][this->faces[k].p1].b);
			glNormal3f(-this->vertices[this->faces[k].c1][this->faces[k].p1].x, -this->vertices[this->faces[k].c1][this->faces[k].p1].y, -this->vertices[this->faces[k].c1][this->faces[k].p1].z);
			glTexCoord2f(this->vertices[this->faces[k].c1][this->faces[k].p1].x, this->vertices[this->faces[k].c1][this->faces[k].p1].y);
			glVertex3f(this->vertices[this->faces[k].c1][this->faces[k].p1].x, this->vertices[this->faces[k].c1][this->faces[k].p1].y, this->vertices[this->faces[k].c1][this->faces[k].p1].z);
			
			glColor3f(this->vertices[this->faces[k].c2][this->faces[k].p2].r, this->vertices[this->faces[k].c2][this->faces[k].p2].g, this->vertices[this->faces[k].c2][this->faces[k].p2].b);
			glNormal3f(-this->vertices[this->faces[k].c2][this->faces[k].p2].x, -this->vertices[this->faces[k].c2][this->faces[k].p2].y, -this->vertices[this->faces[k].c2][this->faces[k].p2].z);
			glTexCoord2f(this->vertices[this->faces[k].c2][this->faces[k].p2].x, this->vertices[this->faces[k].c2][this->faces[k].p2].y);
			glVertex3f(this->vertices[this->faces[k].c2][this->faces[k].p2].x, this->vertices[this->faces[k].c2][this->faces[k].p2].y, this->vertices[this->faces[k].c2][this->faces[k].p2].z);

			glColor3f(this->vertices[this->faces[k].c3][this->faces[k].p3].r, this->vertices[this->faces[k].c3][this->faces[k].p3].g, this->vertices[this->faces[k].c3][this->faces[k].p3].b);
			glNormal3f(-this->vertices[this->faces[k].c3][this->faces[k].p3].x, -this->vertices[this->faces[k].c3][this->faces[k].p3].y, -this->vertices[this->faces[k].c3][this->faces[k].p3].z);
			glTexCoord2f(this->vertices[this->faces[k].c3][this->faces[k].p3].x, this->vertices[this->faces[k].c3][this->faces[k].p3].y);
			glVertex3f(this->vertices[this->faces[k].c3][this->faces[k].p3].x, this->vertices[this->faces[k].c3][this->faces[k].p3].y, this->vertices[this->faces[k].c3][this->faces[k].p3].z);
		}
		glEnd();
	}


	void drawSphere() {
		createFaces();
		drawFaces();
	}

	void animateSphere() {
		double coef = 0.009;
		if (animation) {
			if (increase)
				t += coef;
			else t -= coef;
			if (t >= 1 || t <= 0)
				increase = !increase;
			twinningVertices();
		}
	}
	

};




void display(GLFWwindow * window)
{

	int screenWidth, screenHeight;
	glfwGetFramebufferSize(window, &screenWidth, &screenHeight);

	float   ratio = screenWidth / (float)screenHeight;
	glClearColor(0.3, 0.3, 0.3, 0.0);

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
	Sphere newSphere = Sphere();
	newSphere.animateSphere();
	newSphere.drawSphere();
	glShadeModel(GL_SMOOTH);
	if (texturing) {
		
		glEnable(GL_TEXTURE_2D);
	}
	else
		glDisable(GL_TEXTURE_2D);
	glPolygonMode(GL_FRONT_AND_BACK, mode);


	glfwSwapBuffers(window);
	glfwPollEvents();
}

void draw(GLFWwindow * window) {

	glEnable(GL_NORMALIZE);
	glEnable(GL_LIGHTING);
	GLfloat material_diffuse[] = { 0.0, 1.0, 0.0, 1.0 }; //цвет объекта
	glMaterialfv(GL_FRONT, GL_DIFFUSE, material_diffuse);

	glEnable(GL_LIGHT0);

	GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
	GLfloat diffuse[] = { 0.4, 0.7, 0.2 };
	GLfloat position[] = { -1.0, 0.0, 1.0, 1.0 };
	GLfloat direction[] = { 1.0, 0.0, -1.0 };
	glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glLightfv(GL_LIGHT0, GL_SPOT_DIRECTION, direction);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 0.0); //убывание интенсивности с расстоянием
	glLightf(GL_LIGHT0, GL_LINEAR_ATTENUATION, 0.2);
	glLightf(GL_LIGHT0, GL_QUADRATIC_ATTENUATION, 0.4);
	glLightf(GL_LIGHT0, GL_SPOT_CUTOFF, 45);
	glLightf(GL_LIGHT4, GL_SPOT_EXPONENT, 15.0); //интенсивность для прожектора

	AUX_RGBImageRec *texture1;
	texture1 = auxDIBImageLoad("C:/Users/Alexis/Downloads/camomreal.bmp");

	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, texture1->sizeX, texture1->sizeY, 0, GL_RGB, GL_UNSIGNED_BYTE, texture1->data);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	

	while (!glfwWindowShouldClose(window))
	{
		display(window);

	}
}

void error(int error, const char * description)
{
	fputs(description, stderr);
}

void load_in() {
	std::ifstream file("./sasha.txt");
	file >> x_0 >> y_0 >> z_0;
	file >> nOC >> nOP; 
	file >> kX >> kY >> kZ;
	file >> mX >> mY >> mZ;
	file >> k >> t;
	file >> animation >> texturing >> increase;
	file.close();
}

void load_out() {
	std::ofstream fout;
	fout.open("./sasha.txt");
	if (fout.is_open()) {
		fout << x_0<< std::endl << y_0 << std::endl<<z_0 <<std::endl <<
		nOC<< std::endl << nOP << std::endl <<
		kX << std::endl << kY << std::endl << kZ << std::endl <<
		mX << std::endl << mY << std::endl << mZ << std::endl <<
		k << std::endl << t << std::endl << 
		animation << std::endl << texturing << std::endl << increase;
	}
	fout.close();
}

void key(GLFWwindow * window, int key, int scancode, int action, int mods)
{
	const GLfloat rotation = 5;
	const GLfloat movement = 0.05f;
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_B:
			load_in();
			break;
		case GLFW_KEY_V:
			load_out();
			break;
		case GLFW_KEY_COMMA:
			if (animation) animation=false;
			else animation = true;
			break;
		case GLFW_KEY_LEFT_BRACKET:
			if (texturing) texturing = false;
			else texturing = true;
			break;
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
			if (nOP != 1.f) {
				nOP--;
				//newSphere = Sphere();
			}
			break;
		case GLFW_KEY_K:
			nOP++;
			//newSphere = Sphere();
			break;
		case GLFW_KEY_U:
			if (nOC != 1.f) {
				nOC--;
				//newSphere = Sphere();
			}
			break;
		case GLFW_KEY_I:
			nOC++;
			//newSphere = Sphere();
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