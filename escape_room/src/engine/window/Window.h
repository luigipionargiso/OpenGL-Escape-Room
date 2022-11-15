#pragma once

#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct Point2D
{
	double x, y;
};

class Window
{
private:
	GLFWwindow* m_Window;
	GLboolean m_fullscreen;
	static GLdouble deltaTime;
	static GLdouble lastFrame;
public:
	Window(GLuint width, GLuint height, std::string window_name);
	~Window() = default;

	void MakeCurrent() const { glfwMakeContextCurrent(m_Window); }
	bool IsOpen() const { return !glfwWindowShouldClose(m_Window); }
	void Close() const { glfwWindowShouldClose(m_Window); }

	bool GetKey(int key) const;
	bool GetMouseButton(int key) const;
	Point2D GetCursorPosition() const;
	//void SetCursorPosition(double xpos, double ypos) const;
	bool IsHovered() const;

	void SetWindowIcon(std::string icon_filepath) const;
	void ToggleFullscreen();

	/* Screen coordinates don't necessarily correspond to pixels */
	std::tuple<GLint, GLint> GetFrameBufferSize() const;
	void SwapFrameBuffer();

	static void SetSwapInterval(GLint interval) { glfwSwapInterval(interval); }
	static void PollEvents() { glfwPollEvents(); }
	static void WaitEvents() { glfwWaitEvents(); }
	static void WaitEventsTimeout(GLdouble timeout) { glfwWaitEventsTimeout(timeout); }
	static void CloseAllWindows() { glfwTerminate(); }
	static GLdouble GetTime() { return glfwGetTime(); }
	static GLdouble GetDeltaTime() { return Window::deltaTime; }

	inline GLFWwindow* GetGLFWWindow() { return m_Window; }
};