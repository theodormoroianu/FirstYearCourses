var express = require("express")
var fs = require('fs');
app = express()
app.use(express.json())

app.get("/dogs", (req, res) => {
    console.log("Received a get request");
    console.log(req.query);
    res.end(`{"Hello there":"asd"}`);
});

app.post("/dogs", (req, res) => {
    console.log("Received a post request");
    console.log(req.body);
    res.end(`{"Hello there":"asd"}`);
});

app.put("/dogs", (req, res) => {
    console.log("Received a put request");
    console.log(req.body);
    res.end(`{"Hello there":"asd"}`);
});


app.delete("/dogs", (req, res) => {
    console.log("Received a delete request");
    console.log(req.body);
    res.end(`{"Hello there":"asd"}`);
});

app.get("/", (req, res) => {
    res.redirect('/sample.html')
})


app.use(express.static('assets'));

app.listen(3000, () => console.log(`Listening on port 3000`));
