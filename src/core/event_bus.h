//
// Created by Mateusz Palkowski on 02/11/2022.
//

#ifndef MINECPPRAFT_CORE_EVENT_BUS_H
#define MINECPPRAFT_CORE_EVENT_BUS_H

#include <functional>
#include <queue>
#include <set>
#include <unordered_map>


#include "core/event.h"


// mouse event should have IsInsideWindow and current mode (normal, hidden)
// should event's that nobody subscribes to be published?

namespace prototype {
class EventBus {
 public:
  EventBus();

  using EventCallback = std::function<void(Event)>;
  void Publish(Event e);
  long Subscribe(Event::Type t, EventCallback cb);
  void Unsubscribe(long id);

  void Dispatch();

  static EventBus& Get();

 private:
  void RemoveSubscribers();

  static EventBus* s_event_bus_;

  long current_id_ = 0;
  struct SubscriberInfo {
    long id = -1;
    EventCallback cb;
  };

  std::unordered_multimap<Event::Type, SubscriberInfo> type_to_subscriber_;
  std::queue<Event> undispatched_events_;

  std::set<long> ids_to_remove_;

};
}  // namespace prototype

#endif  // MINECPPRAFT_CORE_EVENT_BUS_H
