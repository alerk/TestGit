// Step 1 - IMport required modul
/**
 * We use the require directive to load the http module and store the returned 
 * HTTP instance into an http variable as follows
 */

var http = require("http");

// Step 2 - Create Server
http.createServer(function (request, response) {
    //Send the HTTP header
    //HTTP status: 200: OK
    //Content Type: text/plain
    response.writeHead(200, {'Content-Type': 'text/plain'});

    //Send the response body as 'Hello world"
    response.end("Hello World!");
}).listen(8081);

//Console will print the message
console.log("Server running at http://127.0.0.1:8081");

/**
 * REPL stands for Read Eval Print Loop and it represents a computer environment
 * like a Windows console or Unix/Linux shell where a command is entered an the
 * system responds with an output in an interactive mode.
 * - Read: read the user's input, parses the input to JavaScript data-structure,
 * and stores in the memory
 * - Eval: takes and evaluates the data structure
 * - Print: prints the result
 * - Loop: loops the above command until the user presses Ctrl+c twice
 */

/**
 * Node Package Manager (NPM) provides 2 main functions:
 - Online repositories for node.js packages/modules which are searchable on
   search.nodejs.org
 - Command line utility to install Node.js packages, do version management and
   dependency management of Node.js packages.
 */
