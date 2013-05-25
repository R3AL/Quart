#include <windows.h>
#include "object.hpp"
#include "window.hpp"

namespace Quart
{
	int Messagebox(const tstring& text, const tstring& title = WIDEN(""), Window* parent = nullptr);
}