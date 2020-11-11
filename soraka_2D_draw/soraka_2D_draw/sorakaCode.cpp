/*---------------------------------------------------------*/
/* ----------------   Práctica 2 --------------------------*/
/*-----------------    2021-1   ---------------------------*/
/*------------- Alfonso Murrieta Villegas ---------------*/
#include <glew.h>
#include <glfw3.h>

#include <iostream>

void resize(GLFWwindow* window, int width, int height);
void my_input(GLFWwindow *window);

// settings
// Window size
int SCR_WIDTH = 600;
int SCR_HEIGHT = 600;

GLFWmonitor *monitors;
GLuint VBO, VAO, EBO;
GLuint shaderProgramRed, shaderProgramColor;

static const char* myVertexShader = "										\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
																			\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);							\n\
}";

static const char* myVertexShaderColor = "									\n\
#version 330 core															\n\
																			\n\
layout (location = 0) in vec3 aPos;											\n\
layout (location = 1) in vec3 aColor;										\n\
out vec3 ourColor;															\n\
void main()																	\n\
{																			\n\
    gl_Position = vec4(aPos, 1.0);											\n\
	ourColor = aColor;														\n\
}";

// Fragment Shader
static const char* myFragmentShaderRed = "									\n\
#version 330																\n\
																			\n\
out vec3 finalColor;														\n\
																			\n\
void main()																	\n\
{																			\n\
    finalColor = vec3(1.0f, 0.0f, 0.0f);									\n\
}";

static const char* myFragmentShaderColor = "								\n\
#version 330 core															\n\
out vec4 FragColor;															\n\
in vec3 ourColor;															\n\
																			\n\
void main()																	\n\
{																			\n\
	FragColor = vec4(ourColor, 1.0f);										\n\
}";

void myData(void);
void setupShaders(void);
void display(void);
void getResolution(void);


void getResolution()
{
	const GLFWvidmode * mode = glfwGetVideoMode(glfwGetPrimaryMonitor());

	SCR_WIDTH = 1000;
	SCR_HEIGHT = 1000;
}

