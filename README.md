# LIBRARY-MANAGEMENT-SYSTEM

This C++ project implements a comprehensive Library Management System using Object-Oriented Programming (OOP) principles such as encapsulation, constructors (parameterized, copy, default), and data constraints. It manages books, members, and their interactions with full validation logic.

Library Management System involving three main classes:
  
    Book
    Member
    Library

The system enforces data constraints such as:
  
    1.Unique ISBN for books
    2.Unique member IDs
    3.Borrow and return limits
    4.Edge case handling for invalid operations

Class Structure:

  Class Book: Represents a book in the library.
      
      Attributes:
        title (public, string)
        author (public, string)
        isbn (private, string)
        copiesAvailable (private, int)
        totalCopies (private, int)
      
      Methods:
        Constructors:
          Parameterized
          With default arguments ("UnknownTitle", "UnknownAuthor", "ISBN", 0, 5)
          Copy constructor (copies all but allows a new ISBN)
        
        Getters:
          getISBN(), getCopiesAvailable(), getTotalCopies()
        
        Setters:
          updateCopies(count) – Ensures neither available nor total falls below 0.
        
        Utilities:
          bool borrowBook() – Decreases copiesAvailable, prints error if 0.
          bool returnBook() – Increases copiesAvailable up to totalCopies.
          void printDetails() – Outputs: title author
        
        Constraints:
          Unique ISBN across library
          copiesAvailable ∈ [0, totalCopies]

  Class Member : Represents a member of the library.
        
        Attributes:
        memberID (private, string)
        name (public, string)
        borrowedBooks (private, map<string, int>)
        borrowLimit (private, int) – default: 3
        
        Methods:
        Constructors:
        Parameterized (memberID, name, borrowLimit)
        Default limit constructor
        
        Utilities:
        bool borrowBook(isbn)
        bool returnBook(isbn)
        void printDetails() – Outputs per borrowed book: memberID name isbnOfBook numberOfBorrowedCopies
        
        Constraints:
        A member cannot borrow more than their borrowLimit (default: 3).
        A member can borrow multiple copies of the same book if available.

Class Library: Represents the full library system.
    
    Attributes:
      books (private, vector<Book>)
      members (private, vector<Member>)
    
    Methods:
      bool addBook(Book&)
      bool registerMember(Member&)
      bool borrowBook(string memberID, string isbn)
      bool returnBook(string memberID, string isbn)
      void printLibraryDetails()
    
    Output Format:
      Books: title author copiesAvailable
      Members: memberID name

Constraints & Limits
   
    Max 50 books
    Max 150 members
    Max 15 copies per book
    Max 15 total borrowed copies per member



Input Format
  
  The system processes structured commands:

        Book
        Title Author ISBN CopiesAvailable TotalCopies

        Book
        None
        
        Book
        ExistingBook OldISBN NewISBN
        
        UpdateCopiesCount
        ISBN NewCount
        
        Member
        MemberId Name BorrowLimit
        
        Member
        NoBorrowLimit MemberId Name
        
        Borrow
        MemberId ISBN
        
        Return
        MemberId ISBN
        
        PrintBook
        ISBN
        
        PrintMember
        MemberId
        
        PrintLibrary
        
        Done
        
 Output Format

    Book details:

      title author
    
    Member details:
      memberID name isbnOfBook numberOfBorrowedCopies
    
    Library overview:
      title author copiesAvailable
      memberID name
      
    ⚠️ Error Messages
      "Invalid request! Book with same isbn already exists"
      "Invalid request! Member with same id already exists"
      "Invalid request! Borrow limit exceeded"
      "Invalid request! Copy of book not available"
      "Invalid request! Book not borrowed"
      "Invalid request! Copy of book exceeds total copies"
      "Invalid request! Count becomes negative"       
              
  [Library Management System.pdf](https://github.com/user-attachments/files/20344876/Library.Management.System.pdf)
