#include "event.hpp"

namespace yakblt {
	template <typename... A>
	Event<A...>::Event () : _next(0), _handlers() {
	}

	template <typename... A>
	int Event<A...>::addHandler (const function<void(A...)> &handler) {
		_handlers.emplace(_next++, handler);
		return _next;
	}

	template <typename... A>
	void Event<A...>::removeHandler (int id) {
		_handlers.erase(id);
		if (_handlers.empty()) {
			_next = 0;
		}
	}

	template <typename... A>
	void Event<A...>::clearHandlers () {
		_handlers.clear();
		_next = 0;
	}

	template <typename... A>
	void Event<A...>::fireEvent (A... args) {
		for (const auto &pair : _handlers) {
			pair.second(args...);
		}
	}
}
