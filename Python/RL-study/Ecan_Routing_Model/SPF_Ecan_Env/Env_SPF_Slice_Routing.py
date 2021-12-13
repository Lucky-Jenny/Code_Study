import numpy as np
import logging

'参数设置'
# 网络情况
state_stuck = 0         # -20
state_normal = 1        # 1
state_reverse = 2       # -10
state_invalid = 3       # -100
state_done = 4          # 10


class SpfSliceRoutingEnv:
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
        self.Action = model.Action_Space
        # 任务列表
        self.Task_List = task_list
        self.T_len = len(task_list)
        self.T_idx = 0

        # 时隙限制
        self.time_limit = 100

        self.M_len = len(self.Router_Perform)
        # self.short_path = []

    def start_slice_routing_in_spf(self, task_space, router_space, path_task):
        """
        分片路由
        :param task_space:
        :param router_space:
        :param path_task:
        :return: times， stuck_prob
        """
        t = 0
        stk_sum, task_mark, joule = 0, 0, 0
        for t in range(self.time_limit):
            has_stuck = 0
            ret_st = self.add_new_task(task_space, router_space)
            if ret_st == state_stuck:
                has_stuck = 1
            # test
            # print('[', t, ']', 'R_space:', router_space)

            # 逆序遍历，防止自传递
            for r in reversed(self.R_list):
                # 队列为空
                if not self.Router_Task_Index_Queue[r]:
                    continue
                # 每个节点在t时间能够处理的数据量，处理缓存: Forward Buff
                fwd_buff = self.Router_Perform[r][0]
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
                    # 执行路由
                    ps_new, state_new, fwd_buff = self.do_route_spf(s, r, fwd_buff, task_space[s], router_space, path_task[s])

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

    def do_route_spf(self, t_idx, r_idx, fwd_buff, t_state, router_spc, path_t):
        """
        分片路由，更新状态。
        :param t_idx:
        :param r_idx:
        :param fwd_buff:
        :param t_state:
        :param router_spc:
        :param path_t: routing path of t_idx
        :return: 更新后的节点位置，网络状态，buff容量
        """
        t_vector = t_state[0]
        # 确定数据块大小
        d_size = t_vector[r_idx]
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

        # 在short_path中找到下一个节点
        act = self.get_next_node(r_idx, path_t)

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
        fwd_buff = self.update_queue_and_buff(fwd_buff, r_idx, act, t_idx, t_size, buff_not_enough)

        return act, state_normal, fwd_buff

    def get_next_node(self, idx, path_t):
        """

        :param idx:
        :param path_t:
        :return:
        """
        act = 0
        if idx in path_t:
            next_index = path_t.index(idx) + 1
            act = path_t[next_index]
        else:
            for p in path_t:
                if p > idx:
                    act = p
                    break
        return act

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

    def get_paths_for_each_task(self, task_path):
        """

        :param task_path:
        :return:
        """
        for i in range(self.T_len):
            t_start, t_target = self.get_terminal_points(i)
            s_path = self.get_1_path_from_dijkstra(t_start, t_target)
            task_path[i] = s_path

    def get_1_path_from_dijkstra(self, start, end):
        """
        该方法只能返回一条最短路径
        :param start: 起点
        :param end: 终点
        :return: 最短路径
        """
        # 获取以start为基准的最短路径表
        s_table = self.get_path_table(start, end)
        # 从end开始进行append
        x = end
        route = []
        while x != start:
            route.append(x)
            x = s_table[x][2]
        route.append(x)
        # 逆序
        route.reverse()
        self.short_path = route
        return route

    def get_path_table(self, s, end):
        spf_table = {a: [False, 99, 0] for a in range(self.M_len)}
        length = 1
        node = s

        # 更新自己
        spf_table[node] = [True, 0, 0]
        self.recursion_update(spf_table, node, length, end)
        # print(spf_table)
        return spf_table

    def recursion_update(self, table, idx, distance, terminal):
        """
        递归更新，边界条件为terminal，因此可迭代更新
        :param table: 路径表
        :param idx: 当前节点
        :param distance: 距离
        :param terminal: 终点，作为递归的结束
        :return: none
        """
        if idx == terminal:
            return

        for i in range(self.M_len):
            if self.Action[idx][i] == 1:
                if table[i][1] < distance:
                    continue
                # Update
                table[i][0] = True
                table[i][1] = min(distance, table[i][1])
                table[i][2] = idx
                self.recursion_update(table, i, distance+1, terminal)

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
        r_start, r_target = self.get_terminal_points(idx)

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

    def get_terminal_points(self, t_idx):
        """
        Get start_node and target_node according to task index.
        :param t_idx: task index.
        :return start_node, target_node
        """
        # 计算起点/目标节点的位置
        idx_sta = self.Task_List[t_idx] % len(self.A_start)
        idx_tar = self.Task_List[t_idx] % len(self.A_target)
        start_node = self.A_start[idx_sta]
        target_node = self.A_target[idx_tar]
        return start_node, target_node

    def select_action(self, r_id, q_array):
        """

        :param r_id: Index of router
        :param q_array:
        :return:
        """
        act = np.argmax(q_array[r_id])
        is_invalid = False
        # 如果无法从Q表中获取有效值，采用随机动作(必须有效)
        if self.Action[r_id][act] == 0:
            is_invalid = True
        else:
            # 如果反向，检查是否陷入了死循环
            if act < r_id:
                act_nxt = np.argmax(q_array[act])
                if act_nxt == r_id:
                    is_invalid = True

        if is_invalid:
            # nxt = self.random_action()
            # 给予方向性
            for a in range(r_id, self.R_len, 1):
                if self.Action[r_id][a] == 1:
                    act = a
                    break
        return act
