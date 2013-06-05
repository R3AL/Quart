# pragma once

# include "Controller.hpp"
# include "MenuBar.hpp"
# include "Accelerator.hpp"

# include <unordered_map>
# include <memory>
# include <vector>

namespace Quart
{
	class Window
	{
		typedef std::unique_ptr<Controller> ControllerPTR;
		typedef std::unique_ptr<MenuBar> MenuBarPTR;

	private:
		MSG msg;
		HWND windowHandle;
		HINSTANCE instance;

		MenuBarPTR menuBar;

		Window* parent;
		enum Controller::type type;

		std::unordered_map<unsigned int, ControllerPTR> controllers;
		std::vector<Accelerator*> accelerators;
		unsigned int controllersID;

	public:
		std::function<void()> OnClose;

		Window(unsigned int width, 
			   unsigned int height, 
			   const tstring& title,
			   Window* parent           = nullptr,
			   int x                    = CW_USEDEFAULT, 
			   int y                    = CW_USEDEFAULT, 
			   unsigned long style      = WS_OVERLAPPEDWINDOW, 
			   unsigned long exStyle    = 0, 
			   unsigned short cursor    = (unsigned short)(IDC_ARROW),
			   unsigned short icon      = (unsigned short)(IDI_APPLICATION), 
			   unsigned short smallIcon = (unsigned short)(IDI_APPLICATION),
			   unsigned long classStyle = (CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS)
			   );

		int Run();
		HWND GetHandle() const;

		void Add(MenuBar*);
		void Add(Accelerator*);
		void Add(Controller*);

		void Enable();
		void Disable();
		void Focus();
		void Close();

	private:
		static LRESULT __stdcall _wndproc(HWND,UINT,WPARAM,LPARAM);
		LRESULT WindowProc(HWND,UINT,WPARAM,LPARAM);
	};
}