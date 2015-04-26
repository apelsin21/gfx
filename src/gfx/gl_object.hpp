#ifndef GL_OBJECT_HPP
#define GL_OBJECT_HPP

#define GLEW_STATIC
#include <GL/glew.h>

namespace gfx {
	class GLObject {
		public:
			GLuint id;
			GLObject();

            virtual void deleteID() = 0;
            virtual bool hasValidID() = 0;
	};
}

#endif //GL_OBJECT_HPP
