#include <bits/stdc++.h>
using namespace std;
int word_count = 0;
//-----------------------------trie-------------------------------------
struct trie {
    bool isEndOfWord;
    unordered_map<char, trie*> map;
    string meaning;
};

class dictionary{
public:

    trie *root = nullptr;

    trie* getNewtrieNode(){
        trie* node = new trie;
        node->isEndOfWord = false;
        return node;
    }


    void insert(const string& str, const string& meaning){
        if (root == nullptr)
            root = getNewtrieNode();

        trie* temp = root;
        for (int i = 0; i < str.length(); i++) {
            char x = str[i];
            if (temp->map.find(x) == temp->map.end())
                temp->map[x] = getNewtrieNode();
                temp = temp->map[x];
        }
        if(temp->isEndOfWord) {
            temp->meaning += "\n";
            temp->meaning += meaning;
            return ;

        }
        temp->isEndOfWord = true;
        temp->meaning = meaning;
    }


    string getMeaning( const string& word){
        if (root == nullptr)
            return "";
        trie* temp = root;
        for (int i = 0; i < word.length(); i++) {
            temp = temp->map[word[i]];
            if (temp == nullptr)
                return "";
        }
        if (temp->isEndOfWord)
            return temp->meaning;
        return "";
    }
};

//------------------------------------------------------------------
signed  main() {
    dictionary obj;
    //---------------Inserting from database ------------------
    {
        ifstream cin("Test.txt");
        string s;
        while (getline(cin, s)) {
            if (s[0] == ' ')
                continue;
            string a = "", b = "";
            bool ck = 0;
            for (char c : s) {
                if (c >= 'A' && c <= 'Z')
                    c = tolower(c);
                if (c == ' ')
                    ck = 1;
                if (ck)
                    b += c;
                else
                    a += c;
            }
            if (a.size() == 0)
                continue;
            obj.insert(a, b);
            word_count++;
            //cout << a <<" " << b << endl;
        }
    }
    //------------------------------------------------------------------------
    while (1) {
        cout << "--------------Menu--------------------------" << endl;;
        cout << "1. Search a word" << endl;
        cout << "2. Add a word" << endl;;
        int c;
        cin >> c;
        if (c == 1) {
            string s;

            cout << "Enter the word " << endl;
            cin >> s;
            for(int i = 0; i < s.size(); i++){
                if(isupper(s[i]))
                    s[i] = tolower(s[i]);
            }
            string mean = obj.getMeaning(s);
            if (mean.size() == 0) {
                cout << "Sorry not in the data base" << endl;
            }
            else {
                cout << s << " :" << endl;
                cout << mean << endl;
            }
        }
        else {
            cout << "Enter the word" << endl;
            string s;
            cin >> s;
            cout << "Enter the meaning " << endl;
            string mean;
            for(int i = 0; i < s.size(); i++){
                if(isupper(s[i]))
                    s[i] = tolower(s[i]);
            }
            cin >> mean;
            obj.insert(s, mean);
            cout << "Sucessfully added" << endl;
        }
        system("pause");
        system("cls");
    }




    return 0;
}
