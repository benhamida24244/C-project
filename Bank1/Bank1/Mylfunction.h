#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <fstream>
#include <limits>
using namespace std;

namespace myfun {

    struct sClient {
        string AccountNumber;
        string PinCode;
        string Name;
        string Phone;
        double AccountBalance;
        bool MarkForDelete = false;
    };

    
    int ReadChoose(const string& message);
    void mainmenuscreen();
    void Guidance(int ch);
    void ShowClientList();
    void AddNewClient();
    sClient ParseClientDataFromString(const string& dataString, const string& delimiter);
    vector<string> SplitString(const string& inputString, const string& delimiter);
    vector<sClient> LoadClientsDataFromFile(const string& filename);
    void PrintClientRecordFormatted(const sClient& client);
    void PrintAllClientsData(const vector<sClient>& clients);
    void goback();
    string ConvertClientDataToString(const sClient& client);
    sClient ReadClientData();
    void AddDataLineToFile(const string& filename, const string& dataLine);
    void DeleteClient();
    bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients);
    bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client);
    vector<sClient> SaveClientsDataToFile(string FileName, vector<sClient> vClients);
    void PrintClientCard(sClient Client);
    bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients);
    void UpdateClient();
    void FindClient();
    bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients);
    sClient ReadandUpdateClientData(sClient client);

    int ReadChoose(const string& message) {
        int number;
        cout << message << endl;
        cin >> number;
        while (cin.fail() || number > 6 || number < 1) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice, enter a valid choice [1 to 6]" << endl;
            cin >> number;
        }
        return number;
    }

    void Guidance(int ch) {
        if (ch == 1) {
            ShowClientList();
        }
        else if (ch == 2) {
            AddNewClient();
        }
        else if (ch == 3) {
            DeleteClient();
        }
        else if (ch == 4) {
            UpdateClient();
        }
        else if (ch == 5) {
            FindClient();
        }
        else if (ch == 6) {
            exit(0);
        }
    }

    void mainmenuscreen() {
        system("cls");
        cout << "=================================================================================\n";
        cout << setw(50) << "Main Menu Screen" << endl;
        cout << "=================================================================================\n";
        cout << setw(30) << "[1] Show Client List " << endl;
        cout << setw(27) << "[2] Add New Client" << endl;
        cout << setw(26) << "[3] Delete Client" << endl;
        cout << setw(26) << "[4] Update Client" << endl;
        cout << setw(24) << "[5] Find Client" << endl;
        cout << setw(18) << "[6] Exit " << endl;
        cout << "=================================================================================\n";
        Guidance(ReadChoose("Choose what do you want to do? [1 to 6] "));
    }

    void ShowClientList() {
        system("cls");
        vector<sClient> Vclient = LoadClientsDataFromFile("Myclient.txt");
        PrintAllClientsData(Vclient);
        goback();
    }

    void AddNewClient() {
        system("cls");
        sClient client = ReadClientData();
        string dataLine = ConvertClientDataToString(client);
        AddDataLineToFile("Myclient.txt", dataLine);
        cout << "\n\n\n\n Done Successfully!\n\n";
        goback();
    }

    void DeleteClient() {
        system("cls");
        vector<sClient> vClients = LoadClientsDataFromFile("Myclient.txt");
        string accountNumber;
        cout << "\n\nEnter Your Account Number to Delete: ";
        cin >> accountNumber;
        DeleteClientByAccountNumber(accountNumber, vClients);
        goback();
    }

    void UpdateClient() {
        system("cls");
        vector<sClient> vClients = LoadClientsDataFromFile("Myclient.txt");
        string accountNumber;
        cout << "\n\nEnter Your Account Number to Update: ";
        cin >> accountNumber;
        UpdateClientByAccountNumber(accountNumber, vClients);
        goback();
    }

    void FindClient() {
        system("cls");
        vector<sClient> vClients = LoadClientsDataFromFile("Myclient.txt");
        string accountNumber;
        sClient Client;
        cout << "\n\nEnter Your Account Number to Find: ";
        cin >> accountNumber;
        if (FindClientByAccountNumber(accountNumber, vClients, Client)) {
            PrintClientCard(Client);
        }
        else {
            cout << "\n\nAccount Number Not Found!\n\n";
        }
        goback();
    }

    void AddDataLineToFile(const string& filename, const string& dataLine) {
        ofstream MyFile(filename, ios::out | ios::app);
        if (MyFile.is_open()) {
            MyFile << dataLine << endl;
            MyFile.close();
        }
        else {
            cout << "Unable to open file: " << filename << endl;
        }
    }

    sClient ReadClientData() {
        sClient client;

        cout << "Enter Your Account Number: ";
        cin >> client.AccountNumber;

        cout << "Enter Your Pin Code: ";
        cin >> client.PinCode;

        cin.ignore(numeric_limits<streamsize>::max(), '\n');  

        cout << "Enter Your Full Name: ";
        getline(cin, client.Name);  

        cout << "Enter Your Phone Number: ";
        cin >> client.Phone;

        cout << "Enter Your Account Balance: ";
        cin >> client.AccountBalance;

        return client;
    }

    string ConvertClientDataToString(const sClient& client) {
        string delimiter = "#/#";
        string formattedString = "";

        formattedString += client.AccountNumber + delimiter;
        formattedString += client.PinCode + delimiter;
        formattedString += client.Name + delimiter;
        formattedString += client.Phone + delimiter;
        formattedString += to_string(client.AccountBalance);

        return formattedString;
    }

    void goback() {
        int ch;
        cout << "\n\n\nTo return to the main menu, click [6] ";
        cin >> ch;
        while (ch != 6) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid choice, enter a valid choice [6]" << endl;
            cin >> ch;
        }
        mainmenuscreen();
    }

    vector<sClient> LoadClientsDataFromFile(const string& filename) {
        vector<sClient> clients;
        ifstream file(filename, ios::in);
        if (file.is_open()) {
            string line;
            while (getline(file, line)) {
                sClient client = ParseClientDataFromString(line, "#/#");
                clients.push_back(client);
            }
            file.close();
        }
        else {
            cout << "Unable to open file: " << filename << endl;
        }
        return clients;
    }

    sClient ParseClientDataFromString(const string& dataString, const string& delimiter) {
        vector<string> data = SplitString(dataString, delimiter);
        sClient client;
        client.AccountNumber = data[0];
        client.PinCode = data[1];
        client.Name = data[2];
        client.Phone = data[3];
        client.AccountBalance = stod(data[4]);
        return client;
    }

    vector<string> SplitString(const string& inputString, const string& delimiter) {
        vector<string> words;
        string str = inputString;
        size_t pos = 0;
        string word;
        while ((pos = str.find(delimiter)) != string::npos) {
            word = str.substr(0, pos);
            if (!word.empty()) {
                words.push_back(word);
            }
            str.erase(0, pos + delimiter.length());
        }
        if (!str.empty()) {
            words.push_back(str);
        }
        return words;
    }

    void PrintClientRecordFormatted(const sClient& client) {
        cout << "| " << setw(15) << left << client.AccountNumber;
        cout << "| " << setw(10) << left << client.PinCode;
        cout << "| " << setw(40) << left << client.Name;
        cout << "| " << setw(12) << left << client.Phone;
        cout << "| " << setw(12) << left << client.AccountBalance << " |";
    }

    void PrintAllClientsData(const vector<sClient>& clients) {
        cout << "\n\t\t\t\t Client list (" << clients.size() << ") clients(s) \n\n";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        cout << "| " << left << setw(15) << "Account Number";
        cout << "| " << left << setw(10) << "Pin Code";
        cout << "| " << left << setw(40) << "Client Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(12) << "Balance";
        cout << "\n_______________________________________________________";
        cout << "_________________________________________\n" << endl;
        for (const sClient& client : clients) {
            PrintClientRecordFormatted(client);
            cout << endl;
        }
    }

    bool DeleteClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
        sClient Client;
        char Answer = 'n';
        if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
            PrintClientCard(Client);
            cout << "\n\nAre you sure you want to delete this client? y/n ? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y') {
                MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
                SaveClientsDataToFile("Myclient.txt", vClients);
                vClients = LoadClientsDataFromFile("Myclient.txt");
                cout << "\n\nClient Deleted Successfully.";
                return true;
            }
        }
        else {
            cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        }
        return false;
    }

    bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient& Client) {
        for (sClient C : vClients) {
            if (C.AccountNumber == AccountNumber) {
                Client = C;
                return true;
            }
        }
        return false;
    }

    vector<sClient> SaveClientsDataToFile(string FileName, vector<sClient> vClients) {
        fstream MyFile;
        MyFile.open(FileName, ios::out);
        string DataLine;

        if (MyFile.is_open()) {
            for (sClient C : vClients) {
                if (!C.MarkForDelete) {
                    DataLine = ConvertClientDataToString(C);
                    MyFile << DataLine << endl;
                }
            }
            MyFile.close();
        }
        return vClients;
    }

    void PrintClientCard(sClient Client) {
        cout << "\nThe following are the client details:\n";
        cout << "\nAccount Number: " << Client.AccountNumber;
        cout << "\nPin Code: " << Client.PinCode;
        cout << "\nName: " << Client.Name;
        cout << "\nPhone: " << Client.Phone;
        cout << "\nAccount Balance: " << Client.AccountBalance << "\n";
    }

    bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
        for (sClient& C : vClients) {
            if (C.AccountNumber == AccountNumber) {
                C.MarkForDelete = true;
                return true;
            }
        }
        return false;
    }

    bool UpdateClientByAccountNumber(string AccountNumber, vector<sClient>& vClients) {
        sClient Client;
        char Answer = 'n';
        if (FindClientByAccountNumber(AccountNumber, vClients, Client)) {
            PrintClientCard(Client);
            cout << "\n\nAre you sure you want to update this client? y/n ? ";
            cin >> Answer;
            if (Answer == 'y' || Answer == 'Y') {
                Client = ReadandUpdateClientData(Client);
                for (sClient& C : vClients) {
                    if (C.AccountNumber == Client.AccountNumber) {
                        C = Client;
                        break;
                    }
                }
                SaveClientsDataToFile("Myclient.txt", vClients);
                cout << "\n\nClient Updated Successfully.";
                return true;
            }
        }
        else {
            cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
        }
        return false;
    }

    sClient ReadandUpdateClientData(sClient client) {
        cout << "Enter Your Full Name: ";
        cin.ignore();
        getline(cin, client.Name);

        cout << "Enter Your Phone Number: ";
        cin >> client.Phone;

        cout << "Enter Your Account Balance: ";
        cin >> client.AccountBalance;

        return client;
    }

}
