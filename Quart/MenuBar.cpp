#include "MenuBar.hpp"
#include <cstdarg>
# include "Window.hpp"

namespace Quart
{
	SubmenuElement::SubmenuElement(const tstring& txt):
		Object(0, 0), text(txt) {}

	void SubmenuElement::Create(HWND&) {}
	void SubmenuElement::Draw(HWND&,HDC&,PAINTSTRUCT&) {}

	MenuElement::MenuElement(const tstring& txt, unsigned int count, ...)
	{
		this->text = txt;

		va_list list;
		va_start(list, count);

		for(unsigned int i = 0; i < count; ++i)
		{
			auto var = va_arg(list, SubmenuElement*);
			this->subelements.emplace_back(var);
		}

		va_end(list);
	}

	MenuBar::MenuBar(Window* parent) : parent(parent)
	{
		this->menu = CreateMenu();
	}

	void MenuBar::Set(HWND& hwnd)
	{
		SetMenu(hwnd, this->menu);
	}

	void MenuBar::Add(MenuElement* elem)
	{
		this->submenu = CreatePopupMenu();

		this->elements.emplace_back(MenuElementPTR(elem));

		for(auto& subelem : elem->subelements)
		{
			subelem->id = this->parent->objID++;
			AppendMenu(this->submenu, MF_STRING, subelem->id, subelem->text.c_str());
		}

		AppendMenu(this->menu, MF_STRING | MF_POPUP, (UINT)this->submenu, (LPTSTR)elem->text.c_str());
	}
}