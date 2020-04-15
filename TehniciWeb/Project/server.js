/// IMPORTING NECESSARY STUFF ---------------------------------------------------------------------------------------------------

var express = require("express")
var fs = require('fs');
app = express()
app.use(express.json())



/// DECLARING USEFULL FUNCTIONS AND ERROR JSONS ---------------------------------------------------------------------------------

var invalid_authentification_json = {
    authentification: {
        authentificated: false,
        message: "Invalid JSON"
    }
};

var wrong_user_or_password_json = {
    authentification: {
        authentificated: false,
        message: "Inexistent username or invalid password"
    }
};

var user_already_exists = {
    authentification: {
        authentificated: false,
        message: "Username already exists"
    }
};

/// verifies if a username is valid
var ValidUserName = str => {
    if ((typeof str) !== "string")
        return false;
    if (str.length == 0 || str.length > 100 ||
      str.match(/^[0-9a-z\._]*$/ig) === null)
        return false;
    return true;    
};

/// returns the JSON of a user if it is valid and null otherwise
var Authentificate = info => {
    /// checks if the authentification JSON is invalid
    if (!info.hasOwnProperty("user") ||
      !info.hasOwnProperty("password"))
        return null;

    /// mostly for security reasons
    if (!ValidUserName(info.user))
        return null;
    
    /// try to read info from file and return if wrong password
    var user_data = null;
    try {
        var str = fs.readFileSync("data/" + info.user + ".sav").toString();
        user_data = JSON.parse(str);
        if (user_data.info.password !== info.password)
            return null;
    }
    catch (e) {
        return null;
    }

    /// got this far it means all is ok
    return user_data;
};

/// HANDLING AUTHENTIFICATION REQUEST -------------------------------------------------------------------------------------------

app.post('/API/login', function(req, res) {
    var obj = req.body;
    
    /// obj now contains the login info for the user. check README.md for more info
    if ((typeof obj) !== 'object' || !obj.hasOwnProperty("info")) {
        res.end(JSON.stringify(invalid_authentification_json));
        return;
    }

    /// call the Authentificate function that verifies the user / password
    var ans = Authentificate(obj.info);
    
    if (ans === null) {
        res.end(JSON.stringify(wrong_user_or_password_json));
        return;
    }
    
    /// got this far it means that the password is the good one (Yeeey)
    ans.authentification = {
        authentificated: true,
        message: "OK"
    };
    res.end(JSON.stringify(ans));
});



/// HANDLING USER CREATION ------------------------------------------------------------------------------------------------------

app.post('/API/signup', function(req, res) {
    var obj = req.body;
    
    /// first i have to check the obj is corect
    if ((typeof obj) !== 'object' || !obj.hasOwnProperty("info")) {
        res.end(JSON.stringify(invalid_authentification_json));
        return;
    }

    var info = obj.info;
    if ((typeof info) != 'object' || !info.hasOwnProperty("user") ||
      !info.hasOwnProperty("password") || !ValidUserName(info.user)) {
        res.end(JSON.stringify(invalid_authentification_json));
        return;
    }

    if (fs.existsSync("data/" + info.user + ".sav")) {
        res.end(JSON.stringify(user_already_exists));
        return;
    }

    fs.writeFile("data/" + obj.info.user + ".sav", JSON.stringify(obj), function (err) {
        if (err) {
            console.log("ERROR while tring to save data.");
            console.log(err);
        }
    });

    obj.authentification = {
        authentificated: true,
        message: "OK"
    };
    res.end(JSON.stringify(obj));
});



/// HANDLING SYNC REQUESTS ------------------------------------------------------------------------------------------------------

app.post('/API/checkpoint', function(req, res) {
    var obj = req.body;

    /// first i have to check the obj is corect
    if ((typeof obj) !== 'object' || !obj.hasOwnProperty("info")) {
        res.end(JSON.stringify(invalid_authentification_json));
        return;
    }

    var ans = Authentificate(obj.info);
    
    if (ans === null) {
        res.end(JSON.stringify(invalid_authentification_json));
        return;
    }

    if (obj.info.hasOwnProperty("new_password") &&
      obj.info.new_password.length > 0) {
          obj.info.password = obj.info.new_password;
          obj.info.new_password = "";
    }

    fs.writeFile("data/" + obj.info.user + ".sav", JSON.stringify(obj), function (err) {
        if (err) {
            console.log("ERROR while tring to save data.");
            console.log(err);
        }
    });

    obj.authentification = {
        authentificated: true,
        message: "OK"
    };
    res.end(JSON.stringify(obj));
});



/// HANDLING SCRIPT / HTML REQUESTS ---------------------------------------------------------------------------------------------

app.use(express.static('assets'));

// app.use('/index.html', function(req, res) {
//     fs.readFile("resources/index.html", function(err, text) {
//         res.end(text);
//     });
// });



/// STARTING SERVER -------------------------------------------------------------------------------------------------------------

app.listen(3000);
