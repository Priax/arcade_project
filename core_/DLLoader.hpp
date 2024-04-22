/*
** EPITECH PROJECT, 2024
** B-OOP-400-MAR-4-1-arcade-vincent.montero-fontaine
** File description:
** DLLoader
*/

#ifndef DLLOADER_HPP_
#define DLLOADER_HPP_

#include <iostream>
#include <dlfcn.h>
#include <memory>
namespace arcade
{
    template <typename T> class DLLoader;
}

template <typename T>
class arcade::DLLoader
{
public:
    DLLoader();
    DLLoader(std::string &path);
    ~DLLoader();
    void loadInstance(std::string &path);
    T* getInstance(std::string instance) const;

private:
    void *_handle = NULL;
};

template <typename T>
arcade::DLLoader<T>::DLLoader()
{
}

template <typename T>
arcade::DLLoader<T>::DLLoader(std::string &path)
{
    this->loadInstance(path);
}

template <typename T>
arcade::DLLoader<T>::~DLLoader()
{
    if (this->_handle) {
        dlclose(this->_handle);
    }
}

template <typename T>
T* arcade::DLLoader<T>::getInstance(std::string instance) const
{
    typedef T *(*object)();
    char *error = NULL;

    if (!this->_handle)
        return nullptr;
    dlerror();
    object conversion = (object)dlsym(this->_handle, instance.c_str());
    error = dlerror();
    if (error) {
        throw std::string(error);
    }
    return conversion();
}

template <typename T>
void arcade::DLLoader<T>::loadInstance(std::string &path)
{
    this->_handle = dlopen(path.c_str(), RTLD_LAZY);
    if (!this->_handle)
        throw std::string(dlerror());
}

#endif /* !DLLOADER_HPP_ */
