#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/Input.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include "Tasks/Labyrinth/Labyrinth.h"

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

public:
	LabyrinthCameraController(Labyrinth labyrinth, unsigned int blockSize)
	{
		this->labyrinth = labyrinth.getField();
		this->blockSize = blockSize;
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

			//���������� �� ���������, �� �� ���������������, � � ����������� �����
			double x = direction.x;
			double z = direction.z;
			double L = direction.Length();
			double l = x * x + z * z;
			double a = (l != 0) ? L / sqrt(l) : 0;
			direction = Vector3(x * a, 0, z * a);

			Vector3 pos = parentTransform->GetPosition();
			if (L != 0)
			{
				std::cout << pos.x << " " << pos.z << std::endl;
				//std::cout << 
			}
			//if((pos.x >= 1 || x > 0) && (pos.z >= 1 || z > 0)) //��� ����� ��� ����, ����� ����� ���� ����������, ���� �������
				


			if (pos.x <= 0 + epsilon && x <= 0)
				direction.x = 0;
			if (pos.z <= 0 + epsilon && z <= 0)
				direction.z = 0;
			/*
			����� �������� ��� �Ѩ ���������� (�������, � �� ����� ��� ���� ������ � 0.5 * blockSize)!
			� ������� field ���� � ������������� 0, 0 ������� � ����� � �������
			(0, 0)			(0, blockSize)
			(blockSize, 0)	(blockSize, blockSize)	
			� ������� field ���� � ������������� i, j ������� � ����� � �������
			(i, j)				(i, j + blockSize)
			(i + blockSize, j)	(i + blockSize, j + blockSize)
			(� ��������� �� ��������; � ������ �� ��� �� ��� � �������� ������ - ��������� �� ��, ��� ������ � �����)
			*/
			/*
			����, ��������:
			1) ���� x � z
			2) ��������� � ��������� �������?
			3) �� ����� ��� ������ �������� ��������� � ���� ���� ��������
			*/

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

			//� ����������� �� ��������������� �������� ������ ������ y (
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
