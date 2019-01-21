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
	bool timeStop;
	double t1;
	double diff;

public:
	YouWonText()
	{
		PlayerHasWon = false;
		timeStop = false;
		t1 = Time::GetTime();
	}

	virtual ~YouWonText() {}

	virtual void Update()
	{
		
		if (PlayerHasWon)
		{
			if (!timeStop)
			{
				timeStop = true;
				double t2 = Time::GetTime();
				diff = t2 - t1;
			}
			std::string str_diff = std::to_string(diff);
			std::string str = "YOU COMPLETED THE LABYRINTH IN\n" + str_diff + " SECONDS. RESTART TO PLAY AGAIN";
			//GUI::Rectangle(0, 0, 500, 500, 0, 0, 0);
			//GUI::Label(0, 0, 500, 500, "YOU WON THE GAME. \nRESTART IT TO PLAY AGAIN");
			GUI::Label(0, 0, 500, 500, str);

		}

	}
	void setWon(bool val)
	{
		PlayerHasWon = val;
	}
};
