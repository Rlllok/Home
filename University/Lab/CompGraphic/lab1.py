import tkinter
from math import floor
from time import perf_counter

class my_name_drawing:

    H = ((10, 10, 10, 30), (10, 20, 20, 20), (20, 10, 20, 30))
    O = ((4, 30, 25),)
    B = ((40, 20, 40, 30), (40, 20, 45, 20), (45, 21, 45, 25), (40, 25, 45, 25), (45, 26, 45, 30), (40, 30, 45, 30))
    I = ((50, 20, 50, 30), (50, 17, 50, 18))
    K = ((55, 20, 55, 30), (55, 25, 60, 20), (55, 25, 60, 30))
    O2 = ((4, 68, 25),)
    B2 = ((75, 20, 75, 30), (75, 20, 80, 20), (80, 21, 80, 25), (75, 25, 80, 25), (80, 26, 80, 30), (75, 30, 80, 30))

    last_name = (H, O, B, I, K, O2, B2)

    def __init__(self, pixel_size = 1):
        self.pixel_size = pixel_size
        self.window = tkinter.Tk()
        self.canvas = tkinter.Canvas(self.window, width = 800, height = 600, bg = "white")
        self.canvas.pack()

        self.frame = tkinter.Frame(self.window, bg = "white")
        self.frame.pack()

        btn = tkinter.Button(self.frame, text = "Bresenham", command = lambda: self.draw_bresenham())
        btn.grid(row = 1, column = 1)
        btn = tkinter.Button(self.frame, text = "Wu", command = lambda: self.draw_wu())
        btn.grid(row = 1, column = 2)
        btn = tkinter.Button(self.frame, text = "DDA", command = lambda: self.draw_dda())
        btn.grid(row = 1, column = 3)
        btn = tkinter.Button(self.frame, text = "Clear", command = lambda: self.canvas.delete("all"))
        btn.grid(row = 1, column = 6)

        self.window.mainloop()

    def draw_pixel(self, x, y, alpha = 1):
        self.canvas.create_rectangle(self.pixel_size * x, self.pixel_size * y,
                                self.pixel_size * x + self.pixel_size, self.pixel_size * y + self.pixel_size,
                                fill = "#%02x%02x%02x" % (255 - round(255 * alpha), round(255 - 255 * alpha), round(255 - 255 * alpha)), 
                                outline = "#%02x%02x%02x" % (round(255 - 255 * alpha), round(255 - 255 * alpha), round(255 - 255 * alpha)), tag = "rectangle",)

    def draw_bresenham(self):
        self.canvas.delete("all")
        start_time = perf_counter()
        for letter in self.last_name:
            for shape in letter:
                if len(shape) == 3:
                    self.bresenham_circle(*shape)
                else:
                    self.bresenham_line(*shape)
        end_time = perf_counter()
        self.canvas.create_text(100,550,fill="darkblue",font="Times 10 italic bold", text="TIME:" + str(end_time - start_time))

    def draw_wu(self):
        self.canvas.delete("all")
        start_time = perf_counter()
        for letter in self.last_name:
            for shape in letter:
                if len(shape) == 3:
                    self.bresenham_circle(*shape)
                else:
                    self.Wu_line(*shape)
        end_time = perf_counter()
        self.canvas.create_text(100,550,fill="darkblue",font="Times 10 italic bold", text="TIME:" + str(end_time - start_time))

    def draw_dda(self):
        self.canvas.delete("all")
        start_time = perf_counter()
        for letter in self.last_name:
            for shape in letter:
                if len(shape) == 3:
                    self.bresenham_circle(*shape)
                else:
                    self.dda_line(*shape)
        end_time = perf_counter()
        self.canvas.create_text(100,550,fill="darkblue",font="Times 10 italic bold", text="TIME:" + str(end_time - start_time))
        

    def bresenham_line(self, x0, y0, x1, y1):
        deltaX = abs(x1 - x0)
        deltaY = abs(y1 - y0)

        error = 0
        deltaErr = deltaY
        y = y0
        dirY = y1 - y0

        if dirY > 0:
            dirY = 1
        if dirY < 0:
            dirY = -1

        if x0 == x1:
            for y in range(y0, y1):
                self.draw_pixel(x0, y)
            return

        for x in range(x0, x1):
            self.draw_pixel(x, y)
            error += deltaErr
            if 2 * error >= deltaX:
                y += dirY
                error -= deltaX

    def bresenham_circle(self, r, x0, y0):
        x = 0
        y = r
        delta = 1 - 2 * r
        error = 0

        while y >= 0:
            self.draw_pixel(x0 + x, y0 + y)
            self.draw_pixel(x0 + x, y0 - y)
            self.draw_pixel(x0 - x, y0 + y)
            self.draw_pixel(x0 - x, y0 - y)

            error = 2 * (delta + y) - 1

            if delta < 0 and error <= 0:
                x += 1
                delta += 2 * x + 1
                continue

            if delta > 0 and error > 0:
                y -= 1
                delta -= 2 * y + 1
                continue

            x += 1
            delta += 2 * (x - y)
            y -= 1

    def dda_line(self, x0, y0, x1, y1):
        dx = abs(x1 - x0)
        dy = abs(y1 - y0)
        steps = dx if dx >= dy else dy
        dx = (x1 - x0) / steps
        dy = (y1 - y0) / steps

        x, y = x0, y0
        self.draw_pixel(x, y)
        for i in range(steps - 1):
            x += dx
            y += dy
            self.draw_pixel(x, y)

    def Wu_line(self, x0, y0, x1, y1):
        # if y0 == y1:
        #     self.bresenham_line(x0, y0, x1, y1)
        #     return None
        def round(x):
            return floor(x + 0.5)

        def fpart(x):
            return x - floor(x)

        def rfpart(x):
            return 1 - fpart(x)

        steep = abs(y1 - y0) > abs(x1 - x0)

        if steep:
            x0, y0 = y0, x0
            x1, y1 = y1, x1

        if x1 < x0:
            x0, x1 = x1, x0
            y0, y1 = y1, y0

        delta_x = x1 - x0
        delta_y = y1 - y0
        
        if delta_x == 0:
            gradient = 1
        else:
            gradient = delta_y / delta_x

        end_x = round(x0)
        end_y = y0 + gradient * (end_x - x0)
        x_gap = rfpart(x0 + 0.5)
        xpxl1 = end_x
        ypxl1 = floor(end_y)

        if steep:
            self.draw_pixel(ypxl1, xpxl1, rfpart(end_y) * x_gap)
            self.draw_pixel(ypxl1, xpxl1, fpart(end_y) * x_gap)
        else:
            self.draw_pixel(xpxl1, ypxl1, rfpart(end_y) * x_gap)
            self.draw_pixel(xpxl1, ypxl1, fpart(end_y) * x_gap)
        
        intery = end_y + gradient

        end_x = round(x1)
        end_y = y1 + gradient * (end_x - x1)
        x_gap = fpart(x1 + 0.5)
        xpxl2 = end_x
        ypxl2 = floor(end_y)

        if steep:
            self.draw_pixel(ypxl2, xpxl2, rfpart(end_y) * x_gap)
            self.draw_pixel(ypxl2, xpxl2, fpart(end_y) * x_gap)
        else:
            self.draw_pixel(xpxl2, ypxl2, rfpart(end_y) * x_gap)
            self.draw_pixel(xpxl2, ypxl2, fpart(end_y) * x_gap)

        if steep:
            for x in range(xpxl1, xpxl2):
                self.draw_pixel(floor(intery), x, rfpart(intery))
                self.draw_pixel(floor(intery) + 1, x, fpart(intery))
                intery = intery + gradient
        else:
            for x in range(xpxl1, xpxl2):
                self.draw_pixel(x, floor(intery), rfpart(intery))
                self.draw_pixel(x, floor(intery) + 1, fpart(intery))
                intery = intery + gradient 


if __name__ == "__main__":
    my_name_drawing(1)