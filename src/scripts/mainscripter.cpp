#include "mainscripter.hpp"
#include "../config.hpp"
#include "../utils.hpp"
#include "../math.hpp"
#include "basicpattern.hpp"
#include "missilepattern.hpp"
#include "minepattern.hpp"

namespace blt {
	void MainScripter::init () {
		wait(1);
		run([this] {
			getContainer()->addScripter( *new BasicPattern() );
		});
		wait(10);
		run([this] {
			getContainer()->addScripter( *new MissilePattern() );
		});
		wait(10);
		run([this] {
			getContainer()->addScripter( *new MinePattern() );
		});
	}
}