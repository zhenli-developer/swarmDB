from .Peer import Peer
from .Node import Node

class Swarm:
    def __init__(self, n, root_folder):
        self.root_folder = root_folder
        self.nodes = []
        for i  in range(n):
            node = {'peer':Peer()}
            node['node'] = Node(node['peer'])


