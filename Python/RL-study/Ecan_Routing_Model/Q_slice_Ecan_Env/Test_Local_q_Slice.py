import numpy as np
import matplotlib.pyplot as plt
import time
from Env_Q_Slice_Routing import QSliceRoutingEnv

from Model_local_q_slice import MAPLocal

mp = MAPLocal()


'---------------- 初始化 ----------------'

# 数据量
T_len = 10          # 也代表了步长
T_size_start = 40
T_size_end = 150

# 迭代次数
Iterations = 800

# 任务状态图   [[独热编码]，状态]
# 状态 --> -1: 未加入  0: 正常  1: 已完成  2: 被抛弃
Task_Space = {x: [np.zeros(mp.R_len), np.zeros(2), -1] for x in range(T_len)}

# Q表 (不用加无效动作的Q值)
Q = np.zeros((T_len, mp.R_len, mp.R_len))

# 路由节点状态图
Router_Space = np.zeros(mp.R_len)

# 路径表
Path_Task = {c: [] for c in range(T_len)}

Observe_Space = {o: [] for o in range(3)}


# 测试Q表的学习结果
def assess_q_table(q_tb, task_space):
    for tk in range(T_len):
        path_tmp = []
        t_start = task_space[tk][1][0]
        t_target = task_space[tk][1][1]
        idx = t_start
        for i in range(mp.R_len * 3):
            path_tmp.append(idx)
            if idx == t_target:
                break
            idx = np.argmax(q_tb[tk][idx])

        # 打印结果
        print(tk, '-> vct:[', t_start, ',', t_target, ']  Path:', path_tmp)


'---------------- 开始 ----------------'

# 产生文件名+时间戳
tm = time.strftime('%H-%M-%S', time.localtime())
filename = 'Q_test_' + tm + '.txt'
pathname = './log/' + filename
file_obj = open(pathname, 'a')

for t_size in range(T_size_start, T_size_end, T_len):
    Observe_Space[0].append(t_size)
    print(t_size)
    # 产生数据
    # Task_List = np.random.poisson(t_size, T_len)
    Task_List = np.arange(t_size, t_size + T_len, 1)
    env_route = QSliceRoutingEnv(mp, Task_List)
    '迭代更新Q表'
    for n in range(Iterations):     # 迭代次数
        env_route.reset_space(Task_Space, Router_Space)
        env_route.generate_q_table_while_routing(Task_Space, Router_Space, Q)
    # 小数点保留n位
    Q = np.around(Q, decimals=6)
    # print('q table finish')
    # 把Q表写入文件中
    str_size = '[ d_size: %d ]\n' % t_size
    file_obj.write(str_size)
    for n in range(T_len):
        str_arr = 'task(%d)-->' % n + '[%d,' % Task_Space[n][1][0] + '%d]\n' % Task_Space[n][1][1] \
                  + '\n'.join('\t'.join('%0.3f' % x for x in Q[n][y]) for y in range(mp.R_len)) + '\n\n'
        file_obj.write(str_arr)
    file_obj.write('\n---------------\n')

    '评估Q表'
    assess_q_table(Q, Task_Space)

    '分片仿真'
    # Path_Task = {c: [0, []] for c in range(T_len)}
    env_route.reset_space(Task_Space, Router_Space)
    times, stk_prob, _ = env_route.start_slice_routing(Task_Space, Router_Space, Q)

    # 记录
    Observe_Space[1].append(times)
    Observe_Space[2].append(stk_prob)

file_obj.close()


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
