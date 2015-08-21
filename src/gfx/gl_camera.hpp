#ifndef GL_CAMERA_HPP
#define GL_CAMERA_HPP

#include "gfx/camera.hpp"

namespace mg {
	class GLCamera : public Camera {
		protected:
		public:
			GLCamera();
			~GLCamera();

			const glm::mat4& getModelMatrix() const;
			const glm::mat4& getViewMatrix() const;
			const glm::mat4& getProjectionMatrix() const;

			void setPosition(const glm::vec3&);
			void setRotation(const glm::vec3&);
			void setScale(const glm::vec3&);

			const glm::vec3& getPosition() const;
			const glm::vec3& getRotation() const;
			const glm::vec3& getScale() const;
	};
}

#endif //GL_CAMERA_HPP
