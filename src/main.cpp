
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <CommonFunctions.h>

#include <Shader.h>

#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window, Shader shaderObj);

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

/*
location very important
tied to:
glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
the first argument is index which has to be tied to location

then
glEnableVertexAttribArray(0);

*/

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "The window title", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

	//Bind the VAO
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);


	//Load the shaders

    Shader myShader("Shaders/vertexShader.vs", "Shaders/fragmentShader.fs");

	float vertices[] = {
	    //position       //colors
		0.1f,0.1f, 0.0f, 1.0f, 0.0f, 0.0f,
		0.7f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.7f, 0.0f, 0.0f, 0.0f, 1.0f
	};

	//Bind the VBO
	GLuint VBO2;

	//first param is number of buffers to be generated
	glGenBuffers(1, &VBO2);
	glBindBuffer(GL_ARRAY_BUFFER, VBO2);

	//put data into buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	//assign data in the format
	//size is number of componenets 2 would also work (position and color)

	//First one is index
	//Second is number of values per vertex
	//Third is type of value
	//Fourth is whether we should normalize
	//Fifth is the stride (number of bytes till next value
    //Sixth is the starting value
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);

	//Second attirbute pointer will be color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3* sizeof(float)));


	//Enable the VAO
	//0 because vertex glVertexAttribPointer index is 0
	//and also shader location is 0
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	//





    //make sure any shader specific changes are called after this line
    //as this activates the shader
    myShader.use();


    //int vertexColorLocation = glGetUniformLocation(myShader.ID, "ourColor");
    //glUniform4f(vertexColorLocation, 0.4f, 0.4f, 0.4f, 1.0f);

    myShader.setFloat("customColor", 0.4f);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // input
        // -----
        processInput(window, myShader);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glDrawArrays(GL_TRIANGLES, 0, 3);

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

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window, Shader shaderObj)
{
    if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    {
        glfwSetWindowShouldClose(window, true);
    }

    if(glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
    {
        shaderObj.setFloat("customColor", 0.7f);
    }

    if(glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS)
    {
        shaderObj.setFloat("customColor", 0.3f);
    }

}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}
