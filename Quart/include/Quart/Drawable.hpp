# pragma once

# include "Controller.hpp"

namespace Quart
{
	enum class PenStyle : int
	{
		SOLID        = 0,
		DASHED       = 1,
		DOTTED       = 2,
		DASHEDDOT    = 3,
		DASHEDDOTDOT = 4
	};

	class Drawable
	{
		friend class Window;

	private:
		bool hidden;

	public:
		void Hide();
		void Unhide();
		bool IsHidden() const;

	protected:
		Drawable();
		Window* parent;

	private:
		virtual void Draw(HDC&, PAINTSTRUCT&) = 0;
	};
}