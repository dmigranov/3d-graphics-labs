#pragma once
#include "GraphicsEngine/Application.h"
#include "GraphicsEngine/GraphicsEngine.h"
#include "GraphicsEngine/Light.h"
#include "GraphicsEngine/Materials/MaterialDiffuse.h"
#include "GraphicsEngine/Materials/MaterialUnlit.h"
#include "GraphicsEngine/Meshes/MeshSphere.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Scene.h"
#include "GraphicsEngine/Transform.h"

#include "Tasks/Task.h"
#include "Tasks/ObjectRotator.h"
#include "Tasks/ObjectMover.h"


/**
* @brief Shows how to write lightning materials.
* Key code is situated in the classes MaterialDiffuse, Light.
*/
class Task04: public Task
{
public:
	virtual ~Task04() { }

	virtual void Init()
	{
		Scene & scene = Application::Instance().GetScene();
		
		// Camera
		{
			Object * pCameraObj = new Object();

			pCameraObj->m_pTransform = new Transform( Vector3(0.0f, 0.0f,-10.0f), Vector3(0.0f, 0.0f, 0.0f));

			Camera * pCamera = new Camera();
			pCameraObj->AddComponent( pCamera );
			

			scene.SetCamera( pCamera );
		}

		// Object - Sphere
		{
			Object * pObject1 = new Object();

			pObject1->m_pTransform	= new Transform(0,0,0, 0,0,0, 3,3,3);
			pObject1->m_pMesh		= new MeshSphere(20);
            pObject1->m_pMaterial	= new MaterialDiffuse();
			pObject1->AddComponent( new ObjectRotator(0,10,0) );

			scene.AddObject( pObject1 );
		}

		// Ligth source #1 - Directional
		{
			Light * pLight = new Light(LIGHT_DIRECTIONAL);
			pLight->SetColor(1,1,0);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform	= new Transform(0,0,-5, 0,0,0, 1,1,1);
			pLightObject->AddComponent(pLight);
			//pLightObject->AddComponent(new ObjectRotator(20, 0, 0));

			scene.AddLight(pLight); //directional works!
		}

		// Ligth source #2 - Point
		/*{
			Light * pLight = new Light(LIGHT_POINT);
			pLight->SetColor(1,1,1);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->m_pTransform	= new Transform(0, 0,-5.5, 0,0,0, 1,1,1);
			pLightObject->AddComponent(pLight);
			//pLightObject->AddComponent(new ObjectRotator(0, 20, 0)); //вращение идёт вокруг собственной оси, поэтому в случае с пойнтом смысла не имеет, т.к он излучает во все стороны

			scene.AddLight(pLight); //it works as well! (read above)
		}*/

		//Ligth source #3 - Spot
		/*{
			Light * pLight = new Light(LIGHT_SPOT);
			pLight->SetColor(1, 1, 1);
			pLight->SetIntensity(1);

			Object * pLightObject = new Object();
			pLightObject->AddComponent(new ObjectRotator(0, -20, 0));
			pLightObject->m_pMesh = new MeshCube(20);
			pLightObject->m_pMaterial = new MaterialUnlit(Vector3(1, 1, 1));
			//pLightObject->m_pTransform = new Transform(0, 0, -6, 0, 0, 0, 1, 1, 1);
			pLightObject->m_pTransform = new Transform(0, 0, -4.5, 0, 0, 0, 1, 1, 1);
			//pLightObject->m_pTransform = new Transform(0, -4.5, 0, PI, 0, 0, 1, 1, 1);
			pLightObject->AddComponent(pLight);


			scene.AddLight(pLight);

		}*/
	}

	virtual void Update()
	{
		
	}
};
