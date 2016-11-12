#include "../induco.h"
#include "display.h"
#include "genetic_core.h"
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

void genetic::display::DrawStats(bool firstcall) {}

void genetic::display::DrawEquation(int pointer, bool nulls, bool index) {
  bool loadoperator = false;
  std::string localbits = population[pointer].bits;
  std::string bytes[16] = {"0", "1", "2", "3", "4", "5", "6",  "7",
                           "8", "9", "+", "-", "*", "/", "14", "15"};
  if (index == true) {
    std::cout << "[" << pointer << "]>";
  }
  for (int i = 0; i < localbits.size(); i += 4) {
    int bit = 0;
    for (int j = i; j < i + 4; j++) {
      if (localbits[j] == '1') {
        bit += pow(2, (3 - (j - i)));
      }
    }
    if (bit < 10 && loadoperator == false) {
      std::cout << bytes[bit];
      loadoperator = true;
    } else if (bit > 9 && bit < 14 && loadoperator == true) {
      std::cout << bytes[bit];
      loadoperator = false;
    } else if (nulls == true) {
      std::cout << "[" << bytes[bit] << "]";
    }
  }
  std::cout << "=" << population[pointer].value << "\n";
}

void genetic::display::DrawEquation(Chromosome chromo, bool nulls) {
  bool loadoperator = false;
  std::string localbits = chromo.bits;
  std::string bytes[16] = {"0", "1", "2", "3", "4", "5", "6",  "7",
                           "8", "9", "+", "-", "*", "/", "14", "15"};
  for (int i = 0; i < localbits.size(); i += 4) {
    int bit = 0;
    for (int j = i; j < i + 4; j++) {
      if (localbits[j] == '1') {
        bit += pow(2, (3 - (j - i)));
      }
    }
    if (bit < 10 && loadoperator == false) {
      std::cout << bytes[bit];
      loadoperator = true;
    } else if (bit > 9 && bit < 14 && loadoperator == true) {
      std::cout << bytes[bit];
      loadoperator = false;
    } else if (nulls == true) {
      std::cout << "[" << bytes[bit] << "]";
    }
  }
  std::cout << "=" << chromo.value;
}

void genetic::display::DrawChromosome(int pointer, bool index) {
  if (index == true) {
    std::cout << "[" << pointer << "]>";
  }
  if (pointer < populationsize && pointer > -1) {
    std::cout << population[pointer].bits << "\n";
  } else {
    std::cout << "\"ERROR\"\n";
  }
}

void genetic::display::DisplayAll(bool chromosome, bool equation, bool fitness,
                                  bool nulls) {
  for (int i = 0; i < population.size(); i++) {
    if (chromosome == true) {
      DrawChromosome(i, true);
    }
    if (equation == true) {
      DrawEquation(i, nulls, true);
    }
    if (fitness == true) {
      std::cout << "[" << i << "]" << population[i].fitness << "\n";
    }
  }
}
