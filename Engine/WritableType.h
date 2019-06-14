#pragma once
#include <string>

namespace meow {

	class WritableType {

	public:
		virtual ~WritableType() = default;

		virtual std::string ToString() const = 0;
		virtual void ParseFromString(const std::string& s) = 0;
	};
}