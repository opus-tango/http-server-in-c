# Simple HTTP Server

This project is a simple HTTP server that can serve static files. I had big plans for POST request support, a templating engine, and backend features, but just serving files turns out to be quite a lot of work, and I unfortunately ran out of time.

For bureaucratic reasons I took a 100 level CS course in my senior year, and since I had no final exams I went totally overboard for my final project. I always wanted to write my own HTTP server, and the final project was the perfect excuse to actually do it. Because of the scope of the program I consider it more of a personal project than a school assignment since I went FAR and above the assignemnt requirements just for the fun of it.

In hindsight there were a lot of decisions I would make differently around code architecture and organization, but I learned so, SO, much doing this project. It has definitely been worth the effort and mistakes even if it's a litte rough around the edges.

## How to use

The project is designed to be very straightforward to run. It includes a Makefile and a Dockerfile. It should work on any linux system with build-essential. I have used Ubuntu for development. If you are unsure of your environment or running on a non-linux system, then running it in a docker container is the easiest way to go.

### Deploying as a docker container

1. Make sure docker is installed on your system.
2. Clone the repository by running `git clone https://github.com/COS135-S2025/project-GShadow5.git`
3. Run the container by running `docker compose up` in the project root directory. (command may be `docker-compose up` on some versions and platforms)
4. Navigate to http://localhost:8080/index.html in your browser.
5. Navigate to other files found in the `public` directory, such as http://localhost:8080/image.png and http://localhost:8080/script.js
6. To stop the server you can hit ctrl+c in the terminal, or type `q` and hit enter.

### Building from source

1. If gcc and make are not installed, install them by running `sudo apt-get install build-essential`
2. Clone the repository by running `git clone https://github.com/COS135-S2025/project-GShadow5.git`
2. Build the project by running `make` in the project root directory (where the Makefile is).
3. Run the server by running `./webserver.out` in the project root directory.
4. Navigate to http://localhost:8080/index.html in your browser.
5. Navigate to other files found in the `public` directory, such as http://localhost:8080/image.png and http://localhost:8080/script.js
6. To stop the server you can hit ctrl+c in the terminal, or type `q` and hit enter.



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
- [ ] ~~Make html page for uploading files~~
- [ ] ~~Get POST requests working~~
- [ ] ~~Implement file uploads (with restricted file types)~~
- [ ] ~~Implement file indexing and serving a directory page~~
- [ ] ~~Create basic templating engine for HTML working~~
- [x] Publish as a portfolio project

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
