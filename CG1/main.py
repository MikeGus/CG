import tkinter as tk
from tkinter import messagebox
import math

FIRST_STORAGE = []
SECOND_STORAGE = []


class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

class Circle:
    def __init__(self, xc=0, yc=0, r=0):
        self.xc=xc
        self.yc=yc
        self.r=r

def is_line(p1, p2, p3):
    return (p1.x - p3.x) * (p2.y - p3.y) == (p2.x - p3.x) * (p1.y * p3.y)


def calculate_circle(p1, p2, p3):
    if is_line(p1, p2, p3):
        return None
    
    a = p2.x - p1.x
    b = p2.y - p1.y
    c = p3.x - p1.x
    d = p3.y - p1.y
    e = a * (p1.x + p2.x) + b * (p1.y + p2.y)
    f = c * (p1.x + p3.x) + d * (p1.y + p3.y)
    g = 2 * (a * (p3.y - p2.y) - b * (p3.x - p2.x))
    if g == 0:
        return None
    xc = (d * e - b * f) / g
    yc = (a * f - c * e) / g
    r = ((p1.x - xc) ** 2 + (p1.y - yc) ** 2) ** 0.5

    return Circle(xc, yc, r)
    
def calculate_area(c1, c2):

    distance = ((c1.xc-c2.xc)**2 + (c1.yc-c2.yc)**2)**0.5
    if (distance + c1.r < c2.r) or (distance + c2.r < c1.r):
        return 0
    
    if c1.r == c2.r:
        area = distance * c1.r
        return area

    dr = abs(c1.r - c2.r)
    fi = math.asin(dr / distance)
    
    lencas = distance * math.cos(fi)

    area = (min(c1.r, c2.r) + 0.5 * dr) * lencas

    return area

def get_coef(p1, p2):
    a = p2.y - p1.y
    b = p1.x - p2.x
    c = p2.x * p1.y - p1.x * p2.y

    return a, b, c

def get_k(a, b):
    if b == 0:
        return 'inf'
    
    return -a/b

def get_k_rev(k):
    if k == 0:
        return 'inf'
    
    return -1/k

def get_d(p, k):
    return p.y - k * p.x


def calculate_buf_point(c1, c2):
    
    distance = ((c1.xc-c2.xc)**2 + (c1.yc-c2.yc)**2)**0.5

    switched = 0

    if(c1.r > c2.r):
        switched = 1
        c1, c2 = c2, c1
    
    r2 = c2.r - c1.r
    r1 = (distance**2 - r2**2)**0.5

    K1 = (c2.xc - c1.xc)**2 + (r1**2 - r2**2) + (c2.yc**2 - c1.yc**2)
    K2 = 2 * (c1.yc - c2.yc)
    K3 = 2 * (c2.xc - c1.xc)
    K4 = K3**2 + K2**2
    K5 = 2 * K1 * K2 - 2 * c1.yc * K3**2
    K6 = K1**2 + K3**2 * (c1.yc**2 - r1**2)

    D = K5**2 - 4 * K4 * K6

    K7 = 1
    K8 = 1
    if c1.xc > c2.xc:
        K7 = -1
    if c1.yc < c2.yc:
        K8 = -1
        
    

    y0 = (-K5 + K8 * D**0.5) / 2 / K4
    x0 = c1.xc + K7 * (r1**2 - (c1.yc - y0)**2)**0.5
    
    if switched:
        c1, c2 = c2, c1

    return x0, y0
    
