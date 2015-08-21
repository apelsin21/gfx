#ifndef CAMERA_HPP
#define CAMERA_HPP

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <cstdio>

namespace CAMERA_HPP {
	class Camera {
		protected:
			glm::mat4 _model, _view, _projection;
			glm::vec3 _position, _rotation, _scale;
		public:
			const glm::mat4& getModelMatrix() const;
			const glm::mat4& getViewMatrix() const;
			const glm::mat4& getProjectionMatrix() const;

			virtual void setPosition(const glm::vec3&) = 0;
			virtual void setRotation(const glm::vec3&) = 0;
			virtual void setScale(const glm::vec3&) = 0;

			virtual const glm::vec3& getPosition() const = 0;
			virtual const glm::vec3& getRotation() const = 0;
			virtual const glm::vec3& getScale() const = 0;
	};
}

#endif //CAMERA_HPP
