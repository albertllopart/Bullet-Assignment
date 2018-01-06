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
	bool sens;
	bool hide;
	bool proceed;
	bool hazards;
	int  incl_ang;
	vec3 incl_axis;
};

CubeDef cube_defs[] = {				    
	{ vec3( 35,  15,  50),   vec3(  7.5, -5.3,  69), Orange, false, false, false, false, -10, vec3(1, 0, 0) },		//Rampa
	{ vec3( 10,  15,  50),   vec3(  -15,    2,  68), Orange, false, false, false, false, -10, vec3(1, 0, 0) },      //barana dreta
	{ vec3( 10,  15,  50),    vec3(  30,    2,  68), Orange, false, false, false, false, -10, vec3(1, 0, 0) },      //barana esquerra
									    
	{ vec3( 35,  15,  50),    vec3( 7.5, -5.4, 193), Orange, false, false, false, false, 10, vec3(1, 0, 0)},		//Rampa
	{ vec3( 10,  15,  50),    vec3( -15,    2, 194), Orange, false, false, false, false, 10, vec3(1, 0, 0)},        //barana dreta
	{ vec3( 10,  15,  50),    vec3(  30,    2, 194), Orange, false, false, false, false, 10, vec3(1, 0, 0)},        //barana esquerra
				 
				 
//External Walls 
	{ vec3(280,  80,  20),   vec3(    0,    0,  -5),  White, false, true},											//Wall 1
	{ vec3( 20,  80, 300),   vec3( -150,    0, 155),  White, false, true},											//Wall 2
	{ vec3( 20,  80, 300),   vec3(  150,    0, 155),  White, false, true},											//Wall 3
	{ vec3(310,  80,  20),   vec3(    0,    0, 305),  White, false, true},											//Wall 4
				 		  	     		   		 		 
//internal Walls 						   
				 						   
	{ vec3( 10,  10, 165),   vec3(  110,    0, 175), Orange },														//Wall 6
	{ vec3( 90,  10,  52),   vec3(   70,    0,  67), Orange },														//Wall 7
	{ vec3( 10,  10,  50),   vec3(  -15,    0,  30), Orange },														//Wall 9
	{ vec3( 10,  10, 100),   vec3(   30,    0, 255), Orange },														//Wall 10
	{ vec3(105,  10,  93),   vec3(-62.5,    0, 216), Orange },														//Wall 12 					   
	{ vec3( 55,  10, 137),   vec3(-87.5,    0, 101), Orange },														//Wall 14
				 
//hazards		 
				 
	{ vec3( 30,   6,   1),	vec3(   -40,    1,  90),  Green, false, false, false, true},
	{ vec3( 34,  10,   1),	vec3(    88,    0, 257),  Green },
	{ vec3( 34,  10,   1),	vec3(    52,    0, 215),  Green },
	{ vec3( 11,  10,   1),	vec3(  -121,    0,  60),  Green },
	{ vec3( 11,  10,   1),	vec3(  -121,    0, 140),  Green },
	{ vec3( 11,  10,   1),	vec3(  -121,    0, 220),  Green },
	{ vec3( 11,  10,   1),	vec3(  -135,    0, 100),  Green },
	{ vec3( 11,  10,   1),	vec3(  -135,    0, 180),  Green },
	{ vec3( 11,  10,   1),	vec3(  -135,    0, 260),  Green },
				 				   		  
//Sensors		 				   		  
				 				   		  
	{ vec3( 70,   5,   1),	vec3(    70,    0, 173),   Blue, true},													//sens1
	{ vec3(  1,   5,  40),	vec3(   -10,    0, 280),   Blue, true},													//sens2
	{ vec3( 40,   5,   1),	vec3(  -130,    0,  50),   Blue, true},													//sens3
								   		  
	{ vec3( 70, 0.1,  10),	vec3(    70,    0, 173),   Blue, false, false, true },
								   		  
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

	App->audio->LoadFx("Sounds/finish_lap.wav");//1
	App->audio->PlayMusic("Sounds/Intro.ogg");

	App->camera->Move(vec3(1.0f, 1.0f, 0.0f));
	App->camera->LookAt(vec3(0, 0, 0));

	Cylinder cy;
	cy.radius = 1;
	cy.height = 10;
	cy.SetRotation(90, { 0,0,1 });
	cy.SetPos(-40, 10, 90);
	cylinder = App->physics->AddBody(cy);


	for (int i = 0; i < SIZE_ARRAY(cube_defs); i++)
		CreateCube(cube_defs[i].dim, cube_defs[i].pos, cube_defs[i].sens, cube_defs[i].hide, cube_defs[i].proceed, cube_defs[i].hazards, cube_defs[i].incl_ang, cube_defs[i].incl_axis,cube_defs[i].color);


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
	p.color = Green;
	p.Render();

	DrawMap();
	if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN) {
		WantToStart = false;
		PreviousWire();
	}
	if (!WantToStart) {
		char title[150];
		sprintf_s(title, "Click Enter to start the game (3Laps) - Best Lap ->%02i:%02i", best_time / 60, best_time % 60);
		App->window->SetTitle(title);
	}
	else {
		char title[150];
		sprintf_s(title, "%.1f Km/h - Timer ->%02i:%02i - Best Lap ->%02i:%02i", App->player->vehicle->GetKmh(), timer_laps.ReadSec() / 60, timer_laps.ReadSec() % 60, best_time / 60, best_time % 60);
		App->window->SetTitle(title);
	}
	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	p2List_item<PhysBody3D*>* sens_list = sens.getFirst()->next;

	if (body1 == sens_list->prev->data) {
		if (last_sensor) {
			last_sensor = false;
			half_lap = false;
			if (timer_laps.ReadSec() < best_time)
				best_time = timer_laps.ReadSec();
			timer_laps.Start();
			laps++;
			App->audio->PlayFx(1);
			if (laps == 3) {
				WantToStart = false;
				App->audio->PlayMusic("Sounds/Intro.ogg");
				PreviousWire();
			}
		}
		if (!started) {
			timer_laps.Start();
			started = true;
		}
	}
	else if (body1 == sens_list->data && started)
		half_lap = true;

	else if (body1 == sens_list->next->data && started && half_lap)
		last_sensor = true;	

	App->player->vehicle->GetTransform(App->player->reset);
}

