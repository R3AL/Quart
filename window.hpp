# pragma once

# include <windows.h>
# include <string>
# include <functional>
# include <unordered_map>
# include <memory>

# include "object.hpp"

namespace Quart
{
	class Window
	{
        typedef std::unique_ptr<Object> ObjectPTR;
        std::unordered_map<int, ObjectPTR> objects;

        HINSTANCE instance;
        HWND handle;
        MSG msg;

        tstring windowName;
        tstring className;

        bool init;
	public:
        unsigned int width;
        unsigned int height;

		Window(unsigned int width,
			   unsigned int height,
			   const tstring& title);

        operator HWND();

        void Add(Object*);
        
        int Run(HINSTANCE instance,
                int cmdShow              = SW_SHOW,
                int x                    = CW_USEDEFAULT,
                int y                    = CW_USEDEFAULT,
                unsigned short cursor    = (WORD)(IDC_ARROW),
                unsigned short icon      = (WORD)(IDI_APPLICATION),
                unsigned short iconSmall = (WORD)(IDI_APPLICATION),
                unsigned long style      = WS_OVERLAPPEDWINDOW);

    private:
        static LRESULT __stdcall _wndproc(HWND,UINT,WPARAM,LPARAM);
        LRESULT WindowProc(HWND,UINT,WPARAM,LPARAM);

        bool Create(HINSTANCE instance,
            int cmdShow              = SW_SHOW,
            int x                    = CW_USEDEFAULT,
            int y                    = CW_USEDEFAULT,
            unsigned short cursor    = (WORD)(IDC_ARROW),
            unsigned short icon      = (WORD)(IDI_APPLICATION),
            unsigned short iconSmall = (WORD)(IDI_APPLICATION),
            unsigned long style      = WS_OVERLAPPEDWINDOW);
	};
}
