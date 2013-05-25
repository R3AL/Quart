# pragma once

# include "object.hpp"

# include <unordered_map>

namespace Quart
{
	static enum class Modifiers : unsigned char
	{
		CONTROL = FCONTROL,
		ALT     = FALT,
		SHIFT   = FSHIFT,
		NONE    = 0
	};

	static enum class vKeys : unsigned short
	{
		Mouse_left_btn   = VK_LBUTTON,
		Mouse_right_btn  = VK_RBUTTON,
		Mouse_middle_btn = VK_MBUTTON,
		Backspace        = VK_BACK,
		Tab	             = VK_TAB,
		Enter            = VK_RETURN,
		Shift            = VK_SHIFT,
		Control          = VK_CONTROL,
		Alt              = VK_MENU,
		Capslock         = VK_CAPITAL,
		Escape           = VK_ESCAPE,
		Space            = VK_SPACE,
		Page_up          = VK_PRIOR,
		Page_down        = VK_NEXT,
		Home             = VK_HOME,
		Left             = VK_LEFT,
		Up               = VK_UP,
		Right            = VK_RIGHT,
		Down             = VK_DOWN,
		Print            = VK_PRINT,
		Printscreen      = VK_SNAPSHOT,
		Insert           = VK_INSERT,
		Delete           = VK_DELETE,
		Help             = VK_HELP,
		NumLock          = VK_NUMLOCK,
		ScrollLock       = VK_SCROLL,
		Winkey_left      = VK_LWIN,
		Winkey_right     = VK_RWIN,
		Sleep            = VK_SLEEP,
		Shift_left       = VK_LSHIFT,
		Shift_right      = VK_RSHIFT,
		Control_left     = VK_LCONTROL,
		Control_right    = VK_RCONTROL,
		Alt_left         = VK_LMENU,
		Alt_right        = VK_RMENU,
		Numpad_0         = VK_NUMPAD0,
		Numpad_1         = VK_NUMPAD1,
		Numpad_2         = VK_NUMPAD2,
		Numpad_3         = VK_NUMPAD3,
		Numpad_4         = VK_NUMPAD4,
		Numpad_5         = VK_NUMPAD5,
		Numpad_6         = VK_NUMPAD6,
		Numpad_7         = VK_NUMPAD7,
		Numpad_8         = VK_NUMPAD8,
		Numpad_9         = VK_NUMPAD9,
		Multiply         = VK_MULTIPLY,
		Add              = VK_ADD,
		Separator        = VK_SEPARATOR,
		Substract        = VK_SUBTRACT,
		Decimal          = VK_DECIMAL,
		Divide           = VK_DIVIDE,
		F1               = VK_F1,
		F2               = VK_F2,
		F3               = VK_F3,
		F4               = VK_F4,
		F5               = VK_F5,
		F6               = VK_F6,
		F7               = VK_F7,
		F8               = VK_F8,
		F9               = VK_F9,
		F10              = VK_F10,
		F11              = VK_F11,
		F12              = VK_F12,
		F13              = VK_F13,
		F14              = VK_F14,
		F15              = VK_F15,
		F16              = VK_F16,
		F17              = VK_F17,
		F18              = VK_F18,
		F19              = VK_F19,
		F20              = VK_F20,
		F21              = VK_F21,
		F22              = VK_F22,
		F23              = VK_F23,
		F24              = VK_F24,
		Key_0            = 0x30,
		Key_1            = 0x31,
		Key_2            = 0x32,
		Key_3            = 0x33,
		Key_4            = 0x34,
		Key_5            = 0x35,
		Key_6            = 0x36,
		Key_7            = 0x37,
		Key_8            = 0x38,
		Key_9            = 0x39,
		Key_A            = 0x41,
		Key_B            = 0x42,
		Key_C            = 0x43,
		Key_D            = 0x44,
		Key_E            = 0x45,
		Key_F            = 0x46,
		Key_G            = 0x47,
		Key_H            = 0x48,
		Key_I            = 0x49,
		Key_J            = 0x4A,
		Key_K            = 0x4B,
		Key_L            = 0x4C,
		Key_M            = 0x4D,
		Key_N            = 0x4E,
		Key_O            = 0x4F,
		Key_P            = 0x50,
		Key_Q            = 0x51,
		Key_R            = 0x52,
		Key_S            = 0x53,
		Key_T            = 0x54,
		Key_U            = 0x55,
		Key_V            = 0x56,
		Key_W            = 0x57,
		Key_X            = 0x58,
		Key_Y            = 0x59,
		Key_Z            = 0x5A
	};

	class Accelerator : public Object
	{
		friend class Window;

		ACCEL accel;
	public:
		Accelerator(const Modifiers& modifierKeys,
					const vKeys& virtualKey);

		operator ACCEL();

		void Draw(HWND&,HDC&,PAINTSTRUCT&);
		void Create(HWND&);
		LRESULT Proc(HWND, UINT, WPARAM, LPARAM);
	};
}