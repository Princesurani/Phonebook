#include <iostream>
#include <fstream>
#include <cstring>
#include<windows.h>

using namespace std;

class phoneBook
{
    char name[20], phonenum[15];

public:
    void getdata();
    void showdata();
    char *getname() { return name; }
    char *getphonenum() { return phonenum; }
    void update(char *nm, char *telno)
    {
        strcpy(phonenum, telno);
    }
};

void phoneBook ::getdata()
{
    cout << "Enter person's Name : ";
    cin >> name;
    cout << "Enter Phone No. : ";
    cin >> phonenum;
}

void phoneBook ::showdata()
{
    cout << name << " : " << phonenum << endl;
}

int main()
{
    system("color 70");
    phoneBook phn;
   
    fstream file;
    file.open("phonebook.txt", ios::ate | ios::in | ios::out | ios::binary);
    char c, ch, nm[20], telno[6];
    int choice, cnt, found = 0;
    cout << "\nPhone Book\n";
    cout << "1) Add New record\n";
    cout << "2) Display All records\n";
    cout << "3) Search Telephone Number.\n";
    cout << "4) Update Telephone Number.\n";
    cout << "5) Exit\n";
    while (1)
    {

        cout << "\nEnter your choice : ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout<< "\nAdd New record " << endl;
            phn.getdata();
            file.write((char *)&phn, sizeof(phn));
            cout << "- record Added Succesfully in phonebook -\n";
            break;

        case 2:
            cout << "\nDisplay All records" << endl;
            file.seekg(0, ios::beg);
            cout << "- records in phonebook -\n";
            while (file)
            {
                file.read((char *)&phn, sizeof(phn));
                if (!file.eof())
                    phn.showdata();
            }
            file.clear();
            break;

        case 3:
            cout << "\n- Search record by person name -" << endl;
            cout << "Enter person's Name : ";
            cin >> nm;
            file.seekg(0, ios::beg);
            found = 0;
            while (file.read((char *)&phn, sizeof(phn)))
            {
                if (strcmp(nm, phn.getname()) == 0)
                {
                    found = 1;
                    phn.showdata();
                }
            }
            file.clear();
            if (found == 0)
                cout << "\n---record Not found---\n";
            break;

        case 4:
            cout << "\n- Update Telephone No. -" << endl;
            cout << "Enter person's Name : ";
            cin >> nm;
            file.seekg(0, ios::beg);
            found = 0;
            cnt = 0;
            while (file.read((char *)&phn, sizeof(phn)))
            {
                cnt++;
                if (strcmp(nm, phn.getname()) == 0)
                {
                    found = 1;
                    break;
                }
            }
            file.clear();
            if (found == 0)
                cout << "\n- record Not found -\n";
            else
            {
                int location = (cnt - 1) * sizeof(phn);
                cin.get(ch);
                if (file.eof())
                    file.clear();

                cout << "Enter New Telephone No : ";
                cin >> telno;
                file.seekp(location);
                phn.update(nm, telno);
                file.write((char *)&phn, sizeof(phn));
                file.flush();
                cout << "- updated successfully -"<<endl;
            }
            break;
        case 5:
            exit(0);
        }
    }
    file.close();

    return 0;
}