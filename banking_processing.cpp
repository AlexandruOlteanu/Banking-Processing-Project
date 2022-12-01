#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

#define DATABASE_LINK "database-users.txt"

struct date {
    int day;
    int month;
    int year;
};

struct card {
    string type;
    string currency;
    string number;
    string cvv;
    date expire_date;
    int pin;
    double ballance;
    double interest_rate;
};

class Account {
    public:
        int number_of_cards;
        string iban;
        vector<card> cards;
};

class User {
    public:
        string name;
        string unique_serial_number;
        date birth_date; 
        Account account;
};

class Database{
    public:
        int number_of_users;
        vector<User> users;
};

void read_date(date &date, ifstream &read);

void read_card_data(card &card, ifstream &read) {
    read >> card.type;
    read >> card.currency;
    read >> card.number;
    read >> card.cvv;
    read_date(card.expire_date, read);
    read >> card.pin;
    read >> card.ballance;
    read >> card.interest_rate;
}

void read_account_data(Account &account, ifstream &read) {
    read >> account.number_of_cards;
    read >> account.iban;
    for(int i = 1; i <= account.number_of_cards; ++i) {
        card current_card;
        read_card_data(current_card, read);
        account.cards.push_back(current_card);
    }
}

void read_date(date &date, ifstream &read) {
    read >> date.day >> date.month >> date.year;
}

void read_user_data(User &user, ifstream &read) {
    getline(read, user.name);
    if (user.name == "") {
        getline(read, user.name);
    }
    read >> user.unique_serial_number;
    read_date(user.birth_date, read);
    read_account_data(user.account, read);
}   

void read_existing_database(Database &database) {
    ifstream read (DATABASE_LINK);
    read >> database.number_of_users;
    for (int i = 1; i <= database.number_of_users; ++i) {
        User current_user;
        read_user_data(current_user, read);
        database.users.push_back(current_user);
    }
}

void display_welcome_message() {
    cout << "###########################################\n";
    cout << "#### Welcome to the International Bank ####\n";
    cout << "###########################################\n";
    cout << "\n\n";
}

void display_options() {
    cout << "Please select one of the following options:\n\n";
    cout << "1) Register an account\n";
    cout << "2) Log in with card details\n\n";

    cout << "Please type a number from 1 to 2: ";
}

void manage_account(Account &account) {

}


void login_user(Database &database) {

}

void register_user(Database &database) {

    User user;
    cout << "Welcome to the registering page!\n\n";
    cout << "Enter your name: ";
    
    string name;
    cin >> name;
    user.name = name;
    
    database.number_of_users++;
    database.users.push_back(user);
}

void write_card(card &card, ofstream &write) {

    write << card.type << '\n';
    write << card.currency << '\n';
    write << card.number << '\n';
    write << card.cvv << '\n';
    write << card.expire_date.day << " " << card.expire_date.month << " " << card.expire_date.year << '\n';
    write << card.pin << '\n';
    write << card.ballance << '\n';
    write << card.interest_rate << '\n';

}

void write_account(Account &account, ofstream &write) {
    write << account.number_of_cards << '\n';
    write << account.iban << '\n';
    for (auto card : account.cards) {
        write_card(card, write);
    }
}

void write_user(User &user, ofstream &write) {
    write << user.name << '\n';
    write << user.unique_serial_number << '\n';
    write << user.birth_date.day << " " << user.birth_date.month << " " << user.birth_date.year << '\n';
    write_account(user.account, write);
}

void update_database(Database &database) {

    ofstream write(DATABASE_LINK);
    write << database.number_of_users << '\n';

    for (auto user : database.users) {
        write_user(user, write);
    }

}

int main() {

    Database *database = new Database();
    read_existing_database(*database);
    display_welcome_message();
    while (true) {

        display_options();
        string option;
        cin >> option;
        if (option == "exit") {
            break;
        }
        if (option != "1" && option != "2") {
            cout << "Error, command unknown\n";
            continue;
        }
        else {
            cout << "You selected option number " << option << '\n';
            if (option == "1") {
                register_user(*database);
            }
            else {
                login_user(*database);
            }
        }
    }

    update_database(*database);


    return 0;
}