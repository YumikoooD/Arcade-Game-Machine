/*
** EPITECH PROJECT, 2024
** Arcade
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
    #define DLLOADER_HPP_

#include <dlfcn.h>
#include <string>
#include <memory>
#include <iostream>
#include "IDLLoader.hpp"

// Load a library that has a fonction to create a pointer using new
template <typename T>
class DLLoader : public ADLLoader<T, void *>{
    public:
        // @brief Load a lib in memory
        // @param path Path to thefile
        DLLoader(const std::string &path) {
            DLLoader::ADLLoader::_lib = dlopen(path.c_str(), RTLD_LAZY);
            if (DLLoader::ADLLoader::_lib == nullptr) {
                std::cerr << dlerror() << std::endl;
                std::__throw_system_error(2);
            }
        };
        ~DLLoader() {
            if (DLLoader::ADLLoader::instance != nullptr)
                DLLoader::ADLLoader::instance = nullptr;
            dlclose(DLLoader::ADLLoader::_lib);
        };
        // @brief Return a pointer to an instance of @c T created using the `name` fonction
        // @note IT IS AUTOMATICALLY FREED, DO NOT DELETE IT
        // @param name The name of the fonction that creates a @c T instance using new
        // @return The pointer to the instance
        T *getInstance(const std::string &name) override {
            if (DLLoader::ADLLoader::instance != nullptr)
                return DLLoader::ADLLoader::instance.get();
            T *(*f)() = reinterpret_cast<T *(*)()>(dlsym(DLLoader::ADLLoader::_lib, name.c_str()));
            if (f == nullptr) {
                std::cerr << dlerror() << std::endl;
                std::__throw_system_error(38);
            }
            DLLoader::ADLLoader::instance.reset(f());
            return DLLoader::ADLLoader::instance.get();
        };
};

#endif /* !DLLOADER_HPP_ */