def calculate_points(c1, c2):

    if c1.r == c2.r:
        p1 = Point(c1.xc, c1.yc)
        p2 = Point(c2.xc, c2.yc)
        a1, b1, c = get_coef(p1, p2)

        k1 = get_k(a1, b1)
        
        if k1 == 'inf':
            res_1 = Point(c1.xc + c1.r, c1.yc)
            res_2 = Point(c2.xc + c2.r, c2.yc)
            
        elif k1 == 0:
            res_1 = Point(c1.xc, c1.yc + c1.r)
            res_2 = Point(c2.xc, c2.yc + c2.r)
            
        else:
            k2 = get_k_rev(k1)
            d1 = get_d(p1, k2)
            d2 = get_d(p2, k2)

            x_res_1, y_res_1 = findxy(c1, k2, d1)
            x_res_2, y_res_2 = findxy(c2, k2, d2)
            res_1 = Point(x_res_1, y_res_1)
            res_2 = Point(x_res_2, y_res_2)
            
        return res_1, res_2

    x0, y0 = calculate_buf_point(c1, c2)
    switched = 0
    if c1.r > c2.r:
        switched = 1
        c1, c2 = c2, c1
    dr = c2.r - c1.r

    x_res_1 = c1.xc + (x0 - c2.xc) * c1.r / dr
    x_res_2 = c2.xc + (x0 - c2.xc) * c2.r / dr

    y_res_1 = c1.yc + (y0 - c2.yc) * c1.r / dr
    y_res_2 = c2.yc + (y0 - c2.yc) * c2.r / dr

    res_1 = Point(x_res_1, y_res_1)
    res_2 = Point(x_res_2, y_res_2)

    if switched:
        c1, c2 = c2, c1
        res_1, res_2 = res_2, res_1
        
    return res_1, res_2
    

def findxy(c, k, d):
    a = k**2 + 1
    b = 2 * (k * (d - c.yc) - c.xc)
    c = c.xc**2 + (d - c.yc)**2 - c.r**2

    disk = b**2 - 4*a*c

    x = (-b + disk**0.5)/2/a

    y = k * x + d

    return x, y

def mast(q, qc, kq):
    return int(kq * q + qc * (1 - kq))
        
        

class SimpleTable(tk.Frame):
    def __init__(self, parent, rows=3, columns=2):
        tk.Frame.__init__(self, parent, background="black")
        self._widgets = []
        for row in range(rows):
            current_row = []
            for column in range(columns):
                entry = tk.Entry(self, borderwidth=0, width=10)
                entry.grid(row=row, column=column, sticky="nsew", padx=1, pady=1)
                current_row.append(entry)
            self._widgets.append(current_row)

        for column in range(columns):
            self.grid_columnconfigure(column, weight=1)


    def set(self, row, column, value):
        widget = self._widgets[row][column]
        widget.configure(text=value)
        widget.update()

    def get(self, row, column):
        widget = self._widgets[row][column]


