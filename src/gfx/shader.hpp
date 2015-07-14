#ifndef SHADER_HPP
#define SHADER_HPP

#include <stdio.h>
#include <string>
#include <stdexcept>
#include <fstream>

namespace mg {
    class Shader {
		protected:
            bool loaded, linked;
        public:
            Shader();

			bool isLoaded();
			bool isLinked();
    };
}

#endif //SHADER_HPP
