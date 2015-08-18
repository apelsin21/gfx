#ifndef RENDERER_HPP
#define RENDERER_HPP

namespace mg {
	class Renderer {
		protected:
		public:
			virtual bool render2D(const glm::vec2&, const glm::vec2&, const glm::vec4%) = 0;
	};
}

#endif //RENDERER_HPP
