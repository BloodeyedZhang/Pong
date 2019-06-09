//
//  Component.cpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/8.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#include "Component.hpp"

Component::Component(Actor* actor, int updateOrder)
{
    this->mOwer = actor;
    this->mUpdateOrder = updateOrder;
    std::cout << "Component construct" << std::endl;
}

Component::~Component()
{
    
}
