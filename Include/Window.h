#pragma once

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

namespace FrogEngine {
    class Window {
    public:
        Window();
        ~Window();

        void InitWindow();

        [[nodiscard]] bool GetFullscreen() const;
        void SetFullscreen(bool new_fullscreen);

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
} // namespace FrogEngine