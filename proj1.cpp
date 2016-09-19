// project 1 - CAV
#include <stdio.h>
#include <math.h>

class FCM {
    // variaveis
    public:
        int order;
        int table[getOrder(order)][27];
    
    // metodos
    int getOrder(int order) {
        return pow(27, order);
    };    
};

teste