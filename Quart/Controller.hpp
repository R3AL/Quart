# pragma once

# include <windows.h>
# include <string>
# include <sstream>

//# define ERRORMB() MessageBox(0, WIDEN("Invalid handle provided in '")  WIDEN(__FUNCTION__) WIDEN("' function\n"),NULL, NULL )

# define ERRORMB() \
	{\
	tstring objType; \
	switch(this->type)\
{\
	case Controller::WINDOW: objType      = WIDEN("Window");           break;\
	case Controller::BUTTON: objType      = WIDEN("Button");           break;\
	case Controller::LABEL: objType       = WIDEN("Label");            break;\
	case Controller::EDITBOX: objType     = WIDEN("Editbox");          break;\
	case Controller::MLEDITBOX: objType   = WIDEN("MultilineEditbox"); break;\
	case Controller::COMBOBOX: objType    = WIDEN("Combobox");         break;\
	case Controller::LISTVIEW: objType    = WIDEN("Listview");         break;\
	case Controller::ACCELERATOR: objType = WIDEN("Accelerator");      break;\
	case Controller::PROGRESSBAR: objType = WIDEN("Progressbar");      break;\
	case Controller::UPDOWN: objType      = WIDEN("Updown");           break;\
}\
	\
	Messagebox(WIDEN("Function name: ") WIDEN(__FUNCTION__)\
	WIDEN("\nObject type: ") + objType, WIDEN("Invalid handle provided !")); }


# ifndef __VISUALSTYLE_CHECK
#	define __VISUALSTYLE_CHECK false
# endif

# ifdef UNICODE
	typedef std::wstring tstring;
	typedef std::wstringstream tstringstream;
#	define to_tstring(a) std::to_wstring(a)
#	define WIDEN2(x) L ## x 
#	define WIDEN(x) WIDEN2(x)
# else
	typedef std::string tstring;
	typedef std::stringstream tstringstream;
#	define to_tstring(a) std::to_string(a)
#	define WIDEN(x) x
# endif

# ifdef _MSC_VER
#    pragma comment(linker, "/subsystem:windows /ENTRY:mainCRTStartup")
# endif

# ifdef ENABLE_CC_VS
#	pragma comment(linker,"\"/manifestdependency:type='win32' \
	name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
	processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
# undef __VISUALSTYLE_CHECK
# define __VISUALSTYLE_CHECK true
# endif

namespace Quart
{
	namespace ___internal
	{
		static bool vsEnable = __VISUALSTYLE_CHECK;
	}

	class Controller
	{
		friend class Window;
		friend class UpDown;

	protected:
		enum type
		{
			CONTROLLER = 0,
			WINDOW,
			BUTTON,
			LABEL,
			EDITBOX,
			MLEDITBOX,
			COMBOBOX,
			LISTVIEW,
			ACCELERATOR,
			PROGRESSBAR,
			UPDOWN
		}type;

		HWND handle;
		unsigned int id;

	public:
		virtual ~Controller();

		Controller(enum type = CONTROLLER);

		void Enable();
		void Disable();
		void Focus();
	
	private:
		virtual void Create(Window*)            = 0;
		virtual void MsgHandler(WPARAM, LPARAM) = 0;
	};
}
