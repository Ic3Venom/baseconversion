#include <iostream>

void convert(uint64_t *pNUM, short BASE);
uint64_t power(short BASE, short exponent);

int main()
{
    using namespace std;
    
    uint64_t NUM, *pNUM;
    unsigned short BASE;
    
    cout << "Base would you like to convert into? (MAX is 16)\n$ ";
    cin >> BASE;
    if (BASE > 16 || BASE <= 1)
    {
        cout << "Expected base case in range of 1 to 16, got " << BASE << ". Exiting program..." << endl;
        return BASE;
    }

    cout << "What number do you want converted? (MAX is 18446744073709551615)\n$ ";
    cin >> NUM;
    cout << "Turning " << NUM << " into base " << BASE << "..." << endl;

    //Uses pointer pNUM to pass u64bit_t NUM to function convert()
    pNUM = &NUM;
    convert(pNUM, BASE);

    return 0;
}
void convert(uint64_t *pNUM, short BASE)
{
    //1-64 for maximum conversion size, 65 to hold total significant digits
    short arr[65] = {};
    char numbers[17] = {"0123456789ABCDEF"};
    
    //Step is column+1 of the conversion number.
    for(short step(0); *pNUM > 0; step++)
    {
        //Max range of NUM
        uint64_t y = power(BASE, step) - 1;
        
        if (y >= *pNUM)
        {
            //Min range of NUM
            uint64_t z = power(BASE, step-1);
            
            //Loops to see how many times z can go into NUM j times before passing y
            for(short j = BASE-1; j >= 0; j--)
            {
                if ((z * j) <= *pNUM && (z * j)<= y)
                {
                    if(!arr[64])
                    {
                        arr[64] = step-1;
                    }
                    
                    //Puts correct number into correct column (step-1)
                    arr[step-1] = numbers[j];
                    *pNUM -= (z * j);
                    step = 0;
                    break;
                }
            }
        }
        //If y !>= NUM, change the step column to '0'
        else
        {
            arr[step-1] = numbers[0];
        }
    }
    //Prints arr[64] times, the max length of the converted number
    for(;arr[64] >= 0; arr[64]--)
    {
        std::cout << char(*(arr + arr[64]));
    }
}
//Basic exponent function, use of cmath for 1 function was not ideal
uint64_t power(short BASE, short exponent)
{
    uint64_t product = 1;
    
    for (;exponent >= 1; exponent--)
    {
        product *= BASE;
    }
    return product;
