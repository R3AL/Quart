# pragma once

# include "Controller.hpp"
# include "Window.hpp"

namespace Quart
{
	class SaveFileDialog
	{
	private:
		tstring retStr;

	public:
		SaveFileDialog(Window& parent, const tstring& filter = WIDEN("All files\0*.*"));

		tstring Get() const;
	};
}