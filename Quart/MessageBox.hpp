# pragma once

# include <windows.h>

# include "Controller.hpp"
# include "Window.hpp"

namespace Quart
{
	int Messagebox(const tstring& text, const tstring& title = WIDEN(""), Window* parent = nullptr);
}