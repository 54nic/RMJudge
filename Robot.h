#ifndef ROBOT_H
#define ROBOT_H
class Robot {
 protected:
  int max_hp, max_hot;
  int hp, hot, team, id, type;
  int level;
  bool died;

 public:
  // #获取最大血量
  int get_max_hp();
  // #设定最大血量
  // @value   设定值
  void set_max_hp(int value);
  // #获取最大热量
  int get_max_hot();
  // #设定最大热量
  // @value   设定值
  void set_max_hot(int value);
  // #获取生命值
  int get_hp();
  // #设定生命值
  // @value   设定值
  void set_hp(int value);
  // #获取热量
  int get_hot();
  // #设定热量
  // @value   设定值
  void set_hot(int value);
  // #获取团队
  int get_team();
  // #设定团队
  // @value   设定值
  void set_team(int value);
  // #获取机器人id
  int get_id();
  // #设定机器人id
  // @value   设定值
  void set_id(int value);
  // #获取兵种
  int get_type();
  // #设定兵种
  // @value   设定值
  void set_type(int value);
  // #获取等级
  virtual int get_level() = 0;
  // #设定等级
  // @value   设定值
  virtual void set_level(int value) = 0;
  // #获取死亡状态
  // @time    时间差
  bool is_died();
  // #设定死亡状态
  // @value   设定值
  void set_died(bool value);
};

class Infantry : public Robot {
 public:
  // #构造并初始化步兵
  Infantry(int team, int id);
  // #获取等级
  int get_level();
  // #设定等级
  // @value   设定值
  void set_level(int value);
};
class Engineer : public Robot {
 public:
  // #构造并初始化工程
  Engineer(int team, int id);
  // #获取等级
  int get_level();
  // #设定等级
  // @value   设定值
  void set_level(int value);
};
#endif