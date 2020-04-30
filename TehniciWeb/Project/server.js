/// IMPORTING NECESSARY STUFF ---------------------------------------------------------------------------------------------------

var express = require("express")
var morgan  = require('morgan')

var fs = require('fs');
app = express()
app.use(express.json())
app.use(morgan())

var assert = (condition) => {
    if (!condition)
        throw "Assertion failed";
}

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
var user_already_exists_json = {
    authentification: {
        authentificated: false,
        message: "Username already exists"
    }
};
var invalid_username_json = {
    authentification: {
        authentificated: false,
        message: "Invalid Username"
    }
};
var invalid_password_json = {
    authentification: {
        authentificated: false,
        message: "Password is too short"
    }
};
var forbidden_resource_json = {
    authentification: {
        authentificated: false,
        message: "The resource you are trying to access is private"
    }
}
var authentification_ok_json = {
    authentification: {
        authentificated: true,
        message: "OK"
    }
}

/// verifies if a username is valid
var ValidUserName = str => {
    if ((typeof str) !== "string")
        return false;
    if (str.length == 0 || str.length > 100 ||
      str.match(/^[0-9a-z\._]*$/ig) === null)
        return false;
    return true;    
};

var ExistsUser = user => {
    if (fs.existsSync("data/users/" + user))
        return true;
    return false;
}

var ReadUser = user => {
    var str = fs.readFileSync("data/users/" + user).toString();
    user_data = JSON.parse(str);
    return user_data;
}

var WriteUser = user => {
    fs.writeFile("data/users/" + user.info.user, JSON.stringify(user), function (err) {
        if (err) {
            console.log("ERROR while tring to save data.");
            console.log(err);
        }
    });
}

var ReadNote = note => {
    var str = fs.readFileSync("data/notes/" + note).toString();
    note_data = JSON.parse(str);
    return note_data;
}

var WriteNote = note => {
    fs.writeFile("data/notes/" + note.note_id, JSON.stringify(note), function (err) {
        if (err) {
            console.log("ERROR while tring to save data.");
            console.log(err);
        }
    });
}

var CreateUniqueID = () => {
    var length = 20;
    var result           = '';
    var characters       = 'ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789';
    var charactersLength = characters.length;
    for ( var i = 0; i < length; i++ ) {
       result += characters.charAt(Math.floor(Math.random() * charactersLength));
    }
    return result;
}

// active tokens store for each token
// the user and the creation_date
active_tokens = { }

/// HANDLING AUTHENTIFICATION REQUEST -------------------------------------------------------------------------------------------

/// returns a new token for user or throws an error
var CreateToken = (user, password) => {
    var user_json = ReadUser(user);
    assert(user_json.password === password);
    var token = CreateUniqueID();

    active_tokens[token] = {
        user: user,
        creation_date: Date()
    }
    return token;
}

/// returns the user for a token of throws an error
var Authentificate = (token) => {
    assert(active_tokens.hasOwnProperty(token));
    return active_tokens[token].user;
}

app.post('/API/login', function(req, res) {
    var obj = req.body;
    try {
        if (!obj.hasOwnProperty('token'))
            obj[token] = CreateToken(obj.user, obj.passord);
        
        var user = Authentificate(obj.token);
        var user_json = ReadUser(user);
        
        user_json.authentification = {
            authentificated: true,
            message: "OK"
        };

        res.end(JSON.stringify(user_json));
    } catch (e) {
        res.end(JSON.stringify(wrong_user_or_password_json));
    }
});

/// HANDLING USER CREATION ------------------------------------------------------------------------------------------------------

app.post('/API/signup', function(req, res) {
    var obj = req.body;
    try {
        if (!ValidUserName(obj.user))
            res.end(invalid_username_json);
        else if (!obj.password.length < 6)
            res.end(invalid_password_json);
        else if (ExistsUser(obj.user))
            res.end(user_already_exists_json);
        else {
            var user_json = {
                authentification: {
                    authentificated: true,
                    message: "OK"
                },
                info: {
                    user: obj.user,
                    name: obj.name,
                    password: obj.password
                },
                config: {
                    sort_notes_by: "alphabetical",
                    sort_asc: true,
                    stay_signed_in: true,
                    avatar_url: "images/avatar.svg"
                },
                notes: []
            }

            WriteUser(user_json);
            user_json.info[token] = CreateToken(obj.user, obj.password);
            delete user_json.info.password;

            res.end(JSON.stringify(user_json));
        }
        
    } catch(e) {
        res.end(JSON.stringify(invalid_authentification_json));
    }
});

