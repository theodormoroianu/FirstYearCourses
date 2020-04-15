var State = {
    date: "Now",
    data: ""
};

var express = require("express")
var fs = require('fs');

app = express()
app.use(express.json())

app.post('/api/sync_content', function(req, res) {
    console.log(req.body);
    State = req.body;
    console.log("Here");
    res.end("GOTHA");
});

app.post('/api/request_content', function(req, res) {
    console.log(req.body);
    res.end(JSON.stringify(State));
});

app.use(express.static('assets'));

app.use('/index.html', function(req, res) {
    fs.readFile("resources/index.html", function(err, text) {
        res.end(text);
    });
});

app.listen(3000);
