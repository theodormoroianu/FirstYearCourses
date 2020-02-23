// https://www.sitepoint.com/build-a-simple-web-server-with-node-js/

var http = require('http');

// include http module in the file
var http = require('http');
 
// create a server
http.createServer(function (req, res) {
    // code to feed or request and prepare response
}).listen(9000); //the server object listens on port 9000

// include http module in the file
var http = require('http');
 
// create a server
http.createServer(function (req, res) {
    // http header
    // 200 - is the OK message
    // to respond with html content, 'Content-Type' should be 'text/html'
    res.writeHead(200, {'Content-Type': 'text/html'}); 
    res.write('Node.js says hello!'); //write a response to the client
    res.end(); //end the response
}).listen(9001); //the server object listens on port 9000