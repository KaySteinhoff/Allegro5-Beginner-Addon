#pragma once
#include "Addon.h"
#include "Matrix.h"
using namespace std;

//<summary>
//This class is used to programm the behavior of the Window.
//It is simplified so that a Person with little knowledge can
//addapt easily to this Addon.
//Obviously this is very much inspired by the workflow in Unity
//</summary>
class Source
{
	//Declaration of the variables (can be added in the Function too like in Unity)
	Matrix mat;
	Mesh mesh;

public:
	//Called at the start of the Application
	void Start()
	{
		mat.setup_3D();
		mesh.LoadFromObjectFile("cube.obj");
	}

	//Called everyframe
	void Update()
	{
		mat.UpdateMatrix(0.03 , mesh);
	}
};
