//
//  InputComponent.cpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/9.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#include "InputComponent.hpp"

InputComponent::InputComponent(class Actor* actor, int updateOrder)
:Component(actor, updateOrder)
{
    
}

void InputComponent::Update(float deltaTime)
{
    // 获取键盘状态
    const Uint8* stat = SDL_GetKeyboardState(NULL);
    mState = ENone;
    if (stat[SDL_SCANCODE_W]) {
        mState = EUp;
    }
    else if (stat[SDL_SCANCODE_S]) {
        mState = EDown;
    }
}
