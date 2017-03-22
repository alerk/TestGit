console.log("Tutorial 8: Global Objects");
console.log("__filename: " + __filename);
console.log("/*-------*/");
console.log("__dirname: " + __dirname);
console.log("/*-------*/");
console.log("Prepare setTimeout(cb,ms): run cb after ms (millisecond)");
function printHello() {
    console.log("Hello");
}
var t = setTimeout(printHello,2000);
console.log("clear the timeout before hand");
clearTimeout(t);
console.log("\'Hello\' will not be printed after this line");
console.log("setInterval(cb, ms);");
var vit;
function clearMyInterval() {
    clearInterval(vit);
}
setTimeout(clearMyInterval, 7500);
vit = setInterval(printHello, 1500);
console.log("\'printHello()\' should go 4 rounds after this line");
console.log("Study more about console and process system object!");
process.on('exit', function(code){
        console.log("Program ended in process.on(\'exit\') with code: "+code+"!");
    });
console.log("Program ended outside exit event!");

