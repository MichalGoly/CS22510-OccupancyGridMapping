#include <stdexcept>
#include <iostream>
#include "GridFrame.h"

using std::domain_error;
using std::cerr;
using std::endl;

/**
 * The starting point of the program
 */
int main() {
    try {
        GridFrame* gridFrame = new GridFrame;
        gridFrame->animate();
    } catch (domain_error e) {
        cerr << e.what() << endl;
        return 1;
    }

    return 0;
}