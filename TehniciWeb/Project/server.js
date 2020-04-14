var State = {
    date: "Now",
    data: "12312"
};

var express = require("express")
var fs = require('fs');

app = express()
app.use(express.json())

// app.use('/index.html', function(req, res) {
//     fs.readFile("resources/index.html", function(err, text) {
//         res.end(text);
//     });
// });

app.post('/api/sync_content', function(req, res) {
    console.log(req.body);
    res.end("GOTHA");
});

app.post('/api/request_content', function(req, res) {
    console.log(req.body);
    res.end(JSON.stringify(State));
});

app.use(express.static('resources'));

app.listen(3000);
