#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/Materials/MaterialUnlitSimple.h"
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

		//генерация лабиринта
		Labyrinth labyrinth = Labyrinth(15, 15);

		// Camera
		{
			Object * pCameraObj = new Object();
			Camera * pCamera = new Camera();
			//pCameraObj->m_pTransform = new Transform(Vector3(0.0f, 1.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
			pCameraObj->m_pTransform = new Transform(Vector3(1.0f, 1.0f, 1.0f), Vector3(0.0f, 0.0f, 0.0f));

			//TODO: исправить LabyrinthCameraController, чтобы он перемещался правильно; кстати, можно добавить мэши, чтобы потом отражалось; для головы отдельный
			pCameraObj->AddComponent(new LabyrinthCameraController(labyrinth, blockSize));
			pCameraObj->AddComponent(pCamera);

			scene.SetCamera(pCamera);
		}

		{
			ushort lX = labyrinth.getX();
			ushort lY = labyrinth.getY();

			{
				Object * floor = new Object();

				floor->m_pTransform = new Transform(lX * blockSize / 2.0, 0, lY * blockSize / 2.0, 0, 0, 0, lX * blockSize, 1, lY * blockSize);
				floor->m_pMesh = new MeshQuad();
				floor->m_pMaterial = new MaterialUnlit(Vector3(0, 1, 0));

				scene.AddObject(floor);
			}

			for (ushort x = 0; x < lX; x++)
			{
				for (ushort y = 0; y < lY; y++)
				{
					Object * labObject = new Object();

					Block block = labyrinth.getAt(x, y);
					switch (block)
					{
					case WALL:
						labObject->m_pTransform = new Transform(x * blockSize - blockSize / 2.0, blockSize / 2.0, y * blockSize - blockSize / 2.0, 0, 0, 0, blockSize, blockSize*2.0, blockSize);
						labObject->m_pMesh = new MeshCube();
						labObject->m_pMaterial = new MaterialUnlit(Vector3(1, 0, 0));
						break;
					}

					scene.AddObject(labObject);
				}
			}
		}




	}

	virtual void Update()
	{

	}
};
