//path_module.js
var path = require("path");

module.exports = {
    examplePathModule: function() {
        console.log("From path_module.js");
        //Normalize(p);
        var p = "/test/test1//2slashes/1slash/tab/..";
        console.log("Normalize(" + p + "): " + path.normalize(p)+"\n");
        //join(path1[, path2][, ...]);
        console.log("'test', 'test1', '2slashes/1slash', 'tab', '..'" + 
            path.join('test', 'test1', '2slashes/1slash', 'tab', '..') + "\n");
        //resolve([from ...], to);
        console.log("resolve: " + path.resolve('main_09.js') + "\n");
        //extName
        console.log("ext name: " + path.extname('main_09.js') + "\n");
    }
};
