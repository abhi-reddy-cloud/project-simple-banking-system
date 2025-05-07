https://github.com/abhi-reddy-cloud/LanguageTransulater
#include <stdio.h>
#include <string.h>

#define MAX_ACCOUNTS 100

struct Account {
    int accountNumber;
    char accountHolderName[100];
    float balance;
};

struct Bank {
    struct Account accounts[MAX_ACCOUNTS];
    int numAccounts;
};

void createAccount(struct Bank *bank) {
    if (bank->numAccounts < MAX_ACCOUNTS) {
        printf("Enter account number: ");
        scanf("%d", &bank->accounts[bank->numAccounts].accountNumber);
        
        // Clear the input buffer
        while (getchar() != '\n');

        printf("Enter account holder name: ");
        fgets(bank->accounts[bank->numAccounts].accountHolderName, sizeof(bank->accounts[bank->numAccounts].accountHolderName), stdin);
        // Remove trailing newline from the input
        bank->accounts[bank->numAccounts].accountHolderName[strcspn(bank->accounts[bank->numAccounts].accountHolderName, "\n")] = '\0';
        
        bank->accounts[bank->numAccounts].balance = 0.0;
        bank->numAccounts++;
        printf("Account created successfully!\n");
    } else {
        printf("Maximum number of accounts reached!\n");
    }
}

void deposit(struct Bank *bank) {
    int accountNumber;
    float amount;
    int found = 0;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < bank->numAccounts; i++) {
        if (bank->accounts[i].accountNumber == accountNumber) {
            printf("Enter amount to deposit: ");
            scanf("%f", &amount);
            bank->accounts[i].balance += amount;
            printf("Deposit successful! New balance: %.2f\n", bank->accounts[i].balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}

void withdraw(struct Bank *bank) {
    int accountNumber;
    float amount;
    int found = 0;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < bank->numAccounts; i++) {
        if (bank->accounts[i].accountNumber == accountNumber) {
            printf("Enter amount to withdraw: ");
            scanf("%f", &amount);
            if (amount > bank->accounts[i].balance) {
                printf("Insufficient balance!\n");
            } else {
                bank->accounts[i].balance -= amount;
                printf("Withdrawal successful! New balance: %.2f\n", bank->accounts[i].balance);
            }
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}

void deleteAccount(struct Bank *bank) {
    int accountNumber;
    int found = 0;

    printf("Enter account number to delete: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < bank->numAccounts; i++) {
        if (bank->accounts[i].accountNumber == accountNumber) {
            // Shift the accounts to the left to fill the gap
            for (int j = i; j < bank->numAccounts - 1; j++) {
                bank->accounts[j] = bank->accounts[j + 1];
            }
            bank->numAccounts--;
            printf("Account deleted successfully!\n");
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}

void displayAccounts(struct Bank *bank) {
    if (bank->numAccounts == 0) {
        printf("No accounts available!\n");
    } else {
        printf("Available Accounts:\n");
        for (int i = 0; i < bank->numAccounts; i++) {
            printf("Account Number: %d\n", bank->accounts[i].accountNumber);
            printf("Account Holder Name: %s\n", bank->accounts[i].accountHolderName);
            printf("Balance: %.2f\n\n", bank->accounts[i].balance);
        }
    }
}

void searchAccount(struct Bank *bank) {
    int accountNumber;
    int found = 0;

    printf("Enter account number to search: ");
    scanf("%d", &accountNumber);

    for (int i = 0; i < bank->numAccounts; i++) {
        if (bank->accounts[i].accountNumber == accountNumber) {
            printf("Account found!\n");
            printf("Account Number: %d\n", bank->accounts[i].accountNumber);
            printf("Account Holder Name: %s\n", bank->accounts[i].accountHolderName);
            printf("Balance: %.2f\n", bank->accounts[i].balance);
            found = 1;
            break;
        }
    }

    if (!found) {
        printf("Account not found!\n");
    }
}

int main() {
    struct Bank bank;
    bank.numAccounts = 0;
    int choice;

    while (1) {
        printf("\nBanking System Menu:\n");
        printf("1. Create Account\n");
        printf("2. Deposit\n");
        printf("3. Withdraw\n");
        printf("4. Delete Account\n");
        printf("5. Display Accounts\n");
        printf("6. Search Account\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                createAccount(&bank);
                break;
            case 2:
                deposit(&bank);
                break;
            case 3:
                withdraw(&bank);
                break;
            case 4:
                deleteAccount(&bank);
                break;
            case 5:
                displayAccounts(&bank);
                break;
            case 6:
                searchAccount(&bank);
                break;
            case 7:
                printf("Exiting...\n");
                return 0;
            default:
                printf("Invalid choice! Please try again.\n");
        }
    }

    return 0;
}