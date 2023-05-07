import tkinter as tk
from PIL import Image, ImageTk
import socket as sk
import time

class TeachPendant():
    def __init__(self):
        self._root = tk.Tk()
        self._socket_ = sk.socket(sk.AF_INET, sk.SOCK_STREAM)
        self._root.configure(bg='#545454')

        

        # Commands
        fn0 = lambda: self._socket_.send(bytes('0', 'utf-8'))
        fn1 = lambda: self._socket_.send(bytes('1', 'utf-8'))
        fn2 = lambda: self._socket_.send(bytes('2', 'utf-8'))
        fn3 = lambda: self._socket_.send(bytes('3', 'utf-8'))
        fn4 = lambda: self._socket_.send(bytes('4', 'utf-8'))

        def fn5():
            # Read the sensors
            self._socket_.send(bytes('5', 'utf-8'))
            time.sleep(0.5)
            humidity = self._socket_.recv(5).decode('utf-8')
            time.sleep(0.5)
            temperature = self._socket_.recv(5).decode('utf-8')
            time.sleep(0.5)
            distance = self._socket_.recv(5).decode('utf-8')

            # Print at the GUI
            text = 'Temp: ' + temperature + '\nHumidity: ' + humidity 
            text += '\nDistance: ' + distance
            self._label.config(text = text)
        #IMAGE
        # Imagen
        self._image = Image.open("est.jpg")
        # Cambiar el tamaño de la imagen
        self._image = self._image.resize((50, 50), Image.ANTIALIAS)
        self._photo = ImageTk.PhotoImage(self._image)
        self._image_label = tk.Label(self._root, image=self._photo)


        # Buttons
        
        self._front = tk.Button(self._root, text = '⬆', command = fn0, 
                                bg='#525C5D', fg="#C40909",
                                height=1 , width= 4,
                                font=("Arial", 10, "bold"))
        self._back = tk.Button(self._root, text = '⬇', command = fn1, 
                               bg='#525C5D',fg="#C40909",
                               height=1 , width= 4,
                               font=("Arial", 10, "bold"))
        self._right = tk.Button(self._root, text = '➡', command = fn2, 
                                bg='#525C5D',fg="#C40909",
                                height=1 , width= 4,
                                font=("Arial", 10, "bold"))
        self._left = tk.Button(self._root, text = '⬅', command = fn3,
                               bg='#525C5D',fg="#C40909",
                               height=1 , width= 4,
                               font=("Arial", 10, "bold"))
        self._stop = tk.Button(self._root, text = 'Stop', command = fn4, 
                               bg='#C40909',fg="#ffffff",
                               height=1 , width= 4,
                               font=("Arial", 10, "bold"))
        self._sensor = tk.Button(self._root, text = '📈📋📉', command = fn5, 
                                 bg='#525C5D',fg="#ffffff",
                                 height=1 , width= 4,
                                 font=("Arial", 15, "bold"))

        # Label/frame
        self._frame = tk.LabelFrame(self._root, text = 'Terreneitor status', font=("Arial", 10, "bold"))
        self._label = tk.Label(self._frame, 
                               text = 'Temperature: 00.00 \nHumidity: 00.00''\nDistance: 00.00',                               
                               justify = tk.LEFT,
                               bg='#302727', fg='#ffffff')
      
        def speed(int):
            self.socket.send(bytes(str(self._scroll.get())+'\n','utf-8'))
            time.sleep(0.1)
            
        self._scroll= tk.Scale(self._root,orient="vertical",from_=0,to=100,command=speed,
                               bg='#525C5D',fg='#C40909', font=("Arial", 10, ))
        
            
        
    def launch(self, ip, port):
        # Wifi
        self._socket_.connect((ip, port))
       
       #image
        self._image_label.grid(column=0, row=3)
    # Load image
        self._image = Image.open("est.jpg")
    
        
        # Buttons
        
       
        
        self._left.grid(column = 1, row = 1)
        self._front.grid(column = 2, row = 0)
        self._stop.grid(column = 2, row = 1)
        self._back.grid(column = 2, row = 2)
        self._right.grid(column = 3, row = 1)
        self._sensor.grid(column = 4, row = 3, columnspan = 2, sticky = 'we')
        self._scroll.grid(column = 0, row = 0, rowspan = 3)

        # Label/frame
        self._frame.grid(column = 4, row = 0, columnspan = 2, rowspan = 3)
        self._label.pack()

        # Columns weights
        self._root.grid_columnconfigure(0, weight = 1)
        self._root.grid_columnconfigure(1, weight = 1)
        self._root.grid_columnconfigure(2, weight = 1)
        self._root.grid_columnconfigure(3, weight = 2)

        self._root.resizable(height = False, width = False)
        self._root.mainloop()



if __name__ == '__main__':
    pendant = TeachPendant() 
    pendant.launch('192.168.0.192', 80)


