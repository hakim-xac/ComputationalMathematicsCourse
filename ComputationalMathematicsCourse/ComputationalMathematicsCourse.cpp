#include <iostream>
#include "InputData.h"
#include "FindingTheAmountOfHeat.h"


int main() {

    std::setlocale(LC_ALL, "Russian");
    KHAS::FindingTheAmountOfHeatSingleton::getInstance(KHAS::InputData{ 0.0015, 0.001, 0.0001 }, 85 ).loop();

    return 0;
}