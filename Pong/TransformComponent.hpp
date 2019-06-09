//
//  TransformComponent.hpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/9.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#ifndef TransformComponent_hpp
#define TransformComponent_hpp

#include <stdio.h>
#include "Component.hpp"

class TransformComponent : public Component
{
public:
    TransformComponent(class Actor* actor, int updateOrder, float x, float y);
    void Update(float deltaTime);
protected:
    // 位置
    Vector2 mPosition;
    // 速度
    Vector2 mVal;
};

#endif /* TransformComponent_hpp */
