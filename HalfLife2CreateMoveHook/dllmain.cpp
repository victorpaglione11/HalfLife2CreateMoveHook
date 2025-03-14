#include "common.h"
#include "minhook/MinHook.h"
#include <windows.h>
#include "hl2/usercmd.h"
#include "utils/mem.h"
#include "hl2/interfaces.h"

HINSTANCE b_hmod = nullptr;

DWORD __stdcall freelib(LPVOID lpParameter) {
	Sleep(100);

	MH_RemoveHook(MH_ALL_HOOKS);
	MH_Uninitialize();

	FreeLibraryAndExitThread(b_hmod, 0);
	Sleep(100);

	return 0;
}

using CreateMove = bool(__thiscall*)(void*, float, C_UserCmd*) noexcept;
static CreateMove CreateMoveOriginal = nullptr;

bool __stdcall	CreateMoveHook(float fTime, C_UserCmd* cmd)
{
	if (cmd->command_number == 0)
		return false;

	//code here

	return false;
}

void hook_setup()
{
	MH_Initialize();                   //vtable -> vfunc index
	MH_CreateHook(mem::Get(interfaces::client_mode, CREATEMOVE_VT_INDEX), &CreateMoveHook, reinterpret_cast<void**>(&CreateMoveOriginal));
	MH_EnableHook(MH_ALL_HOOKS);

}

int WINAPI main()
{
	interfaces::Setup();
	//TODO:
	//implement hook setup like interfaces setup
	hook_setup();

	while (true)
	{
		if (GetAsyncKeyState(VK_TAB)) {
			break;
		}
		Sleep(50);
	}
	CreateThread(NULL, 0, freelib, NULL, 0, NULL);
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hmod, DWORD dwReason, LPVOID pReserved)
{
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		DisableThreadLibraryCalls(hmod);
		b_hmod = hmod;

		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)main, NULL, 0, NULL);
	}
	return TRUE;
}
