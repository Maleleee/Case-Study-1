#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

struct GuestInfo
{
    string name;
    string dob;
    string contact;
    string email;
    string package;
    int numGuest;
    int numDays;
};

struct RoomAvail 
{
    string packageName;
    int slotsAvail;
};
     
    void initialRoom(RoomAvail roomAvailable[], int size)
    {
        roomAvailable[0] = {"Basic", 50}; 
        roomAvailable[1] = {"Standard", 50}; 
        roomAvailable[2] = {"Deluxe", 50}; 
        roomAvailable[3] = {"Premium", 50}; 
        roomAvailable[4] = {"Superior", 50}; 
    }

    
    void displayRoom(const RoomAvail roomAvailable[], int size)
    {
        cout <<"Room Availability: " << endl;
        for (int i = 0; i < size; ++i)
        {
            cout << roomAvailable[i].packageName << ": " << roomAvailable[i].slotsAvail << " available slots" << endl;
        }
    }

    void updateRoom(RoomAvail roomAvailable[], int size, const string& selectedPackage) 
    {
        for (int i=0; i < size; ++i)
        {
            if (roomAvailable[i].packageName == selectedPackage)
            {
                roomAvailable[i].slotsAvail -= 1; // bawas 1 sa available slot ng package
                break;
            }
        }
    }

    void saveInfo(const GuestInfo& guest) // the whole code below is for saving guest info in text file (guests.txt)
    {
        ofstream guestFile("guests.txt", ios::app);
        if (guestFile.is_open())
        {
            guestFile <<"Name: " << guest.name << endl;
            guestFile <<"Date of Birth: " << guest.dob << endl;
            guestFile <<"Contact Number: " << guest.contact << endl;
            guestFile <<"Email Address: " << guest.email << endl;
            guestFile <<"Room Package: " << guest.package << endl;
            guestFile <<"Number of Guests: " << guest.numGuest << endl;
            guestFile <<"Number of Days: " << guest.numDays << endl;
            guestFile << "-------------------------" << endl;
            guestFile.close();

            cout <<"Guest information saved successfully!" << endl;
        } else 
        {
            cout <<"Error saving guest information!" << endl;
        }
    }

// function to check duplicates

bool guestExist(const string& guestName) {
    ifstream inputFile("guests.txt");
    if (inputFile.is_open()) {
        string line;
        while (getline(inputFile, line)) {
            if (line.find("Name: " + guestName) != string::npos) {
                inputFile.close();
                return true;
            }
        }
        inputFile.close();
    }
    return false;
}

    // check-in 
void checkIn(RoomAvail roomAvailable[], int RoomAvailSize) 
{
    GuestInfo guest;

    cout << "Please enter the following information before we check you in: " << endl;
    cout << "Name: ";
    cin.ignore();
    getline(cin, guest.name);

    if (guestExist(guest.name))
    {
        cout <<"A guest with the same name already exists in the database. Please try again." << endl;

    } else {
        cout << "Date of Birth: ";
        getline(cin, guest.dob);

        cout << "Contact Number: ";
        getline(cin, guest.contact);

        cout << "Email Address: ";
        getline(cin, guest.email);

        cout <<"Available Room Packages: " << endl;
        for (int i = 0; i < RoomAvailSize; ++i)
        {
            cout << i + 1 << ". " << roomAvailable[i].packageName << endl;

        }
            int choicePack;
        do 
        {
            cout << "Please select a room package (1-" << RoomAvailSize << "): ";
            cin >> choicePack;
        } while (choicePack < 1 || choicePack > RoomAvailSize);

        guest.package = roomAvailable[choicePack - 1].packageName;

        updateRoom(roomAvailable, RoomAvailSize, guest.package);



        cout << "Number of Guests: ";
        cin >> guest.numGuest;

        cout << "Number of Days: ";
        cin >> guest.numDays;

        saveInfo(guest);
    }

}


void editInfo() {

    string guestName;
    cout <<"Enter your name: " << endl;
    cin.ignore();
    getline(cin, guestName);

    ifstream inputFile("guests.txt");
    ofstream tempFile("temp.txt");

    if (!inputFile || !tempFile)
    {
        cout << "Error opening files for editing." << endl;
        return;
    }

    string line;
    bool found = false;

    while (getline(inputFile, line))
    {
        if (line.find("Name: " + guestName) != string::npos)
      {
        found = true;

        cout <<"Information found, please enter updated information: " << endl;

        GuestInfo updateGuest;

        updateGuest.name = guestName;

        cout << "Date of Birth: ";
        getline(cin, updateGuest.dob);

        cout << "Contact Number: ";
        getline(cin, updateGuest.contact);

        cout << "Email Address: ";
        getline(cin, updateGuest.email);

        cout <<"Room Package: ";
        getline(cin, updateGuest.package);

        cout << "Number of Guests: ";
        cin >> updateGuest.numGuest;

        cout << "Number of Days: ";
        cin >> updateGuest.numDays;
        

        // Store info sa temp file muna 
        tempFile <<"Updated Information of: " << updateGuest.name << endl;
        tempFile <<"Name: " << updateGuest.name << endl;
        tempFile <<"Date of Birth: " << updateGuest.dob << endl;
        tempFile <<"Contact Number: " << updateGuest.contact << endl;
        tempFile <<"Email Address: " << updateGuest.email << endl;
        tempFile <<"Room Package: " << updateGuest.package << endl;
        tempFile <<"Number of Guests: " << updateGuest.numGuest << endl;
        tempFile <<"Number of Days: " << updateGuest.numDays << endl;

        tempFile << "-------------------------" << endl;

        cout <<"Guest information updated successfully!" << endl;
      } else 
      {
        tempFile << line << endl;
      }
    }

    inputFile.close();
    tempFile.close();

    remove("guests.txt");
    rename("temp.txt", "guests.txt");

    if(!found)
    {
        cout <<"Guest information not found!" << endl;
    }

}

int main ()

{
    int choice;
    const int roomAvailableSize = 5;
    RoomAvail roomAvailable[roomAvailableSize]; 
    GuestInfo guest;

    cout << "Welcome to Grand Maple Hotel!" << endl;
    cout << "----------------------------------------------" << endl;


    initialRoom(roomAvailable, roomAvailableSize); 
    do {
        
        cout << "Please select an option: " << endl;
        cout << "[1] Check-in" << endl; // DONE
        cout << "[2] Check Room Availability" << endl; //DONE
        cout << "[3] Edit Check-in Information" << endl; // DONE

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                
                checkIn(roomAvailable, roomAvailableSize);
                break;

            case 2:

                displayRoom(roomAvailable, roomAvailableSize);

                break;
            
            case 3:

             editInfo();

             break;

            case 4: 
                
                    cout << "Thank you for using the Grand Maple Hotel Reservation System!" << endl; 
    
                    break;
            default:
                cout <<"Invalid choice. Please try again." << endl;
        }





    } while (choice != 4);
    

    return 0;

}