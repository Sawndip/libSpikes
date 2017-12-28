//
// Created by akshay on 29-Jun-17.
//

#include <iostream>
#include "libSpikes/Core"

using namespace Spikes;

int main(){

    auto a = FileReader(R"(C:\Users\aksha\Documents\GitHub\NeuCube_Matlab\data\wrist_movement_eeg)");

    for (auto i:a.get_data()) {
        std::cout<<i<<'\n';
    }

    return 0;
}