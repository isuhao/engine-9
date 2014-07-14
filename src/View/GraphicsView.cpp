#include <stdexcept>
#include "GraphicsView.h"
#include "Sprite.h"

GraphicsView::GraphicsView()
{

}

GraphicsView::~GraphicsView()
{
    glfwTerminate();
}

void GraphicsView::Initialize()
{
    // Initialize the graphics library.
    GLFWwindow* window;
    glfwInit();
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
{
        glfwTerminate();
    }
    glfwMakeContextCurrent(window);
    this->window = window;
}

void GraphicsView::Update(GraphicsManager* graphicsManager)
{
	// Clear the screen
	Color clearColor = graphicsManager->GetClearColor();
	glClearColor(clearColor.red, clearColor.green, clearColor.blue, clearColor.alpha);
	
    glClear(GL_COLOR_BUFFER_BIT);

	int spriteNumber = graphicsManager->GetSpriteCount();
	float* vertexBuffer;
	float* colorBuffer;
	unsigned short* indexBuffer;
	vertexBuffer = new float[spriteNumber * 4 * 4]; // 4 vertices; 4 coordinates per vertex
	colorBuffer = new float[spriteNumber * 4 * 4]; // 4 vertieces; 4 channels per vertex
	indexBuffer = new unsigned short[spriteNumber * 2 * 3]; // 2 triangles; 3 indeces per triangle

	graphicsManager->AddSpritesToVCIBuffer(vertexBuffer, colorBuffer, indexBuffer, 0);

	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(4, GL_FLOAT, 0, vertexBuffer);
	glEnableClientState(GL_COLOR_ARRAY);
	glColorPointer(4, GL_FLOAT, 0, colorBuffer);

	glDrawElements(GL_TRIANGLES, 6 * spriteNumber, GL_UNSIGNED_SHORT, indexBuffer);
	
	// Swap the buffers
    glfwSwapBuffers(this->window);
    glfwPollEvents();
    
    // Call OnWindowClose if the user closed the Window.
    if(glfwWindowShouldClose(window) && this->OnWindowClose != NULL)
    {
        this->OnWindowClose();
    }
}

void GraphicsView::CheckOpenGLError()
{
	GLenum error = glGetError();
	switch (error)
	{
	case GL_NO_ERROR:
		return;
	case GL_INVALID_ENUM:
		throw new std::logic_error("There was an OpenGL Invalid Enum error.");
	case GL_INVALID_VALUE:
		throw new std::logic_error("There was an OpenGL Invalid Value error.");
	case GL_INVALID_OPERATION:
		throw new std::logic_error("There was an OpenGL Invalid Operation error.");
	case GL_OUT_OF_MEMORY:
		throw new std::logic_error("There was an OpenGL Out of Memory error.");
	case GL_STACK_UNDERFLOW:
		throw new std::logic_error("There was an OpenGL Stack Underflow error.");
	case GL_STACK_OVERFLOW:
		throw new std::logic_error("There was an OpenGL Stack Overflow error.");
	}
}