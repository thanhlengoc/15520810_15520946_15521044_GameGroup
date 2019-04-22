#include "GameConfiguration.h"

/* Khi đặt static member phải khởi tạo như vậy */
map<const char*, double>* GameConfiguration::globalsConfigurationDouble = 0;
map<const char*, const char*>* GameConfiguration::globalsConfigurationString = 0;


/* Lấy 1 thống số ra từ 1 key cho trước */
double GameConfiguration::GetConfiguration(const char * key)
{
	/* Hướng dẫn: Đọc singleton pattern để hiểu cách viết này */
	if (globalsConfigurationDouble == 0)
	{
		globalsConfigurationDouble = new map<const char*, double>();

		/* window_width, window_height là kích thước cửa sổ */
		globalsConfigurationDouble->insert(pair<const char*, double>("window_width", 600));
		globalsConfigurationDouble->insert(pair<const char*, double>("window_height", 500));

		/* backbuffer_width, backbuffer_height là kích thước của backbuffer */
		globalsConfigurationDouble->insert(pair<const char*, double>("backbuffer_width", 250));
		globalsConfigurationDouble->insert(pair<const char*, double>("backbuffer_height", 208));

		globalsConfigurationDouble->insert(pair<const char*, double>("object_animation_time_default", 60));
		globalsConfigurationDouble->insert(pair<const char*, double>("enemy_animation_time_default", 190));
		globalsConfigurationDouble->insert(pair<const char*, double>("object_default_ay", -270));

		globalsConfigurationDouble->insert(pair<const char*, double>("player_vx", 110));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_vy_jump", 170));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_vy_fall_stand", -70));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_jump_height", 23));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_sit", 19));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_height", 30));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_dead_delay", 1500));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_hit_vx", 130));
		globalsConfigurationDouble->insert(pair<const char*, double>("player_hit_vy", 100));

		globalsConfigurationDouble->insert(pair<const char*, double>("zombie_distance_to_activity", 150));
		//zombie_distance_to_activ

		/* fps là frame_per_second càng lớn càng mượt nhưng nó sử dụng nhiều cpu hơn */
		globalsConfigurationDouble->insert(pair<const char*, double>("fps", 70));

		/* TODO tạo thêm các giá trị cấu hình double game tại đây
		Ví dụ: globalsConfiguration->insert(pair<const char*, double>("gia_tri_key", 10)); 10 la gia tri cua gia_tri_key
		*/

	}
	/* trả ra giá trị cấu hình tại key */
	return globalsConfigurationDouble->at(key);
}

const char * GameConfiguration::GetConfigurationString(const char * key)
{
	/* Hướng dẫn: Đọc singleton pattern để hiểu cách viết này */
	if (globalsConfigurationString == 0)
	{
		globalsConfigurationString = new map<const char*, const char*>();

		/* Tiêu đề của cửa sổ */
		globalsConfigurationString->insert(pair<const char*, const char*>("window_title", "Game"));
		globalsConfigurationString->insert(pair<const char*, const  char*>("window_class", "win_game"));
		/* TODO tạo thêm các giá trị cấu hình string game tại đây
		Ví dụ: globalsConfiguration->insert(pair<const char*, const char*>("gia_tri_key", "value")); "value" la gia tri cua gia_tri_key
		*/

	}
	/* trả ra giá trị cấu hình tại key */
	return globalsConfigurationString->at(key);
}

GameConfiguration::GameConfiguration()
{
}

GameConfiguration::~GameConfiguration()
{
}
