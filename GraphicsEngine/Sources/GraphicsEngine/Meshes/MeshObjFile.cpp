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
	std::vector<Vector3> vertices;
	std::vector<Vector4> colors; //?
	std::vector<Vector3> normals;
	std::vector<Vector3> uv0;

	std::ifstream infile;
	infile.open(m_filepath);

	if (!infile)
	{
		std::cerr << "Unable to open file " << m_filepath << std::endl;
		exit(1);
	}

	std::string str;
	while (std::getline(infile, str))
		std::cout << str << std::endl;

}

void MeshObjFile::Deinit()
{
	Mesh::Deinit();
}
