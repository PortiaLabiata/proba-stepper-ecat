#include "rml_vel_ip_wrapper.h"
#include <RMLVelocityInputParameters.h>

rml_vel_ip_ptr_t rml_vel_ip_create(void) {
    return new RMLVelocityInputParameters(1);
}

void rml_vel_ip_destroy(rml_vel_ip_ptr_t ptr) {
    delete static_cast<RMLVelocityInputParameters*>(ptr);
}

/* Setters */

void rml_vel_ip_current_pos_set(rml_vel_ip_ptr_t ptr, double pos) {
    static_cast<RMLVelocityInputParameters*>(ptr)->CurrentPositionVector->VecData[0] = pos;
}

void rml_vel_ip_current_vel_set(rml_vel_ip_ptr_t ptr, double vel) {
    static_cast<RMLVelocityInputParameters*>(ptr)->CurrentVelocityVector->VecData[0] = vel;
}

void rml_vel_ip_current_acc_set(rml_vel_ip_ptr_t ptr, double acc) {
    static_cast<RMLVelocityInputParameters*>(ptr)->CurrentAccelerationVector->VecData[0] = acc;
}

void rml_vel_ip_max_acc_set(rml_vel_ip_ptr_t ptr, double acc) {
    static_cast<RMLVelocityInputParameters*>(ptr)->MaxAccelerationVector->VecData[0] = acc;
}

void rml_vel_ip_max_jerk_set(rml_vel_ip_ptr_t ptr, double jerk) {
    static_cast<RMLVelocityInputParameters*>(ptr)->MaxJerkVector->VecData[0] = jerk;
}

void rml_vel_ip_target_vel_set(rml_vel_ip_ptr_t ptr, double vel) {
    static_cast<RMLVelocityInputParameters*>(ptr)->TargetVelocityVector->VecData[0] = vel;
}

void rml_vel_ip_selection_set(rml_vel_ip_ptr_t ptr, bool selection) {
    static_cast<RMLVelocityInputParameters*>(ptr)->SelectionVector->VecData[0] = selection;
}