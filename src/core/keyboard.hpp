#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include "core/keyboard_keys.hpp"

namespace mg {
	class Keyboard {
		public:
			virtual bool isKeyDown(mg::KEY) const = 0;
	};
}

#endif //KEYBOARD_HPP
