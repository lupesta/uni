#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

// Global variables
int CurrentUser = 0;
float CurrentAccountBalance = 500.00;
float SavingsAccountBalance = 500.00;
int SavingChoice;
int AccountChoice;
int AccountChoiceMenu;

int CompareNewID;
int CompareNewPIN;
int IsIDValid = 0;
int IsPINValid = 0;
int AttemptsLeft = 2;
int AttemptsLeft2 = 3;

int testID = 246800;
int testPIN = 1357;
int NewID;
int userPIN;
int loopCountFor;
int loopCountDo = 1;
int IDAttempts = 0;
int z = 1;
int regalready = 0;

char FirstName[20];
char LastName[20];

// Struct for a new user
struct NewUser {
    char FirstName[20];
    char LastName[20];
    char DateOFBirth[30];
    int NewID;
    int NewPIN;
    float NewCurrentBalance;
    float NewStandardISABalance;
    float NewISASharesBalance;
    float NewISACashBalance;
    int formCurrent;
    int formSavings;
    int formISACash;
    int formISAShares;
};

// Array to store user accounts
struct NewUser Accounts[20];

// Function to view balance
void viewbalance() {
    int Menu2Selection;

    printf("Which account balance would you like to view?\n");
    printf("1\tCurrent Account\n");
    printf("2\tRegular Savings Account\n");
    printf("3\tStocks ISA\n");
    printf("4\tCash ISA\n");

    scanf("%d", &Menu2Selection);

    switch (Menu2Selection) {
        case 1:
            if (Accounts[CurrentUser].formCurrent == 1) {
                printf("The balance of the current account in GBP is %.2f GBP\n", Accounts[CurrentUser].NewCurrentBalance);
            } else {
                printf("A current account has not been registered\n");
            }
            break;
        case 2:
            if (Accounts[CurrentUser].formSavings == 1) {
                printf("The balance of the savings account in GBP is %.2f GBP\n", Accounts[CurrentUser].NewStandardISABalance);
            } else {
                printf("A savings account has not been registered\n");
            }
            break;
        case 3:
            if (Accounts[CurrentUser].formISAShares == 1) {
                printf("The balance of the ISA stocks and shares account in GBP is %.2f GBP\n", Accounts[CurrentUser].NewISASharesBalance);
            } else {
                printf("A stocks and shares ISA account has not been registered\n");
            }
            break;
        case 4:
            if (Accounts[CurrentUser].formISACash == 1) {
                printf("The balance of the ISA cash account in GBP is %.2f GBP\n", Accounts[CurrentUser].NewISACashBalance);
            } else {
                printf("A cash ISA account has not been registered\n");
            }
            break;
        default:
            printf("Invalid choice, please enter a value between 1 and 4\n");
            break;
    }
}

