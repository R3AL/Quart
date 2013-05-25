#include "MessageBox.hpp"

namespace Quart
{
	int Messagebox(const tstring& text, const tstring& title, Window* parent)
	{
		return ::MessageBox((HWND)parent, text.c_str(), title.c_str(), NULL);
	}
}