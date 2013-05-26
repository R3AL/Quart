# pragma once

#include "object.hpp"

#include <windows.h>
#include <vector>
#include <memory>

namespace Quart
{
	class SubmenuElement : public Object
	{
		friend class Window;
		friend class MenuBar;
		tstring text;
	public:
		SubmenuElement(const tstring&);
		void Create(HWND&);

	private:
		void Draw(HWND&,HDC&,PAINTSTRUCT&);
	};

	class MenuElement
	{
		friend class Window;
		friend class MenuBar;
		std::vector<SubmenuElement*> subelements;
		tstring text;
	public:
		MenuElement(const tstring&, unsigned int, ...);
	};

	class MenuBar
	{
		friend class Window;
		typedef std::unique_ptr<MenuElement> MenuElementPTR;
		std::vector<MenuElementPTR> elements;
		HMENU menu, submenu;
		Window* parent;
	public:
		void Set(HWND&);
		MenuBar(Window*);
		void Add(MenuElement*);
	};
}