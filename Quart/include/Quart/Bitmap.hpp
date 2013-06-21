# pragma once

# include "Controller.hpp"

namespace Quart
{
	class Bitmap : public Controller
	{
	private:
		tstring fileName;
		HBITMAP bitmap;

	public:
		Bitmap(const tstring& fileName,
			   int x,
			   int y);

		~Bitmap();

	private:
		void Create(Window*);
		void MsgHandler(WPARAM, LPARAM);
	};
}