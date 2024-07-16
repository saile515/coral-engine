#pragma once

struct GLFWwindow;

namespace coral {

class Window {
  private:
    GLFWwindow *m_window_handle;

  public:
    Window();

    void make_current();
};

} // namespace coral
