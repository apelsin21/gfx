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
}

#endif //COLOR_HPP
