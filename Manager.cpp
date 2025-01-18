#include "Manager.h"

#include <iostream>
#include <memory>
#include <vector>

#include "Robot.h"
//初始化静态成员变量
std::vector<std::shared_ptr<Robot>> Manager::robot;

void Manager::read() {
  //使用last_time记录时间差
  int N, last_time;
  std::cin >> N;
  // 循环N次，读取N条指令
  for (int i = 0; i < N; i++) {
    char key;
    int time, para1, para2, para3;
    std::cin >> time >> key >> para1 >> para2 >> para3;
    // 处理时间间隔内 热量导致的扣血
    Manager::preprocess(time - last_time);
    // A指令
    if (key == 'A') Manager::add(para1, para2, para3);
    // F指令
    if (key == 'F') Manager::hurt(para1, para2, para3);
    // H指令
    if (key == 'H') Manager::heat(para1, para2, para3);
    // U指令
    if (key == 'U') Manager::up(para1, para2, para3);
    //更新last_time
    last_time = time;
  }
}
void Manager::preprocess(int time) {
  // 循环每个机器人单位
  for (auto i = 0; i < Manager::robot.size(); i++) {
    auto ptr = Manager::robot[i].get();
    //判断是否死亡
    if (!ptr->is_died()) {
      //判断是否超热量
      if (ptr->get_hot() > ptr->get_max_hot()) {
        //判断超出的热量是否大于时间差
        if (ptr->get_hot() - ptr->get_max_hot() >= time) {
          // 扣除时间差的血量和热量
          ptr->set_hp(ptr->get_hp() - time);
          ptr->set_hot(ptr->get_hot() - time);
        } else {
          // 扣除超热量差的血量和热量
          ptr->set_hp(ptr->get_hp() - ptr->get_hot() + ptr->get_max_hot());
          ptr->set_hot(ptr->get_max_hot());
        }
        // 判断是否因热量超出而死
        if (ptr->get_hp() <= 0) {
          ptr->set_died(true);
          std::cout << "D " << ptr->get_team() << " " << ptr->get_id()
                    << std::endl;
        }
      }
    }
  }
}
void Manager::add(int team, int id, int type) {
  // 循环每个机器人单位
  for (auto i = 0; i < Manager::robot.size(); i++) {
    auto ptr = Manager::robot[i].get();
    //判断ID、团队、类型是否完全符合
    if (ptr->get_id() == id && ptr->get_team() == team &&
        ptr->get_type() == type) {
      //判断是否死亡
      if (ptr->is_died()) {
        // 将属性值复活
        ptr->set_hp(ptr->get_max_hp());
        ptr->set_hot(0);
        ptr->set_died(false);
      }
      return;
    }
  }
  //若不存在 则新建一个机器人
  //新建步兵机器人
  if (type == 0) {
    std::shared_ptr<Infantry> infantry = std::make_shared<Infantry>(team, id);
    Manager::robot.push_back(std::shared_ptr<Robot>(infantry));

  }
  //新建工程机器人
  else if (type == 1) {
    std::shared_ptr<Engineer> engineer = std::make_shared<Engineer>(team, id);
    Manager::robot.push_back(std::shared_ptr<Robot>(engineer));
  }
}
void Manager::hurt(int team, int id, int atk) {
  // 循环每个机器人单位
  for (auto i = 0; i < Manager::robot.size(); i++) {
    auto ptr = Manager::robot[i].get();
    //判断ID、团队是否符合 以及是否存活
    if (ptr->get_id() == id && ptr->get_team() == team && !ptr->is_died()) {
      ptr->set_hp(ptr->get_hp() - atk);
      //判断是否被打死了
      if (ptr->get_hp() <= 0) {
        ptr->set_died(true);
        std::cout << "D " << ptr->get_team() << " " << ptr->get_id()
                  << std::endl;
      }
      return;
    }
  }
}
void Manager::heat(int team, int id, int hot) {
  // 循环每个机器人单位
  for (auto i = 0; i < Manager::robot.size(); i++) {
    auto ptr = Manager::robot[i].get();
    //判断ID、团队是否符合 以及是否存活
    if (ptr->get_id() == id && ptr->get_team() == team && !ptr->is_died()) {
      //判断是否为步兵
      if (ptr->get_type() == 0) ptr->set_hot(ptr->get_hot() + hot);
      return;
    }
  }
}
void Manager::up(int team, int id, int lv) {
  // 循环每个机器人单位
  for (auto i = 0; i < Manager::robot.size(); i++) {
    auto ptr = Manager::robot[i].get();
    //判断ID、团队是否符合 以及是否存活
    if (ptr->get_id() == id && ptr->get_team() == team && !ptr->is_died()) {
      // 判断是否为步兵
      if (ptr->get_type() == 0) {
        // 判断目标等级是否大于步兵等级
        if (ptr->get_level() < lv) {
          ptr->set_level(lv);
        }
      }
      return;
    }
  }
}