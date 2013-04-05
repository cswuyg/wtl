#pragma once

#include <atlstr.h>
#include <atltypes.h>
#include <atlwin.h>
#pragma warning( disable:4192 )
#import "..\res\Flash32_11_5_502_135.ocx" raw_interfaces_only, raw_native_types, no_namespace, named_guids, rename("IDispatchEx","IMyDispatchEx")

class FlashPlay{
public:
	FlashPlay(HWND m_hwnd);
	~FlashPlay(){};

	void CreateFlashPlay();
	void Pause();
	void Play();
	void Stop();
private:
	CString GetFlashPath();
private:
	CAxWindow            flash_wnd_;	                  //用于展示flash
	IShockwaveFlash*     flash_wave_;                    //flash控件
	HWND hWnd_;
};