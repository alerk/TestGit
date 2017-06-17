var express = require('express');
var app = express();

// This function to handle get request
app.get('/', function (req, res) {
    console.log("Received GET for homepage");
    res.send('Hello GET!');
});

app.post('/', function (req, res) {
    console.log("Received POST for homepage");
    res.send('Hello POST!');
});

app.delete('/del_user', function (req, res) {
    console.log("Received DELETE for /del_user");
    res.send('Hello DELETE!');
});

app.get('/list_user', function (req, res) {
    console.log("Received GET for /list_user");
    res.send('page_listing!');
});

// This responds a GET request for ab*cd with wildcard
app.get('/ab*cd', function (req, res) {
    console.log("Received GET for /ab*cd");
    res.send('page pattern match!');
});

var server = app.listen(8081, function() {
    var host = server.address().address;
    var port = server.address().port;

    console.log("Example app listening at http://%s:%s", host, port);
})
