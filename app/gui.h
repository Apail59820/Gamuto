#pragma once
#include <d3d9.h>

#include "converter.h"

namespace gui
{
	constexpr int WIDTH = 600;
	constexpr int HEIGHT = 400;

	inline bool exit = true;

	inline HWND window = nullptr;
	inline WNDCLASSEXA windowClass = { };

	inline POINTS position = { };

	inline PDIRECT3D9 d3d = nullptr;
	inline LPDIRECT3DDEVICE9 device = nullptr;
	inline D3DPRESENT_PARAMETERS presentParameters = { };

	void			CreateHWindow(
								const char* windowName,
								const char* className)		noexcept;

	void			DestroyHWindow()			noexcept;

	bool			CreateDevice()				noexcept;
	void			ResetDevice()				noexcept;
	void			DestroyDevice()				noexcept;

	void			CreateImGui()				noexcept;
	void			DestroyImGui()				noexcept;

	void			BeginRender()				noexcept;
	void			EndRender()					noexcept;
	void			Render()					noexcept;

}
