#ifndef KEYBOARD_KEYS_HPP
#define KEYBOARD_KEYS_HPP

#include <SDL2/SDL_scancode.h>

namespace mg {
    enum class KEY {
        NONE,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
      
        NUM_1,
        NUM_2,
        NUM_3,
        NUM_4,
        NUM_5,
        NUM_6,
        NUM_7,
        NUM_8,
        NUM_9,
        NUM_0,
      
        RETURN,
        ESCAPE,
        BACKSPACE,
        TAB,
        SPACE,
      
        MINUS,
        EQUALS,
        LEFTBRACKET,
        RIGHTBRACKET,
        BACKSLASH,

        NONUSHASH,
 
        SEMICOLON,
        APOSTROPHE,
        GRAVE,
  
        COMMA,
        PERIOD,
        SLASH,
   
        CAPSLOCK,
    
        F1,
        F2,
        F3,
        F4,
        F5,
        F6,
        F7,
        F8,
        F9,
        F10,
        F11,
        F12,
      
        PRINTSCREEN,
        SCROLLLOCK,
        PAUSE,
        INSERT,
     
        HOME,
        PAGEUP,
        DELETE,
        END,
        PAGEDOWN,
        RIGHT,
        LEFT,
        DOWN,
        UP,
       
        NUMLOCKCLEAR,
        
        KP_DIVIDE,
        KP_MULTIPLY,
        KP_MINUS,
        KP_PLUS,
        KP_ENTER,
        KP_1,
        KP_2,
        KP_3,
        KP_4,
        KP_5,
        KP_6,
        KP_7,
        KP_8,
        KP_9,
        KP_0,
        KP_PERIOD,
        
        NONUSBACKSLASH,
                   
        APPLICATION,
        POWER,
        
        KP_EQUALS,
        F13,
        F14,
        F15,
        F16,
        F17,
        F18,
        F19,
        F20,
        F21,
        F22,
        F23,
        F24,
        EXECUTE,
        HELP,
        MENU,
        SELECT,
        STOP,
        AGAIN,
        UNDO,
        CUT,
        COPY,
        PASTE,
        FIND,
        MUTE,
        VOLUMEUP,
        VOLUMEDOWN,
        
        KP_COMMA,
        KP_EQUALSAS400,
       
        INTERNATIONAL1,
        
        INTERNATIONAL2,
        INTERNATIONAL3,
        INTERNATIONAL4,
        INTERNATIONAL5,
        INTERNATIONAL6,
        INTERNATIONAL7,
        INTERNATIONAL8,
        INTERNATIONAL9,
        LANG1,
        LANG2,
        LANG3,
        LANG4,
        LANG5,
        LANG6,
        LANG7,
        LANG8,
        LANG9,

        ALTERASE,
        SYSREQ,
        CANCEL,
        CLEAR,
        PRIOR,
        RETURN2,
        SEPARATOR,
        OUT,
        OPER,
        CLEARAGAIN,
        CRSEL,
        EXSEL,
        
        KP_00,
        KP_000,
        THOUSANDSSEPARATOR,
        DECIMALSEPARATOR,
        CURRENCYUNIT,
        CURRENCYSUBUNIT,
        KP_LEFTPAREN,
        KP_RIGHTPAREN,
        KP_LEFTBRACE,
        KP_RIGHTBRACE,
        KP_TAB,
        KP_BACKSPACE,
        KP_A,
        KP_B,
        KP_C,
        KP_D,
        KP_E,
        KP_F,
        KP_XOR,
        KP_POWER,
        KP_PERCENT,
        KP_LESS,
        KP_GREATER,
        KP_AMPERSAND,
        KP_DBLAMPERSAND,
        KP_VERTICALBAR,
        KP_DBLVERTICALBAR,
        KP_COLON,
        KP_HASH,
        KP_SPACE,
        KP_AT,
        KP_EXCLAM,
        KP_MEMSTORE,
        KP_MEMRECALL,
        KP_MEMCLEAR,
        KP_MEMADD,
        KP_MEMSUBTRACT,
        KP_MEMMULTIPLY,
        KP_MEMDIVIDE,
        KP_PLUSMINUS,
        KP_CLEAR,
        KP_CLEARENTRY,
        KP_BINARY,
        KP_OCTAL,
        KP_DECIMAL,
        KP_HEXADECIMAL,
        
