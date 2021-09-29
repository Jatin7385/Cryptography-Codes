// Caeser Cipher
//CODE BY JATIN DHALL
#include <iostream>
#include <string>
using namespace std;

string encrypt(string text,int key)
{
    int length = text.length();
    char c;
    string cipher;
    char ct;
    for(int i=0;i<length;i++)
    {
        c = text.at(i);
        int asc = int(c);
        if(asc>=65 && asc<=90)
        {
            asc += key;
            if(asc>90){
            asc-=26;
            }
            ct = char(asc);
            cipher+=ct;
        }
        else if(asc>=97 && asc<= 122){
            asc += key;
            if(asc>122){
            asc-=26;
            }
            ct = char(asc);
            cipher+=ct;
        } 
    }
    return cipher;
}

string decrypt(string text,int key)
{
    int length = text.length();
    char c;
    string decipher;
    char dt;
    for(int i=0;i<length;i++)
    {
        c = text.at(i);
        int asc = int(c);
        if(asc>=65 && asc<=90){
            asc -= key;
            if(asc>90){
            asc-=26;
            }
            dt = char(asc);
            decipher+=dt;
        }
        else if(asc>=97 && asc<=122)
        {
            asc -= key;
            if(asc>122){
            asc-=26;
            }
            dt = char(asc);
            decipher+=dt;
        }
    }
    return decipher;
}
int main()
{
    string text;
    cout<<"Enter the Text you want to Cipher or Decipher : ";
    getline(cin,text);
    int key;
    cout<<"Enter the Key : ";
    cin>>key;
    cout<<text<<key<<endl;
    while(true){
    cout<<"Enter one of the two options"<<endl;
    cout<<"1. Encrypt"<<endl;
    cout<<"2. Decrypt"<<endl;
    int op;
    cout<<"Enter the choice : ";
    cin>>op;
    string text1;
    switch(op){
        case 0: exit(0);
        case 1: text1 = encrypt(text,key);
                cout<<"The cipher text is : "<<text1<<endl;
                break;
        case 2: text1 = decrypt(text,key);
                cout<<"The deciphered text is : "<<text1<<endl;
                break;
        default : cout<<"Invalid option. Try again"<<endl;
                  break;
    }
    }
}