#!/usr/bin/python3
# -*- coding: utf-8 -*-

import tkinter as tk
import os
import subprocess

import tkinter.filedialog
import serial

import threading

import time
from colors import color

def center(toplevel):
    toplevel.update_idletasks()
    w = toplevel.winfo_screenwidth()
    h = toplevel.winfo_screenheight()
    size = tuple(int(_) for _ in toplevel.geometry().split('+')[0].split('x'))
    x = w/2 - size[0]/2
    y = h/2 - size[1]/2
    toplevel.geometry("%dx%d+%d+%d" % (size + (x, y)))



def handle_data(data):
    for p in data.splitlines(True):
        print("----start------")
        print(p)
        if p[-2] == "\r":
            tfield.insert("end", p[:-2])
            tfield.insert("end", "\n")
        else:
            tfield.insert("end", p)
        print("----end------")
        tfield.see("end")

def read_from_port(ser):
    while(ser.isOpen()):
        try:
            if (ser.inWaiting()>0):
                 #print("thread got data")
                 reading = ser.readline().decode('ascii')
                 handle_data(reading)
            else:
                 time.sleep(0.1)
        except:
            print("thread: read_from_port ng")
            break
    print("thread: read_from_port exit")

#thread = threading.Thread(target=read_from_port, args=(serial_port,))
#thread.daemon = True
#thread.start()

def clickStart():
    if(serial_port.isOpen()):
        print(buttonStart.cget("text"))
        if entryCmd.get() == "":
            serial_port.write(("ping "+entryIP.get()+"\n").encode('ascii'))
        else:
            serial_port.write((entryCmd.get()+"\n").encode('ascii'))


def clickStop():
    if(serial_port.isOpen()):
        print(buttonStop.cget("text"))
        serial_port.write("\x03".encode('ascii'))

def clickLogout():
    if(serial_port.isOpen()):
        print(buttonLogout.cget("text"))
        serial_port.write("\x04".encode('ascii'))



def clickReload():
    tfield.delete('1.0', 'end')


def clickShow():
    folder = tk.filedialog.askdirectory()
    entryPath.delete(0, 'end')
    entryPath.insert(0, folder) 


def clickGitList():
    tfield.delete('1.0', 'end')
    for line in os.popen("gitlist", 'r'):
        tfield.insert("end", line)



def getSetting(myinput):
    process = subprocess.getoutput("git config --global --get " + myinput)
    print(myinput + ":", end="")
    if process:
        print(process.split()[0])
        return (process.split()[0])
    else:
        return ""

def setSetting(myinput, myvalue):
    process = subprocess.getoutput("git config --global " + myinput + " " +
            myvalue)
    print(myinput + myvalue)
    return (process.split()[0])



count = 0
myName = getSetting("user.name")
myEmail = getSetting("user.email")
myCd2method = getSetting("user.cd2method")
myServer = getSetting("senao.server")
myToken = getSetting("senao.gitlabtoken")

root = tk.Tk()
root.title(myServer)



listDev = tk.Listbox(root)
listPower = tk.Listbox(root)


for line in os.popen("ls /dev/ttyUSB*", 'r'):
    listDev.insert("end", line.splitlines())
    listPower.insert("end", line.splitlines())


#for item in ["one", "two", "three", "four"]:
#    listDev.insert('end', item)


serial_port = 0
power_port = 0

def start_power_thread():
    print("thread start...")
    global power_port
    index = listPower.curselection()[0]
    power_port = serial.Serial(listPower.get(index)[0], baudrate=115200,
            parity='N', stopbits=1, xonxoff=0, rtscts=0, timeout=0.1)
    print(power_port)
    thread = threading.Thread(target=read_from_port, args=(power_port,))
    thread.daemon = True
    thread.start()
    print(listPower.get(index)[0]+" opend")


def start_thread():
    print("thread start...")
    global serial_port
    index = listDev.curselection()[0]
    serial_port = serial.Serial(listDev.get(index)[0], baudrate=115200,
            parity='N', stopbits=1, xonxoff=0, rtscts=0, timeout=0.1)
    print(serial_port)
    thread = threading.Thread(target=read_from_port, args=(serial_port,))
    thread.daemon = True
    thread.start()
    print(listDev.get(index)[0]+" opend")

def listboxcheck(event):
    labelList.config(text="Dev="+listDev.get(listDev.curselection()[0])[0])
    if(listDev.get("active")):
        try:
            if(serial_port.isOpen() == False):
                print("not open serial")
        except:
            print("unexcept error")
        else:
            print("serial_port.close()")
            serial_port.close()
            time.sleep(2)
            print("serial_port close ok")

        index = listDev.curselection()[0]
        print(listDev.get(index))
        thread = threading.Thread(target=start_thread)
        thread.daemon = True
        thread.start()
        time.sleep(1)

