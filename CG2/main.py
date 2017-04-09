import tkinter as tk
from tkinter import messagebox
import math

def create_pixel(master, x1, y1):
    master.canvas.create_line(x1, y1, x1+1, y1+1)
    #master.canvas.create_rectangle(x1, y1, x1+1, y1+1, outline='black')

    
def create_line(master, x1, y1, x2, y2):

    dx = round(x2) - round(x1)
    dy = round(y2) - round(y1)
    
    error_x = 0
    error_y = 0

    if dx > 0:
        kx = 1
    elif dx == 0:
        kx = 0
    else:
        kx = -1

    if dy > 0:
        ky = 1
    elif dy == 0:
        ky = 0
    else:
        ky = -1

    dx = abs(dx)
    dy = abs(dy)

    if dy > dx:
        d = dy
    else:
        d = dx

    curr_x = round(x1)
    curr_y = round(y1)
    create_pixel(master, curr_x, curr_y)
    
    while (curr_x != round(x2)) or (curr_y != round(y2)):
        error_x += dx
        error_y += dy
        if error_x >= d:
            error_x -= d
            curr_x += kx
        if error_y >= d:
            error_y -=d
            curr_y += ky
            
        create_pixel(master, curr_x, curr_y)

'''
def create_line(master, x1, y1, x2, y2):

    
    dx = (x2 - x1)
    dy = (y2 - y1)
    if dx == 0 and dy == 0:
        return

    if math.fabs(dy) < math.fabs(dx):
        x = 0
        k = dy / dx

        k2 = 1
        if dx < 0:
            k2 = -1
            
        while math.fabs(x) <= math.fabs(dx):
            create_pixel(master, round(x1 + x), round(y1 + k * x))
            x += k2
    else:
        y = 0
        k = dx / dy

        k2 = 1
        if dy < 0:
            k2 = -1
         
        while math.fabs(y) <= math.fabs(dy):
            create_pixel(master, round(x1 + k * y), round(y1 + y))
            y += k2

'''

class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

class Line:
    def __init__(self, p1, p2):
        self.p1 = p1
        self.p2 = p2

class Storage:
    def __init__(self):
        self.lines = []
        self.arc = []
        self.prev_lines = []
        self.prev_arc = []

        
