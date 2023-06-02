#include "Mesh.h"



const unsigned int width = 800;
const unsigned int height = 800;


Vertex lightVertices[] = { //     COORDINATES     //
	Vertex{ glm::vec3(-0.1f, -0.1f, 0.1f) },
	Vertex{ glm::vec3(-0.1f, -0.1f, -0.1f) },
	Vertex{ glm::vec3(0.1f, -0.1f, -0.1f) },
	Vertex{ glm::vec3(0.1f, -0.1f, 0.1f) },
	Vertex{ glm::vec3(-0.1f, 0.1f, 0.1f) },
	Vertex{ glm::vec3(-0.1f, 0.1f, -0.1f) },
	Vertex{ glm::vec3(0.1f, 0.1f, -0.1f) },
	Vertex{ glm::vec3(0.1f, 0.1f, 0.1f) }
};

GLuint lightIndices[] = {
	0, 1, 2,
	0, 2, 3,
	0, 4, 7,
	0, 7, 3,
	3, 7, 6,
	3, 6, 2,
	2, 6, 5,
	2, 5, 1,
	1, 5, 4,
	1, 4, 0,
	4, 5, 6,
	4, 6, 7
};

	// Vertex i indices dla œcian prostopad³ych do kamery
std::vector<Vertex> wall_vertices = {
	{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
	{ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(1.0f, 1.0f, 0.0f), glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) }
};

std::vector<GLuint> wall_indices = {
	0, 1, 2,
	1, 3, 2
};

	// Vertex i indices dla œcian równoleg³cyh do kamery
std::vector<Vertex> wall_vertices2 = {
	{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 0.0f) },
	{ glm::vec3(0.0f, 0.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 0.0f) },
	{ glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(0.0f, 1.0f) },
	{ glm::vec3(0.0f, 1.0f, -1.0f), glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(1.0f, 1.0f, 1.0f), glm::vec2(1.0f, 1.0f) }
};

std::vector<GLuint> wall_indices2 = {
	0, 1, 2,
	1, 3, 2
};

