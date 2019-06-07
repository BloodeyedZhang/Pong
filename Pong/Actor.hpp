//
//  Actor.hpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/8.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#ifndef Actor_hpp
#define Actor_hpp

enum ActorState
{
    EActive,
    EDead
};

class Actor
{
public:
    virtual void Update(float deltaTime);
    virtual void Draw();
    ActorState GetState() { return mState; };
protected:
    ActorState mState;
};

#endif /* Actor_hpp */
