#include "MeshObjFile.h"
#include "GraphicsEngine/Application.h"
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>


MeshObjFile::MeshObjFile(const char * filepath)
{
	m_filepath = Application::Instance().GetDataDirectory() + "/" + filepath;
}

void MeshObjFile::Init()
{
	Mesh::Init();

	// TODO: Task07
}

void MeshObjFile::Deinit()
{
	Mesh::Deinit();
}
