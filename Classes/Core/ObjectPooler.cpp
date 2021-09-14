#include "ObjectPooler.h"

#include "DefaultValues.h"
#include "Object.h"

ObjectPooler* ObjectPooler::_Instnce = nullptr;


ObjectPooler* ObjectPooler::getInstance()
{
    if (_Instnce == nullptr) {
        _Instnce = new ObjectPooler;
    }
    return _Instnce;
}

void ObjectPooler::reset()
{
    _BulletList.clear();
    _enemyList.clear();
}


Object* ObjectPooler::getAgent(int atag)
{
    if ((atag == TAG_BULLET && _BulletList.empty()) 
            || (atag == TAG_ENEMY && _enemyList.empty()))
    {
        return Object::create(atag);
    }
    
    if (atag == TAG_BULLET) 
    {
       
        Object* resource = _BulletList.front();
        _BulletList.pop_front();
       
        return resource;
    }
    if (atag == TAG_ENEMY)
    {
        Object* resource = _enemyList.front();
        _enemyList.pop_front();
        
        return resource;
    }
}


void ObjectPooler::returnAgent(Object* object)
{
    if (object->getTag() == TAG_BULLET) 
    {
        _BulletList.push_back(object);
    }
    else if (object->getTag() == TAG_ENEMY)
    {
        _enemyList.push_back(object);
        object->reset();
    }
    
}
