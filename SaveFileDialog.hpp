#pragma once

#include "object.hpp"
#include <windows.h>
#include "window.hpp"

namespace Quart
{
	class SaveFileDialog
	{
		tstring retStr;
	public:

		SaveFileDialog(Window&, const tstring& filter);

		tstring Get() const;
	};
}