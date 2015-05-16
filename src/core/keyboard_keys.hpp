#ifndef KEYBOARD_KEYS_HPP
#define KEYBOARD_KEYS_HPP

#include <SDL2/SDL_scancode.h>

namespace mg {
    enum KEYBOARD_KEY {
        KEY_NONE,
        KEY_A = (int)'a',
        KEY_B = (int)'b',
        KEY_C = (int)'c',
        KEY_D = (int)'d',
        KEY_E = (int)'e',
        KEY_F = (int)'f',
        KEY_G = (int)'g',
        KEY_H = (int)'h',
        KEY_I = (int)'i',
        KEY_J = (int)'j',
        KEY_K = (int)'k',
        KEY_L = (int)'l',
        KEY_M = (int)'m',
        KEY_N = (int)'n',
        KEY_O = (int)'o',
        KEY_P = (int)'p',
        KEY_Q = (int)'q',
        KEY_R = (int)'r',
        KEY_S = (int)'s',
        KEY_T = (int)'t',
        KEY_U = (int)'u',
        KEY_V = (int)'v',
        KEY_W = (int)'w',
        KEY_X = (int)'x',
        KEY_Y = (int)'y',
        KEY_Z = (int)'z',
      
        KEY_1 = (int)'1',
        KEY_2 = (int)'2',
        KEY_3 = (int)'3',
        KEY_4 = (int)'4',
        KEY_5 = (int)'5',
        KEY_6 = (int)'6',
        KEY_7 = (int)'7',
        KEY_8 = (int)'8',
        KEY_9 = (int)'9',
        KEY_0 = (int)'0',
      
        KEY_RETURN = (int)'\n',
        KEY_ESCAPE,
        KEY_BACKSPACE,
        KEY_TAB = (int)'\t',
        KEY_SPACE = (int)' ',
      
        KEY_MINUS = (int)'-',
        KEY_EQUALS = (int)'=',
        KEY_LEFTBRACKET = (int)'[',
        KEY_RIGHTBRACKET = (int)']',
        KEY_BACKSLASH = (int)'\b',

        KEY_NONUSHASH,
 
        KEY_SEMICOLON = (int)';',
        KEY_APOSTROPHE,
        KEY_GRAVE,
  
        KEY_COMMA = (int)',',
        KEY_PERIOD = (int)'.',
        KEY_SLASH = (int)'/',
   
        KEY_CAPSLOCK,
    
        KEY_F1 = 1000,
        KEY_F2 = 1001,
        KEY_F3 = 1002,
        KEY_F4 = 1003,
        KEY_F5 = 1004,
        KEY_F6 = 1005,
        KEY_F7 = 1006,
        KEY_F8 = 1007,
        KEY_F9 = 1008,
        KEY_F10	= 1009,
        KEY_F11	= 1010,
        KEY_F12	= 1011,
      
        KEY_PRINTSCREEN,
        KEY_SCROLLLOCK,
        KEY_PAUSE,
        KEY_INSERT,
     
        KEY_HOME,
        KEY_PAGEUP,
        KEY_DELETE,
        KEY_END,
        KEY_PAGEDOWN,
        KEY_RIGHT,
        KEY_LEFT,
        KEY_DOWN,
        KEY_UP,
       
        KEY_NUMLOCKCLEAR,
        
        KEY_KP_DIVIDE,
        KEY_KP_MULTIPLY,
        KEY_KP_MINUS,
        KEY_KP_PLUS,
        KEY_KP_ENTER,
        KEY_KP_1,
        KEY_KP_2,
        KEY_KP_3,
        KEY_KP_4,
        KEY_KP_5,
        KEY_KP_6,
        KEY_KP_7,
        KEY_KP_8,
        KEY_KP_9,
        KEY_KP_0,
        KEY_KP_PERIOD,
        
        KEY_NONUSBACKSLASH,
                       
        KEY_APPLICATION,
        KEY_POWER,
        
