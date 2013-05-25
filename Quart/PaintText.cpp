# include "PaintText.hpp"

namespace Quart
{
	PaintText::PaintText(int id, int x, int y, const tstring& text): Object(id, x, y), text(text) {}

    void PaintText::Draw(HWND& hwnd, HDC& hdc, PAINTSTRUCT& ps)
    {
        hdc = BeginPaint(hwnd, &ps);
        TextOut(hdc, x, y, text.c_str(), text.length() );
        EndPaint(hwnd, &ps);
    }

    void PaintText::Create(HWND&) {}
    LRESULT PaintText::Proc(HWND,UINT,WPARAM,LPARAM) { return 0; }
}