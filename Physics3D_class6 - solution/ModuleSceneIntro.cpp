#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

#define SIZE_ARRAY(a) (sizeof(a)/sizeof(a[0]))

struct CubeDef {
	vec3 dim;
	vec3 pos;
	Color color;
	int  incl_ang;
	vec3 incl_axis;
};

CubeDef cube_defs[] = {
	{ vec3( 40,  2,  50),   vec3(    8,	  1,  67), White, -10, vec3(1, 0, 0) },		//Rampa
	{ vec3( 40,  2,  50),   vec3(    8,   1, 195), White,  10, vec3(1, 0, 0) },		//Rampa
	{ vec3( 40,  2,  79),   vec3(    8, 5.3, 131), White},							//Pont
	
//External Walls
	{ vec3(310, 80,  20),   vec3(    0,   0,  -5), White},							//Wall 1
	{ vec3( 20, 80, 300),   vec3( -150,   0, 155), White},							//Wall 2
	{ vec3( 20, 80, 300),   vec3(  150,   0, 155), White},							//Wall 3
	{ vec3(310, 80,  20),   vec3(    0,   0, 305), White},							//Wall 4
						  	     		  		 
//internal Walls

	{ vec3( 10, 10, 220),   vec3(  110,   0, 155), White},							//Wall 6
	{ vec3( 80, 10,  10),   vec3(   65,   0,  50), White},							//Wall 7
	{ vec3( 10, 10,  50),   vec3(  -15,   0,  30), White},							//Wall 9
	{ vec3( 10, 10, 100),   vec3(   30,   0, 255), White},							//Wall 10
	{ vec3(105, 10,  55),   vec3(-62.5,   0, 235), White},							//Wall 12 					   
	{ vec3(55, 10, 175),    vec3(-87.5,   0, 120), White},							//Wall 14
};

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

	s.size = vec3(40, 0.1, 1);
	s.SetPos(7, 0, 50);

	sensor = App->physics->AddBody(s, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	for (int i = 0; i < SIZE_ARRAY(cube_defs); i++)
		CreateCube(cube_defs[i].dim, cube_defs[i].pos, cube_defs[i].incl_ang, cube_defs[i].incl_axis,cube_defs[i].color);

	timer_laps.Start();
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

	DrawMap();

	sensor->GetTransform(&s.transform);
	s.Render();

	char title[150];
	sprintf_s(title, "%.1f Km/h - %02i:%02i", App->player->vehicle->GetKmh(), timer_laps.ReadSec() / 60, timer_laps.ReadSec() % 60);
	App->window->SetTitle(title);

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	LOG("Hit!");
}

void ModuleSceneIntro::CreateCube(vec3 dimensions, vec3 pos, int rot, vec3 vecRot, Color color) {

	Cube c(dimensions.x, dimensions.y, dimensions.z) ;
	c.SetPos(pos.x, pos.y, pos.z);
	if(rot != 0)
		c.SetRotation(rot, vecRot);
	c.color = color;
	App->physics->AddBody(c, 0);
	cube.add(c);
}

void ModuleSceneIntro::DrawMap() {
	for (p2List_item<Cube>* iter = cube.getFirst(); iter; iter = iter->next)
		iter->data.Render();
}