/*
** File: baseconverter.cpp
** Purpose: to convert numbers from base-(2->16) to base-(2->16)
** Created by Julian Meyn 23.8.2016, Finished 10.1.2017
*/

#include <iostream>
#include <string>

uint64_t    convertDecimal (std::string num,        short baseOld);
std::string convertBase    (uint64_t    num,        short baseNew);
void        baseInRange    (short       base);
int         stringToInt    (char        chr);
void        sizeMax        (short       &numLength, short i);
uint64_t    exponentiate   (short       base,       short exponent);

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
                std::cout << "Unknown value '" << num[i];
                std::cout << "' in base " << baseOld;
                std::cout << ". Exiting program..." << std::endl;
                
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
    short       numSize   {0};
    std::string numNew    (64, '0');
    std::string numRng    {"0123456789ABCDEF"};

    for(short i{0}; num; i++)
    {
        numMax = exponentiate(baseNew, i);
        numMin = exponentiate(baseNew, i - 1);

        //Checks for 'i != 0' because numMin >= numMax @i = 0(1 >= 1)
        if (numMin >= numMax && i != 0)
        {
            sizeMax(numSize, i);

            num          -= numMin;
            numNew[i - 1] = numRng[1];
            i             = 0;
        }

        if (numMax > num)
        {
            //Length of newNum stored using this
            sizeMax(numSize, i);

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
    for(;numSize > 0; numSize--)
    {
        std::cout << numNew[numSize - 1];
    }
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

//Determines the max length of num
void sizeMax(short &numSize, short i)
{
    if (numSize == 0)
    {
        numSize = i;
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
