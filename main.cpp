#include "cl_application.h"

int main()
{
    cl_application object_application(nullptr);
    object_application.build_tree_objects();
    return object_application.exec_app();
}
