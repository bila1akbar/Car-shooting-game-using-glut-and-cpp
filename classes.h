//Bilal Akbar
//Roll No 21i-1174
//Section Q
//Final project
#pragma once
// glut libraries
#include <GL/glut.h>
#include<GL/freeglut.h>
// general libraries
#include <Windows.h>
#include<mmsystem.h>
#include <iostream>
#include <cmath>
#include <string.h>
#include<time.h>
#include"util.h"
#include <fstream>
//global variables

using namespace std;
class Player
{
private:
   string name;
   int score;
   int car_type;
   
public:
    int total_score;
   bool selecting_car_type;
   static int player_count;
   Player();
   void setname(string);
   void set_car_type(int);
   int get_car_type();
   string getname();
   void setscore(int);
   int getscore();
   virtual void Display();
};
//highscore is inherited from player to get name and scores functions from the player class
class HighScore : public Player
{
    static int y_value;
public:
    static void set_y_value();
    void Display();
};
class Canon
{
   public:
   int size;
   float speed;
   //variables of medium canon
   float x_of_medium;
   float y_of_medium;
   bool medium_is_fired;
   int count_of_medium;

   //variables of large canon
   float x_of_large;
   float y_of_large;
   bool large_is_fired;
   int count_of_large;
   static bool sponing_large_canon; //sponing large canon
   static bool map1_and_map3_and_large; // sponing large canon in map 1 and map 3 at one place
   static bool map2_and_large; // sponing large canon in map 2 at one place
   static bool large_at_which_point; // to spong large canon only on given points achieved by the player
   Canon(int = 0);

};
//Vehicle is composed of canon, that's why using canon as composition in the vehicle class
class Vehicle
{
private:
    float x_coordinate;
    float y_coordinate;
    float canon_x_coordinate;
    float canon_y_coordinate;
    int id;
public:
    float bot_speed;
    Canon* canon;
    bool canon_is_fired;
    //sf::RectangleShape my_vehicle;
 static int vehicle_count;
 void InitVehicle(int,int);
   Vehicle(int = 0);
   void setxcoordinate(float );
   void setycoordinate(float);
   float getxcoordinate();
   float getycoordinate();
   void setcanonxcoordinate(float);//setter for canon
   void setcanonycoordinate(float);//setter for canon
   float getcanonxcoordinate();//getter for canon
   float getcanonycoordinate();//getter for canon
   ~Vehicle();
};
//Game class has composition relation with Vehicle and player class, and we are using static player and vehicle variable to avoid 
//global variables

class Game
{
    static Player p1, p2;
    static Vehicle v1, v2;
    static HighScore top10[10];
    int wins;
    static bool getting_data_from_file;
    static bool hitting_collision;
    static int storing_random_level[3];
    static int level;
    static bool leaderboard;
    static bool playing_level[3];
    static bool showing_controls;
    static int vehicle_count;
    static bool rematch;
    static int moving_x1 , moving_x2 ; // to move the cars in the menu;
    static int car;
    static int map; //map selection
    //static int level; // level selection 
    static bool menu; //if the menu is being displayed
    static bool map_selection; // map selection in pvp mode after the menu
    static bool initialzing_map_3;
    static float map3_cloud1_x, map3_cloud1_y, map3_cloud2_x, map3_cloud2_y; // map 2 varibles
    static bool menu_flag1, menu_flag2, bool_map3_cloud1_x, bool_map3_cloud1_y, bool_map3_cloud2_x, bool_map3_cloud2_y;
    static bool multi_player, single_player;
public:
    
    //public functions 
    Game(int = 0,int = 0 );
    void setWins(int);
    //void setlevel(int);
    int getWins() const;
    //int getlevel() const;
    static void GameDisplay();
    static void PrintableKeys(unsigned char, int ,int);
    static void NonPrintableKeys(int,int,int);
   static void displaying_vehicles_for_menu();
   static void map1(), map2(), map3();
   static void drawCar();
   static void drawcanon();
   static void car1(), car2(), car3();
   static void moveshapes();
   friend void selecting_cars();
   friend void displaying_controls();
   friend void displaying_rematch();
   friend void displaying_leaderboard();
   friend void resetting();
};
