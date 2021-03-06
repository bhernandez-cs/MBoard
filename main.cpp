#include "board.h"

bool usernameExists(string username, ifstream &fin){
 bool exists = false;
 fin.open("userInfo.txt");
 string u;
 while(fin >> u){
  if(u == username){
   exists = true;
  }
 }
 fin.close();
 return exists;
}

void getUsername(string &username, ifstream &fin){
 cout << "Please enter desired username" << endl;
 cin >> username;
 while(usernameExists(username, fin)){
  cout << "Please enter an unused username please" << endl;
  cin >> username;
 }
}

void save(User user, ifstream &fin, ofstream &fout){
 //Saving to userInfo.txt
 bool exists = false;
 string s;
 vector<string> all;
 fin.open("userInfo.txt");
 while(fin >> s){
  if(s == user.getUName()){
   exists = true;
   break;
  }
  all.push_back(s);
 }
 fin.close();
 if(!exists){
  fout.open("userInfo.txt");
  for(int i = 0; i < all.size(); i++){
   fout << all[i] << endl;
  }
  fout << user.getUName() << endl;
  fout << user.getPWord() << endl;
  fout << user.getID() << endl;
  fout << user.getType() << endl;
  fout.close();
 }

 //Saving to indexes.txt
 int x;
 vector<int> ind;
 if(exists){
  fin.open("indexes.txt");
  while(fin >> x){
   ind.push_back(x);
   if(x == user.getID()){
    while(fin >> x){
     if(x == user.getID()){
      for(int i = 0; i < (user.getIndexes()).size(); i++){
       ind.push_back((user.getIndexes()).at(i));
      }
      ind.push_back(x);
      break;
     }
    }
   }
  }
  fin.close();
  fout.open("indexes.txt");
  for(int i = 0; i < ind.size(); i++){
   fout << ind[i] << endl;
  }
  fout.close();
 }
 else{
  fin.open("indexes.txt");
  while(fin >> x){
   ind.push_back(x);
  }
  fin.close();
  fout.open("indexes.txt");
  for(int i = 0; i < ind.size(); i++){
   fout << ind[i] << endl;
  }
  fout << user.getID() << endl;
  for(int i = 0; i < (user.getIndexes()).size(); i++){
   fout << (user.getIndexes()).at(i) << endl;
  }
  fout << user.getID() << endl;
  fout.close();
 }
}

