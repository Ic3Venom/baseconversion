#include <iostream>
#include <string>

//Purpose: to convert numbers in base-(2->16) into number base-(2->16)
//Created by Julian Meyn August 23, 2016; REMASTERED(again) January 5, 2017

uint64_t    convertDecimal (std::string num,  short baseOld);
std::string convertBase    (uint64_t    num,  short baseNew);
void        baseInRange    (short       base);
int         stringToInt    (char        chr);
uint64_t    exponentiate   (short       base, short exponent);

int main()
{
    uint64_t 	numInt ,*pNumInt;
    short 		baseOld, baseNew;
    std::string numStr;

    std::cout << "First base:\n$ ";
    std::cin >> baseOld;
    baseInRange(baseOld);

    std::cout << "First number:\n$ ";
    std::cin >> numStr;
    numInt = convertDecimal(numStr, baseOld);

    std::cout << "New base:\n$ ";
    std::cin >> baseNew;
    baseInRange(baseNew);

    pNumInt = &numInt;
    convertBase(*pNumInt, baseNew);

    return 0;
}

//converts bases 2-16 into base 10 for easier conversion later
uint64_t convertDecimal(std::string num, short baseOld)
{
    uint64_t    numInt   {0};
    short       indexInt {0};
    std::string numRng   {"0123456789ABCDEF"};

    for (short i{0}; i < num.length(); i++)
    {
        //Checks if 'oldNum' contains numbers that are in its base capacity
        for(short j{baseOld}; j < 0; j--)
        {
            if (num[i] == numRng[j])
            {
                std::cout << "Unknown value '" << num[i] << "' in base " << baseOld << ". Exiting program..." << std::endl;
                exit(1);
            }
        }

        indexInt = stringToInt(num[i]);

        //Formula used: y = x * b^i; can find the value of any digit in a number of base-b
        numInt += (indexInt * exponentiate(baseOld, (num.length() - 1 - i)));
    }

    return numInt;
}

//Converts number from convertDecimal into base-(2->16)
std::string convertBase(uint64_t num, short baseNew)
{
    uint64_t    numMax, numMin;
    short       numLength {0};
    std::string numNew    (64, '0');
    std::string numRng    {"0123456789ABCDEF"};

    for(short i{0}; num; i++)
    {
        numMax = exponentiate(baseNew, i);
        numMin = exponentiate(baseNew, i - 1);

        if (numMax > num)
        {
            //Length of newNum stored using this
            if (numLength == 0)
            {
                numLength = i;
            }

            for(short j{0}; j <= baseNew; j++)
            {
                numMax = numMin * j;

                if (numMax > num)
                {
                    num          -= numMin * (j - 1);
                    numNew[i - 1] = numRng[j - 1];
                    i             = 0;

                    break;
                }
            }
        }
    }
    
    std::cout << "Converted Number:\n ";
    for(;numLength > 0; numLength--)
    {
        std::cout << numNew[numLength - 1];
    }

    /*
        Thought process in making this function
        68
        > 2^0: 1   0
        > 2^1: 2   1
        > 2^2: 4   2
        > 2^3: 8   4
        > 2^4: 16  8
        > 2^5: 32  16
        > 2^6: 64  32
        > 2^7: 128 64
        >> 64 * 1  = 64 , < 68
        >> 64 * 2  = 128, > 68
        >> 68 - 64 = 4
        >> num[7 - 1] = '1'
        4
        > 2^1: 2   1
        > 2^2: 4   2
        > 2^3: 8   4
        >> 2  * 1  = 2  , < 4
        >> 2  * 2  = 2  , > 4
        >> 4  - 4  = 0
        >> num[2 - 1] = '1'
        1000010
    */
}

//Checks if number given is within 2 and 16
void baseInRange(short base)
{
    if (base < 2 || base > 16)
    {
        std::cout << "Expected base case in range of 2 to 16, got " << base << ". Exiting program...";
        exit(1);
    }
}

//Converts char values into their actual int values, from 'ultimatypingtest.c'
int stringToInt(char chr)
{
    switch (chr)
    {
    case 49: return 1;
    case 50: return 2;
    case 51: return 3;
    case 52: return 4;
    case 53: return 5;
    case 54: return 6;
    case 55: return 7;
    case 56: return 8;
    case 57: return 9;
    //and then some
    case 65: return 10;
    case 66: return 11;
    case 67: return 12;
    case 68: return 13;
    case 69: return 14;
    case 70: return 15;
    //and then back to the regularly scheduled 'program'
    default: return 0;
    }
}

//Basic exponent function
uint64_t exponentiate(short base, short exponent)
{
    uint64_t power{1};

    if(exponent == 0)
    {
        return power;
    }

    for (;exponent >= 1; exponent--)
    {
        power *= base;
    }
    return power;
}