app.delete('/API/signout', function(req, res) {
    var obj = req.body;
    try {
        delete active_tokens[obj.token];
        res.end(JSON.stringify(authentification_ok_json));
    } catch(e) {
        res.end(JSON.stringify(invalid_authentification_json));
    }
});



/// HANDLING NOTES CRUD REQUESTS ------------------------------------------------------------------------------------------------------

app.post('/API/notes', (req, res) => {
    var obj = req.body;
    try {
        assert(active_tokens.hasOwnProperty(obj.token));
        user_json = ReadUser(active_tokens[obj.token].user);
        user_json.notes.push(CreateUniqueID());
        var note_data = obj.data;
        note_data.note_id = user_json.notes[user_json.notes.length - 1]; 
        WriteNote(note_data)

        res.end(JSON.stringify({
            authentification: {
                authentificated: true,
                message: "OK"
            },
            note_id: user_json.notes[user_json.notes.length - 1]
        }));
        WriteUser(user_json);

    } catch (e) {
        res.end(invalid_authentification_json);
    }
});

app.delete('/API/notes', (req, res) => {
    var obj = req.body;
    try {
        assert(active_tokens.hasOwnProperty(obj.token));
        user_json = ReadUser(active_tokens[obj.token].user);
        user_json.notes = user_json.notes.filter((el) => {
            return el !== obj.note_id;
        });
        res.end(JSON.stringify({
            authentification: {
                authentificated: true,
                message: "OK"
            }
        }));
        WriteUser(user_json);

    } catch (e) {
        res.end(invalid_authentification_json);
    }
});

app.get('/API/notes', (req, res) => {
    try {        
        var token = req.query.token;
        var note_id = req.query.note_id;

        assert(active_tokens.hasOwnProperty(token));
        user_json = ReadUser(active_tokens[token].user);

        if (!user_json.notes.includes(note_id))
            res.end(JSON.stringify(forbidden_resource_json));
        else {
            var note = ReadNote(node_id);
            res.end(JSON.stringify({
                authentification: {
                    authentificated: true,
                    message: "OK"
                },
                data: note
            }));
        }
    } catch (e) {
        res.end(invalid_authentification_json);
    }
});

app.put('/API/notes', (req, res) => {
    var obj = req.body;

    try {
        assert(active_tokens.hasOwnProperty(obj.token));
        user_json = ReadUser(active_tokens[obj.token].user);

        if (!user_json.notes.includes(obj.data.note_id))
            res.end(JSON.stringify(forbidden_resource_json));
        else {
            WriteNote(obj.data);
            res.end(JSON.stringify({
                authentification: {
                    authentificated: true,
                    message: "OK"
                }
            }));
        }
    } catch (e) {
        res.end(invalid_authentification_json);
    }
});

/// HANDELING SETTINGS CRUD SYNC ------------------------------------------------------------------------------------------------ 

app.put('/API/settings', function(req, res) {
    var obj = req.body;
    try {
        assert(active_tokens.hasOwnProperty(obj.token));
        user_json = ReadUser(active_tokens[obj.token].user);

        user_json.config = obj.config;
        if (obj.hasOwnProperty(info)) {
            if (obj.info.hasOwnProperty(name))
                user_json.info.name = obj.info.name;
            if (obj.info.hasOwnProperty(password))
                user_json.info.passord = obj.info.passord;
        }

        res.end({
            authentification: {
                authentificated: true,
                message: "OK"
            }
        });
    } catch (e) {
        res.end(JSON.stringify(invalid_authentification_json));
    }
});



/// HANDLING SCRIPT / HTML REQUESTS ---------------------------------------------------------------------------------------------

app.use(express.static('assets'));

// app.use('/index.html', function(req, res) {
//     fs.readFile("resources/index.html", function(err, text) {
//         res.end(text);
//     });
// });



/// STARTING SERVER -------------------------------------------------------------------------------------------------------------

app.listen(3000, () => console.log(`Listening on port 3000`));
