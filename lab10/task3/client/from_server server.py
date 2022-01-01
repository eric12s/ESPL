#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Fri Dec  3 13:05:25 2021

@author: alex
"""
import socket
import threading
import queue
import sys
import subprocess
import os

bufferSize = 1024



#Server Code
def RecvData(sock,recvPackets):
    while True:
        data,addr = sock.recvfrom(bufferSize)
        recvPackets.put((data,addr))

def RunServer(host):
    #host = socket.gethostbyname(socket.gethostname())
    port = 5000
    print('Server hosting on IP-> '+str(host))
    UDPServerSocket = socket.socket(family=socket.AF_INET,type=socket.SOCK_DGRAM)
    UDPServerSocket.bind((host,port))
    recvPackets = queue.Queue()

    print('Server Running...')

    threading.Thread(target=RecvData,args=(UDPServerSocket,recvPackets)).start()

    password = 'p'
    access_list = []
    navigating_now = []
    while True:
        while not recvPackets.empty():
            data,addr = recvPackets.get()
            data = data.decode('utf-8')
            li = data.split()
            if (li[0] == 'mount'):
                if (li[1] == password):
                    access_list.append(addr)
                    message = "SERVER: Done"
                else:
                    message = "SERVER: Wrong password"
                UDPServerSocket.sendto(message.encode('utf-8'), addr)
            elif (li[0] == 'cd' and addr in access_list and not addr in navigating_now):
                navigating_now.append(addr)
                message = "SERVER: Done"
                UDPServerSocket.sendto(message.encode('utf-8'), addr)
            elif (addr in navigating_now):
                if li[0] == 'stopnav':
                    navigating_now.remove(addr)
                elif li[0] == 'cd':
                    os.chdir(li[1])
                elif li[0] == 'get':
                    if not os.path.exists(li[1]):
                        UDPServerSocket.sendto("file-doesn't-exist".encode(), addr)
                    else:
                        print('sending file')
                        file = open(li[1], 'rb')
                        fileData = file.read(1024)
                        while fileData:
                            if UDPServerSocket.sendto(fileData, addr):
                                fileData = file.read(1024)
                        file.close()
                else:
                    result = subprocess.run(li, stderr=subprocess.STDOUT, shell=False, stdout=subprocess.PIPE)
                    UDPServerSocket.sendto(result.stdout, addr)

    UDPServerSocket.close()
#Serevr Code Ends Here


if __name__ == '__main__':
    RunServer(sys.argv[1])

 