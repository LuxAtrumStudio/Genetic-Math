#include "induco.h"
#include <cmath>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

namespace induco {
struct termios t;
}

int induco::Menu(std::string title, std::vector<std::string> options) {
  bool start = true;
  int maxwidth = title.size();
  int input = 0;
  for (unsigned i = 0; i < options.size(); i++) {
    if (options[i].size() + 5 > maxwidth) {
      maxwidth = options[i].size();
    }
  }
  std::string line = "";
  for (int i = 0; i < (maxwidth - title.size()) / 2; i++) {
    line = line + " ";
  }
  line = line + title;
  std::cout << line << "\n";
  Line(maxwidth);
  for (int i = 0; i < options.size(); i++) {
    line = "[" + std::to_string(i + 1) + "]  " + options[i];
    std::cout << line << "\n";
  }
  while (1) {
    Line(maxwidth);
    char inputchar;
    std::cin >> inputchar;
    input = int(inputchar) - 48;
    if (input > 0 && input <= options.size()) {
      return (input);
    }
  }
}

double induco::GetValue(std::string value) {
  std::cout << "Please Enter Value for \"" + value + "\": ";
  long double input = 0;
  std::cin >> input;
  return (input);
}

std::string induco::SGetValue(std::string value) {
  std::cout << "Please Enter Value for \"" + value + "\": ";
  std::string input = "";
  std::cin >> input;
  return (input);
}

std::string induco::DisplayTime(double elapsed, bool unit) {
  std::string line = "", hstring, minstring, secstring, msstring, usstring;
  int microsec = 0, millisec = 0, sec = 0, min = 0, hour = 0;
  sec = floor(elapsed);
  elapsed -= sec;
  elapsed = elapsed * 1000;
  millisec = floor(elapsed);
  elapsed -= millisec;
  elapsed = elapsed * 1000;
  microsec = round(elapsed);
  while (sec >= 60) {
    sec -= 60;
    min++;
  }
  while (min >= 60) {
    min -= 60;
    hour++;
  }
  hstring = std::to_string(hour);
  line = line + hstring;
  if (unit == true) {
    line = line + "h";
  }
  for (int j = hstring.size(); j < 6; j++) {
    line = line + " ";
  }
  line = line + "|";
  minstring = std::to_string(min);
  line = line + minstring;
  if (unit == true) {
    line = line + "m";
  }
  for (int j = minstring.size(); j < 5; j++) {
    line = line + " ";
  }
  line = line + "|";
  secstring = std::to_string(sec);
  line = line + secstring;
  if (unit == true) {
    line = line + "s";
  }
  for (int j = secstring.size(); j < 5; j++) {
    line = line + " ";
  }
  line = line + "|";
  msstring = std::to_string(millisec);
  line = line + msstring;
  if (unit == true) {
    line = line + "ms";
  }
  for (int j = msstring.size(); j < 4; j++) {
    line = line + " ";
  }
  line = line + "|";
  usstring = std::to_string(microsec);
  line = line + usstring;
  if (unit == true) {
    line = line + "us";
  }
  for (int j = usstring.size(); j < 4; j++) {
    line = line + " ";
  }
  return (line);
}

bool induco::Pause() {
  char input;
  std::cout << "[Y/N]";
  std::cin >> input;
  if (input == 'y' || input == 'Y') {
    return (true);
  } else {
    return (false);
  }
}

void induco::Line(int size) {
  std::string line = "";
  while (size > 0) {
    size--;
    line = line + "=";
  }
  std::cout << line << "\n";
}

void induco::Break() {
  std::cout << "\n\n\n\n\n";
  Line(50);
  Line(50);
  std::cout << "\n\n\n\n\n";
}

void induco::Echo(bool setting) {
  if (setting == true) {
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag = -ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
  } else if (setting == false) {
    tcgetattr(STDIN_FILENO, &t);
    t.c_lflag = -ECHOK;
    tcsetattr(STDIN_FILENO, TCSANOW, &t);
  }
}
