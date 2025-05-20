#include<iostream>
#include<vector>
#include"Class_Book.cpp"

using std::cout ;
using std::endl ;

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