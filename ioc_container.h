#ifndef IOC_CONTAINER_H
#define IOC_CONTAINER_H

#include <string>
#include <map>
#include <memory>
#include <functional>
using namespace std;

template<class T>
class Ioc_Container
{
public:
    Ioc_Container() {}
    ~Ioc_Container() {}

    template<class Deriverd>
    void register_type(string str_key)
    {
        std::function<T*()> function_creator = []{return new Deriverd;};
        register_type(str_key, function_creator);
    }

    T* resolve(string str_key)
    {
        if( m_creator_map.find(str_key) == m_creator_map.end() )
            return nullptr;
        std::function<T*()> function = m_creator_map[str_key];
        return function();
    }

    std::shared_ptr<T> resolve_shared(string str_key)
    {
        T* ptr = resolve(str_key);
        return std::shared_ptr<T>(ptr);
    }

private:
    void register_type(string str_key, std::function<T*()> creator)
    {
        if( m_creator_map.find(str_key) != m_creator_map.end() )
            throw std::invalid_argument("this key has already exist!");
        m_creator_map[str_key] = creator;
    }

    map<string, std::function<T*()>> m_creator_map;
};

#endif // IOC_CONTAINER_H
