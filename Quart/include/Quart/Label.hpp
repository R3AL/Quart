# pragma once

# include "Controller.hpp"

# include <functional>

namespace Quart
{
	class Label : public Controller
	{
	private:
		int width, height;
		tstring text;
		unsigned long style;

	public:
		std::function<void()> OnClick,
			OnDbClick;

		Label(int x,
			  int y,
			  int width,
			  int height,
			  const tstring& text,
			  unsigned long style = (WS_CHILD | WS_VISIBLE | SS_NOTIFY) );

		tstring GetText() const;
		void SetText(const tstring& text);

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}