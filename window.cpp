# include "window.hpp"
# include "Button.hpp"
# include "MessageBox.hpp"

# include <CommCtrl.h>
# include <time.h>

namespace Quart
{
	Window::Window(unsigned int width, 
                   unsigned int height, 
                   const tstring& title,
				   Window* parent)
    {
		srand(static_cast<unsigned int>(time(NULL)));

        this->width      = width;
        this->height     = height;
        this->windowName = title;
        this->className  = WIDEN(__TIME__) + to_tstring(rand()) + to_tstring(rand());
        this->instance   = nullptr;
        this->handle     = nullptr;
		this->menuBar    = nullptr;
		this->accels	 = nullptr;
		this->parent	 = parent;
    }

    bool Window::Create(unsigned long style,
						unsigned long EXstyle,
                        int cmdShow, 
                        int x, 
                        int y, 
                        unsigned short cursor,
                        unsigned short icon,
                        unsigned short iconSmall)
    {
        this->instance = GetModuleHandle(0);

        WNDCLASSEX windowclass = {0};

		if(this->parent == nullptr)
		{
			windowclass.cbSize        = sizeof(WNDCLASSEX);
			windowclass.style         = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
			windowclass.lpfnWndProc   = Window::_wndproc;
			windowclass.cbClsExtra    = 0;
			windowclass.cbWndExtra    = 0;
			windowclass.hInstance     = this->instance;
			windowclass.hIcon         = LoadIcon(nullptr, MAKEINTRESOURCE(icon));
			windowclass.hCursor       = LoadCursor(nullptr, MAKEINTRESOURCE(cursor));
			windowclass.hbrBackground = (HBRUSH)(COLOR_WINDOW+1);
			windowclass.lpszMenuName  = nullptr;
			windowclass.lpszClassName = this->className.c_str();
			windowclass.hIconSm       = LoadIcon(nullptr, MAKEINTRESOURCE(iconSmall));
		}
		else
		{
			windowclass.cbSize           = sizeof(WNDCLASSEX);
			windowclass.lpfnWndProc      = Window::_wndproc;
			windowclass.hInstance        = this->instance;
			windowclass.hbrBackground    = GetSysColorBrush(COLOR_3DFACE);
			windowclass.lpszClassName    = this->className.c_str();

			if(!EXstyle)
				EXstyle = WS_EX_DLGMODALFRAME;
		}


		if(!RegisterClassEx(&windowclass))
		{
			Messagebox(WIDEN("Registering window class failed !"));
			return false;
		}

        this->handle = CreateWindowEx(  EXstyle,
                                        this->className.c_str(),
                                        this->windowName.c_str(),
                                        style,
                                        x,
                                        y,
                                        this->width,
                                        this->height,
                                        (this->parent != nullptr ? this->parent->operator HWND() : nullptr),
                                        nullptr,
                                        this->instance,
                                        (void*)this);

        if(!this->handle)
        {
            Messagebox(WIDEN("Creating window failed !"));
            return false;
        }

        ShowWindow(this->handle, cmdShow);
        UpdateWindow(this->handle);

        for(auto i = objects.begin(); i != objects.end(); ++i)
            i->second->Create(this->handle);

        return true;
    }
    
	int Window::Run(unsigned long style,
					unsigned long EXstyle,
					int cmdShow,
					int x,
					int y,
					unsigned short cursor,
					unsigned short icon,
					unsigned short iconSmall)
    {
		auto count = this->accelerators.size();
		auto accel = new ACCEL[count];
		
		auto i = 0;
		for(const auto& elem : this->accelerators)
			accel[i++] = (ACCEL)(*elem.second);

		auto accelTable = CreateAcceleratorTable(accel, count);
		delete accel;

		if(this->Create(style, EXstyle, cmdShow, x, y, cursor, icon, iconSmall))
		{
			while (GetMessage(&this->msg, nullptr, 0, 0))
			{
				if(!TranslateAccelerator(msg.hwnd, accelTable, &this->msg))
				{
					TranslateMessage(&this->msg);
					DispatchMessage(&this->msg);
				}
			}
		}
		return static_cast<int>(msg.wParam);
    }

    Window::operator HWND()
    {
        return this->handle;
    }

	void Window::Enable(bool state)
	{
		EnableWindow(this->handle, state);

		if(state)
			SetFocus(this->handle);
	}

	void Window::Disable()
	{
		this->Enable(false);
	}

	void Window::Close()
	{
		DestroyWindow(this->handle);
	}

    void Window::Add(Object* obj)
    {
        this->objects[obj->id] = ObjectPTR(obj);
    }

	void Window::Add(MenuBar* mb)
	{
		this->menuBar = MenuBarPTR(mb);
		
		for(auto& element : mb->elements)
		{
			for(auto& subelement : element->subelements)
				this->Add(subelement);
		}
	}

	void Window::Add(Accelerator* accel)
	{
		this->objects[accel->id]      = ObjectPTR(accel);
		this->accelerators[accel->id] = accel;
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

    LRESULT Window::WindowProc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        HDC hdc;
        PAINTSTRUCT ps;
        switch (message)
        {
		case WM_CTLCOLORSTATIC:
			{
				auto hdc = (HDC) wparam; 
				SetTextColor(hdc, RGB(0,0,0));    
				SetBkMode (hdc, TRANSPARENT);

				return (LRESULT)GetStockObject(NULL_BRUSH);
			}
        case WM_CREATE:
			{
				if(this->menuBar != nullptr)
					this->menuBar->Set(hwnd);
// [ Stop auto calling accelerators
// 				for(const auto& obj : objects)
// 					obj.second->Proc(hwnd, message, wparam, lparam);
// ]
			}
            return 0;

        case WM_PAINT:
            for(auto i = objects.begin(); i != objects.end(); ++i)
                i->second->Draw(hwnd,hdc,ps);
            return DefWindowProc (hwnd, message, wparam, lparam);

        case WM_COMMAND:
             return objects[LOWORD(wparam)]->Proc(hwnd,HIWORD(wparam),wparam,lparam);
            //return DefWindowProc (hwnd, message, wparam, lparam);

        case WM_DESTROY:
			if(this->callback.count(message))
				if(this->callback[message] != nullptr)
					this->callback[message](wparam,lparam);
			PostQuitMessage(0);
            return 0;

		default:
			if(this->callback.count(message))
			{
				if(this->callback[message] != nullptr)
					this->callback[message](wparam,lparam);
			}
        }
        return DefWindowProc (hwnd, message, wparam, lparam);
    }

}