void mainMenu(User &user, ifstream &fin, ofstream &fout){
 user.load();
 int i = user.getType();
 bool exit = false;
 char c;
 while(!exit){
  cout << endl << endl << endl;
  cout << "e - Exit the program" << endl;
  switch(i){
   case 0:
    cout << "a - Show all users" << endl;
    cout << "b - Show messages by a specific user" << endl;
    cout << "c - Delete a specific user" << endl;
    cin >> c;
      if(c == 'a'){
       user.allUsers();
      }
      else if(c == 'b'){
       string sb;
       cout << "Enter the username of the user whose messages are to be viewed" << endl;
       cin >> sb;
       user.messagesBy(sb);
      }
      else if(c == 'c'){
       string sc;
       cout << "Enter the username of the user to be deleted" << endl;
       cin >> sc;
       user.deleteUser(sc);
      }
      else if(c == 'e'){
       exit = true;
      }
      else{
       cout << "Incorrect input" << endl;
      }
    break;
   case 1:
    cout << "a - Post new advertisement" << endl;
    cout << "b - Delete previous advertisement" << endl;
    cout << "c - View all advertisements" << endl;
    cin >> c;
     if(c == 'a'){
      string s1, s2;
      cout << "Please enter the message for the advertisement" << endl;
      cin >> s1;
      cout << "Please enter the link to be included in the advertisement" << endl;
      cin >> s2;
      user.postAd(s1, s2);
     }
     else if(c == 'b'){
      int i;
      cout << "The indexes of the advertisements that you have posted are ";
      for(int j = 0; j < (user.getIndexes()).size(); j++){
       cout << (user.getIndexes()).at(j) << " ";
      }
      cout << endl << "Please input the index of the message to be deleted" << endl;
      cin >> i;
      bool possession = false;
      for(int j = 0; j < (user.getIndexes()).size(); j++){
       if(i == ((user.getIndexes()).at(j))){
        possession = true;
       }
      }
      if(possession == true){
       user.deleteAd(i);
      }
      else{
       cout << "You were not the creator of specified advertisement" << endl;
      }
     }
     else if(c == 'c'){
      user.viewAds();
     }
     else if(c == 'e'){
      exit = true;
     }
     else{ 
      cout << "Incorrect input" << endl;
     }
    break;
   case 2:
    cout << "a - Post new message" << endl;
    cout << "b - Delete previous message" << endl;
    cout << "c - View all messages" << endl;
    cin >> c;
     if(c == 'a'){
      string s1, s2;
      cout << "Please enter the message for the message board" << endl;
      cin >> s1;
      user.postMessage(s1);
     }
     else if(c == 'b'){
      int i;
      cout << "The indexes of the messages that you have posted are ";
      for(int j = 0; j < (user.getIndexes()).size(); j++){
       cout << (user.getIndexes()).at(j) << " ";
      }
      cout << endl << "Please input the index of the message to be deleted" << endl;
      cin >> i;
      bool possession = false;
      for(int j = 0; j < (user.getIndexes()).size(); j++){
       if(i == ((user.getIndexes()).at(j))){
        possession = true;
       }
      }
      if(possession == true){
       user.deleteMessage(i);
      }
      else{
       cout << "You were not the creator of specified message" << endl;
      }
     }
     else if(c == 'c'){
      user.viewAll();
     }
     else if(c == 'e'){
      exit = true;
     }
     else{ 
      cout << "Incorrect input" << endl;
     }
    break;
  }
 }
 save(user, fin, fout);  
}

int main(int argc, char* argv[]){
 string a1, a2;
 a1 = argv[1];
 a2 = argv[2];
 ifstream fin;
 ofstream fout;
 string username;
 string password;
 int id;
 int type;
 if(argc != 3){
  cout << "Error: Must enter username and password after program call" << endl;
  cout << "Example: ./main username password" << endl << endl;
  cout << "For a new user, type in ./main new user, no capitals." << endl;
  return 1;
 }
 else if(a1 == "new"){
  if(a2 == "user"){
   //Username and password creation
   getUsername(username, fin);
   cout << "Please enter desired password" << endl;
   cin >> password;
   //Unique user ID creation
   string s;
   vector<string> info;
   fin.open("userInfo.txt");
   int n;
   fin >> n;
   id = n + 1000;
   n+=1;
   while(fin >> s){
    info.push_back(s);
   }
   fin.close();
   //Writing everything back
   fout.open("userInfo.txt");
   fout << n << endl;
   for(int i = 0; i < info.size(); i++){
    fout << info[i] << endl;
   }
   fout.close();
   char c;
   cout << "Please enter 'y' if you would like this to be a business account" << endl;
   cin >> c;
   if(c == 'y'){
    type = 1; //business
   }
   else{
    type = 2; //general
   }
  }
  else{
   // ./main new user not typed in correctly
   return 1;
  }
 }
 else{
  bool found = false;
  string s;
  fin.open("userInfo.txt");
  while(fin >> s){
   if(s == a1){
    fin >> s;
    if(s == a2){
     found = true;
     username = a1;
     password = a2;
     fin >> id;
     fin >> type;
    }
    else{
     cout << "Entered password is incorrect" << endl;
     return 1;
    }
   }
  }
  if(!found){
   cout << "Entered username does not exist" << endl;
   return 1;
  }
 }
 User user(username, password, id, type, fin, fout);
 mainMenu(user, fin, fout);
 save(user, fin, fout);
 return 0;
}