class Main:
    def __init__(self, master):
        self.master = master
        self.master.geometry('800x600')
        self.master.title('Задание 1')
        self.master.bind("<Configure>", self.resize)
        self.pic = tk.Frame(self.master)
        self.utils = tk.Frame(self.master)

        st_1 = []
        st_2 = []
                
        self.max_area = 0.0
        self.max_f_circle = None
        self.max_s_circle = None

        self.btnInfo = tk.Button(self.utils, text = 'Информация', width = 20, \
                                 command = self.show_info)
        self.btnInfo.pack()
        self.btnSet = tk.Button(self.utils, text = 'Задать точки', width = 20, \
                                 command = self.set)
        self.btnSet.pack()
        self.btnDraw = tk.Button(self.utils, text = 'Рисовать', width = 20, \
                                 command = self.draw)
        self.btnDraw.pack()
        self.btnQuit = tk.Button(self.utils, text = 'Выйти', width = 20, \
                                 command = self.quit)
        self.btnQuit.pack()

        self.areaLabel = tk.Label(self.utils, text = 'Area = %.2f' % (self.max_area))
        self.areaLabel.pack(side = 'bottom')


        self.canvas = tk.Canvas(self.pic, bg='white')
        self.canvas.pack(expand='yes', fill='both')
        self.pic.place(relheight=1.0, relwidth=0.8)
        self.utils.place(relheight=1.0, relwidth=0.2, relx=0.8)

    def show_info(self):
        self.infoWindow = tk.Toplevel(self.master)
        self.app = Info(self.infoWindow)

    def set(self):
        self.setWindow = Set(tk.Toplevel(self.master))

    def get_sizes(self):
        self.canvas.update()
        return self.canvas.winfo_width(), self.canvas.winfo_height()

    def resize(self, event):
        if not (self.max_f_circle == None or self.max_s_circle == None):
            self.draw()

    def choose_points(self):

        self.max_area = 0.0
        self.max_f_circle = None
        self.max_s_circle = None
        
        global FIRST_STORAGE
        global SECOND_STORAGE

        len_f = len(FIRST_STORAGE)
        len_s = len(SECOND_STORAGE)
        if  len_f < 3 or len_s < 3:
            return None

        for i in range(len_f):
            for j in range(i + 1, len_f):
                for k in range(j + 1, len_f):
                    f_circle = calculate_circle(FIRST_STORAGE[i], FIRST_STORAGE[j], FIRST_STORAGE[k])
                    if f_circle != None:
                        for l in range(len_s):
                            for m in range(l + 1, len_s):
                                for n in range(m + 1, len_s):
                                    s_circle = calculate_circle(SECOND_STORAGE[l], SECOND_STORAGE[m], SECOND_STORAGE[n])
                                    if s_circle != None:
                                        area = calculate_area(f_circle, s_circle)
                                        if area > self.max_area:
                                            self.max_area = area
                                            self.max_f_circle = f_circle
                                            self.max_s_circle = s_circle


    def calculate_coordinates(self, c1, c2, p1, p2):

        lx_c1 = c1.xc - c1.r
        rx_c1 = c1.xc + c1.r
        ty_c1 = c1.yc + c1.r
        by_c1 = c1.yc - c1.r

        lx_c2 = c2.xc - c2.r
        rx_c2 = c2.xc + c2.r
        ty_c2 = c2.yc + c2.r
        by_c2 = c2.yc - c2.r

        lx = min(lx_c1, lx_c2)
        rx = max(rx_c1, rx_c2)

        ty = max(ty_c1, ty_c2)
        by = min(by_c1, by_c2)

        real_width = rx - lx
        real_height = ty - by

        fr_width, fr_height = self.get_sizes()

        k1 = real_width / (fr_width-100)
        k2 = real_height / (fr_height-100)

        center_x = fr_width / 2
        center_y = fr_height / 2

        real_center_x = real_width / 2 + lx
        real_center_y = real_height / 2 + by

        k = min(1/k1, 1/k2)

        lx_c1 = center_x + mast(lx_c1, real_center_x, k)
        lx_c2 = center_x + mast(lx_c2, real_center_x, k)
        rx_c1 = center_x + mast(rx_c1, real_center_x, k)
        rx_c2 = center_x + mast(rx_c2, real_center_x, k)

        ty_c1 = center_y + mast(ty_c1, real_center_y, -k)
        ty_c2 = center_y + mast(ty_c2, real_center_y, -k)
        by_c1 = center_y + mast(by_c1, real_center_y, -k)
        by_c2 = center_y + mast(by_c2, real_center_y, -k)

        pp1_x = center_x + mast(p1.x, real_center_x, k)
        pp2_x = center_x + mast(p2.x, real_center_x, k)
        pp1_y = center_y + mast(p1.y, real_center_y, -k)
        pp2_y = center_y + mast(p2.y, real_center_y, -k)

        cent_x_1 = center_x + mast(c1.xc, real_center_x, k)
        cent_x_2 = center_x + mast(c2.xc, real_center_x, k)

        cent_y_1 = center_y + mast(c1.yc, real_center_y, -k)
        cent_y_2 = center_y + mast(c2.yc, real_center_y, -k)
        
        ltc1 = Point(lx_c1, ty_c1)
        rbc1 = Point(rx_c1, by_c1)

        ltc2 = Point(lx_c2, ty_c2)
        rbc2 = Point(rx_c2, by_c2)

        pp1 = Point(pp1_x, pp1_y)
        pp2 = Point(pp2_x, pp2_y)

        cent_1 = Point(cent_x_1, cent_y_1)
        cent_2 = Point(cent_x_2, cent_y_2)
        

        return ltc1, rbc1, ltc2, rbc2, pp1, pp2, cent_1, cent_2 
        
        
    def draw(self):
        global FIRST_STORAGE
        global SECOND_STORAGE

        self.canvas.delete("all")        
        self.choose_points()

        if self.max_f_circle == None or self.max_s_circle == None:
            messagebox.showinfo("Ошибка", "Введите корректные точки!")
            self.max_area = 0.0
            return None
        
        p1, p2 = calculate_points(self.max_f_circle, self.max_s_circle)
          
        
        ltc1, rbc1, ltc2, rbc2, pp1, pp2, cent_1, cent_2\
              = self.calculate_coordinates(self.max_f_circle, self.max_s_circle, p1, p2)

        #self.canvas.update()
        self.canvas.create_oval(ltc1.x, ltc1.y, rbc1.x, rbc1.y, outline='red')
        self.canvas.create_oval(ltc2.x, ltc2.y, rbc2.x, rbc2.y, outline='blue')
        self.canvas.create_line(pp1.x, pp1.y, pp2.x, pp2.y)
        self.canvas.create_line(pp1.x, pp1.y, (ltc1.x+rbc1.x)/2, (ltc1.y+rbc1.y)/2)
        self.canvas.create_line(pp2.x, pp2.y, (ltc2.x+rbc2.x)/2, (ltc2.y+rbc2.y)/2)
        self.canvas.create_line((ltc1.x+rbc1.x)/2, (ltc1.y+rbc1.y)/2, (ltc2.x+rbc2.x)/2, (ltc2.y+rbc2.y)/2)

        self.canvas.create_text(cent_1.x, cent_1.y + 5, text = 'X= %.2f Y= %.2f' % (self.max_f_circle.xc,\
                                self.max_f_circle.yc))
        self.canvas.create_text(cent_2.x, cent_2.y + 5, text = 'X= %.2f Y= %.2f' % (self.max_s_circle.xc,\
                                self.max_s_circle.yc))
        self.canvas.create_text(pp1.x, pp1.y + 5, text = 'X= %.2f Y= %.2f' % (p1.x,\
                                p1.y))
        self.canvas.create_text(pp2.x, pp2.y + 5, text = 'X= %.2f Y= %.2f' % (p2.x,\
                                p2.y))
        self.areaLabel.configure(text = 'Area = %.2f' % (self.max_area))
        
               
        

    def quit(self):
        self.master.destroy()

