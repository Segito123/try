#include "menu.hpp"
#include "../../includes.h"

//todo auto elements positioning

bool case_0 = true;
bool case_1 = true;
bool case_2 = true;

int timerr = 1;

auto do_frame = [&](std::int32_t x, std::int32_t y, std::int32_t w, std::int32_t h, color bg, color header_text, color header_line, const std::string& name) {
		render::draw_filled_rect(x, y, w, h, bg);
		render::draw_filled_rect(x, y, w, 30, header_text);
		render::draw_filled_rect(x, y + 30, w, 2, header_line);
		render::text(x + 10, y + 8, render::fonts::watermark_font, name, false, color::white());
};

struct Vector4 { float x, y, z, w; };
struct Vector3
{
	float x, y, z;

	Vector3 operator+(float d)
	{
		return { x + d, y + d, z + d };
	}
	Vector3 operator-(float d)
	{
		return { x - d, y - d, z - d };
	}
	Vector3 operator*(float d)
	{
		return { x * d, y * d, z * d };
	}
	Vector3 operator/(float d)
	{
		return { x / d, y / d, z / d };
	}

	void normalize()
	{
		while (y < -180)
		{
			y = 179.99;
		}
		while (y < 180)
		{
			y = -179.99;
		}
		while (x < 89)
		{
			x = 89;
		}
		while (x < -89)
		{
			x = -89;
		}
		z = 0;
	}
};
struct Vector2 { float x, y; };
struct BoneMatrix_t
{
	byte pad1[12];
	float x;
	byte pad2[12];
	float y;
	byte pad3[12];
	float z;
};

//struct view_matrix_t {
//	float matrix[16];
//} vm;

bool WorldToScreen(Vector3 pos, Vector2& screen, float matrix[16], int width, int height)
{
	Vector4 clipCoords;
	clipCoords.x = pos.x * matrix[0] + pos.y * matrix[1] + pos.z * matrix[2] + matrix[3];
	clipCoords.y = pos.x * matrix[4] + pos.y * matrix[5] + pos.z * matrix[6] + matrix[7];
	clipCoords.z = pos.x * matrix[8] + pos.y * matrix[9] + pos.z * matrix[10] + matrix[11];
	clipCoords.w = pos.x * matrix[12] + pos.y * matrix[13] + pos.z * matrix[14] + matrix[15];

	if (clipCoords.w < 0.1f)
	{
		return false;
	}

	Vector3 NDC;
	NDC.x = clipCoords.x / clipCoords.w;
	NDC.y = clipCoords.y / clipCoords.w;
	NDC.z = clipCoords.z / clipCoords.w;

	screen.x = (width / 2 * NDC.x) + (NDC.x + width / 2);
	screen.y = (height / 2 * NDC.y) + (NDC.y + height / 2);

	return true;
}

