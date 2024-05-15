#ifndef KV3_OOP_CL_APPLICATION_H
#define KV3_OOP_CL_APPLICATION_H
#include "c_b.h"

class cl_application : public c_b {
public:
    cl_application(c_b* base);
    void build_tree_objects();
    int exec_app();
};
#endif //KV3_OOP_CL_APPLICATION_H
