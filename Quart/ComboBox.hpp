# include "object.hpp"
# include <vector>

namespace Quart
{
	class Window;
	class ComboBox : public Object
	{
		friend class Window;
		std::vector<tstring> items;
	public:
		using Object::operator HWND;

		ComboBox(int x,
				 int y,
				 int width,
				 int height,
				 HWND parent = nullptr,
				 unsigned long styles = (CBS_DROPDOWN | CBS_HASSTRINGS | WS_CHILD | WS_OVERLAPPED | WS_VISIBLE) );
		
		void Draw(HWND&,HDC&,PAINTSTRUCT&);
		void Create(HWND&);

		void Add(const tstring&);
		void Remove(const unsigned int);
		unsigned int SelectionIndex() const;

	};
}