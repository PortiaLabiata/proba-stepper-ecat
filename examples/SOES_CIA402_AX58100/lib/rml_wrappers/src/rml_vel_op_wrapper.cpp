#include "rml_vel_op_wrapper.h"
#include <RMLVelocityOutputParameters.h>

rml_vel_op_ptr_t rml_vel_op_create(void) {
    return new RMLVelocityOutputParameters(1);
}

void rml_vel_op_destroy(rml_vel_op_ptr_t ptr) {
    delete static_cast<RMLVelocityOutputParameters*>(ptr);
}