#pragma once

namespace Events
{
    class CellFullyLoadedEventHandler : public EventSingleton<CellFullyLoadedEventHandler, RE::TESCellFullyLoadedEvent>
    {
    private:
        inline static std::random_device rd{};

    public:
        inline static std::string notif{};

        inline static std::mt19937 gen{ rd() };

        inline static std::string fallback_notification{ "<font color='#ff5555'>WARNING:</font> {loc} is a <font color='#ff5555'>level {lvl}</font> zone" };

        RE::BSEventNotifyControl ProcessEvent(const RE::TESCellFullyLoadedEvent* a_event, RE::BSTEventSource<RE::TESCellFullyLoadedEvent>* a_eventSource) noexcept override;
    };
} // namespace Events
