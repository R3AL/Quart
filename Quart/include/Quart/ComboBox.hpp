# pragma once

# include "Controller.hpp"

# include <functional>

namespace Quart
{
	class ComboBox : public Controller
	{
	private:
		int width, height;
		unsigned long style;
		unsigned int elementCount;

	public:
		std::function<void()> OnListClose,
			OnListOpen,
			OnElementEdit,
			OnFocus,
			OnFocusLost,
			OnSelectionChanged,
			OnSelectionCanceled;

		ComboBox(int x,
				 int y,
				 int width,
				 int height,
				 unsigned long style = (WS_CHILD	   |
										WS_VISIBLE	   |
										WS_OVERLAPPED  |
										WS_TABSTOP	   |
										CBS_HASSTRINGS |
										CBS_DROPDOWN));

		void Add(const tstring& text);
		void Remove(unsigned int index);
		unsigned int Count() const;
		int SelectionIndex() const;
		void Select(unsigned int index);

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}