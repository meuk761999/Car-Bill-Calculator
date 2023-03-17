#include <bits/stdc++.h>
using namespace std;

string CAPITAL_CASE(string A)
{
    for (int i = 0; i < A.size(); i++)
    {
        if (isalpha(A[i]))
        {
            A[i] = toupper(A[i]);
        }
    }
    return A;
}
string Title_Case(const string A)
{
    char First_capital = toupper(A[0]);
    string B;
    B = First_capital;

    for (int i = 1; i < A.size(); i++)
    {
        if (A[i] == ' ')
            continue;
        if (A[i] >= 'A' && A[i] <= 'Z')
        {
            char small = tolower(A[i]);
            B += small;
            continue;
        }
        else
            B = B + A[i];
    }
    return B;
}

vector<string> split(const string &s, char delim)
{
    vector<string> result;
    stringstream ss(s);
    string item;

    while (getline(ss, item, delim))
    {
        result.push_back(item);
    }

    return result;
}
class car
{
private:
    map<string, int> services_and_costs;
    map<string, string> services_code;
    map<string, string> code_service;
    map<string, int> code_cost;
    string carname;

public:
    car(string carname)
    {
        this->services_and_costs[""] = 0;
        this->services_code[""] = "";
        this->code_service[""] = "";
        this->carname = Title_Case(carname);
        this->code_cost[""] = 0;
    }
    void add_new_service(string service = "", string service_code = "", int cost = 0)
    {
        this->services_and_costs[service] = cost;
        this->services_code[service] = CAPITAL_CASE(service_code);
        this->code_service[CAPITAL_CASE(service_code)] = service;
        this->code_cost[CAPITAL_CASE(service_code)] = cost;
    }
    string getcname()
    {
        return this->carname;
    }
    int getcostbycode(string code)
    {
        return code_cost[code];
    }
    string getservicebycode(string code)
    {
        return code_service[code];
    }
    string getcode(string service)
    {
        return services_code[service];
    }
    void printdata()
    {
        cout << this->carname << "\t";
        for (auto it = this->services_and_costs.begin(); it != this->services_and_costs.end(); it++)
        {
            if (it->first != "")
            {
                cout << "(" << services_code[it->first] << ")";
                cout << it->first << ":";
                cout << it->second << "\t";
            }
        }
        cout << "\n\n";
    }
};
class solution
{
private:
    car Hatchback{"Hatchback"}, Sedan{"Sedan"}, SUV{"SUV"};

public:
    solution()
    {
        Hatchback.add_new_service("Basic Servicing", "BS01", 2000);
        Hatchback.add_new_service("Engine Fixing", "EF01", 5000);
        Hatchback.add_new_service("Clutch Fixing", "CF01", 2000);
        Hatchback.add_new_service("Brake Fixing", "BF01", 1000);
        Hatchback.add_new_service("Gear Fixing", "GF01", 3000);

        Sedan.add_new_service("Basic Servicing", "BS01", 4000);
        Sedan.add_new_service("Engine Fixing", "EF01", 8000);
        Sedan.add_new_service("Clutch Fixing", "CF01", 4000);
        Sedan.add_new_service("Brake Fixing", "BF01", 1500);
        Sedan.add_new_service("Gear Fixing", "GF01", 6000);

        SUV.add_new_service("Basic Servicing", "BS01", 5000);
        SUV.add_new_service("Engine Fixing", "EF01", 10000);
        SUV.add_new_service("Clutch Fixing", "CF01", 6000);
        SUV.add_new_service("Brake Fixing", "BF01", 2500);
        SUV.add_new_service("Gear Fixing", "GF01", 8000);
    }
    void menuDisplay()
    {
        Hatchback.printdata();
        Sedan.printdata();
        SUV.printdata();
    }
    vector<string> dataIn()
    {
        string cartype;
        vector<string> ser_codes;
        int sflag = 1;
        while (sflag)
        {
            cout << "\nEnter Your car type:";
            getline(cin, cartype);
            cartype = Title_Case(cartype);
            if (cartype == Hatchback.getcname() || cartype == Sedan.getcname() || cartype == SUV.getcname())
            {
                sflag = 0;
            }
        }
        cout << "\n Your car type is " << cartype;
        int cflag;
        do
        {
            cflag = 0;
            cout << "\nEnter service codes of request services(For Example 'BS01,CF01' for Break Fixing & clutch fixing): ";
            vector<string> tempv;
            string temps;
            temps.clear();
            tempv.clear();
            ser_codes.clear();
            getline(cin, temps);
            tempv = split(temps, ',');

            for (auto i : tempv)
            {
                ser_codes.push_back(CAPITAL_CASE(i));
            }

            for (auto i : ser_codes)
            {
                if (!(i == "BS01" || i == "EF01" || i == "CF01" || i == "BF01" || i == "GF01"))
                {
                    cflag = 1;
                }
            }
        } while (cflag);
        ser_codes.push_back(cartype);
        return ser_codes;
    }
    void billOut(vector<string> ser_codes_cartype)
    {
        string cartype = (*(prev(ser_codes_cartype.end())));
        int cost = 0;
        cout << endl
             << cartype << endl;
        if (cartype == Hatchback.getcname())
            for (auto it = ser_codes_cartype.begin(); it != prev(ser_codes_cartype.end()); it++)
            {
                cout << "Charges for " << Hatchback.getservicebycode(*it) << " is " << Hatchback.getcostbycode(*it) << endl;
                cost += Hatchback.getcostbycode(*it);
            }
        else if (cartype == Sedan.getcname())
            for (auto it = ser_codes_cartype.begin(); it != prev(ser_codes_cartype.end()); it++)
            {
                cout << "Charges for " << Sedan.getservicebycode(*it) << " is " << Sedan.getcostbycode(*it) << endl;
                cost += Sedan.getcostbycode(*it);
            }
        else if (cartype == SUV.getcname())
            for (auto it = ser_codes_cartype.begin(); it != prev(ser_codes_cartype.end()); it++)
            {
                cout << "Charges for " << SUV.getservicebycode(*it) << " is " << SUV.getcostbycode(*it) << endl;
                cost += SUV.getcostbycode(*it);
            }

        if (cost > 10000)
            cout << endl
                 << "Charges for complimentry cleaning is " << 0 << endl;
        cout << "Total Bill is " << cost;
    }
};
// DRIVER CODE
int main()
{
    solution obj;
    obj.menuDisplay();
    obj.billOut(obj.dataIn());
    getchar();

    return 0;
}