#include<iostream>
#include<string>
#include"Class_Member.cpp"

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