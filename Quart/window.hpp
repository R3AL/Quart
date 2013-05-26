# pragma once

# ifdef ENABLE_COMMON_CONTROLS
	# pragma comment(linker,"\"/manifestdependency:type='win32' \
	name='Microsoft.Windows.Common-Controls' version='6.0.0.0' \
	processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
# endif

# include <windows.h>
# include <string>
# include <functional>
# include <unordered_map>
# include <memory>

# include "object.hpp"
# include "MenuBar.hpp"
# include "Accelerator.hpp"

namespace Quart
{
	class Window
	{
		friend class MenuBar;

        typedef std::unique_ptr<Object> ObjectPTR;
		typedef std::unique_ptr<MenuBar> MenuBarPTR;

        std::unordered_map<int, ObjectPTR> objects;
		std::unordered_map<int, Accelerator*> accelerators;

		Window* parent;

        HINSTANCE instance;
		HACCEL accelTable;
		ACCEL* accels;
        HWND handle;
        MSG msg;

        tstring windowName;
        tstring className;

		MenuBarPTR menuBar;

		unsigned int width;
		unsigned int height;
		unsigned int objID;
	public:
		std::map<unsigned int, std::function<void(WPARAM,LPARAM)> > callback;


		Window(unsigned int width,
			   unsigned int height,
			   const tstring& title,
			   Window* parent = nullptr);

        operator HWND();

        void Add(Object*);
		void Add(MenuBar*);
		void Add(Accelerator*);
        
		int Run();

		void Close();
		void Enable(bool = true);
		void Disable();

		bool Create(unsigned long style      = WS_OVERLAPPEDWINDOW,
					unsigned long EXstyle	 = NULL,
					int cmdShow              = SW_SHOW,
					int x                    = CW_USEDEFAULT,
					int y                    = CW_USEDEFAULT,
					unsigned short cursor    = (WORD)(IDC_ARROW),
					unsigned short icon      = (WORD)(IDI_APPLICATION),
					unsigned short iconSmall = (WORD)(IDI_APPLICATION));

    private:
        static LRESULT __stdcall _wndproc(HWND,UINT,WPARAM,LPARAM);
        LRESULT WindowProc(HWND,UINT,WPARAM,LPARAM);
	};
}