        KEY_KP_EQUALS,
        KEY_F13,
        KEY_F14,
        KEY_F15,
        KEY_F16,
        KEY_F17,
        KEY_F18,
        KEY_F19,
        KEY_F20,
        KEY_F21,
        KEY_F22,
        KEY_F23,
        KEY_F24,
        KEY_EXECUTE,
        KEY_HELP,
        KEY_MENU,
        KEY_SELECT,
        KEY_STOP,
        KEY_AGAIN,
        KEY_UNDO,
        KEY_CUT,
        KEY_COPY,
        KEY_PASTE,
        KEY_FIND,
        KEY_MUTE,
        KEY_VOLUMEUP,
        KEY_VOLUMEDOWN,
        
        KEY_KP_COMMA,
        KEY_KP_EQUALSAS400,
       
        KEY_INTERNATIONAL1,
        
        KEY_INTERNATIONAL2,
        KEY_INTERNATIONAL3,
        KEY_INTERNATIONAL4,
        KEY_INTERNATIONAL5,
        KEY_INTERNATIONAL6,
        KEY_INTERNATIONAL7,
        KEY_INTERNATIONAL8,
        KEY_INTERNATIONAL9,
        KEY_LANG1,
        KEY_LANG2,
        KEY_LANG3,
        KEY_LANG4,
        KEY_LANG5,
        KEY_LANG6,
        KEY_LANG7,
        KEY_LANG8,
        KEY_LANG9,

        KEY_ALTERASE,
        KEY_SYSREQ,
        KEY_CANCEL,
        KEY_CLEAR,
        KEY_PRIOR,
        KEY_RETURN2,
        KEY_SEPARATOR,
        KEY_OUT,
        KEY_OPER,
        KEY_CLEARAGAIN,
        KEY_CRSEL,
        KEY_EXSEL,
        
        KEY_KP_00,
        KEY_KP_000,
        KEY_THOUSANDSSEPARATOR,
        KEY_DECIMALSEPARATOR,
        KEY_CURRENCYUNIT,
        KEY_CURRENCYSUBUNIT,
        KEY_KP_LEFTPAREN,
        KEY_KP_RIGHTPAREN,
        KEY_KP_LEFTBRACE,
        KEY_KP_RIGHTBRACE,
        KEY_KP_TAB,
        KEY_KP_BACKSPACE,
        KEY_KP_A,
        KEY_KP_B,
        KEY_KP_C,
        KEY_KP_D,
        KEY_KP_E,
        KEY_KP_F,
        KEY_KP_XOR,
        KEY_KP_POWER,
        KEY_KP_PERCENT,
        KEY_KP_LESS,
        KEY_KP_GREATER,
        KEY_KP_AMPERSAND,
        KEY_KP_DBLAMPERSAND,
        KEY_KP_VERTICALBAR,
        KEY_KP_DBLVERTICALBAR,
        KEY_KP_COLON,
        KEY_KP_HASH,
        KEY_KP_SPACE,
        KEY_KP_AT,
        KEY_KP_EXCLAM,
        KEY_KP_MEMSTORE,
        KEY_KP_MEMRECALL,
        KEY_KP_MEMCLEAR,
        KEY_KP_MEMADD,
        KEY_KP_MEMSUBTRACT,
        KEY_KP_MEMMULTIPLY,
        KEY_KP_MEMDIVIDE,
        KEY_KP_PLUSMINUS,
        KEY_KP_CLEAR,
        KEY_KP_CLEARENTRY,
        KEY_KP_BINARY,
        KEY_KP_OCTAL,
        KEY_KP_DECIMAL,
        KEY_KP_HEXADECIMAL,
        
        KEY_LCTRL,
        KEY_LSHIFT,
        KEY_LALT,
        KEY_LGUI,
        KEY_RCTRL,
        KEY_RSHIFT,
        KEY_RALT,
        KEY_RGUI,

        KEY_MODE,

