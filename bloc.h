//
// Created by croustibaie on 12/14/15.
//

#ifndef PA_BLOC_H
#include <iostream>
#define PA_BLOC_H


class bloc {

private: int i;
         char x;

public:
    bloc() {
        i=0;
        x='a';
    }
    int get_i()
    {
        std::cout << "i set to " << i << std::endl;
        return i;
    }
    void set_i(int k)
    {
        i=k;
    }
};


#endif //PA_BLOC_H
