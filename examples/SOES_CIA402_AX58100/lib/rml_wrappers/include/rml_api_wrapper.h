#pragma once

#ifdef __cplusplus
extern "C" {
#endif
    typedef void* rml_api_ptr_t;
    rml_api_ptr_t rml_api_create(void);
    void rml_api_destroy(rml_api_ptr_t tr);
#ifdef __cplusplus
}
#endif