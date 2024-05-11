
// Import necessary libraries
#include <FL/Fl.H>
#include <FL/Fl_Window.H>
#include <FL/Fl_Button.H>
#include <FL/Fl_PNG_Image.H>
#include <FL/Fl_JPEG_Image.H>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

// Global variables
std::string filename;
cv::VideoCapture source;

// Function to open file
void open_file(Fl_Widget* widget, void* data) {
    Fl_Native_File_Chooser fnfc;
    fnfc.title("Select file");
    fnfc.type(Fl_Native_File_Chooser::BROWSE_FILE);
    fnfc.filter("Video Files\t*.avi\n*.mp4\n*.mov\n*.mkv");
    fnfc.preset_file(filename.c_str());
    switch (fnfc.show()) {
        case -1:
            fprintf(stderr, "ERROR: %s\n", fnfc.errmsg());
            break;
        case 1:
            filename = fnfc.filename();
            break;
        default:
            break;
    }
    source.open(filename);
}

// Function to show original video
void original_fun(Fl_Widget* widget, void* data) {
    if (filename.empty()) {
        fl_alert("Please select a video file first.");
        return;
    }
    cv::namedWindow("Original Video", cv::WINDOW_AUTOSIZE);
    while (true) {
        cv::Mat frame;
        source >> frame;
        if (frame.empty()) {
            break;
        }
        cv::imshow("Original Video", frame);
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
    cv::destroyWindow("Original Video");
}

// Function to show grayscale video
void grayscale_fun(Fl_Widget* widget, void* data) {
    if (filename.empty()) {
        fl_alert("Please select a video file first.");
        return;
    }
    cv::namedWindow("GrayScale Video", cv::WINDOW_AUTOSIZE);
    while (true) {
        cv::Mat frame;
        source >> frame;
        if (frame.empty()) {
            break;
        }
        cv::Mat gray;
        cv::cvtColor(frame, gray, cv::COLOR_BGR2GRAY);
        cv::imshow("GrayScale Video", gray);
        if (cv::waitKey(1) == 'q') {
            break;
        }
    }
    cv::destroyWindow("GrayScale Video");
}

int main(int argc, char** argv) {
    Fl::scheme("gtk+");
    Fl_Window* window = new Fl_Window(1000, 700, "Video to Grayscale");

    Fl_Box* start1 = new Fl_Box(110, 10, 780, 80, "VIDEO TO GRAYSCALE");
    start1->labelfont(FL_HELVETICA_BOLD_ITALIC);
    start1->labelsize(50);
    start1->labelcolor(fl_rgb_color(255, 0, 255));

    Fl_Box* lbl1 = new Fl_Box(170, 110, 660, 120, "Select any video &\nconvert to grayscale video");
    lbl1->labelfont(FL_HELVETICA_BOLD_ITALIC);
    lbl1->labelsize(40);
    lbl1->labelcolor(fl_rgb_color(0, 128, 0));

    Fl_Box* lbl2 = new Fl_Box(80, 280, 300, 40, "Selected Video");
    lbl2->labelfont(FL_HELVETICA_BOLD_ITALIC);
    lbl2->labelsize(30);
    lbl2->labelcolor(fl_rgb_color(165, 42, 42));

    Fl_Button* selectb = new Fl_Button(120, 580, 150, 50, "SELECT");
    selectb->callback(open_file);

    Fl_Button* originalb = new Fl_Button(80, 450, 300, 50, "ORIGINAL VIDEO");
    originalb->callback(original_fun);

    Fl_Button* grayscaleb = new Fl_Button(560, 450, 300, 50, "GRAYSCALE VIDEO");
    grayscaleb->callback(grayscale_fun);

    Fl_Button* exitb = new Fl_Button(750, 580, 150, 50, "EXIT");
    exitb->callback(fl_close);

    window->end();
    window->show(argc, argv);
    return Fl::run();
}


