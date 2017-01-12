//Purpose: to convert numbers in base-(2->16) into number base-(2->16)
//Created by Julian Meyn August 23, 2016; REMASTERED(again) January 5, 2017
/*
    Necessary funcion/library declarations, can replace use of exponentiate function with cmath::pow()
        #include <string>
        #include <iostream>

        std::string numConvert     (std::string num,  short baseOld, short baseNew);
        uint64_t    convertDecimal (std::string num,  short baseOld);
        std::string convertString  (uint64_t    num,  short baseNew);
        int         stringToInt    (char        chr);
        uint64_t    exponentiate   (short       base, short exponent);
*/
std::string numConvert(std::string num, short baseOld, short baseNew)
{
    uint64_t numInt = convertDecimal(num, baseOld);
    num = convertString(numInt, baseNew);


    return num;
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
std::string convertString(uint64_t num, short baseNew)
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
            if (numSize == 0)
            {
                numSize = i;
            }

            num          -= numMin;
            numNew[i - 1] = numRng[1];
            i             = 0;
        }

        if (numMax > num)
        {
            //Length of newNum stored using this
            if (numSize == 0)
            {
                numSize = i;
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

    std::string numReturn (numSize, '0');

    for(short i{0}; i <= numSize; i++)
    {
        numReturn[numSize - i] = numNew[i - 1];
    }

    return numReturn;
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
