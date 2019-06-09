//
//  TransformComponent.cpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/9.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#include "TransformComponent.hpp"

TransformComponent::TransformComponent(class Actor* actor, int updateOrder, float x, float y)
:Component(actor, updateOrder)
{
    mPosition.x = x;
    mPosition.y = y;
    mVal.x = 0;
    mVal.y = 0;
    std::cout << "TransformComponent construct" << std::endl;
}


void TransformComponent::Update(float deltaTime)
{
    if (mVal.x != 0)
        mPosition.x = mVal.x * deltaTime;
    if (mVal.y != 0)
        mPosition.y = mVal.y * deltaTime;
}
