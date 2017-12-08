#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"

ModuleSceneIntro::ModuleSceneIntro(Application* app, bool start_enabled) : Module(app, start_enabled)
{
}

ModuleSceneIntro::~ModuleSceneIntro()
{}

// Load assets
bool ModuleSceneIntro::Start()
{
	LOG("Loading Intro assets");
	bool ret = true;

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	s.size = vec3(5, 3, 1);
	s.SetPos(0, 2.5f, 20);


	Cube ramp_up(22, 2, 46);
	ramp_up.SetPos(5, 0, 69.5);
	ramp_up.SetRotation(-15, vec3(1, 0, 0));
	App->physics->AddBody(ramp_up, 0);

	Cube ramp_down(22, 2, 46);
	ramp_down.SetPos(5, 0, 138);
	ramp_down.SetRotation(15, vec3(1, 0, 0));
	App->physics->AddBody(ramp_down, 0);

	Cube roof(22, 2, 25);
	roof.SetPos(5, 6, 104);
	App->physics->AddBody(roof, 0);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	return ret;
}

// Load assets
bool ModuleSceneIntro::CleanUp()
{
	LOG("Unloading Intro scene");

	return true;
}

// Update
update_status ModuleSceneIntro::Update(float dt)
{
	Plane p(0, 1, 0, 0);
	p.axis = false;
	p.Render();


	Cube ramp_up(22, 2, 46);
	ramp_up.SetPos(5, 0, 69.5);
	ramp_up.SetRotation(-15, vec3(1, 0, 0));
	ramp_up.Render();


	Cube ramp_down(22, 2, 46);
	ramp_down.SetPos(5, 0, 138);
	ramp_down.SetRotation(15, vec3(1, 0, 0));
	ramp_down.Render();

	Cube roof(22, 2, 25);
	roof.SetPos(5, 6, 104);
	roof.Render();

	sensor->GetTransform(&s.transform);
	s.Render();

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}

