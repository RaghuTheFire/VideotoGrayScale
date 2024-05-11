
// Import necessary libraries
#include <QApplication>
#include <QMainWindow>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QMessageBox>
#include <opencv2/opencv.hpp>

// Main Window Class
class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr) : QMainWindow(parent) {
        // Set window title and size
        setWindowTitle("Video to Grayscale");
        resize(1000, 700);

        // Create main layout
        QVBoxLayout *mainLayout = new QVBoxLayout;

        // Create top label
        QLabel *topLabel = new QLabel("VIDEO TO GRAYSCALE");
        topLabel->setStyleSheet("font-size: 50px; font-weight: bold; text-decoration: underline; color: magenta;");
        mainLayout->addWidget(topLabel, 0, Qt::AlignHCenter);

        // Create label for instructions
        QLabel *instructionsLabel = new QLabel("Select any video &\nconvert to grayscale video");
        instructionsLabel->setStyleSheet("font-size: 40px; color: green;");
        mainLayout->addWidget(instructionsLabel, 0, Qt::AlignHCenter);

        // Create label for selected video
        QLabel *selectedVideoLabel = new QLabel("Selected Video");
        selectedVideoLabel->setStyleSheet("font-size: 30px; color: brown;");
        mainLayout->addWidget(selectedVideoLabel);

        // Create text box for displaying selected video path
        pathTextBox = new QLabel;
        pathTextBox->setStyleSheet("font-size: 30px; background-color: lightyellow; color: orange; border: 2px solid black;");
        mainLayout->addWidget(pathTextBox);

        // Create button layout
        QHBoxLayout *buttonLayout = new QHBoxLayout;

        // Create "SELECT" button
        QPushButton *selectButton = new QPushButton("SELECT");
        selectButton->setStyleSheet("font-size: 25px; background-color: lightgreen; color: blue;");
        connect(selectButton, &QPushButton::clicked, this, &MainWindow::openFile);
        buttonLayout->addWidget(selectButton);

        // Create "ORIGINAL VIDEO" button
        QPushButton *originalVideoButton = new QPushButton("ORIGINAL VIDEO");
        originalVideoButton->setStyleSheet("font-size: 25px; background-color: orange; color: blue;");
        connect(originalVideoButton, &QPushButton::clicked, this, &MainWindow::showOriginalVideo);
        buttonLayout->addWidget(originalVideoButton);

        // Create "GRAYSCALE VIDEO" button
        QPushButton *grayscaleVideoButton = new QPushButton("GRAYSCALE VIDEO");
        grayscaleVideoButton->setStyleSheet("font-size: 25px; background-color: orange; color: blue;");
        connect(grayscaleVideoButton, &QPushButton::clicked, this, &MainWindow::showGrayscaleVideo);
        buttonLayout->addWidget(grayscaleVideoButton);

        // Create "EXIT" button
        QPushButton *exitButton = new QPushButton("EXIT");
        exitButton->setStyleSheet("font-size: 25px; background-color: red; color: blue;");
        connect(exitButton, &QPushButton::clicked, this, &QMainWindow::close);
        buttonLayout->addWidget(exitButton);

        mainLayout->addLayout(buttonLayout);

        // Set main layout
        QWidget *centralWidget = new QWidget;
        centralWidget->setLayout(mainLayout);
        setCentralWidget(centralWidget);
    }

private slots:
    void openFile() {
        QString fileName = QFileDialog::getOpenFileName(this, "Select Video File", QDir::currentPath(), "Video Files (*.mp4 *.avi *.mov)");
        if (!fileName.isEmpty()) {
            pathTextBox->setText(fileName);
            videoPath = fileName.toStdString();
        }
    }

    void showOriginalVideo() {
        if (!videoPath.empty()) {
            cv::VideoCapture cap(videoPath);
            if (cap.isOpened()) {
                cv::namedWindow("Original Video", cv::WINDOW_NORMAL);
                while (true) {
                    cv::Mat frame;
                    cap >> frame;
                    if (frame.empty()) {
                        break;
                    }
                    cv::imshow("Original Video", frame);
                    if (cv::waitKey(30) == 'q') {
                        break;
                    }
                }
                cv::destroyWindow("Original Video");
            } else {
                QMessageBox::warning(this, "Error", "Failed to open video file.");
            }
        } else {
            QMessageBox::warning(this, "Error", "Please select a video file first.");
        }
    }

    void showGrayscaleVideo() {
        if (!videoPath.empty()) {
            cv::VideoCapture cap(videoPath);
            if (cap.isOpened()) {
                cv::namedWindow("Grayscale Video", cv::WINDOW_NORMAL);
                while (true) {
                    cv::Mat frame;
                    cap >> frame;
                    if (frame.empty()) {
                        break;
                    }
                    cv::Mat grayFrame;
                    cv::cvtColor(frame, grayFrame, cv::COLOR_BGR2GRAY);
                    cv::imshow("Grayscale Video", grayFrame);
                    if (cv::waitKey(30) == 'q') {
                        break;
                    }
                }
                cv::destroyWindow("Grayscale Video");
            } else {
                QMessageBox::warning(this, "Error", "Failed to open video file.");
            }
        } else {
            QMessageBox::warning(this, "Error", "Please select a video file first.");
        }
    }

private:
    QLabel *pathTextBox;
    std::string videoPath;
};

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    MainWindow window;
    window.show();
    return app.exec();
}

