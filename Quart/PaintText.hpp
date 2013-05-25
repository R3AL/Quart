# pragma once

# include "object.hpp"

# include <string>

namespace Quart
{
    class PaintText : public Object
    {
        tstring text;
    public:
        PaintText(int x,
				  int y,
				  const tstring& text);

        void Draw(HWND&,HDC&,PAINTSTRUCT&);
        LRESULT Proc(HWND,UINT,WPARAM,LPARAM);
    private:
        void Create(HWND&);
    };
}