        KEY_AUDIONEXT,
        KEY_AUDIOPREV,
        KEY_AUDIOSTOP,
        KEY_AUDIOPLAY,
        KEY_AUDIOMUTE,
        KEY_MEDIASELECT,
        KEY_WWW,
        KEY_MAIL,
        KEY_CALCULATOR,
        KEY_COMPUTER,
        KEY_AC_SEARCH,
        KEY_AC_HOME,
        KEY_AC_BACK,
        KEY_AC_FORWARD,
        KEY_AC_STOP,
        KEY_AC_REFRESH,
        KEY_AC_BOOKMARKS,
       
        KEY_BRIGHTNESSDOWN,
        KEY_BRIGHTNESSUP,
        KEY_DISPLAYSWITCH,
        
        KEY_KBDILLUMTOGGLE,
        KEY_KBDILLUMDOWN,
        KEY_KBDILLUMUP,
        KEY_EJECT,
        KEY_SLEEP,
        
        KEY_APP1,
        KEY_APP2,
        
        KEY_COUNT //for bounds checking
    };

	static SDL_Scancode convertKeyToSDLScancode(mg::KEYBOARD_KEY mgKey) {
		SDL_Scancode sdlKey = SDL_SCANCODE_UNKNOWN;

    	switch(mgKey) {
    	    case mg::KEYBOARD_KEY::KEY_A:
    	        sdlKey = SDL_SCANCODE_A;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_B:
    	        sdlKey = SDL_SCANCODE_B;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_C:
    	        sdlKey = SDL_SCANCODE_C;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_D:
    	        sdlKey = SDL_SCANCODE_D;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_E:
    	        sdlKey = SDL_SCANCODE_E;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F:
    	        sdlKey = SDL_SCANCODE_F;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_G:
    	        sdlKey = SDL_SCANCODE_G;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_H:
    	        sdlKey = SDL_SCANCODE_H;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_I:
    	        sdlKey = SDL_SCANCODE_I;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_J:
    	        sdlKey = SDL_SCANCODE_J;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_K:
    	        sdlKey = SDL_SCANCODE_K;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_L:
    	        sdlKey = SDL_SCANCODE_L;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_M:
    	        sdlKey = SDL_SCANCODE_M;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_N:
    	        sdlKey = SDL_SCANCODE_N;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_O:
    	        sdlKey = SDL_SCANCODE_O;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_P:
    	        sdlKey = SDL_SCANCODE_P;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_Q:
    	        sdlKey = SDL_SCANCODE_Q;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_R:
    	        sdlKey = SDL_SCANCODE_R;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_S:
    	        sdlKey = SDL_SCANCODE_S;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_T:
    	        sdlKey = SDL_SCANCODE_T;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_U:
    	        sdlKey = SDL_SCANCODE_U;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_V:
    	        sdlKey = SDL_SCANCODE_V;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_W:
    	        sdlKey = SDL_SCANCODE_W;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_X:
    	        sdlKey = SDL_SCANCODE_X;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_Y:
    	        sdlKey = SDL_SCANCODE_Y;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_Z:
    	        sdlKey = SDL_SCANCODE_Z;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F1:
    	        sdlKey = SDL_SCANCODE_F1;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F2:
    	        sdlKey = SDL_SCANCODE_F2;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F3:
    	        sdlKey = SDL_SCANCODE_F3;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F4:
    	        sdlKey = SDL_SCANCODE_F4;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F5:
    	        sdlKey = SDL_SCANCODE_F5;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F6:
    	        sdlKey = SDL_SCANCODE_F6;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F7:
    	        sdlKey = SDL_SCANCODE_F7;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F8:
    	        sdlKey = SDL_SCANCODE_F8;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F9:
    	        sdlKey = SDL_SCANCODE_F9;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F10:
    	        sdlKey = SDL_SCANCODE_F10;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F11:
    	        sdlKey = SDL_SCANCODE_F11;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F12:
    	        sdlKey = SDL_SCANCODE_F12;
    	        break;

    	    case mg::KEYBOARD_KEY::KEY_ESCAPE:
    	        sdlKey = SDL_SCANCODE_ESCAPE;
    	        break;
			case mg::KEYBOARD_KEY::KEY_BACKSPACE:
				sdlKey = SDL_SCANCODE_BACKSPACE;
				break;
			case mg::KEYBOARD_KEY::KEY_SPACE:
				sdlKey = SDL_SCANCODE_SPACE;
				break;
    	    case mg::KEYBOARD_KEY::KEY_RETURN:
    	        sdlKey = SDL_SCANCODE_RETURN;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_TAB:
    	        sdlKey = SDL_SCANCODE_TAB;
    	        break;

    	    case mg::KEYBOARD_KEY::KEY_1:
    	        sdlKey = SDL_SCANCODE_1;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_2:
    	        sdlKey = SDL_SCANCODE_2;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_3:
    	        sdlKey = SDL_SCANCODE_3;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_4:
    	        sdlKey = SDL_SCANCODE_4;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_5:
    	        sdlKey = SDL_SCANCODE_5;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_6:
    	        sdlKey = SDL_SCANCODE_6;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_7:
    	        sdlKey = SDL_SCANCODE_7;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_8:
    	        sdlKey = SDL_SCANCODE_8;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_9:
    	        sdlKey = SDL_SCANCODE_9;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_0:
    	        sdlKey = SDL_SCANCODE_0;
    	        break;
    	    default:
    	        break;
    	}

		return sdlKey;
	}
	static mg::KEYBOARD_KEY convertSDLScancodeToKey(SDL_Scancode sdlKey) {
		mg::KEYBOARD_KEY mgKey = mg::KEYBOARD_KEY::KEY_NONE;

    	switch(mgKey) {
    	    case mg::KEYBOARD_KEY::KEY_A:
    	        sdlKey = SDL_SCANCODE_A;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_B:
    	        sdlKey = SDL_SCANCODE_B;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_C:
    	        sdlKey = SDL_SCANCODE_C;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_D:
    	        sdlKey = SDL_SCANCODE_D;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_E:
    	        sdlKey = SDL_SCANCODE_E;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F:
    	        sdlKey = SDL_SCANCODE_F;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_G:
    	        sdlKey = SDL_SCANCODE_G;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_H:
    	        sdlKey = SDL_SCANCODE_H;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_I:
    	        sdlKey = SDL_SCANCODE_I;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_J:
    	        sdlKey = SDL_SCANCODE_J;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_K:
    	        sdlKey = SDL_SCANCODE_K;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_L:
    	        sdlKey = SDL_SCANCODE_L;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_M:
    	        sdlKey = SDL_SCANCODE_M;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_N:
    	        sdlKey = SDL_SCANCODE_N;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_O:
    	        sdlKey = SDL_SCANCODE_O;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_P:
    	        sdlKey = SDL_SCANCODE_P;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_Q:
    	        sdlKey = SDL_SCANCODE_Q;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_R:
    	        sdlKey = SDL_SCANCODE_R;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_S:
    	        sdlKey = SDL_SCANCODE_S;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_T:
    	        sdlKey = SDL_SCANCODE_T;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_U:
    	        sdlKey = SDL_SCANCODE_U;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_V:
    	        sdlKey = SDL_SCANCODE_V;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_W:
    	        sdlKey = SDL_SCANCODE_W;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_X:
    	        sdlKey = SDL_SCANCODE_X;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_Y:
    	        sdlKey = SDL_SCANCODE_Y;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_Z:
    	        sdlKey = SDL_SCANCODE_Z;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F1:
    	        sdlKey = SDL_SCANCODE_F1;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F2:
    	        sdlKey = SDL_SCANCODE_F2;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F3:
    	        sdlKey = SDL_SCANCODE_F3;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F4:
    	        sdlKey = SDL_SCANCODE_F4;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F5:
    	        sdlKey = SDL_SCANCODE_F5;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F6:
    	        sdlKey = SDL_SCANCODE_F6;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F7:
    	        sdlKey = SDL_SCANCODE_F7;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F8:
    	        sdlKey = SDL_SCANCODE_F8;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F9:
    	        sdlKey = SDL_SCANCODE_F9;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F10:
    	        sdlKey = SDL_SCANCODE_F10;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F11:
    	        sdlKey = SDL_SCANCODE_F11;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F12:
    	        sdlKey = SDL_SCANCODE_F12;
    	        break;

    	    case mg::KEYBOARD_KEY::KEY_ESCAPE:
    	        sdlKey = SDL_SCANCODE_ESCAPE;
    	        break;
			case mg::KEYBOARD_KEY::KEY_BACKSPACE:
				sdlKey = SDL_SCANCODE_BACKSPACE;
				break;
			case mg::KEYBOARD_KEY::KEY_SPACE:
				sdlKey = SDL_SCANCODE_SPACE;
				break;
    	    case mg::KEYBOARD_KEY::KEY_RETURN:
    	        sdlKey = SDL_SCANCODE_RETURN;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_TAB:
    	        sdlKey = SDL_SCANCODE_TAB;
    	        break;

    	    case mg::KEYBOARD_KEY::KEY_1:
    	        sdlKey = SDL_SCANCODE_1;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_2:
    	        sdlKey = SDL_SCANCODE_2;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_3:
    	        sdlKey = SDL_SCANCODE_3;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_4:
    	        sdlKey = SDL_SCANCODE_4;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_5:
    	        sdlKey = SDL_SCANCODE_5;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_6:
    	        sdlKey = SDL_SCANCODE_6;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_7:
    	        sdlKey = SDL_SCANCODE_7;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_8:
    	        sdlKey = SDL_SCANCODE_8;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_9:
    	        sdlKey = SDL_SCANCODE_9;
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_0:
    	        sdlKey = SDL_SCANCODE_0;
    	        break;
    	    default:
    	        break;
    	}

		return mgKey;
	}

