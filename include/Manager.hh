#ifndef LIBDYT_H
#define LIBDYT_H

#include <vector>
#include <string>

#include "nlohmann/json.hpp"

#include "Action.hh"
#include "Section.hh"
#include "Settings.hh"

namespace dyt
{

	class DoYourThing
	{
	private:
		Settings _settings;
		std::string _machine_name;
		nlohmann::json _config;
		nlohmann::json _defaults;
		std::vector<Section> _sections;

		void setup();
		void setup_repos(const nlohmann::json &section);
		void setup_managers(const nlohmann::json &section);

		std::vector<Action> get_actions(const nlohmann::json &section);

	public:
		DoYourThing(const std::string &path_to_config, const Settings &settings = {{{Settings::SettingName::Quiet, Settings::SettingOption::n}}});
		DoYourThing(const char *path_to_config, const Settings &settings = {{{Settings::SettingName::Quiet, Settings::SettingOption::n}}});
		~DoYourThing();

		void print_config();
		void print_defaults();

		void do_it(); // That's what Sidious said...

		void theend();
	};

} // namespace dyt

#endif // LIBDYT_H