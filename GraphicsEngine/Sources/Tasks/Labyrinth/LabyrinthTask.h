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

#include "Tasks/Labyrinth/Labyrinth.h"
#include "Tasks/Labyrinth/LabyrinthCameraController.h"

#define blockSize 0.5


class LabyrinthTask : public Task
{
public:
	virtual ~LabyrinthTask() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();

		//смотри другие таски
		//генерация лабиринта
		Labyrinth labyrinth = Labyrinth(25, 25);

		// Camera
		{
			Object * pCameraObj = new Object();
			Camera * pCamera = new Camera();
			pCameraObj->m_pTransform = new Transform(Vector3(0.0f, 2.0f, 0.0f), Vector3(0.0f, 0.0f, 0.0f));
			pCameraObj->AddComponent(new LabyrinthCameraController);
			pCameraObj->AddComponent(pCamera);


			scene.SetCamera(pCamera);
		}

		{
			{
				Object * floor = new Object();

				floor->m_pTransform = new Transform(0, 0, 0, 0, 0, 0, labyrinth.getX() * blockSize, 1, labyrinth.getY() * blockSize);
				floor->m_pMesh = new MeshQuad();
				floor->m_pMaterial = new MaterialUnlit(Vector3(0, 1, 0));

				scene.AddObject(floor);
			}

			for (ushort x = 0; x < labyrinth.getX(); x++)
			{
				for (ushort y = 0; y < labyrinth.getY(); y++)
				{
					Object * labObject = new Object();

					Block block = labyrinth.getAt(x, y);
					switch (block)
					{
					case WALL:
						labObject->m_pTransform = new Transform(x * blockSize, blockSize, y * blockSize, 0, 0, 0, blockSize, blockSize, blockSize);
						labObject->m_pMesh = new MeshCube();
						labObject->m_pMaterial = new MaterialUnlit(Vector3(0, 1, 1));
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
