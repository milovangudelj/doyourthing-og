/**
 * @file Colors.h
 * @author Milovan Gudelj
 * @brief Colors to organise and improve output legibility
 * @date 2022-12-01
 */

#ifndef COLORS_H
#define COLORS_H

#include <fmt/core.h>

namespace dyt
{

	/// Singleton struct containing terminal control codes and colors
	struct Colors
	{
	private:
		static Colors instance;

		Colors(){};
		Colors(const Colors &source) = delete;
		Colors(Colors &&source) = delete;

	public:
		static Colors &Get()
		{
			return instance;
		}

		const char *ERASE_L = "\033[2K";
		const char *ERASE_E = "\033[J";

		const char *RESET = "\033[0m";
		const char *BRIGHT = "\033[1m";
		const char *DIM = "\033[2m";
		const char *UNDERSCORE = "\033[4m";
		const char *BLINK = "\033[5m";
		const char *REVERSE = "\033[7m";
		const char *HIDDEN = "\033[8m";

		const char *BLACK_FG = "\033[30m";
		const char *RED_FG = "\033[31m";
		const char *GREEN_FG = "\033[32m";
		const char *YELLOW_FG = "\033[33m";
		const char *BLUE_FG = "\033[34m";
		const char *MAGENTA_FG = "\033[35m";
		const char *CYAN_FG = "\033[36m";
		const char *WHITE_FG = "\033[37m";

		const char *BLACK_BG = "\033[40m";
		const char *RED_BG = "\033[41m";
		const char *GREEN_BG = "\033[42m";
		const char *YELLOW_BG = "\033[43m";
		const char *BLUE_BG = "\033[44m";
		const char *MAGENTA_BG = "\033[45m";
		const char *CYAN_BG = "\033[46m";
		const char *WHITE_BG = "\033[47m";

		auto paint(auto text, auto color)
		{
			return fmt::format("{}{}{}", color, text, RESET);
		}
	};

} // namespace dyt

#endif // COLORS_H