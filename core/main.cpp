#include "../dependencies/utilities/csgo.hpp"
#include "features/features.hpp"
#include "../includes.h"

inline int timer = 0;

unsigned long WINAPI initialize(void* instance) {
	while (!GetModuleHandleA("serverbrowser.dll"))
		Sleep(200);

#ifdef _DEBUG
	console::initialize("Debug console");
#endif

	try {
		interfaces::initialize();
		render::initialize();
		hooks::initialize();
	}

	catch (const std::runtime_error & error) {
		MessageBoxA(nullptr, error.what(), "csgo-cheat error!", MB_OK | MB_ICONERROR);
		FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
	}

	while (!GetAsyncKeyState(VK_END))
		std::this_thread::sleep_for(std::chrono::milliseconds(50));
	
	//close menu so input is restored to user in the hooks::paint_traverse::hook hook.
	variables::menu::opened = false;
	//wait for paint_traverse::hook to be called and restore input.
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	FreeLibraryAndExitThread(static_cast<HMODULE>(instance), 0);
}

unsigned long WINAPI release() {
	hooks::release();

#ifdef _DEBUG
	console::release();
#endif

	return TRUE;
}

BOOL __stdcall StartThread(HMODULE hModule, LPTHREAD_START_ROUTINE StartAddress)
{
	return CloseHandle(CreateThread(0, 0, (LPTHREAD_START_ROUTINE)StartAddress, hModule, 0, 0));
}

DWORD LocalPlayer_Get()
{
	Engine engine;
	return *(DWORD*)(engine.GameModule() + dwLocalPlayer);
}
bool LocalPlayer_Exists()
{
	Engine engine;
	if (*(DWORD*)(engine.GameModule() + dwLocalPlayer))
		return true;

	return false;
}
int LocalPlayer_GetHealt()
{
	DWORD Player = LocalPlayer_Get();
	if (Player)
		return *(int*)(Player + m_iHealth);
	return -1;
}
int LocalPlayer_GetTeam()
{
	DWORD Player = LocalPlayer_Get();
	if (Player)
		return *(int*)(Player + m_iTeamNum);
	return -1;
}
int LocalPlayer_CrosshairID()
{
	DWORD Player = LocalPlayer_Get();
	if (Player)
		return *(int*)(Player + m_iCrosshairId);
	return -1;
}

DWORD WINAPI TriggerBotThread(HMODULE instance)
{
	while (!GetAsyncKeyState(VK_END))
	{
		if (variables::Trigger_Bot)
		{
			if (variables::triggerbot_first_time == true)
			{
				console::log("[+] TriggerBot on \n");
				variables::triggerbot_first_time = !variables::triggerbot_first_time;
			}
			Engine engine;
			Entity entity;
			DWORD localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);
			int CrosshairId = LocalPlayer_CrosshairID();
			int LocalTeam = LocalPlayer_GetTeam();
			int LocalHealth = LocalPlayer_GetHealt();

			if (CrosshairId > 0 && CrosshairId < 64)
			{
				DWORD Entity = entity.Get(CrosshairId - 1);
				int EntityTeam = entity.GetTeam(Entity);
				int EntityHealth = entity.GetHealth(Entity);

				if (EntityTeam != LocalTeam)
				{
					if (EntityHealth > 0 && LocalHealth > 0)
					{
						Sleep(variables::delay_trigger_bot);
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						if (timer == 20)
						{
							console::log("[::] TriggerBot: Shoot\n");
							timer = 0;
						}
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
						timer++;
					}
				}
			}
		}
		Sleep(1);
	}
	FreeLibraryAndExitThread(instance, 0);
}

bool localPlayer_Exists()
{
	Engine engine;
	if (*(DWORD*)(engine.GameModule() + dwLocalPlayer))
		return true;

	return false;
}

DWORD WINAPI GlowThread(HMODULE instance)
{
	Engine engine;
	while (!GetAsyncKeyState(VK_END))
	{
		DWORD localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);
		if (variables::glow && localplayer != NULL)
		{
			DWORD GlowObj = *(DWORD*)(engine.GameModule() + dwGlowObjectManager);
			DWORD Entity = *(DWORD*)(engine.GameModule() + dwEntityList);
			int LocalTeam = *(int*)(dwLocalPlayer + m_iTeamNum);

			for (int i = 1; i < 32; i++)
			{
				DWORD entity = *(DWORD*)(Entity + i * 0x10);

				if (entity != NULL)
				{
					int EntityTeam = *(int*)(entity + m_iTeamNum);
					int GlowIndex = *(int*)(entity + m_iGlowIndex);

					if (EntityTeam == LocalTeam)
					{
						*(float*)((GlowObj + GlowIndex * 0x38 + 0x8)) = 0.f; // R
						*(float*)((GlowObj + GlowIndex * 0x38 + 0xC)) = 1.f; // G
						*(float*)((GlowObj + GlowIndex * 0x38 + 0x10)) = 0.f; // B
						*(float*)((GlowObj + GlowIndex * 0x38 + 0x14)) = 1.4f; // A
					}
					else
					{
						*(float*)((GlowObj + GlowIndex * 0x38 + 0x8)) = 1.f; // R
						*(float*)((GlowObj + GlowIndex * 0x38 + 0xC)) = 0.f; // G
						*(float*)((GlowObj + GlowIndex * 0x38 + 0x10)) = 0.f; // B
						*(float*)((GlowObj + GlowIndex * 0x38 + 0x14)) = 1.4f; // A
					}
					*(bool*)((GlowObj + GlowIndex * 0x38 + 0x28)) = true;
					*(bool*)((GlowObj + GlowIndex * 0x38 + 0x29)) = false;
				}
			}
		}
		Sleep(1);
	}
	FreeLibraryAndExitThread(instance, 0);
}

void SetEntitySpotted(DWORD _base, BYTE _value)
{
	//printf("[Engine] SetEntitySpotted\n");
	*(BYTE*)(_base + m_bSpotted) = _value;
}

/*DWORD WINAPI RadarThread(HMODULE instance)
{
	Engine engine;
	while (!GetAsyncKeyState(VK_END))
	{
		DWORD localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);

		if (localplayer != NULL)
		{
			for (int i = 0; i < 32; i++)
			{
				DWORD base = GetEntityById(i);
				if (base)
				{
					int LocalTeam = *(int*)(dwLocalPlayer + m_iTeamNum);
					int EntityTeam = *(int*)(base + m_iTeamNum);
					if (EntityTeam != LocalTeam)
					{
						if (*(BYTE*)(base + m_bSpotted) = 1)
						{

						}
					}
				}
			}
		}
	}
	FreeLibraryAndExitThread(instance, 0);
}*/

std::int32_t WINAPI DllMain(const HMODULE instance [[maybe_unused]], const unsigned long reason, const void* reserved [[maybe_unused]] ) {
	DisableThreadLibraryCalls(instance);

	switch (reason) {
	case DLL_PROCESS_ATTACH: {
		Engine engine;
		engine.Init();
		StartThread(instance, (LPTHREAD_START_ROUTINE)TriggerBotThread);
		//StartThread(instance, (LPTHREAD_START_ROUTINE)RadarThread);
		StartThread(instance, (LPTHREAD_START_ROUTINE)GlowThread);
		if (auto handle = CreateThread(nullptr, NULL, initialize, instance, NULL, nullptr))
			CloseHandle(handle);

		break;
	}

	case DLL_PROCESS_DETACH: {
		release();
		break;
	}
	}

	return true;
}
