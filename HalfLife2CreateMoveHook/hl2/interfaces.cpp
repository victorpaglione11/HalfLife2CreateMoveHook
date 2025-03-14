#include "interfaces.h"
#include <Windows.h>

void interfaces::Setup() noexcept
{
	client = Capture<void>(CLIENT_DLL_INTERFACE, CLIENT_DLL_LIB);
	client_mode = **reinterpret_cast<void***>((*reinterpret_cast<unsigned int**>(client))[10] + 5);
}

template <typename T>
T* interfaces::Capture(const char* name, const char* lib) noexcept
{
	const HINSTANCE m_handle = GetModuleHandleA(lib);

	if (!m_handle)
		return nullptr;

	using Fn = T * (*)(const char*, int*);
	const Fn CreateInterface = reinterpret_cast<Fn>(GetProcAddress(m_handle, "CreateInterface"));

	return CreateInterface(name, nullptr);
}