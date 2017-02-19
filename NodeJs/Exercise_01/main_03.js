/* 
   In node application, any async function accepts a callback as the las
   parameter and a callback function accepts an error as the first parameter.

*/
// Import events module
var events = require('events');

// Create an eventEmitter object
var eventEmitter = new events.EventEmitter();

// Create an event handler as follows
var connectHandler = function connected() {
    console.log('connection successful.');

    //Fire the data-received event
    console.log('inside connected function, emit \'data_received\' event');
    eventEmitter.emit('data_received');
}

// Bind the connection event with the handler
eventEmitter.on('connection', connectHandler);

// Bind the data_received event with the anonymous function
eventEmitter.on('data_received', function() {
    console.log('data received successfully');
});

// Fire the connection event
eventEmitter.emit('connection');
for(var i=0;i<10;i++)
{
    eventEmitter.emit('connection');
}
console.log("Program ended");
