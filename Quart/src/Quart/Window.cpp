# include "Window.hpp"

# include <time.h>
# include <CommCtrl.h>
# include "Messagebox.hpp"

namespace Quart
{
	Window::Window(unsigned int width, 
				   unsigned int height, 
				   const tstring& title, 
				   Window* parent,
				   int x, 
				   int y, 
				   unsigned long style, 
				   unsigned long exStyle, 
				   unsigned short cursor,
				   unsigned short icon,
				   unsigned short smallIcon,
				   unsigned long classStyle) :
		controllersID(1),
		windowHandle(nullptr),
		parent(parent),
		type(Controller::WINDOW),
		OnClose(nullptr), OnLClick(nullptr), OnRClick(nullptr)
	{
		srand(static_cast<unsigned int>(time(0)));

		tstring className(WIDEN(__TIME__) WIDEN(" ") + to_tstring(rand()) + to_tstring(rand()) + to_tstring(rand()));

		this->instance = GetModuleHandle(0);

		WNDCLASSEX windowClass    = {0};

		windowClass.cbSize        = sizeof(WNDCLASSEX);
		windowClass.lpszClassName = className.c_str();
		windowClass.hInstance     = this->instance;
		windowClass.hIcon         = LoadIcon(nullptr, MAKEINTRESOURCE(icon));
		windowClass.hIconSm       = LoadIcon(nullptr, MAKEINTRESOURCE(smallIcon));
		windowClass.hCursor       = LoadCursor(nullptr, MAKEINTRESOURCE(cursor));
		windowClass.lpfnWndProc   = Window::_wndproc;

		if(this->parent == nullptr)
		{
			windowClass.style         = classStyle;
			windowClass.cbClsExtra    = 0;
			windowClass.cbWndExtra    = 0;
			windowClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
			windowClass.lpszMenuName  = nullptr;
		}
		else
		{
			windowClass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);

			if(!exStyle)
				exStyle = WS_EX_DLGMODALFRAME;

			this->parent->Disable();
		}

		if(!RegisterClassEx(&windowClass))
		{
			MessageBox(nullptr, WIDEN("Failed registering window class"), NULL, NULL);
			return;
		}

		this->windowHandle = CreateWindowEx(exStyle,
			className.c_str(),
			title.c_str(),
			style,
			x, y,
			width, height,
			(this->parent != nullptr ? this->parent->windowHandle : nullptr),
			nullptr,
			this->instance,
			(void*)this);


		if(!this->windowHandle)
		{
			MessageBox(nullptr, WIDEN("Creating window failed !"), NULL, NULL);
			return;
		}

