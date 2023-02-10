//Bilal Akbar
//Roll No 21i-1174
//Section Q
//Final project
#include "classes.h"

// prototypes
void displayingmenu();
void selecting_maps();
void selecting_cars();
void displaying_controls();
void sortingandsetting(Player&, HighScore[]);
void displaying_rematch();
void displaying_leaderboard();
void resetting_coordinates(Vehicle&,Vehicle &);
// Functions of Player class
// Static Memeber
int Player::player_count(0);
// Constructor and Destructors
Player::Player()
{
	if (player_count == 10) {
		cout << "Enter your name  : ";
		cin >> this->name;
	}
	
	score = 0;
	this->total_score = 0;
	this->selecting_car_type = false;
	player_count++;
}

// Setter and getters
void Player::Display()
{
	cout << "Score is " << total_score << endl;
}
void Player::setname(string temp_name)
{
	this->name = temp_name;
}
void Player::set_car_type(int temp_type)
{
	this->car_type = temp_type;
}
int Player::get_car_type()
{
	return this->car_type;
}
string Player::getname()
{
	return this->name;
}
void Player::setscore(int x)
{
	this->score = x;
}
int Player::getscore()
{
	return this->score;
}
//members of High score class
//static members
int HighScore::y_value(160);
//functions
void HighScore::Display()
{
	DrawString(40, y_value, this->getname(), colors[BLUE]);
	DrawString(150 , y_value, to_string(this->total_score), colors[BLUE]);
	y_value -= 15;
}
void HighScore::set_y_value()
{
	y_value = 160;
}


// Members of Vehicle class
// static member of vehicle class
int Vehicle::vehicle_count = 1;
// Constructors and Destructors

Vehicle ::Vehicle(int canon_size)
{
	this->id = vehicle_count;
	this->canon_is_fired = false;
	if (vehicle_count == 1) // static member vehicle count
	{
		srand(time(NULL));
		this->x_coordinate = ((rand() % 6) + 6);
		while ((int)x_coordinate % 2 != 0) // to get even
			this->x_coordinate = ((rand() % 6) + 6);
		this->y_coordinate = ((rand() % 160) + 12);
		while ((int)y_coordinate % 2 != 0) // to get even
			this->y_coordinate = ((rand() % 160) + 12);
		this->canon_x_coordinate = x_coordinate + 12;
		this->canon_y_coordinate = y_coordinate;
		cout << "The x coordinate of vehicle 1 is : " << x_coordinate << endl;
		cout << "The y coordinate of vehicle 1 : " << y_coordinate << endl;
		 Sleep(1000);
	}
	else if (vehicle_count == 2) // static member vehicle count
	{
		srand(time(NULL));
		this->x_coordinate = ((rand() % 10) + 188);
		while ((int)x_coordinate % 2 != 0) // to get even
			this->x_coordinate = ((rand() % 10) + 188);
		this->y_coordinate = ((rand() % 160) + 12);
		while ((int)y_coordinate % 2 != 0) // to get even
			this->y_coordinate = ((rand() % 160) + 12);
		this->canon_x_coordinate = x_coordinate - 12;
		this->canon_y_coordinate = y_coordinate;
		cout << "The x coordinate of vehicle 2 is : " << x_coordinate << endl;
		cout << "The y coordinate of vehicle 2 : " << y_coordinate << endl;
	}

	this->vehicle_count++;
	this->canon = new Canon(canon_size);
}
Vehicle::~Vehicle()
{
	delete canon;
}
// getters and setters
float Vehicle::getxcoordinate()
{
	return this->x_coordinate;
}
float Vehicle::getycoordinate()
{
	return this->y_coordinate;
}
void Vehicle::setxcoordinate(float x)
{
	this->x_coordinate = x;
}
void Vehicle::setycoordinate(float y)
{
	this->y_coordinate = y;
}
void Vehicle::setcanonxcoordinate(float x)
{
	this->canon_x_coordinate = x;
}
void Vehicle::setcanonycoordinate(float y)
{
	this->canon_y_coordinate = y;
}
float Vehicle::getcanonxcoordinate()
{
	return canon_x_coordinate;
}
float  Vehicle::getcanonycoordinate()
{
	return canon_y_coordinate;
}
void Vehicle::InitVehicle(int x, int y)
{
	this->x_coordinate = x;
	this->y_coordinate = y;
}
// Functions of Canon class

Canon ::Canon(int canon_size)
{
	//properties of medium canon
	this->size = canon_size;
	this->x_of_medium = 250;
	this->y_of_medium = 100;
	this->count_of_medium = 1;
	this->medium_is_fired = false;
	//properties of medium canon
	this->x_of_large = 250;
	this->y_of_large = 100;
	this->count_of_large = 0;
	this->large_is_fired = false;
}
//canon static member
bool Canon::sponing_large_canon = false;
bool Canon::map2_and_large = false;
bool Canon::map1_and_map3_and_large = false;
bool Canon::large_at_which_point = false;

// Functions of the Game class

// Constructor and Destructor
Game::Game(int w, int l)
{
	// level = l;
	wins = w;
}
// static variables
int Game::storing_random_level[3] = {0,0,0}; //generating random map for each level
int Game::level = 1; //level number
int Game::map; //map number
HighScore Game::top10[10]; // storing the highscore for the leaderboard
Vehicle Game::v1;																		  // vehicle 1
Vehicle Game::v2;																		  // vehicle 2
Player Game::p1;//Player 1
Player Game::p2;//Player 2
bool Game::leaderboard = false; // for the leaderboard window
bool Game::rematch = false; //for the rematch window
bool Game::getting_data_from_file = true; //getting data only once from the file
bool Game::playing_level[3] = { 0,0,0 };//when levle is being played (function in gamedisplay)
bool Game::showing_controls = false; //showing controls after choosing controls in menu
bool Game::menu = false;																	  // menu will display when this is false
bool Game::map_selection = false;														  // pvp (map selection will be displayed when it's false)
int Game::moving_x1 = 121, Game::moving_x2 = 179;										  // moving the vehicles in the menu
bool Game::initialzing_map_3 = false;													  // position of clouds in map 3
float Game::map3_cloud1_x, Game::map3_cloud1_y, Game::map3_cloud2_x, Game::map3_cloud2_y; // map 3 cloud varibles
int Game::car = 1;																		  // choosing car
bool Game::menu_flag1 = true, Game::menu_flag2 = true, Game::bool_map3_cloud1_x = true, Game::bool_map3_cloud1_y = true, Game::bool_map3_cloud2_x = true, Game::bool_map3_cloud2_y = true;
bool Game::multi_player = false, Game::single_player = false; // multiplayer and single player switching in the menu
// Getter and Setters
void Game::setWins(int w)
{
	wins = w;
}
// void Game::setlevel(int l)
//{
//	level = l;
// }
int Game::getWins() const
{
	return wins;
}
// int Game::getlevel() const
//{
//	return level;
// }
//  everything that will be displayed
void Game::GameDisplay() /**/
{
	glClearColor(1 /*Red Component*/, 1,
				 1 /*Blue Component*/, 1 /*Alpha component*/);
	cout<<p2.getname();
	glClear(GL_COLOR_BUFFER_BIT);
	if (getting_data_from_file)
	{
		fstream leaderboard;
		string temp;
		leaderboard.open("./leaderboard.txt", ios::in);
		for (int i = 0; i < 10; i++)
		{
			getline(leaderboard, temp, ',');
			top10[i].setname(temp); 
			getline(leaderboard, temp, '\n');
			top10[i].total_score=(stoi(temp));
		}
		getting_data_from_file = false;
	}
	if (menu == false) // displaying menu
	{
		displayingmenu();
	}
	else if (menu && leaderboard)
	{
		displaying_leaderboard();
	}
	else if (menu && map_selection == false && multi_player) // for multiplayer
	{
		selecting_maps();
	}
	else if (menu && map_selection && p1.selecting_car_type == false && multi_player)  //for multiplayer
	{
		selecting_cars();
	}
	else if (menu && map_selection && p1.selecting_car_type && p2.selecting_car_type == false && multi_player) //for multiplayer
	{
		selecting_cars();
	}

	else if (menu && map_selection && p1.selecting_car_type && p2.selecting_car_type && multi_player && rematch ==false) //for multiplayer
	{
		v1.bot_speed = 2;
		v1.canon->speed = 1;
		v2.canon->speed = 1;
		if (map == 1)
			map1();
		else if (map == 2)
			map2();
		else if (map == 3)
			map3();
		drawcanon();
		drawCar();
		if (p1.getscore() >= 10 || p2.getscore() >= 10)
		{
			rematch = true;
			if (p1.getscore() > 10)
				p1.setscore(10);
			else if (p2.getscore() > 10)
				p2.setscore(10);
		}
	}
	else if (menu&& map_selection && p1.selecting_car_type&& p2.selecting_car_type&& multi_player  && rematch) //for rematch
	{
		displaying_rematch();
	}
	else if (menu && p1.selecting_car_type == false && single_player)
	{
		selecting_cars();
	}
	else if (menu && p1.selecting_car_type && single_player)
	{
		if (level == 1) {
			if (playing_level[0] == false) {
				srand(time(NULL));
				storing_random_level[0] = rand() % 3 + 1; // getting random map
				p2.set_car_type (rand () % 3 + 1); // getiing random car
				playing_level[0] = true;
				v2.canon->speed = 0.5;
				v2.bot_speed = 0.25;
				v1.bot_speed = 2;
				v1.canon->speed = 1;
				v1.canon->count_of_medium = 1;
				v2.canon->count_of_large = 0;
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
			}
			if (storing_random_level[0] == 1)
			{
				map1();
				map = 1;
			}
			else if (storing_random_level[0] == 2){
				map2();
				map = 2;
				}
			else if (storing_random_level[0] == 3){
				map3();
				map = 3;
				}
			drawcanon();
			drawCar();
			if (p1.getscore() >= 10)
			{
				level = 2;
				if (p1.getscore() > 10)
					p1.setscore(10);
				p1.total_score = p1.total_score + p1.getscore();
				p1.setscore(0);
				p2.setscore(0);
				playing_level[0] = false;
				resetting_coordinates(v1, v2);
				if (p1.getscore() > 10)
					p1.setscore(10);
			}
			else if (p2.getscore() >= 10)
			{
				single_player = false;
				menu = false;
				p1.total_score = p1.total_score + p1.getscore();
				p1.setscore(0);
				p2.setscore(0);
				sortingandsetting(p1, top10);
				resetting_coordinates(v1, v2);
			}
		}
		else if (level == 2)
		{
			if (playing_level[1] == false) {
				srand(time(NULL));

				storing_random_level[1] = rand() % 3 + 1;//getting random map
				p2.set_car_type(rand() % 3 + 1); //getting random car
				while (storing_random_level[1] == storing_random_level[0]) // checking if the map is already used
					storing_random_level[1] = rand() % 3 + 1;
				playing_level[1] = true;
				v2.canon->speed = 0.6;
				v2.bot_speed = 0.5;
				v1.bot_speed = 2;
				v1.canon->speed = 1;
				v1.canon->count_of_medium = 1;
				v2.canon->count_of_large = 0;
				//sponing large canon
				Canon::map1_and_map3_and_large = false;
				Canon::map2_and_large = false;
				Canon::sponing_large_canon = false;
				Canon::large_at_which_point = false;
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
			}
			if (storing_random_level[1] == 1)
			{
				map1();
				map = 1;
			}
			else if (storing_random_level[1] == 2) {
				map2();
				map = 2;
			}
			else if (storing_random_level[1] == 3) {
				map3();
				map = 3;
			}
			drawcanon();
			drawCar();
			if (p1.getscore() >= 10)
			{	level = 3;
				if (p1.getscore() > 10)
				p1.setscore(10);
				p1.total_score = p1.total_score + p1.getscore();
				p1.setscore(0);
				p2.setscore(0);
				playing_level[0] = false;
				playing_level[1] = false;
				resetting_coordinates(v1, v2);
			}
			else if (p2.getscore() >= 10)
			{
				single_player = false;
				menu = false;
				p1.total_score = p1.total_score + p1.getscore();
				p1.setscore(0);
				p2.setscore(0);
				sortingandsetting(p1, top10);
				resetting_coordinates(v1, v2);
			}
		}
		else if (level == 3)
		{
			if (playing_level[2] == false) {
				srand(time(NULL));
				p2.set_car_type(rand() % 3 + 1); // getting random car
				storing_random_level[2] = rand() % 3 + 1; // getting random map
				while (storing_random_level[2] == storing_random_level[0] || storing_random_level[2] == storing_random_level[1]) //checking if the map is used before
					storing_random_level[2]  = rand() % 3 + 1;
				playing_level[2] = true;
				v2.canon->speed = 0.85;
				v2.bot_speed = 0.72;
				v1.bot_speed = 2;
				v1.canon->speed = 0.85;
				v1.canon->count_of_medium = 1;
				v2.canon->count_of_large = 0;
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				//sponing large canon
				Canon::map1_and_map3_and_large = false;
				Canon::map2_and_large = false;
				Canon::sponing_large_canon = false;
				Canon::large_at_which_point = false;
				
			}
			if (storing_random_level[2] == 1)
			{
				map1();
				map = 1;
			}
			else if (storing_random_level[2] == 2){
				map2();
				map = 2;

				}
			else if (storing_random_level[2] == 3){
				map3();
				map = 3;

				}
			drawcanon();
			drawCar();
			if (p1.getscore() >= 10 || p2.getscore() >= 10) {
				single_player = false;
				playing_level[0] = false;
				playing_level[1] = false;
				playing_level[2] = false;
				menu = false;
				if (p1.getscore() > 10)
					p1.setscore(10);
				p1.total_score = p1.total_score + p1.getscore();
				p1.setscore(0);
				p2.setscore(0);
				p1.selecting_car_type = false;
				sortingandsetting(p1, top10);
				resetting_coordinates(v1, v2);
				level = 1;
				Canon::map1_and_map3_and_large = false;
				Canon::map2_and_large = false;
				Canon::sponing_large_canon = false;
				Canon::large_at_which_point = false;
			}
		}
		
	}
	else if (menu && showing_controls)
	{
	displaying_controls();
 }
	glutSwapBuffers(); // do not modify this line..
}

void Game::displaying_vehicles_for_menu()
{
	// cars
	//  Tyres of 1st tank
	DrawCircle(moving_x1 + 2, 150 - 5, 1, colors[BLACK]);
	DrawCircle(moving_x1 + 6, 150 - 5, 1, colors[BLACK]);
	// first tank
	glBegin(GL_POLYGON);
	glColor3f(1, 0, 0); // green
	glVertex2f(moving_x1, 150 + 4);
	glVertex2f(moving_x1, 150 - 4);
	glVertex2f(moving_x1 + 8, 150 - 4);
	glVertex2f(moving_x1 + 8, 150 + 4);
	glColor3f(0, 0, 0); // light gray
	glVertex2f(moving_x1 + 8, 150 - 1);
	glVertex2f(moving_x1 + 12, 150 - 1);
	glVertex2f(moving_x1 + 12, 150 + 1);
	glVertex2f(moving_x1 + 8, 150 + 1);
	glEnd();
	// Helicopter
	DrawRectangle(moving_x2 + 1, 120 - 6, 2, 8, colors[RED]);
	DrawRectangle(moving_x2 + 1, 120 - 3, 4, 2, colors[RED]);
	DrawRectangle(moving_x2 + 4, 120 - 6, 8, 7, colors[RED]);
	DrawRectangle(moving_x2 + 7, 120, 2, 3, colors[BLUE]);
	DrawRectangle(moving_x2 + 5, 120 + 2, 6, 2, colors[BLUE]);
	DrawRectangle(moving_x2 + 8, 120 - 4, 5, 3, colors[RED]);
	// Airplane
	DrawRectangle(moving_x1 + 4, 90 - 2, 3, 7, colors[BLUE]); // wing1
	DrawRectangle(moving_x1 + 4, 90 - 6, 3, 7, colors[BLUE]); // wing2
	DrawRectangle(moving_x1, 90 - 3, 2, 8, colors[GREEN]);
	DrawRectangle(moving_x1, 90 - 3, 10, 5, colors[GREEN]);
	DrawRectangle(moving_x1 + 8, 90 - 2, 5, 3, colors[GREEN]);
	// tyres of secound tank
	DrawCircle(moving_x2 + 2, 60 - 5, 1, colors[BLACK]);
	DrawCircle(moving_x2 + 6, 60 - 5, 1, colors[BLACK]);
	// secound tank
	glBegin(GL_POLYGON);
	glColor3f(0.1, 0.4, 0.6);
	glVertex2f(moving_x2, 60 + 4);
	glVertex2f(moving_x2, 60 - 4);
	glVertex2f(moving_x2 + 8, 60 - 4);
	glVertex2f(moving_x2 + 8, 60 + 4);
	glColor3f(0.4, 0.1, 0);
	glVertex2f(moving_x2 + 8, 60 - 1);
	glVertex2f(moving_x2 + 12, 60 - 1);
	glVertex2f(moving_x2 + 12, 60 + 1);
	glVertex2f(moving_x2 + 8, 60 + 1);
	glEnd();
}

