//
//  Actor.cpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/8.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#include "Actor.hpp"

Actor::~Actor()
{
    
}

void Actor::Update(float deltaTime)
{
    if (mState == EActive)
    {
        this->UpdateComponents(deltaTime);
        this->UpdateActor(deltaTime);
    }
}

void Actor::AddComponent(Component *comp)
{
    mComponents.push_back(comp);
}

void Actor::RemoveComponent(Component *comp)
{
    mComponents.emplace_back(comp);
}

void Actor::UpdateComponents(float deltaTime)
{
    for (auto component : mComponents)
    {
        component->Update(deltaTime);
    }
}

void Actor::UpdateActor(float deltaTime)
{
    
}
