/* event.hpp
 *
 * Copyright (C) 2019-2020 Космическое П. <kosmospredanie@yandex.ru>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */

#ifndef __BLT_EVENT_H__
#define __BLT_EVENT_H__

#include <unordered_map>
#include <functional>

using namespace std;

namespace yakblt {
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
