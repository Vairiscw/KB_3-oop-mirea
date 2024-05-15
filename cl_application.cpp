#include "cl_application.h"
#include "classes/c_2.h"
#include "classes/c_3.h"
#include "classes/c_4.h"
#include "classes/c_5.h"
#include "classes/c_6.h"

cl_application::cl_application(c_b* base) : c_b(base) {}

int cl_application::exec_app() {
    cout << "Object tree";
    printTree(0);
    cout << endl;
    c_b* tmp = this, *tmp1 = this;
    string command, path, cur_path = "/";
    vector<string> names;
    while (command != "END") {
        cin >> command;
        names.clear();
        if (command == "FIND") {
            cin >> path;
            istringstream iss(path);
            for(string now; getline(iss, now, '/');) {
                names.push_back(now);
            }
            if(tmp->getObjByPath(path) != nullptr) {
                cout << path << "     Object name: " << tmp->getObjByPath(path)->getName() << endl;
            } else {
                cout << path << "     Object is not found" << endl;
            }
        } else if (command == "SET") {
            cin >> path;
            istringstream iss(path);
            for(string now; getline(iss, now, '/');) {
                names.push_back(now);
            }
            if(tmp->getObjByPath(path) != nullptr) {
                tmp = tmp->getObjByPath(path);
                cur_path = path;
                if(cur_path[0] == '.' || cur_path[0] == '/') cur_path.erase(cur_path.begin());
                cout << "Object is set: " << tmp->getName() << endl;
            } else {
                cout << "The object was not found at the specified coordinate: " << path << endl;
            }
        } else if (command == "MOVE") {
            cin >> path;
            tmp1 = tmp->getObjByPath(path);

            bool cnt = false; c_b* find = tmp1;
            while(find != nullptr && find != tmp) find = find->getHead();

            if (tmp1 == nullptr) {
                cout << cur_path << "     Head object is not found" << endl;
            } else if (tmp1->getSubByName(tmp->getName()) != nullptr) {
                cout << path << "     Dubbing the names of subordinate objects" << endl;
            } else if (tmp->findOnBranch(tmp1->getName()) == tmp1 || find == tmp) {
                cout << path << "     Redefining the head object failed" << endl;
            } else if (tmp->changeHeadOfTree(tmp1) == 0) {
                cout << cur_path << "     Redefining the head object failed" << endl;
            } else {
                cout << "New head object: " << tmp1->getName() << endl;
            }
        } else if (command == "DELETE") {
            cin >> path;
            if (tmp->getSubByName(path) != nullptr){
                tmp->deleteObjByName(path);
                cout << "The object /" << cur_path << "/" << path << " has been deleted" << endl;
            }
        } else if (command == "END") {
            cout << "Current object hierarchy tree";
            break;
        }
    }
    printTree(0);
    return 0;
}

void cl_application::build_tree_objects() {
    c_b* base = this, *tmp;
    int num;
    string base_name, new_name, path;
    cin >> base_name;
    setName(base_name);
    bool f = false;
    while(true) {
        cin >> path;
        if (path == "endtree") break;
        cin >> new_name >> num;
        tmp = getObjByPath(path);
        if (tmp != nullptr && tmp->findOnBranch(new_name) == nullptr) {
            if (num == 2) new c_2(tmp, new_name);
            if (num == 3) new c_3(tmp, new_name);
            if (num == 4) new c_4(tmp, new_name);
            if (num == 5) new c_5(tmp, new_name);
            if (num == 6) new c_6(tmp, new_name);
        } else if (tmp == nullptr) {
            cout << "Object tree";
            printTree(0);
            cout << "\nThe head object " << path << " is not found";
            exit(1);
        } else if (tmp->findOnBranch(new_name) != nullptr){
            if (num == 2) new c_2(tmp, new_name);
            if (num == 3) new c_3(tmp, new_name);
            if (num == 4) new c_4(tmp, new_name);
            if (num == 5) new c_5(tmp, new_name);
            if (num == 6) new c_6(tmp, new_name);
            //cout << endl << path << "     Dubbing the names of subordinate objects\n";
        }
    }
    //cout << "\nr\n    b\n        a\n            b\n                c\n                    a\n                        a";
    //cout << "                        b";
}