// Function to withdraw money
void withdrawmoney() {
    float withdraw = 0.00;
    int Menu2Selection;
    printf("\nWhich account would you like to withdraw from\n");
    printf("1\tThe Current Account\n");
    printf("2\tThe Savings Account\n");
    printf("3\tThe Stocks and Savings ISA\n");
    printf("4\tThe Cash ISA\n");
    scanf("%d", &Menu2Selection);

    if (Menu2Selection == 1) {
        printf("How much money from the current account would you like to withdraw?\n");
        scanf("%f", &withdraw);

        if (withdraw < 0) {
            printf("A negative value cannot be withdrawn from the account\n");
        } else if (withdraw > Accounts[CurrentUser].NewCurrentBalance || Accounts[CurrentUser].formCurrent == 0) {
            printf("The transaction was unable to be processed due to either too little account funds or you do not have an account registered of that type\n");
        } else {
            Accounts[CurrentUser].NewCurrentBalance -= withdraw;
            printf("The new current account balance is %.2f GBP\n", Accounts[CurrentUser].NewCurrentBalance);
        }
    } else if (Menu2Selection == 2) {
        printf("\nHow much would you like to withdraw from the savings account?\n");
        scanf("%f", &withdraw);

        if (withdraw < 0) {
            printf("A negative value cannot be withdrawn from the account\n");
        } else if (withdraw > Accounts[CurrentUser].NewStandardISABalance || Accounts[CurrentUser].formSavings == 0) {
            printf("The transaction was unable to be processed due to either too little account funds or you do not have an account registered of that type\n");
        } else {
            Accounts[CurrentUser].NewStandardISABalance -= withdraw;
            printf("Your new Standard ISA Account Balance is %.2f GBP\n", Accounts[CurrentUser].NewStandardISABalance);
        }
    } else if (Menu2Selection == 3) {
        printf("How much would you like to withdraw from the Stocks ISA?\n");
        scanf("%f", &withdraw);

        if (withdraw < 0) {
            printf("A negative value cannot be withdrawn from the account\n");
        } else if (withdraw > Accounts[CurrentUser].NewISASharesBalance || Accounts[CurrentUser].formISAShares == 0) {
            printf("The transaction was unable to be processed due to either too little account funds or you do not have an account registered of that type\n");
        } else {
            Accounts[CurrentUser].NewISASharesBalance -= withdraw;
            printf("Your new ISA Shares balance is %.2f GBP\n", Accounts[CurrentUser].NewISASharesBalance);
        }
    } else {
        printf("\nHow much would you like to withdraw from the cash ISA account: \n");
        scanf("%f", &withdraw);

        if (withdraw < 0) {
            printf("A negative value cannot be withdrawn from the account\n");
        } else if (withdraw > Accounts[CurrentUser].NewISACashBalance || Accounts[CurrentUser].formISACash == 0) {
            printf("The transaction was unable to be processed due to either too little account funds or you do not have an account registered of that type\n");
        } else {
            Accounts[CurrentUser].NewISACashBalance -= withdraw;
            printf("Your new current account balance is %.2f GBP\n", Accounts[CurrentUser].NewISACashBalance);
        }
    }
}

// Function to deposit money
void depositmoney() {
    float deposit = 0.00;
    int Menu2Selection;
    printf("\nWhich account would you like to deposit your money into\n");
    printf("1\t Into the Current Account\n");
    printf("2\t Into the Savings Account\n");
    printf("3\t Into the Stocks ISA Account\n");
    printf("4\t Into the Cash ISA Account\n");
    scanf("%d", &Menu2Selection);

    if (Menu2Selection == 1) {
        printf("\nHow much money in GBP would you like to deposit into the current account?\n");
        scanf("%f", &deposit);

        if (deposit < 0) {
            printf("A negative value cannot be deposited into the account\n");
        } else if (Accounts[CurrentUser].formCurrent == 1) {
            Accounts[CurrentUser].NewCurrentBalance += deposit;
            printf("Your new current account balance is %.2f GBP\n", Accounts[CurrentUser].NewCurrentBalance);
        } else {
            printf("You do not have a registered Current Account\n");
        }
    } else if (Menu2Selection == 2) {
        printf("\nHow much money in GBP would you like to deposit into the savings account?\n");
        scanf("%f", &deposit);

        if (deposit < 0) {
            printf("A negative value cannot be deposited into the account\n");
        } else if (Accounts[CurrentUser].formSavings == 1) {
            Accounts[CurrentUser].NewStandardISABalance += deposit;
            printf("Your new savings account balance is %.2f GBP\n", Accounts[CurrentUser].NewStandardISABalance);
        } else {
            printf("You do not have a registered Savings Account\n");
        }
    } else if (Menu2Selection == 3) {
        printf("How much money in GBP would you like to deposit into the stocks ISA?\n");
        scanf("%f", &deposit);

        if (deposit < 0) {
            printf("A negative value cannot be deposited into the account\n");
        } else if (Accounts[CurrentUser].formISAShares == 1) {
            Accounts[CurrentUser].NewISASharesBalance += deposit;
            printf("Your new stocks ISA account balance is %.2f GBP\n", Accounts[CurrentUser].NewISASharesBalance);
        } else {
            printf("You do not have a registered Stocks ISA\n");
        }
    } else if (Menu2Selection == 4) {
        printf("\nHow much money would you like to deposit into the cash ISA?\n");
        scanf("%f", &deposit);

        if (deposit < 0) {
            printf("A negative value cannot be deposited into the account\n");
        } else if (Accounts[CurrentUser].formISACash == 1) {
            Accounts[CurrentUser].NewISACashBalance += deposit;
            printf("The new cash ISA account balance is %.2f GBP\n", Accounts[CurrentUser].NewISACashBalance);
        } else {
            printf("You do not have a registered Cash ISA\n");
        }
    } else {
        printf("Invalid choice, please enter a value between 1 and 4\n");
    }
}

