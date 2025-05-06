## Final Project Plan Update
Even though I haven't had time to work on it, I have been turning this project over in my mind for the past two weeks. I have wanted to build my own basic HTTP server for a while, and this is the only piece of homework due this week, so I have decided to make my final project a basic HTTP server.

I am also planning to create the car dealership app, but build it as a web app that uses my HTTP server, and modifies HTML and handles POST requests for the user interaction. 

I still have not decided whether to use files, or spin up a redis instance to store state, but I'll deal with that when I come to it.

I also plan to publish this as a portfolio project for my resume.

## TODO List
- [x] Get basic HTTP interaction working
- [x] Get url parsing working
- [ ] Get file serving working
- [ ] Create basic templating engine for HTML working
- [ ] Get POST requests working
- [ ] Set up database (files or redis)
- [ ] Create car dealership "classes"
- [ ] Create car dealership app
- [ ] Publish as a portfolio project



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