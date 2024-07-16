#include "window.hpp"
#include "log.hpp"
#include <GLFW/glfw3.h>

namespace coral {

Window::Window() {
    if (!glfwInit()) {
        error("GLFW failed to initialize.");
        return;
    }

    m_window_handle = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);

    if (!m_window_handle) {
        glfwTerminate();
        error("Failed to create window.");
        return;
    }
}

void Window::make_current() { glfwMakeContextCurrent(m_window_handle); }

} // namespace coral
