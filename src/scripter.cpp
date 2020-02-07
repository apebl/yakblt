#include "scripter.hpp"
#include "config.hpp"
#include "utils.hpp"
#include "globals.hpp"
#include "app.hpp"
#include <algorithm>

namespace {
	long secondsToFrames (float seconds) {
		return static_cast<long>(seconds * FRAMERATE);
	}
}

namespace yakblt {
	/* class Scripter */

	Scripter::Action::Action () {
	}

	Scripter::Action::~Action () {
	}

	Scripter::WaitAction::WaitAction (long waitFrames) :
		waitFrames(waitFrames)
	{
	}

	Scripter::ActionType Scripter::WaitAction::getType () const {
		return ActionType::WAIT;
	}

	Scripter::RunAction::RunAction (const function<void()> &run) :
		run(run)
	{
	}

	Scripter::ActionType Scripter::RunAction::getType () const {
		return ActionType::RUN;
	}

	Scripter::LoopAction::LoopAction (const function<bool()> &cond, const function<void()> &run) :
		cond(cond), run(run), actions(), ended(false)
	{
	}

	Scripter::LoopAction::~LoopAction () {
		while ( !actions.empty() ) {
			delete *actions.begin();
			actions.pop_front();
		}
	}

	Scripter::ActionType Scripter::LoopAction::getType () const {
		return ActionType::LOOP;
	}

	Scripter::Scripter () :
			_container(nullptr),
			_actions(),
			_targetActions(&_actions),
			_stack()
	{
	}

	Scripter::~Scripter () {
		while ( !_actions.empty() ) {
			delete *_actions.begin();
			_actions.pop_front();
		}
	}

	ScripterContainer *Scripter::getContainer () {
		return _container;
	}

	void Scripter::setContainer (ScripterContainer &container) {
		_container = &container;
	}

	bool Scripter::update () {
		while (true) {
			while ( _targetActions->empty() ) {
				if ( _stack.empty() ) return false;
				_stack.pop();
				if ( _stack.empty() ) {
					_targetActions = &_actions;
				} else {
					_targetActions = _stack.top();
				}
			}

			Action *action = *_targetActions->begin();
			switch ( action->getType() ) {
			case ActionType::WAIT: {
				WaitAction *wait = static_cast<WaitAction*>(action);
				wait->waitFrames--;
				if (wait->waitFrames >= 0) return true;
				_targetActions->pop_front();
				delete action;
				break;
			}
			case ActionType::RUN:
				static_cast<RunAction*>(action)->run();
				_targetActions->pop_front();
				delete action;
				break;
			case ActionType::LOOP: {
				LoopAction *loop = static_cast<LoopAction*>(action);
				if (loop->ended) {
					_targetActions->pop_front();
					delete loop;
					break;
				}
				RunAction *loopRun = new RunAction([loop] {
					if ( loop->cond() ) {
						loop->run();
					} else {
						loop->ended = true;
					}
				});
				_stack.push( &(loop->actions) );
				_targetActions = &(loop->actions);
				_targetActions->push_back(loopRun);
				break;
			}
			default:
				ASSERT_NOT_REACHED
			}
		}
		return true;
	}

	void Scripter::wait (float seconds) {
		long frames = secondsToFrames(seconds);
		WaitAction *action = new WaitAction(frames);
		_targetActions->push_back(action);
	}

	void Scripter::run (const function<void()> &func) {
		RunAction *action = new RunAction(func);
		_targetActions->push_back(action);
	}

	void Scripter::loop (const function<bool()> &cond, const function<void()> &func) {
		LoopAction *action = new LoopAction(cond, func);
		_targetActions->push_back(action);
	}

	void Scripter::createBullet (const string name, float x, float y, float rot, bool avoidPlayer) {
		run([name, x, y, rot, avoidPlayer] {
			Bullet *entity = app().bulletFac().get(name);
			ASSERT(entity != nullptr)
			entity->setPosition(x, y);
			entity->setRotation(rot);
			app().world().addBullet(*entity);
			if (avoidPlayer) {
				Player *player = app().world().getPlayer();
				if (player == nullptr) return;
				const Collidable &playerCollid = player->getCollidable();
				entity->updateSelfTransforms();
				const Collidable &collid = entity->getCollidable();
				if ( playerCollid.collideWith(collid) ) {
					app().world().removeBullet(*entity);
				}
			}
		});
	}

	void Scripter::createBullet (const string name, const Node &loc, bool avoidPlayer) {
		run([name, &loc, avoidPlayer] {
			Bullet *entity = app().bulletFac().get(name);
			ASSERT(entity != nullptr)
			entity->setPosition(loc.getPosition());
			entity->setRotation(loc.getRotation());
			app().world().addBullet(*entity);
			if (avoidPlayer) {
				Player *player = app().world().getPlayer();
				if (player == nullptr) return;
				const Collidable &playerCollid = player->getCollidable();
				entity->updateSelfTransforms();
				const Collidable &collid = entity->getCollidable();
				if ( playerCollid.collideWith(collid) ) {
					app().world().removeBullet(*entity);
				}
			}
		});
	}

	void Scripter::createUnit (const string name, float x, float y, float rot) {
		run([name, x, y, rot] {
			Unit *entity = app().unitFac().get(name);
			ASSERT(entity != nullptr)
			entity->setPosition(x, y);
			entity->setRotation(rot);
			app().world().addUnit(*entity);
		});
	}

	/* class ScripterContainer */

	ScripterContainer::ScripterContainer () :
		_scripters(), _deletes()
	{
	}

	ScripterContainer::~ScripterContainer () {
		for (const auto scripter : _scripters) {
			delete scripter;
		}
		for (const auto item : _deletes) {
			delete item;
		}
	}

	vector<Scripter*> &ScripterContainer::scripters () {
		return _scripters;
	}

	void ScripterContainer::addScripter (Scripter &scripter) {
		ASSERT( find(_scripters.begin(), _scripters.end(), &scripter) == _scripters.end() );
		_scripters.push_back(&scripter);
		scripter.setContainer(*this);
		scripter.init();
	}

	void ScripterContainer::deleteScripter (const Scripter &scripter) {
		vector<Scripter*>::iterator iter = find(_scripters.begin(), _scripters.end(), &scripter);
		if (iter == _scripters.end()) return;
		_scripters.erase(iter);
		_deletes.push_back(&scripter);
	}

	void ScripterContainer::clearScripters () {
		for (auto scripter : _scripters) {
			delete scripter;
		}
		_scripters.clear();
	}

	void ScripterContainer::updateScripters () {
		vector<Scripter*> copy = _scripters;
		for (const auto scripter : copy) {
			if ( !scripter->update() ) {
				deleteScripter(*scripter);
			}
		}
		for (const auto item : _deletes) {
			delete item;
		}
		_deletes.clear();
	}
}
