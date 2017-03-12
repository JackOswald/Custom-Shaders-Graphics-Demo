#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/transform.hpp>

struct CameraHandler
{
public:
	CameraHandler()
	{
	}

	void createCamera(const glm::vec3& position, float fov, float aspect, float nearClip, float farClip)
	{
		this->position = position;
		this->forward = glm::vec3(0.0f, 0.0f, 1.0f);
		this->up = glm::vec3(0.0f, 1.0f, 0.0f);
		this->projection = glm::perspective(fov, aspect, nearClip, farClip);
	}

	inline glm::mat4 GetViewProjection() const
	{
		return projection * glm::lookAt(position, position + forward, up);
	}

	void MoveForward(float amt)
	{
		position += forward * amt;
	}

	void MoveRight(float amt)
	{
		position += glm::cross(up, forward) * amt;
	}

protected:
private:
	glm::mat4 projection;
	glm::vec3 position;
	glm::vec3 forward;
	glm::vec3 up;
};