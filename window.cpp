# include "window.hpp"
# include "Button.hpp"


namespace Quart
{
	Window::Window(unsigned int width, 
                   unsigned int height, 
                   const tstring& title)
    {
        this->width      = width;
        this->height     = height;
        this->windowName = title;
        this->className  = WIDEN(__TIME__);
        this->instance   = nullptr;
        this->handle     = nullptr;
    }

    bool Window::Create(HINSTANCE instance,
                        int cmdShow, 
                        int x, 
                        int y, 
                        unsigned short cursor,
                        unsigned short icon,
                        unsigned short iconSmall,
                        unsigned long style)
    {
        this->instance = instance;
        WNDCLASSEX windowclass;

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

        if(!RegisterClassEx(&windowclass))
        {
            MessageBox(NULL,L"Registering class failed",NULL,NULL);
            return false;
        }

        this->handle = CreateWindowEx(  NULL,
                                        this->className.c_str(),
                                        this->windowName.c_str(),
                                        style,
                                        x,
                                        y,
                                        this->width,
                                        this->height,
                                        nullptr,
                                        nullptr,
                                        this->instance,
                                        (void*)this);

        if(!this->handle)
        {
            MessageBox(NULL,L"Creating window failed",NULL,NULL);
            return false;
        }

        ShowWindow(this->handle, cmdShow);
        UpdateWindow(this->handle);

        for(auto i = objects.begin(); i != objects.end(); ++i)
            i->second->Create(this->handle);

        return true;
    }
    
    int Window::Run(HINSTANCE instance,
        int cmdShow,
        int x,
        int y,
        unsigned short cursor,
        unsigned short icon,
        unsigned short iconSmall,
        unsigned long style)
    {
        if(this->Create(instance,cmdShow,x,y,cursor,icon,iconSmall,style))
        {
            while (GetMessage(&this->msg, nullptr, 0, 0))
            {
                TranslateMessage(&this->msg);
                DispatchMessage(&this->msg);
            }
            return static_cast<int>(msg.wParam);
        }
        return 1;
    }

    Window::operator HWND()
    {
        return this->handle;
    }

    void Window::Add(Object* obj)
    {
        this->objects[obj->id] = ObjectPTR(obj);
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
        case WM_CREATE:
            
            return 0;

        case WM_PAINT:
            for(auto i = objects.begin(); i != objects.end(); ++i)
                i->second->Draw(hwnd,hdc,ps);
            return DefWindowProc (hwnd, message, wparam, lparam);

        case WM_COMMAND:
                objects[LOWORD(wparam)]->Proc(hwnd,HIWORD(wparam),wparam,lparam);
            return DefWindowProc (hwnd, message, wparam, lparam);

        case WM_DESTROY:
                PostQuitMessage(0);
            return 0;

        }
        return DefWindowProc (hwnd, message, wparam, lparam);
    }

}