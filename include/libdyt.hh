#ifndef LIBDYT_H
#define LIBDYT_H

#include <vector>
#include <string>

#include "nlohmann/json.hpp"

#include "Action.hh"
#include "Section.hh"

namespace dyt
{

	class DoYourThing
	{
	private:
		nlohmann::json _config;
		std::vector<Section> _sections;

		void setup();

	public:
		DoYourThing(const std::string &path_to_config);
		DoYourThing(const char *path_to_config);
		~DoYourThing();

		void print_config();
		void do_it(); // That's what Sidious said...
		void theend();
	};

} // namespace dyt

#endif // LIBDYT_H