#include "Manager.h"

#include <iostream>
#include <memory>
#include <vector>

#include "Robot.h"
std::vector<std::shared_ptr<ROBOT>> Manager::robot;
void Manager::read() {
  int N, last_time;
  std::cin >> N;
  for (int i = 0; i < N; i++) {
    char key;
    int time, para1, para2, para3;
    std::cin >> time >> key >> para1 >> para2 >> para3;
    Manager::preprocess(time - last_time);
    if (key == 'A') Manager::add(para1, para2, para3);
    if (key == 'F') Manager::hurt(para1, para2, para3);
    if (key == 'H') Manager::heat(para1, para2, para3);
    if (key == 'U') Manager::up(para1, para2, para3);
    last_time = time;
  }
}
void Manager::preprocess(int time) {
  for (auto i = 0; i < Manager::robot.size(); i++) {
    auto ptr = Manager::robot[i].get();
    if (!ptr->died) {
      if (ptr->HOT > ptr->MAX_HOT) {
        if (ptr->HOT - ptr->MAX_HOT >= time) {
          ptr->HP -= time;
          ptr->HOT -= time;
        } else {
          ptr->HP -= ptr->HOT - ptr->MAX_HOT;
          ptr->HOT -= ptr->HOT - ptr->MAX_HOT;
        }
        if (ptr->HP <= 0) {
          ptr->died = true;
          std::cout << "D " << ptr->TEAM << " " << ptr->ID << std::endl;
        }
      }
    }
  }
}
void Manager::add(int team, int id, int type) {
  for (auto i = 0; i < Manager::robot.size(); i++) {
    auto ptr = Manager::robot[i].get();
    if (ptr->ID == id && ptr->TEAM == team && ptr->TYPE == type) {
      //判断是否死亡 并将属性值复活
      if (ptr->died) {
        ptr->HP = ptr->MAX_HP;
        ptr->HOT = 0;
        ptr->died = false;
      }
      return;
    }
  }
  //若不存在 则新建一个机器人
  if (type == 0) {
    std::shared_ptr<Infantry> infantry = std::make_shared<Infantry>(team, id);
    Manager::robot.push_back(std::shared_ptr<ROBOT>(infantry));
  } else if (type == 1) {
    std::shared_ptr<Engineer> engineer = std::make_shared<Engineer>(team, id);
    Manager::robot.push_back(std::shared_ptr<ROBOT>(engineer));
  }
}
void Manager::hurt(int team, int id, int atk) {
  for (auto i = 0; i < Manager::robot.size(); i++) {
    auto ptr = Manager::robot[i].get();
    if (ptr->ID == id && ptr->TEAM == team && !ptr->died) {
      ptr->HP -= atk;
      if (ptr->HP <= 0) {
        ptr->died = true;
        std::cout << "D " << ptr->TEAM << " " << ptr->ID << std::endl;
      }
      return;
    }
  }
}
void Manager::heat(int team, int id, int hot) {
  for (auto i = 0; i < Manager::robot.size(); i++) {
    auto ptr = Manager::robot[i].get();
    if (ptr->ID == id && ptr->TEAM == team && !ptr->died) {
      //判断是否为步兵
      if (ptr->TYPE == 0) ptr->HOT += hot;
      return;
    }
  }
}
void Manager::up(int team, int id, int lv) {
  for (auto i = 0; i < Manager::robot.size(); i++) {
    auto ptr = Manager::robot[i].get();
    if (ptr->ID == id && ptr->TEAM == team && !ptr->died) {
      //判断是否为步兵
      if (ptr->TYPE == 0) {
        if (ptr->level < lv) {
          ptr->level = lv;
          if (lv == 2) {
            ptr->MAX_HOT = 200;
            ptr->MAX_HP = 150;
          } else if (lv == 3) {
            ptr->MAX_HOT = 300;
            ptr->MAX_HP = 250;
          }
        }
      }
      return;
    }
  }
}