#pragma once

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

namespace FrogEngine::Window {
    class Window {
    public:
        Window();
        ~Window();

        void initWindow();

        [[nodiscard]] bool getFullscreen() const;
        void setFullscreen(bool new_fullscreen);

        GLFWwindow *window{nullptr};

    private:
        GLFWmonitor *monitor{nullptr};
        const GLFWvidmode *mode{nullptr};

        int width{640}; // NOLINT
        int height{480}; // NOLINT
        int posX{};
        int posY{};
        bool fullscreen{false};
    };
}