#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/GUI.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include <iostream>


class FpsCounter : public Component
{
	double	t1, t2;
	int		f1, f2;
	double	fps;

public:
	FpsCounter() 
	{
		t1 = Time::GetTime();
		f1 = Time::GetFrameCount();
		std::cout << f1 << std::endl;
		fps = 0;
	}

	virtual ~FpsCounter() {}

	virtual void Update() 
	{
		t2	= Time::GetTime();
		
		if (t2 - t1 >= 1.0)
		{
			f2 = Time::GetFrameCount();
			fps = (f2 - f1) / (t2 - t1);
			
			f1 = f2;
			t1 = t2;
		}

		GUI::Label(0, 0, 100, 100, fps);

		// TODO: Task03
	}
};
