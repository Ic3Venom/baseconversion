#include <iostream>
#define SIZE 32

void convert(int x, int BASE);

int main()
{
    using namespace std;
    unsigned long x;
    int BASE;

    cout << "Base would you like to convert into? (MAX is 10)\n$ ";
    cin >> BASE;
    cout << "What number do you want converted? (MAX is 4294967295)\n$ ";
    cin >> x;
    cout << "Turning " << x << " into base " << BASE << "..." << endl;

    convert(x, BASE);
}
void convert(int x, int BASE)
{
    short arr[SIZE] = {0};
    for(short increment = SIZE - 1; x > 0;)
    {
        arr[increment]++;
        for (short len = SIZE-1; len >= 0; len--)
        {
            if (arr[len] == BASE)
            {
                arr[len] = 0;
                len--;
                arr[len]++;
                len++;
            }
        }
        increment = SIZE - 1;
        x--;
    }
    for (short len = 0; len < SIZE; len++)
    {
        std::cout << arr[len];
    }
}
