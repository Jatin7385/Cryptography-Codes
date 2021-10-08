//HILL Cipher
//CODE BY JATIN DHALL
#include <iostream>
#include <cstring>
#include <cctype>
#include <cmath>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unordered_set>
#include <map>

using namespace std;

//C = PKmod26
//P = CK^-1 mod26

map<char,int> alphabets{
    {'A',0},
    {'B',1},
    {'C',2},
    {'D',3},
    {'E',4},
    {'F',5},
    {'G',6},
    {'H',7},
    {'I',8},
    {'J',9},
    {'K',10},
    {'L',11},
    {'M',12},
    {'N',13},
    {'O',14},
    {'P',15},
    {'Q',16},
    {'R',17},
    {'S',18},
    {'T',19},
    {'U',20},
    {'V',21},
    {'W',22},
    {'X',23},
    {'Y',24},
    {'Z',25},
};

bool isPerfectSquare(long double x)
{
    // Find floating point value of
    // square root of x.
    if (x >= 0) {
 
        long long sr = sqrt(x);
         
        // if product of square root
        //is equal, then
        // return T/F
        return (sr * sr == x);
    }
    // else return false if n<0
    return false;
}


void dispCipherMatrix(vector<int> cipherMatrix,int n)
{
    cout<<"Cipher Matrix after Multiplication is :-"<<endl;
    for(int j=0;j<n;j++)
    {
        cout<<cipherMatrix.at(j)<<" ";
    }
    cout<<endl;
}

vector<int> matrixMult(vector<int> p,vector<vector<int>> keyMatrix,int n,int rows)
{
    int a = 0;
    vector<int> result;
    for(int j=0;j<n;j++)
    {
        a = 0;
        for(int k = 0;k<n;k++)
        {
            a+=p.at(k) * keyMatrix.at(k).at(j);
        }
        a%=26;
        result.push_back(a);
    }
    dispCipherMatrix(result,n);
    return result;
}

char num2Alphabet(int num)
{
    for (auto& x: alphabets) 
    {  
        if(x.second == num){return x.first;}  
    }
    return NULL;
}


string encryption(vector<vector<int>> PlainTextMatrix,vector<vector<int>> KeyMatrix,int n,int rows)
{
    char ch;
    vector<int> p,c;
    string finalstr = "";
    for(int i = 0;i < rows;i++)
    {
        p.clear();c.clear();
        p = PlainTextMatrix.at(i);
        c = matrixMult(p,KeyMatrix,n,rows);
        for(int j=0;j<n;j++)
        {
            ch = num2Alphabet(c.at(j));
            finalstr += ch;
        }
    }
    return finalstr;
}

// Function to remove all spaces from a given string
string removeSpaces(string str)
{
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

void dispKeyMatrix(vector<vector<int>> keyMatrix,int n)
{
    cout<<"Key Matrix is :-"<<endl;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<keyMatrix.at(i).at(j)<<" ";
        }
        cout<<endl;
    }
}

vector<vector<int>> createKeyMatrix(string key, int n)
{
    int count = 0;
    vector<vector<int>> keyMatrix;
    vector<int> temp;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
            int val = alphabets[toupper(key.at(count))];
            temp.push_back(val);
            count++;
        }
        keyMatrix.push_back(temp);
        temp.clear();
    }

    dispKeyMatrix(keyMatrix,n);

    return keyMatrix;
}

void dispPlainTextMatrix(vector<vector<int>> plainTextMatrix,int n,int rows)
{
    cout<<"Plain Text Matrix is :-"<<endl;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<n;j++)
        {
            cout<<plainTextMatrix.at(i).at(j)<<" ";
        }
        cout<<endl;
    }
}

vector<vector<int>> createPlainTextMatrix(string text, int n)
{
    int count = 0;
    vector<vector<int>> plainTextMatrix;
    vector<int> temp;
    int length = text.length();
    int rows = length / n;
    for(int i=0;i<rows;i++)
    {
        for(int j=0;j<n;j++)
        {
            temp.push_back(alphabets[toupper(text.at(count))]); //Pushing in the int value of the alphabet at count from text
            count++;
        }
        plainTextMatrix.push_back(temp);
        temp.clear();
    }

    dispPlainTextMatrix(plainTextMatrix,n,rows);
    return plainTextMatrix;
}

//Driver Code
int main()
{
    string key;
    cout<<"Enter the Key whose length should be square of an integer: ";
    getline(cin,key);
    key = removeSpaces(key);
    long double length = key.length();
    string text;
    cout<<"Enter the Text you want to Encode using HILL Cipher which should be a multiple of the square root of the integer spoken about in the key: ";
    getline(cin,text);
    text = removeSpaces(text);

    vector<vector<int>> keyMatrix,plainTextMatrix;
    if(isPerfectSquare(length))
    {
        int n = sqrt(length);
        if(text.length() % n == 0)
        {
            keyMatrix = createKeyMatrix(key,n);
            plainTextMatrix = createPlainTextMatrix(text,n);
            int length = text.length();
            int rows = length / n;
            string encryptedString = encryption(plainTextMatrix,keyMatrix,n,rows);
            cout<<"The Encrypted string is : "<<encryptedString<<endl;
        }
        else
        {
            cout<<"Incorrect Text size. The Text size should be a multiple of the square root of the integer spoken about in the key, which is "<<n<<endl;
        }
    }
    else
    {
        cout<<"Incorrect Key Size. The key size should be square of an integer"<<endl;
    }
}