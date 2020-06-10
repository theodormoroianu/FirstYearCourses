/// IMPORTING NECESSARY STUFF ---------------------------------------------------------------------------------------------------

var express = require("express");
var morgan  = require('morgan');
const { exec } = require('child_process');

var fs = require('fs');
app = express();
app.use(express.json());
app.use(morgan('tiny'));
app.set('trust proxy', true);

exec('mkdir ' + __dirname + '/data -p', (err, stdout, stderr) => { });
exec('mkdir ' + __dirname + '/data/notes -p', (err, stdout, stderr) => { });
exec('mkdir ' + __dirname + '/data/users -p', (err, stdout, stderr) => { });


/// DECLARING USED FUNCTIONS ----------------------------------------------------------------------------------------------------

var assert = (condition) => {
    if (!condition)
        throw "Assertion failed";
}

var log = (message) => {
    fs.appendFile('data/events.log', message, function (err) {
        if (err) throw err;
    });
}

var GetShortDate = () => {
    var oDate = new Date();
    var sDate;
    if (oDate instanceof Date) {
        sDate = oDate.getYear() + 1900
            + ':'
            + ((oDate.getMonth() + 1 < 10) ? '0' + (oDate.getMonth() + 1) : oDate.getMonth() + 1)
            + ':' + oDate.getDate()
            + ':' + oDate.getHours()
            + ':' + ((oDate.getMinutes() < 10) ? '0' + (oDate.getMinutes()) : oDate.getMinutes())
            + ':' + ((oDate.getSeconds() < 10) ? '0' + (oDate.getSeconds()) : oDate.getSeconds());
    } else {
        throw new Error("oDate is not an instance of Date");
    }
    return sDate + ' ';
}

var GetNiceDate = () => {
    return new Date().toString().replace(/T/, ':').replace(/\.\w*/, '');
}


/// DECLARING USEFULL JSONS AND ERROR JSONS ---------------------------------------------------------------------------------

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
};
var authentification_ok_json = {
    authentification: {
        authentificated: true,
        message: "OK"
    }
};

/// DECLARING I/O FUNCTIONS -----------------------------------------------------------------------------------------------------

/// verifies if a username is valid
var ValidUserName = str => {
    if ((typeof str) !== "string")
        return false;
    if (str.length == 0 || str.length > 100 ||
      str.match(/^[0-9a-z\._]*$/ig) === null)
        return false;
    return true;    
};

/// checks if a username exists
var ExistsUser = user => {
    if (fs.existsSync("data/users/" + user))
        return true;
    return false;
}

/// reads the user_json from user
var ReadUser = user => {
    var str = fs.readFileSync("data/users/" + user).toString();
    user_data = JSON.parse(str);
    return user_data;
}

/// writes a user_json to memory
var WriteUser = user => {
    fs.writeFileSync("data/users/" + user.info.user, JSON.stringify(user), function (err) {
        if (err) {
            console.log("ERROR while tring to save data.");
            console.log(err);
        }
    });
}

/// reads a note from node_id
var ReadNote = note => {
    var str = fs.readFileSync("data/notes/" + note).toString();
    note_data = JSON.parse(str);
    return note_data;
}

/// writes a note to memory
var WriteNote = note => {
    fs.writeFileSync("data/notes/" + note.note_id, JSON.stringify(note), function (err) {
        if (err) {
            console.log("ERROR while tring to save data.");
            console.log(err);
        }
    });
}

/// generates random tokens, for both notes and user tokens
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
active_tokens = { 1: { user: "123" } }



/// HANDLING AUTHENTIFICATION REQUEST -------------------------------------------------------------------------------------------

/// returns a new token for user or throws an error
var CreateToken = (user, password) => {
    var user_json = ReadUser(user);
    assert(user_json.info.password === password);
    var token = CreateUniqueID();

    active_tokens[token] = {
        user: user,
        creation_date: Date.now()
    }
    return token;
}

/// returns the user for a token of throws an error
var Authentificate = (token) => {
    assert(active_tokens.hasOwnProperty(token));
    assert((Date.now() - active_tokens[token].creation_date) / 1000 < 30 * 60);
    /// o sesiune e valida numai 30 de min
    return active_tokens[token].user;
}



/// USER AUTHENTIFICATION CRUD --------------------------------------------------------------------------------------------------

app.post('/API/login', function(req, res) {
    
    var ip = req.connection.remoteAddress;
    console.log(ip);

    var obj = req.body;

    log(GetShortDate() + "Received login request from " + obj.user + " ... ");

    try {
        if (!obj.hasOwnProperty('token'))
            obj['token'] = CreateToken(obj.user, obj.password);
        
        var user = Authentificate(obj.token);
        var user_json = ReadUser(user);
        delete user_json.info.password;
        user_json.info['token'] = obj.token;

        user_json['authentification'] = {
            authentificated: true,
            message: "OK"
        };

        res.end(JSON.stringify(user_json));
        log("ACCEPTED\n");
    }
    catch (e) {
        res.end(JSON.stringify(wrong_user_or_password_json));
        log("DECLINED\n");
    }
});

