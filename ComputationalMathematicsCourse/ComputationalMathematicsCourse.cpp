#include <iostream>
#include "InputData.h"
#include "FindingTheAmountOfHeat.h"


int main() {

    std::setlocale(LC_ALL, "Russian");
    KHAS::FindingTheAmountOfHeatSingleton::getInstance(KHAS::InputData{}, 67 ).loop();

    return 0;
}