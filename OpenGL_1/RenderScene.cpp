#include "common_header.h"

#include "win_OpenGLApp.h"

#include "shaders.h"

#include <math.h>


float fQuad[12]; // Data to render quad using triangle strips (4 vertices, each has 3 floats)
float fQuadColor[12];

float treeUp[18];
float treeMid[18];
float treeDown[18];
float treeLeg[24];

float flag[18];
float mast[24];
float vessel[24];
float stern[18];

const int objects = 9;
UINT uiVBO[objects];
UINT uiVAO[objects];

CShader shVertex, shFragment;
CShaderProgram spMain;

#pragma region Triangle
// Initializes OpenGL features that will be used.
// lpParam - Pointer to anything you want.
void InitScene(LPVOID lpParam)
{
	glGenVertexArrays(objects, uiVAO); // Generate two VAOs, one for triangle and one for quad
	glGenBuffers(objects, uiVBO); // And four VBOs


	// background color
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);


#pragma region Square
	// Setup quad vertices

	fQuad[0] = -0.2f; fQuad[1] = -0.1f; fQuad[2] = 0.0f;
	fQuad[3] = -0.2f; fQuad[4] = -0.6f; fQuad[5] = 0.0f;
	fQuad[6] = 0.2f; fQuad[7] = -0.1f; fQuad[8] = 0.0f;
	fQuad[9] = 0.2f; fQuad[10] = -0.6f; fQuad[11] = 0.0f;

	// Setup quad color

	fQuadColor[0] = 1.0f; fQuadColor[1] = 0.0f; fQuadColor[2] = 0.0f;
	fQuadColor[3] = 0.0f; fQuadColor[4] = 1.0f; fQuadColor[5] = 0.0f;
	fQuadColor[6] = 0.0f; fQuadColor[7] = 0.0f; fQuadColor[8] = 1.0f;
	fQuadColor[9] = 1.0f; fQuadColor[10] = 1.0f; fQuadColor[11] = 0.0f;




	// Setup whole quad
	glBindVertexArray(uiVAO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[0]);
	// Position (create buffer for pos & color to add color data later)
	glBufferData(GL_ARRAY_BUFFER, 24 * sizeof(float), fQuad, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	// Color
	glBufferSubData(GL_ARRAY_BUFFER, 12 * sizeof(float), 12 * sizeof(float), fQuadColor);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void*)(12 * sizeof(float)));
#pragma endregion

#pragma region Tree
#pragma region TreeUp
	// Setup triangle vertices & colors
	treeUp[0] = -1.0f; treeUp[1] = 0.0f; treeUp[2] = 0.0f;
	treeUp[3] = 0.0f; treeUp[4] = 1.0f; treeUp[5] = 0.0f;

	treeUp[6] = -0.8f; treeUp[7] = 0.0f; treeUp[8] = 0.0f;
	treeUp[9] = 0.0f; treeUp[10] = 1.0f; treeUp[11] = 0.0f;

	treeUp[12] = -0.9f; treeUp[13] = 0.2f; treeUp[14] = 0.0f;
	treeUp[15] = 0.0f; treeUp[16] = 1.0f; treeUp[17] = 0.0f;

	// Setup whole triangle
	glBindVertexArray(uiVAO[1]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[1]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), treeUp, GL_STATIC_DRAW);
	// positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	// colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
#pragma endregion

#pragma region TreeMid
	// Setup triangle vertices & colors
	treeMid[0] = -1.0f; treeMid[1] = -0.2f; treeMid[2] = 0.0f;
	treeMid[3] = 0.0f; treeMid[4] = 1.0f; treeMid[5] = 0.0f;

	treeMid[6] = -0.8f; treeMid[7] = -0.2f; treeMid[8] = 0.0f;
	treeMid[9] = 0.0f; treeMid[10] = 1.0f; treeMid[11] = 0.0f;

	treeMid[12] = -0.9f; treeMid[13] = 0.05f; treeMid[14] = 0.0f;
	treeMid[15] = 0.0f; treeMid[16] = 1.0f; treeMid[17] = 0.0f;

	// Setup whole triangle
	glBindVertexArray(uiVAO[2]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[2]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), treeMid, GL_STATIC_DRAW);
	// positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	// colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
