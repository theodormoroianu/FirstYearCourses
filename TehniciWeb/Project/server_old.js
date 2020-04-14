var http = require("http");
var fs = require('fs');
var port = 3000;
var serverUrl = "127.0.0.1";
var counter = 0;

/// definition of the web server
var server = http.createServer(function(req, res) {

    /// counter and logger for debug
    counter++;
    console.log("Request: " + req.url + " (" + counter + ")");

    /// handling POST requests
    if (req.method == "POST") {
        console.log(req);
        res.setHeader("Content-Type", "text/JSON");
        res.end("{'value': '123'}");
        return;
    }

    /// handling needed files
    if(req.url == "/index.html") {
        fs.readFile("index.html", function(err, text){
        res.setHeader("Content-Type", "text/html");
        res.end(text);
        });
        return;
    }
    if(req.url == "/webstyle.css") {
        fs.readFile("webstyle.css", function(err, text){
        res.setHeader("Content-Type", "text/css");
        res.end(text);
        });
        return;
    }
    if (req.url == "/webscript.js") {
        fs.readFile("webscript.js", function(err, text){
        res.setHeader("content-Type", "text/script");
        res.end(text);
        });
        return;
    }
});

console.log("Starting web server at " + serverUrl + ":" + port);
server.listen(port, serverUrl);