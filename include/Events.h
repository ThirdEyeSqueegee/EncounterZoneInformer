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

        RE::BSEventNotifyControl ProcessEvent(const RE::TESCellFullyLoadedEvent* a_event, RE::BSTEventSource<RE::TESCellFullyLoadedEvent>* a_eventSource) noexcept override;
    };
} // namespace Events
