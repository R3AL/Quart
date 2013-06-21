# include "Drawable.hpp"
# include "..\Window.hpp"

namespace Quart
{
	namespace Gdi
	{
		rgb::rgb():
			valid(false)
		{

		}
		rgb::rgb(unsigned long value):
			valid(true)
		{
			this->r = GetRValue(value);
			this->g = GetGValue(value);
			this->b = GetBValue(value);
		}

		rgb::rgb(unsigned char r, unsigned char g, unsigned char b):
			r(r), g(g), b(b), valid(true)
		{

		}

		rgb::operator long() const
		{
			return this->operator unsigned long();
		}

		rgb::operator unsigned long() const
		{
			return RGB(r, g, b);
		}

		bool rgb::operator !=(int) const
		{
			return this->valid;
		}

		Drawable::Drawable(): hidden(false), parent(nullptr)
		{

		}

		void Drawable::Hide()
		{
			if(this->parent != nullptr)
			{
				this->hidden = true;
				this->parent->Redraw();
			}
		}

		void Drawable::Unhide()
		{
			if(this->parent != nullptr)
			{
				this->hidden = false;
				this->parent->Redraw();
			}
		}

		bool Drawable::IsHidden() const
		{
			return this->hidden;
		}
	}
}