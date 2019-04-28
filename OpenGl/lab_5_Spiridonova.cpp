#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>

using namespace std;


#define SCREEN_WIDTH 640
#define SCREEN_HEIGHT 480

struct coord {
	double x, y;
	int index = -1;
	int edge = 0;
};

struct coord lines[2];
struct coord polygon[1000];
struct coord intersects[1000];
struct coord normal;
struct coord direction;

double xpos, ypos;
int size_H ;
int size_W ;

bool intersectOn = false;
int current = 0;
int current_2 = 0;
int number = 0;
int line = 0;
int interCurrent = 0;

bool compare_x(const coord &coord1, const coord  &coord2) {
	return (coord1.x > coord2.x);
}

bool compare_y(const coord &coord1, const coord &coord2) {
	return (coord1.y > coord2.y);
}


void merge(coord* coords, int l, int m, int h, bool(*compare)(const coord&, const coord&)) {
	coord * array = new coord[h - l + 1];
	int i = l;
	int j = m + 1;
	for (auto k = 0; k < (h - l + 1); k++) {
		if (j <= h && (i == (m + 1) || compare(coords[i], coords[j]))) {
			array[k] = coords[j];
			j++;
		}
		else {
			array[k] = coords[i];
			i++;
		}
	}
	for (auto i = l; i < h + 1; i++) {
		coords[i] = array[i - l];
	}
	delete[] array;
}

void mergeSort(coord* coords, int l, int h, bool(*compare) (const coord&, const coord&)) {
	if (l < h) {
		int m = (l + h) / 2;
		mergeSort(coords, l, m, compare);
		mergeSort(coords, m + 1, h, compare);
		merge(coords, l, m, h, compare);
	}
}

double scalMult(struct coord f, struct coord s) {
	return (f.x*s.x + f.y*s.y);
}

void intersect(int i) {
	int back;
	if (i == 0) back = current_2 - 1;
	else back = i - 1;

	struct coord normalI;
	struct coord directionI;
	struct coord Point;

	normalI.x = polygon[back].y - polygon[i].y;
	normalI.y = polygon[i].x - polygon[back].x;

	directionI.x = polygon[i].x - polygon[back].x;
	directionI.y = polygon[i].y - polygon[back].y;

	Point.x = polygon[back].x - lines[0].x;
	Point.y = polygon[back].y - lines[0].y;

	double t, tabs;
	double u, uabs;

	if (scalMult(direction, normalI) != 0) {
		t = scalMult(Point, normalI) / scalMult(direction, normalI);
		u = scalMult(Point, normal) / scalMult(direction, normalI);

		//cout << t << " " << u << endl;

		if (t <= 1 && t >= 0 && u <= 1 && u >= 0) {
			intersects[interCurrent].x = lines[0].x + t * direction.x;
			intersects[interCurrent].y = lines[0].y + t * direction.y;
			//cout << intersects[interCurrent].x << " " << intersects[interCurrent].y << endl;
			interCurrent++;
		}
	}
}


void drawL() {
	if (line > 1) {
		glLineWidth(1);
		glBegin(GL_LINES);
		glColor3f(1.f, 0.f, 0.f);
		glVertex3f(lines[0].x, lines[0].y, 0.f);
		glVertex3f(lines[1].x, lines[1].y, 0.f);
		glEnd();
	}
}

void drawIntersects() {
	if (interCurrent == 0) {
		normal.x = lines[0].y;
		normal.y = -lines[0].x;

		direction.x = -lines[0].x;
		direction.y = -lines[0].y;
		for (auto i = 0; i < current_2; i++) {
			intersect(i);
		}
		if (interCurrent % 2 != 0) drawL();
		interCurrent = 0;
	}
	else {
		glLineWidth(1);
		glBegin(GL_LINES);
		for (int i = 0; i < interCurrent; i += 2) {
			glColor3f(1.f, 0.f, 0.f);
			glVertex3f(intersects[i].x, intersects[i].y, 0.f);
			glVertex3f(intersects[i + 1].x, intersects[i + 1].y, 0.f);
		}
		glEnd();
	}
}

void cut() {
	if (interCurrent == 0) {
		normal.x = lines[0].y - lines[1].y;
		normal.y = lines[1].x - lines[0].x;

		direction.x = lines[1].x - lines[0].x;
		direction.y = lines[1].y - lines[0].y;

		for (auto i = 0; i < current_2; i++) {
			intersect(i);

		}

		mergeSort(intersects, 0, interCurrent - 1, compare_x);
	}
}

void makePolygon() {
	if (number > current_2) {
		polygon[current_2].x = xpos;
		polygon[current_2].y = size_H - ypos;
		current_2++;
	}
}

void makeline() {
	if (line > current) {
		lines[current].x = xpos;
		lines[current].y = size_H- ypos;
		current++;
	}
}

void drawPolygon() {
	glLineWidth(1);
	glBegin(GL_LINES);
	for (int i = 0; i < current_2; i++) {
		int back;
		if (i == 0) back = current_2 - 1;
		else back = i - 1;
		glColor3f(1.f, 1.f, 0.f);
		glVertex3f(polygon[i].x, polygon[i].y, 0.f);
		glVertex3f(polygon[back].x, polygon[back].y, 0.f);
	}
	glEnd();
}


void display(GLFWwindow * window)
{
	glfwGetFramebufferSize(window, &size_W, &size_H);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST); // depth testing
	glDepthFunc(GL_LEQUAL);

	glViewport(0.0f, 0.0f, size_W, size_H);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0, size_W, 0, size_H, 0, 1); // essentially set coordinate system

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	makeline();
	makePolygon(); 
	if (intersectOn) {
		cut();
		drawIntersects();
	}
	else drawL();
	drawPolygon();

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
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_TAB:
			intersectOn = true;
			break;
		}
	}

	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void button(GLFWwindow* window, int button, int action, int mods) {
	if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
		glfwGetCursorPos(window, &xpos, &ypos);
		if (line <=1) line++;
		else number++;
	}
}

void windowSize(GLFWwindow* window, int width, int height) {
	glfwGetWindowSize(window, &size_W, &size_H);
	width = size_W;
	height = size_H;
}

int main()
{
	glfwSetErrorCallback(error);
	if (!glfwInit()) return -1;
	GLFWwindow * window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "LABA_5", NULL, NULL);
	glfwSetInputMode(window, GLFW_STICKY_KEYS, 1);

	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glDrawBuffer(GL_BACK);
	glfwMakeContextCurrent(window);
	glfwSetKeyCallback(window, key);
	glfwSetWindowSizeCallback(window, windowSize);
	glfwSetMouseButtonCallback(window, button);
	glRasterPos2f(0, 0);
	glClearColor(0, 0, 0, 0);

	draw(window);
	glfwDestroyWindow(window);
	glfwTerminate();

	return 0;
}