app.post('/API/signup', function(req, res) {
    var obj = req.body;

    log(GetShortDate() + "Received signup request from " + obj.user + " ... ");

    try {
        if (!ValidUserName(obj.user)) {
            res.end(JSON.stringify(invalid_username_json));
            log("DECLINED\n");
        }
        else if (obj.password.length < 6) {
            res.end(JSON.stringify(invalid_password_json));
            log("DECLINED\n");
        }
        else if (ExistsUser(obj.user)) {
            res.end(JSON.stringify(user_already_exists_json));
            log("DECLINED\n");
        }
        else {
            var user_json = {
                info: {
                    user: obj.user,
                    name: obj.name,
                    password: obj.password
                },
                config: {
                    sort_notes_by: "Alphabetical",
                    sort_asc: true,
                    stay_signed_in: true,
                    avatar_url: "images/avatar.svg"
                },
                notes: [CreateUniqueID()]
            };
            var welcome_note = {
                note_id: user_json.notes[0],
                head: 0,
                versions: [{
                    title: "Getting Started",
                    task: "Work",
                    creation_date: Date.now(),
                    content: `Welcome to the note manager!`,
                    asociated_picture: "Work/0.jpg",
                    deadline: ''
                }]
            };

            WriteNote(welcome_note);
            WriteUser(user_json);

            user_json['authentification'] = {
                authentificated: true,
                message: "OK"
            };
            user_json.info['token'] = CreateToken(obj.user, obj.password);
            delete user_json.info.password;

            res.end(JSON.stringify(user_json));
            log("ACCEPTED\n");
        }
        
    } catch(e) {
        res.end(JSON.stringify(invalid_authentification_json));
        log("DECLINED\n");
    }
});

app.delete('/API/signout', function(req, res) {
    var obj = req.body;

    log(GetShortDate() + "Received signout request from " + obj.user + " ... ");

    try {
        delete active_tokens[obj.token];
        res.end(JSON.stringify(authentification_ok_json));
        log("ACCEPTED\n");
    }
    catch(e) {
        res.end(JSON.stringify(invalid_authentification_json));
        log("DECLINED\n");
    }
});



/// HANDLING NOTES CRUD REQUESTS ------------------------------------------------------------------------------------------------------

app.post('/API/notes', (req, res) => {
    var obj = req.body;

    log(GetShortDate() + "Received POST request to note " + obj.note_id + " ... ");

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
        log("ACCEPTED\n");
    }
    catch (e) {
        res.end(JSON.stringify(invalid_authentification_json));
        log("DECLINED\n");
    }
});

app.delete('/API/notes', (req, res) => {
    var obj = req.body;

    log(GetShortDate() + "Received DELETE request to note " + obj.note_id + " ... ");

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
        log("ACCEPTED\n");
    }
    catch (e) {
        res.end(JSON.stringify(invalid_authentification_json));
        log("DECLINED\n");
    }
});

app.get('/API/notes', (req, res) => {
    
    try {        
        var token = req.query.token;
        var note_id = req.query.note_id;

        log(GetShortDate() + "Received GET request to note " + note_id + " ... ");

        assert(active_tokens.hasOwnProperty(token));
        user_json = ReadUser(active_tokens[token].user);

        if (!user_json.notes.includes(note_id)) {
            res.end(JSON.stringify(forbidden_resource_json));
            log("DECLINED\n");
        }
        else {
            var note = ReadNote(note_id);
            res.end(JSON.stringify({
                authentification: {
                    authentificated: true,
                    message: "OK"
                },
                data: note
            }));
            log("ACCEPTED\n");
        }
    } catch (e) {
        res.end(JSON.stringify(invalid_authentification_json));
    }
});

app.put('/API/notes', (req, res) => {
    var obj = req.body;
    log(GetShortDate() + "Received PUT request to note " + obj.note_id + " ... ");

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
        log("ACCEPTED\n");
    }
    catch (e) {
        res.end(JSON.stringify(invalid_authentification_json));
        log("DECLINED\n");
    }
});



/// HANDELING SETTINGS CRUD SYNC ------------------------------------------------------------------------------------------------ 

app.put('/API/settings', function(req, res) {
    var obj = req.body;

    log(GetShortDate() + "Received PUT request to settings of user with token " + obj.token + " ... ");

    try {
        assert(active_tokens.hasOwnProperty(obj.token));
        user_json = ReadUser(active_tokens[obj.token].user);

        user_json.config = obj.config;
        if (obj.hasOwnProperty('info')) {
            if (obj.info.hasOwnProperty('name'))
                user_json.info.name = obj.info.name;
            if (obj.info.hasOwnProperty('password'))
                user_json.info.password = obj.info.password;
        }

        WriteUser(user_json);
        res.end(JSON.stringify({
            authentification: {
                authentificated: true,
                message: "OK"
            }
        }));
        log("ACCEPTED\n");
    }
    catch (e) {
        res.end(JSON.stringify(invalid_authentification_json));
        log("DECLINED\n");
    }
});



/// HANDLING GET REQUESTS TO PICTURE GRAPH --------------------------------------------------------------------------------------

app.get('/API/note_graph', (req, res) => {
    try { 
        start = Date.now();

        var note_id = req.query.note_id;
        log(GetShortDate() + "Received request to update graph of note " + note_id + " ... ");

        exec('python3 ' + __dirname + '/scripts/generate_graph.py ' + __dirname + '/data/notes/' + note_id, (err, stdout, stderr) => {
            if (err) {
                console.log("Unable to run script: Unhandled error!");
                console.log(stdout);
                log("ERROR\n");
                return;
            }
            res.sendFile(__dirname + '/scripts/diagram.png');
            end = Date.now();
            log("FINISHED. Computing time: " + (end - start) / 1000 + "\n");
        });
    }
    catch (e) {
        res.end(JSON.stringify(invalid_authentification_json));
    }
});



/// HANDLING SCRIPT / HTML REQUESTS ---------------------------------------------------------------------------------------------

app.use(express.static('assets'));



/// STARTING SERVER -------------------------------------------------------------------------------------------------------------


log("\n\n\nSTARTING NEW SERVER AT DATE " + GetNiceDate() + "\n\n");
app.listen(3000, () => console.log(`Listening on port 3000`));
