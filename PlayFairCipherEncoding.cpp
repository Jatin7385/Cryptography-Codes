//Playfair Cipher
//CODE BY JATIN DHALL
//A playfair cipher has a 5X5 playfair matrix which is used for encryption as well as decryption
#include <iostream>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <iterator>
#include <vector>
#include <unordered_set>

using namespace std;

char playfairMatrix[5][5];  
string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

unordered_set<char> getSetFromString(string str)
{
    unordered_set<char> res;
    for(int i=0;i<str.length();i++)
    {
        res.insert(str.at(i));
    }

    unordered_set<char>::iterator itr;
    return res;
}

void dispKeyMatrix()
{
    cout<<"Key Matrix is :-"<<endl;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            cout<<playfairMatrix[i][j]<<" ";
        }
        cout<<endl;
    }
}

void dispPairVectors(vector<pair<char,char>> pairs)
{
    for(int i=0;i<pairs.size();i++)
    {
        cout<<pairs.at(i).first<< " "<<pairs.at(i).second<<endl;
    }
}
vector<char> unorderedSetTOVector(unordered_set<char> keys)
{
    unordered_set<char>::iterator itr;
    vector<char> res;
    for (itr = keys.begin(); itr != keys.end(); itr++)
    {
        res.push_back(*itr);
    }
    reverse(res.begin(),res.end());
    return res;
}

void createPlayFairMatrix(string key)
{
    int lengthKey = key.length();

    int count = 0,count1 = 0;
    int flag = 0;

    string alphabets = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

    unordered_set<char> res = getSetFromString(key);

    vector<char> result = unorderedSetTOVector(res);
    
    //Creating the 5x5 Matrix
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(count < result.size())
            {
                playfairMatrix[i][j] = toupper(result.at(count));
                alphabets.erase(remove(alphabets.begin(), alphabets.end(), toupper(result.at(count))), alphabets.end());
                if(toupper(result.at(count)) == 'I')
                {
                     alphabets.erase(remove(alphabets.begin(), alphabets.end(), toupper('J')), alphabets.end());
                }
                else if(toupper(result.at(count)) == 'J')
                {
                     alphabets.erase(remove(alphabets.begin(), alphabets.end(), toupper('I')), alphabets.end());
                }
                cout<<"Count : "<<count<<" CHAR : "<<result.at(count)<<" Alphabets : "<<alphabets<<endl;
                count++;
            }
            else if(count1 < alphabets.length())
            {
                playfairMatrix[i][j] = toupper(alphabets.at(count1));
                if(alphabets.at(count1) == 'I')
                {
                     alphabets.erase(remove(alphabets.begin(), alphabets.end(), toupper('J')), alphabets.end());
                }
                else if(alphabets.at(count1) == 'J')
                {
                     alphabets.erase(remove(alphabets.begin(), alphabets.end(), toupper('I')), alphabets.end());
                }
                cout<<"Count : "<<count1<<" CHAR : "<<alphabets.at(count1)<<" Alphabets : "<<alphabets<<endl;
                count1++;
            }
        }
    }

    dispKeyMatrix();
}

vector<pair<char, char>> PlainText_To_Pairs(string text)
{
    vector<pair<char,char>> pairs;
    cout<<"The length of the text is : "<<text.length()<<endl;
    if(text.length() % 2 == 0){ //If text length is even, then nothing to worry about, but if the text lenght is odd then, 
    //the last letter gets left out, so we have to increase the length by 2 and add 'X' as the last character
        for(int i=0;i<text.length();i=i+2)
        {
            char a1 = toupper(text.at(i));
            char a2 = toupper(text.at(i+1));
            if(a1 == a2)
            {
                a2 = 'X';
            }
            pairs.push_back(make_pair(a1,a2));
        }
    }
    else
    {
        for(int i=0;i<text.length() + 1;i=i+2)//If the text length is 5, then at the last iteration, i = 4, hence i<5+1 (6)
        {
            char a1 = toupper(text.at(i));
            char a2;
            if(i == text.length() - 1) // If the text length is 5, then in this loop,i at the last iteration would be 4, hence 5-1 = 4
            {
                a2 = 'X';
            }
            else{
                a2 = toupper(text.at(i+1));
            }
            if(a1 == a2)
            {
                a2 = 'X';
            }
            pairs.push_back(make_pair(a1,a2));
            cout<<a1<<" "<<a2<< " "<<i<<endl;
        }
    }

    cout<<"The Pairs Formed from the text are :- "<<endl;
    dispPairVectors(pairs);
    return pairs;
}

pair<int,int> IndexInMatrix(char c)
{
    pair<int,int> res;
    for(int i=0;i<5;i++)
    {
        for(int j=0;j<5;j++)
        {
            if(playfairMatrix[i][j] == c || c == 'I' && playfairMatrix[i][j] == 'J' || c == 'J' && playfairMatrix[i][j] == 'I')
            {
                res = make_pair(i,j);
                return res;
            }
        }
    }
    return res;
}
pair<char,char> generalCase(pair<char,char> substring) //When the letters are not in the same row or column etc.
{
    pair<int,int> coord1,coord2;
    pair<char,char> cipherstring;
    coord1 = IndexInMatrix(substring.first);
    coord2 = IndexInMatrix(substring.second);

    cipherstring = make_pair(playfairMatrix[coord1.first][coord2.second],playfairMatrix[coord2.first][coord1.second]);

    return cipherstring;
}

pair<char,char> sameRow(pair<char,char> substring) // When the letters are on the same row of the playFair Matrix
{
    pair<int,int> coord1,coord2;
    pair<char,char> cipherstring;
    coord1 = IndexInMatrix(substring.first);
    coord2 = IndexInMatrix(substring.second);

    cipherstring = make_pair(playfairMatrix[coord1.first][coord1.second+1],playfairMatrix[coord2.first][coord2.second+1]);

    return cipherstring;
}

pair<char,char> sameColumn(pair<char,char> substring) // When the letters are on the same column of the playFair Matrix
{
    pair<int,int> coord1,coord2;
    pair<char,char> cipherstring;
    coord1 = IndexInMatrix(substring.first);
    coord2 = IndexInMatrix(substring.second);

    cipherstring = make_pair(playfairMatrix[coord1.first+1][coord1.second],playfairMatrix[coord2.first+1][coord2.second]);
    return cipherstring;
}

string PlayFairEncode(vector<pair<char,char>> result)
{
    string encodedString = "";
    pair<int,int> coord1,coord2;
    pair<char,char> substring,encodedPair;
    
    cout<<"The Encoded Pairs are :-"<<endl;
    for(int i=0;i<result.size();i++)
    {
        substring = result.at(i);
        coord1 = IndexInMatrix(substring.first);
        coord2 = IndexInMatrix(substring.second);

        if(coord1.first == coord2.first){encodedPair = sameRow(substring);}
        else if(coord1.second == coord2.second){encodedPair = sameColumn(substring);}
        else{encodedPair = generalCase(substring);}

        encodedString += encodedPair.first; 
        encodedString += encodedPair.second;

        cout<<encodedPair.first<<" "<<encodedPair.second<<endl;
    }

    return encodedString;
}

//Driver Code
int main()
{
    string text;
    cout<<"Enter the Text you want to Encode using PlayFair Cipher";
    getline(cin,text);
    string key;
    cout<<"Enter the Key : ";
    getline(cin,key);

    createPlayFairMatrix(key);

    vector<pair<char,char>> result =  PlainText_To_Pairs(text);

    string encodedString = PlayFairEncode(result);
    cout<<"The Encoded String is : "<<encodedString<<endl;
}
