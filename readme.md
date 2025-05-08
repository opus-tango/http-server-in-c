## Final Project Plan Update - Thursday night (2025-05-08)
The HTTP server has gotten much larger and more complex than I originally anticipated, and once I implement file uploading, it will meet all the requirements of the final project assignment. With that in mind, I have decided to scrap all my other plans and just submit the HTTP server as my final project, since I am also beginning to run out of time to develop a web application front and back end.

This evening I finally worked through the bugs on handling file serving, and have been able to get it working with arbitrary file types. They are still restricted "for security reasons," but it can theoretically be expanded to any file type.

## Final Project Plan Update
Even though I haven't had time to work on it, I have been turning this project over in my mind for the past two weeks. I have wanted to build my own basic HTTP server for a while, and this is the only piece of homework due this week, so I have decided to make my final project a basic HTTP server.

~~I am also planning to create the car dealership app, but build it as a web app that uses my HTTP server, and modifies HTML and handles POST requests for the user interaction.~~
The project has ballooned in complexity, so I don't think I'm going to build an app on top of the server. [2025-05-07]

~~I still have not decided whether to use files, or spin up a redis instance to store state, but I'll deal with that when I come to it.~~
The assignment requirements include file reading and writing, so I will not be using redis. I plan to add uploads and downloads as features for the server. [2025-05-07]

I also plan to publish this as a portfolio project for my resume.

## TODO List
- [x] Get basic HTTP interaction working
- [x] Get url parsing working
- [x] Fix existing bugs in socket handling and TCP buffering
- [x] Finish code to parse HTTP requests
- [x] Update makefile to be more flexible
- [x] Add enums for method types
- [x] Add switch statement to handle different request types
- [x] Add functions to handle each request type
- [x] Finish code to build HTTP responses
- [x] Get html file serving working
- [ ] Make html page for uploading files
- [ ] Get POST requests working
- [ ] Implement file uploads (with restricted file types)
- [ ] Implement file indexing and serving a directory page
- ~~[ ] Create basic templating engine for HTML working~~
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