        LCTRL,
        LSHIFT,
        LALT,
        LGUI,
        RCTRL,
        RSHIFT,
        RALT,
        RGUI,

        MODE,

        AUDIONEXT,
        AUDIOPREV,
        AUDIOSTOP,
        AUDIOPLAY,
        AUDIOMUTE,
        MEDIASELECT,
        WWW,
        MAIL,
        CALCULATOR,
        COMPUTER,
        AC_SEARCH,
        AC_HOME,
        AC_BACK,
        AC_FORWARD,
        AC_STOP,
        AC_REFRESH,
        AC_BOOKMARKS,
       
        BRIGHTNESSDOWN,
        BRIGHTNESSUP,
        DISPLAYSWITCH,
        
        KBDILLUMTOGGLE,
        KBDILLUMDOWN,
        KBDILLUMUP,
        EJECT,
        SLEEP,
        
        APP1,
        APP2,
    };

	static SDL_Scancode convertKeyToSDLScancode(mg::KEY mgKey) {
		SDL_Scancode sdlKey = SDL_SCANCODE_UNKNOWN;

    	switch(mgKey) {
    	    case mg::KEY::A:
    	        sdlKey = SDL_SCANCODE_A;
    	        break;
    	    case mg::KEY::B:
    	        sdlKey = SDL_SCANCODE_B;
    	        break;
    	    case mg::KEY::C:
    	        sdlKey = SDL_SCANCODE_C;
    	        break;
    	    case mg::KEY::D:
    	        sdlKey = SDL_SCANCODE_D;
    	        break;
    	    case mg::KEY::E:
    	        sdlKey = SDL_SCANCODE_E;
    	        break;
    	    case mg::KEY::F:
    	        sdlKey = SDL_SCANCODE_F;
    	        break;
    	    case mg::KEY::G:
    	        sdlKey = SDL_SCANCODE_G;
    	        break;
    	    case mg::KEY::H:
    	        sdlKey = SDL_SCANCODE_H;
    	        break;
    	    case mg::KEY::I:
    	        sdlKey = SDL_SCANCODE_I;
    	        break;
    	    case mg::KEY::J:
    	        sdlKey = SDL_SCANCODE_J;
    	        break;
    	    case mg::KEY::K:
    	        sdlKey = SDL_SCANCODE_K;
    	        break;
    	    case mg::KEY::L:
    	        sdlKey = SDL_SCANCODE_L;
    	        break;
    	    case mg::KEY::M:
    	        sdlKey = SDL_SCANCODE_M;
    	        break;
    	    case mg::KEY::N:
    	        sdlKey = SDL_SCANCODE_N;
    	        break;
    	    case mg::KEY::O:
    	        sdlKey = SDL_SCANCODE_O;
    	        break;
    	    case mg::KEY::P:
    	        sdlKey = SDL_SCANCODE_P;
    	        break;
    	    case mg::KEY::Q:
    	        sdlKey = SDL_SCANCODE_Q;
    	        break;
    	    case mg::KEY::R:
    	        sdlKey = SDL_SCANCODE_R;
    	        break;
    	    case mg::KEY::S:
    	        sdlKey = SDL_SCANCODE_S;
    	        break;
    	    case mg::KEY::T:
    	        sdlKey = SDL_SCANCODE_T;
    	        break;
    	    case mg::KEY::U:
    	        sdlKey = SDL_SCANCODE_U;
    	        break;
    	    case mg::KEY::V:
    	        sdlKey = SDL_SCANCODE_V;
    	        break;
    	    case mg::KEY::W:
    	        sdlKey = SDL_SCANCODE_W;
    	        break;
    	    case mg::KEY::X:
    	        sdlKey = SDL_SCANCODE_X;
    	        break;
    	    case mg::KEY::Y:
    	        sdlKey = SDL_SCANCODE_Y;
    	        break;
    	    case mg::KEY::Z:
    	        sdlKey = SDL_SCANCODE_Z;
    	        break;
    	    case mg::KEY::F1:
    	        sdlKey = SDL_SCANCODE_F1;
    	        break;
    	    case mg::KEY::F2:
    	        sdlKey = SDL_SCANCODE_F2;
    	        break;
    	    case mg::KEY::F3:
    	        sdlKey = SDL_SCANCODE_F3;
    	        break;
    	    case mg::KEY::F4:
    	        sdlKey = SDL_SCANCODE_F4;
    	        break;
    	    case mg::KEY::F5:
    	        sdlKey = SDL_SCANCODE_F5;
    	        break;
    	    case mg::KEY::F6:
    	        sdlKey = SDL_SCANCODE_F6;
    	        break;
    	    case mg::KEY::F7:
    	        sdlKey = SDL_SCANCODE_F7;
    	        break;
    	    case mg::KEY::F8:
    	        sdlKey = SDL_SCANCODE_F8;
    	        break;
    	    case mg::KEY::F9:
    	        sdlKey = SDL_SCANCODE_F9;
    	        break;
    	    case mg::KEY::F10:
    	        sdlKey = SDL_SCANCODE_F10;
    	        break;
    	    case mg::KEY::F11:
    	        sdlKey = SDL_SCANCODE_F11;
    	        break;
    	    case mg::KEY::F12:
    	        sdlKey = SDL_SCANCODE_F12;
    	        break;

    	    case mg::KEY::ESCAPE:
    	        sdlKey = SDL_SCANCODE_ESCAPE;
    	        break;
			case mg::KEY::BACKSPACE:
				sdlKey = SDL_SCANCODE_BACKSPACE;
				break;
			case mg::KEY::SPACE:
				sdlKey = SDL_SCANCODE_SPACE;
				break;
    	    case mg::KEY::RETURN:
    	        sdlKey = SDL_SCANCODE_RETURN;
    	        break;
    	    case mg::KEY::TAB:
    	        sdlKey = SDL_SCANCODE_TAB;
    	        break;

    	    case mg::KEY::NUM_1:
    	        sdlKey = SDL_SCANCODE_1;
    	        break;
    	    case mg::KEY::NUM_2:
    	        sdlKey = SDL_SCANCODE_2;
    	        break;
    	    case mg::KEY::NUM_3:
    	        sdlKey = SDL_SCANCODE_3;
    	        break;
    	    case mg::KEY::NUM_4:
    	        sdlKey = SDL_SCANCODE_4;
    	        break;
    	    case mg::KEY::NUM_5:
    	        sdlKey = SDL_SCANCODE_5;
    	        break;
    	    case mg::KEY::NUM_6:
    	        sdlKey = SDL_SCANCODE_6;
    	        break;
    	    case mg::KEY::NUM_7:
    	        sdlKey = SDL_SCANCODE_7;
    	        break;
    	    case mg::KEY::NUM_8:
    	        sdlKey = SDL_SCANCODE_8;
    	        break;
    	    case mg::KEY::NUM_9:
    	        sdlKey = SDL_SCANCODE_9;
    	        break;
    	    case mg::KEY::NUM_0:
    	        sdlKey = SDL_SCANCODE_0;
    	        break;

    	    case mg::KEY::UP:
    	        sdlKey = SDL_SCANCODE_UP;
    	        break;
    	    case mg::KEY::DOWN:
    	        sdlKey = SDL_SCANCODE_DOWN;
    	        break;
    	    case mg::KEY::LEFT:
    	        sdlKey = SDL_SCANCODE_LEFT;
    	        break;
    	    case mg::KEY::RIGHT:
    	        sdlKey = SDL_SCANCODE_RIGHT;
    	        break;
    	    default:
    	        break;
    	}

		return sdlKey;
	}
	static mg::KEY convertSDLScancodeToKey(SDL_Scancode sdlKey) {
		mg::KEY mgKey = mg::KEY::NONE;

    	switch(mgKey) {
    	    case mg::KEY::A:
    	        sdlKey = SDL_SCANCODE_A;
    	        break;
    	    case mg::KEY::B:
    	        sdlKey = SDL_SCANCODE_B;
    	        break;
    	    case mg::KEY::C:
    	        sdlKey = SDL_SCANCODE_C;
    	        break;
    	    case mg::KEY::D:
    	        sdlKey = SDL_SCANCODE_D;
    	        break;
    	    case mg::KEY::E:
    	        sdlKey = SDL_SCANCODE_E;
    	        break;
    	    case mg::KEY::F:
    	        sdlKey = SDL_SCANCODE_F;
    	        break;
    	    case mg::KEY::G:
    	        sdlKey = SDL_SCANCODE_G;
    	        break;
    	    case mg::KEY::H:
    	        sdlKey = SDL_SCANCODE_H;
    	        break;
    	    case mg::KEY::I:
    	        sdlKey = SDL_SCANCODE_I;
    	        break;
    	    case mg::KEY::J:
    	        sdlKey = SDL_SCANCODE_J;
    	        break;
    	    case mg::KEY::K:
    	        sdlKey = SDL_SCANCODE_K;
    	        break;
    	    case mg::KEY::L:
    	        sdlKey = SDL_SCANCODE_L;
    	        break;
    	    case mg::KEY::M:
    	        sdlKey = SDL_SCANCODE_M;
    	        break;
    	    case mg::KEY::N:
    	        sdlKey = SDL_SCANCODE_N;
    	        break;
    	    case mg::KEY::O:
    	        sdlKey = SDL_SCANCODE_O;
    	        break;
    	    case mg::KEY::P:
    	        sdlKey = SDL_SCANCODE_P;
    	        break;
    	    case mg::KEY::Q:
    	        sdlKey = SDL_SCANCODE_Q;
    	        break;
    	    case mg::KEY::R:
    	        sdlKey = SDL_SCANCODE_R;
    	        break;
    	    case mg::KEY::S:
    	        sdlKey = SDL_SCANCODE_S;
    	        break;
    	    case mg::KEY::T:
    	        sdlKey = SDL_SCANCODE_T;
    	        break;
    	    case mg::KEY::U:
    	        sdlKey = SDL_SCANCODE_U;
    	        break;
    	    case mg::KEY::V:
    	        sdlKey = SDL_SCANCODE_V;
    	        break;
    	    case mg::KEY::W:
    	        sdlKey = SDL_SCANCODE_W;
    	        break;
    	    case mg::KEY::X:
    	        sdlKey = SDL_SCANCODE_X;
    	        break;
    	    case mg::KEY::Y:
    	        sdlKey = SDL_SCANCODE_Y;
    	        break;
    	    case mg::KEY::Z:
    	        sdlKey = SDL_SCANCODE_Z;
    	        break;
    	    case mg::KEY::F1:
    	        sdlKey = SDL_SCANCODE_F1;
    	        break;
    	    case mg::KEY::F2:
    	        sdlKey = SDL_SCANCODE_F2;
    	        break;
    	    case mg::KEY::F3:
    	        sdlKey = SDL_SCANCODE_F3;
    	        break;
    	    case mg::KEY::F4:
    	        sdlKey = SDL_SCANCODE_F4;
    	        break;
    	    case mg::KEY::F5:
    	        sdlKey = SDL_SCANCODE_F5;
    	        break;
    	    case mg::KEY::F6:
    	        sdlKey = SDL_SCANCODE_F6;
    	        break;
    	    case mg::KEY::F7:
    	        sdlKey = SDL_SCANCODE_F7;
    	        break;
    	    case mg::KEY::F8:
    	        sdlKey = SDL_SCANCODE_F8;
    	        break;
    	    case mg::KEY::F9:
    	        sdlKey = SDL_SCANCODE_F9;
    	        break;
    	    case mg::KEY::F10:
    	        sdlKey = SDL_SCANCODE_F10;
    	        break;
    	    case mg::KEY::F11:
    	        sdlKey = SDL_SCANCODE_F11;
    	        break;
    	    case mg::KEY::F12:
    	        sdlKey = SDL_SCANCODE_F12;
    	        break;

    	    case mg::KEY::ESCAPE:
    	        sdlKey = SDL_SCANCODE_ESCAPE;
    	        break;
			case mg::KEY::BACKSPACE:
				sdlKey = SDL_SCANCODE_BACKSPACE;
				break;
			case mg::KEY::SPACE:
				sdlKey = SDL_SCANCODE_SPACE;
				break;
    	    case mg::KEY::RETURN:
    	        sdlKey = SDL_SCANCODE_RETURN;
    	        break;
    	    case mg::KEY::TAB:
    	        sdlKey = SDL_SCANCODE_TAB;
    	        break;

    	    case mg::KEY::NUM_1:
    	        sdlKey = SDL_SCANCODE_1;
    	        break;
    	    case mg::KEY::NUM_2:
    	        sdlKey = SDL_SCANCODE_2;
    	        break;
    	    case mg::KEY::NUM_3:
    	        sdlKey = SDL_SCANCODE_3;
    	        break;
    	    case mg::KEY::NUM_4:
    	        sdlKey = SDL_SCANCODE_4;
    	        break;
    	    case mg::KEY::NUM_5:
    	        sdlKey = SDL_SCANCODE_5;
    	        break;
    	    case mg::KEY::NUM_6:
    	        sdlKey = SDL_SCANCODE_6;
    	        break;
    	    case mg::KEY::NUM_7:
    	        sdlKey = SDL_SCANCODE_7;
    	        break;
    	    case mg::KEY::NUM_8:
    	        sdlKey = SDL_SCANCODE_8;
    	        break;
    	    case mg::KEY::NUM_9:
    	        sdlKey = SDL_SCANCODE_9;
    	        break;
    	    case mg::KEY::NUM_0:
    	        sdlKey = SDL_SCANCODE_0;
    	        break;
    	    default:
    	        break;
    	}

		return mgKey;
	}

