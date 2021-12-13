import numpy as np
import matplotlib.pyplot as plt
import time
from Env_SPF_Slice_Routing import SpfSliceRoutingEnv
from Model_local_spf import MAPLocal

mp = MAPLocal()


'---------------- 初始化 ----------------'

# 数据量
T_len = 10          # 也代表了步长
T_size_start = 40
T_size_end = 160
# T_size_step = 10

# 迭代次数
Iterations = 800

# 任务状态图   [[独热编码], [起点, 终点], 状态]
# 状态 --> -1: 未加入  0: 正常  1: 已完成  2: 被抛弃
Task_Space = {x: [np.zeros(mp.R_len), np.zeros(2), -1] for x in range(T_len)}

# 路由节点状态图
Router_Space = np.zeros(mp.R_len)

# 路径表，每个任务的路径表不同
Path_Task = {x: [] for x in range(T_len)}

Observe_Space = {o: [] for o in range(3)}

'---------------- 开始 ----------------'

for t_size in range(T_size_start, T_size_end, T_len):
    Observe_Space[0].append(t_size)
    print(t_size, end=' ')
    # 产生数据
    # Task_List = np.random.poisson(t_size, T_len)
    Task_List = np.arange(t_size, t_size + T_len, 1)
    env_route = SpfSliceRoutingEnv(mp, Task_List)

    '为每个任务计算最优路径'
    env_route.get_paths_for_each_task(Path_Task)
    # print(Path_Task)
    '分片仿真'
    env_route.reset_space(Task_Space, Router_Space)
    times, stk_prob, _ = env_route.start_slice_routing_in_spf(Task_Space, Router_Space, Path_Task)

    # 记录
    Observe_Space[1].append(times)
    Observe_Space[2].append(stk_prob)


# Mark = [['Stuck Probability', 'stuck_prob'], ['Total Time', 'use_time']]
Name = {
    'style': ['', 'bo-', 'bx-'],
    'label': ['', 'time', 'stuck-prob'],
    'title': ['', 'Size -> time', 'Size -> stuck'],
    'ylabel': ['', 'time_len', 'probability']
}

x = Observe_Space[0]
for p in range(1, 3, 1):
    plt.subplot(1, 2, p)
    plt.plot(x, Observe_Space[p], Name['style'][p], label=Name['label'][p])
    plt.title(Name['title'][p])
    plt.xlabel('data_size')
    plt.ylabel(Name['ylabel'][p])
    plt.legend()

plt.show()
