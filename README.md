# StartMenuButtonHider

"开始"菜单按钮隐藏工具（可以隐藏电源按钮，用户图标等等）

可以作为一个整蛊小程序？（bushi

其实还有其他价值，比如，这个程序展示了很多"用 Win32Api 修改注册表的细节（坑）"，还有 "MessageBox 的一些用例"。

### 实现原理

通过 Win32 API 对特定注册表的值 `HKEY_LOCAL_MACHINE\SOFTWARE\Microsoft\PolicyManager\default\Start\XXXXXX` 进行修改。
当然，使用组策略也可以实现。

不过，考虑到使用家庭版等非专业版系统的用户，程序还是采用注册表修改方式。

因此，运行本程序需要管理员权限，另外若有安全软件拦截，请放行。

### 软件展示

在 Bilibili 上录了个视频的，感觉会详细些。

[你的电脑暂时不想关机——当前没有可用的电源选项 (开始菜单按钮隐藏教程)【原创/整蛊】](https://www.bilibili.com/video/BV1ih41167Sd)

### 使用方式

双击打开程序，输入对应选项前的序号并按下"Enter"即可。

支持一次输入多个纯数字序号，使用空格隔开。

*如果有其他按钮隐藏需要，可以自行修改源码，替换源码中注册表路径的子键*

### 注意事项

本程序已在 Windows 7 / Windows 10 上测试通过。理论上支持 Windows Vista 和 Windows 8，Windows XP 未知。

Win7 及以下版本请使用 `StartMenuButtonHider_Win7.exe`，其余版本使用 `StartMenuButtonHider.exe` 即可。

