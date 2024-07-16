#pragma once

namespace Events
{
    class CellFullyLoadedEventHandler : public EventSingleton<CellFullyLoadedEventHandler, RE::TESCellFullyLoadedEvent>
    {
    public:
        RE::BSEventNotifyControl ProcessEvent(const RE::TESCellFullyLoadedEvent* a_event, RE::BSTEventSource<RE::TESCellFullyLoadedEvent>* a_eventSource) noexcept override;
    };
} // namespace Events
