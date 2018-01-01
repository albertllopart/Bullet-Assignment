#pragma once
#include "Module.h"
#include "Globals.h"
#include "p2Point.h"

struct PhysVehicle3D;

#define MAX_ACCELERATION 3000.0f
#define TURN_DEGREES 4.0f * DEGTORAD
#define BRAKE_POWER 100.0f
#define REVERSE -1000.0f

class ModulePlayer : public Module
{
public:
	ModulePlayer(Application* app, bool start_enabled = true);
	virtual ~ModulePlayer();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

public:

	PhysVehicle3D* vehicle;
	float turn;
	float acceleration;
	float brake;
	float reset[16] = { 1,0,0,0,0,1,0,0,0,0,1,0,0,0.6f,20,1 };
};