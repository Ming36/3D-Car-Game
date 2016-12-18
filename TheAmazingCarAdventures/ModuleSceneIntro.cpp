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

	checkpoints.add(App->physics->CreateWallSensor(30, 1, actual_pos.x, actual_pos.y + 3, actual_pos.z + 15, NORTH));	//1rst sensor
	Map.add(App->physics->CreateRoad(70, EAST, EAST, 0, 30));
	Map.add(App->physics->CreateWall(10, 30, 1, actual_pos.x, actual_pos.y, actual_pos.z, NORTH, RED));		//1rst wall
	Map.add(App->physics->CreateRoad(10, EAST, EAST, 0, 30));
	Map.add(App->physics->CreateRoad(50, EAST, EAST, 30, 30, true, BLUE));
	Map.add(App->physics->CreateRoad(50, EAST, EAST, 30, 30));
	Map.add(App->physics->CreateWall(10, 30, 1, actual_pos.x, actual_pos.y, actual_pos.z, NORTH, BLUE));	//2nd wall
	//Map.add(App->physics->CreateRoad(50, EAST, EAST, 30, 30, false, UNCOLORED, 30));
	Map.add(App->physics->CreateRoad(50, EAST, EAST, 30, 30));
	//Map.add(App->physics->CreateDemolitionBall(actual_pos.x, actual_pos.y + 10, actual_pos.z - 10, 3, 10.0f, RED));
	//Map.add(App->physics->CreateDemolitionBall(actual_pos.x + 10, actual_pos.y + 10, actual_pos.z - 10, 3, 10.0f, RED));
	//checkpoints.add(App->physics->CreateWallSensor(30, 1, actual_pos.x, actual_pos.y, actual_pos.z, NORTH));	//1rst sensor
	checkpoints.add(App->physics->CreateWallSensor(30, 1, actual_pos.x, actual_pos.y + 3, actual_pos.z, NORTH));	//2nd sensor
	Map.add(App->physics->CreateRoad(50, NORTH, EAST, 30, 30));
	//checkpoints.add(App->physics->CreateWallSensor(30, 1, actual_pos.x - 20, actual_pos.y + 3, actual_pos.z, EAST));	//2nd sensor
	Map.add(App->physics->CreateRoad(20, NORTH, NORTH, 30, 30, true, BLUE));
	Map.add(App->physics->CreateRoad(20, NORTH, NORTH, 30, 30, false, UNCOLORED, 20));
	Map.add(App->physics->CreateRoad(20, NORTH, NORTH, 30, 30, false, UNCOLORED, 15));
	Map.add(App->physics->CreateRoad(20, NORTH, NORTH, 30, 30, false, UNCOLORED, 10));
	Map.add(App->physics->CreateRoad(20, NORTH, NORTH, 30, 30, false, UNCOLORED, 5));
	US_2nd_road_bodies.add(App->physics->CreateDemolitionBall(actual_pos.x, actual_pos.y + 10, actual_pos.z - 10, 3, RED, 2, 10.0f));
	US_2nd_road_bodies.add(App->physics->CreateDemolitionBall(actual_pos.x, actual_pos.y + 10, actual_pos.z, 3, GREEN, 2, 10.0f));	
	Map.add(App->physics->CreateRoad(50, NORTH, NORTH, 30, 30));
	checkpoints.add(App->physics->CreateWallSensor(30, 1, actual_pos.x, actual_pos.y + 3, actual_pos.z, EAST));	//3rd sensor
	Map.add(App->physics->CreateWall(10, 30, 1, actual_pos.x, actual_pos.y, actual_pos.z, EAST, GREEN));	//3rd wall
	Map.add(App->physics->CreateRoad(50, WEST, NORTH, 30, 30));
	Map.add(App->physics->CreateRoad(50, WEST, WEST, 30, 30));
	US_3rd_road_bodies.add(App->physics->CreateDemolitionBall(actual_pos.x, actual_pos.y + 10, actual_pos.z, 3, BLUE, 3, 10.0f));
	Map.add(App->physics->CreateRoad(50, WEST, WEST, 30, 30));
	Map.add(App->physics->CreateRoad(50, WEST, WEST, 30, 30));
	Map.add(App->physics->CreateRoad(50, WEST, WEST, 30, 30));
	checkpoints.add(App->physics->CreateWallSensor(30, 1, actual_pos.x, actual_pos.y + 3, actual_pos.z, SOUTH));	//4th sensor
	Map.add(App->physics->CreateRoad(50, SOUTH, WEST, 30, 30));
	Map.add(App->physics->CreateRoad(50, SOUTH, SOUTH, 30, 30));
	US_4th_road_bodies.add(App->physics->CreateDemolitionBall(actual_pos.x, actual_pos.y + 10, actual_pos.z, 3, GREEN, 4, 10.0f));
	Map.add(App->physics->CreateRoad(50, SOUTH, SOUTH, 30, 30));
	Map.add(App->physics->CreateRoad(50, SOUTH, SOUTH, 30, 30));
	checkpoints.add(App->physics->CreateWallSensor(30, 1, actual_pos.x + 10, actual_pos.y + 3, actual_pos.z, WEST));	//5th sensor



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

	for (p2List_item<PhysBody3D*>* item = checkpoints.getFirst(); item; item = item->next)
	{
		item->data->SetAsSensor(true);
		item->data->collision_listeners.add(this);
		checkpoints_bools.add(false);
		checkpoints_num++;
	}

	for (p2List_item<PhysBody3D*>* item = US_2nd_road_bodies.getFirst(); item; item = item->next)
		item->data->collision_listeners.add(this);

	for (p2List_item<PhysBody3D*>* item = US_3rd_road_bodies.getFirst(); item; item = item->next)
		item->data->collision_listeners.add(this);

	for (p2List_item<PhysBody3D*>* item = US_4th_road_bodies.getFirst(); item; item = item->next)
		item->data->collision_listeners.add(this);

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

	//UNCOLORED
	for (p2List_item<Sphere>* item = US_2nd_road.getFirst(); item; item = item->next)
		item->data.color = White;

	for (p2List_item<Sphere>* item = US_3rd_road.getFirst(); item; item = item->next)
		item->data.color = White;

	for (p2List_item<Sphere>* item = US_4th_road.getFirst(); item; item = item->next)
		item->data.color = White;
	//--
	//item->data.color = Color({0,255,255});

	for (p2List_item<Cube>* item = Cubes.getFirst(); item; item = item->next)
		item->data.color = { 100, 100, 100, 1 };	//paint road

	for (p2List_item<Cube>* item = Uncolored_Cubes.getFirst(); item; item = item->next)
		item->data.color = White;		//paint walls

	for (p2List_item<PhysBody3D*>* item = US_2nd_road_bodies.getFirst(); item; item = item->next)
		All_Spheres_bodies.add(item->data);

	for (p2List_item<PhysBody3D*>* item = US_3rd_road_bodies.getFirst(); item; item = item->next)
		All_Spheres_bodies.add(item->data);

	for (p2List_item<PhysBody3D*>* item = US_4th_road_bodies.getFirst(); item; item = item->next)
		All_Spheres_bodies.add(item->data);

	for (p2List_item<PhysBody3D*>* item = Red_Spheres_bodies.getFirst(); item; item = item->next)
		All_Spheres_bodies.add(item->data);

	for (p2List_item<PhysBody3D*>* item = Blue_Spheres_bodies.getFirst(); item; item = item->next)
		All_Spheres_bodies.add(item->data);

	for (p2List_item<PhysBody3D*>* item = Green_Spheres_bodies.getFirst(); item; item = item->next)
		All_Spheres_bodies.add(item->data);

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
		if (checkpoints_bools.getFirst()->next->data == true)
		{
			item->data->GetTransform(&spheres->data.transform);
			spheres = spheres->next;
		}
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

	spheres = US_2nd_road.getFirst();
	for (p2List_item<PhysBody3D*>* item = US_2nd_road_bodies.getFirst(); item; item = item->next)
	{
		item->data->GetTransform(&spheres->data.transform);
		spheres = spheres->next;
	}

	spheres = US_3rd_road.getFirst();
	for (p2List_item<PhysBody3D*>* item = US_3rd_road_bodies.getFirst(); item; item = item->next)
	{
		item->data->GetTransform(&spheres->data.transform);
		spheres = spheres->next;
	}

	spheres = US_4th_road.getFirst();
	for (p2List_item<PhysBody3D*>* item = US_4th_road_bodies.getFirst(); item; item = item->next)
	{
		item->data->GetTransform(&spheres->data.transform);
		spheres = spheres->next;
	}
	//--

	for (p2List_item<Cube>* item = Cubes.getFirst(); item; item = item->next)
		item->data.Render();

	for (p2List_item<Cube>* item = Uncolored_Cubes.getFirst(); item; item = item->next)
		item->data.Render();

	//UNCOLORED SPHERES
	for (p2List_item<Sphere>* item = US_2nd_road.getFirst(); item; item = item->next)
		item->data.Render();

	for (p2List_item<Sphere>* item = US_3rd_road.getFirst(); item; item = item->next)
		item->data.Render();

	for (p2List_item<Sphere>* item = US_4th_road.getFirst(); item; item = item->next)
		item->data.Render();
	//--

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

	//VICTORY?
	if (checkpoints_bools.find(false) == -1)
		App->player->victory = true;
	//--

	return UPDATE_CONTINUE;
}

void ModuleSceneIntro::OnCollision(PhysBody3D* body1, PhysBody3D* body2)
{
	if (body2 == App->player->vehicle && checkpoints.find(body1) != -1)
	{
		p2List_item<bool>* item_bools = checkpoints_bools.getFirst();
		for (p2List_item<PhysBody3D*>* item = checkpoints.getFirst(); item; item = item->next, item_bools = item_bools->next)
		{
			if (body1 == item->data)
			{
				item_bools->data = true;
				if (item->data == checkpoints.getFirst()->data)
				{
					App->player->timer.Start();
					checkpoints_bools.getLast()->data = false;
				}
			}
		}
	}
	else if (body2 == App->player->vehicle && All_Spheres_bodies.find(body1) != -1)
	{
		LOG("car crashed against sphere");
		//TODO: car lives?
	}
}