#pragma once

using ul = unsigned long;

class Settings : public Singleton<Settings>
{
public:
    static void LoadSettings() noexcept;

    inline static bool debug_logging{};

    inline static std::map<ul, std::vector<std::string>> notifications{};

    inline static ul notification_delay{};
};
