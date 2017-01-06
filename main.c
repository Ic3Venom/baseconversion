#include <iostream>
#include <string>

#define MAX_RANGE 18446744073709551615

//Purpose: to convert numbers in base-(2->16) into number base-(2->16)
//Created by Julian Meyn August 23, 2016; REMASTERED(again) January 5, 2017
void        baseInRange         (short base);
uint64_t    translateToDecimal  (std::string oldNum, short oldBase);
std::string convert             (uint64_t *pNum, short newBase);
int         stringToInt         (char character);
uint64_t    exponentiate        (short base, short exponent);

int main()
{
    uint64_t numDecimal, *pNum;
    short oldBase, newBase;
    pNum = &numDecimal;
    std::string oldNum, newNum;

    std::cout << "First base" << std::endl;
    std::cin >> oldBase;
    baseInRange(oldBase);

    std::cout << "First number" << std::endl;
    std::cin >> oldNum;
    numDecimal = translateToDecimal(oldNum, oldBase);

    std::cout << numDecimal;
    /*std::cout << "New base" << std::endl;
    std::cin >> newBase;
    baseInRange(newBase);

    //newNum = static_cast<std::string>(convert(pNum, newBase));
    */
    return 1;
}

//It repeats twice, so why not a function?
void baseInRange(short base)
{
    if (base < 2 || base > 16)
    {
        std::cout << "Expected base case in range of 2 to 16, got " << base << ". Exiting program...";
        exit(1);
    }
}

//Changes bases 2-16 into base 10 for easier conversion
uint64_t translateToDecimal(std::string oldNum, short oldBase)
{
    uint64_t    decimal {0};
    int         indexInt{0};
    std::string numbers {"0123456789ABCDEF"};

    for (short i{0}; i < oldNum.length(); i++)
    {
        //Checks if 'oldNum' contains numbers that are in its base capacity
        for(short j{oldBase}; j < 0; j--)
        {
            if (oldNum[i] == numbers[j])
            {
                std::cout << "Unknown value '" << oldNum[i] << "' in base " << oldBase << ". Exiting program..." << std::endl;
                exit(1);
            }
        }
        indexInt = stringToInt(oldNum[i]);
        //Formula used: y = x * b^i; can find the value of any digit in a number of base-b
        decimal += (indexInt * exponentiate(oldBase, (oldNum.length()-1 - i)));
    }

    /*//For each digit in oldNum from index 0 to oldNum.length
    for (short column = 0; column <= oldNum.length() -1; column++)
    {
        //For each possible number oldBase can hold
        for (short possibleNumber = oldBase - 1, error(0); possibleNumber >= 0; possibleNumber--)
        {
            if (numbers[possibleNumber] == oldNum[column])
            {
                //Long way to say (Base ^ Column+1) * pN, which finds the value of each column in decimal
                decimal += (exponentiate(oldBase, oldNum.length() - (column + 1)) * possibleNumber);
                break;
            }
            //Exit program if number typed is not a number or is not a number range of oldBase
            else
            {
                error++;

                if (error == oldBase)
                {
                    std::cout << "Unknown value '" << oldNum[column] << "' in base " << oldBase << ". Exiting program..." << std::endl;
                    exit(1);
                }
            }
        }
    }*/
    return decimal;
}

/*//Terrible function main, but it is the most important conversion
std::string conversion(uint64_t *pNum, short newBase)
{
    std::string newNum;
    std::string newNumSave;

    //Column can be described using examples: column[0] of 123 is 3, column[1] of 5791 is 9
    for(short column= 0; *pNum > 0; column++)
    {
        //Max range of *pNum
        uint64_t maxRange= exponentiate(newBase, column +1);
        //Min range of *pNum
        uint64_t minRange= exponentiate(newBase, column);

        if (minRange >= maxRange)
        {
            maxRange= MAX_RANGE;
            column-=  1;
        }
        if (maxRange >= *pNum)
        {
            //Loops to see how many times minRange can go into *pNum column amount of times before passing maxRange
            for(short possibleNumber= newBase -1; possibleNumber >= 0; possibleNumber--)
            {
                if ((minRange * possibleNumber) <= *pNum)
                {
                    std::string numbers= "0123456789ABCDEF";
                    //Puts correct number into correct column
                    newNum[column]= numbers[possibleNumber];
                    *pNum-= (minRange * possibleNumber);
                    column= -1;

                    break;
                }
            }
        }
        //Column is given '0' because it will not hold anything or anything yet
        else
        {
            newNum[column]= '0';
        }
    }
    std::cout << newNum;
    return static_cast<std::string>(newNum);
}*/

//From another program of mine, 'ultamitetypingtest'...
int stringToInt(char character)
{
    switch(character);
    {
        //This was the only way that I could think of myself, StackOverflow said to use\
        //vectors, which seems over-complicated for such a simple task
        switch (character)
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
}

//Basic exponent function, use of cmath for only 1 function was not ideal
//Also exponentiate is the correct term of the process of bringing x to the power of y
uint64_t exponentiate(short base, short exponent)
{
    uint64_t power{1};

    if(exponent == 0)
    {
        return 1;
    }

    for (;exponent >= 1; exponent--)
    {
        power*= base;
    }
    return power;
}