	static wchar_t convertKeyToString(mg::KEY mgKey) {
		wchar_t returnChar = '\0';

    	switch(mgKey) {
    	    case mg::KEY::A:
				returnChar = 'a';
    	        break;
    	    case mg::KEY::B:
				returnChar = 'b';
    	        break;
    	    case mg::KEY::C:
				returnChar = 'c';
    	        break;
    	    case mg::KEY::D:
				returnChar = 'd';
    	        break;
    	    case mg::KEY::E:
				returnChar = 'e';
    	        break;
    	    case mg::KEY::F:
				returnChar = 'f';
    	        break;
    	    case mg::KEY::G:
				returnChar = 'g';
    	        break;
    	    case mg::KEY::H:
				returnChar = 'h';
    	        break;
    	    case mg::KEY::I:
				returnChar = 'i';
    	        break;
    	    case mg::KEY::J:
				returnChar = 'j';
    	        break;
    	    case mg::KEY::K:
				returnChar = 'k';
    	        break;
    	    case mg::KEY::L:
				returnChar = 'l';
    	        break;
    	    case mg::KEY::M:
				returnChar = 'm';
    	        break;
    	    case mg::KEY::N:
				returnChar = 'n';
    	        break;
    	    case mg::KEY::O:
				returnChar = 'o';
    	        break;
    	    case mg::KEY::P:
				returnChar = 'p';
    	        break;
    	    case mg::KEY::Q:
				returnChar = 'q';
    	        break;
    	    case mg::KEY::R:
				returnChar = 'r';
    	        break;
    	    case mg::KEY::S:
				returnChar = 's';
    	        break;
    	    case mg::KEY::T:
				returnChar = 't';
    	        break;
    	    case mg::KEY::U:
				returnChar = 'u';
    	        break;
    	    case mg::KEY::V:
				returnChar = 'v';
    	        break;
    	    case mg::KEY::W:
				returnChar = 'w';
    	        break;
    	    case mg::KEY::X:
				returnChar = 'x';
    	        break;
    	    case mg::KEY::Y:
				returnChar = 'y';
    	        break;
    	    case mg::KEY::Z:
				returnChar = 'z';
    	        break;
			case mg::KEY::SPACE:
				returnChar = ' ';
				break;
    	    case mg::KEY::RETURN:
				returnChar = '\n';
    	        break;
    	    case mg::KEY::TAB:
				returnChar = '\t';
    	        break;
    	    case mg::KEY::NUM_1:
				returnChar = '1';
    	        break;
    	    case mg::KEY::NUM_2:
				returnChar = '2';
    	        break;
    	    case mg::KEY::NUM_3:
				returnChar = '3';
    	        break;
    	    case mg::KEY::NUM_4:
				returnChar = '4';
    	        break;
    	    case mg::KEY::NUM_5:
				returnChar = '5';
    	        break;
    	    case mg::KEY::NUM_6:
				returnChar = '6';
    	        break;
    	    case mg::KEY::NUM_7:
				returnChar = '7';
    	        break;
    	    case mg::KEY::NUM_8:
				returnChar = '8';
    	        break;
    	    case mg::KEY::NUM_9:
				returnChar = '9';
    	        break;
    	    case mg::KEY::NUM_0:
				returnChar = '0';
    	        break;
    	    default:
    	        break;
    	}

		return returnChar;
	}
}

#endif //KEYBOARD_KEYS_HPP
