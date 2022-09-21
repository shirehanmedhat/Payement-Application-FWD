/*****************Name : Shirehan Medhat Abd elsalam  *****************/

#include<stdio.h>
#include"../Library/STDTYPES.h"
#include"Card.h"
//char count = 0;

EN_cardError_t getCardHolderName(ST_cardData_t* cardData)
{
    if (cardData != NULL) 
    {
        uint8_t i;
        printf("Enter your name? \n");
        scanf("%[^\n]%*c", cardData->cardHolderName);
        for (i = 0; cardData->cardHolderName[i] != '\0'; i++);
        if ((i > 20) && (i < 24))
        {
            return Card_OK;
        }
        else
        {
            return WRONG_NAME;
        }
    }

}


EN_cardError_t getCardPAN(ST_cardData_t* cardData)
{
    if (cardData != NULL)
    {
        uint8_t flag; // To check the input ascii
        uint8_t count = 0;  // counter

        //Scan the PAN
        printf("\nEnter the CardPAN\n");
        scanf("%s", &cardData->primaryAccountNumber[count]);

        // Count number of elements
        for (count = 0; cardData->primaryAccountNumber[count] != '\0'; count++);
       // put '\0' at the end of the pan 
        for (uint8_t i = count + 1; (i > count && i < 20); i++)
        {
            cardData->primaryAccountNumber[i] = '\0';
        }
        // Check the ascii Case "diits only"
        for (uint8_t q = 0; q < count; q++)
        {
            if ((cardData->primaryAccountNumber[q] >= '0') && (cardData->primaryAccountNumber[q] <= '9'))
            {
                flag = 1;
            }
            else
            {
                flag = 0;
                break;
            }
        }

        //Return the value depending On the number of elements and the ascii case for letters
        if ((count >=16) && (count <= 19) && (flag == 1))
        {
            return Card_OK;
        }
        else
        {
            return WRONG_NAME;
        }
    }

}

EN_cardError_t getCardExpiryDate(ST_cardData_t* cardData)
{
    if (cardData != NULL)
    {
        uint32_t  year, Month;
        //Get Month and Day from user
        printf("\nEnter the Card Expiry Date in the format MM/YY\n");
        scanf_s("%d", &Month);
        scanf_s(" %d", &year);
        //Check the validation of the date
        if (((Month <= 12)&&(year<100)))
        {

            // separate the Month variable into digits
            for (uint8_t i = 1; Month > 0; i--)
            {
                cardData->cardExpirationDate[i] = Month % 10;  // separate the last digit from the Month
                Month = Month / 10;                           // over flow will not occur as all the possible input values will never exceed 1 byte
                if ((Month == 0) && (i == 1))
                {
                    cardData->cardExpirationDate[0] = 0;
                }
            }

            cardData->cardExpirationDate[2] = '/';

            // separate the year variable into digits
            for (uint8_t i = 4; year > 0; i--)
            {
                cardData->cardExpirationDate[i] = year % 10; // separate the last digit from the year
                year = year / 10;
                if ((year == 0) && (i == 4))
                {
                    cardData->cardExpirationDate[3] = 0;
                }
            }

            return Card_OK;
        }
        else
        {
            return WRONG_EXP_DATE;
        }
    }

}

