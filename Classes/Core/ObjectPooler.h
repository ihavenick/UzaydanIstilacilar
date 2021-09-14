#ifndef __OBJECT_POOLER_H_
#define __OBJECT_POOLERL_H_

#include <list>

class Object;

class ObjectPooler
{
private:
    ObjectPooler() {}

public:
    static ObjectPooler* getInstance();
    void reset();
    Object* getAgent(int);
    void returnAgent(Object*);

private:
    static ObjectPooler* _Instnce;
    std::list<Object*> _enemyList;
    std::list<Object*> _BulletList;
    
};

#endif