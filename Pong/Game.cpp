//
//  Game.cpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/1.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#include "Game.hpp"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mTicksCount(0)
{
}

bool Game::Initialize()
{
    // 初始化SDL库
    int sdlResult = SDL_Init(SDL_INIT_VIDEO);
    if (sdlResult != 0)
    {
        SDL_Log("不能初始化 SDL：%s", SDL_GetError());
        return false;
    }
    mWindow = SDL_CreateWindow(
                               "Pong",    // 标题
                               100,             // 窗体左上角的x坐标
                               100,             // 窗体左上角的y坐标
                               1024,            // 窗体宽度
                               768,             // 窗体高度
                               0                //标志位
                               );
    if (!mWindow)
    {
        SDL_Log("创建窗体失败：%s", SDL_GetError());
        return false;
    }
    // 初始化渲染器
    mRenderer = SDL_CreateRenderer(
                                   mWindow,
                                   -1,
                                   SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
                                   );
    if (!mRenderer)
    {
        SDL_Log("创建渲染器失败：%s", SDL_GetError());
        return false;
    }
    // 初始化球拍和球的坐标
    mPaddlePos.x = 10.0f;
    mPaddlePos.y = 768.0f / 2.0f;
    mBallPos.x = 1024.0f / 2.0f;
    mBallPos.y = 768.0f / 2.0f;
    
    return true;
}

void Game::RunLoop()
{
    while (mIsRunning)
    {
        ProcessInpput();
        UpdateGame();
        GenerateOutput();
    }
}

void Game::Shutdown()
{
    SDL_DestroyRenderer(mRenderer);
    SDL_DestroyWindow(mWindow);
    SDL_Quit();
}

void Game::ProcessInpput()
{
    SDL_Event event;
    
    // 有event在队列就一直循环
    while (SDL_PollEvent(&event)) {
        switch (event.type)
        {
            case SDL_QUIT:
                mIsRunning = false;
                break;
            default:
                break;
        }
    }
    
    // 获取键盘状态
    const Uint8* stat = SDL_GetKeyboardState(NULL);
    // 如果按了Esc,则结束循环
    if (stat[SDL_SCANCODE_ESCAPE])
    {
        mIsRunning = false;
    }
}

void Game::UpdateGame()
{
    // 等到与上一帧间隔 16ms
    while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16))
        ;
    
    // 增量时间是上一帧到现在的时间差
    // 转换成（秒）
    float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;
    // 固定增量时间最大值
    if (deltaTime > 0.05f)
    {
        deltaTime = 0.05f;
    }
    
    // 更新运行时间
    mTicksCount = SDL_GetTicks();
}

void Game::GenerateOutput()
{
    // 设置Tiffany蓝
    SDL_SetRenderDrawColor(
                           mRenderer,
                           129,         // R
                           216,         // G
                           209,         // B
                           255          // A
                           );
    
    // 清理后缓冲区
    SDL_RenderClear(mRenderer);
    // 设置绘制颜色
    SDL_SetRenderDrawColor(mRenderer, 0, 0, 255, 255);
    // 顶部墙参数
    SDL_Rect wall {
        0, //左上x坐标
        0, //左上Y坐标
        1024,  //宽度
        kThickness //高度
    };
    SDL_RenderFillRect(mRenderer, &wall);
    // 绘制底部墙
    wall.y = 768 - kThickness;
    SDL_RenderFillRect(mRenderer, &wall);
    // 绘制右边的墙
    wall = {
        1024 - kThickness,
        0,
        kThickness,
        1024
    };
    SDL_RenderFillRect(mRenderer, &wall);
    
    // 绘制球拍
    SDL_Rect paddle {
        static_cast<int>(mPaddlePos.x),
        static_cast<int>(mPaddlePos.y - kPaddleH / 2),
        kThickness,
        static_cast<int>(kPaddleH)
    };
    SDL_RenderFillRect(mRenderer, &paddle);
    
    // 绘制球
    SDL_Rect ball {
        static_cast<int>(mBallPos.x - kThickness / 2),
        static_cast<int>(mBallPos.y - kThickness / 2),
        kThickness,
        kThickness
    };
    SDL_RenderFillRect(mRenderer, &ball);
    
    // 交换前后缓冲区
    SDL_RenderPresent(mRenderer);
}
