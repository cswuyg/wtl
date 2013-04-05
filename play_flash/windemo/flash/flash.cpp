#include "stdafx.h"
#include "flash.h"

#include "../utility/utility.h"


FlashPlay::FlashPlay(HWND hwnd)
	: flash_wave_(NULL)
	, flash_wnd_(0)
	, hWnd_(hwnd)
{
}

void FlashPlay::CreateFlashPlay()
{
	CRect rcFlash;
	::GetClientRect(hWnd_, &rcFlash);
	flash_wnd_.Create(hWnd_, rcFlash, NULL, WS_CHILD | WS_CLIPCHILDREN | WS_CLIPSIBLINGS);
	flash_wnd_.CreateControl(L"ShockwaveFlash.ShockwaveFlash.1");
	flash_wnd_.QueryControl(__uuidof(IShockwaveFlash), reinterpret_cast<void**>(&flash_wave_));
	if (flash_wave_ == NULL)
	{
		flash_wnd_.DestroyWindow();
	}
	else
	{
		CString strFlashPath = GetFlashPath();
		CComBSTR bstr(strFlashPath);
		flash_wave_->put_Movie(bstr);
		flash_wave_->Play();
		flash_wnd_.ShowWindow(SW_SHOW);
	}
}

CString FlashPlay::GetFlashPath()
{
	std::wstring app_path = utility::GetModuleFullName();
	std::wstring::size_type nIndex = app_path.find_last_of(L"\\");
	if(std::wstring::npos != nIndex)
	{
		app_path = app_path.substr(0, nIndex);
		nIndex = app_path.find_last_of(L"\\");
		if (std::wstring::npos != nIndex)
		{
			app_path = app_path.substr(0, nIndex);
			app_path += L"\\res\\test.swf";
		}
	}
	else
	{
		app_path = L"";
	}
	return app_path.c_str();
}

void FlashPlay::Pause()
{
	if (flash_wave_)
	{
		flash_wave_->StopPlay();
	}
}

void FlashPlay::Play()
{
	if (flash_wave_)
	{
		flash_wave_->Play();
	}
}

void FlashPlay::Stop()
{
	if (flash_wave_)
	{
		flash_wave_->StopPlay();
		flash_wave_->Release();
		flash_wave_ = NULL;
		flash_wnd_.DestroyWindow();
	}
}


