import subprocess

from tkinter import filedialog
from tkinter import *
import os
cwd = os.getcwd()
root = Tk()
root.filename =  filedialog.askopenfilename(initialdir = cwd,title = "Select file",filetypes = (("map files","map*"),("all files","*.*")))
print (root.filename)

def runProcess(exe):
    p = subprocess.Popen(exe, stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
    while(True):
        # returns None while subprocess is running
        retcode = p.poll()
        line = p.stdout.readline()
        yield line
        if retcode is not None:
            break


            self.right = tk.LabelFrame(win, text="Files", bg="alice blue", padx = 10, pady = 10)