#pragma endregion

#pragma region TreeDown
	// Setup triangle vertices & colors
	treeDown[0] = -1.0f; treeDown[1] = -0.4f; treeDown[2] = 0.0f;
	treeDown[3] = 0.0f; treeDown[4] = 1.0f; treeDown[5] = 0.0f;

	treeDown[6] = -0.8f; treeDown[7] = -0.4f; treeDown[8] = 0.0f;
	treeDown[9] = 0.0f; treeDown[10] = 1.0f; treeDown[11] = 0.0f;

	treeDown[12] = -0.9f; treeDown[13] = -0.15f; treeDown[14] = 0.0f;
	treeDown[15] = 0.0f; treeDown[16] = 1.0f; treeDown[17] = 0.0f;

	// Setup whole triangle
	glBindVertexArray(uiVAO[3]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[3]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), treeDown, GL_STATIC_DRAW);
	// positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	// colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
#pragma endregion

#pragma region Leg
	// Setup quad vertices

	treeLeg[0] = -0.94f; treeLeg[1] = -0.4f; treeLeg[2] = 0.0f;
	treeLeg[3] = 0.4f; treeLeg[4] = 0.2f; treeLeg[5] = 0.0f;

	treeLeg[6] = -0.94f; treeLeg[7] = -0.6f; treeLeg[8] = 0.0f;
	treeLeg[9] = 0.4f; treeLeg[10] = 0.2f; treeLeg[11] = 0.0f;

	treeLeg[12] = -0.86f; treeLeg[13] = -0.4f; treeLeg[14] = 0.0f;
	treeLeg[15] = 0.4f; treeLeg[16] = 0.2f; treeLeg[17] = 0.0f;

	treeLeg[18] = -0.86f; treeLeg[19] = -0.6f; treeLeg[20] = 0.0f;
	treeLeg[21] = 0.4f; treeLeg[22] = 0.2f; treeLeg[23] = 0.0f;





	// Setup whole quad
	glBindVertexArray(uiVAO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[4]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 12 * sizeof(float), treeLeg, GL_STATIC_DRAW);
	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	// Color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
#pragma endregion
#pragma endregion

#pragma region Ship
#pragma region Flag
	// Setup triangle vertices & colors
	flag[0] = 0.7f; flag[1] = 0.6f; flag[2] = 0.0f;
	flag[3] = 1.0f; flag[4] = 0.0f; flag[5] = 0.0f;

	flag[6] = 0.3f; flag[7] = 0.6f; flag[8] = 0.0f;
	flag[9] = 1.0f; flag[10] = 0.0f; flag[11] = 0.0f;

	flag[12] = 0.3f; flag[13] = 1.0f; flag[14] = 0.0f;
	flag[15] = 1.0f; flag[16] = 0.0f; flag[17] = 0.0f;

	// Setup whole triangle
	glBindVertexArray(uiVAO[5]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[5]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), flag, GL_STATIC_DRAW);
	// positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	// colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
#pragma endregion

#pragma region Mast
	// Setup quad vertices

	mast[0] = 0.27f; mast[1] = 1.0f; mast[2] = 0.0f;
	mast[3] = 0.3f; mast[4] = 0.3f; mast[5] = 0.3f;

	mast[6] = 0.27f; mast[7] = 0.5f; mast[8] = 0.0f;
	mast[9] = 0.3f; mast[10] = 0.3f; mast[11] = 0.3f;

	mast[12] = 0.3f; mast[13] = 1.0f; mast[14] = 0.0f;
	mast[15] = 0.3f; mast[16] = 0.3f; mast[17] = 0.3f;

	mast[18] = 0.3f; mast[19] = 0.5f; mast[20] = 0.0f;
	mast[21] = 0.3f; mast[22] = 0.3f; mast[23] = 0.3f;

	// Setup whole quad
	glBindVertexArray(uiVAO[6]);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[6]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 12 * sizeof(float), mast, GL_STATIC_DRAW);
	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	// Color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
