console.log("NodeJS tutorial: file system");
var fs = require("fs");

//Asynchronous read
fs.readFile('input.txt', function(err, data) {
    if(err) {
       // return console.error("Error handling function: " + err);
        return console.error(err);
    }
    console.log("Asynchronous read: " + data.toString());
});

//Synchronous read
var data = fs.readFileSync('input.txt');
console.log('Synchronous read: ' + data.toString());

console.log("\n/*--- Open a file ---*/");
console.log("fs.open(path, flags[, mode], callback);");
console.log("flags: indicate the behavior of the file to be opened. All possible values are:");
console.log(" r: Open for reading;");
console.log(" r+: Open file for reading and writing, exception when file not exist");
console.log(" rs: Open file for reading in synchronous mode");
console.log(" rs+: Open file for reading/writing synchronously");
console.log(" w: Open file for writing, file is created or truncated");
console.log(" wx: Like 'w' but fails if file exists");
console.log(" w+: Like 'w' with read ability");
console.log(" wx+: Like 'wx' with read ability");
console.log(" a: Appending. File created if not exist");
console.log(" ax: Appending, fails if path exists.");
console.log(" a+: Appending and reading");
console.log(" ax+: Like a+ but fails if not exists");
console.log("mode: The file mode, but only if the file was created. It default's to 0666, readable and writeable");
console.log("callback: This is the callback function which get 2 args (err, fd)");
console.log("Example open a file");
// Asynchronous - Opening a file
console.log("Going to open file!");
fs.open('input.txt', 'r+', function(err, fd) 
{
    if(err) 
    {
        return console.error(err);
    }
    console.log("File opened successfully!");
});

console.log("Get file information");
console.log("Syntax: fs.stat(path, callback);");
console.log("path: Full path file");
console.log("callback: Callback func with (err, stats), stats = obj of fs.Stats class");
console.log("Going to get file info!");
fs.stat("input.txt", function(err,stats)
{
    if(err)
    {
        return console.error(err);
    }
    console.log(stats);
    console.log("Got file info successfully/n Check file type:");
    console.log("isFile ? " + stats.isFile());
    console.log("isDirectory ? " + stats.isDirectory());
});
console.log("Program Ended");
