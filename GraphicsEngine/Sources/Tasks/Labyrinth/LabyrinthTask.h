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
			pCameraObj->m_pTransform = new Transform(Vector3(0.0f, 0.5f, -5.0f), Vector3(10.0f, 0.0f, 0.0f));
			pCameraObj->AddComponent(new LabyrinthCameraController);
			pCameraObj->AddComponent(pCamera);


			scene.SetCamera(pCamera);
		}

		{
			for (ushort x = 0; x < labyrinth.getX(); x++)
			{
				for (ushort y = 0; y < labyrinth.getY(); y++)
				{
					Object * labObject = new Object();

					//unsigned char 
					pObject2->m_pTransform = new Transform(0, 10, 0, 0, 0, 0, 1, 1, 1);
					pObject2->m_pMesh = new MeshCube();
					pObject2->m_pMaterial = new MaterialUnlit(Vector3(1, 1, 1));

					scene.AddObject(labObject);
				}
			}
		}

		{
			Object * pObject2 = new Object();

			pObject2->m_pTransform = new Transform(0, 10, 0, 0, 0, 0, 1, 1, 1);
			pObject2->m_pMesh = new MeshCube();
			pObject2->m_pMaterial = new MaterialUnlit(Vector3(1, 1, 1));

			scene.AddObject(pObject2);
		}


	}

	virtual void Update()
	{

	}
};
