//rei
#pragma once
#include "il2cpp_api.h"

Il2CppImage* (*il2cpp_get_corlib)();
Il2CppObject* (*il2cpp_value_box2)(Il2CppClass* klass, void* data);

template<typename T>
Il2CppObject* il2cpp_value_box(Il2CppClass* cls, T data) {
    return il2cpp_value_box2(cls, &data);
}

Il2CppArray* (*il2cpp_array_new)(Il2CppClass* cls, il2cpp_array_size_t len);
Il2CppClass* (*il2cpp_class_from_name)(Il2CppImage* image, const char* namespaze, const char *name);
const MethodInfo* (*il2cpp_class_get_method_from_name)(Il2CppClass *klass, const char* name, int argsCount);
Il2CppObject* (*il2cpp_object_new)(Il2CppClass* cls);
void (*il2cpp_field_static_get_value)(FieldInfo *field, void* value);
void (*il2cpp_field_static_set_value)(FieldInfo *field, void* value);
FieldInfo* (*il2cpp_class_get_field_from_name)(Il2CppClass *cls, const char *name);
Il2CppDomain* (*il2cpp_domain_get)();
Il2CppAssembly* (*il2cpp_domain_assembly_open)(Il2CppDomain * domain, const char* name);
Il2CppImage* (*il2cpp_assembly_get_image)(Il2CppAssembly * assembly);

Il2CppImage* GetImageToAssembly(const char* assembly) {
    Il2CppDomain* domain = il2cpp_domain_get();
    Il2CppAssembly* domain_asm = il2cpp_domain_assembly_open(domain, assembly);
    Il2CppImage* asm_img = il2cpp_assembly_get_image(domain_asm);
    return asm_img;
}

Il2CppClass* int32;
Il2CppClass* byte;
Il2CppClass* boolean;
Il2CppClass* doubl;
Il2CppClass* single;
Il2CppClass* object;
Il2CppClass* str;
Il2CppImage* p3u3d;
Il2CppClass* hashtable;
Il2CppImage* corlib;

namespace il2cpp_api_wrapper {
    void initialize() {
        il2cpp_get_corlib = (Il2CppImage* (*)()) dlsym(RTLD_DEFAULT,("il2cpp_get_corlib"));
        il2cpp_value_box2 = (Il2CppObject* (*)(Il2CppClass*, void*)) dlsym(RTLD_DEFAULT,("il2cpp_value_box"));
        il2cpp_class_from_name = (Il2CppClass* (*)(Il2CppImage *, const char*, const char *)) dlsym(RTLD_DEFAULT,("il2cpp_class_from_name"));
        il2cpp_array_new = (Il2CppArray* (*)(Il2CppClass*, il2cpp_array_size_t)) dlsym(RTLD_DEFAULT,("il2cpp_array_new"));
        il2cpp_object_new = (Il2CppObject* (*)(Il2CppClass*)) dlsym(RTLD_DEFAULT,("il2cpp_object_new"));
        il2cpp_class_get_method_from_name = (const MethodInfo* (*)(Il2CppClass *, const char* , int )) dlsym(RTLD_DEFAULT,("il2cpp_class_get_method_from_name"));
        il2cpp_field_static_get_value = (void (*)(FieldInfo*, void*)) dlsym(RTLD_DEFAULT,("il2cpp_field_static_get_value"));
        il2cpp_field_static_set_value = (void (*)(FieldInfo*, void*)) dlsym(RTLD_DEFAULT,("il2cpp_field_static_set_value"));
        il2cpp_class_get_field_from_name = (FieldInfo* (*)(Il2CppClass*, const char *)) dlsym(RTLD_DEFAULT,("il2cpp_class_get_field_from_name"));
        il2cpp_domain_get = (Il2CppDomain* (*)()) dlsym(RTLD_DEFAULT,("il2cpp_domain_get"));
        il2cpp_domain_assembly_open = (Il2CppAssembly* (*)(Il2CppDomain*, const char*)) dlsym(RTLD_DEFAULT,("il2cpp_domain_assembly_open"));
        il2cpp_assembly_get_image = (Il2CppImage* (*)(Il2CppAssembly*)) dlsym(RTLD_DEFAULT,("il2cpp_assembly_get_image"));
    }
}