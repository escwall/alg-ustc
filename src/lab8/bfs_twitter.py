from collections import defaultdict, deque
import time
import os

def create_adj_list_from_file(file_path):
    adj_list = defaultdict(list)
    
    with open(file_path, 'r') as file:
        for line in file:
            line = line.strip()
            if line:
                u, v = map(int, line.split())
                adj_list[u].append(v)
    
    return adj_list

def bfs(adj_list, start):
    visited = set()
    queue = deque()
    node_cnt = 0
    
    begin = time.time()
    # 将起始节点添加到队列中，并标记为已访问
    queue.append(start)
    visited.add(start)
    
    while queue:
        node = queue.popleft()
        node_cnt = node_cnt + 1  # 统计访问节点数
        
        # 遍历当前节点的邻接节点
        for neighbor in adj_list[node]:
            if neighbor not in visited:
                queue.append(neighbor)
                visited.add(neighbor)
    
    end = time.time()

    return node_cnt, end - begin

# 测试代码
file_path = os.getcwd() + '/src/lab8/twitter_small.txt'  # 替换为实际的文件路径
adj_list = create_adj_list_from_file(file_path)
begin = 214328887
cnt, total_time = bfs(adj_list, begin)                                                      
print('遍历结点总数为{}，共耗时{:.2f}ms'.format(cnt, total_time * 1000))