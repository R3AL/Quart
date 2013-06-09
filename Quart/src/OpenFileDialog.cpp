# include "OpenFileDialog.hpp"

namespace Quart
{
	OpenFileDialog::OpenFileDialog(Window& parent, const tstring& filter)
	{
		OPENFILENAME ofn           = {0};
		TCHAR FileName[MAX_PATH]   = WIDEN("");
		TCHAR leFilter[MAX_PATH]   = WIDEN("");

		unsigned int i = 0;
		for(const auto& letter : filter)
			leFilter[i++] = letter;

		ofn.lStructSize    = sizeof(OPENFILENAME);
		ofn.hwndOwner      = parent.GetHandle();
		ofn.lpstrFilter    = leFilter;
		ofn.lpstrFile      = FileName;
		ofn.nMaxFile       = MAX_PATH;
		ofn.Flags          = OFN_EXPLORER | OFN_FILEMUSTEXIST;
		ofn.nFileOffset    = 0;
		ofn.nFileExtension = 0;
		ofn.nFilterIndex   = 0;

		if(GetOpenFileName(&ofn))
			this->retStr = tstring(FileName);
	}

	tstring OpenFileDialog::Get() const
	{
		return this->retStr;
	}
}