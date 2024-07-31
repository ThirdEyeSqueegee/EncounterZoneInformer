#include "Settings.h"

void Settings::LoadSettings() noexcept
{
    logger::info("Loading settings");

    CSimpleIniA ini;

    ini.SetUnicode();
    ini.SetMultiKey();
    ini.LoadFile(R"(.\Data\SKSE\Plugins\EncounterZoneInformer.ini)");

    debug_logging = ini.GetBoolValue("Log", "Debug");

    if (debug_logging) {
        spdlog::set_level(spdlog::level::debug);
        logger::debug("Debug logging enabled");
    }

    CSimpleIniA::TNamesDepend sections{};
    ini.GetAllSections(sections);

    for (const auto& s : sections) {
        if (!std::string_view(s.pItem).contains("LevelGap"sv)) {
            continue;
        }
        logger::debug("Parsing section {}", s.pItem);

        CSimpleIniA::TNamesDepend values{};
        ini.GetAllValues(s.pItem, "sNotification", values);
        logger::debug("Got {} values for section {}", values.size(), s.pItem);

        const auto gap{ std::stoul(std::string(s.pItem).substr(8)) };
        logger::debug("Gap for section {} is {}", s.pItem, gap);

        for (const auto& v : values) {
            notifications[gap].emplace_back(v.pItem);
        }
    }

    notification_delay = static_cast<std::uint8_t>(ini.GetLongValue("General", "uNotificationDelay"));

    logger::info("Loaded settings");
    logger::info("\tuNotificationDelay = {} s", notification_delay);
    for (const auto& [gap, notifs] : notifications) {
        logger::info("\tLevel gap = {}", gap);
        for (const auto& n : notifs) {
            logger::info("\t\tNotification = {}", n);
        }
    }
    logger::info("");
}
