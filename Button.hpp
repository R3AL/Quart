# include "object.hpp"

namespace Quart
{
    class Button : public Object
    {
        tstring text;
    public:
        using Object::operator HWND;

        Button(int id,
               int x,
               int y,
               int width,
               int height,
               const tstring& text,
               HWND parent = nullptr,
               unsigned long styles = (WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON)
               );

        void Draw(HWND&,HDC&,PAINTSTRUCT&);
        void Create(HWND&);

    };
}