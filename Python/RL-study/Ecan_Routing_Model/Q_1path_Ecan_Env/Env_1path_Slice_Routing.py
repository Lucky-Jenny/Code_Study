import time
import numpy as np
import queue
import logging


'参数设置'
# Q表产生方式
# METHOD = 1      # SARSA
METHOD = 2    # Q-learning


# 网络情况
state_stuck = 0         # -20
state_normal = 1        # 1
state_reverse = 2       # -10
state_invalid = 3       # -100
state_target = 4        # 20
state_done = 5          # 10

# 奖励
Reward = [-30, 1, -10, -100, 20, 10]


class Q1PathRoutingEnv:
    """
    note
    """

    def __init__(self, model, task_list):
        """
        note
        """
        '状态空间'
        self.Router_Perform = model.Router_Perform
        # 路由节点
        self.R_len = len(self.Router_Perform)
        self.A_start = model.A_start
        self.A_target = model.A_target
        self.R_list = np.arange(self.R_len)
        # 路由节点的每个任务队列
        self.Router_Task_Index_Queue = {c: [] for c in range(self.R_len)}
        self.Router_Task_Data_Queue = {c: [] for c in range(self.R_len)}
        # 动作空间
        self.Action = model.Action_Space_1d
        # 任务列表
        self.Task_List = task_list
        self.T_len = len(task_list)
        self.T_idx = 0
        # 任务路径表
        self.Task_Path = {h: [] for h in range(self.T_len)}

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

    def start_slice_routing(self, task_space, router_space, q_table):
        """
        分片路由
        :param task_space:
        :param router_space:
        :param q_table:
        :return: times， stuck_prob
        """
        t = 0
        stk_sum, task_mark, joule = 0, 0, 0
        for t in range(self.time_limit):  # 时隙
            has_stuck = 0
            ret_st = self.add_new_task(task_space, router_space)
            ''''''
            if ret_st == state_stuck:
                has_stuck = 1

            logging.info('[', t, ']', 'R_space:', router_space)

            # 逆序遍历，防止自传递
            for r in reversed(self.R_list):
                # 队列为空
                if not self.Router_Task_Index_Queue[r]:
                    continue
                # 每个节点在t时间能够处理的数据量，处理缓存: Forward Buff
                fwd_buff = self.Router_Perform[r][0]

                logging.info('    Q[', r, ']:', self.Router_Task_Index_Queue[r], self.Router_Task_Data_Queue[r], end=' ')

                '''
                按照每个节点的任务队列，按buff大小依次对队列中的数据分片进行路由
                1. 只看队列的第一项，直到buff=0
                2. 注意更新队列和其他状态空间
                '''
                while fwd_buff > 0:
                    if not self.Router_Task_Index_Queue[r]:
                        break

                    # 只关注队列首部的任务
                    s = self.Router_Task_Index_Queue[r][0]

                    logging.info(' ts[', s, ']:', task_space[s], end=' ')

                    # 从路径表中选取动作，执行路由
                    action = self.select_action(s, r, task_space[s])
                    ps_new, state_new, fwd_buff = self.slice_action(s, r, action, fwd_buff, task_space[s], router_space)

                    if state_new == state_stuck:
                        has_stuck = 1
                    # 检查该任务是否全部传输完成：列表全为0 && 状态值=0
                    'any() --> False: list所有元素全为 0 / 空 / false'
                    if any(task_space[s][0]) is False and task_space[s][2] == 0:
                        task_space[s][2] = 1
                        task_mark += 1
                        logging.info('task[', s, '] is finished !!! total_finish=', task_mark, '\n------------')

                    # 处理量到达/堵塞，直接结束
                    if fwd_buff == 0 or has_stuck:
                        break
                # 统计能耗
                joule += self.Router_Perform[r][0]

            if has_stuck:
                stk_sum += 1

            if task_mark == self.T_len:
                break

        return t, stk_sum / t, joule

    def select_action(self, t_idx, r_idx, t_state):
        if r_idx == t_state[1][1]:
            return r_idx
        # 找到当前索引，+1
        id_path = self.Task_Path[t_idx].index(r_idx) + 1
        # print('t_idx:', t_idx, ', r_idx:', r_idx, ', ', t_state[1], self.Task_Path[t_idx], 'get idx=', id_path)
        return self.Task_Path[t_idx][id_path]

    def slice_action(self, t_idx, r_idx, act, fwd_buff, t_state, router_spc):
        """
        分片路由，更新状态。
        :param t_idx:
        :param r_idx:
        :param act:
        :param fwd_buff:
        :param t_state:
        :param router_spc:
        :return: 更新后的节点位置，网络状态，buff容量
        """
        t_vector = t_state[0]
        # 确定数据块大小
        d_size = self.Router_Task_Data_Queue[r_idx][0]
        if d_size > fwd_buff:
            buff_not_enough = 1
            t_size = fwd_buff
        else:
            buff_not_enough = 0
            t_size = d_size

        # Current in Target Node
        if r_idx == t_state[1][1]:
            # Remove data
            router_spc[r_idx] += t_size
            t_vector[r_idx] -= t_size
            # 更新队列+buff
            fwd_buff = self.update_queue_and_buff(fwd_buff, r_idx, None, None, t_size, buff_not_enough)
            return r_idx, state_done, fwd_buff

        # Invalid action
        if self.Action[r_idx][act] == 0 and r_idx != act:
            return r_idx, state_invalid, fwd_buff

        # Will be stuck
        if t_size > router_spc[act]:
            # 先留在原地
            return r_idx, state_stuck, fwd_buff

        # 更新节点状态
        router_spc[r_idx] += t_size
        router_spc[act] -= t_size
        # 更新任务向量
        t_vector[r_idx] -= t_size
        t_vector[act] += t_size
        # 更新队列+buff
        logging.info('slice(', t_idx, '): [', r_idx, '] --> [', act, ']')
        fwd_buff = self.update_queue_and_buff(fwd_buff, r_idx, act, t_idx, t_size, buff_not_enough)

        # reverse?
        if r_idx > act:
            return act, state_reverse, fwd_buff

        if act == t_state[1][1]:
            return act, state_target, fwd_buff
        else:
            return act, state_normal, fwd_buff

    def update_queue_and_buff(self, buff, r_idx, nxt_idx, t_idx, t_size, is_not_enough):
        """
        根据标志位更新buff值，当buff有余地时，说明该任务块已经完成传输，更新队列。
        更新所用到的参数较多....
        :param buff: forward buff
        :param r_idx: current index
        :param nxt_idx: next index
        :param t_idx: task index
        :param t_size: task data size
        :param is_not_enough: 标志位-> buff is not enough
                                      1: not enough
                                      0: enough
        :return: buff
        """
        if is_not_enough:
            buff = 0
            self.Router_Task_Data_Queue[r_idx][0] -= t_size
        else:
            # 任务已在当前节点完成，pop出去
            self.Router_Task_Index_Queue[r_idx].pop(0)
            self.Router_Task_Data_Queue[r_idx].pop(0)
            buff -= t_size
        # 无论buff如何，该任务肯定要append到下一个节点的队列中
        if nxt_idx:
            # 如果该队列末尾与当前一致，则不append了
            if not self.Router_Task_Index_Queue[nxt_idx] or \
               self.Router_Task_Index_Queue[nxt_idx][-1] != t_idx:
                self.Router_Task_Index_Queue[nxt_idx].append(t_idx)
                self.Router_Task_Data_Queue[nxt_idx].append(t_size)
            else:
                self.Router_Task_Data_Queue[nxt_idx][-1] += t_size
        return buff

    def generate_path_from_q_table(self, q_table, task_space):
        for tk in range(self.T_len):
            idx = task_space[tk][1][0]
            while True:
                self.Task_Path[tk].append(idx)
                if idx == task_space[tk][1][1]:
                    break
                idx = self.next_node(idx, q_table[tk], task_space[tk])

    def next_node(self, r_id, q_array, t_state):
        """

        :param r_id: Index of router
        :param q_array:
        :return:
        """
        act = np.argmax(q_array[r_id])
        # 如果无法从Q表中获取有效值，采用随机动作(必须有效)
        while True:
            if self.Action[r_id][act] == 1:
                break
            act = self.random_action()

        return act

    def generate_q_table_while_routing(self, task_space, router_space, q_table):
        """
        在路由中进行Q表的更新，只针对单项任务而不进行分片。
        :param task_space:
        :param router_space:
        :param q_table: Q表
        :return:
        """
        for t in range(self.time_limit):  # 时隙
            task_mark = 0
            self.add_new_task(task_space, router_space)
            # 循环遍历Task_State
            for s in range(self.T_len):
                task_state = task_space[s][2]
                # 判断任务是否正常
                if task_state != 0:
                    # 统计已完成任务量
                    if task_state == 1 or task_state == 2:
                        task_mark += 1
                    continue

                task_vector = task_space[s][0]
                ps = np.argmax(task_vector)
                # 探索策略
                action = self.explore_exploit(q_table[s][ps])
                # 执行动作并返回奖励
                ps_new, state_new = self.action_route(task_space[s], action, router_space)
                # 根据奖励，执行Bellman更新
                q_table[s] = self.update_q_table(ps, action, ps_new, state_new, q_table[s], task_space[s])

            if task_mark == self.T_len:
                break

    def reset_space(self, task_space, router_space):
        """
        重置task_space & router_space，返回TL（必须返回，值传递不会影响传参）
        :param task_space:
        :param router_space:
        :return: TL
        """
        self.time_limit = self.T_len * 50
        self.T_idx = 0

        # [[0...], -1]
        for i in range(self.T_len):
            task_space[i][0] = np.zeros(self.R_len)
            task_space[i][2] = -1
        # router perform
        for i in range(self.R_len):
            router_space[i] = self.Router_Perform[i][1]

        # 节点队列
        self.Router_Task_Index_Queue = {c: [] for c in range(self.R_len)}
        self.Router_Task_Data_Queue = {c: [] for c in range(self.R_len)}

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

        # 计算起点/目标节点的位置
        idx_s = self.Task_List[idx] % len(self.A_start)
        idx_t = self.Task_List[idx] % len(self.A_target)
        r_start = self.A_start[idx_s]
        r_target = self.A_target[idx_t]

        # 判断卡住情况
        if self.Task_List[idx] > router_space[r_start]:
            return state_stuck

        # Update Task Space
        task_space[idx][0][r_start] = self.Task_List[idx]
        task_space[idx][1] = [r_start, r_target]
        task_space[idx][2] = 0
        # Update Router Space
        router_space[r_start] -= self.Task_List[idx]

        # 添加到节点队列
        self.Router_Task_Index_Queue[r_start].append(idx)
        self.Router_Task_Data_Queue[r_start].append(self.Task_List[idx])

        # 索引自增
        self.T_idx += 1
        return state_normal

    def update_q_table(self, ps_0, act, ps_1, st_1, q_task, t_state):
        """
        更新Q值
        :param ps_0: original position
        :param act: select which router
        :param ps_1: new position after action
        :param st_1: State of next router after action
        :param q_task: Q table of this task.
        :param t_state:
        :return: Q table updated
        """
        reward = Reward[st_1]
        # 终点 / 堵塞
        if ps_0 == t_state[1][1] or \
                st_1 == state_stuck:
            q_1 = 0.0
        else:
            action_1 = self.explore_exploit(q_task[act])
            if METHOD == 1:
                'SARSA'
                q_1 = q_task[act][action_1]
            else:
                'Q-learning'
                q_1 = np.max(q_task[act])
        # 贝尔曼方程更新
        return self.bellman(ps_0, act, reward, q_1, q_task, t_state)

    def bellman(self, ps_cur, a, reward, q_next, q_task, t_state):
        """
        贝尔曼方程更新Q值
        :param ps_cur: 原先所在的节点
        :param a: 选择动作
        :param reward: 获得奖励
        :param q_next: Q(st_1, act_1)
        :param q_task: Q table of task
        :param t_state:
        :return:
        """
        # done --> Q no change
        if ps_cur == t_state[1][1]:
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
        if current == t_state[1][1]:
            # Remove data
            router_space[current] += data
            t_state[0] = np.zeros(self.R_len)
            t_state[2] = 1
            return current, state_done

        # Invalid action
        if self.Action[current][act] == 0:
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

    def random_action(self):
        """
        随机选择动作
        :return action
        """
        a_next = np.random.randint(self.R_len)
        return a_next
