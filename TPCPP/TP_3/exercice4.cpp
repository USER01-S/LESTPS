#include <iostream>
using std::cout; using std::endl;
namespace global {

    namespace entiers {
        int add(int a, int b) { return a + b; }
        int sub(int a, int b) { return a - b; }
    }

    namespace reel {
        float add(float a, float b) { return a + b; }
        float sub(float a, float b) { return a - b; }
    }

}

int main() {
    cout << "add entiers (5.5+8) : " << global::entiers::add(5.5, 8) << endl;
    cout << "sub entiers (5-8) : " << global::entiers::sub(5, 8) << endl;
    cout << "add reels  (5.5+8.3) : " << global::reel::add(5.5f, 8.3f) << endl;
    cout << "sub reels  (5.5-8.3) : " << global::reel::sub(5.5f, 8.3f) << endl;
    return 0;
}
