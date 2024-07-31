#include "Events.h"

#include "Settings.h"

namespace Events
{
    RE::BSEventNotifyControl CellFullyLoadedEventHandler::ProcessEvent(const RE::TESCellFullyLoadedEvent*               a_event,
                                                                       RE::BSTEventSource<RE::TESCellFullyLoadedEvent>* a_eventSource) noexcept
    {
        if (!a_event) {
            return RE::BSEventNotifyControl::kContinue;
        }

        if (!a_event->cell) {
            return RE::BSEventNotifyControl::kContinue;
        }

        if (const auto player{ RE::PlayerCharacter::GetSingleton() }) {
            if (player->GetParentCell() == a_event->cell) {
                const auto cell_name{ a_event->cell->GetName() };
                logger::debug("Player is in cell {}", cell_name);

                if (const auto ez{ a_event->cell->GetRuntimeData().loadedData->encounterZone }) {
                    const auto player_level{ player->GetLevel() };
                    const auto min_level{ ez->data.minLevel };
                    const auto level_diff{ min_level - player_level };
                    logger::debug("\tMin. level: {}, player level: {}, difference: {}", min_level, player_level, level_diff);

                    auto it{ Settings::notifications.lower_bound(level_diff) };
                    if (it == Settings::notifications.end()) {
                        return RE::BSEventNotifyControl::kContinue;
                    }
                    logger::debug("Nearest level gap: {}", it->first);

                    std::vector<std::string> notifs;
                    std::ranges::sample(Settings::notifications[it->first], std::back_inserter(notifs), 1, gen);
                    notif = notifs.front();
                    logger::debug("Using notification: {}", notif);

                    if (notif.contains("{loc}"sv)) {
                        logger::debug("Replacing loc with {}", cell_name);

                        const auto pos{ notif.find("{loc}"sv) };
                        notif.replace(pos, 5, cell_name);
                        logger::debug("\tNotification: {}", notif);
                    }
                    if (notif.contains("{lvl}"sv)) {
                        logger::debug("Replacing lvl with {}", min_level);

                        const auto pos{ notif.find("{lvl}"sv) };
                        notif.replace(pos, 5, std::to_string(min_level));
                        logger::debug("\tNotification: {}", notif);
                    }

                    stl::add_thread_task([=] { RE::DebugNotification(notif.c_str()); }, std::chrono::seconds(Settings::notification_delay));
                }
            }
        }

        return RE::BSEventNotifyControl::kContinue;
    }
} // namespace Events