void Game::map1()
{
	// background colors
	DrawRectangle(0, 0, 206, 17, colors[DARK_VIOLET]);
	DrawRectangle(0, 16, 206, 17, colors[BROWN]);
	DrawRectangle(0, 32, 206, 17, colors[DARK_VIOLET]);
	DrawRectangle(0, 48, 206, 17, colors[BROWN]);
	DrawRectangle(0, 64, 206, 17, colors[DARK_VIOLET]);
	DrawRectangle(0, 80, 206, 17, colors[BROWN]);
	DrawRectangle(0, 96, 206, 17, colors[DARK_VIOLET]);
	DrawRectangle(0, 112, 206, 17, colors[BROWN]);
	DrawRectangle(0, 128, 206, 17, colors[DARK_VIOLET]);
	DrawRectangle(0, 144, 206, 17, colors[BROWN]);
	DrawRectangle(0, 160, 206, 17, colors[DARK_VIOLET]);
	// borders
	DrawRectangle(0, 0, 6, 66, colors[DARK_BLUE]);	   // left bottom
	DrawRectangle(0, 106, 6, 66, colors[DARK_BLUE]);   // left up
	DrawRectangle(0, 0, 80, 8, colors[DARK_BLUE]);	   // bottom left
	DrawRectangle(120, 0, 80, 8, colors[DARK_BLUE]);   // bottom right
	DrawRectangle(196, 0, 6, 66, colors[DARK_BLUE]);   // right_side bottom
	DrawRectangle(196, 106, 6, 66, colors[DARK_BLUE]); // right up
	DrawRectangle(0, 170, 80, 7, colors[DARK_BLUE]);   // up left
	DrawRectangle(120, 170, 86, 7, colors[DARK_BLUE]); // up right

	// score background color
	DrawRectangle(0, 176, 100, 100, colors[DARK_RED]);
	DrawRectangle(100, 176, 106, 100, colors[DARK_GREEN]);
	// Displaying scores
	if (single_player)
	{
		 string temp;
		 temp = p1.getname();
		 temp = temp + "=" +to_string(p1.getscore());
		DrawString(40, 185, temp, colors[WHITE]);
		temp = "bot";
		temp = temp + "=" + to_string(p2.getscore());
		DrawString(140, 185, temp, colors[WHITE]);
	}
	else if (multi_player)
	{
		string temp;
		temp = p1.getname();
		temp = temp + "=" + to_string(p1.getscore());
		DrawString(40, 185, temp, colors[WHITE]);
		temp = "(Player 2)";
		temp = temp + "=" + to_string(p2.getscore());
		DrawString(140, 185, temp, colors[WHITE]);

	}
}
void Game::map3()
{
	if (initialzing_map_3 == false)
	{

		map3_cloud1_x = GetRandInRange(0, 40);
		map3_cloud1_y = GetRandInRange(14, 116);
		Sleep(1000);
		map3_cloud2_x = GetRandInRange(100, 140);
		map3_cloud2_y = GetRandInRange(14, 116);
		initialzing_map_3 = true;
	}
	// background colors
	DrawRectangle(0, 0, 206, 176, colors[DARK_BLUE]);
	DrawRectangle(0, 176, 100, 100, colors[DARK_RED]);
	DrawRectangle(100, 176, 106, 100, colors[DARK_GREEN]);
	// Displaying scores
	if (single_player)
	{
		string temp;
		temp = p1.getname();
		temp = temp + "=" + to_string(p1.getscore());
		DrawString(40, 185, temp, colors[WHITE]);
		temp = "bot";
		temp = temp + "=" + to_string(p2.getscore());
		DrawString(140, 185, temp, colors[WHITE]);
	}
	else if (multi_player)
	{
		string temp;
		temp = p1.getname();
		temp = temp + "=" + to_string(p1.getscore());
		DrawString(40, 185, temp, colors[WHITE]);
		temp = "(Player 2)";
		temp = temp + "=" + to_string(p2.getscore());
		DrawString(140, 185, temp, colors[WHITE]);

	}

	/*DrawRectangle();
	DrawRectangle();*/
}
void Game::map2()
{
	// background colors
	DrawRectangle(0, 0, 200, 92, colors[DARK_SALMON]);
	DrawRectangle(0, 92, 210, 84, colors[DARK_ORANGE]);
	DrawRectangle(0, 176, 100, 100, colors[DARK_RED]);
	DrawRectangle(100, 176, 106, 100, colors[DARK_GREEN]);
	// player score
	if (single_player)
	{
		string temp;
		temp = p1.getname();
		temp = temp + "=" + to_string(p1.getscore());
		DrawString(40, 185, temp, colors[WHITE]);
		temp = "bot";
		temp = temp + "=" + to_string(p2.getscore());
		DrawString(140, 185, temp, colors[WHITE]);
	}
	else if (multi_player)
	{
		string temp;
		temp = p1.getname();
		temp = temp + "=" + to_string(p1.getscore());
		DrawString(40, 185, temp, colors[WHITE]);
		temp = "(Player 2)";
		temp = temp + "=" + to_string(p2.getscore());
		DrawString(140, 185, temp, colors[WHITE]);

	}
	// borders
	DrawRectangle(0, 0, 6, 176, colors[BROWN]);	  // left
	DrawRectangle(0, 0, 200, 6, colors[BROWN]);	  // bottom
	DrawRectangle(196, 0, 6, 176, colors[BROWN]); // right
	DrawRectangle(0, 174, 206, 6, colors[BROWN]); // up
	// obstacles
	DrawRectangle(25, 60, 10, 10, colors[BROWN]); // obstacle 1 (center x=30)
	DrawRectangle(34, 60, 10, 60, colors[BROWN]);
	DrawRectangle(25, 110, 10, 10, colors[BROWN]);
	DrawSquare(65, 85, 15, colors[BROWN]);		   // obstacle 2 (center x =65)
	DrawRectangle(95, 30, 10, 115, colors[BROWN]); // obstacle 3 (center x=95)
	DrawSquare(120, 85, 15, colors[BROWN]);		   // obstacle 4 (center x =130)
	DrawRectangle(164, 60, 10, 10, colors[BROWN]); // obstacle 5 (center x=155)
	DrawRectangle(155, 60, 10, 60, colors[BROWN]);
	DrawRectangle(164, 110, 10, 10, colors[BROWN]);
}
// cars

// choosing the right car
void Game::drawCar()
{
	if (p1.get_car_type() == 1)
		car1();
	else if (p1.get_car_type() == 2)
		car2();
	else if (p1.get_car_type() == 3)
		car3();
	if (p2.get_car_type() == 1)
		car1();
	else if (p2.get_car_type() == 2)
		car2();
	else if (p2.get_car_type() == 3)
		car3();
	if (map == 3)
	{
		// cloud 1
		DrawRectangle(map3_cloud1_x, map3_cloud1_y, 60, 30, colors[SKY_BLUE]);
		DrawRectangle(map3_cloud1_x + 5, map3_cloud1_y - 10, 50, 50, colors[SKY_BLUE]);
		DrawRectangle(map3_cloud1_x + 14, map3_cloud1_y - 20, 33, 70, colors[SKY_BLUE]);
		// cloud 2
		DrawRectangle(map3_cloud2_x, map3_cloud2_y, 60, 30, colors[SKY_BLUE]);
		DrawRectangle(map3_cloud2_x + 5, map3_cloud2_y - 10, 50, 50, colors[SKY_BLUE]);
		DrawRectangle(map3_cloud2_x + 14, map3_cloud2_y - 20, 33, 70, colors[SKY_BLUE]);
	}
	glutPostRedisplay();
}
void Game::drawcanon()
{
	//small canon
	DrawCircle(v1.getcanonxcoordinate(), v1.getcanonycoordinate(), 1, colors[GREEN]);
	DrawCircle(v2.getcanonxcoordinate(), v2.getcanonycoordinate(), 1, colors[RED]);
	//medium canon
	DrawCircle(v1.canon->x_of_medium, v1.canon->y_of_medium, 2, colors[GREEN]);
	DrawCircle(v2.canon->x_of_medium, v2.canon->y_of_medium, 2, colors[RED]);

	if (p1.getscore() != 0)
		Canon::sponing_large_canon = false;
		if (single_player && (map == 1 || map == 3) ) {
			if (Canon::map1_and_map3_and_large == false && p1.getscore() == 0) {
				srand(time(NULL));
				v1.canon->x_of_large = rand() % 160 + 15;
				v1.canon->y_of_large = rand() % 160 + 10;
				Canon::map1_and_map3_and_large = true;
				Canon::sponing_large_canon = true;
			}
			DrawSquare(v1.canon->x_of_large, v1.canon->y_of_large, 5, colors[GREEN]);
			//v1.canon->sponing_large_canon = true;
		}
		else if (single_player && p1.getscore() == 0 ) {
			
			if (Canon::map2_and_large == false && p1.getscore() == 0) {
				srand(time(NULL));
				v1.canon->x_of_large = rand() % 160 + 15;
				v1.canon->y_of_large = rand() % 25 + 12;
				Canon::map2_and_large = true;
				Canon::sponing_large_canon = true;
			}
			DrawSquare(v1.canon->x_of_large, v1.canon->y_of_large, 5, colors[GREEN]);
			//v1.canon->sponing_large_canon = true;
		}
		if (single_player && Canon::sponing_large_canon == false && v1.canon->large_is_fired == false)
		{
			v1.canon->x_of_large = 250;
			v1.canon->y_of_large = 100;
		}
}
void Game::car1()
{
	if (p1.get_car_type() == 1) {
		// Tyres of 1st tank
		DrawCircle(v1.getxcoordinate() + 2, v1.getycoordinate() - 5, 1, colors[BLACK]);
		DrawCircle(v1.getxcoordinate() + 6, v1.getycoordinate() - 5, 1, colors[BLACK]);
		// first tank
		glBegin(GL_POLYGON);
		glColor3f(1, 1, 1); // green
		glVertex2f(v1.getxcoordinate(), v1.getycoordinate() + 4);
		glVertex2f(v1.getxcoordinate(), v1.getycoordinate() - 4);
		glVertex2f(v1.getxcoordinate() + 8, v1.getycoordinate() - 4);
		glVertex2f(v1.getxcoordinate() + 8, v1.getycoordinate() + 4);
		glColor3f(0, 0, 0); // light gray
		glVertex2f(v1.getxcoordinate() + 8, v1.getycoordinate() - 1);
		glVertex2f(v1.getxcoordinate() + 12, v1.getycoordinate() - 1);
		glVertex2f(v1.getxcoordinate() + 12, v1.getycoordinate() + 1);
		glVertex2f(v1.getxcoordinate() + 8, v1.getycoordinate() + 1);
		glEnd();
	}
	if (p2.get_car_type() == 1)
	{
		// tyres of secound tank
		DrawCircle(v2.getxcoordinate() - 2, v2.getycoordinate() - 5, 1, colors[BLUE]);
		DrawCircle(v2.getxcoordinate() - 6, v2.getycoordinate() - 5, 1, colors[BLUE]);
		// secound tank
		glBegin(GL_POLYGON);
		glColor3f(1.0f, 0.0f, 0.051f); // red
		glVertex2f(v2.getxcoordinate(), v2.getycoordinate() + 4);
		glVertex2f(v2.getxcoordinate(), v2.getycoordinate() - 4);
		glColor3f(0, 1, 1); // sky blue
		glVertex2f(v2.getxcoordinate() - 8, v2.getycoordinate() - 4);
		glVertex2f(v2.getxcoordinate() - 8, v2.getycoordinate() - 1);
		glVertex2f(v2.getxcoordinate() - 12, v2.getycoordinate() - 1);
		glVertex2f(v2.getxcoordinate() - 12, v2.getycoordinate() + 1);
		glVertex2f(v2.getxcoordinate() - 8, v2.getycoordinate() + 1);
		glVertex2f(v2.getxcoordinate() - 8, v2.getycoordinate() + 4);
		glEnd();
	}
}
void Game::car2()
{
	if (p1.get_car_type() == 2)
	{
		// helicopter 1
		DrawRectangle(v1.getxcoordinate() + 1, v1.getycoordinate() - 6, 2, 8, colors[WHITE]);
		DrawRectangle(v1.getxcoordinate() + 1, v1.getycoordinate() - 3, 4, 2, colors[WHITE]);
		DrawRectangle(v1.getxcoordinate() + 4, v1.getycoordinate() - 6, 8, 7, colors[WHITE]);
		DrawRectangle(v1.getxcoordinate() + 7, v1.getycoordinate(), 2, 3, colors[BLUE]);
		DrawRectangle(v1.getxcoordinate() + 5, v1.getycoordinate() + 2, 6, 2, colors[BLUE]);
		DrawRectangle(v1.getxcoordinate() + 8, v1.getycoordinate() - 4, 5, 3, colors[WHITE]);
	}
	if (p2.get_car_type() == 2) {
		// helicopter 2
		DrawRectangle(v2.getxcoordinate() - 1, v2.getycoordinate() - 6, 2, 8, colors[BLUE]);
		DrawRectangle(v2.getxcoordinate() - 3, v2.getycoordinate() - 3, 4, 2, colors[BLUE]);
		DrawRectangle(v2.getxcoordinate() - 10, v2.getycoordinate() - 6, 8, 7, colors[BLUE]);
		DrawRectangle(v2.getxcoordinate() - 7, v2.getycoordinate(), 2, 3, colors[BLUE]);
		DrawRectangle(v2.getxcoordinate() - 9, v2.getycoordinate() + 2, 6, 2, colors[BLUE]);
		DrawRectangle(v2.getxcoordinate() - 12, v2.getycoordinate() - 4, 6, 3, colors[BLUE]);
	}
}
void Game::car3()

{
	if (p1.get_car_type() == 3) {
		// airplane 1
		DrawRectangle(v1.getxcoordinate() + 4, v1.getycoordinate() - 2, 3, 7, colors[YELLOW]); // wing1
		DrawRectangle(v1.getxcoordinate() + 4, v1.getycoordinate() - 6, 3, 7, colors[YELLOW]); // wing2
		DrawRectangle(v1.getxcoordinate(), v1.getycoordinate() - 3, 2, 8, colors[WHITE]);
		DrawRectangle(v1.getxcoordinate() + 8, v1.getycoordinate() - 2, 5, 3, colors[YELLOW]); // NOZZEL
		DrawRectangle(v1.getxcoordinate(), v1.getycoordinate() - 3, 10, 5, colors[WHITE]);
	}
	if (p2.get_car_type() == 3) {
		// airplane 2
		DrawRectangle(v2.getxcoordinate() - 5, v2.getycoordinate() - 2, 3, 7, colors[PURPLE]); // wing1
		DrawRectangle(v2.getxcoordinate() - 5, v2.getycoordinate() - 6, 3, 7, colors[PURPLE]); // wing2
		DrawRectangle(v2.getxcoordinate(), v2.getycoordinate() - 3, 2, 8, colors[YELLOW]);
		DrawRectangle(v2.getxcoordinate() - 11, v2.getycoordinate() - 2, 5, 3, colors[PURPLE]); // NOZZel
		DrawRectangle(v2.getxcoordinate() - 8, v2.getycoordinate() - 3, 10, 5, colors[YELLOW]);
	}
}

