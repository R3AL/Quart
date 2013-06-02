# include "MenuBar.hpp"

namespace Quart
{
	MenuSubElement::MenuSubElement(const tstring& text): 
		text(text),
		OnClick(nullptr)
	{}

	void MenuSubElement::Create(Window*) {}
	
	void MenuSubElement::MsgHandler(WPARAM wparam, LPARAM)
	{
		if(wparam == 0 && this->OnClick != nullptr)
			this->OnClick();
	}

	MenuElement::MenuElement(const tstring& text, unsigned int count, ...):
		text(text),
		OnClick(nullptr)
	{
		va_list list;
		va_start(list, count);

		for(unsigned int i = 0; i < count; ++i)
			this->subelements.emplace_back(va_arg(list, MenuSubElement*));

		va_end(list);
	}

	MenuElement::MenuElement(const tstring& text):
		text(text),
		OnClick(nullptr)
	{

	}

	void MenuElement::Create(Window*) {}

	void MenuElement::MsgHandler(WPARAM wparam, LPARAM)
	{
		if(wparam == 0 && this->OnClick != nullptr)
			this->OnClick();
	}

	MenuBar::MenuBar()
	{
	}

	void MenuBar::Add(MenuElement* elem)
	{
		this->elements.emplace_back(elem);
	}
}