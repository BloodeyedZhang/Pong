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
                               "游戏环境搭建",    // 标题
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
    // 交换前后缓冲区
    SDL_RenderPresent(mRenderer);
}
