#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include <iostream>


class CameraController : public Component
{
	Vector3 mousePos;
	Vector3 mousePosPrev;
	Object * parent;
	Object * child;
	bool isInitialized  = false;

public:
	CameraController()
	{
		parent = new Object();

		/*child = new Object();

		child->m_pTransform = new Transform(); //!*/
		mousePos		= Vector3::Zero();
		mousePosPrev	= Vector3::Zero();
	}

	virtual ~CameraController() {}

	virtual void Update() 
	{
		Transform * pTransform = m_pObject->m_pTransform;


		if (!isInitialized)
		{
			Vector3 pos = pTransform->GetPosition();
			std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
			parent->m_pTransform = new Transform(pos, pTransform->GetEulerAngles());
			pos = parent->m_pTransform->GetPosition();
			std::cout << pos.x << " " << pos.y << " " << pos.z << std::endl;
			pTransform->SetLocalPosition(Vector3(0, 0, 0));
			pTransform->SetParent(parent->m_pTransform);
			isInitialized = true;
		}
		
		Transform * parentTransform = parent->m_pTransform;
		/*Transform * childTransform = child->m_pTransform;
		childTransform*/
		
		
		// Camera Translation
		{
			Vector3 forward	= pTransform->GetForward();
			Vector3 right	= pTransform->GetRight();
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

			parentTransform->Translate( speed * dt * direction );
		}

		// Camera Rotation
		mousePos = Input::GetMousePosition();
		if (mousePosPrev.x != 0 || mousePosPrev.y != 0)
		{
			Vector3 angles = pTransform->GetEulerAngles();
			double x = mousePos.x;
			double y = mousePos.y;
			// TODO : Task08
			//parent???
			/*Matrix4x4 rotX = Matrix4x4::RotationX(mousePosPrev.y - y); //нормировать
			Matrix4x4 rotY = Matrix4x4::RotationY(-(mousePosPrev.x - x));
			Matrix4x4 rot = rotX * rotY;*/


			parentTransform->Rotate(0, -(mousePosPrev.x - x), 0);


			int angle = (int)abs(angles.y) % 360;
			//std::cout << angles.x - (mousePosPrev.y - y) << std::endl;

			//в зависимости от горизонтального поворота делать разный y (
			//if (abs(angles.x - (mousePosPrev.y - y)) <= 90)
				if (angle < 90 || angle >= 270)
				{
					//std::cout << "CASE 1" << std::endl;
					pTransform->Rotate(-(mousePosPrev.y - y), 0, 0);
				}
				else
				{
					//std::cout << "CASE 2" << std::endl;
					pTransform->Rotate((mousePosPrev.y - y), 0, 0);
				}


			//pTransform->Rotate(-(mousePosPrev.y - y), -(mousePosPrev.x - x), 0);

		}
		mousePosPrev = mousePos;
	}
};
