var fs = require("fs");

var data = fs.readFileSync("input.txt");

console.log("This is the blocking example");
console.log(data.toString());
console.log("Program ended!");


console.log("This is the non-blocking example");
fs.readFile('input.txt', function(err, data) {
    if (err) return console.error(err);
    console.log(data.toString());
});
console.log("Program ended!");
