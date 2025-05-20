#include<iostream>
#include<map>
#include<string>

using std::string;
using std::cout ;
using std::endl ;
class Member{
    public:
    string name; // (public, string): Name of the member.

    //constructors - start 
    Member(string id, string n, int blimit);
    Member(string id, string n);
    //constructors - end

    // getter - start
    string getid();
    // getter - end

    //utility methods - start

    bool borrowBook(string isbn);
    
    bool returnBook(string isbn);
    
    void printDetails();

    //member utility - end

    private:
    string memberID; // (private, string): Unique identifier for the member.
    std::map<string,int> borrowedBooks; // (private, map<string, int>): Map of isbn to the number of borrowed copies.
    int borrowLimit; // (private, int): Maximum number of books a member can borrow at a time (by default: 3).

};

Member::Member(string id, string n, int blimit){
    memberID = id ;
    name = n ;
    borrowLimit = blimit ;
}

Member::Member(string id, string n){
    memberID = id ;
    name = n ;
    borrowLimit = 3 ;
}

string Member::getid(){
    return memberID ;
}

bool Member::borrowBook(string isbn){
    int booksborrowed = 0;
    for(auto x : borrowedBooks){
        booksborrowed += x.second ;
    }
    if ( booksborrowed < borrowLimit){
        borrowedBooks[isbn]++ ;
        return true ;
    }
    else{
        cout << "Invalid request! Borrow limit exceeded" << endl ;
    }
    return false ;
}

bool Member::returnBook(string isbn){
    auto ptr = borrowedBooks.find(isbn) ;
    if(ptr != borrowedBooks.end()){
        if(borrowedBooks[isbn] > 0 ){
            borrowedBooks[isbn]-- ;
            return true ;
        }
    }
    cout << "Invalid request! Book not borrowed" << endl ;
    return false ;
}

void Member::printDetails(){
    for(auto x : borrowedBooks){
        if(x.second != 0)
        cout << memberID << " " << name << " " << x.first << " " << x.second << endl ;
    }
}