void ModuleSceneIntro::CreateCube(vec3 dimensions, vec3 pos, bool sens, bool hide, bool proceed, bool hazards, int rot, vec3 vecRot, Color color) {

	Cube c(dimensions.x, dimensions.y, dimensions.z) ;
	c.SetPos(pos.x, pos.y, pos.z);
	if (!sens) {
		if (rot != 0)
			c.SetRotation(rot, vecRot);
		c.color = color;
		c.wire = hide;
		if(!proceed && !hazards)
			App->physics->AddBody(c, 0.0f);
		else if (hazards) {
			cube_rot = App->physics->AddBody(c, 100000);
			cylinder->body->setAngularFactor(btVector3(0, 0, 0));
			cube_rot->body->setLinearFactor(btVector3(0, 0, 0));
			App->physics->AddConstraintHinge(*cylinder, *cube_rot, vec3(0, 0, 0), vec3(0, 0, 0), vec3(1, 0, 0), vec3(0, 0, 0), 80000.0f, true);
		}
		cube.add(c);
	}
	else if (sens) 
		AddSensor(c);
}

void ModuleSceneIntro::DrawMap() {
	p2List_item<Cube>* iter = cube.getFirst();
	for (int i = 0; iter; iter = iter->next, i++) {
		if (cube_defs[i].hazards)
			cube_rot->GetTransform(&iter->data.transform);
		iter->data.Render();
	}
}

void ModuleSceneIntro::AddSensor(Cube c){
	PhysBody3D* sensor;
	sensor = App->physics->AddBody(c, 0.0f);
	sensor->SetAsSensor(true);
	sensor->collision_listeners.add(this);

	sens.add(sensor);
}

void ModuleSceneIntro::PreviousWire() {
	p2List_item<Cube>* iter = cube.getFirst();
	for (int i = 0; iter; i++, iter = iter->next) {
		iter->data.wire = cube_defs[i].hide;

	}
}