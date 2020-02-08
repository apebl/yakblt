/* scripter.hpp
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

#ifndef __BLT_SCRIPTER_H__
#define __BLT_SCRIPTER_H__

#include <vector>
#include <deque>
#include <stack>
#include <functional>
#include "node.hpp"

using namespace std;

namespace yakblt {
	class ScripterContainer;

	class Scripter {
	private:
		enum ActionType {
			WAIT,
			RUN,
			LOOP
		};

		class Action {
		public:
			Action ();
			virtual ~Action ();
			virtual ActionType getType () const = 0;
		};

		class WaitAction : public Action {
		public:
			WaitAction (long waitFrames);
			virtual ActionType getType () const override;
			long waitFrames;
		};

		class RunAction : public Action {
		public:
			RunAction (const function<void()> &run);
			virtual ActionType getType () const override;
			function<void()> run;
		};

		class LoopAction : public Action {
		public:
			LoopAction (const function<bool()> &cond, const function<void()> &run);
			virtual ~LoopAction () override;
			virtual ActionType getType () const override;
			function<bool()> cond;
			function<void()> run;
			deque<Action*> actions;
			bool ended;
		};

		ScripterContainer *_container;
		deque<Action*> _actions;
		deque<Action*> *_targetActions;
		stack<deque<Action*>*> _stack; // A stack storing action queues

	public:
		Scripter ();
		virtual ~Scripter ();
		/**
		 * @return The container of this scripter, or null if no container.
		 */
		ScripterContainer *getContainer ();
		/**
		 * @note This Scripter doesn't hold the ownership of the container.
		 */
		void setContainer (ScripterContainer &container);
		/**
		 * Initializes this scripter.
		 *
		 * This method will be called by a world, when the scripter is added
		 * to the world.
		 */
		virtual void init () = 0;
		/**
		 * Updates this scripter.
		 *
		 * If the scripter ends, it is removed from the container and deleted.
		 *
		 * @return false if this scripter ends, true otherwise.
		 */
		bool update ();

	protected:
		void wait (float seconds);
		void run (const function<void()> &func);
		void loop (const function<bool()> &cond, const function<void()> &func);

		/**
		 * Creates a bullet for the given name and add it to the world.
		 */
		void createBullet (const string name, float x, float y, float rot, bool avoidPlayer = false);
		/**
		 * Creates a bullet for the given name and add it to the world, with
		 * the same position and rotation as the node.
		 */
		void createBullet (const string name, const Node &node, bool avoidPlayer = false);
		void createUnit (const string name, float x, float y, float rot);
	};

	class ScripterContainer {
	public:
		ScripterContainer ();
		virtual ~ScripterContainer ();

		vector<Scripter*> &scripters ();
		/**
		 * Adds a scripter to this.
		 *
		 * Sets the container of the scripter to this and calls init() of
		 * the scripter.
		 *
		 * @note This ScripterContainer hold the ownership of the scripter.
		 *
		 * @param[in] scripter The scripter to be added
		 */
		void addScripter (Scripter &scripter);
		/**
		 * Removes the scripter from this and deletes it.
		 *
		 * @param[in] scripter The scripter to be deleted
		 */
		void deleteScripter (const Scripter &scripter);
		/**
		 * Removes and deletes all the scripters.
		 */
		void clearScripters ();
		void updateScripters ();
	private:
		vector<Scripter*> _scripters;
		vector<const Scripter*> _deletes;
	};
}

#endif