void myData(){
	float escala = 3.0f;
	float escalaColor = 0.255f;
	//faceColor
	float face_R = 0.242 / escalaColor,
		  face_G = 0.227 / escalaColor,
		  face_B = 0.224 / escalaColor;

	float whiteRGB = 0.242 / escalaColor;
	float eyeR_2 = 0.138 / escalaColor,
		  eyeG_2 = 0.145 / escalaColor,
		  eyeB_2 = 0.125 / escalaColor;

	float eyeR = 0.165 / escalaColor,
		eyeG = 0.187 / escalaColor,
		eyeB = 0.129 / escalaColor;

	float hairR = 0.163 / escalaColor,
		  hairG = 0.192 / escalaColor,
		  hairB = 0.188 / escalaColor;

	float hairR2 = 0.170 / escalaColor,
		  hairG2 = 0.200 / escalaColor,
		  hairB2 = 0.195 / escalaColor;

	float alasR = 0.237 / escalaColor,
		  alasG = 0.237 / escalaColor,
		  alasB = 0.237 / escalaColor;

	float   cuarnoR = 0.218 / escalaColor,
			cuarnoG = 0.196 / escalaColor,
			cuarnoB = 0.125 / escalaColor;

	float   facialR = 0.234 / escalaColor,
			facialG = 0.179 / escalaColor,
			facialB = 0.171 / escalaColor;

	float   estrellaR = 0.224 / escalaColor,
			estrellaG = 0.215 / escalaColor,
			estrellaB = 0.130 / escalaColor;

	float   estrellaR_2 = 0.204 / escalaColor,
		    estrellaG_2 = 0.171 / escalaColor,
		    estrellaB_2 = 0.057 / escalaColor;
	
	float   blueR = 0.162 / escalaColor,
			blueG = 0.207 / escalaColor,
			blueB = 0.228 / escalaColor;

	float   pestaR = 0.064 / escalaColor,
			pestaG = 0.014 / escalaColor,
			pestaB = 0.014 / escalaColor;


	float   auxLineR = 0.138/ escalaColor,
			auxLineG = 0.151/ escalaColor,
			auxLineB = 0.151/ escalaColor;

	float   sombraR = 0.247 / escalaColor,
			sombraG = 0.193 / escalaColor,
			sombraB = 0.182 / escalaColor;

	float vertices[] = {
	// FACE							
		(0.01 * escala),(-0.03*escala),0.01f,  face_R,face_G,face_B, //V0
		(0.05 * escala),(0.0*escala),0.01f,  face_R,face_G,face_B, 
		(0.08 * escala),(0.05*escala),0.01f,  face_R,face_G,face_B, 
		(0.08 * escala),(0.10*escala),0.01f,  face_R,face_G,face_B,
		(0.0 * escala),(0.18*escala),0.01f,  face_R,face_G,face_B,
		(-0.08 * escala),(0.10*escala),0.01f,  face_R,face_G,face_B,//V5
		(-0.08 * escala),(0.05*escala),0.01f,  face_R,face_G,face_B,
		(-0.05 * escala),(0.0*escala),0.01f,  face_R,face_G,face_B,
		(0.0 * escala),(0.05*escala),0.01f,  face_R,face_G,face_B, //pivote V8

	// EYES
		//left
		(-0.05 * escala),(0.06*escala),0.02f,  whiteRGB,whiteRGB,whiteRGB, //V9 pivote
			(-0.05 * escala),(0.05*escala),0.02f,  whiteRGB,whiteRGB,whiteRGB, //V10
			(-0.04 * escala),(0.05*escala),0.02f,  whiteRGB,whiteRGB,whiteRGB,
		(-0.03 * escala),(0.06*escala),0.02f,  whiteRGB,whiteRGB,whiteRGB,
			(-0.033 * escala),(0.07*escala),0.02f,  whiteRGB,whiteRGB,whiteRGB,
			(-0.05 * escala),(0.075*escala),0.02f,  whiteRGB,whiteRGB,whiteRGB,
		(-0.06 * escala),(0.07*escala),0.02f,  whiteRGB,whiteRGB,whiteRGB,//V15
			(-0.07 * escala),(0.065*escala),0.02f,  whiteRGB,whiteRGB,whiteRGB,
			(-0.06 * escala),(0.05*escala),0.02f,  whiteRGB,whiteRGB,whiteRGB,//V17

		//inside left
		(-0.05 * escala),(0.06*escala),0.03f,  eyeR,eyeG,eyeB, //V18 pivote
		
		(-0.045 * escala),(0.045*escala),0.03f,  eyeR,eyeG,eyeB,//
			(-0.04 * escala),(0.05*escala),0.03f,  eyeR,eyeG,eyeB,					
			(-0.037 * escala),(0.055*escala),0.03f,  eyeR,eyeG,eyeB,

		(-0.035 * escala),(0.06*escala),0.03f,  eyeR_2,eyeG_2,eyeB_2,//22
			(-0.038 * escala),(0.065*escala),0.03f,  eyeR_2,eyeG_2,eyeB_2,
			(-0.040 * escala),(0.070*escala),0.03f,  eyeR_2,eyeG_2,eyeB_2,

		(-0.042 * escala),(0.072*escala),0.03f,  eyeR_2,eyeG_2,eyeB_2,//25
			(-0.052 * escala),(0.07*escala),0.03f,  eyeR_2,eyeG_2,eyeB_2,
			(-0.057 * escala),(0.065*escala),0.03f,  eyeR_2,eyeG_2,eyeB_2,

		(-0.06 * escala),(0.06*escala),0.03f,  eyeR,eyeG,eyeB,//
			(-0.057 * escala),(0.05*escala),0.03f,  eyeR,eyeG,eyeB,
			(-0.052 * escala),(0.045*escala),0.03f,  eyeR,eyeG,eyeB,//30

	//CUERPO
	(0.0 * escala),(0.15*escala),0.0f,   face_R,face_G,face_B, //V31 pivote = 35
	
		(0.01 * escala),(-0.23*escala),0.01f,   face_R,face_G,face_B,
		(0.17 * escala),(-0.23*escala),0.01f,   face_R,face_G,face_B,
		(0.155 * escala),(-0.15*escala),0.01f,   face_R,face_G,face_B,
		(0.14 * escala),(-0.10*escala),0.01f,   face_R,face_G,face_B,
		(0.13 * escala),(-0.07*escala),0.01f,   face_R,face_G,face_B,
		(0.115 * escala),(-0.06*escala),0.01f,   face_R,face_G,face_B,//37
		(0.10 * escala),(-0.062*escala),0.01f,   face_R,face_G,face_B,
		(0.07 * escala),(-0.065*escala),0.01f,   face_R,face_G,face_B,
		(0.05 * escala),(-0.06*escala),0.01f,   face_R,face_G,face_B,
		(0.042 * escala),(-0.05*escala),0.01f,   face_R,face_G,face_B,
		(0.04 * escala),(-0.03*escala),0.01f,   face_R,face_G,face_B,
		(0.04 * escala),(0.01*escala),0.01f,   face_R,face_G,face_B,
		(0.01 * escala),(-0.03*escala),0.01f,   face_R,face_G,face_B,//barbilla-44

		//segunda mitad
	(0.0 * escala), (0.15*escala), 0.01f, face_R, face_G, face_B, //V31 pivote = 45

		(0.01 * escala),(-0.03*escala),0.01f,   face_R,face_G,face_B,//barbilla-46
		(-0.015 * escala), (0.01*escala), 0.01f, face_R, face_G, face_B,
		(-0.015 * escala), (-0.03*escala), 0.01f, face_R, face_G, face_B,
		(-0.025 * escala), (-0.05*escala), 0.01f, face_R, face_G, face_B,
		(-0.04 * escala), (-0.06*escala), 0.01f, face_R, face_G, face_B,//50
		(-0.045 * escala), (-0.065*escala), 0.01f, face_R, face_G, face_B,
		(-0.05 * escala), (-0.062*escala), 0.01f, face_R, face_G, face_B,
		(-0.08 * escala), (-0.06*escala), 0.01f, face_R, face_G, face_B,
		(-0.10 * escala), (-0.07*escala), 0.01f, face_R, face_G, face_B,
		(-0.12 * escala), (-0.10*escala), 0.01f, face_R, face_G, face_B,
		(-0.13 * escala), (-0.155*escala), 0.01f, face_R, face_G, face_B,
		(-0.15 * escala), (-0.23*escala), 0.01f, face_R, face_G, face_B,
		(0.01 * escala), (-0.23*escala), 0.01f, face_R, face_G, face_B,//58

	
	//general hair
	(0.0 * escala), (0.0*escala), 0.0f, hairR, hairG, hairB,//pivote -59

		(0.0 * escala), (-0.23*escala), 0.0f, hairR, hairG, hairB,//60
		(-0.18 * escala), (-0.23*escala), 0.0f, hairR, hairG, hairB,
		(-0.16 * escala), (-0.15*escala), 0.0f, hairR, hairG, hairB,
		(-0.167 * escala), (-0.10*escala), 0.0f, hairR, hairG, hairB,
		(-0.14 * escala), (-0.05*escala), 0.0f, hairR, hairG, hairB,
		(-0.13 * escala), (-0.0*escala), 0.0f, hairR, hairG, hairB,//65
		(-0.12 * escala), (0.05*escala), 0.0f, hairR, hairG, hairB,
		(-0.123 * escala), (0.10*escala), 0.0f, hairR, hairG, hairB,
		(-0.10 * escala), (0.15*escala), 0.0f, hairR, hairG, hairB,
		(-0.09 * escala), (0.18*escala), 0.0f, hairR, hairG, hairB,
		(-0.07 * escala), (0.20*escala), 0.0f, hairR, hairG, hairB,//70
		(-0.05 * escala), (0.22*escala), 0.0f, hairR, hairG, hairB,
		(-0.02 * escala), (0.228*escala), 0.0f, hairR, hairG, hairB,
		(0.0 * escala), (0.23*escala), 0.0f, hairR, hairG, hairB, //mitad -73

	//general hair right
	(0.0 * escala), (0.0*escala), 0.0f, hairR, hairG, hairB,//pivote - 74
		(0.0 * escala), (-0.23*escala), 0.0f, hairR, hairG, hairB,
		(0.14 * escala), (-0.23*escala), 0.0f, hairR, hairG, hairB,
		(0.11 * escala), (-0.05*escala), 0.0f, hairR, hairG, hairB,
		(0.105 * escala), (0.0*escala), 0.0f, hairR, hairG, hairB,
		(0.105 * escala), (0.05*escala), 0.0f, hairR, hairG, hairB,
		(0.10 * escala), (0.10*escala), 0.0f, hairR, hairG, hairB,//80
		(0.095 * escala), (0.15*escala), 0.0f, hairR, hairG, hairB,
		(0.075 * escala), (0.185*escala), 0.0f, hairR, hairG, hairB,
		(0.065 * escala), (0.20*escala), 0.0f, hairR, hairG, hairB,
		(0.05 * escala), (0.212*escala), 0.0f, hairR, hairG, hairB,
		(0.02 * escala), (0.22*escala), 0.0f, hairR, hairG, hairB,
		(0.0 * escala), (0.23*escala), 0.0f, hairR, hairG, hairB,//mitad -86

	//Alas
		(0.15 * escala), (-0.02*escala), 0.0f, alasR, alasG, alasB,//pivote - 87
			(0.08 * escala), (-0.06*escala), 0.0f, alasR, alasG, alasB,
			(0.12 * escala), (-0.03*escala), 0.0f, alasR, alasG, alasB,
			(0.16 * escala), (0.0*escala), 0.0f, alasR, alasG, alasB,//90
			(0.18 * escala), (0.03*escala), 0.0f, alasR, alasG, alasB,
			(0.20 * escala), (0.06*escala), 0.0f, alasR, alasG, alasB,
			(0.202 * escala), (0.04*escala), 0.0f, alasR, alasG, alasB,
			(0.20 * escala), (0.02*escala), 0.0f, alasR, alasG, alasB,
			(0.18 * escala), (-0.01*escala), 0.0f, alasR, alasG, alasB,
			(0.15 * escala), (-0.04*escala), 0.0f, alasR, alasG, alasB,
			(0.10 * escala), (-0.09*escala), 0.0f, alasR, alasG, alasB,//97
		
		(0.15 * escala), (-0.06*escala), 0.0f, alasR, alasG, alasB,//pivote - 98
			(0.11 * escala), (-0.07*escala), 0.0f, alasR, alasG, alasB,
			(0.12 * escala), (-0.06*escala), 0.0f, alasR, alasG, alasB,//100
			(0.14 * escala), (-0.04*escala), 0.0f, alasR, alasG, alasB,
			(0.16 * escala), (-0.035*escala), 0.0f, alasR, alasG, alasB,
			(0.194 * escala), (-0.02*escala), 0.0f, alasR, alasG, alasB,
			(0.19 * escala), (-0.04*escala), 0.0f, alasR, alasG, alasB,
			(0.17 * escala), (-0.06*escala), 0.0f, alasR, alasG, alasB,
			(0.14 * escala), (-0.08*escala), 0.0f, alasR, alasG, alasB,//106

		//Ala izquierda 
		(-0.14 * escala), (-0.03*escala), 0.0f, alasR, alasG, alasB,//pivote - 107
			(-0.175 * escala), (0.02*escala), 0.0f, alasR, alasG, alasB,
			(-0.15 * escala), (0.0*escala), 0.0f, alasR, alasG, alasB,
			(-0.13 * escala), (-0.02*escala), 0.0f, alasR, alasG, alasB,
			(-0.08 * escala), (-0.07*escala), 0.0f, alasR, alasG, alasB,//111
			(-0.09 * escala), (-0.09*escala), 0.0f, alasR, alasG, alasB,
			(-0.12 * escala), (-0.07*escala), 0.0f, alasR, alasG, alasB,
			(-0.15 * escala), (-0.04*escala), 0.0f, alasR, alasG, alasB,
			(-0.17 * escala), (-0.01*escala), 0.0f, alasR, alasG, alasB,//115

		//ala izquierda pequeña
		(-0.14 * escala), (-0.07*escala), 0.0f, alasR, alasG, alasB,//pivote - 116
			(-0.17 * escala), (-0.04*escala), 0.0f, alasR, alasG, alasB,
			(-0.15 * escala), (-0.05*escala), 0.0f, alasR, alasG, alasB,
			(-0.12 * escala), (-0.07*escala), 0.0f, alasR, alasG, alasB,
			(-0.11 * escala), (-0.10*escala), 0.0f, alasR, alasG, alasB,
			(-0.13 * escala), (-0.10*escala), 0.0f, alasR, alasG, alasB,
			(-0.16 * escala), (-0.07*escala), 0.0f, alasR, alasG, alasB,//122

		//zona blanca de ropa
		(-0.05 * escala), (-0.19*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//pivote - 123
			(-0.09 * escala), (-0.23*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(0.0 * escala), (-0.23*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//125
			(0.015 * escala), (-0.22*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//MID
			(0.015 * escala), (-0.19*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//MID
			(0.0 * escala), (-0.165*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(-0.03 * escala), (-0.15*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(-0.05 * escala), (-0.14*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//130
			(-0.07 * escala), (-0.142*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(-0.09 * escala), (-0.15*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(-0.10 * escala), (-0.16*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(-0.11 * escala), (-0.18*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(-0.11 * escala), (-0.20*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//135

		(0.08 * escala), (-0.19*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//pivote - 136
			(0.11 * escala), (-0.23*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(0.02 * escala), (-0.23*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(0.015 * escala), (-0.22*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//MID
			(0.015 * escala), (-0.19*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//MID-140

			(0.03 * escala), (-0.165*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(0.06 * escala), (-0.14*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(0.07 * escala), (-0.14*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(0.09 * escala), (-0.142*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//144

			(0.11 * escala), (-0.15*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(0.115 * escala), (-0.16*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(0.125 * escala), (-0.18*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,
			(0.125 * escala), (-0.20*escala), 0.0f, whiteRGB, whiteRGB, whiteRGB,//148

	//CABELLO DETALLADO
		(-0.04 * escala), (0.12*escala), 0.0f, hairR2, hairG2, hairB2,//pivote - 149
			(-0.05 * escala), (0.20*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.05 * escala), (0.12*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.03 * escala), (0.07*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.028 * escala), (0.09*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.008 * escala), (0.07*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.02 * escala), (0.10*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.034 * escala), (0.17*escala), 0.0f, hairR2, hairG2, hairB2,//156

		(-0.07 * escala), (0.12*escala), 0.0f, hairR2, hairG2, hairB2,//pivote - 157
			(-0.04 * escala), (0.10*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.07 * escala), (0.08*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.10 * escala), (0.05*escala), 0.0f, hairR2, hairG2, hairB2,//160
			(-0.09 * escala), (0.084*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.10 * escala), (0.09*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.09 * escala), (0.12*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.08 * escala), (0.16*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.05 * escala), (0.16*escala), 0.0f, hairR2, hairG2, hairB2,//165


	//cuernito
		(-0.045 * escala), (0.19*escala), 0.0f, cuarnoR, cuarnoG, cuarnoB,//pivote - 166
			(-0.065 * escala), (0.21*escala), 0.0f, cuarnoR, cuarnoG, cuarnoB,
			(-0.055 * escala), (0.18*escala), 0.0f, cuarnoR, cuarnoG, cuarnoB,
			(-0.04 * escala), (0.15*escala), 0.0f, cuarnoR, cuarnoG, cuarnoB,
			(-0.025 * escala), (0.135*escala), 0.0f, cuarnoR, cuarnoG, cuarnoB,
			(-0.025 * escala), (0.175*escala), 0.0f, cuarnoR, cuarnoG, cuarnoB,//171


	//CABELLO
		(-0.025 * escala), (0.175*escala), 0.0f, hairR2, hairG2, hairB2,//pivote - 172
			(-0.025 * escala), (0.10*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.002 * escala), (0.075*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.002 * escala), (0.12*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.006 * escala), (0.14*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.004 * escala), (0.17*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.0 * escala), (0.20*escala), 0.0f, hairR2, hairG2, hairB2,
			(-0.025 * escala), (0.175*escala), 0.0f, hairR2, hairG2, hairB2,//179

	//fleco derecho
		(0.03 * escala), (0.17*escala), 0.0f, hairR2, hairG2, hairB2,//pivote - 180
			(-0.003 * escala), (0.204*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.003 * escala), (0.17*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.005 * escala), (0.14*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.05 * escala), (0.11*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.08 * escala), (0.10*escala), 0.0f, hairR2, hairG2, hairB2,//185
			(0.11 * escala), (0.11*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.08 * escala), (0.13*escala), 0.0f, hairR2, hairG2, hairB2,

			(0.095 * escala), (0.132*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.06 * escala), (0.17*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.02 * escala), (0.196*escala), 0.0f, hairR2, hairG2, hairB2,//190
	
	//fleco extremo derecho
		(0.085 * escala), (0.095*escala), 0.0f, hairR2, hairG2, hairB2,//pivote - 191
			(0.07 * escala), (0.13*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.065 * escala), (0.10*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.065 * escala), (0.07*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.055 * escala), (0.03*escala), 0.0f, hairR2, hairG2, hairB2,//195
			(0.07 * escala), (0.04*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.06 * escala), (-0.01*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.09 * escala), (0.05*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.095 * escala), (0.065*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.12 * escala), (0.06*escala), 0.0f, hairR2, hairG2, hairB2,//200
			(0.14 * escala), (0.065*escala), 0.0f, hairR2, hairG2, hairB2,
			(0.10 * escala), (0.10*escala), 0.0f, hairR2, hairG2, hairB2,//202


	//rasgos faciales

	//boca
		(0.004 * escala), (0.005*escala), 0.0f, facialR, facialG, facialB, //pivote - 203
			(0.0 * escala), (0.006*escala), 0.0f, facialR, facialG, facialB,
			(0.0 * escala), (0.004*escala), 0.0f, facialR, facialG, facialB,
			(0.008 * escala), (0.004*escala), 0.0f, facialR, facialG, facialB,
			(0.008 * escala), (0.006*escala), 0.0f, facialR, facialG, facialB,//207

	//Nariz
		(-0.006 * escala), (0.033*escala), 0.0f, facialR, facialG, facialB, //pivote - 208
			(-0.005 * escala), (0.036*escala), 0.0f, facialR, facialG, facialB,
			(-0.005 * escala), (0.03*escala), 0.0f, facialR, facialG, facialB,
			(-0.007 * escala), (0.03*escala), 0.0f, facialR, facialG, facialB,
			(-0.007 * escala), (0.036*escala), 0.0f, facialR, facialG, facialB,//212

	
	//right
	(0.04 * escala),(0.08*escala),0.01f,  whiteRGB,whiteRGB,whiteRGB,//pivote 213

		(0.04 * escala), (0.06*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,
			(0.05 * escala), (0.062*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,
			(0.06 * escala), (0.07*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,

		(0.06 * escala), (0.075*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,
			(0.058 * escala), (0.089*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,
			(0.05 * escala), (0.09*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,

		(0.04 * escala), (0.09*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,//220
			(0.035 * escala), (0.087*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,
			(0.030 * escala), (0.082*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,

		(0.025 * escala), (0.075*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,
			(0.028 * escala), (0.070*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,
			(0.032 * escala), (0.067*escala), 0.01f, whiteRGB, whiteRGB, whiteRGB,//225


	(0.04 * escala), (0.08*escala), 0.01f, eyeR, eyeG, eyeB,//pivote 226
		(0.04 * escala), (0.062*escala), 0.02f, eyeR, eyeG, eyeB,
			(0.05 * escala), (0.064*escala), 0.02f, eyeR, eyeG, eyeB,

		(0.052 * escala), (0.075*escala), 0.02f, eyeR_2, eyeG_2, eyeB_2,
			(0.048 * escala), (0.085*escala), 0.02f, eyeR_2, eyeG_2, eyeB_2,//230

		(0.04 * escala), (0.088*escala), 0.02f, eyeR_2, eyeG_2, eyeB_2,
			(0.03 * escala), (0.082*escala), 0.02f, eyeR_2, eyeG_2, eyeB_2,

		(0.027 * escala), (0.075*escala), 0.02f, eyeR, eyeG, eyeB,
			(0.03 * escala), (0.065*escala), 0.02f, eyeR, eyeG, eyeB,//234

	//Pupila derecha			
	(0.038 * escala), (0.073*escala), 0.01f, eyeR_2, eyeG_2, eyeB_2,//pivote 235
		(0.036 * escala), (0.075*escala), 0.02f, eyeR_2, eyeG_2, eyeB_2,
		(0.036 * escala), (0.071*escala), 0.02f, eyeR_2, eyeG_2, eyeB_2,

		(0.040 * escala), (0.071*escala), 0.02f, eyeR_2, eyeG_2, eyeB_2,
		(0.040 * escala), (0.075*escala), 0.02f, eyeR_2, eyeG_2, eyeB_2,//239

	//PUPILA IZQUIERDA
	(-0.05 * escala), (0.058*escala), 0.03f, eyeR_2, eyeG_2, eyeB_2, //V 240
		(-0.048 * escala), (0.060*escala), 0.03f, eyeR_2, eyeG_2, eyeB_2,
		(-0.048 * escala), (0.056*escala), 0.03f, eyeR_2, eyeG_2, eyeB_2,

		(-0.052 * escala), (0.056*escala), 0.03f, eyeR_2, eyeG_2, eyeB_2,
		(-0.052 * escala), (0.060*escala), 0.03f, eyeR_2, eyeG_2, eyeB_2,//244

	//fleco extremo derecho
	(-0.08 * escala), (0.04*escala), 0.0f, hairR2, hairG2, hairB2,//pivote - 245
		(-0.095 * escala), (0.08*escala), 0.0f, hairR2, hairG2, hairB2,
		(-0.08 * escala), (0.005*escala), 0.0f, hairR2, hairG2, hairB2,
		(-0.075 * escala), (0.02*escala), 0.0f, hairR2, hairG2, hairB2,
		(-0.045 * escala), (-0.02*escala), 0.0f, hairR2, hairG2, hairB2,
		(-0.06 * escala), (0.01*escala), 0.0f, hairR2, hairG2, hairB2,//250
		(-0.05 * escala), (0.008*escala), 0.0f, hairR2, hairG2, hairB2,
		(-0.07 * escala), (0.04*escala), 0.0f, hairR2, hairG2, hairB2,
		(-0.08 * escala), (0.09*escala), 0.0f, hairR2, hairG2, hairB2,//253
	

	//ESTRELLA
	(0.015 * escala), (-0.15*escala), 0.0f, estrellaR, estrellaG, estrellaB,//pivote - 254
		
		(0.015 * escala), (-0.11*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,//255
			(0.03 * escala), (-0.135*escala), 0.0f, estrellaR, estrellaG, estrellaB,

		(0.05 * escala), (-0.15*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,
			(0.03 * escala), (-0.165*escala), 0.0f, estrellaR, estrellaG, estrellaB,

		(0.015 * escala), (-0.19*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,
			(0.0 * escala), (-0.165*escala), 0.0f, estrellaR, estrellaG, estrellaB,//260

		(-0.025 * escala), (-0.15*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,
			(0.0 * escala), (-0.135*escala), 0.0f, estrellaR, estrellaG, estrellaB,//262
				
	//interna
	(0.015 * escala), (-0.15*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,//pivote - 263

				(0.015 * escala), (-0.105*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,
				(0.035 * escala), (-0.13*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,

				(0.055 * escala), (-0.15*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,
				(0.035 * escala), (-0.17*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,

				(0.015 * escala), (-0.195*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,
				(-0.005 * escala), (-0.17*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,

				(-0.03 * escala), (-0.15*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,
				(-0.005 * escala), (-0.13*escala), 0.0f, estrellaR_2, estrellaG_2, estrellaB_2,//271


	//estrella azul
	(0.05 * escala), (-0.12*escala), 0.0f, blueR, blueG, blueB,//pivote - 272
			(0.015 * escala), (-0.15*escala), 0.0f, blueR, blueG, blueB,
			(0.015 * escala), (-0.135*escala), 0.0f, blueR, blueG, blueB,
			(0.03 * escala), (-0.11*escala), 0.0f, blueR, blueG, blueB,
		(0.05 * escala), (-0.098*escala), 0.0f, blueR, blueG, blueB,
			(0.08 * escala), (-0.10*escala), 0.0f, blueR, blueG, blueB,
			(0.07 * escala), (-0.12*escala), 0.0f, blueR, blueG, blueB,
		(0.05 * escala), (-0.14*escala), 0.0f, blueR, blueG, blueB,//279

	//estrella azul left
	
	(-0.02 * escala), (-0.12*escala), 0.0f, blueR, blueG, blueB,//pivote - 280
			(-0.05 * escala), (-0.10*escala), 0.0f, blueR, blueG, blueB,
			(-0.04 * escala), (-0.12*escala), 0.0f, blueR, blueG, blueB,
			(-0.02 * escala), (-0.14*escala), 0.0f, blueR, blueG, blueB,
			(0.01 * escala), (-0.15*escala), 0.0f, blueR, blueG, blueB,
			(0.015 * escala), (-0.12*escala), 0.0f, blueR, blueG, blueB,
			(-0.01 * escala), (-0.10*escala), 0.0f, blueR, blueG, blueB,//286

	(-0.02 * escala), (-0.18*escala), 0.0f, blueR, blueG, blueB,//pivote - 287
			(-0.04 * escala), (-0.21*escala), 0.0f, blueR, blueG, blueB,
			(-0.01 * escala), (-0.2*escala), 0.0f, blueR, blueG, blueB,
			(-0.0 * escala), (-0.18*escala), 0.0f, blueR, blueG, blueB,//90
			(0.01 * escala), (-0.15*escala), 0.0f, blueR, blueG, blueB,
			(-0.02 * escala), (-0.16*escala), 0.0f, blueR, blueG, blueB,
			(-0.048 * escala), (-0.18*escala), 0.0f, blueR, blueG, blueB,//293



	(0.05 * escala), (-0.18*escala), 0.0f, blueR, blueG, blueB,//pivote - 294
		(0.07 * escala), (-0.21*escala), 0.0f, blueR, blueG, blueB,
		(0.072 * escala), (-0.18*escala), 0.0f, blueR, blueG, blueB,
		(0.05 * escala), (-0.16*escala), 0.0f, blueR, blueG, blueB,
		(0.01 * escala), (-0.15*escala), 0.0f, blueR, blueG, blueB,
		(0.025 * escala), (-0.175*escala), 0.0f, blueR, blueG, blueB,
		(0.03 * escala), (-0.20*escala), 0.0f, blueR, blueG, blueB,//300

	//COLLAR
			
	(0.015 * escala), (-0.045*escala), 0.02f, estrellaR, estrellaG, estrellaB,//pivote - 301
		(0.025 * escala), (-0.05*escala), 0.02f, estrellaR, estrellaG, estrellaB,
		(0.04 * escala), (-0.04*escala), 0.02f, estrellaR, estrellaG, estrellaB,
		(0.04 * escala), (-0.03*escala), 0.02f, estrellaR, estrellaG, estrellaB,
		(0.025 * escala), (-0.038*escala), 0.02f, estrellaR, estrellaG, estrellaB,//305
		
		(0.0 * escala), (-0.038*escala), 0.02f, estrellaR, estrellaG, estrellaB,
		(-0.015 * escala), (-0.03*escala), 0.02f, estrellaR, estrellaG, estrellaB,
		(-0.025 * escala), (-0.04*escala), 0.02f, estrellaR, estrellaG, estrellaB,
		(0.0 * escala), (-0.05*escala), 0.02f, estrellaR, estrellaG, estrellaB,//309
	

	//PESTAÑAS
	(0.04 * escala), (0.09*escala), 0.02f, pestaR, pestaG, pestaB,//pivote - 310
		(0.03 * escala), (0.088*escala), 0.02f, pestaR, pestaG, pestaB,
		(0.02 * escala), (0.08*escala), 0.02f, pestaR, pestaG, pestaB,
		(0.04 * escala), (0.086*escala), 0.02f, pestaR, pestaG, pestaB,
		(0.06 * escala), (0.082*escala), 0.02f, pestaR, pestaG, pestaB,
		(0.055 * escala), (0.089*escala), 0.02f, pestaR, pestaG, pestaB,
		(0.04 * escala), (0.092*escala), 0.02f, pestaR, pestaG, pestaB,//316


	(-0.06 * escala), (0.071*escala), 0.02f, pestaR, pestaG, pestaB,//pivote - 317
		(-0.08 * escala), (0.06*escala), 0.02f, pestaR, pestaG, pestaB,
		(-0.07 * escala), (0.061*escala), 0.02f, pestaR, pestaG, pestaB,
		(-0.06 * escala), (0.067*escala), 0.02f, pestaR, pestaG, pestaB,//320
		(-0.04 * escala), (0.069*escala), 0.02f, pestaR, pestaG, pestaB,
	(-0.03 * escala), (0.068*escala), 0.02f, pestaR, pestaG, pestaB,
		(-0.05 * escala), (0.078*escala), 0.02f, pestaR, pestaG, pestaB,
		(-0.06 * escala), (0.073*escala), 0.02f, pestaR, pestaG, pestaB,//324

	//VERTICES DE LAS LÍNEAS
	(0.102 * escala), (-0.11*escala), 0.02f, auxLineR, auxLineG, auxLineB,//325
	(0.10 * escala), (-0.12*escala), 0.02f, auxLineR, auxLineG, auxLineB,
	(0.10 * escala), (-0.13*escala), 0.02f, auxLineR, auxLineG, auxLineB,
	(0.105 * escala), (-0.14*escala), 0.02f, auxLineR, auxLineG, auxLineB,
	(0.11 * escala), (-0.15*escala), 0.02f, auxLineR, auxLineG, auxLineB,//329


	//arm left
			(-0.082 * escala), (-0.11*escala), 0.02f, auxLineR, auxLineG, auxLineB,//330
			(-0.08 * escala), (-0.12*escala), 0.02f, auxLineR, auxLineG, auxLineB,
			(-0.082 * escala), (-0.13*escala), 0.02f, auxLineR, auxLineG, auxLineB,
			(-0.085 * escala), (-0.14*escala), 0.02f, auxLineR, auxLineG, auxLineB,
			(-0.09 * escala), (-0.15*escala), 0.02f, auxLineR, auxLineG, auxLineB,//334


	//shoulder right
			(0.035 * escala), (-0.08*escala), 0.02f, auxLineR, auxLineG, auxLineB,//335
			(0.05 * escala), (-0.07*escala), 0.02f, auxLineR, auxLineG, auxLineB,
			(0.07 * escala), (-0.065*escala), 0.02f, auxLineR, auxLineG, auxLineB,//337

	//HAIR LINES
		(-0.145 * escala), (-0.14*escala), 0.02f, auxLineR, auxLineG, auxLineB,//338
		(-0.14 * escala), (-0.10*escala), 0.02f, auxLineR, auxLineG, auxLineB,
		(-0.13 * escala), (-0.06*escala), 0.02f, auxLineR, auxLineG, auxLineB,
		(-0.125 * escala), (-0.04*escala), 0.02f, auxLineR, auxLineG, auxLineB,//341

	
		(-0.155 * escala), (-0.15*escala), 0.02f, auxLineR, auxLineG, auxLineB,//342
		(-0.15 * escala), (-0.18*escala), 0.02f, auxLineR, auxLineG, auxLineB,
		(-0.151 * escala), (-0.20*escala), 0.02f, auxLineR, auxLineG, auxLineB,
		(-0.16 * escala), (-0.22*escala), 0.02f, auxLineR, auxLineG, auxLineB,//345

		
		(-0.119 * escala), (-0.075*escala), 0.02f, auxLineR, auxLineG, auxLineB,//346
		(-0.10 * escala), (-0.05*escala), 0.02f, auxLineR, auxLineG, auxLineB,
		(-0.09 * escala), (-0.01*escala), 0.02f, auxLineR, auxLineG, auxLineB,//348

		//lado derecho
		(0.09 * escala), (-0.05*escala), 0.02f, auxLineR, auxLineG, auxLineB,//349
		(0.085 * escala), (-0.02*escala), 0.02f, auxLineR, auxLineG, auxLineB,
		(0.08 * escala), (-0.01*escala), 0.02f, auxLineR, auxLineG, auxLineB,//MID
		(0.08 * escala), (0.025*escala), 0.02f, auxLineR, auxLineG, auxLineB,//352

		(0.075 * escala), (-0.05*escala), 0.02f, auxLineR, auxLineG, auxLineB,//353
		(0.08 * escala), (-0.01*escala), 0.02f, auxLineR, auxLineG, auxLineB,
		(0.08 * escala), (0.025*escala), 0.02f, auxLineR, auxLineG, auxLineB,//355

		//en cabeza
		(0.065 * escala), (0.13*escala), 0.02f, auxLineR, auxLineG, auxLineB,//356
		(0.05 * escala), (0.15*escala), 0.02f, auxLineR, auxLineG, auxLineB,
		(0.025 * escala), (0.175*escala), 0.02f, auxLineR, auxLineG, auxLineB,//358

		(0.07 * escala), (0.12*escala), 0.02f, auxLineR, auxLineG, auxLineB,//359
		(0.055 * escala), (0.135*escala), 0.02f, auxLineR, auxLineG, auxLineB,//360


		(-0.01 * escala), (0.11*escala), 0.02f, auxLineR, auxLineG, auxLineB,//361
		(-0.02 * escala), (0.14*escala), 0.02f, auxLineR, auxLineG, auxLineB,//362
		
		(-0.07 * escala), (0.11*escala), 0.02f, auxLineR, auxLineG, auxLineB,//363
		(-0.085 * escala), (0.085*escala), 0.02f, auxLineR, auxLineG, auxLineB,
		(-0.08 * escala), (0.11*escala), 0.02f, auxLineR, auxLineG, auxLineB,//365

	//CEJAS
		(0.04 * escala), (0.115*escala), 0.0f, pestaR, pestaG, pestaB, //pivote - 366
			(0.02 * escala), (0.116*escala), 0.0f, pestaR, pestaG, pestaB,
			(0.02 * escala), (0.114*escala), 0.0f, pestaR, pestaG, pestaB,
			(0.06 * escala), (0.114*escala), 0.0f, pestaR, pestaG, pestaB,
			(0.06 * escala), (0.116*escala), 0.0f, pestaR, pestaG, pestaB,//370

	//LINEAS AZUL
		(0.015 * escala), (-0.15*escala), 0.02f, auxLineR, auxLineG, auxLineB,//371
			(-0.02 * escala), (-0.12*escala), 0.02f, auxLineR, auxLineG, auxLineB,
			(0.05 * escala), (-0.12*escala), 0.02f, auxLineR, auxLineG, auxLineB,
			(0.05 * escala), (-0.18*escala), 0.02f, auxLineR, auxLineG, auxLineB,
			(-0.02 * escala), (-0.18*escala), 0.02f, auxLineR, auxLineG, auxLineB,



	};



	unsigned int indices[] ={
		//FACE
		8,0,1,2,3,4,5,6,7,0, //10

		//LEFT EYE
		//eye blanck parte
		9,10,11,12,13,14,15,16,17,10, //10

		//iris
		18,19,20,21,22,23,24,25,26,27,28,29,30,19,//14

		//BODY
		//first half
		31,32,33,34,35,36,37,38,39,40,41,42,43,44,32,//15
		45,46,47,48,49,50,51,52,53,54,55,56,57,58,46, //15

		//Hair general left
		59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,60,//16
		74,75,76,77,78,79,80,81,82,83,84,85,86,75,//14

		//Alas
		87,88,89,90,91,92,93,94,95,96,97,88,//12
		98,99,100,101,102,103,104,105,106,99, //10

		//Ala izquierda mayor
		107,108,109,110,111,112,113,114,115,108,//10
		116,117,118,119,120,121,122,117,//8

		//zona blanca de ropa
		123,124,125,126,127,128,129,130,131,132,133,134,135,124,//14
		136,137,138,139,140,141,142,143,144,145,146,147,148,137, //14

		//cabello detallado
		149,150,151,152,153,154,155,156,150,//9

		157,158,159,160,161,162,163,164,165,158,//10


		//cuerno 
		166,167,168,169,170,171,167,//7

		//mas cabello
		172,173,174,175,176,177,178,179,173,//9
		180,181,182,183,184,185,186,187,188,189,190,181,//12

		//mas cabello :(
		191,192,193,194,195,196,197,198,199,200,201,202,192,//13

		//RANGOS FACIALES
		//boca
		203,204,205,206,207,204,//6

		//nariz
		208,209,210,211,212,209,//6

		//ojo derecho
		213,214,215,216,217,218,219,220,221,222,223,224,225,214,//14
		226,227,228,229,230,231,232,233,234,227,//10
		235,236,237,238,239,236,//6
		240,241,242,243,244,241,//6

		//fleco extremo derecho
		245,246,247,248,249,250,251,252,253,246,//10

		//ESTRELLA
		254,255,256,257,258,259,260,261,262,255,//10
		//interna
		263,264,265,266,267,268,269,270,271,264, //10
		
		//petalo azul
		272,273,274,275,276,277,278,279,273,//9
		280,281,282,283,284,285,286,281,//8
		287,288,289,290,291,292,293,288,//8
		294,295,296,297,298,299,300,295,//8

		//collar
		301,302,303,304,305,306,307,308,309,302,//10

		//ceja
		310,311,312,313,314,315,316,311,//8

		//ceja
		317,318,319,320,321,322,323,324,318,//9


		//VERTICES LINEAS+
		//brazos
		325,326,327,328,329,

		330,331,332,333,334,

		335,336,337,

		338,339,340,341,

		342,343,344,345,

		346,347,348,

		//lado derecho
		349,350,351,352,
		353,354,355,

		356,357,358,
		359,360,
		361,362,

		363,364,365,

		//CEJA
		366,367,368,369,370,367,

		//MORE LINES
			371, 372,
			371, 373,
			371, 374,
			371, 375



	};

	//Se manda el vector de vertices al buffer 
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// position attribute
	//GL_false es porque no están en 0 y 1 o sea no están normalizados, 0 significa cada cuanto saltaba si es que hay más atributos, (void*)0
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);// Le pasa al buffer las entradas aPos y aColor
	glEnableVertexAttribArray(0);


	// color attribute
	//1 es el número de la entrada, cantidad de datos, tipo de datos, GL_false es porque no están en 0 y 1 o sea no están normalizados,
	//6 * sizeof(float) significa cada cuanto va a estar leyendo -> o sea cada cuanto saltará, este menciona donde empieza
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	//Para trabajar con indices (Element Buffer Object)
	glGenBuffers(1, &EBO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

}

void display(void){

	glUseProgram(shaderProgramColor);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glPointSize(5.0);
	
	//DIBUJO DE LAS ENTIDADES 
	/**/
	//Alas
	glDrawElements(GL_TRIANGLE_FAN, 12, GL_UNSIGNED_INT, (void*)(95 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, (void*)(107 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, (void*)(117 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, (void*)(127 * sizeof(float)));

	//Hair
	glDrawElements(GL_TRIANGLE_FAN, 16, GL_UNSIGNED_INT, (void*)(65 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 14, GL_UNSIGNED_INT, (void*)(81 * sizeof(float)));

	//Rostro
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, 0);

	//ojo izquierdo
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, (void*)(10 * sizeof(float)));

	//ojo izquierdo-green
	glDrawElements(GL_TRIANGLE_FAN, 14, GL_UNSIGNED_INT, (void*)(20 * sizeof(float)));

	//BODY
	glDrawElements(GL_TRIANGLE_FAN, 15, GL_UNSIGNED_INT, (void*)(35 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 15, GL_UNSIGNED_INT, (void*)(50 * sizeof(float)));

	//ROPA BLANCO
	glDrawElements(GL_TRIANGLE_FAN, 14, GL_UNSIGNED_INT, (void*)(135 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 14, GL_UNSIGNED_INT, (void*)(149 * sizeof(float)));


	//CEJA
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(401 * sizeof(float)));

	//hair detail
	glDrawElements(GL_TRIANGLE_FAN, 9, GL_UNSIGNED_INT, (void*)(163 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, (void*)(172 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 9, GL_UNSIGNED_INT, (void*)(189 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 12, GL_UNSIGNED_INT, (void*)(198 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 13, GL_UNSIGNED_INT, (void*)(210 * sizeof(float)));



	//cuerno
	glDrawElements(GL_TRIANGLE_FAN, 7, GL_UNSIGNED_INT, (void*)(182 * sizeof(float)));


	//rasgos faciales
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(223 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(229 * sizeof(float)));

	//LEFT EYE
	glDrawElements(GL_TRIANGLE_FAN, 14, GL_UNSIGNED_INT, (void*)(235 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, (void*)(249 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(259 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 6, GL_UNSIGNED_INT, (void*)(265 * sizeof(float)));
	
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, (void*)(271 * sizeof(float)));
	

	//petalos
	glDrawElements(GL_TRIANGLE_FAN, 9, GL_UNSIGNED_INT, (void*)(300 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, (void*)(309 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, (void*)(317 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, (void*)(325 * sizeof(float)));

	//MORE LINES
	glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, (void*)(407 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, (void*)(409 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, (void*)(411 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, (void*)(413 * sizeof(float)));//HERE






	//ESTRELLA
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, (void*)(290 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, (void*)(280 * sizeof(float)));
	
	//collar 
	glDrawElements(GL_TRIANGLE_FAN, 10, GL_UNSIGNED_INT, (void*)(333 * sizeof(float)));

	//pestañas y cejas
	glDrawElements(GL_TRIANGLE_FAN, 8, GL_UNSIGNED_INT, (void*)(343 * sizeof(float)));
	glDrawElements(GL_TRIANGLE_FAN, 9, GL_UNSIGNED_INT, (void*)(351 * sizeof(float)));

	//DELINEADO
	glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(360 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 5, GL_UNSIGNED_INT, (void*)(365 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, (void*)(370 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 4, GL_UNSIGNED_INT, (void*)(373 * sizeof(float)));

	glDrawElements(GL_LINE_STRIP, 4, GL_UNSIGNED_INT, (void*)(377 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, (void*)(381 * sizeof(float)));

	//lado derecho
	glDrawElements(GL_LINE_STRIP, 4, GL_UNSIGNED_INT, (void*)(384 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, (void*)(388 * sizeof(float)));


	glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, (void*)(391 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, (void*)(394 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 2, GL_UNSIGNED_INT, (void*)(396 * sizeof(float)));
	glDrawElements(GL_LINE_STRIP, 3, GL_UNSIGNED_INT, (void*)(398 * sizeof(float)));




	
	glBindVertexArray(0);
	glUseProgram(0);
}



void setupShaders(){

	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &myVertexShader, NULL);
	glCompileShader(vertexShader);

	unsigned int vertexShaderColor = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShaderColor, 1, &myVertexShaderColor, NULL);
	glCompileShader(vertexShaderColor);

	unsigned int fragmentShaderRed = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderRed, 1, &myFragmentShaderRed, NULL);
	glCompileShader(fragmentShaderRed);

	unsigned int fragmentShaderColor = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShaderColor, 1, &myFragmentShaderColor, NULL);
	glCompileShader(fragmentShaderColor);


	//Crear el Programa que combina Geometría con Color
	shaderProgramRed = glCreateProgram();
	glAttachShader(shaderProgramRed, vertexShader);
	glAttachShader(shaderProgramRed, fragmentShaderRed);
	glLinkProgram(shaderProgramRed);

	shaderProgramColor = glCreateProgram();
	glAttachShader(shaderProgramColor, vertexShaderColor);
	glAttachShader(shaderProgramColor, fragmentShaderColor);
	glLinkProgram(shaderProgramColor);
	//Check for errors 

	//ya con el Programa, el Shader no es necesario
	glDeleteShader(vertexShader);
	glDeleteShader(vertexShaderColor);
	glDeleteShader(fragmentShaderRed);
	glDeleteShader(fragmentShaderColor);

}

int main(){
    
    glfwInit();

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
	monitors = glfwGetPrimaryMonitor();
	
	//PREVIO
	getResolution();

    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Soraka - 2D-DRAW", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
	glfwSetWindowPos(window, 0, 30);
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, resize);

	glewInit();


	//Mis funciones
	//Datos a utilizar
	myData();
	//Configurar Shaders
	setupShaders();
    

    // render loop
    // While the windows is not closed
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        my_input(window);

        // render
        // Backgound color
		float escalaColor = 0.255f;
		glClearColor(0.194f/escalaColor, 0.207f / escalaColor, 0.213f / escalaColor, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

		//Mi función de dibujo
		display();

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

void my_input(GLFWwindow *window)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)  //GLFW_RELEASE
        glfwSetWindowShouldClose(window, true);
}

void resize(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}