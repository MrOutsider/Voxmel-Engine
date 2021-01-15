#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

// Declarations
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// Settings
const uint32_t WINDOW_WIDTH = 800;
const uint32_t WINDOW_HEIGHT = 600;

const char* vertexShaderSource = "#version 330 core\n"
	"layout (location = 0) in vec3 aPos;\n"
	"void main()\n"
	"{\n"
	"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
	"}\0";

const char* fragmentShaderSource = "#version 330 core\n"
	"out vec4 FragColor;\n"
	"uniform vec4 ourColor;\n"
	"void main()\n"
	"{\n"
	"	FragColor = ourColor;\n"
	"}\0";

int main()
{
	// GLFW : Init and config window
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

	// GLFW : Create window
	GLFWwindow* window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Voxmel Engine", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window." << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	// GLFW : Init and setup the viewport change callback
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);


	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to init GLAD." << std::endl;
		return -1;
	}

	// Build & compile shaders
	//-------------------------
	// Vertex Shader
	uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);	// Assign the id of the shader to this unint
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);		// Compile the source for shader into the id
	glCompileShader(vertexShader);
	// Vars for shader compile check
	int success;
	char infoLog[512];
	// Check if shader compiled without error
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Fragment Shader
	uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// Check if shader compiled without error
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	// Shader Program
	uint32_t shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// Check if program linked without error
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}

	// Delete the shaders
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	float vertices[] = {
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
	};
	uint32_t indices[] = {  // note that we start from 0!
		0, 1, 2
	};

	// Gen and asaign these var IDs
	uint32_t VAO, VBO, EBO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);
	// Copy vertices array into a Vertex Buffer Object for OpenGL to use
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	// Copy indices array into an Element Array Buffer Object for OpenGL to reuse verts from the VBO
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	// Set the vertex attributes pointers
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0) // Only unbind when VAO is not in use
	glBindVertexArray(0); // Unbind the VAO so it is not chanched further

	// DEBUG : Draw wireframe
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

	// Timesteps
	double limitFPS = 1.0 / 60.0, limitPhysicsSteps = 1.0 / 30.0;
	double lastTime = glfwGetTime(), nowTime = 0, timer = lastTime;
	double deltaTimeRender = 0, deltaTimePhysics = 0;
	int frames = 0, physicsUpdates = 0;

	// Main Loop
	while (!glfwWindowShouldClose(window))
	{
		// Timestep
		nowTime = glfwGetTime();
		deltaTimeRender += (nowTime - lastTime) / limitFPS;
		deltaTimePhysics += (nowTime - lastTime) / limitPhysicsSteps;
		lastTime = nowTime;

		// Input
		processInput(window);

		if (deltaTimePhysics >= 1.0)
		{
			deltaTimePhysics--;
			physicsUpdates++;

			// Do physics here
		}

		if (deltaTimeRender >= 1.0)
		{
			deltaTimeRender--;
			frames++;

			// Do Update() stuff before rendering

			// Rendering commands
			glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);

			// Draw Here
			float timeValue = glfwGetTime();
			float greenValue = (sin(timeValue) / 2.0f) + 0.5f;
			int vertexColorLocation = glGetUniformLocation(shaderProgram, "ourColor");
			glUseProgram(shaderProgram);
			glUniform4f(vertexColorLocation, 0.0f, greenValue, 0.0f, 1.0f);
			glBindVertexArray(VAO);
			glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
			//glBindVertexArray(0); // Only one VAO used so no need to unbind after every loop

			// Check/Call events and swap buffers
			glfwSwapBuffers(window);
			glfwPollEvents();
		}

		// Reset the updates and fps counter every second
		if (glfwGetTime() - timer > 1.0)
		{
			timer++;
			//std::cout << "FPS: " << frames << " Physics Updates:" << physicsUpdates << std::endl;
			physicsUpdates = 0, frames = 0;
		}
	}

	// Release resources
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteProgram(shaderProgram);

	glfwTerminate();
	return 0;
}

// This func is the callback to change the viewport size
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}

// This function is looped to detect input
void processInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, true);
	}
}