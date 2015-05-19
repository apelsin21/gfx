#ifndef ENGINE_HPP
#define ENGINE_HPP

#include <memory>
#include <exception>

#include "core/sdl2_window.hpp"
#include "gfx/context_settings.hpp"

namespace mg {
	class Engine {
		protected:
			std::shared_ptr<mg::SDL2Window> window;
		public:
			Engine();
			~Engine();
	
			template<typename T>
			std::shared_ptr<T> get();
	};
	
	template<typename SDL2Window>
	std::shared_ptr<SDL2Window> Engine::get() {
		if(this->window == nullptr) {
			this->window = std::make_shared<SDL2Window>();
		}

		return this->window;
	}
}



#endif //ENGINE_HPP
