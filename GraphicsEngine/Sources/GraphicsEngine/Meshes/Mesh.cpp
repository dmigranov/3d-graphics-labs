#include "Mesh.h"
#include "GraphicsEngine/GraphicsEngineFabric.h"
#include <cstddef>


Mesh::Mesh()
{
	meshImpl = NULL;
}

void Mesh::Init()
{
	if (NULL != meshImpl)
	{
		Deinit();
	}

	meshImpl = GraphicsEngineFabric::CreateMesh();
	meshImpl->Init();
	meshImpl->SetTransparent(transparent);
}

void Mesh::Deinit()
{
	meshImpl->Deinit();
}

void Mesh::Render()
{
	meshImpl->Render();
}

void Mesh::SetTransparent(bool value)
{
	transparent = value;
}
