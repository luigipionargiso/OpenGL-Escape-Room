#pragma once

#include <string>
#include "GL/glew.h"
#include "GLFW/glfw3.h"

struct Point2D
{
	float x, y;
};

typedef void (*function)();

class Window
{
private:
	GLFWwindow* m_Window;
	GLboolean fullscreen;
	static GLdouble m_deltaTime;
	static GLdouble m_lastFrame;
public:
	Window(GLuint width, GLuint height, std::string window_name);
	~Window();

	void MakeCurrent() const;
	bool IsOpen() const;
	void Close() const;

	bool GetKey(int key) const;
	bool GetMouseButton(int key) const;
	Point2D GetCursorPosition() const;
	bool isHovered() const;

	void SetWindowIcon(std::string icon_filepath) const;
	void ToggleFullscreen();

	void SetKeyCallback(function keyboard_callback) const;
	void SetWindowSizeCallback(function resize_callback) const;
	void SetFrameBufferSizeCallback(function frame_resize_callback) const;

	/* Screen coordinates don't necessarily correspond to pixels */
	std::tuple<GLint, GLint> GetFrameBufferSize() const;
	void SwapFrameBuffer();

	static void SetSwapInterval(GLint interval);
	static void PollEvents();
	static void WaitEvents();
	static void WaitEventsTimeout(GLdouble timeout);
	static void CloseAllWindows();
	static GLdouble GetTime() { return glfwGetTime(); }
	static GLdouble GetDeltaTime() { return m_deltaTime; }

	inline GLFWwindow* GetGLFWWindow() { return m_Window; }
};