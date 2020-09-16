#include "camera.h"

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 0.01f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

vec3 Position;
vec3 Front;
vec3 Up;
vec3 Right;
vec3 WorldUp;

float Yaw;
float Pitch;

float MovementSpeed;
float MouseSensitivity;
float Zoom;

void updateCameraVectors();

float fov_back()
{
	return Zoom;
}

void Camera(vec3 position, vec3 up, float yaw, float pitch) {
	printf("Init camera\n");
	MovementSpeed = SPEED;
	MouseSensitivity = SENSITIVITY;
	Zoom = ZOOM;
	glm_vec3_copy(position, Position);
	glm_vec3_copy(up, WorldUp);
	Yaw = yaw;
	Pitch = yaw;
	updateCameraVectors();
}

void GetViewMatrix(mat4 destination) {
	vec3 temp;
	glm_vec3_add(Position, Front, temp);
	glm_lookat(Position, temp, Up, destination);
}

void ProcessKeyboard(enum Camera_Movement direction, float deltaTime) {
	float velocity = MovementSpeed * deltaTime;
	vec3 velocity_vec = {velocity, velocity, velocity};
	vec3 t;

	if (direction == FORWARD) {
		//t = Front * velocity
		//Position = Position + t
		glm_vec3_mulv(Front, velocity_vec, t);
		glm_vec3_add(Position, t, Position);
	}
	if (direction == BACKWARD) {
		//t = Front * velocity
		//Position = Poisiton - t
		glm_vec3_mulv(Front, velocity_vec, t);
		glm_vec3_sub(Position, t, Position);
	}
	if (direction == LEFT) {
		//t = Right * velocity
		//Position = Position - t
		glm_vec3_mulv(Right, velocity_vec, t);
		glm_vec3_sub(Position, t, Position);
	}
	if (direction == RIGHT) {
		//t = Right * velocity
		//Position = Position + t
		glm_vec3_mulv(Right, velocity_vec, t);
		glm_vec3_add(Position, t, Position);
	}
}

void ProcessMouseMovement(float xoffset, float yoffset, GLboolean constrainPitch) {
	xoffset *= MouseSensitivity;
	yoffset *= MouseSensitivity;

	Yaw += xoffset;
	Pitch += yoffset;

	if (constrainPitch) {
		if (Pitch > 89.0f)
			Pitch = 89.0f;
		if (Pitch < -89.0f)
			Pitch = -89.0f;
	}

	updateCameraVectors();
}

void ProcessMouseScroll(float yoffset) {
	if (Zoom >= 1.0f && Zoom <= 45.0f)
		Zoom -= yoffset;
	if (Zoom <= 1.0f)
		Zoom = 1.0f;
	if (Zoom >= 45.0f)
		Zoom = 45.0f;
}

void updateCameraVectors() {
	vec3 front = { cos(glm_rad(Yaw)) * cos(glm_rad(Pitch)), sin(glm_rad(Pitch)), sin(glm_rad(Yaw)) * cos(glm_rad(Pitch)) };
	glm_vec3_normalize(front);
	glm_vec3_copy(front, Front);

	vec3 right_temp;
	vec3 up_temp;

	glm_vec3_cross(Front, WorldUp, right_temp);
	glm_vec3_normalize(right_temp);
	glm_vec3_copy(right_temp, Right);

	glm_vec3_cross(Right, Front, up_temp);
	glm_vec3_normalize(up_temp);
	glm_vec3_copy(up_temp, Up);
}