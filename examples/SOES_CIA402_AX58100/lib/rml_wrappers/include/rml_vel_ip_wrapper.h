#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    typedef void* rml_vel_ip_ptr_t;
    rml_vel_ip_ptr_t rml_vel_ip_create(void);
    void rml_vel_ip_destroy(rml_vel_ip_ptr_t ptr);

    void rml_vel_ip_current_pos_set(rml_vel_ip_ptr_t ptr, double pos);
    void rml_vel_ip_current_vel_set(rml_vel_ip_ptr_t ptr, double vel);
    void rml_vel_ip_current_acc_set(rml_vel_ip_ptr_t ptr, double acc);

    void rml_vel_ip_max_acc_set(rml_vel_ip_ptr_t ptr, double acc);
    void rml_vel_ip_max_jerk_set(rml_vel_ip_ptr_t ptr, double jerk);
    void rml_vel_ip_target_vel_set(rml_vel_ip_ptr_t ptr, double vel);
    void rml_vel_ip_selection_set(rml_vel_ip_ptr_t ptr, bool selection);
#ifdef __cplusplus
}
#endif