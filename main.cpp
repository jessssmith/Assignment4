#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include "GenQueue.h"
#include "Window.h"
//#include "Student.h"

int main(int argc, char** argv) {
  //queue to hold students in line or at window
  GenQueue<Student*> *q = new GenQueue<Student*>();
  //queue to hold students who have gone through the line
  GenQueue<Student*> *finishedQ = new GenQueue<Student*>();

  //variables
  int time = 0;
  string file = "";
  int numStudents = 0;
  float waitTime = 0;
  int waitOverTen = 0;
  float wIdleTimes = 0;
  int idleOverFive = 0;
  int numWindows = 0;
  int clockTime = 0;

  //take in command line argument
  if(argc == 1) {
    //if the user put no command line arguments
    cerr << "Please enter the name of the file as a command line argument" << endl;
    exit(1);
  }
  else {
    //assign file name from command line argument to string variable
    file = argv[1];
  }

  //open the file
  ifstream inFile (file);

  string line;
  vector<int> input;
  int lineInput;
  if(inFile.is_open()) {
    while(getline(inFile, line)) {
      try {
        lineInput = stoi(line);
        input.push_back(lineInput);
      }
      catch(std::invalid_argument) {
        cout << "file must contain only numeric values" << endl;
        exit(1);
      }

    }
  }
  else {
    cerr << "File was not opened properly" << endl;
    exit(1);
  }

  //close file
  inFile.close();

  //creating windows
  numWindows = input[0];
  //cout << "numWindows " << numWindows << endl;
  Window *windowArray[numWindows];
  for(int i = 0; i < numWindows; ++i) {
    Window *w = new Window();
    windowArray[i] = w;
  }

  //create students and add them to queue
  bool createStudents = true;
  while(createStudents == true) {
    for(int i = 1; i < input.size(); ++i) {
      time = input[i];
      numStudents = input[i+1];
      for(int j = i+2; j < i+2+numStudents; ++j) {
        Student *s = new Student();
        s->timeAtWindow = input[j];
        s->timeArrived = time;
        q->insert(s);
      }
      i += (numStudents+1);
    }
    createStudents = false;
  }

//main loop
  int qSize = q->getSize();
  int sWaitTimes[qSize];
  while(!q->isEmpty()) {
    for(int i = 0; i < q->getSize(); ++i) {
      Student *tempStudent = q->peekFront();
      q->remove();
      //if the time the student arrived is the time it is right now
      if(tempStudent->timeArrived == clockTime) {
        int closedWindows = 0;
        for(int i = 0; i < numWindows; ++i) {
          //add student to the first open window, also assign time that student will leave window
          if(windowArray[i]->isOpen == true && tempStudent->atWindow == false) {
            tempStudent->timeLeaveWindow = tempStudent->timeAtWindow + clockTime;
            windowArray[i]->addStudent(tempStudent);
          }
          //keep track of closed windows at each time
          else if(windowArray[i]->isOpen == false) {
            closedWindows++;
            //if all windows are closed student has to wait in line
            if(closedWindows == numWindows) {
              tempStudent->updadteTimeWait();
            }
          }
          //if there is an open window, will be taken care of when window is updated
          else {
            continue;
          }
        }
      }
      //if the student has been waiting in line for open window
      else if(tempStudent->timeArrived < clockTime && tempStudent->atWindow == false) {
        int closedWindows = 0;
        for(int i = 0; i < numWindows; ++i) {
          //add student to window if one is now open, also assign time that student will leave window
          if(windowArray[i]->isOpen == true && tempStudent->atWindow == false) {
            tempStudent->timeLeaveWindow = tempStudent->timeAtWindow + clockTime;
            windowArray[i]->addStudent(tempStudent);
          }
          //keep track of how many windows are closed
          else if(windowArray[i]->isOpen == false) {
            closedWindows++;
            //if all the windows are closed student has to wait in line still
            if(closedWindows == numWindows) {
              tempStudent->updadteTimeWait();
            }
          }
        }
      }
      //check if student at window needs to leave, student is removed when updateWindow is called below
      //add student to finishedQ if they are done at the window, else stay in original queue
      if(tempStudent->timeLeaveWindow == clockTime)
        finishedQ->insert(tempStudent);
      else
        q->insert(tempStudent);
    }
    //update the windows as long as the q is not empty;
    if(q->isEmpty() == false) {
      for(int i = 0; i < numWindows; ++i) {
        windowArray[i]->updateWindow();
      }
      clockTime++;
    }
  }

 //calculating stats
 //get all student wait times into an array to make calculations easier
 for(int i = 0; i < qSize; ++i) {
   Student *studentStats = finishedQ->peekFront();
   finishedQ->remove();
   sWaitTimes[i] = studentStats->timeWait;
 }

 //sort array from smallest to largest
 sort(sWaitTimes, sWaitTimes+qSize);

 //calculate mean total wait time and the number of wait times over 10 minutes
 for(int i = 0; i < qSize; ++i) {
   waitTime += sWaitTimes[i];
   if(sWaitTimes[i] > 10)
    waitOverTen++;
 }
 //calculate median student wait time
 float medianSWait = 0;
 if(qSize%2 == 0)
  medianSWait = (sWaitTimes[(qSize/2)] + sWaitTimes[(qSize/2)-1]) / 2.0;
 else
  medianSWait = sWaitTimes[(qSize/2)+1];

  //calculate mean window idle time
  for(int i = 0; i < numWindows; ++i) {
    wIdleTimes += windowArray[i]->timeOpen;
    if(windowArray[i]->timeOpen > 5)
      idleOverFive++;
  }

  //sort array from smallest to largest
  int idleTimeArr[numWindows];
  for(int i = 0; i < numWindows; ++i) {
    idleTimeArr[i] = windowArray[i]->timeOpen;
  }
  sort(idleTimeArr, idleTimeArr+numWindows);


 cout << "1. Mean student wait time " << waitTime/qSize << " minutes" << endl;
 cout << "2. Median student wait time " << medianSWait << endl;
 cout << "3. Longest student wait time " << sWaitTimes[qSize-1] << endl;
 cout << "4. Number of students with wait times over 10 minutes " << waitOverTen << endl;
 cout << "5. Mean window idle time " << wIdleTimes/numWindows << endl;
 cout << "6. Longest window idle time " << idleTimeArr[numWindows-1] << endl;
 cout << "7. Number of windows idle for over 5 minutes " << idleOverFive << endl;

}
