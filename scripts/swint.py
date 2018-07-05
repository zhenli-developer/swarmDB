#!/usr/bin/env python2.7

import os
import shutil
import json
import uuid
import sys
import subprocess
import threading
import copy

from swint.Peer import Peer
from swint.Node import Node

def folder_setup(root_folder):
    if(os.path.exists(root_folder)):
        shutil.rmtree(root_folder)
    os.mkdir(root_folder)

def sub_folder_setup(root_folder, swarm):
    for peer_info in swarm:
        os.mkdir(root_folder +"/" + peer_info['peer'].name)

#TODO encapsulate in Swarm
def create_swarm_info(n):
    swarm = []
    for i in range( n ):
        info = {'peer' : Peer(i)}
        info['node'] = Node(info["peer"])
        swarm.append(info)
    return swarm

def make_peers_file_text(indexes, swarm):
    file_text = "["
    for index in indexes:
        file_text = file_text + swarm[index]["peer"].to_json() + ","

    file_text = file_text[:-1]
    file_text = file_text +"]"
    return file_text

def write_peers_list_files(root_folder, swarm):
    index = 0
    for peer_info in swarm:
        indexes = [0,1]
        if index not in indexes:
            indexes.append(index)
        file_text = make_peers_file_text(indexes, swarm)
        peers_file = open(root_folder + "/" + peer_info['peer'].name + "/peers.json", "w")
        peers_file.write(file_text)
        index = index + 1

def write_peer_config_files(root_folder, swarm):
    index = 0
    for peer_info in swarm:
        config_file = open(root_folder + "/" + peer_info['peer'].name + "/peer.json", "w")
        config_file.write(peer_info['node'].to_json())

def copy_daemons_to_working_folders(root_folder, swarm):
    i = 0
    for peer_info in swarm:
        shutil.copy("../cmake-build-debug/output/swarm", root_folder + "/" + peer_info['peer'].name)
        i = i+1

def create_add_peer(peer):
    add = {}
    add["bzn-api"] = "raft"
    add["cmd"] = "add_peer"
    add["data"] = {}
    add["data"]["peer"] = peer
    return json.dumps(add)

def create_remove_peer(uuid):
    remove = {}
    remove["bzn-api"] = "raft"
    remove["cmd"] = "remove_peer"
    remove["data"] = {}
    remove["data"]["uuid"] = uuid
    return json.dumps(remove)

def perform_long_test(peers):
    #cdir = os.curdir
    #folder = peer_folder(0, peers)
    #os.chdir(folder)
    #p = subprocess.Popen(["./swarm", "-c", "bluzelle.json"], stdout=subprocess.PIPE)
    #print("started swarm: " + str(p.pid))

    #print("killing swarm: " + str(p.pid))
    #p.kill()

    #os.chdir(cdir)

    i = 0


    def hello():
        print("hello, world - "  )

    t = threading.Timer(1.0, hello)
    t.start() # after 30 seconds, "hello, world" will be printed
    return t





    #i = 0
    #for peer in peers:
    #    folder = peer_folder(i, peers)
    #    subprocess.run(["./swarm","-c","bluzelle.json"])
    #print("swarm processes started")




    # fib(0) = 1
    # fib(1) = 1
    # fib(2) = fib(0) + fib(1)
    # fib(3) = fib(1) + fib(2)
    # ...
    # fib(i) = fib(i-2) + fib(i-1)
    # if n > 100 start removing fib(rand(0..n))
    # at fib(150) start over




    return 0


def crud_instructions():
    print("\nHere's how you do CRUD:")
    print("./crud -n 127.0.0.1:49152 ping")
    print("./crud -n 127.0.0.1:49152 create -u 53b5645b-a2b1-42a1-a907-145ac2851d34 -k temp -v 38493")
    print("./crud -n 127.0.0.1:49154 read -u 53b5645b-a2b1-42a1-a907-145ac2851d34 -k temp")
    print("./crud -n 127.0.0.1:49152 update -u 53b5645b-a2b1-42a1-a907-145ac2851d34 -k temp -v 3849")
    print("./crud -n 127.0.0.1:49154 delete -u 53b5645b-a2b1-42a1-a907-145ac2851d34 -k temp")
    print("./crud -n 127.0.0.1:49152 has -k KEY -u 53b5645b-a2b1-42a1-a907-145ac2851d34")
    print("./crud -n 127.0.0.1:49153 keys -u 53b5645b-a2b1-42a1-a907-145ac2851d34")


def print_all_instructions(swarm):
    print("\nHere's how you add peers:")
    for v in swarm:
        print(create_add_peer(v["peer"]))
    print("\nHere's how you add peers:")
    for v in peers:
        print(create_remove_peer(v["peer"]["uuid"]))
    crud_instructions()



def main():
    n = 3
    root_folder = "./test"

    # TODO: do get opts correctly
    if len(sys.argv)>1 :
        n = int(sys.argv[1])

    # TODO: Implement Swarm class
    print("Setting up "+root_folder+" folder...")
    folder_setup(root_folder)

    print("\nCreating peer info for a swarm of " + str(n) + " peers...")
    swarm = create_swarm_info(n)

    print("\nCreating the peer sub folders...")
    sub_folder_setup(root_folder, swarm)

    print("\nCreating the peers.json files that lists the nodes in the swarm...")
    write_peers_list_files(root_folder, swarm)

    print("\nCreating the peer.json config file for each node in the swarm...")
    write_peer_config_files(root_folder, swarm)

    print("\nCopying the daemon to the peers folders...")
    copy_daemons_to_working_folders(root_folder, swarm)


    #### print_all_instructions(swarm)

    # TODO start all daemons
    print (swarm[0]['peer'].to_json())
    print (swarm[0]['node'].to_json())




    # TODO send commands to daemons



    return 0



#########################################
main()
