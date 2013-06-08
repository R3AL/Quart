# pragma once

# include "Controller.hpp"

# include <vector>
# include <functional>

namespace Quart
{
	class MenuSubElement : public Controller
	{
		friend class Window;

	private:
		tstring text;

	public:
		std::function<void()> OnClick;

		MenuSubElement(const tstring&);

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};

	class MenuElement : public Controller
	{
		friend class Window;

	private:
		std::vector<MenuSubElement*> subelements;
		tstring text;

	public:
		std::function<void()> OnClick;
		
		MenuElement(const tstring& text);
		MenuElement(const tstring& text, unsigned int subelementCount, ...);

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};

	class MenuBar
	{
		friend class Window;

	private:
		std::vector<MenuElement*> elements;

	public:
		MenuBar();
		void Add(MenuElement*);
	};
}