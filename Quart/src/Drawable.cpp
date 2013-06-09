# include "Drawable.hpp"
# include "Window.hpp"

namespace Quart
{
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