
#include <iostream>

using std::getline;
using std::fstream;
using std::cout;

int main() {
 char array[5];
    for(int i=0;i<5;i++)
        array[i]='a'+i;
    char array2[5];
    for(int i=0;i<5;i++)
        array2[i]='a'+i+2;
    array[0]=array2[0];

    return 0;
}
