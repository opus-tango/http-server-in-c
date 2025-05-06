## Final Project Plan Update
After thinking it over more, I am going to try building a webserver for user interaction. Whether that becomes big enough to be the whole final project, or I add a website to it, I don't know yet.


## Original Plan
I'm going to build a car dealership interface.

You can log in as a dealer or buyer. Both have inventories, but only dealers can add cars, and only buyers can add money. Buyers can buy cars from dealers. There are two files, one for users and one for transactions, that store the state of the system between sessions.

Malloc will be used to store the dynamic arrays. String handling with pointers will be used to deal with user input. All structs will come with constructors and destructors. The state of the program will be generated from the state of the files at startup, and will be saved to the files as changes occur in the program. A switch statement will be used to handle user input.

For the stretch goal I am considering making two programs, a "server" and a "client," so that multiple users can connect to the "server" concurrently with IPC. Alternatively, maybe make a nice colorized autocomplete interface.

Structs:
- Car struct
    - id
    - make
    - model
    - year
    - price
    - color
- User struct
    - id
    - username
    - password hash
    - user type (buyer, dealer)
    - list of cars
    - list of transaction ids (maybe)
    - money
- Transaction struct
    - id
    - date
    - car id
    - buyer id
    - seller id
    - price

Files:
- Transactions file
- Users file