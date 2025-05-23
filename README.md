# Survival

使用`EasyX`开发的幸存者类小游戏

B站教程：[https://www.bilibili.com/video/BV1eM4m1S74K](https://www.bilibili.com/video/BV1eM4m1S74K)

# `main`

负责：

1. 加载基础资源
2. 循环处理用户输入
3. 生成游戏物体（玩家、敌人）
4. 循环渲染图片

通过以下代码实现帧率控制：

```cpp
DWORD end_time = GetTickCount();
DWORD delta_time = end_time - start_time;
if (delta_time < 1000 / FPS) // 设定刷新率为FPS
{
	Sleep(1000 / FPS - delta_time);
}
```

# `utils`

基础通用功能

`putimage_alpha`：渲染图片，且保证图片透明部分正常显示

`DrawBBox`：绘制包围盒

`DrawTipText`：显示提示信息

# `Atlas`

保存`sprite`素材

`atlas` 有两个重载的构造函数，可以从图片构造，也可以从已构造好的`atlas`构造，目的是生成对称素材和纯白图片

# `Animation`

动画基类，播放动画的基础逻辑

# `Player`

玩家类，处理用户输入并移动，还负责绘制玩家图片

玩家类中的`atlas_left_white`和`atlas_right_white`用于在受到伤害时渲染出闪烁的效果，逻辑是通过交替显示普通图片和纯白图片达到闪烁效果，具体实现在`Player::Draw`中

# `Enemy`

敌人类，处理敌人移动和绘制逻辑，判断是否与玩家或子弹发生碰撞

# `Bullet`

子弹类，负责子弹定义和绘制

# `Button`

按钮基类，包含三种状态，处理点击时状态切换和做出响应，其中响应方法为`OnClick`，为纯虚方法，需要具体按钮具体实现

# `StartButton`和`QuitButton`

开始游戏和结束游戏按钮，继承自`Button`

# `Enums`

枚举类，将所有全局的枚举类型都放在这里，虽然只有一个