#pragma endregion

#pragma region Vessel
	// Setup quad vertices

	vessel[0] = -0.1f; vessel[1] = 0.5f; vessel[2] = 0.0f;
	vessel[3] = 0.3f; vessel[4] = 0.8f; vessel[5] = 1.0f;

	vessel[6] = -0.1f; vessel[7] = 0.2f; vessel[8] = 0.0f;
	vessel[9] = 0.3f; vessel[10] = 0.8f; vessel[11] = 1.0f;

	vessel[12] = 0.6f; vessel[13] = 0.5f; vessel[14] = 0.0f;
	vessel[15] = 0.3f; vessel[16] = 0.8f; vessel[17] = 1.0f;

	vessel[18] = 0.6f; vessel[19] = 0.2f; vessel[20] = 0.0f;
	vessel[21] = 0.3f; vessel[22] = 0.8f; vessel[23] = 1.0f;

	// Setup whole quad
	glBindVertexArray(uiVAO[7]);
	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[7]);
	glBufferData(GL_ARRAY_BUFFER, 2 * 12 * sizeof(float), vessel, GL_STATIC_DRAW);
	// Position
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	// Color
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
#pragma endregion

#pragma region Stern
	// Setup triangle vertices & colors
	stern[0] = 0.6f; stern[1] = 0.5f; stern[2] = 0.0f;
	stern[3] = 0.3f; stern[4] = 0.8f; stern[5] = 1.0f;

	stern[6] = 0.6f; stern[7] = 0.2f; stern[8] = 0.0f;
	stern[9] = 0.3f; stern[10] = 0.8f; stern[11] = 1.0f;

	stern[12] = 0.9f; stern[13] = 0.5f; stern[14] = 0.0f;
	stern[15] = 0.3f; stern[16] = 0.8f; stern[17] = 1.0f;

	// Setup whole triangle
	glBindVertexArray(uiVAO[8]);

	glBindBuffer(GL_ARRAY_BUFFER, uiVBO[8]);
	glBufferData(GL_ARRAY_BUFFER, 18 * sizeof(float), stern, GL_STATIC_DRAW);
	// positions
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), 0);
	// colors
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
#pragma endregion

#pragma endregion


	// Load shaders and create shader program

	shVertex.LoadShader("data\\shaders\\shader.vert", GL_VERTEX_SHADER);
	shFragment.LoadShader("data\\shaders\\shader.frag", GL_FRAGMENT_SHADER);

	spMain.CreateProgram();
	spMain.AddShaderToProgram(&shVertex);
	spMain.AddShaderToProgram(&shFragment);

	spMain.LinkProgram();
	spMain.UseProgram();
}

// Renders whole scene.
// lpParam - Pointer to anything you want.
void RenderScene(LPVOID lpParam)
{
	// Typecast lpParam to COpenGLControl pointer
	COpenGLControl* oglControl = (COpenGLControl*)lpParam;

	// We just clear color
	glClear(GL_COLOR_BUFFER_BIT);

	// Square
	glBindVertexArray(uiVAO[0]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	// Tree
	// UP
	glBindVertexArray(uiVAO[1]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// MID
	glBindVertexArray(uiVAO[2]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// DOWN
	glBindVertexArray(uiVAO[3]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// TREE LEG
	glBindVertexArray(uiVAO[4]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);


	// Ship
	// FLAG
	glBindVertexArray(uiVAO[5]);
	glDrawArrays(GL_TRIANGLES, 0, 3);
	// MAST
	glBindVertexArray(uiVAO[6]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	// VESSEL
	glBindVertexArray(uiVAO[7]);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	// STERN
	glBindVertexArray(uiVAO[8]);
	glDrawArrays(GL_TRIANGLES, 0, 3);

	oglControl->SwapBuffersM();
}

// Releases OpenGL scene.
// lpParam - Pointer to anything you want.
void ReleaseScene(LPVOID lpParam)
{
	spMain.DeleteProgram();

	shVertex.DeleteShader();
	shFragment.DeleteShader();
}