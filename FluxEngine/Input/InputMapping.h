#pragma once

enum class KeyboardKey
{
	KEY_UNKNOWN = SDL_SCANCODE_UNKNOWN,
	KEY_A = SDL_SCANCODE_A,
	KEY_B = SDL_SCANCODE_B,
	KEY_C = SDL_SCANCODE_C,
	KEY_D = SDL_SCANCODE_D,
	KEY_E = SDL_SCANCODE_E,
	KEY_F = SDL_SCANCODE_F,
	KEY_G = SDL_SCANCODE_G,
	KEY_H = SDL_SCANCODE_H,
	KEY_I = SDL_SCANCODE_I,
	KEY_J = SDL_SCANCODE_J,
	KEY_K = SDL_SCANCODE_K,
	KEY_L = SDL_SCANCODE_L,
	KEY_M = SDL_SCANCODE_M,
	KEY_N = SDL_SCANCODE_N,
	KEY_O = SDL_SCANCODE_O,
	KEY_P = SDL_SCANCODE_P,
	KEY_Q = SDL_SCANCODE_Q,
	KEY_R = SDL_SCANCODE_R,
	KEY_S = SDL_SCANCODE_S,
	KEY_T = SDL_SCANCODE_T,
	KEY_U = SDL_SCANCODE_U,
	KEY_V = SDL_SCANCODE_V,
	KEY_W = SDL_SCANCODE_W,
	KEY_X = SDL_SCANCODE_X,
	KEY_Y = SDL_SCANCODE_Y,
	KEY_Z = SDL_SCANCODE_Z,
	KEY_1 = SDL_SCANCODE_1,
	KEY_2 = SDL_SCANCODE_2,
	KEY_3 = SDL_SCANCODE_3,
	KEY_4 = SDL_SCANCODE_4,
	KEY_5 = SDL_SCANCODE_5,
	KEY_6 = SDL_SCANCODE_6,
	KEY_7 = SDL_SCANCODE_7,
	KEY_8 = SDL_SCANCODE_8,
	KEY_9 = SDL_SCANCODE_9,
	KEY_0 = SDL_SCANCODE_0,
	KEY_RETURN = SDL_SCANCODE_RETURN,
	KEY_ESCAPE = SDL_SCANCODE_ESCAPE,
	KEY_BACKSPACE = SDL_SCANCODE_BACKSPACE,
	KEY_TAB = SDL_SCANCODE_TAB,
	KEY_SPACE = SDL_SCANCODE_SPACE,
	KEY_MINUS = SDL_SCANCODE_MINUS,
	KEY_EQUALS = SDL_SCANCODE_EQUALS,
	KEY_LEFTBRACKET = SDL_SCANCODE_LEFTBRACKET,
	KEY_RIGHTBRACKET = SDL_SCANCODE_RIGHTBRACKET,
	KEY_BACKSLASH = SDL_SCANCODE_BACKSLASH,
	KEY_NONUSHASH = SDL_SCANCODE_NONUSHASH,
	KEY_SEMICOLON = SDL_SCANCODE_SEMICOLON,
	KEY_APOSTROPHE = SDL_SCANCODE_APOSTROPHE,
	KEY_GRAVE = SDL_SCANCODE_GRAVE,
	KEY_COMMA = SDL_SCANCODE_COMMA,
	KEY_PERIOD = SDL_SCANCODE_PERIOD,
	KEY_SLASH = SDL_SCANCODE_SLASH,
	KEY_CAPSLOCK = SDL_SCANCODE_CAPSLOCK,
	KEY_F1 = SDL_SCANCODE_F1,
	KEY_F2 = SDL_SCANCODE_F2,
	KEY_F3 = SDL_SCANCODE_F3,
	KEY_F4 = SDL_SCANCODE_F4,
	KEY_F5 = SDL_SCANCODE_F5,
	KEY_F6 = SDL_SCANCODE_F6,
	KEY_F7 = SDL_SCANCODE_F7,
	KEY_F8 = SDL_SCANCODE_F8,
	KEY_F9 = SDL_SCANCODE_F9,
	KEY_F10 = SDL_SCANCODE_F10,
	KEY_F11 = SDL_SCANCODE_F11,
	KEY_F12 = SDL_SCANCODE_F12,
	KEY_PRINTSCREEN = SDL_SCANCODE_PRINTSCREEN,
	KEY_SCROLLLOCK = SDL_SCANCODE_SCROLLLOCK,
	KEY_PAUSE = SDL_SCANCODE_PAUSE,
	KEY_INSERT = SDL_SCANCODE_INSERT,
	KEY_HOME = SDL_SCANCODE_HOME,
	KEY_PAGEUP = SDL_SCANCODE_PAGEUP,
	KEY_DELETE = SDL_SCANCODE_DELETE,
	KEY_END = SDL_SCANCODE_END,
	KEY_PAGEDOWN = SDL_SCANCODE_PAGEDOWN,
	KEY_RIGHT = SDL_SCANCODE_RIGHT,
	KEY_LEFT = SDL_SCANCODE_LEFT,
	KEY_DOWN = SDL_SCANCODE_DOWN,
	KEY_UP = SDL_SCANCODE_UP,
	KEY_NUMLOCKCLEAR = SDL_SCANCODE_NUMLOCKCLEAR,
	KEY_KEYPAD_DIVIDE = SDL_SCANCODE_KP_DIVIDE,
	KEY_KEYPAD_MULTIPLY = SDL_SCANCODE_KP_MULTIPLY,
	KEY_KEYPAD_MINUS = SDL_SCANCODE_KP_MINUS,
	KEY_KEYPAD_PLUS = SDL_SCANCODE_KP_PLUS,
	KEY_KEYPAD_ENTER = SDL_SCANCODE_KP_ENTER,
	KEY_KEYPAD_1 = SDL_SCANCODE_KP_1,
	KEY_KEYPAD_2 = SDL_SCANCODE_KP_2,
	KEY_KEYPAD_3 = SDL_SCANCODE_KP_3,
	KEY_KEYPAD_4 = SDL_SCANCODE_KP_4,
	KEY_KEYPAD_5 = SDL_SCANCODE_KP_5,
	KEY_KEYPAD_6 = SDL_SCANCODE_KP_6,
	KEY_KEYPAD_7 = SDL_SCANCODE_KP_7,
	KEY_KEYPAD_8 = SDL_SCANCODE_KP_8,
	KEY_KEYPAD_9 = SDL_SCANCODE_KP_9,
	KEY_KEYPAD_0 = SDL_SCANCODE_KP_0,
	KEY_KEYPAD_PERIOD = SDL_SCANCODE_KP_PERIOD,
	KEY_NONUSBACKSLASH = SDL_SCANCODE_NONUSBACKSLASH,
	KEY_APPLICATION = SDL_SCANCODE_APPLICATION,
	KEY_POWER = SDL_SCANCODE_POWER,
	KEY_KEYPAD_EQUALS = SDL_SCANCODE_KP_EQUALS,
	KEY_F13 = SDL_SCANCODE_F13,
	KEY_F14 = SDL_SCANCODE_F14,
	KEY_F15 = SDL_SCANCODE_F15,
	KEY_F16 = SDL_SCANCODE_F16,
	KEY_F17 = SDL_SCANCODE_F17,
	KEY_F18 = SDL_SCANCODE_F18,
	KEY_F19 = SDL_SCANCODE_F19,
	KEY_F20 = SDL_SCANCODE_F20,
	KEY_F21 = SDL_SCANCODE_F21,
	KEY_F22 = SDL_SCANCODE_F22,
	KEY_F23 = SDL_SCANCODE_F23,
	KEY_F24 = SDL_SCANCODE_F24,
	KEY_EXEC = SDL_SCANCODE_EXECUTE,
	KEY_HELP = SDL_SCANCODE_HELP,
	KEY_MENU = SDL_SCANCODE_MENU,
	KEY_SELECT = SDL_SCANCODE_SELECT,
	KEY_STOP = SDL_SCANCODE_STOP,
	KEY_AGAIN = SDL_SCANCODE_AGAIN,
	KEY_UNDO = SDL_SCANCODE_UNDO,
	KEY_CUT = SDL_SCANCODE_CUT,
	KEY_COPY = SDL_SCANCODE_COPY,
	KEY_PASTE = SDL_SCANCODE_PASTE,
	KEY_FIND = SDL_SCANCODE_FIND,
	KEY_MUTE = SDL_SCANCODE_MUTE,
	KEY_VOLUMEUP = SDL_SCANCODE_VOLUMEUP,
	KEY_VOLUMEDOWN = SDL_SCANCODE_VOLUMEDOWN,
	KEY_KEYPAD_COMMA = SDL_SCANCODE_KP_COMMA,
	KEY_KEYPAD_EQUALSAS400 = SDL_SCANCODE_KP_EQUALSAS400,
	KEY_INTERNATIONAL1 = SDL_SCANCODE_INTERNATIONAL1,
	KEY_INTERNATIONAL2 = SDL_SCANCODE_INTERNATIONAL2,
	KEY_INTERNATIONAL3 = SDL_SCANCODE_INTERNATIONAL3,
	KEY_INTERNATIONAL4 = SDL_SCANCODE_INTERNATIONAL4,
	KEY_INTERNATIONAL5 = SDL_SCANCODE_INTERNATIONAL5,
	KEY_INTERNATIONAL6 = SDL_SCANCODE_INTERNATIONAL6,
	KEY_INTERNATIONAL7 = SDL_SCANCODE_INTERNATIONAL7,
	KEY_INTERNATIONAL8 = SDL_SCANCODE_INTERNATIONAL8,
	KEY_INTERNATIONAL9 = SDL_SCANCODE_INTERNATIONAL9,
	KEY_LANG1 = SDL_SCANCODE_LANG1,
	KEY_LANG2 = SDL_SCANCODE_LANG2,
	KEY_LANG3 = SDL_SCANCODE_LANG3,
	KEY_LANG4 = SDL_SCANCODE_LANG4,
	KEY_LANG5 = SDL_SCANCODE_LANG5,
	KEY_LANG6 = SDL_SCANCODE_LANG6,
	KEY_LANG7 = SDL_SCANCODE_LANG7,
	KEY_LANG8 = SDL_SCANCODE_LANG8,
	KEY_LANG9 = SDL_SCANCODE_LANG9,
	KEY_ALTERASE = SDL_SCANCODE_ALTERASE,
	KEY_SYSREQ = SDL_SCANCODE_SYSREQ,
	KEY_CANCEL = SDL_SCANCODE_CANCEL,
	KEY_CLEAR = SDL_SCANCODE_CLEAR,
	KEY_PRIOR = SDL_SCANCODE_PRIOR,
	KEY_RETURN2 = SDL_SCANCODE_RETURN2,
	KEY_SEPARATOR = SDL_SCANCODE_SEPARATOR,
	KEY_OUT = SDL_SCANCODE_OUT,
	KEY_OPER = SDL_SCANCODE_OPER,
	KEY_CLEARAGAIN = SDL_SCANCODE_CLEARAGAIN,
	KEY_CRSEL = SDL_SCANCODE_CRSEL,
	KEY_EXSEL = SDL_SCANCODE_EXSEL,
	KEY_KEYPAD_00 = SDL_SCANCODE_KP_00,
	KEY_KEYPAD_000 = SDL_SCANCODE_KP_000,
	KEY_THOUSANDSSEPARATOR = SDL_SCANCODE_THOUSANDSSEPARATOR,
	KEY_DECIMALSEPARATOR = SDL_SCANCODE_DECIMALSEPARATOR,
	KEY_CURRENCYUNIT = SDL_SCANCODE_CURRENCYUNIT,
	KEY_CURRENCYSUBUNIT = SDL_SCANCODE_CURRENCYSUBUNIT,
	KEY_KEYPAD_LEFTPAREN = SDL_SCANCODE_KP_LEFTPAREN,
	KEY_KEYPAD_RIGHTPAREN = SDL_SCANCODE_KP_RIGHTPAREN,
	KEY_KEYPAD_LEFTBRACE = SDL_SCANCODE_KP_LEFTBRACE,
	KEY_KEYPAD_RIGHTBRACE = SDL_SCANCODE_KP_RIGHTBRACE,
	KEY_KEYPAD_TAB = SDL_SCANCODE_KP_TAB,
	KEY_KEYPAD_BACKSPACE = SDL_SCANCODE_KP_BACKSPACE,
	KEY_KEYPAD_A = SDL_SCANCODE_KP_A,
	KEY_KEYPAD_B = SDL_SCANCODE_KP_B,
	KEY_KEYPAD_C = SDL_SCANCODE_KP_C,
	KEY_KEYPAD_D = SDL_SCANCODE_KP_D,
	KEY_KEYPAD_E = SDL_SCANCODE_KP_E,
	KEY_KEYPAD_F = SDL_SCANCODE_KP_F,
	KEY_KEYPAD_XOR = SDL_SCANCODE_KP_XOR,
	KEY_KEYPAD_POWER = SDL_SCANCODE_KP_POWER,
	KEY_KEYPAD_PERCENT = SDL_SCANCODE_KP_PERCENT,
	KEY_KEYPAD_LESS = SDL_SCANCODE_KP_LESS,
	KEY_KEYPAD_GREATER = SDL_SCANCODE_KP_GREATER,
	KEY_KEYPAD_AMPERSAND = SDL_SCANCODE_KP_AMPERSAND,
	KEY_KEYPAD_DBLAMPERSAND = SDL_SCANCODE_KP_DBLAMPERSAND,
	KEY_KEYPAD_VERTICALBAR = SDL_SCANCODE_KP_VERTICALBAR,
	KEY_KEYPAD_DBLVERTICALBAR = SDL_SCANCODE_KP_DBLVERTICALBAR,
	KEY_KEYPAD_COLON = SDL_SCANCODE_KP_COLON,
	KEY_KEYPAD_HASH = SDL_SCANCODE_KP_HASH,
	KEY_KEYPAD_SPACE = SDL_SCANCODE_KP_SPACE,
	KEY_KEYPAD_AT = SDL_SCANCODE_KP_AT,
	KEY_KEYPAD_EXCLAM = SDL_SCANCODE_KP_EXCLAM,
	KEY_KEYPAD_MEMSTORE = SDL_SCANCODE_KP_MEMSTORE,
	KEY_KEYPAD_MEMRECALL = SDL_SCANCODE_KP_MEMRECALL,
	KEY_KEYPAD_MEMCLEAR = SDL_SCANCODE_KP_MEMCLEAR,
	KEY_KEYPAD_MEMADD = SDL_SCANCODE_KP_MEMADD,
	KEY_KEYPAD_MEMSUBTRACT = SDL_SCANCODE_KP_MEMSUBTRACT,
	KEY_KEYPAD_MEMMULTIPLY = SDL_SCANCODE_KP_MEMMULTIPLY,
	KEY_KEYPAD_MEMDIVIDE = SDL_SCANCODE_KP_MEMDIVIDE,
	KEY_KEYPAD_PLUSMINUS = SDL_SCANCODE_KP_PLUSMINUS,
	KEY_KEYPAD_CLEAR = SDL_SCANCODE_KP_CLEAR,
	KEY_KEYPAD_CLEARENTRY = SDL_SCANCODE_KP_CLEARENTRY,
	KEY_KEYPAD_BINARY = SDL_SCANCODE_KP_BINARY,
	KEY_KEYPAD_OCTAL = SDL_SCANCODE_KP_OCTAL,
	KEY_KEYPAD_DECIMAL = SDL_SCANCODE_KP_DECIMAL,
	KEY_KEYPAD_HEXADECIMAL = SDL_SCANCODE_KP_HEXADECIMAL,
	KEY_LEFT_CTRL = SDL_SCANCODE_LCTRL,
	KEY_LEFT_SHIFT = SDL_SCANCODE_LSHIFT,
	KEY_LEFT_ALT = SDL_SCANCODE_LALT,
	KEY_LEFT_GUI = SDL_SCANCODE_LGUI,
	KEY_RIGHT_CTRL = SDL_SCANCODE_RCTRL,
	KEY_RIGHT_SHIFT = SDL_SCANCODE_RSHIFT,
	KEY_RIGHT_ALT = SDL_SCANCODE_RALT,
	KEY_RIGHT_GUI = SDL_SCANCODE_RGUI,
	KEY_MODE = SDL_SCANCODE_MODE,
	KEY_AUDIONEXT = SDL_SCANCODE_AUDIONEXT,
	KEY_AUDIOPREV = SDL_SCANCODE_AUDIOPREV,
	KEY_AUDIOSTOP = SDL_SCANCODE_AUDIOSTOP,
	KEY_AUDIOPLAY = SDL_SCANCODE_AUDIOPLAY,
	KEY_AUDIOMUTE = SDL_SCANCODE_AUDIOMUTE,
	KEY_MEDIASELECT = SDL_SCANCODE_MEDIASELECT,
	KEY_WWW = SDL_SCANCODE_WWW,
	KEY_MAIL = SDL_SCANCODE_MAIL,
	KEY_CALCULATOR = SDL_SCANCODE_CALCULATOR,
	KEY_COMPUTER = SDL_SCANCODE_COMPUTER,
	KEY_AC_SEARCH = SDL_SCANCODE_AC_SEARCH,
	KEY_AC_HOME = SDL_SCANCODE_AC_HOME,
	KEY_AC_BACK = SDL_SCANCODE_AC_BACK,
	KEY_AC_FORWARD = SDL_SCANCODE_AC_FORWARD,
	KEY_AC_STOP = SDL_SCANCODE_AC_STOP,
	KEY_AC_REFRESH = SDL_SCANCODE_AC_REFRESH,
	KEY_AC_BOOKMARKS = SDL_SCANCODE_AC_BOOKMARKS,
	KEY_BRIGHTNESSDOWN = SDL_SCANCODE_BRIGHTNESSDOWN,
	KEY_BRIGHTNESSUP = SDL_SCANCODE_BRIGHTNESSUP,
	KEY_DISPLAYSWITCH = SDL_SCANCODE_DISPLAYSWITCH,
	KEY_KBDILLUMTOGGLE = SDL_SCANCODE_KBDILLUMTOGGLE,
	KEY_KBDILLUMDOWN = SDL_SCANCODE_KBDILLUMDOWN,
	KEY_KBDILLUMUP = SDL_SCANCODE_KBDILLUMUP,
	KEY_EJECT = SDL_SCANCODE_EJECT,
	KEY_SLEEP = SDL_SCANCODE_SLEEP,
	KEY_APP1 = SDL_SCANCODE_APP1,
	KEY_APP2 = SDL_SCANCODE_APP2,

	MAX = SDL_NUM_SCANCODES,
	NONE = -1
};

enum class MouseKey
{
	LEFT_BUTTON = SDL_BUTTON_LEFT,
	MIDDLE_BUTTON = SDL_BUTTON_MIDDLE,
	RIGHT_BUTTON = SDL_BUTTON_RIGHT,
	NONE = -1
};