#pragma once

namespace variables {
	inline bool Trigger_Bot = false;
	inline int delay_trigger_bot = 0;
	inline float delta = 50.f;
	inline int fov_int = 120;
	inline bool bhop = false;
	inline bool Fov = false;
	inline bool third_person = false;
	inline bool anti_flashbang = false;
	inline bool glow = false;

	// timer's
	inline bool Fov_first_time = true;
	inline bool bhop_first_time = true;
	inline bool anti_flash_first_time = true;
	inline bool third_person_first_time = true;
	inline bool triggerbot_first_time = true;

	namespace menu {
		inline bool opened = false;
		inline int x = 140, y = 140;
		inline int w = 400, h = 300;
	}

	namespace watermark {
		inline int x = 10, y = 10;
		inline int w = 300, h = 10;
	}
}