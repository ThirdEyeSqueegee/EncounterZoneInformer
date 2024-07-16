#pragma once

class Settings : public Singleton<Settings>
{
public:
    static void LoadSettings() noexcept;

    inline static bool debug_logging{};

    inline static std::string notification_color{};

    inline static std::uint8_t notification_delay{};

    inline static std::uint8_t level_gap{};

    inline static bool always_show_notification{};
};
