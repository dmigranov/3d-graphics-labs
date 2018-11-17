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
	{
		if (str[0] == 'v')
		{
			if (str[1] == ' ') //v -0.5 0.5 -0.5
			{
				str = str.substr(2);
				std::vector<std::string> parsedStrings = parseString(str, ' ');
				std::vector<double> values = getNumericValues(parsedStrings);
				vertices.push_back(Vector3(values[0], values[1], values[2]));
			}
			else if (str[1] == 'n') //vn 0 0 -1
			{
				str = str.substr(3);
				std::vector<std::string> parsedStrings = parseString(str, ' ');
				std::vector<double> values = getNumericValues(parsedStrings);
				normals.push_back(Vector3(values[0], values[1], values[2]));
			}
		}
	}



	/*meshImpl->SetVertices(vertices);
	meshImpl->SetColors(colors);
	meshImpl->SetNormals(normals);
	meshImpl->SetUV0(uv0);

	meshImpl->SetIndices(indices, MESH_TOPOLOGY_TRIANGLE_STRIP);

	meshImpl->Apply();*/


}

void MeshObjFile::Deinit()
{
	Mesh::Deinit();
}


std::vector<std::string> MeshObjFile::parseString(std::string str, char delimiter)
{
	std::vector<std::string> vec;
	size_t startIndex = 0;
	size_t endIndex;
	while ((endIndex = str.find(delimiter, startIndex)) != std::string::npos)
	{
		std::string substr = str.substr(startIndex, endIndex - startIndex);
		vec.push_back(substr);
		startIndex = endIndex + 1;
	}
	std::string substr = str.substr(startIndex, endIndex - startIndex);
	vec.push_back(substr);
	return vec;
}

std::vector<double> MeshObjFile::getNumericValues(std::vector<std::string> strings)
{
	std::vector<double> vec;
	for (std::string str : strings)
	{
		vec.push_back(atof(str.c_str()));
	}
	return vec;
}