int main() {
	// Initialize GLFW
	glfwInit();

	// Tell GLFW what version of OpenGL we are using
	// In this case we are using OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	// Tell GLFW we are using the CORE profile
	// So that means we only have the modern functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Create a GLFWwindow object of 800 by 800 pixels, naming it "YoutubeOpenGL"
	GLFWwindow* window = glfwCreateWindow(width, height, "YoutubeOpenGL", NULL, NULL);
	// Error check if the window fails to create
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	// Introduce the window into the current context
	glfwMakeContextCurrent(window);

	//Load GLAD so it configures OpenGL
	gladLoadGL();
	// Specify the viewport of OpenGL in the Window
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
	glViewport(0, 0, width, height);

	// Texture data
	Texture textures[]{
		Texture("planks.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("planksSpec.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};

	Texture wall_textures[]{
		Texture("dirt.png", "diffuse", 0, GL_RGBA, GL_UNSIGNED_BYTE),
		Texture("dirt.png", "specular", 1, GL_RED, GL_UNSIGNED_BYTE)
	};


	std::vector<Texture> tex(textures, textures + sizeof(textures) / sizeof(Texture));
	std::vector<Texture> wall_tex(wall_textures, wall_textures + sizeof(wall_textures) / sizeof(Texture));


	// 4 œcianki prostopad³ych do kamery
	Shader wallShader("default.vert", "default.frag");
	Mesh wall(wall_vertices, wall_indices, wall_tex);
	Shader wall2Shader("default.vert", "default.frag");
	Mesh wall2(wall_vertices, wall_indices, wall_tex);
	Shader wall3Shader("default.vert", "default.frag");
	Mesh wall3(wall_vertices, wall_indices, wall_tex);
	Shader wall4Shader("default.vert", "default.frag");
	Mesh wall4(wall_vertices, wall_indices, wall_tex);

	// 6 œcianek równoleg³ych z kamer¹


	//// 6 odwróconych œcianek
	Shader wall5Shader("default.vert", "default.frag");
	Mesh wall5(wall_vertices2, wall_indices2, wall_tex);
	Shader wall6Shader("default.vert", "default.frag");
	Mesh wall6(wall_vertices2, wall_indices2, wall_tex);
	Shader wall7Shader("default.vert", "default.frag");
	Mesh wall7(wall_vertices2, wall_indices2, wall_tex);
	Shader wall8Shader("default.vert", "default.frag");
	Mesh wall8(wall_vertices2, wall_indices2, wall_tex);
	Shader wall9Shader("default.vert", "default.frag");
	Mesh wall9(wall_vertices2, wall_indices2, wall_tex);
	Shader wall10Shader("default.vert", "default.frag");
	Mesh wall10(wall_vertices2, wall_indices2, wall_tex);


	// Shader for light cube
	Shader lightShader("light.vert", "light.frag");
	// Store mesh data in vectors for the mesh
	std::vector<Vertex> lightVerts(lightVertices, lightVertices + sizeof(lightVertices) / sizeof(Vertex));
	std::vector<GLuint> lightInd(lightIndices, lightIndices + sizeof(lightIndices) / sizeof(GLuint));
	Mesh light(lightVerts, lightInd, tex);

	glm::vec4 lightColor = glm::vec4(1.0f, 1.0f, 1.0f, 1.0f);
	glm::vec3 lightPos = glm::vec3(-1.0f, 3.0f, -1.0f);
	glm::mat4 lightModel = glm::mat4(1.0f);
	lightModel = glm::translate(lightModel, lightPos);

		// Prostopad³e
	glm::vec3 wallPos = glm::vec3(0.0f, 0.0f, -2.0f);
	glm::mat4 wallModel = glm::mat4(1.0f);
	wallModel = glm::translate(wallModel, wallPos);

	glm::vec3 wall2Pos = glm::vec3(-1.0f, 0.0f, -2.0f);
	glm::mat4 wall2Model = glm::mat4(1.0f);
	wall2Model = glm::translate(wall2Model, wall2Pos);

	glm::vec3 wall3Pos = glm::vec3(-1.0f, 0.0f, -1.0f);
	glm::mat4 wall3Model = glm::mat4(1.0f);
	wall3Model = glm::translate(wall3Model, wall3Pos);

	glm::vec3 wall4Pos = glm::vec3(-2.0f, 0.0f, -1.0f);
	glm::mat4 wall4Model = glm::mat4(1.0f);
	wall4Model = glm::translate(wall4Model, wall4Pos);

	// Równoleg³e
	glm::vec3 wall5Pos = glm::vec3(0.0f, 0.0f, 0.0f);
	glm::mat4 wall5Model = glm::mat4(1.0f);
	wall5Model = glm::translate(wall5Model, wall5Pos);

	glm::vec3 wall6Pos = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::mat4 wall6Model = glm::mat4(1.0f);
	wall6Model = glm::translate(wall6Model, wall6Pos);

	glm::vec3 wall7Pos = glm::vec3(1.0f, 0.0f, -1.0f);
	glm::mat4 wall7Model = glm::mat4(1.0f);
	wall7Model = glm::translate(wall7Model, wall7Pos);

	glm::vec3 wall8Pos = glm::vec3(-1.0f, 0.0f, -2.0f);
	glm::mat4 wall8Model = glm::mat4(1.0f);
	wall8Model = glm::translate(wall8Model, wall8Pos);

	glm::vec3 wall9Pos = glm::vec3(-2.0f, 0.0f, -1.0f);
	glm::mat4 wall9Model = glm::mat4(1.0f);
	wall9Model = glm::translate(wall9Model, wall9Pos);

	glm::vec3 wall10Pos = glm::vec3(-2.0f, 0.0f, -2.0f);
	glm::mat4 wall10Model = glm::mat4(1.0f);
	wall10Model = glm::translate(wall10Model, wall10Pos);

	// Œwiat³o
	lightShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(lightShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(lightModel));
	glUniform4f(glGetUniformLocation(lightShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);

	// Prostopad³e
	wallShader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(wallShader.ID, "model"), 1, GL_FALSE, glm::value_ptr(wallModel));
	glUniform4f(glGetUniformLocation(wallShader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(wallShader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	wall2Shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(wall2Shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(wall2Model));
	glUniform4f(glGetUniformLocation(wall2Shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(wall2Shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	wall3Shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(wall3Shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(wall3Model));
	glUniform4f(glGetUniformLocation(wall3Shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(wall3Shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	wall4Shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(wall4Shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(wall4Model));
	glUniform4f(glGetUniformLocation(wall4Shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(wall4Shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	// Równoleg³e
	wall5Shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(wall5Shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(wall5Model));
	glUniform4f(glGetUniformLocation(wall5Shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(wall5Shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	wall6Shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(wall6Shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(wall6Model));
	glUniform4f(glGetUniformLocation(wall4Shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(wall4Shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	wall7Shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(wall7Shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(wall7Model));
	glUniform4f(glGetUniformLocation(wall4Shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(wall4Shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	wall8Shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(wall8Shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(wall8Model));
	glUniform4f(glGetUniformLocation(wall4Shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(wall4Shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	wall9Shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(wall9Shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(wall9Model));
	glUniform4f(glGetUniformLocation(wall4Shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(wall4Shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);
	wall10Shader.Activate();
	glUniformMatrix4fv(glGetUniformLocation(wall10Shader.ID, "model"), 1, GL_FALSE, glm::value_ptr(wall10Model));
	glUniform4f(glGetUniformLocation(wall4Shader.ID, "lightColor"), lightColor.x, lightColor.y, lightColor.z, lightColor.w);
	glUniform3f(glGetUniformLocation(wall4Shader.ID, "lightPos"), lightPos.x, lightPos.y, lightPos.z);

	// Enables the Depth Buffer
	glEnable(GL_DEPTH_TEST);

	// Creates camera object
	Camera camera(width, height, glm::vec3(0.0f, 0.0f, 2.0f));


	// Main while loop
	while (!glfwWindowShouldClose(window)) {
		// Specify the color of the background
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and depth buffer
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


		// Handles camera inputs
		camera.Inputs(window);
		// Updates and exports the camera matrix to the Vertex Shader
		camera.updateMatrix(45.0f, 0.1f, 100.0f);


		// Draws different meshes
		light.Draw(lightShader, camera);
		wall.Draw(wallShader, camera);
		wall2.Draw(wall2Shader, camera);
		wall3.Draw(wall3Shader, camera);
		wall4.Draw(wall4Shader, camera);
		wall5.Draw(wall5Shader, camera);
		wall6.Draw(wall6Shader, camera);
		wall7.Draw(wall7Shader, camera);
		wall8.Draw(wall8Shader, camera);
		wall9.Draw(wall9Shader, camera);
		wall10.Draw(wall10Shader, camera);


		// Swap the back buffer with the front buffer
		glfwSwapBuffers(window);
		// Take care of all GLFW events
		glfwPollEvents();
	}



	// Delete all the objects we've created
	lightShader.Delete();
	wallShader.Delete();
	wall2Shader.Delete();
	wall3Shader.Delete();
	wall4Shader.Delete();
	wall5Shader.Delete();
	wall6Shader.Delete();
	wall7Shader.Delete();
	wall8Shader.Delete();
	wall9Shader.Delete();
	wall10Shader.Delete();

	//wall2Shader.Delete();
	// Delete window before ending the program
	glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
	glfwTerminate();
	return 0;
}