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

			GUI::Label(0, 0, 500, 500, "YOU WON THE GAME. \nRESTART IT TO PLAY AGAIN");
		}

	}
	void setWon(bool val)
	{
		PlayerHasWon = val;
	}
};