// Function to transfer money between accounts
void transfermoney() {
    int transferfrom;
    int transferto;
    float transfer;
    printf("\nPlease choose one of the following accounts to transfer money from\n");
    printf("1\tFrom the Current Account\n");
    printf("2\tFrom the Savings Account\n");
    printf("3\tFrom the Cash ISA\n");
    printf("4\tFrom the Stocks ISA\n");
    scanf("%d", &transferfrom);

    printf("\nPlease choose one of the following accounts to transfer money to\n");
    printf("1\tTo the Current Account\n");
    printf("2\tTo the Savings Account\n");
    printf("3\tTo the Cash ISA\n");
    printf("4\tTo the Stocks ISA\n");
    scanf("%d", &transferto);

    printf("\nHow much would you like to transfer? \n");
    scanf("%f", &transfer);

    // Deduct the transfer amount from the selected account
    if (transferfrom == 1 && transfer <= Accounts[CurrentUser].NewCurrentBalance && Accounts[CurrentUser].formCurrent == 1) {
        Accounts[CurrentUser].NewCurrentBalance -= transfer;
        printf("The transfer between the two accounts is complete\n");
    } else if (transferfrom == 2 && transfer <= Accounts[CurrentUser].NewStandardISABalance && Accounts[CurrentUser].formSavings == 1) {
        Accounts[CurrentUser].NewStandardISABalance -= transfer;
        printf("The transfer between the two accounts is complete\n");
    } else if (transferfrom == 3 && transfer <= Accounts[CurrentUser].NewISACashBalance && Accounts[CurrentUser].formISACash == 1) {
        Accounts[CurrentUser].NewISACashBalance -= transfer;
        printf("The transfer between the two accounts is complete\n");
    } else if (transferfrom == 4 && transfer <= Accounts[CurrentUser].NewISASharesBalance && Accounts[CurrentUser].formISAShares == 1) {
        Accounts[CurrentUser].NewISASharesBalance -= transfer;
        printf("The transfer between the two accounts is complete\n");
    } else {
        printf("The transaction was unable to be processed due to either too little account funds or you do not have an account registered of that type\n");
        return;
    }

    // Add the transfer amount to the selected account
    if (transferto == 1 && transferfrom != 1 && Accounts[CurrentUser].formCurrent == 1) {
        Accounts[CurrentUser].NewCurrentBalance += transfer;
    } else if (transferto == 2 && transferfrom != 2 && Accounts[CurrentUser].formSavings == 1) {
        Accounts[CurrentUser].NewStandardISABalance += transfer;
    } else if (transferto == 3 && transferfrom != 3 && Accounts[CurrentUser].formISACash == 1) {
        Accounts[CurrentUser].NewISACashBalance += transfer;
    } else if (transferto == 4 && transferfrom != 4 && Accounts[CurrentUser].formISAShares == 1) {
        Accounts[CurrentUser].NewISASharesBalance += transfer;
    } else {
        printf("The transaction was unable to be processed due to either too little account funds or you do not have an account registered of that type\n");
    }
}

