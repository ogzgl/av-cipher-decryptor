#include <cstdlib>
#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
using namespace std;

static string read_text_file(const string& filename);
int key_length();
int get_position(char c);
int get_position(char c);
char get_letter(int position);
int find_plain_letter(int indexer,int cipherLetter);
int alphabet_size();
void find_key_pairs(int keyIndexer);
void print_key_pairs();
void print_all_plain();
int encyrpt(int key, int key2, int cipher);
char find_plain_letter(int key, int key2,int cipherLetter);
void fill_array();

int keyLength;
string s;
char alphabet[29] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z', ' ', '-', '.'};
int alphabetSize;
double alphabetProbabilities[29] = {8.167, 1.492, 2.782, 4.253, 12.702,2.228,2.015,6.094,6.966,0.153,0.772,4.025,2.406,6.749,7.507,1.929,0.095,5.987,6.327,9.056,2.758,0.978,2.360,0.150,1.974,0.074,18.288,1.530,6.530};
int keyPairs[23][2];
char cipherText[3627];

int main(){

  const string filename = "220201015.cipher.txt";
  s = read_text_file(filename);
  keyLength=key_length();
  std::cout << "Key Length is: "<< keyLength << '\n';
  std::cout << "Text file size is: "<< s.size() << '\n';
  alphabetSize=alphabet_size();
  for(int i=0;i<keyLength;i++){
    find_key_pairs(i);
  }
  keyPairs[2][0]=1;keyPairs[2][1]=29;
  keyPairs[3][0]=1;keyPairs[3][1]=29;
  keyPairs[20][0]=12;keyPairs[20][1]=21;
  print_key_pairs();
  fill_array();
  print_all_plain();
  return EXIT_SUCCESS;
}

void fill_array(){
  for(int i=0;i<3627;i++){
    cipherText[i]=s[i];
  }
}
void find_key_pairs(int keyIndexer){
  double maxResult=0.0;
  double tempFrequency[29];
  double result;
  int c;
  for(int i=1;i<29;i++){
    for(int j=1;j<29;j++){
      fill_n(tempFrequency,alphabetSize,0);
      for(int q=0;q<3611;q++){
        if(q%23==keyIndexer){
          c = encyrpt(i,j,get_position(s[q]));
          tempFrequency[c]+=1;
        }
      }
      result=0.0;
      for(int k=0;k<29;k++){
        result+=alphabetProbabilities[k]*tempFrequency[k];
      }
      if(result>maxResult){
        maxResult=result;
        keyPairs[keyIndexer][0]=i;
        keyPairs[keyIndexer][1]=j;
      }
    }
  }
}

int alphabet_size(){
  return (sizeof(alphabet)/sizeof(*alphabet));
}
int key_length(){
  int key_length =0, i=1, possible_key=0, occurence_counter=0,max_occurence=0;
  while (i<40){
    for (int x=0;x<s.size();x++){
      if (x+i>s.size()-1){
        break;
      }
      if(s[x]==s[x+i]){
        occurence_counter+=1;
      }
    }
    if (occurence_counter>max_occurence){
      max_occurence=occurence_counter;
      possible_key=i;
    }
    i+=1;
    occurence_counter=0;
  }
  return possible_key;
}
int encyrpt(int key, int key2, int cipher){
  return (((key*cipher)+key2)%29);
}
char find_plain_letter(int key, int key2,int cipherLetter){
  return alphabet[((key*cipherLetter)+key2)%29];
}
void print_all_plain(){
    char c;
    for(int i=0;i<3627;i++){
        c=find_plain_letter(keyPairs[i%23][0],keyPairs[i%23][1], get_position(cipherText[i]));
        cout<<c;
    }
    cout<<endl;
}
string read_text_file(const string& filename){
  ifstream fin(filename.c_str());
  if (!fin.is_open()) {
    cerr << "Error opening file " << filename << " for reading" << endl;
    exit(EXIT_FAILURE);
  }
  stringstream sstr;
  sstr << fin.rdbuf();
  return sstr.str();
}

int get_position(char c){
  for(int i=0;i<alphabetSize;i++){
    if(alphabet[i]==c){
      return i;
    }
  }
}
void print_key_pairs(){
  for(int i=0;i<23;i++){
    std::cout << i<<". key pair: " << keyPairs[i][0]<< " and "<< keyPairs[i][1] << '\n';
  }
}
char get_letter(int position){
  return alphabet[position];
}
