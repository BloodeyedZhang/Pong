//
//  Component.hpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/8.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#ifndef Component_hpp
#define Component_hpp

#include <iostream>
#include "Consts.h"
#include "Actor.hpp"

class Component
{
public:
    // 构造函数
    Component (class Actor* actor, int updateOrder = 100);
    // 析构
    virtual ~Component();
    // 通过增量时间更新组件
    virtual void Update(float deltaTime) = 0;
    
    int GetUpdateOrder() const { return mUpdateOrder; };
protected:
    // 属于的角色
    class Actor* mOwer;
    // 组件的顺序
    int mUpdateOrder;
};

#endif /* Component_hpp */
