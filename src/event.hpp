#ifndef __BLT_EVENT_H__
#define __BLT_EVENT_H__

#include <unordered_map>
#include <functional>

using namespace std;

namespace blt {
	template <typename... A>
	class Event {
	public:
		Event ();
		/**
		 * Adds the given handler to this event.
		 *
		 * @param[in] handler The handler to be added
		 * @return The identifier of the added handler
		 */
		int addHandler (const function<void(A...)> &handler);
		void removeHandler (int id);
		void clearHandlers ();
		void fireEvent (A... args);

	private:
		int _next;
		unordered_multimap<int, const function<void(A...)>> _handlers;
	};
}

#include "event.tpp"

#endif
