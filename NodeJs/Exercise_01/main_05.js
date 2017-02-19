var buf = new Buffer(26).fill(0);
var myString = "Xin chao, toi ten la Quyen\0";
var myBuf = new Buffer(myString.length+66).fill(0);
var offset = 0;
console.log("==================");
console.log("Write to buf with encoding");
var len = myString.length;
console.log("myString.len = " + len);
var writeLen = myBuf.write(myString, offset, len, 'utf-8'); //will try default encoding later
console.log('Num of bytes written: ' + writeLen);
console.log('Read myString from myBuf: ' + myBuf.toString('utf-8'));
console.log('Write to buf without encoding');
myBuf.write(myString, offset+5, len); // without encoding param
var start = 3;
var end = start + len;
console.log("Read again from myBuf: " + myBuf.toString('utf-8', start, end));

console.log("==================");
console.log("Convert to JSON");
var json = myBuf.toJSON(myBuf);
//console.log(json);

console.log("==================");
console.log("Concat 2 buffer");
var buf1 = new Buffer('TutorialsPoint ');
var buf2 = new Buffer("Simply Easy Learning");
var buf3 = Buffer.concat([buf1, buf2]);
console.log("Buf1: " + buf1 + "\nBuf2: " + buf2 + "\nBuf3: " + buf3);

console.log("==================");
console.log("Compare 2 buffers: buf1 & buf3: "+buf3.compare(buf1));

console.log("==================");
console.log("Copy part of myBuf to new buffer");
var targetStart = 0;
var sourceStart = 0;
var sourceEnd = len/2;
myBuf.copy(buf, targetStart, sourceStart, sourceEnd);
console.log("Result: " + buf.toString());
console.log("==================");
console.log("Slice buffer: " + buf.slice(2, 6));

console.log("Program ended");
