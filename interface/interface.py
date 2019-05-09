from tkinter import *

class Interface(Frame):

    def __init__(self, fenetre, **kwargs):
        Frame.__init__(self, fenetre, width=768, height=576, **kwargs)
        self.pack(fill=BOTH)

        self.grid = [ [-1]*8  for n in range(8)] # list comprehension
        self.canvas = Canvas(self, width=550, height=820)
        self.canvas.pack()
        self.w = 50 # width of each cell
        self.draw()
        self.bouton_cliquer = Button(self, text="Cliquez ici", fg="red",
                                     command=self.cliquer)
        self.bouton_cliquer.pack(side="right")

    def draw(self):
        x,y = 50,20
        for row in self.grid:
            for col in row:
                if col == 1:
                    self.canvas.create_rectangle(x, y, x + self.w, y + self.w, fill='red')
                else:
                    self.canvas.create_rectangle(x, y, x + self.w, y + self.w, fill='blue')
                x = x + self.w  # move right
            y = y + self.w # move down
            x = 50 # rest to left edge
    def cliquer(self):
        self.canvas.itemconfig(self.grid[0][0], fill='blue')



fenetre = Tk()
interface = Interface(fenetre)

interface.mainloop()
interface.destroy()