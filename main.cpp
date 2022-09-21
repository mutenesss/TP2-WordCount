#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

list<string> data;
list<string> words;
list<int> word_freq;

void read_file(){
    string aux;
    ifstream file("input.txt");
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

void scan(){
    for(int i = 0; data.size() > 0; i++){
        string aux = data.front();
        data.pop_front();
        string word;
        aux.erase(remove_if(aux.begin(), aux.end(), ::isspace), aux.end());
        for(int j = 0; j < aux.size(); j++){
            if(aux[j] != ' '){
                word += aux[j];
            }
            else{
                words.push_back(word);
                word = "";
            }
        }
        if(word != ""){
            words.push_back(word);
        }
    }
}

void remove_stop_words(){
    list<string> stop_words;
    string aux;
    ifstream file("stop-words.txt");
    while(getline(file, aux, ',')){
        stop_words.push_back(aux);
    }
    // Adicao do alfabeto a lista de stop_words
    for (int a = 'a'; a <= 'z'; a++){
        string aux;
        aux += a;
        stop_words.push_back(aux);
    }
    /*
    Tudo que tem dessa parte pra baixo eu nao tenho garantia
    que ajuda, mas existe.
    A comparacao dentro do for esta com problema, pois ela esta
    encontrando apenas valores que se repetem nas stop_words

    anterior a remocao, eh pra lista words ter tamanho 148 e
    a lista data ter tamanho 0
    // list<int> indexes;

    // for(int i = 0; i < words.size(); i++){
    //     string aux = words.front();
    //     words.pop_front();
    //     if(find(stop_words.begin(), stop_words.end(), aux) == stop_words.end()){
    //         words.push_back(aux);
    //     }
    //     else{
    //         indexes.push_back(i);
    //     }
    // }

    // indexes.sort(greater<int>());
    
    // for(int i = 0; indexes.size() > 0; i++){
    //     int aux = indexes.front();
    //     indexes.pop_front();
    //     words.erase(aux);
    // }
    */

}

int main(){
    read_file();
    filter_and_normalize();
    scan();
    remove_stop_words();
    cout << words.size() << endl;
    // for (auto const &i: words) {
    //     std::cout << i << std::endl;}
    return 0;
}
