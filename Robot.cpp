#include "Robot.h"

Infantry::Infantry(int team, int id) {
  this->TEAM = team;
  this->TYPE = 0;
  this->ID = id;
  this->MAX_HOT = 100;
  this->MAX_HP = 100;
  this->HP = this->MAX_HP;
  this->HOT = this->MAX_HOT;
  this->level = 1;
  this->died = false;
}
Engineer::Engineer(int team, int id) {
  this->TEAM = team;
  this->TYPE = 1;
  this->ID = id;
  this->MAX_HOT = 0;
  this->MAX_HP = 300;
  this->HP = this->MAX_HP;
  this->HOT = this->MAX_HOT;
  this->died = false;
}