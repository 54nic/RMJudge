#include "Robot.h"

int Robot::get_max_hp() { return this->max_hp; }
void Robot::set_max_hp(int value) { this->max_hp = value; }
int Robot::get_max_hot() { return this->max_hot; }
void Robot::set_max_hot(int value) { this->max_hot = value; }
int Robot::get_hp() { return this->hp; }
void Robot::set_hp(int value) { this->hp = value; }
int Robot::get_hot() { return this->hot; }
void Robot::set_hot(int value) { this->hot = value; }
int Robot::get_team() { return this->team; }
void Robot::set_team(int value) { this->team = value; }
int Robot::get_id() { return this->id; }
void Robot::set_id(int value) { this->id = value; }
int Robot::get_type() { return this->type; }
void Robot::set_type(int value) { this->type = value; }
bool Robot::is_died() { return this->died; }
void Robot::set_died(bool value) { this->died = value; }
Infantry::Infantry(int team, int id) {
  this->team = team;
  this->type = 0;
  this->id = id;
  this->max_hot = 100;
  this->max_hp = 100;
  this->hp = this->max_hp;
  this->hot = this->max_hot;
  this->level = 1;
  this->died = false;
}
int Infantry::get_level() { return this->level; }
void Infantry::set_level(int value) {
  this->level = value;  // 若等级为2，则升为二级步兵
  if (value == 2) {
    this->set_max_hot(200);
    this->set_max_hp(150);
    this->set_hp(150);
  }
  // 若等级为3，则升为三级步兵
  else if (value == 3) {
    this->set_max_hot(300);
    this->set_max_hp(250);
    this->set_hp(250);
  }
}
Engineer::Engineer(int team, int id) {
  this->team = team;
  this->type = 1;
  this->id = id;
  this->max_hot = 0;
  this->max_hp = 300;
  this->hp = this->max_hp;
  this->hot = this->max_hot;
  this->died = false;
}

int Engineer::get_level() { return 0; }

void Engineer::set_level(int value) {}
