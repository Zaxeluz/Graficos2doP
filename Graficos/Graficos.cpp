// Graficos.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#define GLEW_STATIC
#include "GL\glew.h"
#include "GLFW\glfw3.h"

#include "glm\gtx\transform.hpp"
#include "glm\glm.hpp"
#include <iostream>

#include "Vertice.h"
#include "Shader.h"
#include "Modelo.h"

#include <math.h>

using namespace std;

GLfloat red, green, blue;
GLuint posicionID;
GLuint colorID;
GLuint transformacionesID;

Modelo *pagaro;
Modelo *techo;
Modelo *estructura;
Modelo *puerta;
Modelo *ventana;

Shader *shader;
//Declaración de Ventana
GLFWwindow *window;

void actualizar()
{
	pagaro->transformaciones = translate(pagaro->transformaciones, vec3(-0.0001f, 0.0f, 0.0f));
	pagaro->transformaciones = rotate(pagaro->transformaciones, 0.0003f, vec3(0.0f, 1.0f, 0.0f));
}

void dibujar()
{
	techo->dibujar(GL_POLYGON);
	estructura->dibujar(GL_QUADS);
	puerta->dibujar(GL_QUADS);
	ventana->dibujar(GL_QUADS);
	pagaro->dibujar(GL_POLYGON);
}

void inicializarPagaro()
{
	pagaro = new Modelo();
	Vertice v1 =
	{ vec4(-0.05f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v2 =
	{ vec4(0.05f, 0.05f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v3 =
	{ vec4(-0.02f, 0.0f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v4 =
	{ vec4(0.05f, -0.05f, 0.0f, 1.0f), vec4(0.0f, 1.0f, 1.0f, 1.0f) };

	pagaro->vertices.push_back(v1);
	pagaro->vertices.push_back(v2);
	pagaro->vertices.push_back(v3);
	pagaro->vertices.push_back(v4);

}
void inicializarCasa()
{
	estructura = new Modelo();
	Vertice v1 =
	{ vec4(-1.0f, -1.0f, 0.0f,1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f) };
	Vertice v2 =
	{ vec4(-1.0f, -0.5f, 0.0f,1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f) };
	Vertice v3 =
	{ vec4(-0.4f, -0.5f, 0.0f,1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f) };
	Vertice v4 =
	{ vec4(-0.4f, -1.0f, 0.0f,1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f) };

	estructura->vertices.push_back(v1);
	estructura->vertices.push_back(v2);
	estructura->vertices.push_back(v3);
	estructura->vertices.push_back(v4);

	puerta = new Modelo();
	Vertice v5 =
	{ vec4(-0.75f, -1.0f, 0.0f,1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v6 =
	{ vec4(-0.75f, -0.7f, 0.0f,1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v7 =
	{ vec4(-0.65f, -0.7f, 0.0f,1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v8 =
	{ vec4(-0.65f, -1.0f, 0.0f,1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };

	puerta->vertices.push_back(v5);
	puerta->vertices.push_back(v6);
	puerta->vertices.push_back(v7);
	puerta->vertices.push_back(v8);

	ventana = new Modelo();
	Vertice v9 =
	{ vec4(-0.9f, -0.9f, 0.0f,1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v10 =
	{ vec4(-0.9f, -0.65f, 0.0f,1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v11 =
	{ vec4(-0.79f, -0.65f, 0.0f,1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };
	Vertice v12 =
	{ vec4(-0.79f, -0.9f, 0.0f,1.0f), vec4(1.0f, 1.0f, 1.0f, 1.0f) };

	ventana->vertices.push_back(v9);
	ventana->vertices.push_back(v10);
	ventana->vertices.push_back(v11);
	ventana->vertices.push_back(v12);

	techo = new Modelo();
	Vertice v13 =
	{ vec4(-1.0f, -0.5f, 0.0f,1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f) };
	Vertice v14 =
	{ vec4(-0.7f, -0.2f, 0.0f,1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f) };
	Vertice v15 =
	{ vec4(-0.4f, -0.5f, 0.0f,1.0f), vec4(0.0f, 0.0f, 0.0f, 1.0f) };

	techo->vertices.push_back(v13);
	techo->vertices.push_back(v14);
	techo->vertices.push_back(v15);
}


int main()
{
	
	//Propiedades de la ventana
	GLfloat ancho = 1024;
	GLfloat alto = 600;

	//Inicialización de GLFW
	if (!glfwInit())
	{
		//Si no se inicia bien termina la ejecución
		exit(EXIT_FAILURE);
	}

	//Inicialización de la ventana
	window = glfwCreateWindow(ancho, alto, "Gráficos", NULL, NULL);

	//Verificación de creación de ventana
	if (!window)
	{
		//Cerrar todos los procesos de GLFW
		glfwTerminate();
		//Termina ejecución
		exit(EXIT_FAILURE);
	}
	
	//Establecer "windows" como contexto
	glfwMakeContextCurrent(window);

	//Se trae las funciones de OpenGL Moderno
	glewExperimental = true;

	//Inicializar GLEW
	GLenum glewError = glewInit();

	//Verificar si GLEW se inicializo bien
	if (glewError != GLEW_OK)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	const GLubyte *version = glGetString(GL_VERSION);
	cout << "Version de OpenGL:" << version << endl;

	red = 0.0f, green = 0.5f, blue = 0.9f;

	inicializarPagaro();
	inicializarCasa();

	//Crear instancia del shader
	const char * rutaVertex = "vShaderSimple.shader";
	const char * rutaFragment = "fShaderSimple.shader";

	shader = new Shader(rutaVertex, rutaFragment);

	//Mapeo de atributos
	posicionID = glGetAttribLocation(shader->getID(), "posicion");
	colorID = glGetAttribLocation(shader->getID(), "color");
	transformacionesID = glGetUniformLocation(shader->getID(), "transformaciones");

	//Desenlazar shader
	shader->desenlazarShader();

	techo->shader = shader;
	techo->inicializarVertexArray(posicionID, colorID, transformacionesID);

	estructura->shader = shader;
	estructura->inicializarVertexArray(posicionID, colorID, transformacionesID);

	puerta->shader = shader;
	puerta->inicializarVertexArray(posicionID, colorID, transformacionesID);

	ventana->shader = shader;
	ventana->inicializarVertexArray(posicionID, colorID, transformacionesID);
	
	pagaro->shader = shader;
	pagaro->inicializarVertexArray(posicionID, colorID, transformacionesID);

	//Ciclo de Dibujo
	while (!glfwWindowShouldClose(window))
	{
		//Establecer el area de render (viewport)
		glViewport(0, 0, ancho, alto);
		//Establecer el color con el que se limpia
		glClearColor(red, green, blue, 1);

		//Limpiar pantalla
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		//Rutina de Dibujo
		actualizar();
		dibujar();

		//Intercambio de Buffers
		glfwSwapBuffers(window);
		//Buscar nueva señal de entrada
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate();
    return 0;
}

