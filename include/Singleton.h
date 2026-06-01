#pragma once

template<typename Class>
class Singleton
{

public:
    static Class& GetInstance()
    {
        static Class instance;
        return instance;
    }

};