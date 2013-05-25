#include "SaveFileDialog.hpp"

namespace Quart
{
	SaveFileDialog::SaveFileDialog(Window& parent, const tstring& filter)
	{
		OPENFILENAME ofn           = {0};
		TCHAR FileName[MAX_PATH]   = WIDEN("");
		TCHAR leFilter[MAX_PATH]   = WIDEN("");

		unsigned int i = 0;
		for(const auto& letter : filter)
			leFilter[i++] = letter;

		ofn.lStructSize     = sizeof(ofn);
		ofn.hwndOwner       = parent;
		ofn.lpstrFilter		= leFilter;
		ofn.lpstrFile       = FileName;
		ofn.lpstrInitialDir = WIDEN(".");
		ofn.nMaxFile        = MAX_PATH;
		ofn.Flags           = OFN_EXPLORER | OFN_PATHMUSTEXIST | OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT;

		if(GetSaveFileName(&ofn))
			this->retStr = tstring(FileName);
	}

	tstring SaveFileDialog::Get() const
	{
		return this->retStr;
	}
}