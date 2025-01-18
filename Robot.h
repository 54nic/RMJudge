#ifndef ROBOT_H
#define ROBOT_H
class ROBOT {
 public:
  int MAX_HP;
  int MAX_HOT;
  int HP, HOT, TEAM, ID, TYPE;
  int level;
  bool died;
};

class Infantry : public ROBOT {
 public:
  Infantry(int team, int id);
};
class Engineer : public ROBOT {
 public:
  Engineer(int team, int id);
};
#endif