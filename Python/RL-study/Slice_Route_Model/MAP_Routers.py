

# 路由节点 --> [计算速率, 缓存容量]
Router_Perform = [
    [30, 300],  # 0
    [15, 150],  # 1
    [15, 140],  # 2
    [10, 60],  # 3
    [10, 170],  # 4
    [10, 150],  # 5
    [20, 200],  # 6
    [15, 180],  # 7
    [20, 300]   # 8
]


# 动作空间
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

Action_Space_1d = [
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
Action_Space = [
    [1, 1, 1, 1, 0, 0, 0, 0, 0],    # 0
    [1, 1, 0, 0, 1, 0, 0, 0, 0],    # 1
    [1, 0, 1, 0, 0, 1, 0, 0, 0],    # 2
    [1, 0, 0, 1, 1, 0, 0, 1, 0],    # 3
    [0, 1, 0, 1, 1, 0, 1, 0, 0],    # 4
    [0, 0, 1, 0, 0, 1, 0, 1, 0],    # 5
    [0, 0, 0, 0, 1, 0, 1, 1, 1],    # 6
    [0, 0, 0, 1, 0, 1, 1, 1, 1],    # 7
    [0, 0, 0, 0, 0, 0, 1, 1, 1]     # 8
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





