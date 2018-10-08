#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/Camera.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Meshes/MeshCube.h"
#include "GraphicsEngine/Meshes/MeshCylinder.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Materials/MaterialSphereMorphing.h"
#include "GraphicsEngine/Materials/MaterialCylinderMorphing.h"

#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"
#include "Tasks/CameraController.h"


/**
* @brief Shows how to morph the objects.
* Key code is situated in the classes MaterialTask02Cube, MaterialTask02Cylinder.
*/
class Task02: public Task
{
public:
	virtual ~Task02() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
	
		// Camera
		{
			Object * pCameraObj = new Object();
			pCameraObj->m_pTransform = new Transform( Vector3(0, 3, -5), Vector3(20.0f, 0.0f, 0.0f));
			Camera * pCamera = new Camera();
			pCamera->SetFovY(90);
			pCamera->SetNearPlane(0.01f);
			pCamera->SetFarPlane(100);
			pCameraObj->AddComponent( pCamera );
			pCameraObj->AddComponent( new CameraController() );

			scene.SetCamera( pCamera );
		}

		// Object # 1 - Cube (is morphed to sphere)
		{
			Object * pObject = new Object();
			pObject->m_pTransform	= new Transform( Vector3(-1.5, 0, 0), Vector3(0, 30, 0) );
			pObject->m_pMesh		= new MeshCube(10);			
            pObject->m_pMaterial	= new MaterialSphereMorphing(); //create another Class

			scene.AddObject( pObject );
		}

		// Object #2 - Cylinder (is twisted)
        {
			Object * pObject = new Object();
			pObject->m_pTransform	= new Transform( Vector3(1.5, 0, 0), Vector3(0, 30, 0) );
			pObject->m_pMesh		= new MeshCylinder(20);			
			pObject->m_pMaterial	= new MaterialCylinderMorphing(); //create another Class
			
			scene.AddObject( pObject );
        }
	}

	virtual void Update()
	{
		
	}
};