	static wchar_t convertKeyToString(mg::KEYBOARD_KEY mgKey) {
		wchar_t returnChar = '\0';

    	switch(mgKey) {
    	    case mg::KEYBOARD_KEY::KEY_A:
				returnChar = 'a';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_B:
				returnChar = 'b';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_C:
				returnChar = 'c';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_D:
				returnChar = 'd';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_E:
				returnChar = 'e';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_F:
				returnChar = 'f';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_G:
				returnChar = 'g';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_H:
				returnChar = 'h';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_I:
				returnChar = 'i';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_J:
				returnChar = 'j';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_K:
				returnChar = 'k';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_L:
				returnChar = 'l';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_M:
				returnChar = 'm';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_N:
				returnChar = 'n';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_O:
				returnChar = 'o';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_P:
				returnChar = 'p';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_Q:
				returnChar = 'q';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_R:
				returnChar = 'r';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_S:
				returnChar = 's';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_T:
				returnChar = 't';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_U:
				returnChar = 'u';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_V:
				returnChar = 'v';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_W:
				returnChar = 'w';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_X:
				returnChar = 'x';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_Y:
				returnChar = 'y';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_Z:
				returnChar = 'z';
    	        break;
			case mg::KEYBOARD_KEY::KEY_SPACE:
				returnChar = ' ';
				break;
    	    case mg::KEYBOARD_KEY::KEY_RETURN:
				returnChar = '\n';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_TAB:
				returnChar = '\t';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_1:
				returnChar = '1';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_2:
				returnChar = '2';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_3:
				returnChar = '3';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_4:
				returnChar = '4';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_5:
				returnChar = '5';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_6:
				returnChar = '6';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_7:
				returnChar = '7';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_8:
				returnChar = '8';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_9:
				returnChar = '9';
    	        break;
    	    case mg::KEYBOARD_KEY::KEY_0:
				returnChar = '0';
    	        break;
    	    default:
    	        break;
    	}

		return returnChar;
	}
}

#endif //KEYBOARD_KEYS_HPP
