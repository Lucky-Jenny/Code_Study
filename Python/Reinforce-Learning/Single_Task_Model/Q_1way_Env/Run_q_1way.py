import numpy as np

# 迭代次数
Iterations = 800


def run_q_1way_model(env_route, router_pfm, router_spc, act_spc, task_spc, task_list, q_tb):
    """

    :param env_route:
    :param router_pfm:  Router_Performance
    :param router_spc:  Router_Space
    :param act_spc:     Action_Space
    :param task_spc:    Task_Space
    :param task_list:   Task_List
    :param q_tb:        Q table
    :return:
    """
    # 参数
    r_len = len(router_pfm)
    t_len = len(task_list)

    # env_route = Q1DirectRoutingEnv(router_pfm, act_spc, task_list)
    '迭代更新Q表'
    for n in range(Iterations):
        env_route.reset_space(task_spc, router_spc)
        env_route.start_routing_in_r_learning(1, task_spc, router_spc, q_tb, None)
    # 小数点保留n位
    q_tb = np.around(q_tb, decimals=3)

    '根据Q表进行仿真'
    path_record = {c: [0, []] for c in range(t_len)}
    env_route.reset_space(task_spc, router_spc)
    times, stk_sm = env_route.start_routing_in_r_learning(2, task_spc, router_spc, q_tb, path_record)

    stk_prob = stk_sm / times
    return times, stk_prob
