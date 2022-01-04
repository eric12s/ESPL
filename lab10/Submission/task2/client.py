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
from os.path import dirname, realpath, join
import subprocess

bufferSize = 1024

#Client Code

class FileReaderDetails():
    def __init__(self):
        self.gettingFile = False
        self.file_name = None
        self.path = None

    def setParams(self, _gettingFile, _file_name, _path):
        self.gettingFile = _gettingFile
        self.file_name = _file_name
        self.path = _path

    def getParams(self):
        return self.gettingFile, self.file_name, self.path


fileReaderDetails = FileReaderDetails()

def ReceiveData(sock):
    while True:
        try:
            data,addr = sock.recvfrom(bufferSize)
            gettingFile, file_name, path = fileReaderDetails.getParams()
            if gettingFile == False:
                print(data.decode('utf-8'))
            else:
                if path == 'cwd': path = ''
                else:  path = path + '/'
                if data.decode() == "file-doesn't-exist":
                    print("File doesn't exist on server.")
                    fileReaderDetails.setParams(False, None, None)
                else:
                    write_name = 'from_server_'+ file_name
                    fileReaderDetails.setParams(False, None, None)
                    if os.path.exists(write_name): os.remove(write_name)
                    with open(path + write_name ,'wb') as file:
                        while data:
                            file.write(data)
                            sock.settimeout(2)
                            data, addr = sock.recvfrom(bufferSize)
                    file.close()
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
            if splittedRequest[0] == 'cd' and splittedRequest[1] == 'local:':
                navigating = False
                UDPClientSocket.sendto('stopnav'.encode('utf-8'), server)
            else:
                if splittedRequest[0] == 'get':
                    fileReaderDetails.setParams(True, splittedRequest[1], splittedRequest[2])
                    UDPClientSocket.sendto(request.encode('utf-8'), server)
                else:
                    UDPClientSocket.sendto(request.encode('utf-8'), server)
        elif splittedRequest[0] == 'cd':
            os.chdir(splittedRequest[1])

        else:
            result = subprocess.run(splittedRequest, stderr=subprocess.STDOUT, shell=False)
            result.stdout
    UDPClientSocket.close()
    os._exit(1)
#Client Code Ends Here




if __name__ == '__main__':

    RunClient(sys.argv[1])
    