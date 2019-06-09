//
//  Paddle.hpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/8.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#ifndef Paddle_hpp
#define Paddle_hpp

#include "Actor.hpp"
#include "InputComponent.hpp"
#include "TransformComponent.hpp"

class Paddle : public Actor
{
public:
    Paddle();
    void UpdateActor(float deltaTime) override;
};

#endif /* Paddle_hpp */
