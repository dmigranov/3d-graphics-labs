#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/Materials/MaterialUnlitSimple.h"
#include "GraphicsEngine/Materials/MaterialWall.h"
#include "GraphicsEngine/Materials/MaterialDirty.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"

#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"

#include "Tasks/Labyrinth/LabyrinthCameraController.h"

#define blockSize 1


class LabyrinthTask : public Task
{
public:
	virtual ~LabyrinthTask() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();

		//��������� ���������
		Labyrinth labyrinth = Labyrinth(15, 15);

		// Camera
		{
			Object * pCameraObj = new Object();
			Camera * pCamera = new Camera();
			pCameraObj->m_pTransform = new Transform(Vector3(1.5f, 1.0f, 1.5f), Vector3(0.0f, 0.0f, 0.0f));
			//TODO: ����� �������� ����, ����� ����� ���������� (?); ��� ������ ���������?
			pCameraObj->AddComponent(new LabyrinthCameraController(labyrinth, blockSize));

			pCameraObj->AddComponent(pCamera);
			scene.SetCamera(pCamera);
		}

		{
			ushort lX = labyrinth.getX();
			ushort lY = labyrinth.getY();
			{
				Object * floor = new Object();
				/*Mesh mesh;
				mesh.Render();*/

				floor->m_pTransform = new Transform(lX * blockSize / 2.0, 0, lY * blockSize / 2.0, 0, 0, 0, lX * blockSize, 1, lY * blockSize);
				floor->m_pMesh = new MeshQuad();
				floor->m_pMaterial = new MaterialDirty(TEXTURE_FILTER_MODE_ANISOTROPIC);

				scene.AddObject(floor);	//TODO: � ����� ���� ����� ������� ��� ����� ���� ����������, �����!
			}

			{
				Object * ceil = new Object();
				double height = blockSize * 3 / 2.0;
				ceil->m_pTransform = new Transform(lX * blockSize / 2.0, height, lY * blockSize / 2.0, 0, 0, 180, lX * blockSize, 1, lY * blockSize);
				ceil->m_pMesh = new MeshQuad();
				ceil->m_pMaterial = new MaterialUnlit(Vector3(1, 1, 1));

				scene.AddObject(ceil);

				//TODO: �������� "���������� �������"
			}

			for (ushort x = 0; x < lX; x++)
			{
				for (ushort y = 0; y < lY; y++)
				{
					Object * labObject = new Object();
					Object * labObject_u = new Object();

					Block block = labyrinth.getAt(x, y);
					switch (block)
					{
					case WALL:
						//labObject->m_pTransform = new Transform(x * blockSize, blockSize / 2.0, y * blockSize, 0, 0, 0, blockSize, blockSize*2.0, blockSize);
						labObject->m_pTransform = new Transform(x * blockSize + blockSize / 2.0, blockSize / 2.0, y * blockSize + blockSize / 2.0, 0, 0, 0, blockSize, blockSize*2.0, blockSize);
						labObject->m_pMesh = new MeshCube();
						labObject->m_pMaterial = new MaterialWall(TEXTURE_FILTER_MODE_ANISOTROPIC);

						//����� - ���� �����
						
						labObject_u->m_pTransform = new Transform(x * blockSize + blockSize / 2.0, -blockSize / 2.0, y * blockSize + blockSize / 2.0, 0, 0, 0, blockSize, blockSize*2.0, blockSize);
						labObject_u->m_pMesh = new MeshCube();
						labObject_u->m_pMaterial = new MaterialWall(TEXTURE_FILTER_MODE_ANISOTROPIC);

						break;
					case FINISHWALL:
						labObject->m_pTransform = new Transform(x * blockSize + blockSize / 2.0, blockSize / 2.0, y * blockSize + blockSize / 2.0, 0, 0, 0, blockSize, blockSize*2.0, blockSize);
						labObject->m_pMesh = new MeshCube();
						labObject->m_pMaterial = new MaterialRoad();

						labObject_u->m_pTransform = new Transform(x * blockSize + blockSize / 2.0, -blockSize / 2.0, y * blockSize + blockSize / 2.0, 0, 0, 0, blockSize, blockSize*2.0, blockSize);
						labObject_u->m_pMesh = new MeshCube();
						labObject_u->m_pMaterial = new MaterialRoad();
						break;
					}

					scene.AddObject(labObject);
					scene.AddObject(labObject_u);
				}
			}

			//TODO: �������� ���������� ������� (reflectio, environment mapping (cubic?))
		}

	}

	virtual void Update()
	{

	}
};
