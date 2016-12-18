#include "Globals.h"
#include "Application.h"
#include "ModuleSceneIntro.h"
#include "Primitive.h"
#include "PhysBody3D.h"
#include "PhysVehicle3D.h"

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

	actual_pos.x = 0;
	actual_pos.y = 0;
	actual_pos.z = 0;

	Map.add(App->physics->CreateRoad(70, EAST, EAST, 0, 30));
	checkpoints.add(App->physics->CreateWallSensor(30, 1, actual_pos.x, actual_pos.y + 3, actual_pos.z-10, NORTH));	//1rst sensor
	Map.add(App->physics->CreateWall(10, 30, 1, actual_pos.x, actual_pos.y, actual_pos.z, NORTH, RED));		//1rst wall
	Map.add(App->physics->CreateRoad(10, EAST, EAST, 0, 30));
	Map.add(App->physics->CreateRoad(50, EAST, EAST, 30, 30, true, BLUE));
	Map.add(App->physics->CreateRoad(50, EAST, EAST, 30, 30));
	Map.add(App->physics->CreateWall(10, 30, 1, actual_pos.x, actual_pos.y, actual_pos.z, NORTH, BLUE));	//2nd wall
	//Map.add(App->physics->CreateRoad(50, EAST, EAST, 30, 30, false, UNCOLORED, 30));
	Map.add(App->physics->CreateRoad(50, EAST, EAST, 30, 30));
	//Map.add(App->physics->CreateDemolitionBall(actual_pos.x, actual_pos.y + 10, actual_pos.z - 10, 3, 10.0f, RED));
	//Map.add(App->physics->CreateDemolitionBall(actual_pos.x + 10, actual_pos.y + 10, actual_pos.z - 10, 3, 10.0f, RED));
	checkpoints.add(App->physics->CreateWallSensor(30, 1, actual_pos.x, actual_pos.y, actual_pos.z, NORTH));	//1rst sensor
	Map.add(App->physics->CreateRoad(50, NORTH, EAST, 30, 30));
	Map.add(App->physics->CreateRoad(20, NORTH, NORTH, 30, 30, true, BLUE));
	Map.add(App->physics->CreateRoad(20, NORTH, NORTH, 30, 30, false, UNCOLORED, 20));
	Map.add(App->physics->CreateRoad(20, NORTH, NORTH, 30, 30, false, UNCOLORED, 15));
	Map.add(App->physics->CreateRoad(20, NORTH, NORTH, 30, 30, false, UNCOLORED, 10));
	Map.add(App->physics->CreateRoad(20, NORTH, NORTH, 30, 30, false, UNCOLORED, 5));
	Map.add(App->physics->CreateDemolitionBall(actual_pos.x, actual_pos.y + 10, actual_pos.z - 10, 3, 10.0f, RED));
	Map.add(App->physics->CreateDemolitionBall(actual_pos.x, actual_pos.y + 10, actual_pos.z, 3, 10.0f, RED));
	Map.add(App->physics->CreateRoad(50, NORTH, NORTH, 30, 30));
	Map.add(App->physics->CreateWall(10, 30, 1, actual_pos.x, actual_pos.y, actual_pos.z, EAST, GREEN));	//3rd wall
	Map.add(App->physics->CreateRoad(50, WEST, NORTH, 30, 30));
	Map.add(App->physics->CreateRoad(50, WEST, WEST, 30, 30));
	/*Map.add(App->physics->CreateRoad(50, SOUTH, EAST, 20, 20));
	Map.add(App->physics->CreateRoad(50, SOUTH, SOUTH, 20, 20));
	Map.add(App->physics->CreateRoad(50, SOUTH, SOUTH, 20, 20, false, UNCOLORED, 15));
	Map.add(App->physics->CreateRoad(50, SOUTH, SOUTH, 20, 20));
	Map.add(App->physics->CreateRoad(50, SOUTH, SOUTH, 20, 20, true, GREEN));
	Map.add(App->physics->CreateRoad(200, SOUTH, SOUTH, 20, 20));
	Map.add(App->physics->CreateRoad(50, WEST, SOUTH, 20, 20));
	Map.add(App->physics->CreateRoad(50, WEST, WEST, 20, 20));
	Map.add(App->physics->CreateRoad(50, WEST, WEST, 20, 20, false, UNCOLORED, 10));
	Map.add(App->physics->CreateRoad(50, WEST, WEST, 20, 20));
	Map.add(App->physics->CreateRoad(50, WEST, WEST, 20, 20, true, GREEN));
	Map.add(App->physics->CreateRoad(50, WEST, WEST, 20, 20));
	Map.add(App->physics->CreateRoad(50, NORTH, WEST, 20, 20));
	Map.add(App->physics->CreateRoad(50, NORTH, NORTH, 20, 20));
	*/

	/*Cube cube;
	cube.size.Set(50, 1, 50);
	cube.SetPos(App->scene_intro->actual_pos.x, App->scene_intro->actual_pos.y, App->scene_intro->actual_pos.z + 25);
	App->scene_intro->actual_pos.Set(App->scene_intro->actual_pos.x, App->scene_intro->actual_pos.y, App->scene_intro->actual_pos.z + 25);
	App->physics->AddBody(cube);*/
	//Cubes.add(cube);
	//Map.add(App->physics->CreateWall(10, 50, 1, 0, 0, NORTH, GREEN));	//We will need to use actual_pos to help positioning walls
	/*Cube cube2;
	cube2.size.Set(50, 1, 50);
	cube2.SetPos(0,0,0);
	cube2.SetRotation(45, vec3(1, 0, 0));
	App->physics->AddBody(cube2);
	Cubes.add(cube2);*/

	for (p2List_item<PhysBody3D*>* item = App->scene_intro->checkpoints.getFirst(); item; item = item->next)
	{
		item->data->SetAsSensor(true);
		item->data->collision_listeners.add(this);
	}

	//RED
	for (p2List_item<Cube>* item = Red_Cubes.getFirst(); item; item = item->next)
		item->data.color = Red;

	for (p2List_item<Sphere>* item = Red_Spheres.getFirst(); item; item = item->next)
		item->data.color = Red;
	//--

	//BLUE
	for (p2List_item<Cube>* item = Blue_Cubes.getFirst(); item; item = item->next)
		item->data.color = Blue;

	for (p2List_item<Sphere>* item = Blue_Spheres.getFirst(); item; item = item->next)
		item->data.color = Blue;
	//--

	//GREEN
	for (p2List_item<Cube>* item = Green_Cubes.getFirst(); item; item = item->next)
		item->data.color = Green;

	for (p2List_item<Sphere>* item = Green_Spheres.getFirst(); item; item = item->next)
		item->data.color = Green;
	//--

	for (p2List_item<Sphere>* item = Uncolored_Spheres.getFirst(); item; item = item->next)
		item->data.color = White;
	//item->data.color = Color({0,255,255});

	for (p2List_item<Cube>* item = Cubes.getFirst(); item; item = item->next)
		item->data.color = { 100, 100, 100, 1 };	//paint road

	for (p2List_item<Cube>* item = Uncolored_Cubes.getFirst(); item; item = item->next)
		item->data.color = White;		//paint walls
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
	//TRANSFORMATIONS
	p2List_item<Sphere>* spheres = Red_Spheres.getFirst();
	for (p2List_item<PhysBody3D*>* item = Red_Spheres_bodies.getFirst(); item; item = item->next)
	{
		item->data->GetTransform(&spheres->data.transform);
		spheres = spheres->next;
	}

	spheres = Blue_Spheres.getFirst();
	for (p2List_item<PhysBody3D*>* item = Blue_Spheres_bodies.getFirst(); item; item = item->next)
	{
		item->data->GetTransform(&spheres->data.transform);
		spheres = spheres->next;
	}

	spheres = Green_Spheres.getFirst();
	for (p2List_item<PhysBody3D*>* item = Green_Spheres_bodies.getFirst(); item; item = item->next)
	{
		item->data->GetTransform(&spheres->data.transform);
		spheres = spheres->next;
	}
	//--

	for (p2List_item<Cube>* item = Cubes.getFirst(); item; item = item->next)
		item->data.Render();

	for (p2List_item<Cube>* item = Uncolored_Cubes.getFirst(); item; item = item->next)
		item->data.Render();

	for (p2List_item<Sphere>* item = Uncolored_Spheres.getFirst(); item; item = item->next)
		item->data.Render();

	//RED
	if (App->player->red_off == false)
	{
		for (p2List_item<Cube>* item = Red_Cubes.getFirst(); item; item = item->next)
			item->data.Render();

		for (p2List_item<Sphere>* item = Red_Spheres.getFirst(); item; item = item->next)
			item->data.Render();
	}
	//--

	//GREEN
	if (App->player->green_off == false)
	{
		for (p2List_item<Cube>* item = Green_Cubes.getFirst(); item; item = item->next)
			item->data.Render();

		for (p2List_item<Sphere>* item = Green_Spheres.getFirst(); item; item = item->next)
			item->data.Render();

	}
	//--

	//BLUE
	if (App->player->blue_off == false)
	{
		for (p2List_item<Cube>* item = Blue_Cubes.getFirst(); item; item = item->next)
			item->data.Render();

		for (p2List_item<Sphere>* item = Blue_Spheres.getFirst(); item; item = item->next)
			item->data.Render();
	}
	//--

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2 = App->player->vehicle)
	{
		LOG("ayy lmao");
	}
}