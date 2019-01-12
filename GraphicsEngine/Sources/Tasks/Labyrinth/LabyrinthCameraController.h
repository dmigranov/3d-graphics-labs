#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include <iostream>


class LabyrinthCameraController : public Component
{
	Vector3 mousePos;
	Vector3 mousePosPrev;
	Object * parent;

	bool isInitialized = false;

public:
	LabyrinthCameraController()
	{
		parent = new Object();

		mousePos = Vector3::Zero();
		mousePosPrev = Vector3::Zero();
	}

	virtual ~LabyrinthCameraController() {}

	virtual void Update()
	{
		Transform * pTransform = m_pObject->m_pTransform;


		if (!isInitialized)
		{
			Vector3 pos = pTransform->GetPosition();

			parent->m_pTransform = new Transform(pos, pTransform->GetEulerAngles());
			pos = parent->m_pTransform->GetPosition();

			pTransform->SetLocalPosition(Vector3(0, 0, 0));
			pTransform->SetParent(parent->m_pTransform);
			isInitialized = true;
		}

		Transform * parentTransform = parent->m_pTransform;

		// Camera Translation
		{
			Vector3 forward = pTransform->GetForward();
			Vector3 right = pTransform->GetRight();
			double dt = Time::GetDeltaTime();

			const double speed = 1.0;
			Vector3 direction;

			//if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
			if (Input::GetKey(KEY_CODE_W) || Input::GetKey(KEY_CODE_UP_ARROW))
			{
				direction += forward;
			}
			else if (Input::GetKey(KEY_CODE_S) || Input::GetKey(KEY_CODE_DOWN_ARROW))
			{
				direction -= forward;
			}
			else if (Input::GetKey(KEY_CODE_D) || Input::GetKey(KEY_CODE_RIGHT_ARROW))
			{
				direction += right;
			}
			else if (Input::GetKey(KEY_CODE_A) || Input::GetKey(KEY_CODE_LEFT_ARROW))
			{
				direction -= right;
			}

			double x = direction.x;
			double z = direction.z;
			double L = direction.Length();
			double l = x*x + z*z;
			double a = (l!=0) ? L / sqrt(l) : 0;
			direction = Vector3(x * a, 0, z * a);
				
			parentTransform->Translate(speed * dt * direction);
		}

		// Camera Rotation
		mousePos = Input::GetMousePosition();
		if (mousePosPrev.x != 0 || mousePosPrev.y != 0)
		{
			Vector3 angles = pTransform->GetEulerAngles();
			double x = mousePos.x;
			double y = mousePos.y;

			parentTransform->Rotate(0, -(mousePosPrev.x - x), 0);


			int angle = (int)abs(angles.y) % 360;

			//в зависимости от горизонтального поворота делать разный y (
			if (abs(angles.x - (mousePosPrev.y - y)) <= 90)
				if (angle < 90 || angle >= 270)
				{
					pTransform->Rotate(-(mousePosPrev.y - y), 0, 0);
				}
				else
				{
					pTransform->Rotate((mousePosPrev.y - y), 0, 0);
				}
		}
		mousePosPrev = mousePos;
	}
};