// Function to display account options menu
void AccountsMenu() {
    int MenuSelection;

    printf("Please select what you would like to do\n");
    printf("1\t Display Account Balance\n");
    printf("2\tWithdraw money from the account\n");
    printf("3\tDeposit money into the account\n");
    printf("4\tTransfer money into the account\n");
    scanf("%d", &MenuSelection);

    switch (MenuSelection) {
        case 1:
            viewbalance();
            break;
        case 2:
            withdrawmoney();
            break;
        case 3:
            depositmoney();
            break;
        case 4:
            transfermoney();
            break;
        default:
            printf("Invalid choice, please enter a value between 1 and 4\n");
            break;
    }
}

// Function to register a new account
void registernewaccount() {
    static int NoOfAccounts = 0;  // Static variable to keep track of the number of accounts
    int OpenNewAccount;

    NoOfAccounts++;
    if (NoOfAccounts > 20) {
        printf("The maximum number of users that can register to the bank is 20\n");
    } else {
        Accounts[NoOfAccounts].NewISASharesBalance = 0;
        Accounts[NoOfAccounts].NewISACashBalance = 0;
        Accounts[NoOfAccounts].NewStandardISABalance = 0;
        Accounts[NoOfAccounts].NewCurrentBalance = 0;

        printf("We would first like you to enter your first name\n");
        scanf("%s", Accounts[NoOfAccounts].FirstName);

        printf("Please may you now enter your last name onto the database\n");
        scanf("%s", Accounts[NoOfAccounts].LastName);

        printf("Please may you now enter your date of birth (dd/mm/yyyy)\n");
        scanf("%s", Accounts[NoOfAccounts].DateOFBirth);

        printf("\nPlease now enter an ID for the account\n");
        scanf("%d", &CompareNewID);
        while (CompareNewID < 111111 || CompareNewID > 999999) {
            printf("\nIt must be 6 numbers long, please enter a new ID: \n");
            scanf("%d", &CompareNewID);
        }
        Accounts[NoOfAccounts].NewID = CompareNewID;

        printf("Please now enter a pin for the account, which must be 4 digits long\n");
        scanf("%d", &CompareNewPIN);
        while (CompareNewPIN < 1111 || CompareNewPIN > 9999) {
            printf("\nYour password must be 4 numbers long, please enter a new password\n");
            scanf("%d", &CompareNewPIN);
        }
        Accounts[NoOfAccounts].NewPIN = CompareNewPIN;

        printf("It is now required for you to choose an account to open\n");
        printf("1\t Stock and Shares ISA\n");
        printf("2\t Cash ISA\n");
        printf("3\t Regular savings account\n");
        printf("4\t Current Account\n");
        scanf("%d", &AccountChoice);

        switch (AccountChoice) {
            case 1:
                if (Accounts[NoOfAccounts].formISAShares == 0 && Accounts[NoOfAccounts].formISACash == 0) {
                    Accounts[NoOfAccounts].formISAShares = 1;
                    printf("A new stocks ISA account has been created\n");
                } else {
                    printf("You are only allowed one ISA account, which is not allowed, so account registration must restart\n");
                }
                break;
            case 2:
                if (Accounts[NoOfAccounts].formISACash == 0 && Accounts[NoOfAccounts].formISAShares == 0) {
                    Accounts[NoOfAccounts].formISACash = 1;
                    printf("A new cash ISA account has been created\n");
                } else {
                    printf("You are only allowed one ISA account, which is not allowed, so account registration must restart\n");
                }
                break;
            case 3:
                if (Accounts[NoOfAccounts].formSavings == 0) {
                    Accounts[NoOfAccounts].formSavings = 1;
                    printf("A new regular savings account has been created\n");
                } else {
                    printf("You already have a savings account\n");
                }
                break;
            case 4:
                if (Accounts[NoOfAccounts].formCurrent == 0) {
                    Accounts[NoOfAccounts].formCurrent = 1;
                    printf("A new current account has been created\n");
                } else {
                    printf("You already have a current account\n");
                }
                break;
            default:
                printf("Invalid choice, please enter a value between 1 and 4\n");
                break;
        }
    }
}

