#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

int table_size = 10;
struct User
{
    string username;
    string passwordHash;
    int flag ;
    /*flag = 0 -> EMPTY
      flag = 1 -> OCCUPIED
      flag = 2 -> DELETED
    */
};

class HASHING
{
    private : 
        User table[10];
        
    public : 

    HASHING()
    {
        for(int i = 0; i < table_size; i++)
        {
            table[i].flag = 0;
        }
    }

    int hashFunction( string username )
    {
            int hash = 0;
            for(char c : username)
            {
                hash = hash + c;
            }
            return hash % table_size;
    }

    string passwordHash(string password)
    {
        unsigned long long hash = 5381;

        for(char c : password)
        {
            hash = ((hash << 5) + hash) + c;
        }

        return to_string(hash);
    }

    void insert( string username , string password)
    {
        int index = hashFunction(username);
        int i = 0;
        while(i < table_size && table[(index+i) % table_size].flag == 1  )
        {
            i++;
        }
        if(i == table_size )
        {
            cout << "Hash Table is Full. Try Again Later" << endl;
            return;
        }
        table[(index+i)%table_size].username = username; 
        table[(index+i)%table_size].passwordHash = passwordHash(password);
        table[(index+i)%table_size].flag = 1;
    }

    void Display()
    {

        cout<< left
            << setw(10) << "Index"
            << setw(15) << "Status"
            << setw(20) << "Username"
            << endl;
        cout << string(45, '-') << endl;
        
        
        for (int i =0; i < table_size; i++)
        {
            cout << left << setw(10) << i;
            if(table[i].flag == 0)
            {
                cout << setw(15) << "EMPTY";
            }
            else if(table[i].flag == 1)
            {
                cout << setw(15) << "OCCUPIED" << setw(20) << table[i].username;
            }
            else
            {
                cout << setw(15) << "DELETED";
            }
            cout << endl;
        }
    }

    void Login( string username ,string Entered_password)
    {
        int search_index = hashFunction(username);
        int i = 0;
        Entered_password = passwordHash(Entered_password);
        for(i =0; i < table_size; i++)
        {
            int current = (search_index + i) % table_size;
            if( table[current].flag == 0)
            {
                cout << "Username Not Found " << endl;
                return;
            }
            if( table[current].flag == 1 && table[current].username == username)
            {
                if( table[current].passwordHash == Entered_password )
                {
                    cout << "Login Successful ! " << endl;
                    return;
                }
                cout << "Invalid Password . " << endl;
                return;
            }
        }
        cout << "Username Not Found . " << endl;
    }

    void loadFromFile()
    {
        ifstream file("users.txt");
        string username, passwordHash;

        while( file >> username >> passwordHash )
        {
            loadUser(username,passwordHash);
        }
        file.close();
    }

    void loadUser(string username, string storedHash)
    {
        int index = hashFunction(username);
        int i = 0;

        while(i < table_size &&
              table[(index+i) % table_size].flag == 1)
        {
            i++;
        }

        if(i == table_size)
        {
            cout << "Hash Table is Full." << endl;
            return;
        }

        table[(index+i)%table_size].username = username;
        table[(index+i)%table_size].passwordHash = storedHash;
        table[(index+i)%table_size].flag = 1;
    }

    bool userExsist(string username)
    {
        int search_index = hashFunction(username);
        for(int i = 0; i < table_size; i++)
        {
            int current = (search_index + i) % table_size;

            if(table[current].flag == 0)
            {
               return false;
            }

            if(table[current].flag == 1 && table[current].username == username)
            {
                return true;
            }
        }
        return false;
    }

    void registerUser()
    {
        string username,password;
        cout << "Enter the UserName : ";
        cin >> username;
        if(userExsist(username))
        {
            cout << "Username already Exsist !" << endl;
            return;
        }
        cout << "Enter the Password : ";
        cin >> password;

        ofstream dbfile("DB.txt" , ios::app);
        if(!dbfile)
        {
            cout << "Unable to open File \n";
            return;
        }
        dbfile << username << " " << password << endl;
        dbfile.close();

        insert(username,password);
        ofstream file("users.txt" , ios::app);
        if(!file)
        {
            cout << "Unable to open File \n";
            return;
        }
        file << username << " " << passwordHash(password) << endl;
        file.close();
        cout << "Registration Successful !. " << endl;

    }

};

int main()
{
    HASHING h;
    h.loadFromFile();
    int choice;
    string username,password;

    do
    {
        cout << "\n================================\n";
        cout << "        HASH LOGIN SYSTEM\n";
        cout << "================================\n";
        cout << "1. Login\n";
        cout << "2. Register\n";
        cout << "3. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch(choice)
        {
            case 1:
                cout << "Enter the UserName : ";
                cin >> username;
                cout << "Enter the Password : ";
                cin >> password;
                h.Login(username,password);
                break;
            
            case 2:
                h.registerUser();
                break;

            case 3:
                cout << "Exiting Login Page. " << endl;
                break;
        }
    }while( choice != 3);
    return 0;
}
