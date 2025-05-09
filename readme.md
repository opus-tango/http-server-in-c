# Simple HTTP Server

This project is a simple HTTP server that can serve static files. I had big plans for POST request support, a templating engine, and backend features, but just serving files turns out to be quite a lot of work, and I unfortunately ran out of time.

I was originally going to make a simple toy car dealership application for my final project, but I've wanted to write an HTTP server for a while, and since I had the time I decided to give it a shot. I'm proud that I was able to accomplish all this in just four days, especially since the basic file serving feature ballooned in complexity faster than I expected.

In hindsight there were a lot of decisions I would make differently around code architecture and organization, but I learned so, SO, much doing this project. It has definitely been worth the effort and mistakes even if it's a litte rough around the edges.

## How to use

The project is designed to be very straightforward to run. It includes a Makefile and a Dockerfile. It should work on any linux system with build essentials. I have used Ubuntu for development. If you are unsure of your environment or running on a non-linux system, the running it in a docker container is the easiest way to go.

### Deploying as a docker container

1. Make sure docker is installed on your system.
2. Clone the repository by running `git clone https://github.com/COS135-S2025/project-GShadow5.git`
3. Run the container by running `docker compose up` in the project root directory. (command may be `docker-compose up` on some versions and platforms)
4. Navigate to http://localhost:8080/index.html in your browser.
5. Navigate to other files found in the `public` directory, such as http://localhost:8080/image.png and http://localhost:8080/script.js
6. To stop the server you can hit ctrl+c in the terminal, or type `q` and hit enter.

### Building from source

1. Clone the repository by running `git clone https://github.com/COS135-S2025/project-GShadow5.git`
2. Build the project by running `make` in the project root directory (where the Makefile is).
3. Run the server by running `./webserver.out` in the project root directory.
4. Navigate to http://localhost:8080/index.html in your browser.
5. Navigate to other files found in the `public` directory, such as http://localhost:8080/image.png and http://localhost:8080/script.js
6. To stop the server you can hit ctrl+c in the terminal, or type `q` and hit enter.



### Note on running on a remote server
If you run the project on a remote server, you'll need to forward port 8080, correctly configure your firewall, and use the external IP address of the server instead of localhost. The details of remote hosting are out of scope for these instructions.

## Assignment checklist
- [x] Use malloc LL or dynamic array - See the header_kv array in the http_request struct in http_stuff.h and http_stuff.c
- [x] Use Makefile - I started out with the Makefile format from class, but that quickly became too cumbersome to work with, and I could not get incremental builds to work with the debug flag for some reason, so I upgraded to pattern matching and conditional compilation. It's still basic as make files go, but this is a small project.
- [x] Assignments via pointers - This used to be EVERYWHERE in this project, but as the complexity grew I started using string library functions more. See lines 50 - 57 of request_handler.c for an example of pointer assignment. You can also look at the early commit history to see if all over the place.
- [x] Loop through array with ptr increment/decrement - Used to be everywhere, but the only example left is line 16 of response_builder.c. Still meets the requirement though.
- [x] No memory leaks - I have verified that the server does not leak memory by running Valgrind. There is a warning about a *possible* memory leak with `pthread_create`, but that's normal for multithreaded applications. Since the thread detaches successfully, the memory that Valgrind is worried about gets collected by the OS when the thread terminates.
- [x] Reading and writing to files - Files are read every time a file is served; see response_build_static_file in response_builder.c. Files are written by the logger function in logging.c.
- [x] Github - Everything is on github, and the commit history is EXTENSIVE.
- [x] Switch statement - Used in response_build_static_file in response_builder.c and handle_request in request_handler.c.
- [x] Something not taught in class - See below

### Something[s] not taught in class
There are three major things not taught in class that are core to this project. 

1. The first is networking. It's an HTTP server and uses sockets to communicate. I've experimented with sockets before a few years ago before college, but this was the first time really digging into them.
2. The second is multithreading. I am quite comfortable with multithreading because of some of my higher level classes, and I enjoy it a lot. Definitely not something typically taught in a 100 level class.
3. Variadic arguments. I've never used variadic arguments before, but it was SUPER cool to find out I could make my own logging system. I've always wanted to do that, but most of the time I've been working in higher level languages that make it a nightmare. Variadic arguments are a awesome!


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
- [x] Add flexible logging with variadic arguments
- ~~[ ] Make html page for uploading files~~
- ~~[ ] Get POST requests working~~
- ~~[ ] Implement file uploads (with restricted file types)~~
- ~~[ ] Implement file indexing and serving a directory page~~
- ~~[ ] Create basic templating engine for HTML working~~
- [ ] Publish as a portfolio project

## Known issues
There is an issue where the CSS file is not being received properly when included in an HTML file on Firefox based browsers. It works fine on Chromium based browsers, and Firefox loads the CSS file just fine when loaded directly, so I'm not sure what the issue is. If Firefox is behaving strangely try it with something Chromium based.

I have not debugged the issue yet becayse I'm not hung up on broad compatability for the scale that this project is at, and it works fine on Chromium browsers.


## References
- [HTTP status codes](https://developer.mozilla.org/en-US/docs/Web/HTTP/Reference/Status)
- [How I built a simple HTTP server from scratch using C](https://dev.to/jeffreythecoder/how-i-built-a-simple-http-server-from-scratch-using-c-739): I used this to understand how to get started, but exapanded from it a lot.
- [strtok reference](https://www.geeksforgeeks.org/strtok-strtok_r-functions-c-examples/): Didn't end up using strtok, but it was one of the approaches I tried for parsing the incoming requests.
- Variadic arguments references:
    - [Variadic functions in C](https://www.geeksforgeeks.org/variadic-functions-in-c/)
    - [How to create function like printf](https://stackoverflow.com/questions/7031116/how-to-create-function-like-printf-variable-argument)
- I did not use any references for multithreading as I have used pthreads extensively for the last few semesters.
- [Makefile reference](https://www.gnu.org/software/make/manual/html_node/index.html): Used a bunch of this to understand how to write more complex makefiles.