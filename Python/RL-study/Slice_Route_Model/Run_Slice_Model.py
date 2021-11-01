import time

import numpy as np
import matplotlib.pyplot as plt
# 导入模型
from MAP_Routers import Router_Perform, Action_Space, Action_Space_1d
# 导入算法
from Q_slice_Env import Run_q_slice, Env_Q_Slice_Routing
from Q_1path_slice_Env import Run_1path_slice, Env_1path_Slice_Routing
from SPF_slice_Env import Env_SPF_Slice_Routing

Alg_num = 3

R_len = len(Router_Perform)
R_start = 0
R_target = R_len - 1

'---------------- 初始化 ----------------'
# 数据量
T_len = 10          # 也代表了步长
T_size_start = 40
T_size_end = 250
# T_size_step = 10

# 重复次数，防止抖动
Repeat = 1

# 任务状态图   [[独热编码]，状态]
# 状态 --> -1: 未加入  0: 正常  1: 已完成  2: 被抛弃
Task_Space = {x: [np.zeros(R_len), -1] for x in range(T_len)}

# Q表 (不用加无效动作的Q值)
Q = np.zeros((T_len, R_len, R_len))

# 路由节点状态图
Router_Space = np.zeros(R_len)

Observe_Space = {'data': [],
                 'Q-lr': [[], []],
                 'Q-wt': [[], []],
                 'spf': [[], []]}
# print(Observe_Space)


def q_slice_model():
    global Q
    env_qlr = Env_Q_Slice_Routing.QSliceRoutingEnv(Router_Perform, Action_Space, Task_List)
    tm_qlr, prob_qlr = 0, 0
    for k in range(Repeat):
        Q = np.zeros_like(Q)
        tm, prob = Run_q_slice.run_q_slice_model(env_qlr, Router_Space, Task_Space, Q)
        tm_qlr += tm
        prob_qlr += prob
    # 记录
    Observe_Space['Q-lr'][0].append(tm_qlr/Repeat)
    Observe_Space['Q-lr'][1].append(prob_qlr/Repeat)


def water_slice_model():
    global Q
    env_wt = Env_1path_Slice_Routing.Q1PathRoutingEnv(Router_Perform, Action_Space_1d, Task_List)
    tm_q1d, prob_q1d = 0, 0
    for k in range(Repeat):
        Q = np.zeros_like(Q)
        tm, prob = Run_1path_slice.run_wt_slice_model(env_wt, Router_Space, Task_Space, Q)
        tm_q1d += tm
        prob_q1d += prob
    # 记录
    Observe_Space['Q-wt'][0].append(tm_q1d / Repeat)
    Observe_Space['Q-wt'][1].append(prob_q1d / Repeat)


def dijkstra_slice_model():
    env_spf = Env_SPF_Slice_Routing.SpfSliceRoutingEnv(Router_Perform, Action_Space, Task_List)
    tm_spf, prob_spf = 0, 0
    r_start, r_target = R_start, R_target
    s_path = env_spf.get_1_path_from_dijkstra(r_start, r_target)
    for k in range(Repeat):
        env_spf.reset_space(Task_Space, Router_Space)
        tm, stk_prob = env_spf.start_slice_routing_in_spf(Task_Space, Router_Space)
        tm_spf += tm
        prob_spf += stk_prob
    # 记录
    Observe_Space['spf'][0].append(tm_spf / Repeat)
    Observe_Space['spf'][1].append(prob_spf / Repeat)

'''
def weaken_deviation(expect, actual):
    theta = 0.1
    dev = theta * (actual - expect)
    return expect + dev


def deal_with_time(exp_qlr, exp_q1d):
    len_obs = len(Observe_Space['data'])
    pfm = np. array(Router_Perform)
    # 取所有内存中的最小值
    pfm_min = np.min(pfm[:, 1])
    for n in range(len_obs):
        if Observe_Space['data'][n] > pfm_min:
            break
        m_qlr = Observe_Space['Q-lr'][0][n]
        m_q1d = Observe_Space['Q-wt'][0][n]
        Observe_Space['Q-lr'][0][n] = weaken_deviation(exp_qlr, m_qlr)
        Observe_Space['Q-wt'][0][n] = weaken_deviation(exp_q1d, m_q1d)



def run_in_multi_process(method):
    if method == 0:
        q_slice_model()
    elif method == 1:
        water_slice_model()
    else:
        dijkstra_slice_model()
'''


def draw_observation():
    mark = [['Contrast of Time', 'use_time'], ['Contrast of Stuck Probability', 'stuck_prob']]

    x = Observe_Space['data']
    x = np.array(x)
    for p in range(2):
        idx = p + 1
        plt.subplot(1, 2, idx)
        y_lr = np.array(Observe_Space['Q-lr'][p])
        y_1d = np.array(Observe_Space['Q-wt'][p])
        y_spf = np.array(Observe_Space['spf'][p])

        plt.plot(x, y_lr, 'bx-', label='Q-learning')
        plt.plot(x, y_1d, 'g+-', label='Q-water')
        plt.plot(x, y_spf, 'ro-', label='Dijkstra')

        plt.title(mark[p][0])
        plt.xlabel('data_size')
        plt.ylabel(mark[p][1])
        plt.legend()

    plt.show()


'---------------- 开始 ----------------'

if __name__ == '__main__':
    # 记录处理时间
    start_tm = time.clock()
    for t_size in range(T_size_start, T_size_end, T_len):
        Observe_Space['data'].append(t_size)
        # 产生数据
        # Task_List = np.random.poisson(t_size, T_len)      # 泊松分布
        Task_List = np.arange(t_size, t_size + T_len, 1)
        T_len = len(Task_List)
        print('T_range: [', t_size, ',', t_size+T_len, ']')
        'Q-learning'
        q_slice_model()

        'Water'
        water_slice_model()

        'Dijkstra'
        dijkstra_slice_model()

    print('观测空间', Observe_Space)
    end_tm = time.clock()
    print('处理时间: ', end_tm-start_tm)

    draw_observation()
