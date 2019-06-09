//
//  Game.cpp
//  Pong
//
//  Created by 张佳俊 on 2019/6/1.
//  Copyright © 2019 张佳俊. All rights reserved.
//

#include "Game.hpp"
#include "Paddle.hpp"

Game::Game()
:mWindow(nullptr)
,mRenderer(nullptr)
,mIsRunning(true)
,mTicksCount(0)
,mPaddleDir(0)
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
    mBallVel = {-200.0f, 235.0f};
    new Paddle();
    
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
    // 通过w/s更新球拍位置
    mPaddleDir = 0;
    if (stat[SDL_SCANCODE_W]) {
        mPaddleDir -= 1;
    }
    else if (stat[SDL_SCANCODE_S]) {
        mPaddleDir += 1;
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
    
    // 更新所欲的 actors
    mUpdatingActors = true;
    for (auto actor : mActors)
    {
        actor->Update(deltaTime);
    }
    mUpdatingActors = false;
    
    // 将待定的 actor 加入到 mActors
    for (auto pending : mPendingActors)
    {
        mActors.emplace_back(pending);
    }
    mPendingActors.clear();
    
    // 添加废弃的 actor 到另一个临时变量
    std::vector<Actor *> deadActors;
    for (auto actor : mActors)
    {
        if (actor->GetState() == Actor::EDead)
        {
            deadActors.emplace_back(actor);
        }
    }
    
    // 删除废弃的 actor
    for (auto actor : deadActors)
    {
        delete actor;
    }
    
    // 根据方向更新球拍位置
    if (mPaddleDir != 0) {
        mPaddlePos.y += mPaddleDir * 300.0f * deltaTime;
    }
    // 确保球拍不会移出窗口
    if (mPaddlePos.y < (kPaddleH / 2.0f + kThickness)) {
        mPaddlePos.y = kPaddleH / 2.0f + kThickness;
    }
    else if (mPaddlePos.y > (768.0 - kPaddleH / 2.0f - kThickness)) {
        mPaddlePos.y = 768.0 - kPaddleH / 2.0f - kThickness;
    }
    
    // 更新球
    // 球是否和顶部墙相碰
    if (mBallPos.y <= kThickness && mBallVel.y < 0.0f) {
        mBallVel.y *= -1.0f;
    }
    // 球是否和底部墙相碰
    else if (mBallPos.y >= (768 - kThickness) && mBallVel.y > 0.0f) {
        mBallVel.y *= -1.0f;
    }
    // 是否和球拍相交
    float diff = mPaddlePos.y - mBallPos.y;
    diff = diff > 0.0f ? diff : -diff;
    if (
        // y分量足够小
        diff <= kPaddleH / 2.0f &&
        // 球拍的x范围内
        mBallPos.x <= 25.0f && mBallPos.x >= 20.0f &&
        // 球正在向左运动
        mBallVel.x < 0.0f
        )
    {
        mBallVel.x *= -1.0f;
    }
    // 如果球出了窗口，则游戏结束
    else if (mBallPos.x <= 0.0f) {
        mIsRunning = false;
    }
    // 如果球碰到右边的墙，则反弹
    else if (mBallPos.x >= (1024.0 - kThickness) && mBallVel.x > 0.0f) {
        mBallVel.x *= -1.0f;
    }
    mBallPos.x += mBallVel.x * deltaTime;
    mBallPos.y += mBallVel.y * deltaTime;
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

void Game::AddActor(Actor *actor)
{
    if (mUpdatingActors)
    {
        mPendingActors.emplace_back(actor);
    }
    else
    {
        mActors.emplace_back(actor);
    }
}

void Game::RemoveActor(Actor *actor)
{
    auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actor);
    if (iter != mPendingActors.end())
    {
        // 交换到尾部,避免复制
        std::iter_swap(iter, mPendingActors.end() - 1);
        mPendingActors.pop_back();
    }
    
    iter = std::find(mActors.begin(), mActors.end(), actor);
    if (iter != mActors.end())
    {
        std::iter_swap(iter, mActors.end() - 1);
        mActors.pop_back();
    }
}
