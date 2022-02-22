import numpy as np


# 网络情况
state_stuck = 0         # -50
state_normal = 1        # -1
state_reverse = 2       # -10
state_invalid = 3       # -100
state_done = 4          # 0


class DijkstraEnv:
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

        self.M_len = len(route_pfm)
        self.short_path = []

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
        # 判断有效性
        if idx >= self.T_len or self.Task_List[idx] > router_space[0]:
            return

        # Update Task Space
        task_space[idx][0][0] = self.Task_List[idx]
        task_space[idx][1] = 0
        # Update Router Space
        router_space[0] -= self.Task_List[idx]

        # 索引自增
        self.T_idx += 1

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

    def start_routing_in_spf(self, task_space, router_space, t_path):
        """

        :param task_space:
        :param router_space:
        :param t_path: 任务路径
        :return:
        """
        t = 0
        stk_sum = 0
        for t in range(self.time_limit):
            task_mark = 0
            self.add_new_task(task_space, router_space)
            has_stuck = 0
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
                ps_new, state_new = self.do_route(task_space[s], router_space)
                '记录路径'
                t_path[s][0] = np.max(task_vector)
                t_path[s][1].append(ps)
                if state_new == state_stuck:
                    has_stuck = 1
            if has_stuck:
                stk_sum += 1

            if task_mark == self.T_len:
                break
        return t, stk_sum

    def do_route(self, t_state, router_space):
        """

        :param t_state:
        :param router_space
        :return:
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

        # 在short_path中找到下一个节点
        act = self.get_next_node(current)
        # Will be stuck
        if data > router_space[act]:
            return current, state_stuck

        # Update Router State
        router_space[act] -= data
        router_space[current] += data
        # Update Task State
        t_vector[current] = 0
        t_vector[act] = data

        return act, state_normal

    def get_next_node(self, idx):
        act = 0
        if idx in self.short_path:
            next_index = self.short_path.index(idx) + 1
            act = self.short_path[next_index]
        else:
            for p in self.short_path:
                if p > idx:
                    act = p
                    break
        return act
