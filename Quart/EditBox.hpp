# include "object.hpp"

namespace Quart
{
	class EditBox : public Object
	{
		tstring text;
	public:
		using Object::operator HWND;

		EditBox(int id,
				int x,
				int y,
				int width,
				int height,
				const tstring& text,
				HWND parent = nullptr,
				unsigned long styles = (WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | ES_AUTOHSCROLL | ES_AUTOVSCROLL) );

		void Draw(HWND&,HDC&,PAINTSTRUCT&);
		void Create(HWND&);

		tstring GetText() const;
		void SetText(const tstring&);
		void Clear();
	};
}