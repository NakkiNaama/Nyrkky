#pragma once
#include <iostream>
#include <GLFW/glfw3.h>

class Timer
{
public:

	inline void Update()
	{
		double lastTime = glfwGetTime();
	}

	float GetDeltaTime() {
		double currentTime = glfwGetTime();
		float deltaTime = static_cast<float>(currentTime - lastTime);
		lastTime = currentTime;
		return deltaTime;
	}

private:
	double lastTime;


};

