#include <memory>
#include <vector>

#include "Robot.h"
#ifndef MANAGER_H
#define MANAGER_H
class Manager {
 public:
  static std::vector<std::shared_ptr<ROBOT>> robot;
  // #读取指令
  static void read();
  // #根据时间变化处理机器人热量
  static void preprocess(int time);
  // #A命令   新增一个机器人
  // @team    团队
  // @id      机器人标识符
  // @type    机器人类型
  static void add(int team, int id, int type);
  // #F命令   对一个机器人造成伤害
  // @team    团队
  // @id      机器人标识符
  // @atk     造成的伤害数值
  static void hurt(int team, int id, int atk);
  // #H命令   把一个机器人的热量上升指定值
  // @team    团队
  // @id      机器人标识符
  // @atk     热量指定值
  static void heat(int team, int id, int hot);
  // #U命令   将一个机器人上升到该等级
  // @team    团队
  // @id      机器人标识符
  // @lv      等级指定值
  static void up(int team, int id, int lv);
};
#endif