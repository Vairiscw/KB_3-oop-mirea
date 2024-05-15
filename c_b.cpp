#include "c_b.h"
#include <queue>
c_b::c_b(c_b* base, string obj_name) : name(obj_name), p_head_obj(base) {
    if(base) {
        base->sub_objs.push_back(this);
    }
}

c_b::~c_b() {
    for (auto & sub_obj : sub_objs) {
        delete sub_obj;
    }
}

bool c_b::setName(string new_name) {
    bool f = true;
    for (int i = 0; i < sub_objs.size(); ++i) {
        if (sub_objs[i]->getName() == new_name) f = false;
    }
    if (f) name = new_name;
    return f;
}

string c_b::getName() {
    return name;
}

c_b* c_b::getHead() {
    return p_head_obj;
}

void c_b::printTree(int prob) {
    cout << "\n" << string(prob, ' ') << this->name;
    for(auto sub : sub_objs) sub->printTree(prob + 4);
}

void c_b::printStatus(int prob) {
    cout << "\n" << string(prob, ' ') << this->name;
    if (this->status != 0) cout << " is ready";
    else cout << " is not ready";
    for(auto sub : sub_objs) sub->printStatus(prob + 4);
}

void c_b::setStatus(int stat) {
    if(p_head_obj == nullptr || p_head_obj->status != 0) this->status = stat;
    if(stat == 0){
        this->status = stat;
        for(auto sub : sub_objs) sub->setStatus(0);
    }
}

c_b* c_b::getSubByName(string sub_name) {
    for (int i = 0; i < sub_objs.size(); ++i) {
        if (sub_objs[i]->name == sub_name) return sub_objs[i];
    }
    return nullptr;
}


c_b* c_b::findOnBranch(string name) {
    c_b * find = nullptr, * tmp = this;
    queue<c_b*> q;
    q.push(this);
    while (!q.empty()) {
        c_b* p_f = q.front();
        q.pop();
        if (p_f->getName() == name) {
            if (find != nullptr) return nullptr;
            find = p_f;
        }
        for(auto sub : p_f->sub_objs) q.push(sub);
    }
    return find;
}

c_b* c_b::findOnTree(string name){
    if (p_head_obj != nullptr) {
        return p_head_obj->findOnTree(name);
    }
    return findOnBranch(name);
}


bool c_b::changeHeadOfTree(c_b* new_head) {
    if (new_head == nullptr || this->getHead() == nullptr) {
        return false;
    }

    c_b* a = new_head;
    while (a != nullptr && a != this) {
        a = a->getHead();
    }
    if (a == this) {
        new_head->changeHeadOfTree(this->getHead());
    }
    c_b* old_head = this->getHead();
    if (old_head != nullptr) {
        for(int i = 0; i < old_head->sub_objs.size(); ++i) {
            if (old_head->sub_objs[i]->getName() == this->getName()) {
                old_head->sub_objs.erase(old_head->sub_objs.begin() + i);
            }
        }
    }
    this->p_head_obj = new_head;
    new_head->sub_objs.push_back(this);
    return true;
}

void c_b::deleteObjByName(string name) {
    for(int i = 0; i < sub_objs.size(); ++i) {
        if (sub_objs[i]->getName() == name) {
            sub_objs[i]->p_head_obj = nullptr;
            sub_objs.erase(sub_objs.begin() + i);
        }
    }
}

c_b* c_b::getObjByPath(string path) {
    c_b* p = nullptr;
    vector<string> names;
    if(path.length() == 1) {
        if (path == "/") {
            p = this;
            while (p->getHead() != nullptr) p = p->getHead();
        } else if (path == ".") {
            p = this;
        }
    } else if (path.length() > 1) {
        istringstream iss(path);
        for(string now; getline(iss, now, '/');) {
            names.push_back(now);
        }
        if (path[0] == '/' && path[1] == '/') {
            p = findOnTree(names[2]);
        } else if (path[0] == '.') {
            path.erase(path.begin());
            p = findOnBranch(path);
        } else if (path[0] == '/') {
            p = this;
            while (p->getHead() != nullptr) p = p->getHead();
            for(int i = 1; i < names.size() && p != nullptr; ++i) {
                p = p->getSubByName(names[i]);
            }
        } else {
            p = this;
            for(int i = 0; i < names.size() && p != nullptr; ++i) {
                p = p->getSubByName(names[i]);
            }
        }
    }
    return p;
}

