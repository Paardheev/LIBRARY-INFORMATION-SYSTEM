#include<iostream>
#include<string>
#include<vector>
#include<map>
#include<sstream>

using std::string ;
using std::cout ;
using std::cin ;
using std::endl ;

class Book{
    public:
    std::string title ;//(public, std::string): Title of the book.
    std::string author; //(public, std::string): Author of the book.
    
    //constructors - start
    Book(std::string t, std::string a, std::string i, int ca ,int tc );
    
    Book();
    
    Book(Book b, std::string newisbn );
    //constructors - end

    // getters - start
    
    std::string getisbn();

    int getcopiesAvailable();

    int gettotalCopies();

    //getters - end

    //setter - start

    void updateCopies(int count);

    // setter - end

    // utility-method - start
    
    bool borrowBook() ;

    bool returnBook() ;

    void printDetails() ;

    // utility-method - end

    private:
    std::string isbn ;//(private, std::string): Unique identifier for the book.
    int copiesAvailable; //(private, int): Number of available copies.
    int totalCopies ;//(private, int): Total copies of the book in the library.

};

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

class Library{
    public:

    // member - utility - start
    bool addBook(Book & b) ;

    bool registerMember(Member & m);

    bool borrowBook(string memberID, string isbn);

    bool returnBook(string memberID, string isbn);

    void printLibraryDetails();

    void updateBook(string preisbn, string postisbn);

    void printBook(string isbn);

    void printMember(string MemberId);

    void updateCopiesCount(string isbn, int b);
    
    // member - utility - end
    private:
    std::vector<Book> books ;
    std::vector<Member> members ;
};

Book::Book(std::string t, std::string a, std::string i, int ca ,int tc ){ 
    title = t ;
    author = a ;
    isbn = i ;
    copiesAvailable = ca ;
    totalCopies = tc ;
}

Book::Book(){
    title = "UnknownTitle";
    author = "UnknownAuthor" ;
    isbn = "ISBN" ;
    copiesAvailable = 0 ;
    totalCopies = 5 ;
}

Book::Book(Book b, std::string newisbn ){
    title = b.title ;
    author = b.author ;
    isbn = newisbn ;
    copiesAvailable = b.copiesAvailable ;
    totalCopies = b.totalCopies ;   
}

std::string Book::getisbn(){
    return isbn ;
}

int Book::getcopiesAvailable(){
    return copiesAvailable ;
}

int Book::gettotalCopies(){
    return totalCopies ;
}

void Book::updateCopies(int count){
    if((totalCopies + count) >= 0 && (copiesAvailable + count) >= 0 ) totalCopies += count , copiesAvailable += count ;
    else std::cout << "Invalid request! Count becomes negative" << std::endl ;
}

bool Book::borrowBook(){
    if(copiesAvailable){
        copiesAvailable-- ;
        return true ;
    }
    else std::cout << "Invalid request! Copy of book not available" << std::endl ;
    return false ;
}
bool Book::returnBook(){
    if(copiesAvailable < totalCopies){
        copiesAvailable++ ;
        return true ;
    }
    else std::cout << "Invalid request! Copy of book exceeds total copies" << std::endl ;
    return false ;
}
void Book::printDetails(){
    std::cout << title << " " << author << std::endl ;
}

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

bool Library::addBook(Book & b){
    for(auto & x : books){
        if(x.getisbn() == b.getisbn()){ 
            cout << "Invalid request! Book with same isbn already exists" << endl ;
            return false ;
        }
    }
    books.push_back(b);
    return true ;
}

bool Library::registerMember(Member & m){
    for(auto & x : members){
        if(x.getid() == m.getid()){
            cout << "Invalid request! Member with same id already exists" << endl ;
            return false ;
        }
    }
    members.push_back(m);
    return true ;
}
bool Library::borrowBook(string memberID, string isbn){
    // check if book is available
    int i = 0;
    for(auto & x : members){
        if(x.getid() == memberID) break ;
        i++;
    }
    for(auto & x : books){
        if(x.getisbn() == isbn){
            if(x.borrowBook()){
                if(members[i].borrowBook(isbn)) return true ;
                else x.returnBook() ;
            }
        }
    }
    return false ;
}
bool Library::returnBook(string memberID, string isbn){
    int i = 0;
    for(auto & x : members){
        if(x.getid() == memberID) break ;
        i++;
    }
    for(auto & x : books){
        if(x.getisbn() == isbn){
            if(x.returnBook()){
                if(members[i].returnBook(isbn)) return true ;
                else x.borrowBook() ;
            }
        }
    }
    return false ;
}
void Library::printLibraryDetails(){
    for(auto & x : books){
        cout << x.title << " " << x.author << " " << x.getcopiesAvailable() << endl ;
    }
    for(auto & x : members){
        cout << x.getid() << " " << x.name << endl ;
    }   
}
void Library:: updateBook(string preisbn, string postisbn){
    for(auto & x : books){
        if(x.getisbn() == preisbn){
            Book b(x,postisbn);
            books.push_back(b);
        }
    }
}
void Library::printBook(string isbn){
    for(auto & x : books){
        if(x.getisbn() == isbn) x.printDetails();
    }
}
void Library::printMember(string MemberId){
    for(auto & x : members){
        if(x.getid() == MemberId) x.printDetails();
    }
}
void Library::updateCopiesCount(string isbn, int b){
    for(auto & x  : books){
        if(x.getisbn() == isbn) x.updateCopies(b);
    }
}


int main(){

    Library l;

    string command;

    while(getline(cin,command)){

        if(command == "Done") break;

        if(command=="Book"){

            string line;
            
            getline(cin,line);
            
            std::istringstream mystring(line);
            
            string yourstring;
            
            mystring>>yourstring;
            
            if(yourstring=="None"){
                
                Book b;
                l.addBook(b);
            }
            else if(yourstring=="ExistingBook"){
                
                string oldisbn,newisbn;
                mystring>>oldisbn>>newisbn;
                l.updateBook(oldisbn,newisbn);
            }
            else{
                
                string title = yourstring, author, isbn;
                int copiesAvailable, totalCopies;
                mystring >> author >> isbn >> copiesAvailable >> totalCopies;
                Book bl(title, author, isbn, copiesAvailable, totalCopies);
                l.addBook(bl);
            }
        }
        else if (command == "Member") {
            
            string line;
            
            getline(cin, line);
            
            std::istringstream mystring(line);
            
            string first, id, name;
            
            int blimit;
            
            mystring >> first;

            if (first == "NoBorrowLimit") {
            
                mystring >> id >> name;
                Member ml(id,name);
                l.registerMember(ml);
            } else {
            
                id = first;
                mystring >> name >> blimit;
                Member ml(id,name,blimit);
                l.registerMember(ml);
            }
        }
        else if (command == "Return") {
            
            string memberId, isbn;
            cin >> memberId >> isbn;
            l.returnBook(memberId, isbn);
        }
        else if (command == "Borrow") {
            
            string memberId, isbn;
            cin >> memberId >> isbn;
            l.borrowBook(memberId, isbn);
        }
        else if (command == "PrintMember") {
            
            string memberId;
            cin >> memberId;
            l.printMember(memberId);
        }
        else if (command == "PrintBook") {
            
            string isbn;
            cin >> isbn;
            l.printBook(isbn);
        } 
        else if (command == "PrintLibrary") {
            
            l.printLibraryDetails();

        } else if (command == "UpdateCopiesCount") {
            
            string isbn;
            int Count;
            cin >> isbn >> Count;
            l.updateCopiesCount(isbn, Count);
            
        }
    }
}