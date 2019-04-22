#pragma once
#include<map>
using namespace std;
/* Xem hướng dẫn: cần đọc về khái niệm define trong hướng dẫn để hiểu chỗ này */
#define GLOBALS_D(name) GameConfiguration::GetConfiguration(name)
#define GLOBALS_S(name) GameConfiguration::GetConfigurationString(name)
class GameConfiguration
{
	/* Kiểu ánh xạ từ key ra value kiểu double để sử dụng thông số cấu hình qua 1 cái key*/
	static map<const char*, double>* globalsConfigurationDouble;
	static map<const char*, const char*>* globalsConfigurationString;
public:
	/* Lấy 1 thống số double ra từ 1 key cho trước */
	static double GetConfiguration(const char* key);
	static const char* GetConfigurationString(const char* key);
	GameConfiguration();
	~GameConfiguration();
};
