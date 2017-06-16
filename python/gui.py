#!/usr/bin/python3

import tkinter as tk
import os


def center(toplevel):
    toplevel.update_idletasks()
    w = toplevel.winfo_screenwidth()
    h = toplevel.winfo_screenheight()
    size = tuple(int(_) for _ in toplevel.geometry().split('+')[0].split('x'))
    x = w/2 - size[0]/2
    y = h/2 - size[1]/2
    toplevel.geometry("%dx%d+%d+%d" % (size + (x, y)))

def clickOK():
    global count
    count = count + 1
    #label2.configure(text = "Click OK " + str(count) + " times")

def clickReload():
    for line in os.popen("ls", 'r'):
        tfield.insert("end", line)



count = 0
win = tk.Tk()
win.title("Atlantis info")

#label1 = tk.Label(win, text = "http://atlantis.senao.com")
#label2 = tk.Label(win, text = "Result")

button1 = tk.Button(win, text = "OK", command = clickOK)
button2 = tk.Button(win, text = "Reload", command = clickReload)

tfield = tk.Text(win)
scroll = tk.Scrollbar(win, orient = "vertical", command = tfield.yview)


#label1.grid(column = 0, row = 0)
#label2.grid(column = 0, row = 1)
button1.grid(column = 0, row = 0)
button2.grid(column = 0, row = 1)
tfield.grid(column = 1, row = 0, rowspan = 2)
#scroll.grid(column = 2, row = 0, rowspan = 15, columnspan = 1, sticky = "ns")
scroll.grid(column = 2, row = 0, rowspan = 2, sticky = "ns")

center(win)
win.mainloop()