// Function to re-login to the system
void relogin() {
    printf("\nPlease can you now enter your ID number\n");
    scanf("%d", &NewID);

    int CurrentNewID;
    int CurrentUserPIN;
    int findElement;

    // Search for the user ID in the accounts array
    for (findElement = 0; findElement < 20; findElement++) {
        if (Accounts[findElement].NewID == NewID) {
            CurrentNewID = Accounts[findElement].NewID;
            CurrentUserPIN = Accounts[findElement].NewPIN;
            CurrentUser = findElement;
            break;
        }
    }

    // If the ID is not found, prompt the user to re-enter the ID
    if (NewID != Accounts[CurrentUser].NewID && NewID != testID) {
        for (loopCountFor = 1; loopCountFor <= 2; ++loopCountFor) {
            IDAttempts++;
            printf("The ID number you have entered is not in the database, please try again\n");
            scanf("%d", &NewID);
            if (NewID == testID || NewID == Accounts[CurrentUser].NewID) {
                break;
            }
        }
    }

    if (NewID == CurrentNewID) {
        CurrentUser = 1;
    }

    if (IDAttempts <= 2) {
        printf("ID successfully found\n");
    } else {
        printf("Please contact the system administrator as you have now been locked out of this account due to suspicious activity\n");
        exit(1);
    }

    printf("It is now required for you to enter your PIN\n");
    scanf("%d", &userPIN);

    while (z == 1) {
        if (userPIN >= 1000 && userPIN <= 9999) {
            break;
        } else {
            printf("\nThe PIN needs to be 4 digits long to meet the requirements\n");
            scanf("%d", &userPIN);
        }
    }

    if (userPIN != testPIN && userPIN != CurrentUserPIN) {
        do {
            AttemptsLeft2--;
            printf("You have %d attempts left\n", AttemptsLeft2);
            printf("The PIN you have entered is not valid\n");
            scanf("%d", &userPIN);

            while (z == 1) {
                if (userPIN >= 1000 && userPIN <= 9999) {
                    break;
                } else {
                    printf("Please make sure the PIN is 4 digits long to meet the requirements\n");
                    scanf("%d", &userPIN);
                }
            }

            if (userPIN == testPIN || userPIN == CurrentUserPIN) {
                printf("The pin has been entered successfully so you have now logged in\n");
                break;
            }
            AttemptsLeft--;
        } while (AttemptsLeft > 0);

        if (AttemptsLeft == 0) {
            printf("Please contact the system administrator as you have now been locked out of this account due to suspicious activity\n");
            exit(1);
        }
    } else {
        printf("You have successfully logged onto Lukes bank\n");
    }
}

