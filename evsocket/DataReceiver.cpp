#include "DataReceiver.h"

#include <iostream>
#include <string>

DataReceiver::DataReceiver() : 
    requestedClose(false) {

}

DataReceiver::~DataReceiver() {
    std::cout << "DataReceiver destructor" << std::endl;
}

void DataReceiver::onDataReceived(int n, char* buffer) {
    std::cout << "Received: " << buffer << std::endl;
    if ('q' == buffer[0]) {
        requestedClose = true;
    }
}