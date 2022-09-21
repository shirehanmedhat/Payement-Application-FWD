#include <stdio.h>
#include "../Card/Card.h"
#include "../Terminal/Terminal.h"
#include"../Server/Server.h"

void main(void)
{   //Step (1) : -> Ask for the User Name
    ST_cardData_t CardInputs;
    ST_cardData_t* PtrToCardInputs;
    PtrToCardInputs = &CardInputs;
    EN_cardError_t Name = getCardHolderName(PtrToCardInputs);

    if (Name == Card_OK)
    {
        //Step (2) : -> Ask for the Expiration Date 

        EN_cardError_t ExpiryDate = getCardExpiryDate(PtrToCardInputs);
        if (ExpiryDate == Card_OK)
        {
            // Step(3) :->Get the PAN Number 
          
            EN_cardError_t PANCheck = getCardPAN(PtrToCardInputs);
            if (PANCheck == Card_OK)
            {
                // Step(4) : -> Get the Transcation Date 
                ST_terminalData_t transsactionDate;
                ST_terminalData_t* PtrToTranssactionDate;
                PtrToTranssactionDate = &transsactionDate;
                ;
                EN_terminalError_t ReturnFromTransDate = getTransactionDate(PtrToTranssactionDate);
                if (ReturnFromTransDate == terminal_OK)
                {

                    // Step(5) : -> compare dates
                    EN_terminalError_t CheckVal = isCardExpired(CardInputs, transsactionDate);
                    if (CheckVal == terminal_OK)
                    {
                        // Step(6) : -> Get The Transaction Amount
                        
                        EN_terminalError_t AmmountCheck = getTransactionAmount(PtrToTranssactionDate);
                        if (AmmountCheck == terminal_OK)
                        {
                            // Step(7) : -> Set Max Amount
                            EN_terminalError_t SetMaxCheck = setMaxAmount(PtrToTranssactionDate);
                            if (SetMaxCheck == terminal_OK)
                            {

                                // Step(8) : ->Check Below The Limitation
                                EN_terminalError_t BelowCheck = isBelowMaxAmount(PtrToTranssactionDate);
                                if (BelowCheck == terminal_OK)
                                {

                                    // Step(9) : ->check the recieved PAN 
                                    EN_serverError_t checkPanVar = isValidAccount(PtrToCardInputs);

                                    if (checkPanVar == Server_OK)
                                    {                                        
                                        //Step(10) : -> save the Transaction 
                                        ST_transaction trans;
                                        trans.cardHolderData = CardInputs;
                                        ST_transaction* PtrTotrans;
                                        PtrTotrans = &trans;
                                        PtrTotrans->terminalData.transAmount = PtrToTranssactionDate->transAmount;
                                        EN_transStat_t recieve_Data = recieveTransactionData(PtrTotrans);
                                        if (recieve_Data == APPROVED)
                                        {
                                            printf("\nProcess is Done\nPASSED\n");
                                        }


                                    }
                                    //OF step (9) -> valid account
                                    else
                                    {
                                        printf("\nDECLINED STOLEN CARD");
                                    }


                                }
                                //OF step (8) -> Below Max Amount
                                else
                                {
                                    printf("\n Error Exeeding Limit\n");
                                }
                            }

                        }
                        //OF step (6) -> Get Transaction Amount
                        else if (AmmountCheck == INVALID_AMOUNT)
                        {
                            printf("\nInvalid Ammaount\n");
                        }
                    }
                    //OF step (5) -> Card Is Expired
                    else
                    {
                        printf("\nCard Is Expired\n");
                    }
                }

            }
            //OF step (3) -> Invalid Pan Format
            else
            {
                printf("\nIn Valid PAN Format\n");
            }



        }
        

    }
    //OF step (1) -> Invalid Name Format
    else
    {
        printf("\n wrong Name Format");
    }




}