class Main:
    def __init__(self, master):
        self.master = master
        self.master.geometry('920x600')
        self.master.title('Задание 2')

        self.data = Storage()

        self.pic = tk.Frame(self.master)
        self.utils = tk.Frame(self.master, width = 200)

        self.canvas = tk.Canvas(self.pic, background = 'white')

        self.labelShift = tk.Label(self.utils, text = 'Перенос:', width = 20)
        self.labelShiftX = tk.Label(self.utils, text = 'X:')
        self.labelShiftY = tk.Label(self.utils, text = 'Y:')
        self.shiftX = tk.Entry(self.utils, width = 10)
        self.shiftX.insert(0, '0.0')
        self.shiftY = tk.Entry(self.utils, width = 10)
        self.shiftY.insert(0, '0.0')
        self.btnShift = tk.Button(self.utils, text = 'Применить', width = 20, command=self.shift)

        self.labelRot = tk.Label(self.utils, text = 'Поворот:', width = 20)
        self.labelRotX = tk.Label(self.utils, text = 'Xc:')
        self.labelRotY = tk.Label(self.utils, text = 'Yc:')
        self.rotX = tk.Entry(self.utils, width = 10)
        self.rotY = tk.Entry(self.utils, width = 10)
        self.labelRotDeg = tk.Label(self.utils, text = 'Угол:')
        self.rotDeg = tk.Entry(self.utils, width = 10)
        self.btnRot = tk.Button(self.utils, text = 'Применить', width = 20, command=self.rotate)

        self.labelMast = tk.Label(self.utils, text = 'Масштабирование:', width = 20)
        self.labelMastX = tk.Label(self.utils, text = 'Xc:')
        self.labelMastY = tk.Label(self.utils, text = 'Yc:')
        self.mastX = tk.Entry(self.utils, width = 10)
        self.mastY = tk.Entry(self.utils, width = 10)
        self.labelMastKx = tk.Label(self.utils, text = 'Kx:')
        self.labelMastKy = tk.Label(self.utils, text = 'Ky:')
        self.mastKx = tk.Entry(self.utils, width = 10)
        self.mastKy = tk.Entry(self.utils, width = 10)
        self.btnMast = tk.Button(self.utils, text = 'Применить', width = 20,\
                          command=self.scale)

        self.btnRev = tk.Button(self.utils, text = 'Откатить операцию', width = 20, command=self.rev_draw)
        self.btnFRev = tk.Button(self.utils, text = 'Исходная позиция', width = 20, command=self.init_data)

        self.btnQuit = tk.Button(self.utils, text = 'Выйти', width = 20, command = self.quit)


        self.pic.place(relwidth = 0.75, relheight = 1.0);
        self.canvas.place(relheight = 1.0, relwidth = 1.0)

        
        wid, hei = self.get_sizes()
        self.rotX.insert(0, str(wid/2))
        self.rotY.insert(0, str(hei/2))
        self.mastX.insert(0, str(wid/2))
        self.mastY.insert(0, str(hei/2))
        self.mastKx.insert(0, '1.0')
        self.mastKy.insert(0, '1.0')
        self.rotDeg.insert(0, '0.0')
        
        self.utils.place(relwidth = 0.25, relx = 0.75, relheight = 1.0)

        self.labelShift.grid(row=0, sticky='n', columnspan=5, padx=5, pady=5)
        self.labelShiftX.grid(row=1, sticky='w', padx=5)
        self.labelShiftY.grid(row=1, column=3, sticky='w', padx=5)
        self.shiftX.grid(row=1, column=2, sticky='w', padx=5)
        self.shiftY.grid(row=1, column=4, sticky='w', padx=5)
        self.btnShift.grid(row=2, column=2, columnspan=3, sticky='n', padx=5, pady=5)

        self.labelRot.grid(row=3, sticky='n', columnspan=5, padx=5)
        self.labelRotX.grid(row=4, sticky='w', padx=5)
        self.labelRotY.grid(row=4, column=3, sticky='w', padx=5)
        self.rotX.grid(row=4, column=2, sticky='w', padx=5)
        self.rotY.grid(row=4, column=4, sticky='w', padx=5)
        self.labelRotDeg.grid(row=5, sticky='w', padx=5, pady=5)
        self.rotDeg.grid(row=5,column=2, sticky='w', padx=5)
        self.btnRot.grid(row=6, column=2, columnspan=3, sticky='n', padx=5, pady=5)

        self.labelMast.grid(row=7, sticky='n', columnspan=5, padx=5)
        self.labelMastX.grid(row=8, sticky='w', padx=5)
        self.labelMastY.grid(row=8, column=3, sticky='w', padx=5)
        self.mastX.grid(row=8, column=2, sticky='w', padx=5)
        self.mastY.grid(row=8, column=4, sticky='w', padx=5)
        self.labelMastKx.grid(row=9, sticky='w', padx=5, pady=5)
        self.labelMastKy.grid(row=9, column=3, sticky='w', padx=5, pady=5)
        self.mastKx.grid(row=9,column=2, sticky='w', padx=5)
        self.mastKy.grid(row=9,column=4, sticky='w', padx=5)
        self.btnMast.grid(row=10, column=2, columnspan=3, sticky='n', padx=5, pady=5)

        tk.Label(self.utils).grid(row=11, rowspan=4)
        tk.Label(self.utils).grid(row=17, rowspan=4)

        self.btnRev.grid(row=15, column=1, columnspan=5, sticky='n', padx=5, pady=5)
        self.btnFRev.grid(row=16, column=1, columnspan=5, sticky='n', padx=5, pady=5)
        self.btnQuit.grid(row=21, column=1, columnspan=5, sticky='n', padx=5, pady=5)

        self.init_coordinates()
        self.init_data()
            

    def get_sizes(self):
        self.canvas.update()
        return self.canvas.winfo_width(), self.canvas.winfo_height()
    

    def init_coordinates(self):
        self.size_x, self.size_y  = self.get_sizes()
        self.rel_c = self.size_x / 100
        
        
    def init_data(self):

        p1 = Point(self.size_x / 4, self.size_y / 2)
        p4 = Point(self.size_x / 4, self.size_y / 2)
        p2 = Point(p1.x + 25 * self.rel_c, p1.y + 12.5 * self.rel_c)
        p3 = Point(p4.x + 25 * self.rel_c, p1.y - 12.5 * self.rel_c)

        dash = []
        dash.append(Point(p1.x + 2.5 * self.rel_c, p1.y - 1.25 * self.rel_c))
        dash.append(Point(p1.x + 7.5 * self.rel_c, p1.y + 3.75 * self.rel_c))
        
        dash.append(Point(p1.x + 5 * self.rel_c, p1.y - 2.5 * self.rel_c))
        dash.append(Point(p1.x + 15 * self.rel_c, p1.y + 7.5 * self.rel_c))
        
        dash.append(Point(p1.x + 7.5 * self.rel_c, p1.y - 3.75 * self.rel_c))
        dash.append(Point(p1.x + 22.5 * self.rel_c, p1.y + 11.25 * self.rel_c))
        
        dash.append(Point(p1.x + 10 * self.rel_c, p1.y - 5 * self.rel_c))
        dash.append(Point(p1.x + 27 * self.rel_c, p1.y + 12 * self.rel_c))
        
        dash.append(Point(p1.x + 12.5 * self.rel_c, p1.y - 6.25 * self.rel_c))
        dash.append(Point(p1.x + 28.75 * self.rel_c, p1.y + 10 * self.rel_c))

        dash.append(Point(p1.x + 15 * self.rel_c, p1.y - 7.5 * self.rel_c))
        dash.append(Point(p1.x + 30 * self.rel_c, p1.y + 7.5 * self.rel_c))

        dash.append(Point(p1.x + 17.5 * self.rel_c, p1.y - 8.75 * self.rel_c))
        dash.append(Point(p1.x + 30.75 * self.rel_c, p1.y + 4.65 * self.rel_c))

        dash.append(Point(p1.x + 20 * self.rel_c, p1.y - 10 * self.rel_c))
        dash.append(Point(p1.x + 31.25 * self.rel_c, p1.y + 1.25 * self.rel_c))

        dash.append(Point(p1.x + 22.5 * self.rel_c, p1.y - 11.25 * self.rel_c))
        dash.append(Point(p1.x + 31.1 * self.rel_c, p1.y - 2.65 * self.rel_c))
        
        dash.append(Point(p1.x + 25 * self.rel_c, p1.y - 12.5 * self.rel_c))
        dash.append(Point(p1.x + 30 * self.rel_c, p1.y - 7.5 * self.rel_c))

        l1 = Line(p1, p2)
        l2 = Line(p4, p3)

        lt = Point(p2.x-6.25*self.rel_c, p2.y)
        rb = Point(p3.x+6.25*self.rel_c, p3.y)
        
        self.data.arc = poly_arc(lt.x, lt.y, rb.x, rb.y)
        self.data.lines.clear()
        self.data.lines.append(l1)
        self.data.lines.append(l2)

        i = 0
        while i < len(dash):
            self.data.lines.append(Line(dash[i], dash[i+1]))
            i += 2

        self.data.prev_lines = self.data.lines
        self.data.prev_arc = self.data.arc

        self.draw()
        

    def draw(self):

        width, height = self.get_sizes()

        self.canvas.delete('all')

        p1 = self.data.lines[0].p1
        p2 = self.data.lines[0].p2
        p3 = self.data.lines[1].p2

        self.canvas.create_text(p1.x, height - p1.y + 5, text = 'X= %.2f Y= %.2f' % (p1.x,\
                                p1.y))
        self.canvas.create_text(p2.x, height - p2.y + 5, text = 'X= %.2f Y= %.2f' % (p2.x,\
                                p2.y))
        self.canvas.create_text(p3.x, height - p3.y + 5, text = 'X= %.2f Y= %.2f' % (p3.x,\
                                p3.y))
        
        for line in self.data.lines:
            p1, p2 = line.p1, line.p2
            #self.canvas.create_line(p1.x, height - p1.y, p2.x, height - p2.y)
            create_line(self, p1.x, height - p1.y, p2.x, height - p2.y)
    
        for i in range(len(self.data.arc) - 1):
            #self.canvas.create_line(self.data.arc[i].x, height - self.data.arc[i].y, \
            #                       self.data.arc[i+1].x, height - self.data.arc[i+1].y)
            create_line(self, self.data.arc[i].x, height - self.data.arc[i].y, \
                                  self.data.arc[i+1].x, height - self.data.arc[i+1].y)

    
            
        
    def rev_draw(self):
        
        self.data.prev_lines, self.data.lines = self.data.lines, self.data.prev_lines
        self.data.prev_arc, self.data.arc = self.data.arc, self.data.prev_arc
        self.draw()

    def shift(self):
        try:
            dx = float(self.shiftX.get())
            dy = float(self.shiftY.get())
        except ValueError:
            messagebox.showinfo('Ошибка', 'Введите корректные данные!')
            return

        self.data.prev_lines = []
        self.data.prev_arc = []
        for line in tuple(self.data.lines):
            p1 = Point(line.p1.x, line.p1.y)
            p2 = Point(line.p2.x, line.p2.y)
            self.data.prev_lines.append(Line(p1, p2))
        for p in tuple(self.data.arc):
            self.data.prev_arc.append(Point(p.x, p.y))
        
        for line in self.data.lines:
            line.p1.x += dx
            line.p1.y += dy
            line.p2.x += dx
            line.p2.y += dy
        for point in self.data.arc:
            point.x += dx
            point.y += dy
        self.draw()

    def rotate(self):
        try:
            xc = float(self.rotX.get())
            yc = float(self.rotY.get())
            
            deg = math.pi / 180 * float(self.rotDeg.get())
        except ValueError:
            messagebox.showinfo('Ошибка', 'Введите корректные данные!')
            return

        self.data.prev_lines = []
        self.data.prev_arc = []
        for line in tuple(self.data.lines):
            p1 = Point(line.p1.x, line.p1.y)
            p2 = Point(line.p2.x, line.p2.y)
            self.data.prev_lines.append(Line(p1, p2))
        for p in tuple(self.data.arc):
            self.data.prev_arc.append(Point(p.x, p.y))

        cos = math.cos(deg)
        sin = math.sin(deg)
        
        for line in self.data.lines:
            x1 = xc + (line.p1.x - xc) * cos - (line.p1.y - yc) * sin
            y1 = yc + (line.p1.y - yc) * cos + (line.p1.x - xc) * sin
            x2 = xc + (line.p2.x - xc) * cos - (line.p2.y - yc) * sin
            y2 = yc + (line.p2.y - yc) * cos + (line.p2.x - xc) * sin
            p1 = Point(x1, y1)
            p2 = Point(x2, y2)
            line.p1 = p1
            line.p2 = p2
        for p in self.data.arc:
            x1 = xc + (p.x - xc) * cos - (p.y - yc) * sin
            y1 = yc + (p.y - yc) * cos + (p.x - xc) * sin
            p.x = x1
            p.y = y1
        self.draw()

    def scale(self):

        try:
            xc = float(self.mastX.get())
            yc = float(self.mastY.get())
            kx = float(self.mastKx.get())
            ky = float(self.mastKy.get())
            
        except ValueError:
            messagebox.showinfo('Ошибка', 'Введите корректные данные!')
            return

        self.data.prev_lines = []
        self.data.prev_arc = []
        for line in tuple(self.data.lines):
            p1 = Point(line.p1.x, line.p1.y)
            p2 = Point(line.p2.x, line.p2.y)
            self.data.prev_lines.append(Line(p1, p2))
        for p in tuple(self.data.arc):
            self.data.prev_arc.append(Point(p.x, p.y))

        for line in self.data.lines:
            line.p1.x = self.mast_op(line.p1.x, xc, kx)
            line.p2.x = self.mast_op(line.p2.x, xc, kx)
            line.p1.y = self.mast_op(line.p1.y, yc, ky)
            line.p2.y = self.mast_op(line.p2.y, yc, ky)

        for p in self.data.arc:
            p.x = self.mast_op(p.x, xc, kx)
            p.y = self.mast_op(p.y, yc, ky)

        self.draw()
        

    def mast_op(self, q, qc, kq):
        return kq * q + qc * (1 - kq)

    def quit(self):
        self.master.destroy()
   
def poly_arc(x0,y0, x1,y1, steps=720, rotation=0):

    a = (x1 - x0) / 2.0
    b = (y1 - y0) / 2.0

    xc = x0 + a
    yc = y0 + b

    point_list = []

    for i in range(steps):
        theta = math.pi * (float(i) / steps) - math.pi / 2

        x1 = a * math.cos(theta)
        y1 = b * math.sin(theta)

        x = (x1 * math.cos(rotation)) + (y1 * math.sin(rotation))
        y = (y1 * math.cos(rotation)) - (x1 * math.sin(rotation))

        point_list.append(Point(round(x + xc),round(y + yc)))

    return point_list


def main():
    root = tk.Tk()
    app = Main(root)
    root.mainloop()

if __name__ == '__main__':
    main()
