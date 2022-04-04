// PandaPlatformerPrac.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "pandaFramework.h"
#include "pandaSystem.h"

#include "genericAsyncTask.h"
#include "asyncTaskManager.h"

PT(AsyncTaskManager) taskMgr = AsyncTaskManager::get_global_ptr();
PT(ClockObject) globalClock = ClockObject::get_global_clock();
NodePath camera;

AsyncTask::DoneStatus spinCameraTask(GenericAsyncTask* task, void* data) {
	double time = globalClock->get_real_time();
	double angledegrees = time * 6.0;
	double angleradians = angledegrees * (3.14 / 180);
	camera.set_pos(20 * sin(angleradians), -20 * cos(angleradians), 3);
	camera.set_hpr(angledegrees, 0, 0);

	return AsyncTask::DS_cont;
}

int main(int argc, char* argv[]) {
	
	// Open a new window framework
	PandaFramework framework;
	framework.open_framework(argc, argv);

	// Set the window title and open the window
	framework.set_window_title("My Panda3D Window");
	WindowFramework* window = framework.open_window();
	//window->setup_trackball();
	camera = window->get_camera_group();

	// Here is room for your own code
	NodePath scene = window->load_model(framework.get_models(), "models/environment");
	scene.reparent_to(window->get_render());

	scene.set_scale(0.25f, 0.25f, 0.25f);
	scene.set_pos(-8, 42, 0);

	taskMgr->add(new GenericAsyncTask("spin task", &spinCameraTask, nullptr));

	// Do the main loop, equal to run() in python
	framework.main_loop();
	framework.close_framework();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
