#include <iostream>
#include <vector>
using namespace std;

vector<vector<int>> vigenereTable;

vector<vector<int>> createVigenereTable()
{
    vector<vector<int>> table;
    vector<int> row;
    int value = 0;
    for(int i=0;i<26;i++)
    {
        for(int j=i;j<26 + i;j++)
        {
            value = j%26;
            row.push_back(value);
        }
        table.push_back(row);
        row.clear();
    }
    return table;
}

string encrypt(string text,string key)
{
    char p,k,c;int p1,k1;
    string ciphertext = "";
    for(int i=0;i<text.length();i++)
    {
        p = toupper(text.at(i));
        k = toupper(key.at(i));
        p1 = p-65;
        k1 = k-65;
        c = vigenereTable.at(k1).at(p1) + 65;
        ciphertext+=c;
    }
    return ciphertext;
}

string decrypt(string cipher,string key)
{
    char c,k,p; int p1;
    string plainText = "";
    for(int i=0;i<cipher.length();i++)
    {
        k = key.at(i);
        c = cipher.at(i);
        p1 = (c-65) - (k-65);
        if(p1<0){
            p1 = 26 + p1;
        }
        p1 += 65;
        p = p1;
        plainText += p;
    }
    return plainText;
}

int main()
{
    string text,key,key1 = "";
    cout<<"Enter the text"<<endl;
    cin>>text;
    cout<<"Enter the key"<<endl;
    cin>>key;

    cout<<"\nEncryption"<<endl;
    int count = 0;
    for(int i=0;i<text.length();i++)
    {
        key1 += key.at(count);
        count++;
        count%=key.length();
    }
    
    vigenereTable = createVigenereTable();

    string cipherText,plainText;
    cipherText = encrypt(text,key1);
    cout<<"The Cipher Text is : "<<cipherText<<endl;

    cout<<"\nDecryption"<<endl;
    plainText = decrypt(cipherText,key1);
    cout<<"The Deciphered Text is : "<<plainText<<endl;

}