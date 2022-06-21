#include <map>

#include "Settings.hh"

using namespace std;
using namespace dyt;

Settings::Settings(const map<SettingName, SettingOption> &settings) : _settings{settings} {};

Settings::~Settings(){};