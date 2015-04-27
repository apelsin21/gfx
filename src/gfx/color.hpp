#ifndef COLOR_HPP
#define COLOR_HPP

namespace gfx {
    class Color {
        public:
            Color() {
                this->r = 0.0f;
                this->g = 0.0f;
                this->b = 0.0f;
                this->a = 0.0f;
            }
            Color(float r, float g, float b, float a) {
                this->r = r;
                this->g = g;
                this->b = b;
                this->a = a;
            }
            ~Color() {
            }

            float r, g, b, a;
    };

    static const Color CLEAR = Color(0, 0, 0, 0);
    static const Color WHITE = Color(1, 1, 1, 1);
    static const Color BLACK = Color(0, 0, 0, 1);
    static const Color RED = Color(1, 0, 0, 1);
    static const Color GREEN = Color(0, 1, 0, 1);
    static const Color BLUE = Color(0, 0, 1, 1);
    static const Color LIGHT_GRAY = Color(0.75f, 0.75f, 0.75f, 1);
    static const Color GRAY = Color(0.5f, 0.5f, 0.5f, 1);
    static const Color DARK_GRAY = Color(0.25f, 0.25f, 0.25f, 1);
    static const Color PINK = Color(1, 0.68f, 0.68f, 1);
    static const Color ORANGE = Color(1, 0.78f, 0, 1);
    static const Color YELLOW = Color(1, 1, 0, 1);
    static const Color MAGENTA = Color(1, 0, 1, 1);
    static const Color CYAN = Color(0, 1, 1, 1);
    static const Color OLIVE = Color(0.5f, 0.5f, 0, 1);
    static const Color PURPLE = Color(0.5f, 0, 0.5f, 1);
    static const Color MAROON = Color(0.5f, 0, 0, 1);
    static const Color TEAL = Color(0, 0.5f, 0.5f, 1);
    static const Color NAVY = Color(0, 0, 0.5f, 1);
}

#endif //COLOR_HPP
