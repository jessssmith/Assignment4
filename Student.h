#include <iostream>

using namespace std;

class Student {
  public:
    int timeArrived;
    int timeAtWindow;
    int timeWait;
    int timeLeaveWindow;
    bool atWindow;

    Student();
    Student(int timeAtWindow);
    ~Student();

    void updateTimeAtWindow();
    void updadteTimeWait();
};

Student::Student() {
  timeArrived = 0;
  timeAtWindow = 0;
  timeWait = 0;
  int timeLeaveWindow = -1;
  atWindow = false;
}

Student::Student(int timeAtWindow) {
  timeArrived = 0;
  timeAtWindow = timeAtWindow;
  timeWait = 0;
}

Student::~Student() {
  //figure out 
}

void Student::updateTimeAtWindow() {
  timeAtWindow--;
}

void Student::updadteTimeWait() {
  timeWait++;
}
