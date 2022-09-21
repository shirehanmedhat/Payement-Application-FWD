/*****************Name : Shirehan Medhat Abd elsalam  *****************/
#include<stdio.h>
#include"../Library/STDTYPES.h"
#include "../Card/Card.h"
#include"../Terminal/Terminal.h"
#include"Server.h"
ST_accountsDB_t DatBase[255] = { {200.0 ,"11111222221111122"},
                             {9000.0    ,"11221122112211221"},
                             {8000.0     ,"11111000001111100"},
                             {5000.0    ,"363636363636363636"},
                             {3000.0    ,"00000000000000000"},
};
ST_transaction UpdatedData[255] = { 0 };
int flag;
int FLAG;
uint8_t seq = 0;

EN_serverError_t isValidAccount(ST_cardData_t* cardData)
{  
    if (cardData != NULL)
    {
        for (uint8_t i = 0; i < 5; i++)
        {
            for (uint8_t x = 0; x < 20; x++)
            {
                if (cardData->primaryAccountNumber[x] == DatBase[i].primaryAccountNumber[x])
                {
                    flag = 1;
                }
                else if (cardData->primaryAccountNumber[x] != DatBase[i].primaryAccountNumber[x])
                {
                    flag = 0;
                    break;
                }

            }
            if (flag == 1)
            {
                buffer = i;
                break;
            }

        }

        if (flag == 1)
        {

            return Server_OK;

        }
        else if (flag == 0)
        {
            FLAG = 2;

            return DECLINED_STOLEN_CARD;
        }
    }
}

EN_serverError_t isAmountAvailable(ST_terminalData_t* termData)
{
    if (termData != NULL)
    {
        if ((termData->transAmount) <= (DatBase[buffer].balance))
        {
            
            return Server_OK;
        }
        else
        {
            printf("DECLINED INSUFFECIENTFUND");
            FLAG = 3;
            return LOW_BALANCE;
        }

    }

}

EN_serverError_t saveTransaction(ST_transaction* transData)
{
    if (transData != NULL)
    {
        

        UpdatedData[seq].cardHolderData = transData->cardHolderData;
        UpdatedData[seq].terminalData = transData->terminalData;
        DatBase[buffer].balance = DatBase[buffer].balance - transData->terminalData.transAmount;
        UpdatedData[seq].transactionSequenceNumber = seq;
        if (FLAG == 1)
        {
            UpdatedData[seq].transState = APPROVED;
            seq++;
        }
        else if (FLAG == 2)
        {
            UpdatedData[seq].transState = DECLINED_STOLEN_CARD;
            seq++;
        }
        else if (FLAG == 3)
        {
            UpdatedData[seq].transState = LOW_BALANCE;
            seq++;
        }

    }

}




EN_transStat_t recieveTransactionData(ST_transaction* transData)
{ 
    if (transData != NULL)
    {
        //ST_cardData_t* CARD = &transData->cardHolderData.primaryAccountNumber;
        ST_terminalData_t* amount = &transData->terminalData.transAmount;

        //EN_serverError_t check_PAN = isValidAccount(CARD);
        EN_serverError_t check_Amount = isAmountAvailable(amount);
        EN_serverError_t SAVE = saveTransaction(transData);

        if (SAVE == APPROVED)
        {

            return APPROVED;
        }
        else if (SAVE == DECLINED_STOLEN_CARD)
        {
            return DECLINED_STOLEN_CARD;
        }
        else if (SAVE == LOW_BALANCE)
        {
            return LOW_BALANCE;
        }
    }


}