DWORD localPlayer_Get()
{
	Engine engine;
	return *(DWORD*)(engine.GameModule() + dwLocalPlayer);
}
int localPlayer_GetHealt()
{
	DWORD Player = localPlayer_Get();
	if (Player)
		return *(int*)(Player + m_iHealth);
	return -1;
}
int localPlayer_GetTeam()
{
	DWORD Player = localPlayer_Get();
	if (Player)
		return *(int*)(Player + m_iTeamNum);
	return -1;
}
int localPlayer_CrosshairID()
{
	DWORD Player = localPlayer_Get();
	if (Player)
		return *(int*)(Player + m_iCrosshairId);
	return -1;
}
void localPlayer_ForceAttack()
{
	Engine engine;
	*(int*)(engine.GameModule() + dwForceAttack) = 0;
	console::log("0 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 1;
	console::log("1 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 2;
	console::log("2 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 3;
	console::log("3 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 4;
	console::log("4 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 5;
	console::log("5 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 6;
	console::log("6 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 7;
	console::log("7 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 8;
	console::log("8 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 9;
	console::log("9 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 10;
	console::log("10 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 11;
	console::log("11 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 12;
	console::log("12 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 13;
	console::log("13 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 14;
	console::log("14 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 15;
	console::log("15 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 16;
	console::log("16 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 17;
	console::log("17 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 18;
	console::log("18 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 19;
	console::log("19 \n");
	Sleep(200);
	*(int*)(engine.GameModule() + dwForceAttack) = 20;
	console::log("20 \n");
	Sleep(200);
}
void localPlayer_StopAttack()
{
	Engine engine;
	*(int*)(engine.GameModule() + dwForceAttack) = 4;
}
void localPlayer_SetViewAngles(Vector3 Input)
{
	Engine engine;
	
}

static int64_t eptime = std::chrono::duration_cast<std::chrono::seconds>(std::chrono::system_clock::now().time_since_epoch()).count();

void menu::render() {
	
	if (timerr == 1)
	{
		interfaces::console->console_printf("      Thanks for Using my cheat \n      (Who . . . . Cares?#6969)\n");
		interfaces::console->console_printf("      Have Fun! :D\n");
		timerr++;
	}

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
		int CrosshairId = localPlayer_CrosshairID();
		int LocalTeam = localPlayer_GetTeam();
		int LocalHealth = localPlayer_GetHealt();
		
		if (CrosshairId > 0 && CrosshairId < 64)
		{
			DWORD Entity = entity.Get(CrosshairId - 1);
			int EntityTeam = entity.GetTeam(Entity);
			int EntityHealth = entity.GetHealth(Entity);

			if (EntityTeam != LocalTeam)
			{
				if (EntityHealth > 0)
				{
					if (LocalHealth > 0)
					{
						Sleep(variables::delay_trigger_bot);
						mouse_event(MOUSEEVENTF_LEFTDOWN, 0, 0, 0, 0);
						Sleep(10);
						mouse_event(MOUSEEVENTF_LEFTUP, 0, 0, 0, 0);
					}
				}
			}
		}
	}
	else if (variables::Trigger_Bot == false)
	{
		if (variables::triggerbot_first_time == false)
		{
			console::log("[-] TriggerBot off \n");
			variables::triggerbot_first_time = !variables::triggerbot_first_time;
		}
	}
	if (variables::Fov == true)
	{
		if (variables::Fov_first_time)
		{
			console::log("[+] Fov Changer on \n");
			variables::Fov_first_time = !variables::Fov_first_time;
		}
		Engine engine;
		DWORD localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);
		if (localplayer == NULL)
		{
			localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);
		}
		if (localplayer != NULL)
		{
			*(int*)(localplayer + m_iFOVStart) = variables::fov_int;
			*(int*)(localplayer + m_iFOV) = variables::fov_int;
		}
	}
	else if(variables::Fov == false)
	{
		if (variables::Fov_first_time == false)
		{
			console::log("[-] Fov Changer off \n");
			variables::Fov_first_time = !variables::Fov_first_time;
		}
		Engine engine;
		DWORD localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);
		if (localplayer == NULL)
			localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);

		if (localplayer != NULL)
			*(int*)(localplayer + m_iFOV) = 90;
	}
	if (variables::anti_flashbang)
	{
		if (variables::anti_flash_first_time == true)
		{
			console::log("[+] Anti Flashbang on \n");
			variables::anti_flash_first_time = !variables::anti_flash_first_time;
		}
		Engine engine;
		DWORD localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);
		if (localplayer == NULL)
			localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);

		if (localplayer != NULL)
			*(float*)(localPlayer_Get() + m_flFlashMaxAlpha) = variables::delta;
	}
	else if (variables::anti_flashbang == false)
	{
		if (variables::anti_flash_first_time == false)
		{
			console::log("[-] Anti Flashbang off \n");
			variables::anti_flash_first_time = !variables::anti_flash_first_time;
		}
	}
	if (variables::third_person || GetAsyncKeyState('X'))
	{
		if (variables::third_person_first_time == true)
		{
			console::log("[+] Third Person on \n");
			variables::third_person_first_time = !variables::third_person_first_time;
		}
		Engine engine;
		DWORD localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);
		if (localplayer == NULL)
			localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);

		if (localplayer != NULL)
			*(int*)(localplayer + m_iObserverMode) = 1;
	}
	else if (variables::third_person == false)
	{
		if (variables::third_person_first_time == false)
		{
			console::log("[-] Third Person off \n");
			variables::third_person_first_time = !variables::third_person_first_time;
		}
		Engine engine;
		DWORD localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);
		if (localplayer == NULL)
			localplayer = *(DWORD*)(engine.GameModule() + dwLocalPlayer);

		if (localplayer != NULL)
			*(int*)(localplayer + m_iObserverMode) = 0;
	}
	if (variables::bhop)
	{
		if (variables::bhop_first_time)
		{
			console::log("[+] Bhop on \n");
			variables::bhop_first_time = !variables::bhop_first_time;
		}
	}
	else if (variables::bhop == false)
	{
		if (variables::bhop_first_time == false)
		{
			console::log("[-] Bhop off \n");
			variables::bhop_first_time = !variables::bhop_first_time;
		}
	}

	if (!variables::menu::opened)
		return;

	do_frame(variables::menu::x, variables::menu::y, variables::menu::w, variables::menu::h, color(36, 36, 36, 255), color(25, 25, 25, 255), color(36, 36, 36, 255), "Who . . . . Cares?#6969");
	
	menu_framework::group_box(variables::menu::x + 5, variables::menu::y + 35, 100, 260, render::fonts::watermark_font, "tabs", false); {
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + (260 / 2) - 35, 100, 30, render::fonts::watermark_font, "aimbot", menu::current_tab, 0, false);
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + (260 / 2), 100, 30, render::fonts::watermark_font, "visuals", menu::current_tab, 1, false);
		menu_framework::tab(variables::menu::x + 5, variables::menu::y + (260 / 2) + 35, 100, 30, render::fonts::watermark_font, "misc", menu::current_tab, 2, false);
	}

	switch (current_tab) {
	case 0:
		if (case_0 == true)
		{
			console::log("[::] Aimbot tab\n");
			case_0 = false;
			case_1 = true;
			case_2 = true;
		}
		menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::watermark_font, "Legit", false); {
			menu_framework::check_box(variables::menu::x + 120, variables::menu::y + 45, variables::menu::x + 375, render::fonts::watermark_font, "TriggerBot", variables::Trigger_Bot);
			menu_framework::sliderint(variables::menu::x + 120, variables::menu::y + 60, 125, render::fonts::watermark_font, "Delay (ms)", variables::delay_trigger_bot, 0, 101);
		}
		break;
	case 1:
		if (case_1 == true)
		{
			console::log("[::] Visuals tab\n");
			case_0 = true;
			case_1 = false;
			case_2 = true;
		}
		menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::watermark_font, "visuals", false); {
			menu_framework::check_box(variables::menu::x + 120, variables::menu::y + 45, variables::menu::x + 375, render::fonts::watermark_font, "Glow", variables::glow);
		}
		break;
	case 2:
		if( case_2 == true)
		{
			console::log("[::] Misc tab\n");
			case_0 = true;
			case_1 = true;
			case_2 = false;
		}
		menu_framework::group_box(variables::menu::x + 110, variables::menu::y + 35, 285, 260, render::fonts::watermark_font, "misc", false); {
			menu_framework::check_box(variables::menu::x + 120, variables::menu::y + 45, variables::menu::x + 375, render::fonts::watermark_font, "Bhop", variables::bhop);
			menu_framework::check_box(variables::menu::x + 120, variables::menu::y + 65, variables::menu::x + 375, render::fonts::watermark_font, "Fov", variables::Fov);
			menu_framework::check_box(variables::menu::x + 120, variables::menu::y + 85, variables::menu::x + 375, render::fonts::watermark_font, "Anti Flashbang", variables::anti_flashbang);
			menu_framework::check_box(variables::menu::x + 120, variables::menu::y + 105, variables::menu::x + 375, render::fonts::watermark_font, "Third Person", variables::third_person);
			if (variables::Fov == true)
			{
				menu_framework::sliderint(variables::menu::x + 120, variables::menu::y + 125, 100, render::fonts::watermark_font, "Fov", variables::fov_int, 20, 160);
			}
			if (variables::anti_flashbang == true)
			{
				menu_framework::sliderfloat(variables::menu::x + 120, variables::menu::y + 145, 100, render::fonts::watermark_font, "Delta", variables::delta, 0.f, 255.f);
			}
		}
		break;
	}

	menu_framework::menu_movement(variables::menu::x, variables::menu::y, variables::menu::w, 30);
}

void menu::toggle() {
	if (GetAsyncKeyState(VK_INSERT) & 1)
		variables::menu::opened = !variables::menu::opened;
}
