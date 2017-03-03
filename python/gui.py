#!/usr/bin/python3

import tkinter as tk
import os

root = tk.Tk()
tfield = tk.Text(root)
tfield.pack()
for line in os.popen("ls", 'r'):
    tfield.insert("end", line)
root.mainloop()