// Main function
int main() {
    int leavemain = 0;

    int SavingChoice;
    int AccountChoice;
    int AccountChoiceMenu;

    int CompareNewID;
    int CompareNewPIN;
    int IsIDValid = 0;
    int IsPINValid = 0;

    int testID = 246800;
    int testPIN = 1357;
    int NewID;
    int userPIN;
    int loopCountFor;
    int loopCountDo = 1;
    int IDAttempts = 0;
    int AttemptsLeft = 2;
    int AttemptsLeft2 = 3;
    int z = 1;
    int regalready = 0;

    char FirstName[20];
    char LastName[20];

    printf("Hello and welcome to Lukes bank login system\n");
    printf("You will either have to create a new account or login to an existing one\n");

    int OpenNewAccount = 0;
    int NoOfAccounts = 0;
    int CurrentNewID;
    int CurrentUserPIN;

    do {
        printf("Do you wish to create a new account\n");
        printf("1\tYes\n");
        printf("2\tNo\n");
        printf("3\tExit the program\n");
        scanf("%d", &regalready);

        if (regalready == 1) {
            registernewaccount();
        } else if (regalready == 2) {
            relogin();
        } else {
            printf("Thank you for using the system. Goodbye!\n");
            exit(0);
        }

        printf("\nPlease can you now enter your ID number\n");
        scanf("%d", &NewID);

        int findElement;

        for (findElement = 0; findElement < 20; findElement++) {
            if (Accounts[findElement].NewID == NewID) {
                CurrentNewID = Accounts[findElement].NewID;
                CurrentUserPIN = Accounts[findElement].NewPIN;
                CurrentUser = findElement;
                break;
            }
        }

        if (NewID != Accounts[CurrentUser].NewID && NewID != testID) {
            for (loopCountFor = 1; loopCountFor <= 2; ++loopCountFor) {
                IDAttempts++;
                printf("The ID number you have entered is not in the database, please try again\n");
                scanf("%d", &NewID);
                if (NewID == testID || NewID == Accounts[CurrentUser].NewID) {
                    break;
                }
            }
        }

        if (NewID == CurrentNewID) {
            CurrentUser = 1;
        }

        if (IDAttempts <= 2) {
            printf("ID successfully found\n");
        } else {
            printf("Please contact the system administrator as you have now been locked out of this account due to suspicious activity\n");
            exit(1);
        }

        printf("It is now required for you to enter your PIN\n");
        scanf("%d", &userPIN);

        while (z == 1) {
            if (userPIN >= 1000 && userPIN <= 9999) {
                break;
            } else {
                printf("\nThe PIN needs to be 4 digits long to meet the requirements\n");
                scanf("%d", &userPIN);
            }
        }

        if (userPIN != testPIN && userPIN != CurrentUserPIN) {
            do {
                AttemptsLeft2--;
                printf("You have %d attempts left\n", AttemptsLeft2);
                printf("The PIN you have entered is not valid\n");
                scanf("%d", &userPIN);

                while (z == 1) {
                    if (userPIN >= 1000 && userPIN <= 9999) {
                        break;
                    } else {
                        printf("Please make sure the PIN is 4 digits long to meet the requirements\n");
                        scanf("%d", &userPIN);
                    }
                }

                if (userPIN == testPIN || userPIN == CurrentUserPIN) {
                    printf("The pin has been entered successfully so you have now logged in\n");
                    break;
                }
                AttemptsLeft--;
            } while (AttemptsLeft > 0);

            if (AttemptsLeft == 0) {
                printf("Please contact the system administrator as you have now been locked out of this account due to suspicious activity\n");
                return 0;
            }
        } else {
            printf("You have successfully logged onto Lukes bank\n");
        }

        int PersonalDetailsOption1;
        int exit = 0;
        int ValidatePin = 0;
        int PersonalDetailsOption2 = 0;

        char name[30];
        char address[50];
        char DateOFBirth[20];
        int NewPIN;
        char UserChoice;

        printf("Please choose one of the four options from below\n");

        do {
            printf("1\tUpdate your information\n");
            printf("2\tSelect an Account\n");
            printf("3\tRegister a new account\n");
            printf("4\tExit current user\n");
            scanf("%s", &UserChoice);

            switch (UserChoice) {
                case '1':
                    printf("You have chosen to update user information\n");
                    printf("1\tChange the PIN\n");
                    printf("2\tChange your personal details\n");
                    scanf("%d", &PersonalDetailsOption1);

                    if (PersonalDetailsOption1 == 1) {
                        while (ValidatePin == 0) {
                            printf("Please can you enter a new pin for this account\n");
                            scanf("%d", &NewPIN);
                            if (NewPIN >= 1000 && NewPIN <= 9999) {
                                if (CurrentUser == 1) {
                                    Accounts[NoOfAccounts].NewPIN = NewPIN;
                                } else {
                                    testPIN = NewPIN;
                                }
                                printf("Your PIN has been successfully changed, the new PIN is %d\n", NewPIN);
                                ValidatePin = 1;
                            } else {
                                printf("Please make sure the PIN is 4 digits long to meet the requirements\n");
                            }
                        }
                    } else if (PersonalDetailsOption1 == 2) {
                        printf("Which of your personal details would you like to update\n");
                        printf("1\tYour Name\n");
                        printf("2\tYour Address\n");
                        printf("3\tYour Date of Birth\n");
                        scanf("%d", &PersonalDetailsOption2);
                        switch (PersonalDetailsOption2) {
                            case 1:
                                if (CurrentUser == 1) {
                                    printf("Please can you enter your first name\n");
                                    scanf("%s", Accounts[CurrentUser].FirstName);
                                    printf("Please can you enter your last name\n");
                                    scanf("%s", Accounts[CurrentUser].LastName);
                                } else {
                                    printf("Please now enter your name\n");
                                    scanf("%s", name);
                                    printf("The name for this account is now %s\n", name);
                                }
                                break;
                            case 2:
                                printf("Now may you please enter your address\n");
                                scanf("%s", address);
                                printf("The new address is: %s\n", address);
                                break;
                            case 3:
                                if (CurrentUser == 1) {
                                    printf("Now may you please enter your date of birth (DD/MM/YYYY)\n");
                                    scanf("%s", Accounts[CurrentUser].DateOFBirth);
                                } else {
                                    printf("Now may you please enter your date of birth (DD/MM/YYYY)\n");
                                    scanf("%s", DateOFBirth);
                                }
                                printf("The new date of birth is %s\n", DateOFBirth);
                                break;
                            default:
                                printf("Invalid choice, please enter a value between 1 and 3\n");
                                break;
                        }
                    }
                    break;
                case '2':
                    AccountsMenu();
                    break;
                case '3':
                    printf("What kind of account would you like to register for\n");
                    printf("1\tStock and Shares ISA\n");
                    printf("2\tCash ISA\n");
                    printf("3\tRegular savings account\n");
                    printf("4\tCurrent Account\n");
                    scanf("%d", &AccountChoiceMenu);

                    switch (AccountChoiceMenu) {
                        case 1:
                            if (Accounts[CurrentUser].formISAShares == 0 && Accounts[CurrentUser].formISACash == 0) {
                                Accounts[CurrentUser].formISAShares = 1;
                                printf("A stocks ISA account has now been opened\n");
                            } else {
                                printf("You are only allowed one ISA account, which is not allowed, so account registration must restart\n");
                            }
                            break;
                        case 2:
                            if (Accounts[CurrentUser].formISACash == 0 && Accounts[CurrentUser].formISAShares == 0) {
                                Accounts[CurrentUser].formISACash = 1;
                                printf("A cash ISA account has now been opened\n");
                            } else {
                                printf("You are only allowed one ISA account, which is not allowed, so account registration must restart\n");
                            }
                            break;
                        case 3:
                            if (Accounts[CurrentUser].formSavings == 0) {
                                Accounts[CurrentUser].formSavings = 1;
                                printf("A regular savings account has now been opened\n");
                            } else {
                                printf("A savings account is already what you have\n");
                            }
                            break;
                        case 4:
                            if (Accounts[CurrentUser].formCurrent == 0) {
                                Accounts[CurrentUser].formCurrent = 1;
                                printf("A regular current account has now been opened\n");
                            } else {
                                printf("A current account is already what you have\n");
                            }
                            break;
                        default:
                            printf("Invalid choice, please enter a value between 1 and 4\n");
                            break;
                    }
                    break;
                case '4':
                    printf("Thank you for visiting Lukes bank, we hope you become a long term customer\n");
                    leavemain = 1;
                    break;
                default:
                    printf("Invalid number entered - you must enter a number between one and four\n");
                    break;
            }
        } while (leavemain == 0);
    } while (leavemain == 0);

    return 0;
}
