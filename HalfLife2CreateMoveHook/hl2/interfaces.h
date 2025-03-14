#define CLIENT_DLL_LIB				"client.dll"
#define CLIENT_DLL_INTERFACE		"VClient017"
#define CREATEMOVE_VT_INDEX			22

namespace interfaces
{
	void Setup() noexcept;

	template <typename T>
	T* Capture(const char* name, const char* lib) noexcept;

	inline void* client = nullptr;
	inline void* client_mode = nullptr;
}