		ShowWindow(this->windowHandle, SW_SHOW);
		UpdateWindow(this->windowHandle);
	}

	LRESULT Window::WindowProc(HWND hwnd, UINT message,WPARAM wparam,LPARAM lparam)
	{
		HDC hdc = nullptr;

		switch (message)
		{
		case WM_PAINT:
			{
				PAINTSTRUCT ps;
				hdc = BeginPaint(hwnd, &ps);
				
				for(auto& elem : this->drawables)
					if(!elem->IsHidden())
					{
						elem->Draw(hdc, ps);
					}

				EndPaint(hwnd, &ps);
//				ReleaseDC(hwnd, hdc);
			}break;

		case WM_DESTROY:
			if(this->parent != nullptr)
				this->parent->Enable();

			if(this->OnClose != nullptr)
				this->OnClose();

			PostQuitMessage(0);
			break;
		
		case WM_PRINTCLIENT:
		case WM_CTLCOLORSTATIC:
			{
				hdc = (HDC) wparam; 
				SetTextColor(hdc, RGB(0,0,0));    
				SetBkMode (hdc, TRANSPARENT);

				return (LRESULT)GetStockObject(NULL_BRUSH);
			}

		case WM_COMMAND:
			{
				auto lword = LOWORD(wparam);
				auto hword = HIWORD(wparam);

				if(this->controllers.count(lword))
				{
					if(this->controllers[lword]->type == Controller::ACCELERATOR)
						this->controllers[lword]->MsgHandler(0, lparam);
					else
						this->controllers[lword]->MsgHandler(hword, lparam);
				}
			}
			break;

		case WM_NOTIFY:
			{
				auto lpnmhdr = reinterpret_cast<LPNMHDR>(lparam);

				auto id = static_cast<int>(GetWindowLongPtr((HWND)lparam, GWL_ID));

				if(this->controllers.count(id))
				{
					this->controllers[lpnmhdr->idFrom]->MsgHandler(lpnmhdr->code, lparam);
				}
			}break;

		case WM_VSCROLL:
		case WM_HSCROLL:
			{
				auto id = static_cast<int>(GetWindowLongPtr((HWND)lparam, GWL_ID));

				if(this->controllers.count(id))
				{
					this->controllers[id]->MsgHandler(LOWORD(wparam), HIWORD(wparam));
				}
			}break;

		case WM_LBUTTONDOWN:
			{
				if(this->OnLClick != nullptr)
				{
					POINTS mpos = MAKEPOINTS(lparam);
					this->OnLClick(mpos.x, mpos.y);
				}
			}break;

		case WM_RBUTTONDOWN:
			{
				if(this->OnRClick != nullptr)
				{
					POINTS mpos = MAKEPOINTS(lparam);
					this->OnRClick(mpos.x, mpos.y);
				}
			}break;

// 		case WM_NOTIFY:
// 			{
// 				if(HIWORD(wparam) == LVN_INSERTITEM)
// 				{
//  					auto lvTmp = (reinterpret_cast<LPNMLISTVIEW>(lparam));
// 					if(lvTmp->hdr.code == LVN_INSERTITEM)
// 						MessageBox(NULL, NULL, NULL, NULL);
// 
// 				
// 					if(this->controllers.count(lvTmp->hdr.idFrom))
// 						this->controllers[lvTmp->hdr.idFrom]->MsgHandler(lvTmp->hdr.code, )
// 				}
// 			}break;

		}
		return DefWindowProc(hwnd, message, wparam, lparam);
	}

	LRESULT Window::_wndproc(HWND a, UINT b, WPARAM c, LPARAM d)
	{
		Window* wnd = nullptr;

		if (b == WM_NCCREATE)
			SetWindowLongPtr(a, GWL_USERDATA, (long)((LPCREATESTRUCT(d))->lpCreateParams));

		wnd = (Window*)GetWindowLongPtr(a, GWL_USERDATA);

		if(wnd)
			return wnd->WindowProc(a,b,c,d);
		else
			return DefWindowProc(a,b,c,d);
	}

	int Window::Run()
	{
		this->Redraw();

		auto count = this->accelerators.size();
		auto accel = new ACCEL[count];

		auto i = 0;
		for(const auto& elem : this->accelerators)
			accel[i++] = (ACCEL)(*elem);

		auto accelTable = CreateAcceleratorTable(accel, count);
		delete accel;

		while (GetMessage(&this->msg, nullptr, 0, 0) > 0)
		{
			if(!TranslateAccelerator(this->windowHandle, accelTable, &this->msg))
			{
				if(!IsDialogMessage(this->windowHandle, &this->msg))
				{
					TranslateMessage(&this->msg);
					DispatchMessage(&this->msg);
				}
			}
		}

		return static_cast<int>(msg.wParam);
	}

	void Window::Add(Controller* obj)
	{
		obj->id                    = this->controllersID++;
		this->controllers[obj->id] = ControllerPTR(obj);
	
		obj->Create(this);
	}

	void Window::Add(MenuBar* mb)
	{
		auto menu = CreateMenu();

		for(const auto& elem : mb->elements)
		{
			this->Add(elem);

			if(elem->subelements.size() == 0)
			{
				AppendMenu(menu, MF_STRING, elem->id, (LPTSTR)elem->text.c_str() );
			}
			else
			{
				auto submenu = CreatePopupMenu();

				for(const auto& subelem : elem->subelements)
				{
					this->Add(subelem);

					AppendMenu(submenu, MF_STRING, subelem->id, (LPTSTR)subelem->text.c_str() );
				}

				AppendMenu(menu, MF_STRING | MF_POPUP, (UINT)submenu, (LPTSTR)elem->text.c_str() );
			}
		}

		SetMenu(this->GetHandle(), menu);
	}

	void Window::Add(Accelerator* accel)
	{
		accel->id = accel->accel.cmd = this->controllersID++;
		this->accelerators.emplace_back(accel);
		this->controllers[accel->id] = ControllerPTR(accel);
	}

	void Window::Draw(Drawable* obj, bool forceRedraw)
	{
		obj->parent = this;
		this->drawables.emplace_back(DrawablePTR(obj));

		if(forceRedraw)
			this->Redraw();
	}

	void Window::Focus()
	{
		if(this->windowHandle != nullptr && SetFocus(this->windowHandle) != 0);
		else
			ERRORMB();		
	}

	void Window::Enable()
	{
		if(this->windowHandle != nullptr)
		{
			EnableWindow(this->windowHandle, true);
			this->Focus();
		}
		else
			ERRORMB();		
	}

	void Window::Disable()
	{
		if(this->windowHandle != nullptr)
			EnableWindow(this->windowHandle, false);
		else
			ERRORMB();		
	}

	void Window::Close()
	{
		if(this->windowHandle != nullptr && DestroyWindow(this->windowHandle) != 0);
		else
			ERRORMB();
	}

	HWND Window::GetHandle() const
	{
		return this->windowHandle;
	}

	void Window::Redraw()
	{
		InvalidateRect(this->windowHandle, nullptr, true);
	}
}