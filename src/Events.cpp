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
                if (const auto ez{ a_event->cell->extraList.GetEncounterZone() }) {
                    const auto player_level{ player->GetLevel() };
                    const auto min_level{ ez->data.minLevel };
                    const auto level_diff{ ez->data.minLevel - player_level };
                    logger::debug("\tMin. level: {}, player level: {}, difference: {}", min_level, player_level, level_diff);
                    if (Settings::always_show_notification || level_diff >= Settings::level_gap) {
                        std::jthread([=] {
                            std::this_thread::sleep_for(std::chrono::seconds(Settings::notification_delay));
                            SKSE::GetTaskInterface()->AddTask([=] {
                                RE::DebugNotification(fmt::format("<font color='#{}'>WARNING:</font> {} is a <font color='#{}'>level {}</font> zone", Settings::notification_color,
                                                                  cell_name, Settings::notification_color, min_level)
                                                          .c_str());
                            });
                        }).detach();
                    }
                }
            }
        }

        return RE::BSEventNotifyControl::kContinue;
    }
} // namespace Events
