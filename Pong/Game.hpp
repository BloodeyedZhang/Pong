//
//  Game.hpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/1.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#ifndef Game_hpp
#define Game_hpp

#include <SDL2/SDL.h>

const int kThickness = 15; //墙的厚度
const float kPaddleH = 100.0f; // 控制球拍的长度

// Vector2 结构之存储x和y坐标
struct Vector2
{
    float x;
    float y;
};

// Game class
class Game
{
public:
    Game();
    // 游戏初始化
    bool Initialize();
    // 运行游戏循环，直到游戏结束
    void RunLoop();
    // 关闭游戏
    void Shutdown();
private:
    // 处理进程输入
    void ProcessInpput();
    // 更新游戏
    void UpdateGame();
    // 生成输出
    void GenerateOutput();
    
    // 通过SDL创建窗体
    SDL_Window* mWindow;
    // 渲染器
    SDL_Renderer* mRenderer;
    // 继续运行
    bool mIsRunning;
    // 球拍位置
    Vector2 mPaddlePos;
    // 球拍方向
    int mPaddleDir;
    // 球的位置
    Vector2 mBallPos;
    // 球的速度
    Vector2 mBallVel;
    // 运行时间
    Uint32 mTicksCount;
};

#endif /* Game_hpp */
