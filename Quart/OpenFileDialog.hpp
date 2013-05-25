#pragma once

#include "object.hpp"
#include <windows.h>
#include "window.hpp"

namespace Quart
{
	class OpenFileDialog
	{
		tstring retStr;
	public:

		OpenFileDialog(Window&, const tstring& filter);

		tstring Get() const;
	};
}