#include <iostream>
using namespace std;

int main()
{
    string text,key;
    cout<<"Enter the text to be encrypted and then decrypted"<<endl;
    cin>>text;
    cout<<"Enter the key of the same length as the text"<<endl;
    cin>>key;

    cout<<"Encryption"<<endl;
    if(text.length() == key.length()){
        int sum = 0;char c;string cipherText = "";
        for(int i=0;i<text.length();i++)
        {
            sum = (toupper(text.at(i))-65) + (toupper(key.at(i)) - 65);
            sum%=26;
            c = (sum+65);
            cipherText += c;
        }
        cout<<"The Cipher Text is : "<<cipherText<<endl;

        cout<<"\nDecryption"<<endl;
        int sub = 0;string plainText = "";
        for(int i=0;i<cipherText.length();i++)
        {
            sub = (toupper(cipherText.at(i))-65) - (toupper(key.at(i)) - 65);
            if(sub<0){sub += 26;}
            c = (sub+65);
            plainText += c;
        }
        cout<<"The Deciphered Text is : "<<plainText<<endl;

    }
    else
    {
        cout<<"The lenght of the text should be equal to the length of the key"<<endl;
    }
}