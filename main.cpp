#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>
#include <map>
#include <vector>
#include <utility>

using namespace std;
list<string> data;
list<string> words;
map<string, int> freq_words;
vector<pair<string, int>> vec;

// Funcao de leitura de arquivo
void read_file(string nome){
    string aux;
    ifstream file(nome);
    while(getline(file, aux)){
        data.push_back(aux);
    }
};

// Essa funcao considera apenas cararcteres alfabeticos (A - Z e a - z)
// todo o restante eh transformado em espaco
void filter_and_normalize(){
    for(int i = 0; i < data.size(); i++){
        string aux = data.front();
        data.pop_front();
        for(int j = 0; j < aux.size(); j++){
            if(isalpha(aux[j])){
                if (isupper(aux[j])){
                    aux[j] = tolower(aux[j]);
                }
            }
            
            else{
                aux[j] = ' ';
            }
        }
        data.push_back(aux);
    }

}

// Funcao de leitura de palavras
void scan(){
    for(int i = 0; data.size() > 0; i++){
        string aux = data.front();
        data.pop_front();
        string word;
        for(int j = 0; j < aux.size(); j++){
            if(aux[j] != ' '){
                word += aux[j];
            }
            else if (word != ""){
                words.push_back(word);
                word = "";
            }
        }
        if((word[0] >= 'a' ) and (word[0] <= 'z')){
            words.push_back(word);
        }
    }
}

// Preenchimento do map com as palavras do input
void fill_dict(){
    for (auto &word:words){
        if (freq_words.count(word)){
            freq_words[word] += 1;
        }
        else{
            freq_words[word] = 1;
        }
    }
}

void remove_stop_words(){
    string aux;
    // Adicao do alfabeto a lista de stop_words
    for (int a = 'a'; a <= 'z'; a++){
        string aux;
        aux += a;
        data.push_back(aux);
    }

    for(auto word:words){
        freq_words.erase(word);
    }
}

void sort_words(){
    for (auto &word:freq_words){
        vec.push_back(word);
    }
    sort(vec.begin(), vec.end(), [](const pair<string, int> &a, const pair<string, int> &b){
        return a.second > b.second;
    });
}

void print_freq(){
    for(int i = 0; i < 25 and i < vec.size(); i++){
        cout << i+1 << "º " << vec[i].first << " - " << vec[i].second << endl;
    }
}

int main(){
    read_file("frankenstein.txt");       
    filter_and_normalize();         
    scan();                         
    fill_dict();
    read_file("stop-words.txt");
    filter_and_normalize();
    words.clear();
    scan();
    remove_stop_words();
    sort_words();
    print_freq();
    return 0;
}