def listpowercheck(event):
    labelPower.config(text="Power="+listPower.get(listPower.curselection()[0])[0])
    labelList.config(text="Dev="+listPower.get(listPower.curselection()[0])[0])
    if(listPower.get("active")):
        try:
            if(serial_port.isOpen() == False):
                print("not open serial")
        except:
            print("unexcept error")
        else:
            print("serial_port.close()")
            serial_port.close()
            time.sleep(2)
            print("serial_port close ok")

        index = listPower.curselection()[0]
        print(listPower.get(index))
        thread = threading.Thread(target=start_power_thread)
        thread.daemon = True
        thread.start()
        time.sleep(1)



listDev.bind('<ButtonRelease-1>', listboxcheck)
listPower.bind('<ButtonRelease-1>', listpowercheck)

labelList = tk.Label(root, text = 'List:')
labelPower = tk.Label(root, text = 'Power:')
labelPath = tk.Label(root, text = 'Log path:')
labelCmd = tk.Label(root, text = 'command:')
labelLoop = tk.Label(root, text = 'Loop:')
labelBaud = tk.Label(root, text = 'Baudrate:')
labelIP = tk.Label(root, text = 'DUT ip:')
labelTimeout = tk.Label(root, text = 'Timeout:')
labelBoottime = tk.Label(root, text = 'Boot time:')
labelOfftime = tk.Label(root, text = 'Off time:')
entryPath = tk.Entry(root)
entryCmd = tk.Entry(root)
entryLoop = tk.Entry(root)
entryBaud = tk.Entry(root)
entryIP = tk.Entry(root)
entryTimeout = tk.Entry(root)
entryBoottime = tk.Entry(root)
entryOfftime = tk.Entry(root)

buttonPath = tk.Button(root, text = 'open', command = clickShow)
#buttonGitList = tk.Button(root, text = 'clickGitList', command = clickGitList)

labelInfo = tk.Label(root, text = 'git config info:\n  Name: ' + myName +
        '\n  Email: ' + myEmail + '\n  ' + 'Token: ' + myToken, justify="left")

buttonReload = tk.Button(root, text = "Clear", command = clickReload)

buttonStart = tk.Button(root, text = "Start", command = clickStart)
buttonStop = tk.Button(root, text = "Stop(c-c)", command = clickStop)
buttonLogout = tk.Button(root, text = "Logout(c-d)", command = clickLogout)

#add text and scroll bar
#tfield = tk.Text(root, bg = 'black', fg = 'white')
tfield = tk.Text(root)

scroll = tk.Scrollbar(root, orient = "vertical", command = tfield.yview)
tfield.configure( yscrollcommand=scroll.set )
####


####insert terminal######
#termf = tk.Frame(root, height=400, width=500)
#wid = termf.winfo_id()
#os.system('xterm -into %d -geometry 80x30 -sb &' % wid)
##########################







listrow=10

######grid layout##########
labelInfo.grid(column = 1, row = 0)

tfield.grid(column = 3, row = 0, rowspan=40, sticky = "ewsn")
scroll.grid(column = 4, row = 0, rowspan=40, sticky = "ns")

labelList.grid(column = 0, row = 1,columnspan=3, sticky='wsn')
labelPower.grid(column = 0, row = 2,columnspan=3, sticky='wsn')
listDev.grid(column=0, row=3, columnspan=3, rowspan=listrow,sticky='wsn')
listPower.grid(column=0, row=3, columnspan=3, rowspan=listrow,sticky='esn')

labelPath.grid(column = 0, row = listrow+5, sticky='e')
entryPath.grid(column = 1, row = listrow+5, sticky='we')
buttonPath.grid(column = 2, row = listrow+5, sticky='wen')

labelCmd.grid(column = 0, row = listrow+6, sticky='e')
entryCmd.grid(column = 1, row = listrow+6, sticky='we')
buttonReload.grid(column = 2, row = listrow+6, sticky='wen')

labelLoop.grid(column = 0, row = listrow+7, sticky='we')
entryLoop.grid(column = 1, row = listrow+7, sticky='we')

labelBaud.grid(column = 0, row = listrow+8, sticky='we')
entryBaud.grid(column = 1, row = listrow+8, sticky='we')

labelIP.grid(column = 0, row = listrow+9, sticky='we')
entryIP.grid(column = 1, row = listrow+9, sticky='we')

labelTimeout.grid(column = 0, row = listrow+10, sticky='we')
entryTimeout.grid(column = 1, row = listrow+10, sticky='we')

labelBoottime.grid(column = 0, row = listrow+11, sticky='we')
entryBoottime.grid(column = 1, row = listrow+11, sticky='we')

labelOfftime.grid(column = 0, row = listrow+12, sticky='we')
entryOfftime.grid(column = 1, row = listrow+12, sticky='we')

#termf.grid(column=5, row=0, rowspan=40, sticky='ewsn')

#buttonGitList.grid(column = 4, row = 2, sticky='wen')

buttonStart.grid(column = 0, row = listrow+14, columnspan=3, sticky='ew')
buttonStop.grid(column = 0, row = listrow+15, columnspan=3, sticky='ew')
buttonLogout.grid(column = 0, row = listrow+16, columnspan=3, sticky='ew')


center(root)
root.mainloop()
