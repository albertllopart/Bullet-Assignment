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

	void CreateCube(vec3 dimensions, vec3 pos, int rot = 0, vec3 vecRot = { 0,0,0 },Color color = White);
	void DrawMap();

public:
	Cube s;
	PhysBody3D* sensor;
	p2List<Cube> cube;

	Timer timer_laps;
	
};
