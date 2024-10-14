import sys
import os
import random
from time import sleep
from PyQt5.QtWidgets import QApplication, QMainWindow, QVBoxLayout, QFileDialog, QErrorMessage
from PyQt5.QtGui import QPalette, QColor
from PyQt5 import uic, QtCore
import numpy as np
import matplotlib.pyplot as plt
import matplotlib
matplotlib.use("Qt5Agg")
from matplotlib.figure import Figure
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
from matplotlib.backends.backend_qt5agg import NavigationToolbar2QT as NavigationToolbar
from matplotlib import image as mpimg


# Loading the UI file from the path
Form = uic.loadUiType(os.path.join(os.getcwd(), 'gui.ui'))[0]


class Window(QMainWindow, Form):
    def __init__(self):
        # Initializing the parent classes and setup the UI
        QMainWindow.__init__(self)
        Form.__init__(self)
        self.setupUi(self)

        # Figure section with the toolbar
        self.figure = Figure()
        self.canvas = FigureCanvas(self.figure)
        self.navigationToolbar = NavigationToolbar(self.canvas, self)

        # Putting the figure and canvas into the empty widget 
        picture_widget = QVBoxLayout(self.picture_widget)   
        picture_widget.addWidget(self.canvas)
        picture_widget.addWidget(self.navigationToolbar)

        # Different sections' events
        self.time_lineEdit.textChanged.connect(self.time_lineEdit_changed)
        self.brightness_lineEdit.textChanged.connect(self.brightness_lineEdit_changed)
        self.time_slider.sliderMoved.connect(self.time_slider_changed)
        self.time_slider.valueChanged.connect(self.time_slider_changed)
        self.brightness_slider.sliderMoved.connect(self.brightness_slider_changed)
        self.openButton.clicked.connect(self.open_file)
        self.startButton.clicked.connect(self.start_plot)
        self.greyButton.clicked.connect(self.grey_button_checked)
        self.colorButton.clicked.connect(self.color_button_checked)

        # Initial value of the sections
        self.brightness_slider.setValue(50)
        self.time_slider.setRange(0, 60)
        self.time_slider.setValue(30)
        self.time_lineEdit.setText('30')
        self.brightness_lineEdit.setText('0')

        # Disabling the functions at first
        self.greyButton.setChecked(False)
        self.colorButton.setChecked(False)
        self.greyButton.setEnabled(False)
        self.colorButton.setEnabled(False)
        self.time_slider.setEnabled(False)
        self.brightness_slider.setEnabled(False)
        self.time_lineEdit.setEnabled(False)
        self.brightness_lineEdit.setEnabled(False)
        self.startButton.setEnabled(False)

        # Setting the theme of the main window and buttons
        self.palette = QPalette()
        self.palette.setColor(QPalette.Window, QColor('darkgrey'))
        self.palette.setColor(QPalette.Button, QColor('darkgrey'))
        self.setPalette(self.palette)
        
        # Required member variables of different sections(used in different methods)
        self.time = 30
        self.thread = None
        self.image = None
        self.grey_image = None
        self.curr_image = None
        self.input_error_message = QErrorMessage()


    def time_lineEdit_changed(self, time):
        # Setting the time and time slider values
        if time == '':
            self.time = 0
            self.time_slider.setValue(0)
        else:
            self.time = int(time)
            self.time_slider.setValue(int(time))


    def brightness_lineEdit_changed(self, brightness):
        # Setting the brightness line edit
        if brightness == '':
            self.brightness_slider.setValue(50)
        else:
            self.brightness_slider.setValue(int(brightness) + 50)
            # self.curr_image *= (brightness / 100)
            # self.ax.imshow(self.curr_image)
            # self.figure.canvas.draw()


    def time_slider_changed(self, value):
        # Setting the time and time line edit values
        self.time = value
        self.time_lineEdit.setText(str(value))  


    def brightness_slider_changed(self, value):
        # Setting the brightness line edit value
        self.brightness_lineEdit.setText(str(value - 50))        


    def open_file(self):
        # File dialog
        filename, _ = QFileDialog.getOpenFileName(self, 'Open Image')
        if filename:
            # Checking the format of the file
            if filename.split('.')[-1] != 'jpg' and filename.split('.')[-1] != 'png':
                self.input_error_message.showMessage("Wrong Input Format!")
                return
            # Current image is used to udpate the canvas in different sections so its write flag is on
            self.image = mpimg.imread(filename)
            self.curr_image = self.image.copy()
            self.curr_image.setflags(write=1)

            # Making a grey image right after openning the original image
            self.grey_image = self.image.copy()
            self.grey_image[:, :, 0] = self.grey_image[:, :, 1] = self.grey_image[:, :, 2] = np.dot(self.grey_image, [0.5, 0.1, 0.2])

            # Adding axes to the figure
            self.ax = self.figure.add_axes([0.1, 0.1, 0.8, 0.8])
            self.ax.set_xticks([])
            self.ax.set_yticks([])

            # Displaying the image to the canvas
            self.ax.imshow(self.curr_image)
            self.figure.canvas.draw()

            # Enabling all the widgets
            self.greyButton.setEnabled(True)
            self.colorButton.setEnabled(True)
            self.time_slider.setEnabled(True)
            self.brightness_slider.setEnabled(True)
            self.time_lineEdit.setEnabled(True)
            self.brightness_lineEdit.setEnabled(True)
            self.startButton.setEnabled(True)
            self.colorButton.setChecked(True)
            self.greyButton.setChecked(False)
        

    def grey_button_checked(self):
        # Setting the current image to the grey image 
        self.curr_image = self.grey_image

        # If the timer is not running the whole image turns grey 
        # else the current image is sent to the thread class
        if not self.thread:
            self.ax.imshow(self.curr_image)
            self.figure.canvas.draw()
        else:
            self.thread.set_image(self.curr_image)


    def color_button_checked(self):
        # Setting the current image to the original image 
        self.curr_image = self.image.copy()

        # If the timer is not running the whole image turns colorful
        # else the current image is sent to the thread class
        if not self.thread:
            self.ax.imshow(self.image)
            self.figure.canvas.draw()
        else:
            self.thread.set_image(self.curr_image)


    def start_plot(self):
        self.startButton.setEnabled(False)

        # making a thread and setting its signals
        self.thread = PlotThread(self, self.curr_image, self.time)
        self.thread.upload_image.connect(self.update_image)
        self.thread.finished.connect(self.stop_update)
        self.thread.timer.connect(self.timer)
        self.thread.start()


    def update_image(self, updated_image):
        # Current image is the updated image and its displayed on the figure
        self.curr_image = updated_image.copy()
        self.ax.imshow(updated_image)
        self.figure.canvas.draw()


    def stop_update(self):
        self.startButton.setEnabled(True)


    def timer(self, oldtime, time):
        # Updating the timer due to the change of timer signal in the thread class
        if (oldtime - time) <= 0:
            self.time_lineEdit.setText('0')
        else:
            self.time_slider.setValue(oldtime - time)
            self.time_lineEdit.setText(str(oldtime - time))


