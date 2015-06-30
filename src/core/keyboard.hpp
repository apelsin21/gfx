#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

namespace mg {
	class Keyboard {
		public:
			virtual bool isKeyDown(const std::string&) = 0;
	};
}

#endif //KEYBOARD_HPP
