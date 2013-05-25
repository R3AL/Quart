# include "object.hpp"

# include <CommCtrl.h>

namespace Quart
{
	class ListView : public Object
	{
		unsigned int collumnsNumber;
	public:
		using Object::operator HWND;

		ListView(int x,
				 int y,
				 int width,
				 int height,
				 HWND parent = nullptr,
				 unsigned long styles = (WS_CHILD | LVS_REPORT | LVS_EDITLABELS | LVS_SHOWSELALWAYS ) );
	
	void Draw(HWND&,HDC&,PAINTSTRUCT&);
	void Create(HWND&);

	void AddCollumn(const tstring&, int index = -1, unsigned int = 100);
	void AddItem(unsigned int index, ...);
	void EditItem(unsigned int index, ...);
	void RemoveItem(unsigned int index);
	void ScrollTo(unsigned int index);
	void Clear();
	};
}