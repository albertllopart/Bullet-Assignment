#pragma once
#include "Module.h"
#include "p2DynArray.h"
#include "Globals.h"
#include "Primitive.h"

#define MAX_SNAKE 2

struct PhysBody3D;
struct PhysMotor3D;

class ModuleSceneIntro : public Module
{
public:
	ModuleSceneIntro(Application* app, bool start_enabled = true);
	~ModuleSceneIntro();

	bool Start();
	update_status Update(float dt);
	bool CleanUp();

	void OnCollision(PhysBody3D* body1, PhysBody3D* body2);

	void CreateCube(vec3 dimensions, vec3 pos, bool sens = false, int rot = 0, vec3 vecRot = { 0,0,0 },Color color = White);
	void DrawMap();
	void AddSensor(Cube c);

public:
	Cube s1;
	p2List<PhysBody3D*> sens;
	//PhysBody3D* sensor =  nullptr;
	//PhysBody3D* sensor2 = nullptr;
	//PhysBody3D* sensor3 = nullptr;
	p2List<Cube> cube;

	Timer timer_laps;
	uint best_time = 6000;
	bool started = false;
	bool half_lap = false;
	bool last_sensor = false;
	bool WantToStart = false;
};
