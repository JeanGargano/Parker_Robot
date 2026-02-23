#ifndef PS4_CONTROLLER_H
#define PS4_CONTROLLER_H

class Ds4Controller {
public:
    void init();
    void chekConnection();
    int readInput();
};

#endif
