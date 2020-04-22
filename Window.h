#include <iostream>
#include "Student.h"

using namespace std;

class Window {
public:
  bool isOpen;
  int timeOpen;

  Window();
  ~Window();

  void updateWindow();
  void addStudent(Student *s);
  Student removeStudent();

  Student *s;
};

Window::Window() {
  isOpen = true;
  timeOpen = 0;
}

Window::~Window() {
  //figure out 
}

void Window::updateWindow() {
  if(isOpen == true)
    timeOpen++;
  else {
    s->timeAtWindow--;
    if(s->timeAtWindow == 0)
      removeStudent();
  }
}

void Window::addStudent(Student *st) {
  s = st;
  isOpen = false;
  s->atWindow = true;
}

Student Window::removeStudent() {
    Student *st = s;
    s = NULL;
    isOpen = true;
    return *st;
}
