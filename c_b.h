#ifndef KV3_OOP_C_B_H
#define KV3_OOP_C_B_H
#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class c_b {
    c_b * p_head_obj;
    vector<c_b*> sub_objs;
    string name;
    int status;
public:
    c_b (c_b* base, string obj_name = "Base Object");
    ~c_b();
    bool setName(string new_name);
    string getName();
    c_b* getHead();
    c_b* getSubByName(string sub_name);
    void printTree(int prob = 0);
    void printStatus(int prob = 0);
    c_b* findOnBranch(string name);
    c_b* findOnTree(string name);
    void setStatus(int stat);
    bool changeHeadOfTree(c_b* new_head);
    void deleteObjByName(string name);
    c_b* getObjByPath(string path);
    vector<string> parsPath(const string path);
};
#endif //KV3_OOP_C_B_H
