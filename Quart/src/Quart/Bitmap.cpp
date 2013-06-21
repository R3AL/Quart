# include "Bitmap.hpp"
# include "Window.hpp"
# include "Messagebox.hpp"

namespace Quart
{
	Bitmap::Bitmap(const tstring& fileName, int x, int y):
		Controller(x, y, Controller::BMP), 
		fileName(fileName)
	{
		this->bitmap = (HBITMAP)LoadImage(GetModuleHandle(0),
			this->fileName.c_str(),
			IMAGE_BITMAP,
			0, 0,
			LR_LOADFROMFILE);

		if(!this->bitmap)
			ERRORMB();
	}


	void Bitmap::Create(Window* parent)
	{
		this->handle = CreateWindowEx(
			0,
			WIDEN("static"),
			nullptr,
			WS_VISIBLE | WS_CHILD | SS_BITMAP,
			this->x,
			this->y,
			0,
			0,
			parent->GetHandle(),
			(HMENU)this->id,
			GetModuleHandle(0),
			nullptr);

		if(!this->handle)
			ERRORMB();

		SendMessage(this->handle, STM_SETIMAGE, (WPARAM)IMAGE_BITMAP, (LPARAM)this->bitmap);
	}

	void Bitmap::MsgHandler(WPARAM, LPARAM)
	{

	}

	Bitmap::~Bitmap()
	{
		DeleteObject(this->bitmap);
	}
}