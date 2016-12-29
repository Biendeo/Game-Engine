#include "ComCamera.h"

#include <iostream>

#include "../GameObject.h"
#include "../CommonMath.h"

namespace Biendeo::GameOff2016::Engine::Components {
	ComCamera::ComCamera(GameObject* gameObject) : Component(gameObject) {
		perspective = true;
		fov = 75.0f;
	}

	ComCamera::~ComCamera() {

	}

	bool ComCamera::Perspective() {
		return perspective;
	}

	bool ComCamera::Perspective(bool perspective) {
		this->perspective = perspective;
		return perspective;
	}

	float ComCamera::FOV() {
		return fov;
	}

	float ComCamera::FOV(float fov) {
		this->fov = fov;
		return fov;
	}

	void ComCamera::SetupViewCamera(int screenX, int screenY, int width, int height) {
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();

		float aspectRatio = width * 1.0f / height;
		float roughNearPlane = tan(FOV() / 2.0f * PI() / 180.0f);
		const float nearPlaneFactor = 0.1f;
		const float farPlane = 1000.0f;

		if (aspectRatio >= 1.0) {
			glFrustum(-aspectRatio * nearPlaneFactor, aspectRatio * nearPlaneFactor, -nearPlaneFactor, nearPlaneFactor, nearPlaneFactor / roughNearPlane, farPlane);
			//std::cout << -aspectRatio * nearPlaneFactor << ", " << aspectRatio * nearPlaneFactor << ", " << -nearPlaneFactor << ", " << nearPlaneFactor << ", " << nearPlaneFactor / roughNearPlane << ", " << farPlane << "\n";
			
		} else {
			glFrustum(-nearPlaneFactor, nearPlaneFactor, -nearPlaneFactor / aspectRatio, nearPlaneFactor / aspectRatio, nearPlaneFactor / roughNearPlane, farPlane);
			//std::cout << -nearPlaneFactor << ", " << nearPlaneFactor << ", " << -nearPlaneFactor / aspectRatio << ", " << nearPlaneFactor / aspectRatio << ", " << nearPlaneFactor / roughNearPlane << ", " << farPlane << "\n";
		}

		glViewport(0, 0, width, height);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		// TODO: Use the global transform rather than the local transform.
		glRotatef(-gameObject->Transform().Rotate().x, 1.0f, 0.0f, 0.0f);
		glRotatef(-gameObject->Transform().Rotate().y, 0.0f, 1.0f, 0.0f);
		glRotatef(-gameObject->Transform().Rotate().z, 0.0f, 0.0f, 1.0f);
		glTranslatef(-gameObject->Transform().Translate().x, -gameObject->Transform().Translate().y, -gameObject->Transform().Translate().z);
	}

	void ComCamera::Awake() {

	}

	void ComCamera::LateUpdate(float deltaTime) {

	}

	void ComCamera::OnActive() {

	}

	void ComCamera::OnDestroy() {

	}

	void ComCamera::OnDisable() {

	}

	void ComCamera::Start() {

	}

	void ComCamera::Update(float deltaTime) {
		
	}
}