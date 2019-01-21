#pragma once
#include "GraphicsEngine/Component.h"
#include "GraphicsEngine/GUI.h"
#include "GraphicsEngine/Object.h"
#include "GraphicsEngine/Transform.h"
#include "GraphicsEngine/Time.h"
#include "GraphicsEngine/Vector3.h"

#include <iostream>


class YouWonText : public Component
{
	bool PlayerHasWon;

public:
	YouWonText()
	{
		PlayerHasWon = false;
	}

	virtual ~YouWonText() {}

	virtual void Update()
	{
		
		if (PlayerHasWon)
		{
			//сделать всё черным

			GUI::Rectangle(0, 0, 2000, 2000, 0,0,0);
		}

	}
	void setWon(bool val)
	{
		PlayerHasWon = val;
	}
};
