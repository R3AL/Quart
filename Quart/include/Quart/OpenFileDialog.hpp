# pragma once

# include "Controller.hpp"
# include "Window.hpp"

namespace Quart
{
	class OpenFileDialog
	{
	private:
		tstring retStr;

	public:
		OpenFileDialog(Window& parent, const tstring& filter = WIDEN("All files\0*.*"));

		tstring Get() const;
	};
}