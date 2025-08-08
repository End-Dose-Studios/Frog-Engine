#pragma once

struct GLFWwindow;
struct GLFWmonitor;
struct GLFWvidmode;

namespace EngineCore {
    class Window {
    public:
        Window();
        ~Window();

        void InitWindow();

        [[nodiscard]] GLFWwindow *GetWindowPtr() const;
        [[nodiscard]] bool GetFullscreen() const;

        void SetFullscreen(bool new_fullscreen);

    private:
        GLFWwindow *window{nullptr};
        GLFWmonitor *monitor{nullptr};
        const GLFWvidmode *mode{nullptr};

        int width{640}; // NOLINT
        int height{480}; // NOLINT
        int posX{};
        int posY{};
        bool fullscreen{false};
    };
} // namespace EngineCore