class Info:
    def __init__(self, master):
        self.master = master
        self.master.title('Информация')
        self.text = tk.Text(self.master, width=60, wrap='word')
        self.text.insert(1.0, 'Задание:\nНа плоскости заданы два множества точек. Найти \
пару окружностей, каждая из которых проходит хотя бы через три различных точки \
одного и того же множества (точки берутся из разных множеств для разных окружностей),\
 для которых площадь четырехугольника, образованного центрами окружностей и \
 точками касания общей касательной, максимальна.')
        self.text.config(state='disabled')
        self.btnOk = tk.Button(self.master, text = 'Выйти', width = 25, \
                                  height=2,command = self.close_window)
        self.text.pack()
        self.btnOk.pack()

    def close_window(self):
        self.master.destroy()

class Set:
    def __init__(self, master):
        self.master = master
        self.master.title('Задайте точки')
        self.master.geometry('400x500')
        self.fl = tk.Frame(self.master)
        self.fr = tk.Frame(self.master)

        self.ll = tk.Label(self.fl, text='Первое множество')
        self.lr = tk.Label(self.fr, text='Второе множество')
        self.labLegL = tk.Label(self.fl, text='x\ty')
        self.labLegR = tk.Label(self.fr, text='x\ty')

        options = []
        
        for i in range(3, 16):
            options.append(i)
        self.first_num = tk.IntVar(self.master)

        global FIRST_STORAGE
        global SECOND_STORAGE

        defrows_1 = 3
        defrows_2 = 3
        if len(FIRST_STORAGE) > 3:
            self.first_num.set(len(FIRST_STORAGE))
            defrows_1 = len(FIRST_STORAGE)
        else:
            self.first_num.set(options[0])
        
        self.optionLeft = tk.OptionMenu(self.fl, self.first_num, *options, command=\
                                        self.change_table_left)
        self.second_num = tk.IntVar(self.master)

        if len(SECOND_STORAGE) > 3:
            self.second_num.set(len(SECOND_STORAGE))
            defrows_2 = len(SECOND_STORAGE)
        else:
            self.second_num.set(options[0])
            
        self.optionRight = tk.OptionMenu(self.fr, self.second_num, *options, command=\
                                         self.change_table_right)
        

        self.tableLeft = SimpleTable(self.fl, defrows_1)
        self.tableRight = SimpleTable(self.fr, defrows_2)
        
        for i in range(len(FIRST_STORAGE)):
            (self.tableLeft._widgets[i][0]).insert(0, str(FIRST_STORAGE[i].x))
            (self.tableLeft._widgets[i][1]).insert(0, str(FIRST_STORAGE[i].y))

        for i in range(len(SECOND_STORAGE)):
            (self.tableRight._widgets[i][0]).insert(0, str(SECOND_STORAGE[i].x))
            (self.tableRight._widgets[i][1]).insert(0, str(SECOND_STORAGE[i].y))
    
        
        self.btnQuit = tk.Button(self.master, text = 'Отмена', width = 25, \
                                  height=2,command = self.close_window)
        self.btnOk = tk.Button(self.master, text = 'ОК', width = 25, \
                                  height=2,command = self.get_data)
        self.ll.pack()
        self.optionLeft.pack()
        self.labLegL.pack()
        self.tableLeft.pack()
        self.fl.place(relheight=0.8, relwidth=0.5)
        
        
        self.lr.pack()
        self.optionRight.pack()
        self.labLegR.pack()
        self.tableRight.pack()
        self.fr.place(relheight=0.8, relwidth=0.5, relx=0.5)
        self.btnQuit.pack(side='bottom',fill='x')
        self.btnOk.pack(side='bottom',fill='x')
        

    def close_window(self):
        self.master.destroy()

    def change_table_left(self, value):
        self.tableLeft.destroy()
        self.tableLeft = SimpleTable(self.fl, rows=value)
        global FIRST_STORAGE
        
        for i in range(min(self.first_num.get(), len(FIRST_STORAGE))):
            (self.tableLeft._widgets[i][0]).insert(0, str(FIRST_STORAGE[i].x))
            (self.tableLeft._widgets[i][1]).insert(0, str(FIRST_STORAGE[i].y))

        self.tableLeft.pack()

    def change_table_right(self, value):
        self.tableRight.destroy()
        self.tableRight = SimpleTable(self.fr, rows=value)
        global SECOND_STORAGE

        for i in range(min(self.second_num.get(), len(SECOND_STORAGE))):
            (self.tableRight._widgets[i][0]).insert(0, str(SECOND_STORAGE[i].x))
            (self.tableRight._widgets[i][1]).insert(0, str(SECOND_STORAGE[i].y))
        self.tableRight.pack()

    def get_data(self):

        global FIRST_STORAGE
        global SECOND_STORAGE

        FIRST_STORAGE = []
        SECOND_STORAGE = []
        
        for rows in self.tableLeft._widgets:
            point = Point(rows[0].get(), rows[1].get())
            if (point.x and point.y):
                point.x = float(point.x)
                point.y = float(point.y)
                FIRST_STORAGE.append(point)
                

        for rows in self.tableRight._widgets:
            point = Point(rows[0].get(), rows[1].get())
            if (point.x and point.y):
                point.x = float(point.x)
                point.y = float(point.y)
                SECOND_STORAGE.append(point)

        self.master.destroy()

def main():
    root = tk.Tk()
    app = Main(root)
    root.mainloop()

if __name__ == '__main__':
    main()
