#include "GraphicsEngine/Application.h"

#include "Tasks/Task01.h"
#include "Tasks/Task02.h"
#include "Tasks/Task03.h"
#include "Tasks/Task04.h"
#include "Tasks/Task05_01.h"
#include "Tasks/Task05_02.h"
#include "Tasks/Task05_03.h"
#include "Tasks/Task06.h"
#include "Tasks/Task07.h"
#include "Tasks/Task08.h"


// The application's entry point
int main(int argc, char ** argv)
{
	// Remember argc, argv
	{
		Application & app = Application::Instance();
		app.argc = argc;
		app.argv = argv;
	}

    //Task * pTask = new Task01(); //done using plain DirectX 9
    //Task * pTask = new Task02(); //done
    //Task * pTask = new Task03(); //done
    //Task * pTask = new Task04(); //mistakes?
    //Task * pTask = new Task05_01(); //well I guess it's done
    //Task * pTask = new Task05_02(); //not that beautiful but I guess done
    Task * pTask = new Task05_03();
    //Task * pTask = new Task06();
	//Task * pTask = new Task07();
	//Task * pTask = new Task08();	
	{
		GraphicsEngine & engine = GraphicsEngine::Instance();

		engine.Init();
        pTask->Init();

		while (engine.IsRunning())
		{
            pTask->Update();
			engine.Render();

			_sleep(10);
		}

        delete pTask;
		engine.Deinit();
    }
	
    return 0;
}
