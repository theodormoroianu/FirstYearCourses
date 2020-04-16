/// FUNCTION FOR SYNCING WITH THE SERVER ----------------------------------------------------------------------------------------

function SYNC_ServerRequest(url, obj, callback) {
    var xhttp = new XMLHttpRequest();
    
    xhttp.open("POST", url, true);
    xhttp.setRequestHeader("Content-type", "application/json");
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200)
            callback(JSON.parse(this.response));
    };
    xhttp.send(JSON.stringify(obj));
}



/// FUNCTION FOR AUTHENTIFICATION -----------------------------------------------------------------------------------------------

function SYNC_SignIn(user, password, callback) {
    var obj = {
        info: {
            user: user,
            password: password 
        }
    };

    SYNC_ServerRequest("API/login", obj, callback);
}



/// FUNCTION FOR CREATING USER --------------------------------------------------------------------------------------------------

function SYNC_CreateUser(user, name, password, callback) {
    var obj = {
        info: {
            user: user,
            name: name,
            password: password
        },
        config: {
            sort_notes_by: "Alphabetical",
            sort_asc: true,
            stay_signed_in: true,
            avatar_url: "images/avatar.svg"
        },
        data: [{
            title: "Getting Started",
            task: "Work",
            creation_date: Date.now(),
            content: 'Welcome to the Notes apps!',
            asociated_picture: "Work/0.jpg",
            deadline: "9999-03-23"
        }]
    };
    SYNC_ServerRequest("API/signup", obj, callback);
}



/// FUNCTION FOR SAVING STATE ---------------------------------------------------------------------------------------------------

function SYNC_Checkpoint(obj, callback) {
    SYNC_ServerRequest("API/checkpoint", obj, callback);
}



