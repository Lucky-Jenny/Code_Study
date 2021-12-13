
class MAPLocal:
    def __init__(self):
        # 路由节点 --> [计算速率, 缓存容量]
        self.Router_Perform = [
            [13, 300],  # 0
            [12, 300],  # 1
            [12, 140],  # 2
            [15, 110],  # 3
            [14, 170],  # 4
            [13, 150],  # 5
            [13, 200],  # 6
            [15, 200],  # 7
            [16, 300]   # 8
        ]

        # 节点个数
        self.R_len = len(self.Router_Perform)

        # 起始/目标节点的集合
        self.A_start = [0, 1]
        self.A_target = [6, 7, 8]

        # 动作空间
        self.Action_Space = [
           # 0  1  2  3  4  5  6  7  8
            [0, 0, 1, 1, 0, 0, 0, 0, 0],    # 0
            [0, 0, 1, 1, 0, 0, 0, 0, 0],    # 1
            [1, 1, 0, 0, 1, 1, 0, 0, 0],    # 2
            [1, 1, 0, 0, 1, 1, 0, 0, 0],    # 3
            [0, 0, 1, 1, 0, 0, 1, 1, 1],    # 4
            [0, 0, 1, 1, 0, 0, 1, 1, 1],    # 5
            [0, 0, 0, 0, 1, 1, 0, 1, 0],    # 6
            [0, 0, 0, 0, 1, 1, 1, 0, 1],    # 7
            [0, 0, 0, 0, 1, 1, 0, 1, 0]     # 8
        ]

        self.Action_Space_1d = [
           # 0  1  2  3  4  5  6  7  8
            [0, 0, 1, 1, 0, 0, 0, 0, 0],    # 0
            [0, 0, 1, 1, 0, 0, 0, 0, 0],    # 1
            [0, 0, 0, 0, 1, 1, 0, 0, 0],    # 2
            [0, 0, 0, 0, 1, 1, 0, 0, 0],    # 3
            [0, 0, 0, 0, 0, 0, 1, 1, 1],    # 4
            [0, 0, 0, 0, 0, 0, 1, 1, 1],    # 5
            [0, 0, 0, 0, 0, 0, 0, 1, 0],    # 6
            [0, 0, 0, 0, 0, 0, 0, 0, 1],    # 7
            [0, 0, 0, 0, 0, 0, 0, 0, 0]     # 8
        ]

'''
# 路由节点 --> [计算速率, 缓存容量]
Router_Perform = [
    [20, 300],  # 0
    [10, 140],  # 1
    [10, 130],  # 2
    [10, 120],  # 3
    [15, 170],  # 4
    [10, 130],  # 5
    [15, 200],  # 6
    [10, 200],  # 7
    [20, 300]   # 8
]

Action_Space = [
    [0, 1, 1, 1, 0, 0, 0, 0, 0],    # 0
    [1, 0, 0, 0, 1, 0, 0, 0, 0],    # 1
    [1, 0, 0, 0, 0, 1, 0, 0, 0],    # 2
    [1, 0, 0, 0, 1, 0, 0, 1, 0],    # 3
    [0, 1, 0, 1, 0, 0, 1, 0, 0],    # 4
    [0, 0, 1, 0, 0, 0, 0, 1, 0],    # 5
    [0, 0, 0, 0, 1, 0, 0, 1, 1],    # 6
    [0, 0, 0, 1, 0, 1, 1, 0, 1],    # 7
    [0, 0, 0, 0, 0, 0, 1, 1, 0]     # 8
]
'''
'''
# 动作空间
Action_Space = [
    [0, 1, 1, 1, 0, 0, 0, 0, 0],    # 0
    [0, 0, 0, 0, 1, 0, 0, 0, 0],    # 1
    [0, 0, 0, 0, 0, 1, 0, 0, 0],    # 2
    [0, 0, 0, 0, 1, 0, 0, 1, 0],    # 3
    [0, 0, 0, 0, 0, 0, 1, 0, 0],    # 4
    [0, 0, 0, 0, 0, 0, 0, 1, 0],    # 5
    [0, 0, 0, 0, 0, 0, 0, 1, 1],    # 6
    [0, 0, 0, 0, 0, 0, 0, 0, 1],    # 7
    [0, 0, 0, 0, 0, 0, 0, 0, 0]     # 8
]
'''

"""
'路由节点 --> [计算速率, 缓存容量]'
Router_Perform = [
    [3, 300],  # 0
    [2, 140],  # 1
    [2, 130],  # 2
    [5, 120],  # 3
    [4, 170],  # 4
    [3, 130],  # 5
    [3, 300]   # 6
]

'动作空间'
Action_Space = [
    [0, 1, 1, 1, 0, 0, 0],
    [1, 0, 0, 1, 1, 0, 0],
    [1, 0, 0, 1, 0, 1, 0],
    [1, 1, 1, 0, 1, 1, 1],
    [0, 1, 0, 1, 0, 0, 1],
    [0, 0, 1, 1, 0, 0, 1],
    [0, 0, 0, 1, 1, 1, 0]
]
"""
