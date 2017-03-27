//os_module.js
var os = require("os");
module.exports = {
    exampleOSModule: function() 
    { 
            console.log("From os_module.js"); 
            //Endianness
            console.log("Endiannes: " + os.endianness());

            //OS type
            console.log("OS type: " + os.type());

            //OS platform
            console.log("Platform: " + os.platform());

            //Total system memory
            console.log("Total mem: " + os. totalmem() + " bytes.");

            //Total free memory
            console.log("Free memory: " + os.freemem() + " bytes.");
    } 
};
