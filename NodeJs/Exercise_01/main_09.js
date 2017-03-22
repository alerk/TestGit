console.log("Utility modules: 5 types");
console.log("1. OS Module: Basic OS related utility functions");
console.log("2. Path Module: Handling and transforming file paths");
console.log("3. Net Module: Servers and clients as streams. Network wrapper");
console.log("4. DNS Module: Functions to do actual DNS lookup as well as to use underlying OS name resolution");
console.log("5. Domain Module: Ways to handle multiple different I/O operations as single group");
console.log("OS module example");
var os_module = require('./os_module');

console.log("Path module example");
var path_module = require('./path_module');

console.log("Net module example");
var net_module = require('./net_module');

console.log("DNS module example");
var dns_module = require('./dns_module');

console.log("Domain module example");
var domain_module = require('./domain_module');