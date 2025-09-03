#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    typedef void* rml_vel_op_ptr_t;
    rml_vel_op_ptr_t rml_vel_op_create(void);
    void rml_vel_op_destroy(rml_vel_op_ptr_t ptr);

    
#ifdef __cplusplus
}
#endif