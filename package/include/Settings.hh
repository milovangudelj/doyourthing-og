#ifndef SETTINGS_H
#define SETTINGS_H

#include <string>
#include <map>

namespace dyt
{

	class Settings
	{
	public:
		typedef enum
		{
			Quiet
		} SettingName;
		typedef enum
		{
			n,
			y
		} SettingOption;

	private:
		typedef std::map<SettingName, SettingOption> SettingsCollection;
		SettingsCollection _settings;

	public:
		Settings(const SettingsCollection &settings);
		~Settings();

		SettingOption &operator[](const SettingName &name)
		{
			return _settings[name];
		}
	};

}

#endif