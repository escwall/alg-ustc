from collections import defaultdict, deque

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
    
    # 将起始节点添加到队列中，并标记为已访问
    queue.append(start)
    visited.add(start)
    
    while queue:
        node = queue.popleft()
        print(node)  # 可以根据需要进行其他操作
        
        # 遍历当前节点的邻接节点
        for neighbor in adj_list[node]:
            if neighbor not in visited:
                queue.append(neighbor)
                visited.add(neighbor)

# 测试代码
file_path = 'twitter_small.txt'  # 替换为实际的文件路径
adj_list = create_adj_list_from_file(file_path)
bfs(adj_list, adj_list[214328887])