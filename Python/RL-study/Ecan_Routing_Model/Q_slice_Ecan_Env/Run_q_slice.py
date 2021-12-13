import logging

import numpy as np

# 迭代次数
Iterations = 800


def run_q_slice_model(env_route, router_spc, task_spc, q_tb):
    """

    :param env_route:
    :param router_spc:  Router_Space
    :param task_spc:    Task_Space
    :param q_tb:        Q table
    :return:
    """
    '迭代更新Q表'
    for n in range(Iterations):
        env_route.reset_space(task_spc, router_spc)
        env_route.generate_q_table_while_routing(task_spc, router_spc, q_tb)
    # 小数点保留n位
    q_tb = np.around(q_tb, decimals=3)
    logging.info('q-learning done.')
    '根据Q表进行仿真'
    env_route.reset_space(task_spc, router_spc)
    return env_route.start_slice_routing(task_spc, router_spc, q_tb)

