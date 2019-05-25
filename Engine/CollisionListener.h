#pragma once

namespace meow {

	class CollisionListener {

		virtual void OnTriggerEnter() {}
		virtual void OnTriggerExit() {}
		virtual void OnCollision() {}
	};
}