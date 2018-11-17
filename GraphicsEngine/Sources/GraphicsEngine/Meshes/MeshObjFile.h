#pragma once
#include "Mesh.h"
#include <vector>
#include "GraphicsEngine/Vector3.h"


class MeshObjFile : public Mesh
{
public:
	MeshObjFile(const char * filepath);

	virtual void Init();
	virtual void Deinit();

private:
	std::string m_filepath;
	std::vector<std::string> parseString(std::string str, char delimiter);
	std::vector<double> getNumericValues(std::vector<std::string> strings);
};
