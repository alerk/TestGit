console.log("Streams");
console.log("4 types of streams:\n  -Readable: used for read");
console.log("  -Writable: used for write");
console.log("  -Duplex: used for both read&write");
console.log("  -Transform: output is based on input\n-----");

console.log("Each type of streams is an EvenEmitter. Some commonly used events");
console.log("  -data: when data is available to read");
console.log("  -end: when there is no more data to read");
console.log("  -error: when there is any error receiving/writing data");
console.log("  -finish: when all data has been flushed to underlying system");

console.log("-------------\n Demo read from a stream");
var fs = require("fs");
var data = '';
//Create a readable stream
var readerStream = fs.createReadStream('input.txt');

//Set the encoding to be utf8
readerStream.setEncoding("UTF8");

//Handle stream events --> data, end, and error
readerStream.on('data', function(chunk) {
    data += chunk;
});

readerStream.addListener("end", function(){
    console.log("readerStream: " + data);
});

readerStream.on('error', function (err){
    console.log("Handle error from event\n==>"+err.stack);
});

console.log("--------------\n Demo write to a stream");
var data = 'Simply Easy Learning\n';

//Create a writable stream
var writerStream = fs.createWriteStream("output.txt");

//Write the data to stream with encoding to be utf-8
writerStream.write(data, 'UTF8');

// Mark the end of file
writerStream.end();

//Handle stream events --> finish, and error
writerStream.on('finish', function() {
    console.log('Write completed');
});

writerStream.on('error', function(err) {
    console.log('Error throws: ' + err.stack);
});

console.log("------------\n Demo piping stream");
var writerStream1 = fs.createWriteStream("pipeOutput.txt");

//Pipe the read and write operations
//Read input.txt and put data to pipeOutput.txt
readerStream.pipe(writerStream1);
console.log("-----------\n Demo chaining stream");
var zlib = require("zlib");
console.log("Compress input.txt and put it to input.txt.gz");
fs.createReadStream("input.txt")
.pipe(zlib.createGzip())
.pipe(fs.createWriteStream("input.txt.gz"));
console.log("File compressed");

console.log("----\nDecompress input.txt.gz and put it to file unzip.txt");
var outputUnzipWriterStream = fs.createWriteStream("unzip.txt");
console.log("pipe to unzip.txt")
fs.createReadStream("input.txt.gz")
.pipe(zlib.createGunzip().on('error', function(err) {
    console.log("unzip error: " + err.stack);
})
)
.pipe(outputUnzipWriterStream);

outputUnzipWriterStream.end();
outputUnzipWriterStream.on('data', function(chunk) {
    data += chunk; 
});

outputUnzipWriterStream.addListener("end", function(){
    console.log("outputUnzipWriterStream ended!: " + data);
});

outputUnzipWriterStream.on('error', function (err){
    console.log("Handle error from event\n==>"+err.stack);
});

console.log("File decompressed");
outputUnzipWriterStream.emit('end');

console.log("Program Ended");

