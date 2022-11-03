//
// Created by Mateusz Palkowski on 02/11/2022.
//
#include "event_bus.h"

#include <algorithm>
#include <iostream>

namespace prototype {
EventBus* EventBus::s_event_bus_ = nullptr;

void EventBus::Publish(Event e) { undispatched_events_.push(e); }
long EventBus::Subscribe(Event::Type t, EventBus::EventCallback cb) {
  long id = current_id_;
  type_to_subscriber_.emplace(t, SubscriberInfo{current_id_, cb});
  current_id_ += 1;
  return id;
}

void EventBus::Unsubscribe(long id) { ids_to_remove_.insert(id); }
void EventBus::Dispatch() {
  RemoveSubscribers();

  if (type_to_subscriber_.empty()) {
    std::queue<Event> empty;
    std::swap(undispatched_events_, empty);
  }

  while (!undispatched_events_.empty()) {
    auto& event = undispatched_events_.front();
    auto range = type_to_subscriber_.equal_range(event.type);
    for (auto it = range.first; it != range.second; ++it) {
      if (it->second.id != -1) {
        it->second.cb(event);
      }
    }
    undispatched_events_.pop();
  }
}

void EventBus::RemoveSubscribers() {
  if (ids_to_remove_.empty()) {
    return;
  }
  auto to_remove_it = ids_to_remove_.begin();
  for (auto it = type_to_subscriber_.begin();
       it != type_to_subscriber_.end() && to_remove_it != ids_to_remove_.end();) {
    if (it->second.id == *to_remove_it) {
      it = type_to_subscriber_.erase(it);
      ++to_remove_it;
    } else {
      ++it;
    }
  }
  ids_to_remove_.clear();
}

EventBus::EventBus() {
  if (s_event_bus_ == nullptr) {
    std::cout << "Probably a mistake, there should be only one EventBus"
              << std::endl;
  }
  s_event_bus_ = this;
}

EventBus& EventBus::Get() { return *s_event_bus_; }

}  // namespace prototype
