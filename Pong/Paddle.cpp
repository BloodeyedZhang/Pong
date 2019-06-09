//
//  Paddle.cpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/8.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#include "Paddle.hpp"

Paddle::Paddle()
{
    int updateOrder = 100;
    Component* input = new InputComponent(this, updateOrder++);
    this->AddComponent(input);
    Component* transform = new TransformComponent(this, updateOrder++, 10.0f, 768.9f / 2.0f);
    this->AddComponent(transform);
}

void Paddle::UpdateActor(float deltaTime)
{
    
}