void Game::NonPrintableKeys(int key, int x, int y)
{
	if (menu && ((map_selection && multi_player && p1.selecting_car_type && p2.selecting_car_type) || single_player)){
		//small canon,others canon are in printable keys
		if (key == GLUT_KEY_CTRL_R)
		{
			v1.canon_is_fired = true;
		}
		if (key == GLUT_KEY_LEFT /*GLUT_KEY_LEFT is constant and contains ASCII for left arrow key*/)
		{
			// what to do when left key is pressed...
			v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
			
			if (map == 1)
			{
				// collision with each other
				if ((v1.getxcoordinate() - 2  <= v2.getxcoordinate() && v1.getxcoordinate()  + 2 >= v2.getxcoordinate())&& (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				// passing through the given space
				if (v1.getxcoordinate() <= -12 && (v1.getycoordinate() >= 72 && v1.getycoordinate() <= 102))
					v1.setxcoordinate(200);
				// collision with boundries
				if (v1.getxcoordinate() <= 4 && (v1.getycoordinate() >= 0 && v1.getycoordinate() <= 71))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				else if (v1.getxcoordinate() <= 4 && (v1.getycoordinate() >= 103 && v1.getycoordinate() <= 172))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				else if (v1.getxcoordinate() < 80 && (v1.getycoordinate() < 13))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				else if (v1.getxcoordinate() < 80 && (v1.getycoordinate() > 166))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
			}
			if (map == 3)
			{
				if (v1.getxcoordinate() < -12)
					v1.setxcoordinate(200);
				// vehicle collision with each other
				if ((v1.getxcoordinate() - 2 <= v2.getxcoordinate() && v1.getxcoordinate() + 2 >= v2.getxcoordinate()) && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
					v1.setxcoordinate(v1.getxcoordinate() + 2);
			}
			else if (map == 2)
			{
				if (v1.getxcoordinate() < 5)
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				// vehicle collision with each other
				if ((v1.getxcoordinate() - 2 <= v2.getxcoordinate() && v1.getxcoordinate() + 2 >= v2.getxcoordinate()) && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				// collision with obstacles if speed == 1 || speed ==2
				if (v1.getxcoordinate() == 42 && (v1.getycoordinate() >= 57 && v1.getycoordinate() <= 125))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				else if (v1.getxcoordinate() == 78 && (v1.getycoordinate() >= 82 && v1.getycoordinate() <= 104))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				else if (v1.getxcoordinate() == 102 && (v1.getycoordinate() >= 28 && v1.getycoordinate() <= 148))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				else if (v1.getxcoordinate() == 132 && (v1.getycoordinate() >= 82 && v1.getycoordinate() <= 102))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				else if (v1.getxcoordinate() == 172 && (v1.getycoordinate() >= 108 && v1.getycoordinate() <= 124))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				else if (v1.getxcoordinate() == 162 && (v1.getycoordinate() >= 76 && v1.getycoordinate() <= 106))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
				else if (v1.getxcoordinate() == 172 && (v1.getycoordinate() >= 58 && v1.getycoordinate() <= 74))
					v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
			}
			//canon positioning
			if (v1.canon_is_fired == false) {
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
			}
			cout << "x1 : " << v1.getxcoordinate() << endl;
		}
		else if (key == GLUT_KEY_RIGHT /*GLUT_KEY_RIGHT is constant and contains ASCII for right arrow key*/)
		{
			v1.setxcoordinate(v1.getxcoordinate() + v1.bot_speed);
			
			if (map == 1)
			{
				// collision with each other
				if ((v1.getxcoordinate() + 25 >= v2.getxcoordinate() && v1.getxcoordinate() + 23 <=v2.getxcoordinate() ) && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
				{
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				}
				// passing through the given space
				if (v1.getxcoordinate() >= 200 && (v1.getycoordinate() >= 72 && v1.getycoordinate() <= 102))
					v1.setxcoordinate(-12);
				// collision with boundries
				if (v1.getxcoordinate() >= 184 && (v1.getycoordinate() >= 0 && v1.getycoordinate() <= 71))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				else if (v1.getxcoordinate() >= 184 && (v1.getycoordinate() >= 103 && v1.getycoordinate() <= 172))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				else if (v1.getxcoordinate() == 108 && (v1.getycoordinate() < 13))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				else if (v1.getxcoordinate() == 108 && (v1.getycoordinate() > 166))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
			}

			if (map == 3)
			{
				if (v1.getxcoordinate() > 210)
					v1.setxcoordinate(-10);
				// collision with each other
				if ((v1.getxcoordinate() + 25 >= v2.getxcoordinate() && v1.getxcoordinate() + 23 <= v2.getxcoordinate()) && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
				{
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				}
			}
			else if (map == 2)
			{
				if (v1.getxcoordinate() > 184)
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				// collision with each other
				if ((v1.getxcoordinate() + 25 >= v2.getxcoordinate() && v1.getxcoordinate() + 23 <= v2.getxcoordinate()) && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
				{
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				}
				// collision with obstacles
				if (v1.getxcoordinate() == 14 && (v1.getycoordinate() >= 58 && v1.getycoordinate() <= 74))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				else if (v1.getxcoordinate() == 24 && (v1.getycoordinate() >= 76 && v1.getycoordinate() <= 106))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				else if (v1.getxcoordinate() == 14 && (v1.getycoordinate() >= 108 && v1.getycoordinate() <= 124))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				else if (v1.getxcoordinate() == 54 && (v1.getycoordinate() >= 82 && v1.getycoordinate() <= 104))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				else if (v1.getxcoordinate() == 84 && (v1.getycoordinate() >= 28 && v1.getycoordinate() <= 148))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				else if (v1.getxcoordinate() == 110 && (v1.getycoordinate() >= 82 && v1.getycoordinate() <= 104))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
				else if (v1.getxcoordinate() == 144 && (v1.getycoordinate() >= 58 && v1.getycoordinate() <= 124))
					v1.setxcoordinate(v1.getxcoordinate() - v1.bot_speed);
			}
			//canon positioning
			if (v1.canon_is_fired == false) {
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
			}
			cout << "x1 : " << v1.getxcoordinate() << endl;
		}
		else if (key == GLUT_KEY_UP /*GLUT_KEY_UP is constant and contains ASCII for up arrow key*/)
		{

			v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);

			if (map == 1)
			{
				// collision with each other
				if ((v1.getycoordinate() + 11 >= v2.getycoordinate() && v1.getycoordinate() + 9 <= v2.getycoordinate()) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				// passing through the given space
				if (v1.getycoordinate() >= 174 && (v1.getxcoordinate() >= 80 && v1.getxcoordinate() <= 108))
					v1.setycoordinate(-4);
				// collision with boundries
				if (v1.getycoordinate() >= 168 && (v1.getxcoordinate() >= 0 && v1.getxcoordinate() <= 78))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				else if (v1.getycoordinate() >= 168 && (v1.getxcoordinate() >= 110 && v1.getxcoordinate() <= 184))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				else if (v1.getycoordinate() == 104 && (v1.getxcoordinate() <= 4))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				else if (v1.getycoordinate() == 104 && (v1.getxcoordinate() >= 184))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
			}
			if (map == 3)
			{
				if (v1.getycoordinate() > 172)
					v1.setycoordinate(-4);
				// collision with each other
				if ((v1.getycoordinate() + 12 >= v2.getycoordinate() && v1.getycoordinate() + 6 <= v2.getycoordinate()) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
			}
			if (map == 2)
			{
				if (v1.getycoordinate() > 171)
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				// collision with each other
				if ((v1.getycoordinate() + 12 >= v2.getycoordinate() && v1.getycoordinate() + 6 <= v2.getycoordinate()) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				// collision with the obstacles
				if (v1.getycoordinate() == 58 && (v1.getxcoordinate() >= 14 && v1.getxcoordinate() <= 43))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				else if (v1.getycoordinate() == 82 && (v1.getxcoordinate() >= 53 && v1.getxcoordinate() <= 79))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				else if (v1.getycoordinate() == 106 && (v1.getxcoordinate() >= 14 && v1.getxcoordinate() <= 22))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				else if (v1.getycoordinate() == 28 && (v1.getxcoordinate() > 83 && v1.getxcoordinate() <= 104))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				else if (v1.getycoordinate() == 82 && (v1.getxcoordinate() > 108 && v1.getxcoordinate() <= 134))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				else if (v1.getycoordinate() == 58 && (v1.getxcoordinate() >= 143 && v1.getxcoordinate() <= 173))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
				else if (v1.getycoordinate() == 106 && (v1.getxcoordinate() >= 164 && v1.getxcoordinate() <= 173))
					v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
			}
			//canon positioning
			if (v1.canon_is_fired == false) {
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
			}
			cout << "yI : " << v1.getycoordinate() << endl;
		}

		else if (key == GLUT_KEY_DOWN /*GLUT_KEY_DOWN is constant and contains ASCII for down arrow key*/)
		{
			v1.setycoordinate(v1.getycoordinate() - v1.bot_speed);
		
			if (map == 1)
			{
				// collision with each other
				if ((v1.getycoordinate() - 8 >= v2.getycoordinate() && v1.getycoordinate() - 10  <= v2.getycoordinate()) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				// passing through the given space
				if (v1.getycoordinate() <= -2 && (v1.getxcoordinate() >= 80 && v1.getxcoordinate() <= 108))
					v1.setycoordinate(172);
				// collision with boundries
				if (v1.getycoordinate() < 14 && (v1.getxcoordinate() >= 6 && v1.getxcoordinate() <= 79))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				else if (v1.getycoordinate() < 14 && (v1.getxcoordinate() >= 110 && v1.getxcoordinate() <= 184))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				else if (v1.getycoordinate() <= 71 && (v1.getxcoordinate() <= 4))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				else if (v1.getycoordinate() <= 71 && (v1.getxcoordinate() >= 184))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
			}
			if (map == 3)
			{
				if (v1.getycoordinate() < 0)
					v1.setycoordinate(172);
				// collision with each other
				if ((v1.getycoordinate() - 8 >= v2.getycoordinate() && v1.getycoordinate() - 10 <= v2.getycoordinate()) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
			}
			if (map == 2)
			{
				if (v1.getycoordinate() < 12)
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				// collision with each other
				if ((v1.getycoordinate() - 8 >= v2.getycoordinate() && v1.getycoordinate() - 10 <= v2.getycoordinate()) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				// collision with obstacles
				if (v1.getycoordinate() == 124 && (v1.getxcoordinate() >= 14 && v1.getxcoordinate() <= 43))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				else if (v1.getycoordinate() == 74 && (v1.getxcoordinate() >= 14 && v1.getxcoordinate() <= 22))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				else if (v1.getycoordinate() == 104 && (v1.getxcoordinate() >= 53 && v1.getxcoordinate() <= 79))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				else if (v1.getycoordinate() == 148 && (v1.getxcoordinate() > 83 && v1.getxcoordinate() <= 104))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				else if (v1.getycoordinate() == 104 && (v1.getxcoordinate() >= 108 && v1.getxcoordinate() <= 134))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				else if (v1.getycoordinate() == 124 && (v1.getxcoordinate() >= 143 && v1.getxcoordinate() <= 173))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
				else if (v1.getycoordinate() == 74 && (v1.getxcoordinate() >= 164 && v1.getxcoordinate() <= 173))
					v1.setycoordinate(v1.getycoordinate() + v1.bot_speed);
			}
			//canon positioning
			if (v1.canon_is_fired == false) {
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
			}
			cout << "yI : " << v1.getycoordinate() << endl;
		}
	}
	/* This function calls the Display function to redo the drawing. Whenever you need to redraw just call
	 * this function*/

	glutPostRedisplay();
}

void Game::PrintableKeys(unsigned char key, int x, int y)
{
	//medium canon of vehicle 1 
	if (key == '/' && v1.canon->count_of_medium <= 3)
	{
		v1.canon->medium_is_fired = true;
		v1.canon->x_of_medium = (v1.getxcoordinate() + 12);
		v1.canon->y_of_medium = (v1.getycoordinate());
		v1.canon->count_of_medium++;
	}
	if (key == '\'' && (v1.getxcoordinate() + 24 >=v1.canon->x_of_large  && v1.getxcoordinate() - 12 <=v1.canon->x_of_large) && (v1.getycoordinate() + 24 >= v1.canon->y_of_large && v1.getycoordinate() - 24 <= v1.canon->y_of_large) && Canon::sponing_large_canon)
	{
		Canon::sponing_large_canon = false;
		v1.canon->count_of_large = 1;
	}
	else if (key=='\'' && Canon::sponing_large_canon == false && v1.canon->count_of_large == 1 ) {
		v1.canon->large_is_fired = true;
		v1.canon->count_of_large = 0;
		v1.canon->x_of_large = v1.getxcoordinate() + 12;
		v1.canon->y_of_large = v1.getycoordinate();

	}
	if (menu == false)
	{
		if ((key == 27 || key == '5') && menu == false)
		{
			exit(1); // exit the program when escape key is pressed.
		}
		else if (key == '1' )
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			single_player = true;
			menu = true;
		}
		else if (key == '2' )
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			menu = true;
			multi_player = true;
			key = NULL;
		}
		else if (key == '3')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			menu = true;
			leaderboard = true;
		}
		else if (key == '4')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			menu = true; 
			showing_controls = true;
		}
	}
	else if (menu && leaderboard)
	{
		if (key == 27)
		{
			leaderboard = false;
			menu = false;
			PlaySound(TEXT("./SOUNDS/exit.wav"), NULL, SND_ASYNC);
		}
	}
	else if (menu && map_selection == false && multi_player)
	{
		if (key == '1')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			map = 1;
			map_selection = true;
			key = NULL;
		}
		else if (key == '2')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			map = 2;
			map_selection = true;

			key = NULL;
		}
		else if (key == '3')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			map = 3;
			map_selection = true;
			key = NULL;
		}
		else if (key == 27)
		{
			menu = false;
			multi_player = false;
			PlaySound(TEXT("./SOUNDS/exit.wav"), NULL, SND_ASYNC);
		}
	}
	else if (menu && map_selection && p1.selecting_car_type == false && multi_player)
	{
		if (key == '1')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			p1.set_car_type(1);
			p1.selecting_car_type = true;
			key = NULL;
		}
		else if (key == '2')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			p1.set_car_type(2);
			p1.selecting_car_type = true;
			key = NULL;
		}
		else if (key == '3')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			p1.set_car_type(3);
			p1.selecting_car_type = true;
			key = NULL;
		}
		else if (key == 27) {
			map_selection = false;
			PlaySound(TEXT("./SOUNDS/exit.wav"), NULL, SND_ASYNC);
		}
	}
	else if (menu && map_selection && p1.selecting_car_type && p2.selecting_car_type == false && multi_player)
	{
		if (key == '1')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			p2.set_car_type(1);
			p2.selecting_car_type = true;
			key = NULL;
		}
		else if (key == '2')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			p2.set_car_type(2);
			p2.selecting_car_type = true;
			key = NULL;
		}
		else if (key == '3')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			p2.set_car_type(3);
			p2.selecting_car_type = true;
			key = NULL;
		}
		else if (key == 27) {
			p1.selecting_car_type = false;
			PlaySound(TEXT("./SOUNDS/exit.wav"), NULL, SND_ASYNC);
		}
	}
	else if (menu && map_selection && p1.selecting_car_type && p2.selecting_car_type && multi_player && rematch == false)
	{
		if (key == 27)
		{
			map_selection = false;
			key = NULL;
			// resetting v1 coordinates
			v1.setxcoordinate((rand() % 6) + 6);
			while ((int)v1.getxcoordinate() % 2 != 0) // to get even
				v1.setxcoordinate((rand() % 6) + 6);
			v1.setycoordinate((rand() % 160) + 12);
			while ((int)v1.getycoordinate() % 2 != 0) // to get even
				v1.setycoordinate  ((rand() % 160) + 12);
			v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
			v1.setcanonycoordinate(v1.getycoordinate());
			Sleep(1000);
			// resetting v2 coordinates
			v2.setxcoordinate((rand() % 10) + 188);
			while ((int)v2.getxcoordinate() % 2 != 0) // to get even
				v2.setxcoordinate((rand() % 10) + 188);
			v2.setycoordinate((rand() % 160) + 12);
			while ((int)v2.getycoordinate() % 2 != 0) // to get even
				v2.setycoordinate  ((rand() % 160) + 12);
			v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
			v2.setcanonycoordinate(v2.getycoordinate());
			//playing sound
			PlaySound(TEXT("./SOUNDS/exit.wav"), NULL, SND_ASYNC);
		}
		else if (key == 'b' || key == 'B' ) // Key for firing small canon
		{
			v2.canon_is_fired = true;
		}
		else if (key == 'V' || key == 'v' && v2.canon->count_of_medium <= 3) //key for firing medium canon
		{
			v2.canon->medium_is_fired = true;
			v2.canon->x_of_medium = v2.getxcoordinate() - 12;
			v2.canon->y_of_medium = v2.getycoordinate();
			v2.canon->count_of_medium++;
		}
		//medium canon of 1st player
		else if (key == 'w' || key == 'W') // up
		{
			v2.setycoordinate(v2.getycoordinate() + 2);
			if (map == 1)
			{
				// collision with each other
				if (v1.getycoordinate() == v2.getycoordinate() + 10 && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v2.setycoordinate(v2.getycoordinate() - 2);
				// passing through the given space
				if (v2.getycoordinate() >= 174 && (v2.getxcoordinate() >= 80 + 12 && v2.getxcoordinate() <= 108 + 12))
					v2.setycoordinate(-4);
				// collision with boundries
				if (v2.getycoordinate() >= 166 && (v2.getxcoordinate() >= 0 + 12 && v2.getxcoordinate() <= 78 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
				else if (v2.getycoordinate() >= 166 && (v2.getxcoordinate() >= 110 + 12 && v2.getxcoordinate() <= 184 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
				else if (v2.getycoordinate() == 102 && (v2.getxcoordinate() <= 4 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
				else if (v2.getycoordinate() == 102 && (v2.getxcoordinate() >= 184 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
			}
			
			if (map == 3)
			{
				if (v2.getycoordinate() > 172)
					v2.setycoordinate(0);
				// collision with each other
				if (v1.getycoordinate() == v2.getycoordinate() + 10 && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v2.setycoordinate(v2.getycoordinate() - 2);
			}
			if (map == 2)
			{

				if (v2.getycoordinate() > 171)
					v2.setycoordinate(v2.getycoordinate() - 2);
				// collision with each other
				if (v1.getycoordinate() == v2.getycoordinate() + 10 && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v2.setycoordinate(v2.getycoordinate() - 2);
				// collsion with the obstacles
				if (v2.getycoordinate() == 58 && (v2.getxcoordinate() >= 14 + 12 && v2.getxcoordinate() <= 43 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
				else if (v2.getycoordinate() == 82 && (v2.getxcoordinate() >= 53 + 12 && v2.getxcoordinate() <= 79 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
				else if (v2.getycoordinate() == 106 && (v2.getxcoordinate() >= 14 + 12 && v2.getxcoordinate() <= 22 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
				else if (v2.getycoordinate() == 28 && (v2.getxcoordinate() > 83 + 12 && v2.getxcoordinate() <= 104 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
				else if (v2.getycoordinate() == 82 && (v2.getxcoordinate() >= 108 + 12 && v2.getxcoordinate() <= 134 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
				else if (v2.getycoordinate() == 58 && (v2.getxcoordinate() >= 143 + 12 && v2.getxcoordinate() <= 173 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
				else if (v2.getycoordinate() == 106 && (v2.getxcoordinate() >= 164 + 12 && v2.getxcoordinate() <= 173 + 12))
					v2.setycoordinate(v2.getycoordinate() - 2);
			}
			//small canon positioning
			if (v2.canon_is_fired == false) {
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
			}
			cout << "y2 : " << v2.getycoordinate() << endl;
		}
		else if (key == 's' || key == 'S') // down
		{
			v2.setycoordinate(v2.getycoordinate() - 2);
			
			if (map == 1)
			{
				// collision with each other
				if (v1.getycoordinate() == v2.getycoordinate() - 8 && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v2.setycoordinate(v2.getycoordinate() + 2);
				// passing through the given space
				if (v2.getycoordinate() <= -2 && (v2.getxcoordinate() >= 80 + 12 && v2.getxcoordinate() <= 108 + 12))
					v2.setycoordinate(172);
				// collision with boundries
				if (v2.getycoordinate() < 14 && (v2.getxcoordinate() >= 6 + 12 && v2.getxcoordinate() <= 79 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
				else if (v2.getycoordinate() < 14 && (v2.getxcoordinate() >= 110 + 12 && v2.getxcoordinate() <= 184 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
				else if (v2.getycoordinate() <= 71 && (v2.getxcoordinate() <= 4 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
				else if (v2.getycoordinate() <= 71 && (v2.getxcoordinate() >= 184 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
			}
			if (map == 3)
			{
				if (v2.getycoordinate() < -4)
					v2.setycoordinate(172);
				// collision with each other
				if (v1.getycoordinate() == v2.getycoordinate() - 8 && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v2.setycoordinate(v2.getycoordinate() + 2);
			}
			if (map == 2)
			{
				if (v2.getycoordinate() < 12)
					v2.setycoordinate(v2.getycoordinate() + 2);
				// collision with each other
				if (v1.getycoordinate() == v2.getycoordinate() - 8 && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
					v2.setycoordinate(v2.getycoordinate() + 2);
				if (v2.getycoordinate() == 124 && (v2.getxcoordinate() >= 14 + 12 && v2.getxcoordinate() <= 43 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
				else if (v2.getycoordinate() == 74 && (v2.getxcoordinate() >= 14 + 12 && v2.getxcoordinate() <= 22 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
				else if (v2.getycoordinate() == 104 && (v2.getxcoordinate() >= 53 + 12 && v2.getxcoordinate() <= 79 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
				else if (v2.getycoordinate() == 148 && (v2.getxcoordinate() > 83 + 12 && v2.getxcoordinate() <= 104 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
				else if (v2.getycoordinate() == 104 && (v2.getxcoordinate() >= 108 + 12 && v2.getxcoordinate() <= 134 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
				else if (v2.getycoordinate() == 124 && (v2.getxcoordinate() >= 143 + 12 && v2.getxcoordinate() <= 173 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
				else if (v2.getycoordinate() == 74 && (v2.getxcoordinate() >= 164 + 12 && v2.getxcoordinate() <= 173 + 12))
					v2.setycoordinate(v2.getycoordinate() + 2);
			}
			//canon positioning
			if (v2.canon_is_fired == false) {
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
			}
			cout << "y2 : " << v2.getycoordinate() << endl;
		}
		else if (key == 'a' || key == 'A') // left
		{
			v2.setxcoordinate(v2.getxcoordinate() - 2);
			
			if (map == 1)
			{
				// collision with each other
				if (v1.getxcoordinate() + 22 == v2.getxcoordinate() && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				// passing through the space
				if (v2.getxcoordinate() <= -10 && (v2.getycoordinate() >= 72 && v2.getycoordinate() <= 102))
					v2.setxcoordinate(210);
				// collision with boundries
				if (v2.getxcoordinate() <= 4 + 12 && (v2.getycoordinate() >= 0 && v2.getycoordinate() <= 71))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() <= 4 + 12 && (v2.getycoordinate() >= 103 && v2.getycoordinate() <= 172))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() < 80 + 12 && (v2.getycoordinate() < 13))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() < 80 + 12 && (v2.getycoordinate() > 166))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
			}
			if (map == 3)
			{
				//passing through the space
				if (v2.getxcoordinate() < -10)
					v2.setxcoordinate(200);
				// collision with each other
				if (v1.getxcoordinate() + 22 == v2.getxcoordinate() && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
			}
			if (map == 2)
			{
				//colision with the boundry
				if (v2.getxcoordinate() < 17)
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				// collision with each other
				if (v1.getxcoordinate() + 22 == v2.getxcoordinate() && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
					v2.setxcoordinate(v2.getxcoordinate() + 2);

				// collision with obstacles when speed  == 1 || speed == 2
				if (v2.getxcoordinate() == 42 + 12 && (v2.getycoordinate() >= 57 && v2.getycoordinate() <= 125))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() == 78 + 12 && (v2.getycoordinate() >= 82 && v2.getycoordinate() <= 104))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() == 102 + 12 && (v2.getycoordinate() >= 28 && v2.getycoordinate() <= 148))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() == 132 + 12 && (v2.getycoordinate() >= 82 && v2.getycoordinate() <= 102))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() == 172 + 12 && (v2.getycoordinate() >= 108 && v2.getycoordinate() <= 124))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() == 162 + 12 && (v2.getycoordinate() >= 76 && v2.getycoordinate() <= 106))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() == 172 + 12 && (v2.getycoordinate() >= 58 && v2.getycoordinate() <= 74))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
			}
			//canon positioning
			if (v2.canon_is_fired == false) {
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
			}
			cout << "x2 : " << v2.getxcoordinate() << endl;
		}
		else if (key == 'd' || key == 'D') // right
		{
			v2.setxcoordinate(v2.getxcoordinate() + 2);
			
			if (map == 1)
			{
				// collision with each other
				if (v1.getxcoordinate() + 2 == v2.getxcoordinate() && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				// passing through the space
				if (v2.getxcoordinate() >= 210 && (v2.getycoordinate() >= 72 && v2.getycoordinate() <= 102))
					v2.setxcoordinate(-2);
				// collision with boundries
				if (v2.getxcoordinate() >= 184 + 12 && (v2.getycoordinate() >= 0 && v2.getycoordinate() <= 71))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				else if (v2.getxcoordinate() >= 184 + 12 && (v2.getycoordinate() >= 103 && v2.getycoordinate() <= 172))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				else if (v2.getxcoordinate() == 108 + 14 && (v2.getycoordinate() < 13))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				else if (v2.getxcoordinate() == 108 + 14 && (v2.getycoordinate() > 166))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
			}
			if (map == 3)
			{
				if (v2.getxcoordinate() > 210)
					v2.setxcoordinate(-10);
				// collision with each other
				if (v1.getxcoordinate() + 2 == v2.getxcoordinate() && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
			}
			if (map == 2)
			{
				if (v2.getxcoordinate() > 196)
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				// collision with each other
				if (v1.getxcoordinate() + 2 == v2.getxcoordinate() && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				cout << "x2 : " << v2.getxcoordinate() << endl;
				// collision with the obstacles with speed == 1 || speed ==2
				if (v2.getxcoordinate() == 14 + 12 && (v2.getycoordinate() >= 58 && v2.getycoordinate() <= 74))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				else if (v2.getxcoordinate() == 24 + 12 && (v2.getycoordinate() >= 76 && v2.getycoordinate() <= 106))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				else if (v2.getxcoordinate() == 14 + 12 && (v2.getycoordinate() >= 108 && v2.getycoordinate() <= 124))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				else if (v2.getxcoordinate() == 54 + 12 && (v2.getycoordinate() >= 82 && v2.getycoordinate() <= 104))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				else if (v2.getxcoordinate() == 84 + 12 && (v2.getycoordinate() >= 28 && v2.getycoordinate() <= 148))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				else if (v2.getxcoordinate() == 110 + 12 && (v2.getycoordinate() >= 82 && v2.getycoordinate() <= 104))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
				else if (v2.getxcoordinate() == 144 + 12 && (v2.getycoordinate() >= 58 && v2.getycoordinate() <= 124))
					v2.setxcoordinate(v2.getxcoordinate() - 2);
			}
			//canon positioning
			if (v2.canon_is_fired == false) {
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
			}
		}
	}
	else if (menu && map_selection && p1.selecting_car_type && p2.selecting_car_type && multi_player  && rematch)
	{
		if (key == '1')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			map_selection = true;
			p1.selecting_car_type = false;
			p2.selecting_car_type = false;
			rematch = false;
			p1.setscore(0);
			p2.setscore(0);
			resetting_coordinates(v1, v2);
			v1.canon->count_of_medium = 0;
			v2.canon->count_of_medium = 0;
		}
		else if (key == '2')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			map_selection = false;
			p1.selecting_car_type = false;
			p2.selecting_car_type = false;
			multi_player = false;
			menu = false; 
			p1.setscore(0);
			p2.setscore(0);
			resetting_coordinates(v1, v2);
			v1.canon->count_of_medium = 0;
			v2.canon->count_of_medium = 0;

		}
	}
	else if (menu && p1.selecting_car_type == false && single_player)
	{
		if (key == '1')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			p1.set_car_type(1);
			p1.selecting_car_type = true;
			key = NULL;
		}
		else if (key == '2')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			p1.set_car_type(2);
			p1.selecting_car_type = true;
			key = NULL;
		}
		else if (key == '3')
		{
			PlaySound(TEXT("./SOUNDS/click.wav"), NULL, SND_ASYNC);
			p1.set_car_type(3);
			p1.selecting_car_type = true;
			key = NULL;
		}
		else if (key == 27) {
			menu = false;
			single_player = false;
			PlaySound(TEXT("./SOUNDS/exit.wav"), NULL, SND_ASYNC);
		}
	}
	else if (menu && showing_controls)
	{
		
		if (key == 27) {
			menu = false;
			showing_controls = false;
			PlaySound(TEXT("./SOUNDS/exit.wav"), NULL, SND_ASYNC);
		}
	}
	else if (menu && p1.selecting_car_type && single_player)
	{
		if (key == 27)
		{
			menu = false;
			p1.selecting_car_type = false;
			playing_level[0] = false;
			single_player = false;
			playing_level[1] = false;
			playing_level[2] = false;//
			v1.canon->count_of_medium = 0;
			v2.canon->count_of_medium = 0;
			//sorting the values
			sortingandsetting(p1, top10);
			resetting_coordinates(v1, v2);
			Canon::map1_and_map3_and_large = false;
			Canon::map2_and_large = false;
			Canon::sponing_large_canon = false;
			Canon::large_at_which_point = false;
			PlaySound(TEXT("./SOUNDS/exit.wav"), NULL, SND_ASYNC);
		}
	}
	glutPostRedisplay();
}
// moving the shapes
void Game::moveshapes()
{
	// menu cars
	if (moving_x1 < 180 && menu_flag1)
	{
		moving_x1 = moving_x1 + 1;
		if (moving_x1 >= 180)
			menu_flag1 = false;
	}
	else if (moving_x1 > 120 && !menu_flag1)
	{
		moving_x1 = moving_x1 - 1;
		if (moving_x1 <= 120)
			menu_flag1 = true;
	}
	if (moving_x2 < 180 && menu_flag2)
	{
		moving_x2 = moving_x2 + 1;
		if (moving_x2 >= 180)
			menu_flag2 = false;
	}
	else if (moving_x2 > 120 && !menu_flag2)
	{
		moving_x2 = moving_x2 - 1;
		if (moving_x2 <= 120)
			menu_flag2 = true;
	}
	if (map == 3)
	{
		// map 3 cloud 1 x
		if (map3_cloud1_x < 40 && bool_map3_cloud1_x)
		{
			map3_cloud1_x += 0.5;
			if (map3_cloud1_x >= 40)
				bool_map3_cloud1_x = false;
		}
		else if (map3_cloud1_x > 0 && !bool_map3_cloud1_x)
		{
			map3_cloud1_x -= 0.5;
			if (map3_cloud1_x <= 0)
				bool_map3_cloud1_x = true;
		}
		// map 3 cloud 1 y
		if (map3_cloud1_y < 116 && bool_map3_cloud1_y)
		{
			map3_cloud1_y += 0.5;
			if (map3_cloud1_y >= 116)
				bool_map3_cloud1_y = false;
		}
		else if (map3_cloud1_y > 14 && !bool_map3_cloud1_y)
		{
			map3_cloud1_y -= 0.5;
			if (map3_cloud1_y <= 14)
				bool_map3_cloud1_y = true;
		}
		// map 3 cloud 2 x
		if (map3_cloud2_x < 140 && bool_map3_cloud2_x)
		{
			map3_cloud2_x += 0.5;
			if (map3_cloud2_x >= 140)
				bool_map3_cloud2_x = false;
		}
		else if (map3_cloud2_x > 100 && !bool_map3_cloud2_x)
		{
			map3_cloud2_x -= 0.5;
			if (map3_cloud2_x <= 100)
				bool_map3_cloud2_x = true;
		}
		// map 3 cloud 2 y
		if (map3_cloud2_y < 116 && bool_map3_cloud2_y)
		{
			map3_cloud2_y += 0.5;
			if (map3_cloud2_y >= 116)
				bool_map3_cloud2_y = false;
		}
		else if (map3_cloud2_y > 14 && !bool_map3_cloud2_y)
		{
			map3_cloud2_y -= 0.5;
			if (map3_cloud2_y <= 14)
				bool_map3_cloud2_y = true;
		}
	}
	//small canon of 1st player
	if (v1.canon_is_fired)
	{
		v1.setcanonxcoordinate(v1.getcanonxcoordinate() + v1.canon->speed);
		if (map == 1)
		{
			// collision of canon with enemy
			if ((v1.getcanonxcoordinate() <= v2.getxcoordinate() - 12 && v1.getcanonxcoordinate() >= v2.getxcoordinate() - 14) && (v1.getcanonycoordinate() + 8 >= v2.getycoordinate() && v1.getcanonycoordinate() - 8 <= v2.getycoordinate()))
			{
				p1.setscore(p1.getscore() + 1);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/explosion.wav"), NULL, SND_ASYNC);
				//canon coordinates of v1
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
				// resetting v2 coordinates
				v2.setxcoordinate((rand() % 10) + 188);
				while ((int)v2.getxcoordinate() % 2 != 0) // to get even
					v2.setxcoordinate((rand() % 10) + 188);
				v2.setycoordinate((rand() % 160) + 12);
				while ((int)v2.getycoordinate() % 2 != 0) // to get even
					v2.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v2.canon_is_fired) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
				
			}
			// passing through the given space
			if (v1.getcanonxcoordinate() >= 200 && (v1.getcanonycoordinate() >= 72 && v1.getcanonycoordinate() <= 102))
			{
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			// collision with boundries
			if (v1.getcanonxcoordinate() >= 184 + 12 && (v1.getcanonycoordinate() >= 0 && v1.getcanonycoordinate() <= 71))
			{
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			else if (v1.getcanonxcoordinate() >= 184 + 12 && (v1.getcanonycoordinate() >= 103 && v1.getcanonycoordinate() <= 172))
			{
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			else if (v1.getcanonxcoordinate() == 108 + 12 && (v1.getcanonycoordinate() < 13))
			{
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			else if (v1.getcanonxcoordinate() == 108 + 12 && (v1.getcanonycoordinate() > 166))
			{
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}

		}
		else if (map == 2)
		{
			if (v1.getcanonxcoordinate() > 184 + 12) {

				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			// collision with each other
			if ((v1.getcanonxcoordinate() <= v2.getxcoordinate() - 12 && v1.getcanonxcoordinate() >= v2.getxcoordinate() - 14) && (v1.getcanonycoordinate() + 8 >= v2.getycoordinate() && v1.getcanonycoordinate() - 8 <= v2.getycoordinate()))
			{
				p1.setscore(p1.getscore() + 1);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/explosion.wav"), NULL, SND_ASYNC);
				//canon coordinates of v1
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
				// resetting v2 coordinates
				v2.setxcoordinate((rand() % 10) + 188);
				while ((int)v2.getxcoordinate() % 2 != 0) // to get even
					v2.setxcoordinate((rand() % 10) + 188);
				v2.setycoordinate((rand() % 160) + 12);
				while ((int)v2.getycoordinate() % 2 != 0) // to get even
					v2.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v2.canon_is_fired) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
			}
			// collision with obstacles
			if ((v1.getcanonxcoordinate() >= 14 + 12 && v1.getcanonxcoordinate() <= 14 + 13) && (v1.getcanonycoordinate() >= 58 + 4 && v1.getcanonycoordinate() <= 74 - 3)) {
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			else if ((v1.getcanonxcoordinate() >= 24 + 12 && v1.getcanonxcoordinate() <= 24 + 13) && (v1.getcanonycoordinate() >= 72 && v1.getcanonycoordinate() <= 109)) {
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			else if ((v1.getcanonxcoordinate() >= 14 + 12 && v1.getcanonxcoordinate() <= 14 + 13) && (v1.getcanonycoordinate() >= 108 + 2 && v1.getcanonycoordinate() <= 124 - 4))
			{
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			else if ((v1.getcanonxcoordinate() >= 54 + 12 && v1.getcanonxcoordinate() <= 54 + 13) && (v1.getcanonycoordinate() >= 82 + 4 && v1.getcanonycoordinate() <= 104 - 3))
			{
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			else if ((v1.getcanonxcoordinate() >= 82 + 12 && v1.getcanonxcoordinate() <= 82 + 13) && (v1.getcanonycoordinate() >= 28 + 4 && v1.getcanonycoordinate() <= 148 - 3))
			{
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			else if ((v1.getcanonxcoordinate() >= 110 + 12 && v1.getcanonxcoordinate() <= 110 + 13) && (v1.getcanonycoordinate() >= 82 + 4 && v1.getcanonycoordinate() <= 104 - 3))
			{
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			else if ((v1.getcanonxcoordinate() >= 144 + 12 && v1.getcanonxcoordinate() <= 144 + 13) && (v1.getcanonycoordinate() >= 58 + 4 && v1.getcanonycoordinate() <= 124 - 3))
			{
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}

		}
		else if (map == 3)
		{
			//passing through the space
			if (v1.getcanonxcoordinate() > 200) {
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
			}
			// collision with each other
			// collision of canon with enemy
			if ((v1.getcanonxcoordinate() <= v2.getxcoordinate() - 12 && v1.getcanonxcoordinate() >= v2.getxcoordinate() - 14) && (v1.getcanonycoordinate() + 8 >= v2.getycoordinate() && v1.getcanonycoordinate() - 8 <= v2.getycoordinate()))
			{
				p1.setscore(p1.getscore() + 1);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/explosion.wav"), NULL, SND_ASYNC);
				//canon coordinates of v1
				v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
				v1.setcanonycoordinate(v1.getycoordinate());
				v1.canon_is_fired = false;
				// resetting v2 coordinates
				v2.setxcoordinate((rand() % 10) + 188);
				while ((int)v2.getxcoordinate() % 2 != 0) // to get even
					v2.setxcoordinate((rand() % 10) + 188);
				v2.setycoordinate((rand() % 160) + 12);
				while ((int)v2.getycoordinate() % 2 != 0) // to get even
					v2.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v2.canon_is_fired) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
			}
		}
	}
	// medium canon of first player
	if (v1.canon->medium_is_fired) {
		v1.canon->x_of_medium = (v1.canon->x_of_medium + v1.canon->speed);
		if (map == 1)
		{
			// collision of canon with enemy
			if ((v1.canon->x_of_medium <= v2.getxcoordinate() - 12 && v1.canon->x_of_medium >= v2.getxcoordinate() - 14) && (v1.canon->y_of_medium + 8 >= v2.getycoordinate() && v1.canon->y_of_medium - 8 <= v2.getycoordinate()))
			{

				p1.setscore(p1.getscore() + 2);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/medium_and_large_explosion.wav"), NULL, SND_ASYNC);
				//medium canon coordinates of v1
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
				// resetting v2 coordinates
				v2.setxcoordinate((rand() % 10) + 188);
				while ((int)v2.getxcoordinate() % 2 != 0) // to get even
					v2.setxcoordinate((rand() % 10) + 188);
				v2.setycoordinate((rand() % 160) + 12);
				while ((int)v2.getycoordinate() % 2 != 0) // to get even
					v2.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v2.canon_is_fired) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}

			}
			// passing through the given space
			if (v1.canon->x_of_medium >= 200 && (v1.canon->y_of_medium >= 72 && v1.canon->y_of_medium <= 102))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			// collision with boundries
			if (v1.canon->x_of_medium >= 184 + 12 && (v1.canon->y_of_medium >= 0 && v1.canon->y_of_medium <= 71))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			else if (v1.canon->x_of_medium >= 184 + 12 && (v1.canon->y_of_medium >= 103 && v1.canon->y_of_medium <= 172))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			else if (v1.canon->x_of_medium == 108 + 12 && (v1.canon->x_of_medium < 13))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			else if (v1.canon->x_of_medium == 108 + 12 && (v1.canon->y_of_medium > 166))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}

		}
		else if (map == 2)
		{
			if (v1.canon->x_of_medium > 184 + 12) {

				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			// collision with each other
			if ((v1.canon->x_of_medium <= v2.getxcoordinate() - 12 && v1.canon->x_of_medium >= v2.getxcoordinate() - 14) && (v1.canon->y_of_medium + 8 >= v2.getycoordinate() && v1.canon->y_of_medium - 8 <= v2.getycoordinate()))
			{
				p1.setscore(p1.getscore() + 2);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/medium_and_large_explosion.wav"), NULL, SND_ASYNC);
				//canon coordinates of v1
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
				// resetting v2 coordinates
				v2.setxcoordinate((rand() % 10) + 188);
				while ((int)v2.getxcoordinate() % 2 != 0) // to get even
					v2.setxcoordinate((rand() % 10) + 188);
				v2.setycoordinate((rand() % 160) + 12);
				while ((int)v2.getycoordinate() % 2 != 0) // to get even
					v2.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v2.canon_is_fired) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
			}
			// collision with obstacles
			if ((v1.canon->x_of_medium >= 14 + 12 && v1.canon->x_of_medium <= 14 + 13) && (v1.canon->y_of_medium >= 58 + 4 && v1.canon->y_of_medium <= 74 - 3)) {
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			else if ((v1.canon->x_of_medium >= 24 + 12 && v1.canon->x_of_medium <= 24 + 13) && (v1.canon->y_of_medium >= 72 && v1.canon->y_of_medium <= 109)) {
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			else if ((v1.canon->x_of_medium >= 14 + 12 && v1.canon->x_of_medium <= 14 + 13) && (v1.canon->y_of_medium >= 108 + 2 && v1.canon->y_of_medium <= 124 - 4))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			else if ((v1.canon->x_of_medium >= 54 + 12 && v1.canon->x_of_medium <= 54 + 13) && (v1.canon->y_of_medium >= 82 + 4 && v1.canon->y_of_medium <= 104 - 3))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			else if ((v1.canon->x_of_medium >= 82 + 12 && v1.canon->x_of_medium <= 82 + 13) && (v1.canon->y_of_medium >= 28 + 4 && v1.canon->y_of_medium <= 148 - 3))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			else if ((v1.canon->x_of_medium >= 110 + 12 && v1.canon->x_of_medium <= 110 + 13) && (v1.canon->y_of_medium >= 82 + 4 && v1.canon->y_of_medium <= 104 - 3))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			else if ((v1.canon->x_of_medium >= 144 + 12 && v1.canon->x_of_medium <= 144 + 13) && (v1.canon->y_of_medium >= 58 + 4 && v1.canon->y_of_medium <= 124 - 3))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}

		}
		else if (map == 3)
		{
			//passing through the space
			if (v1.canon->x_of_medium > 200) {
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
			}
			// collision of canon with enemy
			if ((v1.canon->x_of_medium <= v2.getxcoordinate() - 12 && v1.canon->x_of_medium >= v2.getxcoordinate() - 14) && (v1.canon->y_of_medium + 8 >= v2.getycoordinate() && v1.canon->y_of_medium - 8 <= v2.getycoordinate()))
			{
				p1.setscore(p1.getscore() + 2);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/medium_and_large_explosion.wav"), NULL, SND_ASYNC);
				//canon coordinates of v1
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->medium_is_fired = false;
				// resetting v2 coordinates
				v2.setxcoordinate((rand() % 10) + 188);
				while ((int)v2.getxcoordinate() % 2 != 0) // to get even
					v2.setxcoordinate((rand() % 10) + 188);
				v2.setycoordinate((rand() % 160) + 12);
				while ((int)v2.getycoordinate() % 2 != 0) // to get even
					v2.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v2.canon_is_fired) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
			}
		}
	}
	//large canon of first player (only in single player mode)
	if (v1.canon->large_is_fired) {
		v1.canon->x_of_large = (v1.canon->x_of_large + v1.canon->speed);
		if (map == 1)
		{	
			// collision of canon with enemy
			if ((v1.canon->x_of_large <= v2.getxcoordinate() - 12 && v1.canon->x_of_large >= v2.getxcoordinate() - 14) && (v1.canon->y_of_large + 8 >= v2.getycoordinate() && v1.canon->y_of_large - 8 <= v2.getycoordinate()))
			{
				p1.setscore(p1.getscore() + 4);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/medium_and_large_explosion.wav"), NULL, SND_ASYNC);
				//medium canon coordinates of v1
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
				// resetting v2 coordinates
				v2.setxcoordinate((rand() % 10) + 188);
				while ((int)v2.getxcoordinate() % 2 != 0) // to get even
					v2.setxcoordinate((rand() % 10) + 188);
				v2.setycoordinate((rand() % 160) + 12);
				while ((int)v2.getycoordinate() % 2 != 0) // to get even
					v2.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v2.canon_is_fired) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
			}
			// passing through the given space
			if (v1.canon->x_of_large >= 200 && (v1.canon->y_of_large >= 72 && v1.canon->y_of_large <= 102))
			{
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
			}
			// collision with boundries
			if (v1.canon->x_of_large >= 184 + 12 && (v1.canon->y_of_large >= 0 && v1.canon->y_of_large <= 71))
			{
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
			}
			else if (v1.canon->x_of_large >= 184 + 12 && (v1.canon->y_of_large >= 103 && v1.canon->y_of_large <= 172))
			{
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
			}
			else if (v1.canon->x_of_large == 108 + 12 && (v1.getcanonycoordinate() < 13))
			{
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
			}
			else if (v1.canon->x_of_large == 108 + 12 && (v1.canon->y_of_large > 166))
			{
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
			}

		}
		else if (map == 2)
		{
			if (v1.canon->x_of_large > 184 + 12) {

				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->medium_is_fired = false;
			}
			// collision with each other
			if ((v1.canon->x_of_large <= v2.getxcoordinate() - 12 && v1.canon->x_of_large >= v2.getxcoordinate() - 14) && (v1.canon->y_of_large + 8 >= v2.getycoordinate() && v1.canon->y_of_large - 8 <= v2.getycoordinate()))
			{
				p1.setscore(p1.getscore() + 4);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/medium_and_large_explosion.wav"), NULL, SND_ASYNC);
				//canon coordinates of v1
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
				// resetting v2 coordinates
				v2.setxcoordinate((rand() % 10) + 188);
				while ((int)v2.getxcoordinate() % 2 != 0)
					v2.setxcoordinate((rand() % 10) + 188);
				v2.setycoordinate((rand() % 160) + 12);
				while ((int)v2.getycoordinate() % 2 != 0) // to get even
					v2.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v2.canon_is_fired) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
			}
			// collision with obstacles
			if ((v1.canon->x_of_large >= 14 + 12 && v1.canon->x_of_large <= 14 + 13) && (v1.canon->y_of_large >= 58 + 4 && v1.canon->y_of_large <= 74 - 3)) {
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
			}
			else if ((v1.canon->x_of_large >= 24 + 12 && v1.canon->x_of_large <= 24 + 13) && (v1.canon->y_of_large >= 72 && v1.canon->y_of_large <= 109)) {
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
			}
			else if ((v1.canon->x_of_medium >= 14 + 12 && v1.canon->x_of_large <= 14 + 13) && (v1.canon->y_of_large >= 108 + 2 && v1.canon->y_of_large <= 124 - 4))
			{
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
			}
			else if ((v1.canon->x_of_large >= 54 + 12 && v1.canon->x_of_large <= 54 + 13) && (v1.canon->y_of_large >= 82 + 4 && v1.canon->y_of_large <= 104 - 3))
			{
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
			}
			else if ((v1.canon->x_of_large >= 82 + 12 && v1.canon->x_of_large <= 82 + 13) && (v1.canon->y_of_large >= 28 + 4 && v1.canon->y_of_large <= 148 - 3))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->large_is_fired = false;
			}
			else if ((v1.canon->x_of_large >= 110 + 12 && v1.canon->x_of_large <= 110 + 13) && (v1.canon->y_of_large >= 82 + 4 && v1.canon->y_of_large <= 104 - 3))
			{
				v1.canon->x_of_medium = 250;
				v1.canon->y_of_medium = 200;
				v1.canon->large_is_fired = false;
			}
			else if ((v1.canon->x_of_large >= 144 + 12 && v1.canon->x_of_large <= 144 + 13) && (v1.canon->y_of_large >= 58 + 4 && v1.canon->y_of_large <= 124 - 3))
			{
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->large_is_fired = false;
			}

		}
		else if (map == 3)
		{
			//passing through the space
			if (v1.canon->x_of_large > 200) {
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->medium_is_fired = false;
			}
			// collision with each other
			// collision of canon with enemy
			if ((v1.canon->x_of_large <= v2.getxcoordinate() - 12 && v1.canon->x_of_large >= v2.getxcoordinate() - 14) && (v1.canon->y_of_large + 8 >= v2.getycoordinate() && v1.canon->y_of_large - 8 <= v2.getycoordinate()))
			{
				p1.setscore(p1.getscore() + 4);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/medium_and_large_explosion.wav"), NULL, SND_ASYNC);
				//canon coordinates of v1
				v1.canon->x_of_large = 250;
				v1.canon->y_of_large = 200;
				v1.canon->medium_is_fired = false;
				// resetting v2 coordinates
				v2.setxcoordinate((rand() % 10) + 188);
				while ((int)v2.getxcoordinate() % 2 != 0) // to get even
					v2.setxcoordinate((rand() % 10) + 188);
				v2.setycoordinate((rand() % 160) + 12);
				while ((int)v2.getycoordinate() % 2 != 0) // to get even
					v2.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v2.canon_is_fired) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
			}
		}
	}

	if (v2.canon_is_fired)
	{
		//canon speed
		v2.setcanonxcoordinate(v2.getcanonxcoordinate() - v2.canon->speed);
		if (map == 1) {
			// collision of canon with the other vehicle
			if ((v1.getxcoordinate() + 12 <= v2.getcanonxcoordinate() && v1.getxcoordinate() + 13 >=v2.getcanonxcoordinate()) && (v1.getycoordinate() + 8 >= v2.getcanonycoordinate() && v1.getycoordinate() - 8 <= v2.getcanonycoordinate()))
			{

				v2.canon_is_fired = false;
				p2.setscore(p2.getscore() + 1);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/explosion.wav"), NULL, SND_ASYNC);
				// resetting v1 coordinates
				v1.setxcoordinate((rand() % 6) + 6);
				while ((int)v1.getxcoordinate() % 2 != 0) // to get even
					v1.setxcoordinate((rand() % 6) + 6);
				v1.setycoordinate((rand() % 160) + 12);
				while ((int)v1.getycoordinate() % 2 != 0) // to get even
					v1.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v1.canon_is_fired) {
					v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
					v1.setcanonycoordinate(v1.getycoordinate());
				}
				//v2 canon coordinates 
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());

			}
			// passing through the space
			if (v2.getcanonxcoordinate() <= 0 && (v2.getcanonycoordinate() >= 72 && v2.getcanonycoordinate() <= 102))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;

			}
			// collision with boundries
			if (v2.getcanonxcoordinate() <= 4  && (v2.getcanonycoordinate() >= 0 && v2.getcanonycoordinate() <= 71))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;

			}
			else if (v2.getcanonxcoordinate() <= 4  && (v2.getcanonycoordinate() >= 103 && v2.getcanonycoordinate() <= 172))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
			else if (v2.getcanonxcoordinate() < 80  && (v2.getcanonycoordinate() < 13))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
			else if (v2.getcanonxcoordinate() < 80  && (v2.getcanonycoordinate() > 166))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
		}
		else if (map == 2)
		{
			//colision with the boundry
			if (v2.getcanonxcoordinate() < 17 - 12)
				{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
			// collision of canon with the other vehicle
			if ((v1.getxcoordinate() + 12 <= v2.getcanonxcoordinate() && v1.getxcoordinate() + 13 >= v2.getcanonxcoordinate()) && (v1.getycoordinate() + 8 >= v2.getcanonycoordinate() && v1.getycoordinate() - 8 <= v2.getcanonycoordinate()))
			{
				v2.canon_is_fired = false;
				p2.setscore(p2.getscore() + 1);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/explosion.wav"), NULL, SND_ASYNC);
				// resetting v1 coordinates
				v1.setxcoordinate((rand() % 6) + 6);
				while ((int)v1.getxcoordinate() % 2 != 0) // to get even
					v1.setxcoordinate((rand() % 6) + 6);
				v1.setycoordinate((rand() % 160) + 12);
				while ((int)v1.getycoordinate() % 2 != 0) // to get even
					v1.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v1.canon_is_fired) {
					v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
					v1.setcanonycoordinate(v1.getycoordinate());
				}
				//v2 canon coordinates 
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());

			}
			// collision with obstacles when speed  == 1 || speed == 2
			if ((v2.getcanonxcoordinate() >= 42 && v2.getcanonxcoordinate()<=43) &&   (v2.getcanonycoordinate() >= 57 + 4 && v2.getcanonycoordinate() <= 125 - 4))
				{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
			else if ((v2.getcanonxcoordinate() >=78  && v2.getcanonxcoordinate() <= 79) && (v2.getcanonycoordinate() >= 82 + 4 && v2.getcanonycoordinate() <= 104 - 4))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
			else if ((v2.getcanonxcoordinate() >= 102 && v2.getcanonxcoordinate() <= 103) && (v2.getcanonycoordinate() >= 28 + 4 && v2.getcanonycoordinate() <= 148 - 4))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
			else if ((v2.getcanonxcoordinate() >= 132 && v2.getcanonxcoordinate() <= 133) && (v2.getcanonycoordinate() >= 82 + 4 && v2.getcanonycoordinate() <= 102 - 4))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
			else if ((v2.getcanonxcoordinate() >= 172 && v2.getcanonxcoordinate() <= 173) && (v2.getcanonycoordinate() >= 108 + 1 && v2.getcanonycoordinate() <= 124 - 4))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
			else if ((v2.getcanonxcoordinate() >= 162 && v2.getcanonxcoordinate() <= 163) && (v2.getcanonycoordinate() >= 76 - 4  && v2.getcanonycoordinate() <= 106 + 2 ))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
			else if ((v2.getcanonxcoordinate() >= 172 && v2.getcanonxcoordinate() <= 173) && (v2.getcanonycoordinate() >= 58 + 2 && v2.getcanonycoordinate() <= 74 - 4))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}

		}
		else if (map == 3)
		{
			if (v2.getcanonxcoordinate() <= 0)
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon_is_fired = false;
			}
			if ((v1.getxcoordinate() + 12 <= v2.getcanonxcoordinate() && v1.getxcoordinate() + 13 >= v2.getcanonxcoordinate()) && (v1.getycoordinate() + 8 >= v2.getcanonycoordinate() && v1.getycoordinate() - 8 <= v2.getcanonycoordinate()))
			{
				v2.canon_is_fired = false;
				//playing the sound
				PlaySound(TEXT("./SOUNDS/explosion.wav"), NULL, SND_ASYNC);
				p2.setscore(p2.getscore() + 1);
				// resetting v1 coordinates
				v1.setxcoordinate((rand() % 6) + 6);
				while ((int)v1.getxcoordinate() % 2 != 0) // to get even
					v1.setxcoordinate((rand() % 6) + 6);
				v1.setycoordinate((rand() % 160) + 12);
				while ((int)v1.getycoordinate() % 2 != 0) // to get even
					v1.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v1.canon_is_fired) {
					v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
					v1.setcanonycoordinate(v1.getycoordinate());
				}
				//v2 canon coordinates 
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.setcanonycoordinate(v2.getycoordinate());

			}
		}
	}
	//medium canon of secound player
	if (v2.canon->medium_is_fired)
	{//canon speed
		v2.canon->x_of_medium = (v2.canon->x_of_medium - v2.canon->speed);
		if (map == 1) {
			// collision of canon with the other vehicle
			if ((v1.getxcoordinate() + 12 <= v2.canon->x_of_medium && v1.getxcoordinate() + 13 >= v2.canon->x_of_medium) && (v1.getycoordinate() + 8 >= v2.canon->y_of_medium && v1.getycoordinate() - 8 <= v2.canon->y_of_medium))
			{
				v2.canon->medium_is_fired = false;
				p2.setscore(p2.getscore() + 2);
				//playing the sound
				PlaySound(TEXT("./SOUNDS/medium_and_large_explosion.wav"), NULL, SND_ASYNC);
				// resetting v1 coordinates
				v1.setxcoordinate((rand() % 6) + 6);
				while ((int)v1.getxcoordinate() % 2 != 0) // to get even
					v1.setxcoordinate((rand() % 6) + 6);
				v1.setycoordinate((rand() % 160) + 12);
				while ((int)v1.getycoordinate() % 2 != 0) // to get even
					v1.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v1.canon->medium_is_fired ) {
					v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
					v1.setcanonycoordinate(v1.getycoordinate());
				}
				//v2 canon coordinates 
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;

			}
			// passing through the space
			if (v2.canon->x_of_medium <= 0 && (v2.canon->y_of_medium >= 72 && v2.canon->y_of_medium <= 102))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;

			}
			// collision with boundries
			if (v2.canon->x_of_medium <= 4 && (v2.canon->y_of_medium >= 0 && v2.canon->y_of_medium <= 71))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;

			}
			else if (v2.canon->x_of_medium <= 4 && (v2.canon->y_of_medium >= 103 && v2.canon->y_of_medium <= 172))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}
			else if (v2.canon->x_of_medium < 80 && (v2.canon->y_of_medium < 13))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}
			else if (v2.canon->x_of_medium < 80 && (v2.canon->y_of_medium > 166))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}
		}
		else if (map == 2)
		{
			//colision with the boundry
			if (v2.canon->x_of_medium < 17 - 12)
			{
				v2.canon->x_of_medium = 250 ;
				v2.setcanonycoordinate(v2.getycoordinate());
				v2.canon->medium_is_fired = false;
			}
			// collision of canon with the other vehicle
			if ((v1.getxcoordinate() + 12 <= v2.canon->x_of_medium && v1.getxcoordinate() + 13 >= v2.canon->x_of_medium) && (v1.getycoordinate() + 8 >= v2.canon->y_of_medium && v1.getycoordinate() - 8 <= v2.canon->y_of_medium))
			{
				v2.canon->medium_is_fired = false;
				//playing the sound
				PlaySound(TEXT("./SOUNDS/medium_and_large_explosion.wav"), NULL, SND_ASYNC);
				p2.setscore(p2.getscore() + 2);
				// resetting v1 coordinates
				v1.setxcoordinate((rand() % 6) + 6);
				while ((int)v1.getxcoordinate() % 2 != 0) // to get even
					v1.setxcoordinate((rand() % 6) + 6);
				v1.setycoordinate((rand() % 160) + 12);
				while ((int)v1.getycoordinate() % 2 != 0) // to get even
					v1.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v1.canon->medium_is_fired) {
					v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
					v1.setcanonycoordinate(v1.getycoordinate());
				}
				//v2 canon coordinates 
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;

			}
			// collision with obstacles when speed  == 1 || speed == 2
			if ((v2.canon->x_of_medium >= 42 && v2.canon->x_of_medium <= 43) && (v2.canon->y_of_medium >= 57 + 4 && v2.canon->y_of_medium <= 125 - 4))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}
			else if ((v2.canon->x_of_medium >= 78 && v2.canon->x_of_medium <= 79) && (v2.canon->y_of_medium >= 82 + 4 && v2.canon->y_of_medium <= 104 - 4))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}
			else if ((v2.canon->x_of_medium >= 102 && v2.canon->x_of_medium <= 103) && (v2.canon->y_of_medium >= 28 + 4 && v2.canon->y_of_medium <= 148 - 4))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}
			else if ((v2.canon->x_of_medium >= 132 && v2.canon->x_of_medium <= 133) && (v2.canon->y_of_medium >= 82 + 4 && v2.canon->y_of_medium <= 102 - 4))
			{
				v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}
			else if ((v2.canon->x_of_medium >= 172 && v2.canon->x_of_medium <= 173) && (v2.canon->y_of_medium >= 108 + 1 && v2.canon->y_of_medium <= 124 - 4))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}
			else if ((v2.canon->x_of_medium >= 162 && v2.canon->x_of_medium <= 163) && (v2.canon->y_of_medium >= 76 - 4 && v2.canon->y_of_medium <= 106 + 2))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}
			else if ((v2.canon->x_of_medium >= 172 && v2.canon->x_of_medium <= 173) && (v2.canon->y_of_medium >= 58 + 2 && v2.canon->y_of_medium <= 74 - 4))
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}

		}
		else if (map == 3)
		{
			if (v2.canon->x_of_medium <= 0)
			{
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;
				v2.canon->medium_is_fired = false;
			}
			if ((v1.getxcoordinate() + 12 <= v2.canon->x_of_medium && v1.getxcoordinate() + 13 >= v2.canon->x_of_medium) && (v1.getycoordinate() + 8 >= v2.canon->y_of_medium && v1.getycoordinate() - 8 <= v2.canon->y_of_medium))
			{
				v2.canon->medium_is_fired = false;
				//playing the sound
				PlaySound(TEXT("./SOUNDS/medium_and_large_explosion.wav"), NULL, SND_ASYNC);
				p2.setscore(p2.getscore() + 2);
				// resetting v1 coordinates
				v1.setxcoordinate((rand() % 6) + 6);
				while ((int)v1.getxcoordinate() % 2 != 0) // to get even
					v1.setxcoordinate((rand() % 6) + 6);
				v1.setycoordinate((rand() % 160) + 12);
				while ((int)v1.getycoordinate() % 2 != 0) // to get even
					v1.setycoordinate((rand() % 160) + 12);
				//canon coordiantes
				if (!v1.canon->medium_is_fired) {
					v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
					v1.setcanonycoordinate(v1.getycoordinate());
				}
				//v2 canon coordinates 
				v2.canon->x_of_medium = 250 ;
				v2.canon->y_of_medium = 100;

			}
		}
	}
	
	//bot movement
	if (single_player)
	{
		if (map == 1)
		{
			//upward bot movement
				if (v2.getycoordinate()  <= v1.getycoordinate() ) {
					v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
					if (v2.canon_is_fired == false)
					{
						v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
						v2.setcanonycoordinate(v2.getycoordinate());
					}
					cout << "y2 up is " << v2.getycoordinate() << endl;
				}
				// collision with each other
				if ((v1.getycoordinate() <= v2.getycoordinate() + 11 && v1.getycoordinate() >= v2.getycoordinate() + 9) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
				{
					v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				}
				// passing through the given space
				if (v2.getycoordinate() >= 174 && (v2.getxcoordinate() >= 80 + 12 && v2.getxcoordinate() <= 108 + 12))
					v2.setycoordinate(-4);
				// collision with boundries
				if (v2.getycoordinate() >= 166 && (v2.getxcoordinate() >= 0 + 12 && v2.getxcoordinate() <= 78 + 12))
					v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				else if (v2.getycoordinate() >= 166 && (v2.getxcoordinate() >= 110 + 12 && v2.getxcoordinate() <= 184 + 12))
					v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				else if (v2.getycoordinate() == 102 && (v2.getxcoordinate() <= 4 + 12))
					v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				else if (v2.getycoordinate() == 102 && (v2.getxcoordinate() >= 184 + 12))
					v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				//downward movement
				if (v2.getycoordinate()  >= v1.getycoordinate() ) {

					v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
					if (v2.canon_is_fired == false) {
						v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
						v2.setcanonycoordinate(v2.getycoordinate());
					}
					cout << "y2 down is " << v2.getycoordinate() << endl;

				}
				// collision with each other
				if ((v1.getycoordinate() >= v2.getycoordinate() - 9 && v1.getycoordinate() <= v2.getycoordinate() - 7) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate())) {
					v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
					//moving right and left to pass the obstacle
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				}
				// passing through the given space
				if (v2.getycoordinate() <= -2 && (v2.getxcoordinate() >= 80 + 12 && v2.getxcoordinate() <= 108 + 12))
					v2.setycoordinate(172);
				// collision with boundries
				if (v2.getycoordinate() < 14 && (v2.getxcoordinate() >= 6 + 12 && v2.getxcoordinate() <= 79 + 12))
					v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				else if (v2.getycoordinate() < 14 && (v2.getxcoordinate() >= 110 + 12 && v2.getxcoordinate() <= 184 + 12))
					v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				else if (v2.getycoordinate() <= 71 && (v2.getxcoordinate() <= 4 + 12))
					v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				else if (v2.getycoordinate() <= 71 && (v2.getxcoordinate() >= 184 + 12))
					v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				//right movement
				if (v2.getxcoordinate() < v1.getxcoordinate() + 30) {
					v2.setxcoordinate(v2.getxcoordinate() + v2.bot_speed);
					if (v2.canon_is_fired == false) {
						v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
						v2.setcanonycoordinate(v2.getycoordinate());
					}
					cout << "x2 is " << v2.getxcoordinate() << endl;
				}
				// collision with each other
				if ((v1.getxcoordinate() - 1 <= v2.getxcoordinate() && v1.getxcoordinate() + 1 >= v2.getxcoordinate()) && (v1.getycoordinate() + 10 >= v2.getycoordinate() && v1.getycoordinate() - 10 <= v2.getycoordinate()))
				{
					v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
					if (v2.getycoordinate() <= 90)
						v2.setycoordinate(v2.getycoordinate() + 6);
					else
						v2.setycoordinate(v2.getycoordinate() - 6);
				}
				// passing through the space
				if (v2.getxcoordinate() >= 210 && (v2.getycoordinate() >= 72 && v2.getycoordinate() <= 102))
					v2.setxcoordinate(-2);
				// collision with boundries
				if (v2.getxcoordinate() >= 184 + 12 && (v2.getycoordinate() >= 0 && v2.getycoordinate() <= 71))
					v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
				else if (v2.getxcoordinate() >= 184 + 12 && (v2.getycoordinate() >= 103 && v2.getycoordinate() <= 172))
					v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
				else if (v2.getxcoordinate() == 108 + 14 && (v2.getycoordinate() < 13))
					v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
				else if (v2.getxcoordinate() == 108 + 14 && (v2.getycoordinate() > 166))
					v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
			
				//left movement
				if (v1.getxcoordinate() + 50 <= v2.getxcoordinate())
				{
					v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
					if (v2.canon_is_fired == false) {
						v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
						v2.setcanonycoordinate(v2.getycoordinate());
					}
					/*if (v1.getycoordinate() == v2.getycoordinate() && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate())) {
						v2.canon_is_fired = true;
					}*/
					cout << "x2 is " << v2.getxcoordinate() << endl;
				}
				// collision with each other
				if (v1.getxcoordinate() + 22 == v2.getxcoordinate() && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				// passing through the space
				if (v2.getxcoordinate() <= -10 && (v2.getycoordinate() >= 72 && v2.getycoordinate() <= 102))
					v2.setxcoordinate(210);
				// collision with boundries
				if (v2.getxcoordinate() <= 4 + 12 && (v2.getycoordinate() >= 0 && v2.getycoordinate() <= 71))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() <= 4 + 12 && (v2.getycoordinate() >= 103 && v2.getycoordinate() <= 172))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() < 80 + 12 && (v2.getycoordinate() < 13))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				else if (v2.getxcoordinate() < 80 + 12 && (v2.getycoordinate() > 166))
					v2.setxcoordinate(v2.getxcoordinate() + 2);
				//firing canon
				if ((v1.getxcoordinate() + 12 <= v2.getcanonxcoordinate() && (v2.getxcoordinate() > v1.getxcoordinate() + 12)) && (v1.getycoordinate() + 4 >= v2.getycoordinate() && v1.getycoordinate() - 4 <= v2.getycoordinate())) {
					v2.canon_is_fired = true;
				}
		}
		else if (map == 2)
		{
			//upward movement 
			if (v2.getycoordinate() <= v1.getycoordinate()) {
				v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				if (v2.canon_is_fired == false)
				{
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
				cout << "y2 up is " << v2.getycoordinate() << endl;
			}
			// collision with each other
			if ((v1.getycoordinate() <= v2.getycoordinate() + 11 && v1.getycoordinate() >= v2.getycoordinate() + 9) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
			{
				v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			// collsion with the obstacles
			if ((v2.getycoordinate() >= 57 && v2.getycoordinate() <= 59) && (v2.getxcoordinate() >= 14 + 12 && v2.getxcoordinate() <= 43 + 12)) {

				v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				if (v2.getxcoordinate() <= 54 && v1.getxcoordinate() + 20 < v2.getxcoordinate() )
					v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			else if ((v2.getycoordinate() >= 80 && v2.getycoordinate() <= 82) && (v2.getxcoordinate() >= 53 + 12 && v2.getxcoordinate() <= 79 + 12)) {

				v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				if (v2.getxcoordinate() <= 68 && v1.getxcoordinate() + 20 < v2.getxcoordinate())
					v2.setxcoordinate(v2.getxcoordinate() - (v2.bot_speed + 1));
				else 
					v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			else if ((v2.getycoordinate() >= 105 && v2.getycoordinate() <= 107) && (v2.getxcoordinate() >= 14 + 12 && v2.getxcoordinate() <= 22 + 12)) {

				v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);

			}
			else if ((v2.getycoordinate() >= 27 && v2.getycoordinate() <= 29) && (v2.getxcoordinate() > 83 + 12 && v2.getxcoordinate() <= 104 + 12)) {

				v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				if (v2.getxcoordinate() <= 116 && v1.getxcoordinate() + 20 < v2.getxcoordinate())
					v2.setxcoordinate(v2.getxcoordinate() - (v2.bot_speed + 1));
				else
					v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			else if ((v2.getycoordinate() >= 82 && v2.getycoordinate() <= 83) && (v2.getxcoordinate() >= 108 + 12 && v2.getxcoordinate() <= 134 + 12)) {

				v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				if (v2.getxcoordinate() < 146 && v1.getxcoordinate() + 20 < v2.getxcoordinate())
					v2.setxcoordinate(v2.getxcoordinate() - (v2.bot_speed + 1));
				else
					v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			else if ((v2.getycoordinate() >= 58 && v2.getycoordinate() <= 59) && (v2.getxcoordinate() >= 143 + 12 && v2.getxcoordinate() <= 173 + 12)) {

				v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				if (v2.getxcoordinate() <= 186 && v1.getxcoordinate() + 20 < v2.getxcoordinate())
					v2.setxcoordinate(v2.getxcoordinate() - (v2.bot_speed + 1));
				else
					v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			//downward movement
			if (v2.getycoordinate() >= v1.getycoordinate()) {

				v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				if (v2.canon_is_fired == false) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
				cout << "y2 down is " << v2.getycoordinate() << endl;

			}
			// collision with each other
			if ((v1.getycoordinate() >= v2.getycoordinate() - 9 && v1.getycoordinate() <= v2.getycoordinate() - 7) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate())) {
				v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				//moving right and left to pass the obstacle
				v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			//collision with the obstacles
			if ((v2.getycoordinate() <= 125 && v2.getycoordinate() >= 124) && (v2.getxcoordinate() >= 14 && v2.getxcoordinate() <= 43 + 12)) {
				v2.setycoordinate(v2.getycoordinate() + (v2.bot_speed + 1));
				//moving right and left to pass the obstacle
					v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));

			}
			else if ((v2.getycoordinate() <= 75 && v2.getycoordinate() >= 73) && (v2.getxcoordinate() >= 14 + 12 && v2.getxcoordinate() <= 22 + 12)) {
				v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);

			}
			else if ((v2.getycoordinate() <= 105 && v2.getycoordinate() >= 103) && (v2.getxcoordinate() >= 53 + 12 && v2.getxcoordinate() <= 79 + 12)) {
				v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				//moving right and left to pass the obstacle
				if (v1.getxcoordinate() + 20 < v2.getxcoordinate())
					v2.setxcoordinate(v2.getxcoordinate() - (v2.bot_speed + 1));
				else
					v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			else if ((v2.getycoordinate() <= 150 && v2.getycoordinate() >= 147) && (v2.getxcoordinate() > 83 + 12 && v2.getxcoordinate() <= 104 + 12)) {
				v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				//moving right and left to pass the obstacle
				if (v1.getxcoordinate() + 20 < v2.getxcoordinate())
					v2.setxcoordinate(v2.getxcoordinate() - (v2.bot_speed + 1));
				else
					v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));

			}
			else if ((v2.getycoordinate() <= 105 && v2.getycoordinate() >= 103) && (v2.getxcoordinate() >= 108 + 12 && v2.getxcoordinate() <= 134 + 12)) {
				v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				//moving right and left to pass the obstacle
				if (v1.getxcoordinate() + 20 < v2.getxcoordinate())
					v2.setxcoordinate(v2.getxcoordinate() - (v2.bot_speed + 1));
				else
					v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			else if ((v2.getycoordinate() <= 125 && v2.getycoordinate() >= 123) && (v2.getxcoordinate() >= 143 + 12 && v2.getxcoordinate() <= 173 + 12)) {
				v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				//moving right and left to pass the obstacle
				if (v1.getxcoordinate() + 20 < v2.getxcoordinate())
					v2.setxcoordinate(v2.getxcoordinate() - (v2.bot_speed + 1));
				else
					v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			else if ((v2.getycoordinate() <= 75 && v2.getycoordinate() >= 73) && (v2.getxcoordinate() >= 164 + 12 && v2.getxcoordinate() <= 173 + 12)) {
				v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				//moving right and left to pass the obstacle
				if (v1.getxcoordinate() + 20 < v2.getxcoordinate())
					v2.setxcoordinate(v2.getxcoordinate() - (v2.bot_speed + 1));
				 else
					 v2.setxcoordinate(v2.getxcoordinate() + (v2.bot_speed + 1));
			}
			//right movement
			if (v2.getxcoordinate() < v1.getxcoordinate() + 30) {
				v2.setxcoordinate(v2.getxcoordinate() + v2.bot_speed);
				if (v2.canon_is_fired == false) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
				cout << "x2 is " << v2.getxcoordinate() << endl;
			}
			if (v2.getxcoordinate() > 196)
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
			// collision with each other
			if ((v1.getxcoordinate() - 1 <= v2.getxcoordinate() && v1.getxcoordinate() + 1 >= v2.getxcoordinate()) && (v1.getycoordinate() + 10 >= v2.getycoordinate() && v1.getycoordinate() - 10 <= v2.getycoordinate()))
			{
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
				if (v2.getycoordinate() <= 88)
					v2.setycoordinate(v2.getycoordinate() + 4);
				else
					v2.setycoordinate(v2.getycoordinate() - 4);
			}
			// collision with the obstacles with speed == 1 || speed ==2
			if ((v2.getxcoordinate() >= 14 + 11 && v2.getxcoordinate() <= 14 + 13) && (v2.getycoordinate() >= 58 && v2.getycoordinate() <= 74))
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
			else if ((v2.getxcoordinate() >= 24 + 11 && v2.getxcoordinate() <= 24 + 13) && (v2.getycoordinate() >= 76 && v2.getycoordinate() <= 106))
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
			else if ((v2.getxcoordinate() >= 14 + 11 && v2.getxcoordinate() <= 14 + 13) && (v2.getycoordinate() >= 108 && v2.getycoordinate() <= 124))
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
			else if ((v2.getxcoordinate() >= 54 + 11 && v2.getxcoordinate() <= 54 + 13) && (v2.getycoordinate() >= 82 && v2.getycoordinate() <= 104)) {
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
				if (v2.getycoordinate() < 92)
					v2.setycoordinate(v2.getycoordinate() - (v2.bot_speed + 1));
				else
					v2.setycoordinate(v2.getycoordinate() + (v2.bot_speed + 1));

			}
			else if ((v2.getxcoordinate() >= 84 + 11 && v2.getxcoordinate() <= 84 + 13) && (v2.getycoordinate() >= 28 && v2.getycoordinate() <= 148)) {
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
				//passing the obstacle in the mid
				if (v2.getycoordinate() < 88)
					v2.setycoordinate(v2.getycoordinate() - (v2.bot_speed + 1));
				else
					v2.setycoordinate(v2.getycoordinate() + (v2.bot_speed + 1));
				
			}
			else if ((v2.getxcoordinate() >= 110 + 11 && v2.getxcoordinate() <= 110 + 13) && (v2.getycoordinate() >= 82 && v2.getycoordinate() <= 104)) {
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
				if (v2.getycoordinate() < 92)
					v2.setycoordinate(v2.getycoordinate() - (v2.bot_speed + 1));
				else
					v2.setycoordinate(v2.getycoordinate() + (v2.bot_speed + 1));
			}
			else if ((v2.getxcoordinate() >= 144 + 11 && v2.getxcoordinate() <= 144 + 13) && (v2.getycoordinate() >= 58 && v2.getycoordinate() <= 124))
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
			//left movement
			if (v1.getxcoordinate() + 36 <= v2.getxcoordinate())
			{
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
				if (v2.canon_is_fired == false) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
				cout << "x2 is " << v2.getxcoordinate() << endl;
			}
			//colision with the boundry
			if (v2.getxcoordinate() < 56)
				v2.setxcoordinate(v2.getxcoordinate() + v2.bot_speed);
			// collision with each other
			if (v1.getxcoordinate() + 22 == v2.getxcoordinate() && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
				v2.setxcoordinate(v2.getxcoordinate() + v2.bot_speed);
			// collision with obstacles when speed  == 1 || speed == 2
			if ((v2.getxcoordinate() >= 42 + 12 && v2.getxcoordinate() <= 42 + 14) && (v2.getycoordinate() >= 57 && v2.getycoordinate() <= 125)) {
				v2.setxcoordinate(v2.getxcoordinate() + v2.bot_speed);
				if (v2.getycoordinate() < 91)
					v2.setycoordinate(v2.getycoordinate() - (v2.bot_speed + 1));
				else
					v2.setycoordinate(v2.getycoordinate() + (v2.bot_speed + 1));

			}
			else if ((v2.getxcoordinate() >= 78 + 12 && v2.getxcoordinate() <= 78 + 14) && (v2.getycoordinate() >= 82 && v2.getycoordinate() <= 102)) {
				v2.setxcoordinate(v2.getxcoordinate() + v2.bot_speed);
				if (v2.getycoordinate() < 92)
					v2.setycoordinate(v2.getycoordinate() - (v2.bot_speed + 1));
				else
					v2.setycoordinate(v2.getycoordinate() + (v2.bot_speed + 1));

			}
			else if ((v2.getxcoordinate() >= 102 + 12 && (v2.getxcoordinate() <= 102 + 14)) && (v2.getycoordinate() >= 28 && v2.getycoordinate() <= 148)) {
				v2.setxcoordinate(v2.getxcoordinate() + v2.bot_speed);
				if (v2.getycoordinate() < 88)
					v2.setycoordinate(v2.getycoordinate() - (v2.bot_speed + 1));
				else
					v2.setycoordinate(v2.getycoordinate() + (v2.bot_speed + 1));

			}
			else if ((v2.getxcoordinate() >= 132 + 12 && v2.getxcoordinate() <= 132 + 14) && (v2.getycoordinate() >= 82 && v2.getycoordinate() <= 102)) {
				v2.setxcoordinate(v2.getxcoordinate() + v2.bot_speed);
				if (v2.getycoordinate() < 92)
					v2.setycoordinate(v2.getycoordinate() - (v2.bot_speed + 1));
				else
					v2.setycoordinate(v2.getycoordinate() + (v2.bot_speed + 1));


			}

			else if ((v2.getxcoordinate() >= 186 && v2.getxcoordinate() <= 188) && (v2.getycoordinate() >= 56 && v2.getycoordinate() <= 126)) {
				v2.setxcoordinate(v2.getxcoordinate() + v2.bot_speed);
				if (v2.getycoordinate() < 91)
					v2.setycoordinate(v2.getycoordinate() - (v2.bot_speed + 1));
				else
					v2.setycoordinate(v2.getycoordinate() + (v2.bot_speed + 1));
			
			}
			//canon firing
			if ((v1.getxcoordinate() + 60 >= v2.getcanonxcoordinate() && v1.getxcoordinate() + 12 <= v2.getcanonxcoordinate()) && (v1.getycoordinate() + 4 >= v2.getycoordinate() && v1.getycoordinate() - 4 <= v2.getycoordinate())) {
			v2.canon_is_fired = true;
			}
		}
		else if (map == 3)
		{
			//upward bot movement
			if (v2.getycoordinate() < v1.getycoordinate() ) {
				v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				if (v2.canon_is_fired == false)
				{
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
				cout << "y2 is " << v2.getycoordinate() << endl;
			}
			// collision with each other
			if ((v1.getycoordinate() <= v2.getycoordinate() + 11 && v1.getycoordinate() >= v2.getycoordinate() + 9) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate()))
			{
				v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				v2.setxcoordinate(v2.getxcoordinate() + 2);
			}
			//downward bot movement
			if (v2.getycoordinate() >= v1.getycoordinate() ) {

				v2.setycoordinate(v2.getycoordinate() - v2.bot_speed);
				if (v2.canon_is_fired == false) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
				cout << "y2 is " << v2.getycoordinate() << endl;

			}
			// collision with each other
			if ((v1.getycoordinate() >= v2.getycoordinate() - 9 && v1.getycoordinate() <= v2.getycoordinate() - 7) && (v1.getxcoordinate() + 22 >= v2.getxcoordinate() && v1.getxcoordinate() < v2.getxcoordinate())) {
				v2.setycoordinate(v2.getycoordinate() + v2.bot_speed);
				//moving right and left to pass the obstacle
				v2.setxcoordinate(v2.getxcoordinate() + 2);
			}
			//right bot movement
			if (v2.getxcoordinate() < v1.getxcoordinate() + 30) {
				v2.setxcoordinate(v2.getxcoordinate() + v2.bot_speed);
				if (v2.canon_is_fired == false) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
				cout << "x2 is " << v2.getxcoordinate() << endl;
			}
			// collision with each other
			if ((v1.getxcoordinate() - 1 <= v2.getxcoordinate() && v1.getxcoordinate() + 1 >= v2.getxcoordinate()) && (v1.getycoordinate() + 10 >= v2.getycoordinate() && v1.getycoordinate() - 10 <= v2.getycoordinate()))
			{
				v2.setxcoordinate(v2.getxcoordinate() - 1);
				if (v2.getycoordinate() < 88)
					v2.setycoordinate(v2.getycoordinate() + 4);
				else
					v2.setycoordinate(v2.getycoordinate() - 4);
			}
			//left bot movement
			if (v1.getxcoordinate() + 50 < v2.getxcoordinate())
			{
				v2.setxcoordinate(v2.getxcoordinate() - v2.bot_speed);
				if (v2.canon_is_fired == false) {
					v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
					v2.setcanonycoordinate(v2.getycoordinate());
				}
				
				cout << "x2 is " << v2.getxcoordinate() << endl;
			}
			//passing through the space
			if (v2.getxcoordinate() < -10)
				v2.setxcoordinate(200);
			// collision with each other
			if (v1.getxcoordinate() + 22 == v2.getxcoordinate() && (v1.getycoordinate() + 8 >= v2.getycoordinate() && v1.getycoordinate() - 8 <= v2.getycoordinate()))
				v2.setxcoordinate(v2.getxcoordinate() + 2);
			//firing canon
			if ((v1.getxcoordinate() + 12 <= v2.getcanonxcoordinate() && (v2.getxcoordinate() > v1.getxcoordinate() + 12 ))&& (v1.getycoordinate() + 4 >= v2.getycoordinate() && v1.getycoordinate() - 4 <= v2.getycoordinate())) {
				v2.canon_is_fired = true;
			}
		}
	}
}

void displayingmenu()
{

	/*DrawRectangle(0,0,200,100,colors[BROWN]);
	DrawRectangle(0, 100, 200, 100, colors[BLACK]);*/

	DrawRectangle(0, 0, 6, 200, colors[BROWN]);	  // left
	DrawRectangle(0, 0, 200, 6, colors[BROWN]);	  // bottom
	DrawRectangle(196, 0, 6, 200, colors[BROWN]); // right
	DrawRectangle(0, 194, 206, 6, colors[BROWN]); // up

	// vehicle displaying functions
	Game::displaying_vehicles_for_menu();
	// menu text
	DrawString(20, 140, "Combat by Bilal Akbar", colors[BLACK]);
	DrawString(20, 120, "1.Rank matches ", colors[BLACK]);
	DrawString(20, 100, "2.Friendly match pvp", colors[BLACK]);
	DrawString(20, 80, "3.Leaderboard ", colors[BLACK]);
	DrawString(20, 60, "4.Controls ", colors[BLACK]);
	DrawString(20, 40, "5.Exit", colors[RED]);
	glutPostRedisplay();
}
// selecting map for player v player mode

void selecting_maps()
{
	// borders
	DrawRectangle(0, 0, 6, 200, colors[BROWN]);	  // left
	DrawRectangle(0, 0, 200, 6, colors[BROWN]);	  // bottom
	DrawRectangle(196, 0, 6, 200, colors[BROWN]); // right
	DrawRectangle(0, 194, 206, 6, colors[BROWN]); // up
	// vehicle displaying functions
	Game::displaying_vehicles_for_menu();
	// menu text
	DrawString(20, 120, "PvP ", colors[GREEN]);
	DrawString(20, 100, "1.Classic : (less hurdles)", colors[BLUE]);
	DrawString(20, 80, "2.Hard (Hurdles)", colors[DARK_ORANGE]);
	DrawString(20, 60, "3.Superstars ", colors[RED]);
	glutPostRedisplay();
}
//cars selection
void selecting_cars()
{
	string temp;
	// borders
	DrawRectangle(0, 0, 6, 200, colors[BROWN]);	  // left
	DrawRectangle(0, 0, 200, 6, colors[BROWN]);	  // bottom
	DrawRectangle(196, 0, 6, 200, colors[BROWN]); // right
	DrawRectangle(0, 194, 206, 6, colors[BROWN]); // up
	// Player 1
	if (Game::p1.selecting_car_type == false) {
		temp = "Car selection for " + Game::p1.getname();
		DrawString(20, 140, temp, colors[GREEN]);
		DrawString(20, 120, "1.Tank ", colors[BLUE]);
		DrawString(20, 100, "2.Chopper", colors[DARK_ORANGE]);
		DrawString(20, 80, "3.Plane", colors[RED]);
	}
	//Player 2
	if (Game::p2.selecting_car_type == false && Game::p1.selecting_car_type == true) {
		temp = "Car selection for  Player 2 ";
		DrawString(20, 140, temp, colors[GREEN]);
		DrawString(20, 120, "1.Tank ", colors[BLUE]);
		DrawString(20, 100, "2.Chopper", colors[DARK_ORANGE]);
		DrawString(20, 80, "3.Plane", colors[RED]);
	}
	Game::displaying_vehicles_for_menu();
	glutPostRedisplay();
}
void displaying_controls()
{
	// borders
	DrawRectangle(0, 0, 6, 200, colors[BROWN]);	  // left
	DrawRectangle(0, 0, 200, 6, colors[BROWN]);	  // bottom
	DrawRectangle(196, 0, 6, 200, colors[BROWN]); // right
	DrawRectangle(0, 194, 206, 6, colors[BROWN]); // up
	string temp;
	temp = "Controls for (Player 1) " + Game::p1.getname() + " are ";
	DrawString(20, 140, temp, colors[GREEN]);
	DrawString(20, 120, "Up arrow key to move up ", colors[GREEN]);
	DrawString(20, 100, "Down arrow key to move down ", colors[GREEN]);
	DrawString(20, 80, "Right arrow key to move right", colors[GREEN]);
	DrawString(20, 60, "Left arrow key to move left", colors[GREEN]);
	DrawString(20, 40, "R shift key to hit canon", colors[GREEN]);
	temp = "Controls for (Player 2) " + Game::p2.getname() + " are ";
	DrawString(120, 140, temp, colors[RED]);
	DrawString(120, 120, "'w' to move up ", colors[RED]);
	DrawString(120, 100, "'s'to move down ", colors[RED]);
	DrawString(120, 80, "'d'to move right", colors[RED]);
	DrawString(120, 60, "'a'to move left", colors[RED]);
	DrawString(120, 40, "b button key to hit canon", colors[RED]);

	
}
void displaying_rematch() {
	// borders
	DrawRectangle(0, 0, 6, 200, colors[BROWN]);	  // left
	DrawRectangle(0, 0, 200, 6, colors[BROWN]);	  // bottom
	DrawRectangle(196, 0, 6, 200, colors[BROWN]); // right
	DrawRectangle(0, 194, 206, 6, colors[BROWN]); // up
	//name and scores
	string temp;
	temp = "Score of (Player 1)" + Game::p1.getname() + " is " + to_string(Game::p1.getscore());
	DrawString(20, 140, temp, colors[GREEN]);
	temp = "Score of (Player 2)" + Game::p2.getname() + " is " + to_string(Game::p2.getscore());
	DrawString(20, 120, temp, colors[RED]);
	if (Game::p1.getscore() > Game::p2.getscore())
		DrawString(20, 100, "Player 1 is the winner", colors[YELLOW]);
	else 
		DrawString(20, 100, "Player 2 is the winner", colors[YELLOW]);
	DrawString(20, 80, "Do you want to rematch", colors[GREEN]);
	DrawString(20, 60, "1.Yes", colors[GREEN]);
	DrawString(20, 40, "2.No", colors[RED]);
	Game::rematch = true;
	// resetting v1 coordinates
	Game::v1.setxcoordinate((rand() % 6) + 6);
	while ((int)Game::v1.getxcoordinate() % 2 != 0) // to get even
		Game::v1.setxcoordinate((rand() % 6) + 6);
	Game::v1.setycoordinate((rand() % 160) + 12);
	while ((int)Game::v1.getycoordinate() % 2 != 0) // to get even
		Game::v1.setycoordinate((rand() % 160) + 12);
	Game::v1.setcanonxcoordinate(Game::v1.getxcoordinate() + 12);
	Game::v1.setcanonycoordinate(Game::v1.getycoordinate());
	Sleep(1000);
	// resetting v2 coordinates
	Game::v2.setxcoordinate((rand() % 10) + 188);
	while ((int)Game::v2.getxcoordinate() % 2 != 0) // to get even
		Game::v2.setxcoordinate((rand() % 10) + 188);
	Game::v2.setycoordinate((rand() % 160) + 12);
	while ((int)Game::v2.getycoordinate() % 2 != 0) // to get even
		Game::v2.setycoordinate((rand() % 160) + 12);
	Game::v2.setcanonxcoordinate(Game::v2.getxcoordinate() - 12);
	Game::v2.setcanonycoordinate(Game::v2.getycoordinate());
}	
void displaying_leaderboard()
{
	Player *temp;
	// borders
	DrawRectangle(0, 0, 6, 200, colors[BROWN]);	  // left
	DrawRectangle(0, 0, 200, 6, colors[BROWN]);	  // bottom
	DrawRectangle(196, 0, 6, 200, colors[BROWN]); // right
	DrawRectangle(0, 194, 206, 6, colors[BROWN]); // up
	//
	DrawString(40, 180, "Name", colors[GREEN]);
	DrawString(150, 180, "Score", colors[GREEN]);
	for (int i = 0; i < 10; i++)
	{
		temp = &Game::top10[i];
		temp->Display();
	}
	HighScore::set_y_value();
}
void sortingandsetting(Player &player,HighScore Top10[])
{
	int i_value=10;
	int i_value_score;
	string i_value_name;
	for (int i = 0; i <10 ; i++)
	{
		if (player.total_score >= Top10[i].total_score)
		{
			i_value = i + 1;
			i_value_score = Top10[i].total_score;
			i_value_name = Top10[i].getname();
			Top10[i].total_score = player.total_score;
			Top10[i].setname(player.getname());
			break;
		}
	}
	for (int i = 9; i >= i_value + 1; i--)
	{
		Top10[i].setname(Top10[i - 1].getname());
		Top10[i].total_score = Top10[i - 1].total_score;
	}
	if (i_value != 10) {
		Top10[i_value].setname(i_value_name);
		Top10[i_value].total_score = i_value_score;
	}
	fstream leaderboard("leaderboard.txt", ios::out);
	for (int i = 0; i < 10; i++)
	{
		leaderboard << Top10[i].getname() << ',' << Top10[i].total_score << '\n';
	}


}
void resetting_coordinates(Vehicle &v1,Vehicle &v2)
{
	// resetting v1 coordinates
	v1.setxcoordinate((rand() % 6) + 6);
	while ((int)v1.getxcoordinate() % 2 != 0) // to get even
		v1.setxcoordinate((rand() % 6) + 6);
	v1.setycoordinate((rand() % 160) + 12);
	while ((int)v1.getycoordinate() % 2 != 0) // to get even
		v1.setycoordinate((rand() % 160) + 12);
	v1.setcanonxcoordinate(v1.getxcoordinate() + 12);
	v1.setcanonycoordinate(v1.getycoordinate());
	Sleep(1000);
	// resetting v2 coordinates
	v2.setxcoordinate((rand() % 10) + 188);
	while ((int)v2.getxcoordinate() % 2 != 0) // to get even
		v2.setxcoordinate((rand() % 10) + 188);
	v2.setycoordinate((rand() % 160) + 12);
	while ((int)v2.getycoordinate() % 2 != 0) // to get even
		v2.setycoordinate((rand() % 160) + 12);
	v2.setcanonxcoordinate(v2.getxcoordinate() - 12);
	v2.setcanonycoordinate(v2.getycoordinate());

}

