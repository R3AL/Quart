# include "Messagebox.hpp"

namespace Quart
{
	int Messagebox(const tstring& text, const tstring& title, Window* parent)
	{
		return ::MessageBox( ( parent != nullptr ? parent->GetHandle() : nullptr), text.c_str(), title.c_str(), 0);
	}
}