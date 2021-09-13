在机器人研究领域，给定某一特定任务之后，如何规划机器人的运动方式至关重要。



最近，GitHub 上开源了一个存储库，该库实现了机器人技术中常用的一些路径规划算法，大部分代码是用 Python 实现的。值得一提的是，开发者用 plotting 为每种算法演示了动画运行过程，直观清晰。



项目地址：
https://github.com/zhm-real/PathPlanning

该开源库中实现的路径规划算法包括基于搜索和基于采样的规划算法，具体目录如下图所示：

   基于搜索的路径规划算法

基于搜索的路径规划算法已经较为成熟且得到了广泛应用，常常被用于游戏中人物和移动机器人的路径规划。

最佳路径优先搜索算法

Dijkstra 算法

A * 搜索算法

双向 A * 搜索算法

重复 A * 搜索算法

Anytime Repairing A* (ARA*) 搜索算法

实时学习 A * 搜索（LRTA*）算法

实时适应性 A * 搜索（RTAA*）算法

动态 A * 搜索（D*）算法

终身规划 A * 搜索算法

Anytime D * 搜索算法：变动较小

Anytime D * 搜索算法：变动较大

基于采样的路径规划算法

与基于搜索不同，基于采样的路径规划算法不需要显式构建整个配置空间和边界，并且在高维度的规划问题中得到广泛应用。

快速随机搜索树（RRT）算法

目标偏好 RRT 算法

双向快速扩展随机树（RRT_CONNECT）算法

Extended_RRT 算法

动态 RRT 算法

N = 10000 时，rrt * 算法

N = 1000 时，rrt*-Smart 算法

快速行进树（FMT*）算法

N =1000 时，Informed rrt * 算法

Batch Informed 树（BIT*）算法

参考链接：
https://blog.csdn.net/RoboChengzi/article/details/104096663
http://www.chenjianqu.com/show-137.html
