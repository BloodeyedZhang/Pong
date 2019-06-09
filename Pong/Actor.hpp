//
//  Actor.hpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/8.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp

#include <vector>
#include "Component.hpp"


class Actor
{
public:
    virtual ~Actor() = 0;
    void Update(float deltaTime);
    enum State { EActive, EDead };
    State GetState() { return mState; };
protected:
    // 当前角色状态
    State mState;
    // 组件集合
    std::vector<class Component*> mComponents;
    virtual void UpdateActor(float deltaTime) = 0;
    void AddComponent(class Component* comp);
    void RemoveComponent(class Component* comp);
    void UpdateComponents(float deltaTime);
};

#endif /* Actor_hpp */
