### 开发环境

> Win 10
>
> VS2017



*直接点击Tetris.sln可把项目加载到VS里面*



**Brick类**

定义整个界面的砖块划分50*50

定义与砖块映射关系的二维数组

定义颜色常量及函数

定义根据二维数组绘图函数  其中主界面也包含在里面



**Tetris类**

定义方向常量

定义方块形状	!重要

定义方块变形函数 	!重要

定义方块移动是否合法函数	!重要



**Game头文件**

封装界面的刷新与转换函数

封装方块消除判断函数

封装操作历史分数函数



> Ver 1.0.0.0
>
> 修改了方块移动枚举的小bug