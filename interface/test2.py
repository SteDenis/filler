from tkinter import filedialog
import tkinter as tk
from tkinter.ttk import Frame, Button, Style
import subprocess
import os, sys, time
import re
cwd = os.getcwd()

class Player:
    def __init__(self, name):
        self.name = name
        self.file = None
        self.score = 0

    def generate_label_text(self):
        return self.name + ': ' + str(self.score)

class Map:
    def __init__(self, file):
        self.name = file.split('/')[-1]
        self.file = file
        self.map = []
        self.map_y = 0
        self.map_x = 0
        self.w = 0
        self.get_map()

    def get_map(self):
        with open(self.file) as fp:
            for cnt, line in enumerate(fp):
                self.map.append(line.split("\n")[0])
                self.map_x = len(line.split("\n")[0])
                self.map_y = cnt
        self.w = 580 / self.map_x

class Interface(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Filler Interface")
        self.geometry("1000x750")
        self.vm = ""
        self.p1 = None
        self.p2 = None
        self.map = None
        self.style = Style()
        self.style.theme_use("clam")

        top = tk.Frame(self, width="1000", height="200", bg="alice blue", pady=10, padx=20)
        top.pack(fill=tk.X, side=tk.TOP)
        top.columnconfigure(0, weight=1)
        top.columnconfigure(1, weight=1)
        win = tk.Frame(self, width="1000", bg="alice blue", padx=20)
        win.pack(fill=tk.X, side=tk.TOP)

        photo = tk.PhotoImage(file='logo.gif')
        label = tk.Label(top, image=photo)
        label.image = photo
        label.grid(row=0, column=0, sticky=tk.W)

        self.top2 = tk.LabelFrame(top, width="300", text="Game stats", bg="alice blue", padx = 50, pady = 10)
        self.top2.grid(row=0, column=1, sticky=tk.E)
        txt5 = tk.Label(self.top2, text="Players Scores :", font=('calibri', 12), bg="alice blue", fg="black", pady=5)
        txt5.grid(row=0, column=0)

        self.right = tk.LabelFrame(win, text="Files", bg="alice blue", padx = 10, pady = 10)
        self.right.grid(row=0, column=0, sticky=tk.W+tk.N)
        frame = tk.Frame(win, relief="groove", borderwidth=2, bg="snow")
        frame.grid(row=0, column=1, sticky=tk.E)
        self.canvas = tk.Canvas(frame, width=580, height=600)
        self.canvas.grid(row=0)

        txt1 = tk.Label(self.right, width="30",text="Filler vm :", font=('calibri', 12), bg="alice blue", fg="black", pady=5, anchor='w')
        txt1.grid(row=0, column=0)
        self.bb = Button(self.right, text="Browse", command=self.browsevm)
        self.bb.grid(row=1, column=0, sticky=tk.E)

        txt2 = tk.Label(self.right, text="Player 1 :", font=('calibri', 12), bg="alice blue", fg="black", pady=5)
        txt2.grid(row=2, column=0, sticky=tk.W)
        self.bbp1 = Button(self.right, text="Browse", command=self.browsep1)
        self.bbp1.grid(row=3, column=0, sticky=tk.E)

        txt3 = tk.Label(self.right, text="Player 2 :", font=('calibri', 12), bg="alice blue", fg="black", pady=5, anchor='w')
        txt3.grid(row=4, column=0, sticky=tk.W)
        self.bbp2 = Button(self.right, text="Browse", command=self.browsep2)
        self.bbp2.grid(row=5, column=0, sticky=tk.E)

        txt4 = tk.Label(self.right, text="Map :", font=('calibri', 12), bg="alice blue", fg="black", pady=5, anchor='w')
        txt4.grid(row=6, column=0, sticky=tk.W)
        self.bbm = Button(self.right, text="Browse", command=self.browsemap)
        self.bbm.grid(row=7, column=0, sticky=tk.E)

        self.ll = Button(self.right, text="Launch", command=self.launch_game)
        self.ll.grid(row=8, column=0, sticky=tk.E)

        self.colour_schemes = [{"bg": "lightgrey", "fg": "black"}, {"bg": "grey", "fg": "white"}]

    def launch_game(self):
        exe = [self.vm, "-f", self.map.file, "-p1", self.p1.file, "-p2", self.p2.file]
        p = subprocess.Popen(exe, stdout=subprocess.PIPE)
        sys.stdout.flush()
        self.readstd(p)

    def readstd(self, p):
        for line in iter(p.stdout.readline, b''):
            arr = []
            sys.stdout.flush()
            #line = p.stdout.readline()
            while re.match(r'^0', line.decode('utf-8')):
                arr.append(line.decode('utf-8').split(" ")[1].split("\n")[0])
                line = p.stdout.readline()
            if len(arr) > 0:
                self.updatemap(arr)
            del arr

    def updatemap(self, arr):
        x,y = 0,0
        for i, row in enumerate(arr):
            for j, col in enumerate(row):
                if col == 'x' or col == 'X':
                    self.canvas.itemconfig(self.tab[i][j], fill='red')
                elif col == 'o' or col == 'O':
                    self.canvas.itemconfig(self.tab[i][j], fill='green')
                else:
                    self.canvas.itemconfig(self.tab[i][j], fill='blue')
                x = x + self.map.w  # move right
            y = y + self.map.w # move down
            x = 0
        self.canvas.update()

    def browsevm(self):
        file = filedialog.askopenfilename(initialdir = cwd,title = "Select VM File",filetypes = (("filler vm","filler_vm*"),("all files","*.*")))
        if file:
            self.vm = file
            self.bb.config(text=self.vm.split("/")[-1])

    def browsep1(self):
        file = filedialog.askopenfilename(initialdir = cwd,title = "Select Player 1",filetypes = (("player file","*.filler"),("all files","*.*")))
        if file:
            self.p1 = Player(file.split('/')[-1].split('.filler')[0])
            self.p1.file = file
            self.bbp1.config(text=self.p1.name)

    def browsep2(self):
        file = filedialog.askopenfilename(initialdir = cwd,title = "Select Player 2",filetypes = (("player file","*.filler"),("all files","*.*")))
        if file:
            self.p2 = Player(file.split('/')[-1].split('.filler')[0])
            self.p2.file = file
            self.bbp2.config(text=self.p2.name)

    def browsemap(self):
        file = filedialog.askopenfilename(initialdir = cwd,title = "Select Map",filetypes = (("map file","map*"),("all files","*.*")))
        if file:
            self.map = Map(file)
            self.map.name = self.map.file.split("/")[-1]
            self.bbm.config(text=self.map.name)
            self.tab = [[0 for x in range(self.map.map_x + 1)] for y in range(self.map.map_y + 1)]
            self.init_map()

    def init_map(self):
        x,y = 0,0
        for i, row in enumerate(self.map.map):
            for j, col in enumerate(row):
                if col == 'X':
                    self.tab[i][j] = self.canvas.create_rectangle(x, y, x + self.map.w, y + self.map.w, fill='red')
                elif col == 'O':
                    self.tab[i][j] = self.canvas.create_rectangle(x, y, x + self.map.w, y + self.map.w, fill='green')
                else:
                    self.tab[i][j] = self.canvas.create_rectangle(x, y, x + self.map.w, y + self.map.w, fill='blue')
                x = x + self.map.w  # move right
            y = y + self.map.w # move down
            x = 0

if __name__ == "__main__":
    inter = Interface()
inter.config(background="alice blue")
inter.mainloop()