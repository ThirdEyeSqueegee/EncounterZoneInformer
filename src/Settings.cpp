#include "Settings.h"

void Settings::LoadSettings() noexcept
{
    logger::info("Loading settings");

    CSimpleIniA ini;

    ini.SetUnicode();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\EncounterZoneInformer.ini)");

    debug_logging = ini.GetBoolValue("Log", "Debug");

    if (debug_logging) {
        spdlog::set_level(spdlog::level::debug);
        logger::debug("Debug logging enabled");
    }

    notification_color       = ini.GetValue("General", "sNotificationColor");
    notification_delay       = ini.GetLongValue("General", "uNotificationDelay");
    level_gap                = ini.GetLongValue("General", "uLevelGap");
    always_show_notification = ini.GetBoolValue("General", "bAlwaysShowNotification");

    logger::info("Loaded settings");
    logger::info("\tsNotificationColor = {}", notification_color);
    logger::info("\tuNotificationDelay = {}", notification_delay);
    logger::info("\tuLevelGap = {}", level_gap);
    logger::info("\tbAlwaysShowNotification = {}", always_show_notification);
    logger::info("");
}
