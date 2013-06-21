# pragma once

# include "Controller.hpp"

# include <functional>
# include <CommCtrl.h>

namespace Quart
{
	class ListView : public Controller
	{
	private:
		int width, height;
		unsigned long style;
		unsigned int collumnsNumber;

	public:
		ListView(int x,
				 int y,
				 int width,
				 int height,
				 unsigned long style = (WS_CHILD		 |
										WS_VISIBLE		 |
										LVS_REPORT		 |
										LVS_EDITLABELS	 |
										LVS_SHOWSELALWAYS));

		void AddCollumn(const tstring& text, int index = -1, unsigned int width = 100);
		void AddItem(unsigned int index, ...);
		void RemoveItem(unsigned int index);
		void EditItem(unsigned int index, ...);
		void ScrollTo(unsigned int index);
		void Select(unsigned int index);
		void Unselect(unsigned int index = -1);
		void Clear();

		int Count() const;
		int SelectionIndex() const;
	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}