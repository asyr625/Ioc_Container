#ifndef IOC_CONTAINER2_H
#define IOC_CONTAINER2_H

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
using namespace std;

#include "any.h"
#include "non_copyable.h"
class Ioc_Container2 : Non_Copyable
{
public:
    Ioc_Container2() {}
    ~Ioc_Container2() {}

    template<class T, typename Depend, typename... Args>
    void register_type(const string& str_key)
    {
        std::function<T*(Args...)> function_creator = [](Args...args){return new T(new Depend(args...));};
        m_creator_map[str_key] = function_creator;
    }

    template<class T, typename... Args>
    T* resolve(const string& str_key, Args... args)
    {
        if( m_creator_map.find(str_key) == m_creator_map.end() )
            return nullptr;
        Any resolver = m_creator_map[str_key];
        std::function<T*(Args...)> function = resolver.any_cast<std::function<T*(Args...)>>();
        return function(args...);
    }

    template<class T, typename... Args>
    std::shared_ptr<T> resolve_shared(const string& str_key, Args... args)
    {
        T* t = resolve<T>(str_key, args...);
        return std::shared_ptr<T>(t);
    }

private:
    void register_type(const string &str_key, Any creator)
    {
        if( m_creator_map.find(str_key) != m_creator_map.end() )
            throw std::invalid_argument("this key has already exist!");
        //m_creator_map[str_key] = creator;
        m_creator_map.emplace(str_key, creator);
    }

    unordered_map<string, Any> m_creator_map;
};

#endif // IOC_CONTAINER2_H
