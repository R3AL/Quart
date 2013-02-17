# include "Button.hpp"

namespace Quart
{
    Button::Button(int id, 
        int x, 
        int y, 
        int width, 
        int height, 
        const tstring& text, 
        HWND parent, 
        unsigned long styles) : Object(id, x, y, width, height, styles), text(text)
    {
        this->parent = nullptr;
    }

    void Button::Draw(HWND& hwnd, HDC& hdc, PAINTSTRUCT& ps) {}

    void Button::Create(HWND& parent)
    {
        this->parent = parent;
        this->handle = CreateWindowEx(NULL,
            WIDEN("BUTTON"),
            this->text.c_str(),
            this->styles,
            this->x,
            this->y,
            this->width,
            this->height,
            this->parent,
            (HMENU)this->id,
            (HINSTANCE)GetWindowLongPtr(this->parent, GWL_HINSTANCE),
            NULL);
        ShowWindow(this->handle, SW_SHOW);
    }

    LRESULT Button::Proc(HWND hwnd, UINT message, WPARAM wparam, LPARAM lparam)
    {
        if(message == WM_LBUTTONDBLCLK)
            MessageBox(NULL,L"DUBLU",NULL,NULL);
        if(this->callback.count(message))
        {
            if(this->callback[message] != nullptr)
                this->callback[message](wparam,lparam);
        }

        return 0;
    }

}