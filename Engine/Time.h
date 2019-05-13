#pragma once
#include <chrono>

class Time final {

	friend class Engine;

public:
	Time(const Time& other) = delete;
	Time(Time&& other) noexcept = delete;
	Time& operator=(const Time& other) = delete;
	Time& operator=(Time&& other) noexcept = delete;

	float GetDeltaT() const;
	float GetFPS() const;

private:
	// time scale
	// frame count (nr of render passes)
	float m_DeltaT;
	float m_FPS;

	Time() = default;
	~Time() = default;
};
