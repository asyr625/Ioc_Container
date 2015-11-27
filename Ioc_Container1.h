#ifndef IOC_CONTAINER1_H
#define IOC_CONTAINER1_H

#include <string>
#include <unordered_map>
#include <memory>
#include <functional>
using namespace std;

#include "any.h"

class Ioc_Container1
{
public:
    Ioc_Container1() {}
    ~Ioc_Container1() {}

    template<class T, typename Depend>
    void register_type(const string& str_key)
    {
        std::function<T*()> function_creator = []{return new T(new Depend());};
        //m_creator_map[str_key] = function_creator;
        register_type(str_key, function_creator);
    }

    template<class T>
    T* resolve(const string& str_key)
    {
        if( m_creator_map.find(str_key) == m_creator_map.end() )
            return nullptr;
        Any resolver = m_creator_map[str_key];
        std::function<T*()> function = resolver.any_cast<std::function<T*()>>();
        return function();
    }

    template<class T>
    std::shared_ptr<T> resolve_shared(const string& str_key)
    {
        T* t = resolve<T>(str_key);
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
#endif // IOC_CONTAINER1_H