class PlotThread(QtCore.QThread):
    # Signals 
    upload_image = QtCore.pyqtSignal(np.ndarray)
    finished = QtCore.pyqtSignal()
    timer = QtCore.pyqtSignal(int, int)

    def __init__(self, window, image, time):
        QtCore.QThread.__init__(self, parent=window)
        self.time = time
        self.image = image
        self.height = self.image.shape[0]
        self.new_image = np.zeros_like(self.image)
        self.fraction = int(self.height / self.time)


    # Used in the grey and color check boxes
    def set_image(self, image):
        self.image = image
        
        
    def run(self):
        sleep_time = 1 / self.fraction
        self.upload_image.emit(self.new_image)
        elapsed_time = 0
        for n in range(0, self.height, self.fraction):
            # updating the new image values with the image values (one fraction at each time)
            self.new_image[n:n+self.fraction] = self.image[n:n+self.fraction]
            self.upload_image.emit(self.new_image)
            sleep(1)
            elapsed_time += 1
            self.timer.emit(self.time, elapsed_time)
        self.finished.emit()


# Making the application and showing it
app = QApplication(sys.argv)
w = Window()
w.setWindowTitle("Sina Rashidi 9523047")
app.setStyle('Fusion')
w.show()
sys.exit(app.exec_())   
