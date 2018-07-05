import json
import uuid

class Peer:
    def __init__(self, index):
        self.name = "peer" + str(index)
        self.host = "127.0.0.1"
        self.port = 49152 + index
        self.http_port = 9082 + index
        self.uuid = str(uuid.uuid4())

    def to_json(self):
        return json.dumps(self, default=lambda o: o.__dict__,
                          sort_keys=True, indent=4)