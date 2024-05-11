# VideotoGrayScale

This C++ code uses the Qt framework and OpenCV library to create a GUI application that allows the user to select a video file, view the original video, and view the grayscale version of the video. The main components of the code are:

1. `MainWindow` class: This class inherits from `QMainWindow` and represents the main window of the application. It contains the UI elements such as labels, text boxes, and buttons, and handles the user interactions.

2. `openFile()` slot: This slot is connected to the "SELECT" button and opens a file dialog for the user to select a video file. The selected file path is displayed in the text box.

3. `showOriginalVideo()` slot: This slot is connected to the "ORIGINAL VIDEO" button and opens a new window to display the original video using OpenCV's `cv::VideoCapture` and `cv::imshow()` functions.

4. `showGrayscaleVideo()` slot: This slot is connected to the "GRAYSCALE VIDEO" button and opens a new window to display the grayscale version of the video. It uses OpenCV's `cv::cvtColor()` function to convert the video frames to grayscale.

5. `main()` function: This is the entry point of the application. It creates a `QApplication` instance and a `MainWindow` object, and shows the main window.
