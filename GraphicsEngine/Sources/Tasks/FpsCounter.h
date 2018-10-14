#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/GUI.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"


class FpsCounter : public Component
{
	double	t1;
	int		f1;
	double	fps;

public:
	FpsCounter() 
	{
		t1 = Time::GetTime();
		f1 = Time::GetFrameCount();
		fps = 0;
	}

	virtual ~FpsCounter() {}

	virtual void Update() 
	{
		double t2	= Time::GetTime();
		int f2		= Time::GetFrameCount();

		GUI::Label(0, 0, 100, 100, 60.0);

		// TODO: Task03
	}
};
