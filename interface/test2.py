from tkinter import filedialog
from tkinter.messagebox import showerror
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

class Map:
    def __init__(self, file):
        self.name = file.split('/')[-1]
        self.file = file
        self.map = []
        self.map_y = 0
        self.map_x = 0
        self.w = 0
        self.y = 0
        self.get_map()

    def get_map(self):
        valid = r".Ox"
        with open(self.file) as fp:
            for cnt, line in enumerate(fp):
                if not any(st in line for st in valid):
                    self.invalid_map()
                    break
                if self.map_x > 0:
                    if len(line.split("\n")[0]) != self.map_x:
                        self.invalid_map()
                        break
                self.map.append(line.split("\n")[0])
                self.map_x = len(line.split("\n")[0])
                self.map_y = cnt
        if self.map_x > 0 and self.map_y > 0:
            self.w = 580 / self.map_x
            self.y = 630 / self.map_y

    def invalid_map(self):
        showerror("Map error", "Invalid map")
        del self.map
        self.map = []
        self.map_x = 0
        self.map_y = 0

class Interface(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Filler Interface")
        self.geometry("978x825")
        self.resizable(False, False)
        self.vm = ""
        self.p1 = None
        self.p2 = None
        self.map = None
        self.style = Style()
        self.p = None
        self.style.theme_use("classic")
        self.style.map("C.TButton",
                       foreground=[('pressed', 'white'), ('active', 'white')],
                       background=[('pressed', '!disabled', 'DodgerBlue4'), ('active', 'DodgerBlue4')]
                       )
        self.style.configure("C.TButton", justify="LEFT", font=('calibri', 15), bd=0, highlightthickness=0, relief="flat", foreground="white", background="DodgerBlue4")

        top = tk.Frame(self, width="1000", height="800", bg="SlateGray4", bd=0, highlightthickness=0)
        top.pack(fill=tk.X, side=tk.TOP)
        photo = tk.PhotoImage(file='interface.gif')
        label = tk.Label(top, image=photo)
        label.image = photo
        label.grid(row=0, column=0)

        self.sc1 = tk.Label(top, width=20, text="", font=('calibri', 16), bg="SteelBlue4", fg="white", pady=5, anchor='w')
        self.sc1.place(x=430, y=45)
        self.sc2 = tk.Label(top, width=20, text="", font=('calibri', 16), bg="SteelBlue4", fg="black", pady=5, anchor='w')
        self.sc2.place(x=650, y=45)


        self.canvas = tk.Canvas(top, width=600, height=680, bg="alice blue", relief='ridge')
        self.canvas.place(x=25, y=120)
        self.bb = Button(top, width="13", text="Browse", command=self.browsevm, style="C.TButton")
        self.bb.place(x=775, y=178)
        self.bbp1 = Button(top, width="13", text="Browse", command=self.browsep1, style="C.TButton")
        self.bbp1.place(x=775, y=305)
        self.bbp2 = Button(top, width="13", text="Browse", command=self.browsep2, style="C.TButton")
        self.bbp2.place(x=775, y=366)
        self.bbm = Button(top, width="13", text="Browse", command=self.browsemap, style="C.TButton")
        self.bbm.place(x=775, y=240)

        self.st = Button(top, width="4", state="disabled", text="Start", command=self.launch_game, style="C.TButton")
        self.st.place(x=665, y=510)

        self.rt = Button(top, width="4", text="Reset", command=self.reset_game, style="C.TButton")
        self.rt.place(x=760, y=495)
        self.rt2 = Button(top, width="4", text="Stop", command=self.reset_game, style="C.TButton")
        self.rt2.place(x=762, y=523)

        self.qt = Button(top, width="4", text="Quit", command=self.quit, style="C.TButton")
        self.qt.place(x=855, y=510)

        self.colour_schemes = [{"bg": "lightgrey", "fg": "black"}, {"bg": "grey", "fg": "white"}]

    def launch_game(self):
        self.st.config(state="disabled")
        self.bb.config(state="disabled")
        self.bbm.config(state="disabled")
        self.bbp1.config(state="disabled")
        self.bbp2.config(state="disabled")
        exe = [self.vm, "-f", self.map.file, "-p1", self.p1.file, "-p2", self.p2.file]
        self.p = subprocess.Popen(exe, stdout=subprocess.PIPE)
        sys.stdout.flush()
        self.readstd()
        self.p = None
        self.st.config(state="normal")
        self.bb.config(state="normal")
        self.bbm.config(state="normal")
        self.bbp1.config(state="normal")
        self.bbp2.config(state="normal")

    def quit(self):
        self.destroy()
        sys.exit()

    def readstd(self):
        for line in iter(self.p.stdout.readline, b''):
            arr = []
            sys.stdout.flush()
            if "<got (X)" in line.decode('utf-8'):
                self.p2.score += 1
                self.sc2.config(text=self.p2.name + " " + str(self.p2.score))
            if "<got (O)" in line.decode('utf-8'):
                self.p1.score += 1
                self.sc1.config(text=self.p1.name + " " + str(self.p1.score))
            while re.match(r'^0', line.decode('utf-8')):
                arr.append(line.decode('utf-8').split(" ")[1].split("\n")[0])
                if self.p is not None:
                    line = self.p.stdout.readline()
                else:
                    break
            if len(arr) > 0:
                self.updatemap(arr)
            del arr
            if self.p is None:
                break

    def reset_game(self):
        if self.p is not None:
            self.p.kill()
            self.p = None
        else:
            self.del_map()
            del self.map
            del self.tab
            if self.p1 is not None:
                self.p1.score = 0
                self.sc1.config(text=self.p1.name + " " + str(self.p1.score))
            if self.p2 is not None:
                self.p2.score = 0
                self.sc2.config(text=self.p2.name + " " + str(self.p2.score))
            self.map = None
            self.st.config(state="disabled")
            self.bbm.config(text="Browse")
            self.canvas.update()

    def updatemap(self, arr):
        for i, row in enumerate(arr):
            for j, col in enumerate(row):
                if col == 'X':
                    self.canvas.itemconfig(self.tab[i][j], fill='SlateBlue4')
                elif col == 'O':
                    self.canvas.itemconfig(self.tab[i][j], fill='red3')
                elif col == 'x':
                    self.canvas.itemconfig(self.tab[i][j], fill='SlateBlue2')
                elif col == 'o':
                    self.canvas.itemconfig(self.tab[i][j], fill='tomato2')
                else:
                    self.canvas.itemconfig(self.tab[i][j], fill='azure')
        self.canvas.update()

    def check_state(self):
        if self.vm is not "" and self.map is not None and self.p1 is not None and self.p2 is not None:
            self.st.config(state="normal")

    def browsevm(self):
        file = filedialog.askopenfilename(initialdir = cwd, title = "Select VM File")
        if file:
            self.vm = file
            self.bb.config(text=self.vm.split("/")[-1])
            self.check_state()

    def browsep1(self):
        file = filedialog.askopenfilename(initialdir = cwd,title = "Select Player 1")
        if file:
            self.p1 = Player(file.split('/')[-1].split('.filler')[0])
            self.p1.file = file
            self.bbp1.config(text=self.p1.name)
            self.sc1.config(text=self.p1.name + " " + str(self.p1.score))
            self.check_state()

    def browsep2(self):
        file = filedialog.askopenfilename(initialdir = cwd,title = "Select Player 2")
        if file:
            self.p2 = Player(file.split('/')[-1].split('.filler')[0])
            self.p2.file = file
            self.bbp2.config(text=self.p2.name)
            self.sc2.config(text=self.p2.name + " " + str(self.p2.score))
            self.check_state()

    def browsemap(self):
        file = filedialog.askopenfilename(initialdir = cwd,title = "Select Map")
        if self.map is not None:
            self.del_map()
            del self.map
            del self.tab
            self.map = None
        if file:
            self.map = Map(file)
            if self.map.map_x == 0:
                del self.map
                self.map = None
            else:
                self.map.name = self.map.file.split("/")[-1]
                self.bbm.config(text=self.map.name)
                self.tab = [[None for x in range(self.map.map_x + 1)] for y in range(self.map.map_y + 1)]
                self.init_map()
                self.check_state()

    def del_map(self):
        x,y = 10,5
        for i, row in enumerate(self.map.map):
            for j, col in enumerate(row):
                self.canvas.delete(self.tab[i][j])
                x = x + self.map.w
            y = y + self.map.y
            x = 10

    def init_map(self):
        x,y = 10,5
        for i, row in enumerate(self.map.map):
            for j, col in enumerate(row):
                if col == 'X':
                    self.tab[i][j] = self.canvas.create_rectangle(x, y, x + self.map.w, y + self.map.y, fill='SlateBlue4')
                elif col == 'O':
                    self.tab[i][j] = self.canvas.create_rectangle(x, y, x + self.map.w, y + self.map.y, fill='red3')
                else:
                    self.tab[i][j] = self.canvas.create_rectangle(x, y, x + self.map.w, y + self.map.y, fill='azure')
                x = x + self.map.w
            y = y + self.map.y
            x = 10

if __name__ == "__main__":
    inter = Interface()
inter.config(background="SlateGray4")
inter.mainloop()