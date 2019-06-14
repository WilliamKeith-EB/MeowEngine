#pragma once

namespace meow {

	class CollisionListener {

	public:
		virtual ~CollisionListener() = default;
		virtual void OnCollision() {}
	};
}