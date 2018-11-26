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
	//std::vector<Vector4> colors; //?
	std::vector<Vector3> normals;
	std::vector<Vector3> uv0;

	std::vector<int> vertexIndices;
	std::vector<int> textureIndices;
	std::vector<int> normalIndices;

	std::ifstream infile;
	infile.open(m_filepath);

	if (!infile)
	{
		std::cerr << "Unable to open file " << m_filepath << std::endl;
		exit(1);
	}

	std::string str;
	size_t polygonSize;

	while (std::getline(infile, str))
	{
		std::cout << str << std::endl;
		if (str[0] == 'v')
		{
			if (str[1] == ' ') //v -0.5 0.5 -0.5
			{
				str = str.substr(2);
				std::vector<std::string> parsedStrings = parseString(str, ' ');
				std::vector<double> values = getDoubleValues(parsedStrings);
				vertices.push_back(Vector3(values[0], values[1], values[2]));
			}
			else if (str[1] == 'n') //vn 0 0 -1
			{
				str = str.substr(3);
				std::vector<std::string> parsedStrings = parseString(str, ' ');
				std::vector<double> values = getDoubleValues(parsedStrings);
				normals.push_back(Vector3(values[0], values[1], values[2]));
			}
			else if (str[1] == 't') //vt 0 0
			{
				str = str.substr(3);
				std::vector<std::string> parsedStrings = parseString(str, ' ');
				std::vector<double> values = getDoubleValues(parsedStrings);
				uv0.push_back(Vector3(values[0], values[1], 0));
			}
		}
		else if (str[0] == 'f') //f 2/2/2 4/4/4 1/1/1
		{
			str = str.substr(2);
			std::vector<std::string> parsedStrings = parseString(str, ' '); 
			polygonSize = parsedStrings.size(); //3 or 4
			for (std::string substr : parsedStrings) //2/2/2
			{
				std::vector<std::string> strIndices = parseString(substr, '/');
				std::vector<double> indices = getIntValues(strIndices);
				vertexIndices.push_back(indices[0] - 1); //кароч в этом obj индексы считаются с единицы, а не с нуля. ну ваще...
				textureIndices.push_back(indices[1] - 1);
				normalIndices.push_back(indices[2] - 1);
			}
		}
		else if (str[0] == 'm') //mtllib
		{
			str = str.substr(7);
			//parseMTL(str);

			
		}
	}

	int i = 0;

	std::vector<Vector4> colors;
	for (unsigned int i = 0; i < vertices.size(); i++)
	{
		colors.push_back(Vector4(1.0f, 1.0f, 1.0f, 0.5f)); //
	}

	meshImpl->SetVertices(vertices);
	meshImpl->SetColors(colors); //change
	meshImpl->SetNormals(normals);
	meshImpl->SetUV0(uv0);


	meshImpl->SetIndices(vertexIndices, MESH_TOPOLOGY_TRIANGLE_LIST); //ну тут работает, а как это из файла понять, что там не STRIP?

	meshImpl->Apply();


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

std::vector<double> MeshObjFile::getDoubleValues(std::vector<std::string> strings)
{
	std::vector<double> vec;
	for (std::string str : strings)
	{
		vec.push_back(atof(str.c_str()));
	}
	return vec;
}

std::vector<double> MeshObjFile::getIntValues(std::vector<std::string> strings)
{
	std::vector<double> vec;
	for (std::string str : strings)
	{
		vec.push_back(atoi(str.c_str()));
	}
	return vec;
}

void MeshObjFile::parseMTL(std::string mtlpath)
{
	std::string fullpath = Application::Instance().GetDataDirectory() + "/" + mtlpath;
	std::ifstream infile;
	infile.open(fullpath);

	if (!infile)
	{
		std::cerr << "Unable to open file " << m_filepath << std::endl;
		exit(1);
	}

	std::string str;

	while (std::getline(infile, str))
	{

	}
}
