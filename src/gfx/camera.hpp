#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>

namespace mg {
    class Camera {
        public:
            glm::mat4 projection, view, combined;
            glm::vec3 position, direction, up;
            glm::vec2 width, height;
            float near, far;

            virtual void update() = 0;
            virtual void lookAt(const glm::vec3&) = 0;

            virtual void normalizeUp() = 0;
            virtual void rotate(const glm::vec3&, float) = 0;
            virtual void translate(const glm::vec3&) = 0;
    };
}

#endif //CAMERA_HPP
