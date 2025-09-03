#include <rml_api_wrapper.h>

#include <ReflexxesAPI.h>

rml_api_ptr_t rml_api_create(void) {
    /*
        Да, это динамическая память. Но так как (скорее всего) таких объектов будет всего
        1-2 и они не будут удаляться до завершения программы (то есть никогда), то всё ок.
    */
    return new ReflexxesAPI(1, 0.1);
}

void rml_api_destroy(rml_api_ptr_t ptr) {
    /*
        Вряд ли пригодится, но пусть будет.
    */
    delete static_cast<ReflexxesAPI*>(ptr);
}