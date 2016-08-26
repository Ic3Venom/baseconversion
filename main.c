#include <iostream>
#include <string>

void baseInRange(short base);
uint64_t translateToDecimal(uint64_t *pNum, short oldBase);
void convert(uint64_t *pNum, short newBase);
uint64_t exponentiate(short base, short exponent);

main()
{
    uint64_t num, *pNum;
    unsigned short oldBase, newBase;

    std::cout << "What base is the original number? (MIN is 2, MAX is 16)\n$ ";
    std::cin >> oldBase;
    baseInRange(oldBase);

    std::cout << "What number do you want converted? (MIN is 1, MAX is (2^64-1)-10)\n$ ";
    pNum = &num;
    num = translateToDecimal(pNum, oldBase);

    //Decided not to put a safeguard here because no higher or lower number can be in a uint64,
    //because num would just wrap around to some other number.

    std::cout << "What base would you like to convert into? (MIN is 2, MAX is 16)\n$ ";
    std::cin >> newBase;
    baseInRange(newBase);

    std::cout << "When translated from base " << oldBase << " into base " << newBase << ", your number becomes:\n  ";
    //Uses pointer pNum to pass u64int_t num to function convert()
    convert(pNum, newBase);
}
//It repeats twice, so why not a function?
void baseInRange(short base)
{
    if (base > 16 || base <= 1)
    {
        std::cout << "Expected base case in range of 2 to 16, got " << base << ". Exiting program...";
        exit(base);
    }
}
//Changes bases 2-16 into base 10 for easier conversion
uint64_t translateToDecimal(uint64_t *pNum, short oldBase)
{
    uint64_t decimal = 0;
    std::string num;

    std::cin >> num;
    //For each digit in num from index 0 to num.length
    for (short column(0); column <= num.length() - 1; column++)
    {
        //For each possible number oldBase can hold
        for (short possibleNumber(oldBase-1), error(0); possibleNumber >= 0; possibleNumber--)
        {
            std::string numbers = "0123456789ABCDEF";
            if (numbers[possibleNumber] == num[column])
            {
                //Long way to say (Base ^ Column+1) * pN, which finds the value of each column in decimal
                decimal += exponentiate(oldBase, num.length()-(column+1)) * possibleNumber;
                break;
            }
            //Exit program if number typed is not a number or is not a number range of oldBase
            else
            {
                error++;
                if (error == oldBase)
                {
                    std::cout << "Unknown value '" << num[column] << "' in base " << oldBase << ". Exiting program..." << std::endl;
                    exit(numbers[column]);
                }
            }
        }
    }
    return decimal;
}
//In this entire function, *pNum is called oldNum, because *pNum points to the old number given by user
void convert(uint64_t *pNum, short newBase)
{
    short length= 0;
    std::string newNum;

    uint64_t woweeeee = *pNum;
    //Column can be described using examples: column[0] of 123 is 3 / column[1] of 5791 is 9
    for(short column(0); woweeeee > 0; column++)
    {
        //Max range of oldNum
        uint64_t maxRange = exponentiate(newBase, column) -1;

        if (maxRange >= woweeeee)
        {
            //Min range of oldNum
            uint64_t minRange = exponentiate(newBase, column -1);

            //Loops to see how many times minRange can go into oldNum column amount of times before passing maxRange
            for(short possibleNumber = newBase-1; possibleNumber >= 0; possibleNumber--)
            {
                if ((minRange * possibleNumber) <= woweeeee && (minRange * possibleNumber) <= maxRange)
                {
                    if(!length)
                    {
                        length = column -1;
                    }
                    std::string numbers = "0123456789ABCDEF";
                    //Puts correct number into correct column
                    newNum[column]= numbers[possibleNumber];
                    woweeeee-= (minRange * possibleNumber);
                    column= 0;

                    break;
                }
            }
        }
        //Column is given '0' because it will not hold anything or anything yet
        else
        {
            newNum[column-1] = '0';
        }
    }

    //Prints 'column' amount of times
    for(;length >= 0; length--)
    {
        std::cout << newNum[length];
    }
}

//Basic exponent function, use of cmath for only 1 function was not ideal
//Also exponentiate is the correct term of the process of bringing x to the power of y
uint64_t exponentiate(short base, short exponent)
{
    uint64_t power = 1;

    for (;exponent >= 1; exponent--)
    {
        power *= base;
    }
    return power;
}
