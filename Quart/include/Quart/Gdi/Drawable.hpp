# pragma once

# include "..\Controller.hpp"

namespace Quart
{
	namespace Gdi
	{
		enum class PenStyle : int
		{
			SOLID        = 0,
			DASHED       = 1,
			DOTTED       = 2,
			DASHEDDOT    = 3,
			DASHEDDOTDOT = 4
		};

		struct rgb
		{
		private:
			bool valid;

		public:
			unsigned char r,
						  g,
						  b;

			rgb();
			rgb(unsigned long);
			rgb(unsigned char, unsigned char, unsigned char);

			operator long() const;
			operator unsigned long() const;
			bool operator!=(int) const;
		};

		namespace Colors
		{
			static const rgb RED   = rgb(255,   0,   0);
			static const rgb GREEN = rgb(0  , 255,   0);
			static const rgb BLUE  = rgb(0  ,   0, 255);
			static const rgb WHITE = rgb(255, 255, 255);
			static const rgb BLACK = rgb(0  ,   0,   0);
		}

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
}