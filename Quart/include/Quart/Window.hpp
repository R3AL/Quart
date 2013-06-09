# pragma once

# include "Controller.hpp"
# include "Drawable.hpp"
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
		typedef std::unique_ptr<Drawable> DrawablePTR;

	private:
		MSG msg;
		HWND windowHandle;
		HINSTANCE instance;

		MenuBarPTR menuBar;

		Window* parent;
		enum Controller::type type;

		unsigned int controllersID;
		std::unordered_map<unsigned int, ControllerPTR> controllers;
		std::vector<Accelerator*> accelerators;
		std::vector<DrawablePTR> drawables;

	public:
		std::function<void()> OnClose;
		std::function<void(int,int)> OnLBtnDown,
			OnLBtnUp,
			OnRBtnDown,
			OnRBtnUp,
			OnMouseMove;

		Window(unsigned int width, 
			   unsigned int height, 
			   const tstring& title,
			   Window* parent           = nullptr,
			   int x                    = CW_USEDEFAULT, 
			   int y                    = CW_USEDEFAULT, 
			   unsigned long style      = WS_OVERLAPPEDWINDOW | WS_CLIPCHILDREN, 
			   unsigned long exStyle    = 0, 
			   unsigned short cursor    = (unsigned short)(IDC_ARROW),
			   unsigned short icon      = (unsigned short)(IDI_APPLICATION), 
			   unsigned short smallIcon = (unsigned short)(IDI_APPLICATION),
			   unsigned long classStyle = (CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS)
			   );

		int Run();
		int operator()();

		HWND GetHandle() const;

		void Add(MenuBar*);
		void Add(Accelerator*);
		void Add(Controller*);

		void Draw(Drawable*, bool forceRedraw = true);

		void Enable();
		void Disable();
		void Focus();
		void Close();
		void Redraw();

	private:
		static LRESULT __stdcall _wndproc(HWND,UINT,WPARAM,LPARAM);
		LRESULT WindowProc(HWND,UINT,WPARAM,LPARAM);
	};
}