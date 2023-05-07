import tkinter as tk
import socket as sk
import time


class Pendant():
    def __init__(self):
        self._root = tk.Tk()
        self.socket = sk.socket(sk.AF_INET, sk.SOCK_STREAM)
        self._root.configure(bg='#1c1c1c')

        # Commands
        fn0 = lambda: self.socket.send(bytes('0', 'utf-8'))
        fn1 = lambda: self.socket.send(bytes('1', 'utf-8'))
        fn2 = lambda: self.socket.send(bytes('2', 'utf-8'))
        fn3 = lambda: self.socket.send(bytes('3', 'utf-8'))
        fn4 = lambda: self.socket.send(bytes('4', 'utf-8'))

        def fn5():
            # Read the sensors
            self.socket.send(bytes('5', 'utf-8'))
            time.sleep(0.5)
            humidity = self.socket.recv(5).decode('utf-8')
            time.sleep(0.5)
            temperature = self.socket.recv(5).decode('utf-8')
            time.sleep(0.5)
            distance = self.socket.recv(5).decode('utf-8')
            

            # Print at the GUI
            text = 'Temp: ' + temperature + '\nHumidity: ' + humidity + 'Dist: ' + distance
            self._label.config(text = text)


        # Buttons
        btn_config = {'bg': '#444444', 'fg': '#ffffff', 'font': ("Arial", 15, 'bold'), 'height':1 , 'width': 8, 'bd':2}
        self._front = tk.Button(self._root, text = '⇧', command = fn0, **btn_config)
        self._back = tk.Button(self._root, text = '⇩', command = fn1, **btn_config)
        self._right = tk.Button(self._root, text = '⇨', command = fn2, **btn_config)
        self._left = tk.Button(self._root, text = '⇦', command = fn3, **btn_config)
        self._stop = tk.Button(self._root, text = 'Stop', command = fn4, **btn_config)
        self._sensor = tk.Button(self._root, text = 'Sensors', command = fn5, **btn_config)

        # Label/frame
        self._frame = tk.LabelFrame(self._root, text = 'Robot status', bg='#1c1c1c', fg='#ffffff', font=("Arial", 12, 'bold'), bd=2, highlightthickness=0, relief='solid')
        self._label = tk.Label(self._frame, 
                               text = 'Temperature: 00.00 \nHumidity: 00.00', 
                               justify = tk.LEFT, bg='#1c1c1c', fg='#ffffff', font=("Arial", 12))
        # Slider
        def on_slider_move(value):
            # Haga aquí la acción que desea realizar cuando se mueve el slider
            print("El valor del slider es: \n", value)

        self._slider_label = tk.Label(self._root, text="Slider", bg='#1c1c1c', fg='#ffffff', font=("Arial", 12))
        

    #def launch(self, ip, port):
        # Wifi
       # self.socket.connect((ip, port))

        # Buttons
        self._left.grid(column = 0, row = 1)
        self._front.grid(column = 1, row = 0)
        self._stop.grid(column = 1, row = 1)
        self._back.grid(column = 1, row = 2)
        self._right.grid(column = 2, row = 1)
        self._sensor.grid(column = 3, row = 3, columnspan = 2, sticky = 'we')

        # Label/frame
        self._frame.grid(column = 3, row = 0, columnspan = 2, rowspan = 3)
        self._label.pack()
        
        # Slider
        self._slider = tk.Scale(self._root, from_=0, to=100, orient='vertical', command=on_slider_move)
        self._slider_label.grid(column=0, row=3)
        self._slider.grid(column=1, row=3, columnspan=2)

        # Columns weights
        self._root.grid_columnconfigure(0, weight = 1)
        self._root.grid_columnconfigure(1, weight = 1)
        self._root.grid_columnconfigure(2, weight = 1)
        self._root.grid_columnconfigure(3, weight = 2)

        self._root.resizable(height = False, width = False)
        self._root.mainloop()



if __name__ == '__main__':
    pendant = Pendant()
  #  pendant.launch('192.168.0.142', 80)


       
        
       
       
