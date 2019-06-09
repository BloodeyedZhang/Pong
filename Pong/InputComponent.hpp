//
//  InputComponent.hpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/9.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#ifndef InputComponent_hpp
#define InputComponent_hpp

#include <SDL2/SDL.h>
#include "Component.hpp"

class InputComponent : public Component
{
public:
    InputComponent(class Actor* actor, int updateOrder);
    void Update(float deltaTime);
    enum State { ENone, EUp, EDown };
    State GetState() { return mState; };
private:
    State mState;
};

#endif /* InputComponent_hpp */
