/**
* Copyright (C) 2019 Elisha Riedlinger
*
* This software is  provided 'as-is', without any express  or implied  warranty. In no event will the
* authors be held liable for any damages arising from the use of this software.
* Permission  is granted  to anyone  to use  this software  for  any  purpose,  including  commercial
* applications, and to alter it and redistribute it freely, subject to the following restrictions:
*
*   1. The origin of this software must not be misrepresented; you must not claim that you  wrote the
*      original  software. If you use this  software  in a product, an  acknowledgment in the product
*      documentation would be appreciated but is not required.
*   2. Altered source versions must  be plainly  marked as such, and  must not be  misrepresented  as
*      being the original software.
*   3. This notice may not be removed or altered from any source distribution.
*/

#include "dinput.h"

HRESULT m_IDirectInputA::QueryInterface(REFIID riid, LPVOID * ppvObj)
{
	if ((riid == IID_IDirectInputA || riid == IID_IUnknown) && ppvObj)
	{
		AddRef();

		*ppvObj = this;

		return S_OK;
	}

	HRESULT hr = ProxyInterface->QueryInterface(riid, ppvObj);

	if (SUCCEEDED(hr))
	{
		genericQueryInterface(riid, ppvObj);
	}

	return hr;
}

ULONG m_IDirectInputA::AddRef()
{
	return ProxyInterface->AddRef();
}

ULONG m_IDirectInputA::Release()
{
	ULONG x = ProxyInterface->Release();

	if (x == 0)
	{
		delete this;
	}

	return x;
}

HRESULT m_IDirectInputA::CreateDevice(REFGUID rguid, LPDIRECTINPUTDEVICEA *lplpDirectInputDevice, LPUNKNOWN pUnkOuter)
{
	HRESULT hr = ProxyInterface->CreateDevice(rguid, lplpDirectInputDevice, pUnkOuter);

	if (SUCCEEDED(hr) && lplpDirectInputDevice)
	{
		*lplpDirectInputDevice = ProxyAddressLookupTable.FindAddress<m_IDirectInputDeviceA>(*lplpDirectInputDevice);
	}

	return hr;
}

HRESULT m_IDirectInputA::EnumDevices(DWORD dwDevType, LPDIENUMDEVICESCALLBACKA lpCallback, LPVOID pvRef, DWORD dwFlags)
{
	return ProxyInterface->EnumDevices(dwDevType, lpCallback, pvRef, dwFlags);
}

HRESULT m_IDirectInputA::GetDeviceStatus(REFGUID rguidInstance)
{
	return ProxyInterface->GetDeviceStatus(rguidInstance);
}

HRESULT m_IDirectInputA::RunControlPanel(HWND hwndOwner, DWORD dwFlags)
{
	return ProxyInterface->RunControlPanel(hwndOwner, dwFlags);
}

HRESULT m_IDirectInputA::Initialize(HINSTANCE hinst, DWORD dwVersion)
{
	return ProxyInterface->Initialize(hinst, dwVersion);
}
