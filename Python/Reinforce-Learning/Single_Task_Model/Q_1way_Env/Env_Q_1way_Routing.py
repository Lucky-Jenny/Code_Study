import numpy as np


'参数设置'
# Q表产生方式
METHOD = 1      # SARSA
# METHOD = 2    # Q-learning


# 网络情况
state_stuck = 0         # -20
state_normal = 1        # 1
state_reverse = 2       # -10
state_invalid = 3       # -100
state_done = 4          # 10

# 奖励
Reward = [-30, 1, -10, -100, 10]


class Q1DirectRoutingEnv:
    """
    note
    """

    def __init__(self, route_pfm, action_space, task_list):
        """
        note
        """
        '状态空间'
        self.Router_Perform = route_pfm
        self.Action = action_space
        self.Task_List = task_list

        # 路由节点
        self.R_len = len(route_pfm)
        self.R_start = 0
        self.R_target = self.R_len - 1
        # 任务
        self.T_len = len(task_list)
        self.T_idx = 0
        # 时隙限制
        self.time_limit = 100

        '参数设置'
        # 公式参数
        self.epsilon = 0.1
        self.alpha = 0.1
        self.gamma = 0.9

        '动态-状态空间'
        # Task_Space = {}     # 任务状态空间
        # Router_Space = []  # 路由器状态空间
        # Q = []  # Q表

    def start_routing_in_r_learning(self, mode, task_space, router_space, q_table, t_path):
        """
        强化学习中进行路由策略仿真，按照mode决定不同动作。
        :param mode: 1--> update Q table
                     2--> simulate (t_path is must)
        :param task_space:
        :param router_space:
        :param q_table: Q表
        :param t_path: 任务路径（if mode=2，必须有传参）
        :return:
        """
        t = 0
        stk_sum = 0
        for t in range(self.time_limit):  # 时隙
            task_mark = 0
            has_stuck = 0
            ret_st = self.add_new_task(task_space, router_space)
            if ret_st == state_stuck:
                has_stuck = 1
            # 循环遍历Task_State
            for s in range(self.T_len):
                task_state = task_space[s][1]
                # 判断任务是否正常
                if task_state != 0:
                    # 统计已完成任务量
                    if task_state == 1 or task_state == 2:
                        task_mark += 1
                    continue

                task_vector = task_space[s][0]
                ps = np.argmax(task_vector)
                if mode == 1:
                    # 探索策略
                    action = self.explore_exploit(q_table[s][ps])
                    # 执行动作并返回奖励
                    ps_new, state_new = self.action_route(task_space[s], action, router_space)
                    # 根据奖励，执行Bellman更新
                    q_table[s] = self.update_q_table(ps, action, ps_new, state_new, q_table[s])
                else:
                    # 仿真
                    # action = self.explore_in_stable(ps, q_table[s][ps])
                    action = np.argmax(q_table[s][ps])
                    ps_new, state_new = self.action_route(task_space[s], action, router_space)
                    '记录路径'
                    t_path[s][0] = np.max(task_vector)
                    t_path[s][1].append(ps)
                    if state_new == state_stuck or \
                       state_new == state_reverse or \
                       state_new == state_invalid:
                        has_stuck = 1
            if has_stuck:
                stk_sum += 1

            if task_mark == self.T_len:
                break
        return t, stk_sum

    def reset_space(self, task_space, router_space):
        """
        重置task_space & router_space，返回TL（必须返回，值传递不会影响传参）
        :param task_space:
        :param router_space:
        :return: TL
        """
        self.time_limit = self.T_len * 10
        self.T_idx = 0

        # [[0...], -1]
        for i in range(self.T_len):
            task_space[i][0] = np.zeros(self.R_len)
            task_space[i][1] = -1
        # router perform
        for i in range(self.R_len):
            router_space[i] = self.Router_Perform[i][1]

    def add_new_task(self, task_space, router_space):
        """
        根据索引，将任务添加到状态图中
        :param task_space: 任务状态
        :param router_space:
        :return:
        """
        idx = self.T_idx
        # 判断长度
        if idx >= self.T_len:
            return state_normal

        # 判断卡住情况
        if self.Task_List[idx] > router_space[0]:
            return state_stuck

        # Update Task Space
        task_space[idx][0][0] = self.Task_List[idx]
        task_space[idx][1] = 0
        # Update Router Space
        router_space[0] -= self.Task_List[idx]

        # 索引自增
        self.T_idx += 1
        return state_normal

    def update_q_table(self, ps_0, act, ps_1, st_1, q_task):
        """
        更新Q值
        :param ps_0: original position
        :param act: select which router
        :param ps_1: new position after action
        :param st_1: State of next router after action
        :param q_task: Q table of this task.
        :return: Q table updated
        """
        reward = Reward[st_1]
        # 起点 / 终点 / 堵塞
        if ps_0 == self.R_start or \
                ps_0 == self.R_target or \
                st_1 == state_stuck:
            q_1 = 0.0
        else:
            action_1 = self.explore_exploit(q_task[ps_1])
            if METHOD == 1:
                'SARSA'
                q_1 = q_task[ps_1][action_1]
            else:
                'Q-learning'
                q_1 = np.max(q_task[ps_1])
        # 贝尔曼方程更新
        return self.bellman(ps_0, act, reward, q_1, q_task)

    def bellman(self, ps_cur, a, reward, q_next, q_task):
        """
        贝尔曼方程更新Q值
        :param ps_cur: 原先所在的节点
        :param a: 选择动作
        :param reward: 获得奖励
        :param q_next: Q(st_1, act_1)
        :param q_task: Q table of task
        :return:
        """
        # done --> Q no change
        if ps_cur == self.R_target:
            return q_task

        # Update Bellman
        q_task[ps_cur][a] = q_task[ps_cur][a] + self.alpha * (reward + self.gamma * q_next - q_task[ps_cur][a])
        # print('q_task[', ps_cur, '][', action, ']:', q_task[ps_cur][action])
        return q_task

    def action_route(self, t_state, act, router_space):
        """
        执行动作（需要判断是否有效），并更新状态空间
        :param t_state: 单个任务的状态空间
        :param act: 动作->下一个节点
        :param router_space:
        :return: new_position, reward
        """
        t_vector = t_state[0]
        current = np.argmax(t_vector)
        data = np.max(t_vector)

        # Current in Target Node
        if current == self.R_target:
            # Remove data
            router_space[current] += data
            t_state[0] = np.zeros(self.R_len)
            t_state[1] = 1
            return current, state_done

        # Invalid action
        if self.Action[current][act] == 0 and current != act:
            return current, state_invalid

        # Will be stuck
        if data > router_space[act]:
            # 先留在原地
            return current, state_stuck

        # Update Router State
        router_space[act] -= data
        router_space[current] += data
        # Update Task State
        t_vector[current] = 0
        t_vector[act] = data

        # reverse?
        if current > act:
            return act, state_reverse

        return act, state_normal

    def explore_exploit(self, q_array):
        """
        根据epsilon-greedy算法探索策略
        (原本根据任务当前节点，对动作进行收敛，后发现没有必要)
        :param q_array: 具体的Q数组，不用再定位了
        :return: action
        """
        # call a random number -> (0,1)
        r = np.random.uniform()

        if r < self.epsilon:
            a = self.random_action()
        else:
            a = np.argmax(q_array)
        return a

    def explore_in_stable(self, idx, q_array):
        act = np.argmax(q_array)
        # 如果无法从Q表中获取有效值，采用随机动作(必须有效)
        if self.Action[idx][act] == 0:
            act = self.random_action()
        return act

    def random_action(self):
        """
        随机选择动作
        :return action
        """
        a_next = np.random.randint(self.R_len)
        return a_next
