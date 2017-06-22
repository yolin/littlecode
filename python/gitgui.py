#!/usr/bin/python3

import tkinter as tk
import os
import subprocess

import tkinter.filedialog



def center(toplevel):
    toplevel.update_idletasks()
    w = toplevel.winfo_screenwidth()
    h = toplevel.winfo_screenheight()
    size = tuple(int(_) for _ in toplevel.geometry().split('+')[0].split('x'))
    x = w/2 - size[0]/2
    y = h/2 - size[1]/2
    toplevel.geometry("%dx%d+%d+%d" % (size + (x, y)))

def clickReload():
    tfield.delete('1.0', 'end')
    for line in os.popen("ls"+" "+entryPath.get(), 'r'):
        tfield.insert("end", line)


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
myName = getSetting("")
myEmail = getSetting("")
myCd2method = getSetting("")
myServer = getSetting("")
myToken = getSetting("")

root = tk.Tk()
root.title(myServer)


labelPath = tk.Label(root, text = 'path:')
entryPath = tk.Entry(root)

buttonVendors = tk.Button(root, text = 'Change', command = clickShow)
buttonGitList = tk.Button(root, text = 'clickGitList', command = clickGitList)

labelInfo = tk.Label(root, text = 'git config info:\n  Name: ' + myName +
        '\n  Email: ' + myEmail + '\n  ' + 'Token: ' + myToken, justify="left")

buttonReload = tk.Button(root, text = "Dir", command = clickReload)

#add text and scroll bar
tfield = tk.Text(root)
scroll = tk.Scrollbar(root, orient = "vertical", command = tfield.yview)
tfield.configure( yscrollcommand=scroll.set )
####


######grid layout##########
labelInfo.grid(column = 1, row = 0)
tfield.grid(column = 2, row = 0, rowspan=3)
scroll.grid(column = 3, row = 0, rowspan=3, sticky = "ns")
labelPath.grid(column = 0, row = 1, sticky='e')
entryPath.grid(column = 1, row = 1, sticky='we')
buttonReload.grid(column = 4, row = 0, sticky='wen')
buttonVendors.grid(column = 4, row = 1, sticky='wen')
buttonGitList.grid(column = 4, row = 2, sticky='wen')

center(root)
root.mainloop()
