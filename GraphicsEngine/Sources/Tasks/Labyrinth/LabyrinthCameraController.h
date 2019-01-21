#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include "Tasks/Labyrinth/Labyrinth.h"
#include "Tasks/Labyrinth/YouWonText.h"

#include <iostream>

#define epsilon 0.15

class LabyrinthCameraController : public Component
{

	Vector3 mousePos;
	Vector3 mousePosPrev;
	Object * parent;
	bool isInitialized = false;
	Block ** labyrinth;
	unsigned int blockSize;
	YouWonText * ywt = NULL;


public:
	LabyrinthCameraController(Labyrinth labyrinth, unsigned int blockSize, YouWonText * ywt)
	{
		this->labyrinth = labyrinth.getField();
		this->blockSize = blockSize;
		parent = new Object();
		//parent->m_pMesh = new MeshSphere(20);

		mousePos = Vector3::Zero();
		mousePosPrev = Vector3::Zero();
		this->ywt = ywt;
	}

	virtual ~LabyrinthCameraController() {}

	virtual void Update()
	{
		Transform * pTransform = m_pObject->m_pTransform;

		if (!isInitialized)
		{
			Vector3 pos = pTransform->GetPosition();

			parent->m_pTransform = new Transform(pos, pTransform->GetEulerAngles());
			//parent->m_pTransform = new Transform(Vector3(pos.x, pos.y - 0.5, pos.z), pTransform->GetEulerAngles(), Vector3(0.3, 0.3, 0.3));

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
			double speed = 1.0; //1.0!
			Vector3 direction;

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

			//отображаем на плоскость, но не перпендикулярно, а с сохранением длины
			double x = direction.x;
			double z = direction.z;
			double L = direction.Length();
			double l = x * x + z * z;
			double a = (l != 0) ? L / sqrt(l) : 0;
			direction = Vector3(x * a, 0, z * a);
			Vector3 pos = parentTransform->GetPosition();

			//if((pos.x >= 1 || x > 0) && (pos.z >= 1 || z > 0)) //или нужны для того, чтобы можно было сдвинуться, если застрял
			/*if (pos.x <= 1 + epsilon && x <= 0)
			{
				direction.x = 0;
			}
			if (pos.z <= 1 + epsilon && z <= 0)
			{
				direction.z = 0;
			}*/

			//floor(pos.x), floor(pos.z) - это в точности (теперь, после сдвига) тот элемент массива, в котором мы находимся!
			int i = floor(pos.x);
			int j = floor(pos.z);

			//коллизии
			if ((labyrinth[i][j] == FLOOR || labyrinth[i][j] == FINISHPOINT) &&
				((labyrinth[i - 1][j] == WALL || labyrinth[i - 1][j] == FINISHWALL) && pos.x <= i + epsilon && x <= 0)
				||
				((labyrinth[i + 1][j] == WALL || labyrinth[i + 1][j] == FINISHWALL) && pos.x - 1 >= i - epsilon && x >= 0)
			)
			{
				direction.x = 0;
			}
			if ((labyrinth[i][j] == FLOOR || labyrinth[i][j] == FINISHPOINT) &&
				(( ( labyrinth[i][j - 1] == WALL || labyrinth[i][j - 1] == FINISHWALL ) && pos.z <= j + epsilon && z <= 0)
				||
				((labyrinth[i][j + 1] == WALL || labyrinth[i][j + 1] == FINISHWALL) && pos.z - 1 >= j - epsilon && z >= 0)
			)
			)
			{
				direction.z = 0;
			}
			/*if ((labyrinth[i][j] == FLOOR || labyrinth[i][j] == FINISHPOINT) &&
				(((labyrinth[i - 1][j - 1] == WALL || labyrinth[i - 1][j - 1] == FINISHWALL) && pos.z <= j + epsilon && z <= 0 && pos.x <= i + epsilon && x <= 0)
					||
				((labyrinth[i - 1][j + 1] == WALL || labyrinth[i - 1][j + 1] == FINISHWALL) && pos.z - 1 >= j - epsilon && z >= 0 && pos.x <= i + epsilon && x <= 0)
					)
				)
			{
				direction.x = 0;
				direction.z = 0;
			}*/

			if (labyrinth[i][j] == FINISHPOINT) //&& и если близко к шарику
			{
				//set flag variable
				ywt->setWon(true);
			}

			if (Input::GetKey(KEY_CODE_LEFT_SHIFT))
			{
				speed = 2;
			}
			else
			{
				speed = 1;
			}


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

			//в зависимости от горизонтального поворота делать разный y
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
