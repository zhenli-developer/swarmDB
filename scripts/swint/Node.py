import json

class Node:

    def __init__(self, peer):
        self.ethereum = "0xddbd2b932c763ba5b1b7ae3b362eac3e8d40121a"
        self.ethereum_io_api_token = "53IW57FSZSZS3QXJUEBYT8F4YZ9IZFXBPQ"
        self.bootstrap_file = "./peers.json"
        self.listener_address = peer.host
        self.listener_port = peer.port
        self.uuid = peer.uuid
        self.debug_logging = True
        self.log_to_stdout = True

    def to_json(self):
        return json.dumps(self, default=lambda o: o.__dict__,
                          sort_keys=True, indent=4)
