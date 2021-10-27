import numpy as np
import matplotlib.pyplot as plt
from Env_Dijkstra_Routing import DijkstraEnv
from Model_un_dir import Router_Perform, Action_Space


R_len = len(Router_Perform)
R_start = 0
R_target = R_len - 1


'任务列表'
T_size = 80
T_len = 10
# 迭代次数
Iterations = 2000

# 任务状态图   [[独热编码]，状态]
# 状态 --> -1: 未加入  0: 正常  1: 已完成  2: 被抛弃
Task_Space = {x: [np.zeros(R_len), -1] for x in range(T_len)}

# 路由节点状态图
Router_Space = np.zeros(R_len)

# 路径表
# Path_Task = {c: [] for c in range(T_len)}

Observe_Space = {o: [] for o in range(3)}


'---------------- 开始 ----------------'


for step in range(10):
    T_size = 80 + 5 * step
    Observe_Space[0].append(T_size)
    print(T_size, end=' ')
    # 泊松分布
    Task_List = np.random.poisson(T_size, T_len)
    env_ds = DijkstraEnv(Router_Perform, Action_Space, Task_List)
    s_path = env_ds.get_1_path_from_dijkstra(R_start, R_target)
    print(s_path)
    # 进行路由
    Path_Task = {c: [0, []] for c in range(T_len)}
    env_ds.reset_space(Task_Space, Router_Space)
    times, stk_sm = env_ds.start_routing_in_spf(Task_Space, Router_Space, Path_Task)
    stk_prob = stk_sm / times
    # 记录
    Observe_Space[1].append(times)
    Observe_Space[2].append(stk_prob)
    print(Path_Task)
    print('Router:', Router_Space)


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
