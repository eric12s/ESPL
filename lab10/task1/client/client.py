#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Wed Dec  8 13:03:13 2021

@author: alex
"""
import socket
import threading
import sys
import random
import os
import subprocess

bufferSize = 1024


#Client Code
def ReceiveData(sock):
    while True:
        try:
            data,addr = sock.recvfrom(bufferSize)
            print(data.decode('utf-8'))
        except:
            pass

def RunClient(serverIP):
    host = socket.gethostbyname(socket.gethostname())
    port = random.randint(6000,10000)
    print('Client IP->'+str(host)+' Port->'+str(port))
    server = (str(serverIP),5000)
    UDPClientSocket = socket.socket(family=socket.AF_INET,type=socket.SOCK_DGRAM)
    UDPClientSocket.bind((host,port))
    name = 'make connection to the server'
    UDPClientSocket.sendto(name.encode('utf-8'),server)
    threading.Thread(target=ReceiveData,args=(UDPClientSocket,)).start()
    mounted = False
    navigating = False
    print("What is your request:")
    while True:        
        request = input()
        splittedRequest = request.split()
        if splittedRequest[0] == 'mount':
            mounted = True
            path = splittedRequest[2].split(':')
            server = (path[0], int(path[1]))
            UDPClientSocket.sendto(request.encode('utf-8'), server)  
        elif mounted == True and splittedRequest[0] == 'cd' and splittedRequest[1] == str(serverIP) + ':5000' + ':/Server':
            navigating = True
            UDPClientSocket.sendto(request.encode('utf-8'), server)  
        elif navigating == True:
            if splittedRequest[1] == 'local:':
                navigating = False
                UDPClientSocket.sendto('stopnav'.encode('utf-8'), server)
            else:
                UDPClientSocket.sendto(request.encode('utf-8'), server)
        elif splittedRequest[0] == 'cd':
            os.chdir(splittedRequest[1])
        else:
            result = subprocess.run(splittedRequest, stderr=subprocess.STDOUT, shell=False)
            result.stdout
    #UDPClientSocket.sendto(data.encode('utf-8'),server)
    UDPClientSocket.close()
    os._exit(1)
#Client Code Ends Here




if __name__ == '__main__':

    RunClient(sys.argv[1])
    