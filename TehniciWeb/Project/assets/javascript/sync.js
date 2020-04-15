/// FUNCTION FOR SYNCING WITH THE SERVER ----------------------------------------------------------------------------------------

function SYNC_ServerRequest(url, obj, callback) {
    var answer = null;
    var xhttp = new XMLHttpRequest();
    
    xhttp.open("POST", url, true);
    xhttp.setRequestHeader("Content-type", "application/json");
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log(this.response);
            console.log(typeof this.response);
            callback(JSON.parse(this.response));
        }
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
            sort_notes_by: "alphabetical",
            sort_asc: true,
            stay_signed_in: false,
            avatar_url: "images/avatar.jpg"
        },
        data: [{
            title: "Getting Started",
            task: "Work",
            creation_date: "2020-04-01",
            content: 'Welcome to the Notes apps!',
            asociated_picture: "03.jpg"
        }]
    };
    SYNC_ServerRequest("API/signup", obj, callback);
}



/// FUNCTION FOR SAVING STATE ---------------------------------------------------------------------------------------------------

function SYNC_Checkpoint(obj, callback) {
    SYNC_ServerRequest("API/checkpoint", obj, callback);
}


function SyncContent(){
    // Selecting the input element and get its value 
    var inputVal = document.getElementById("textbox").value;
    
    State.data = inputVal;

    var xhttp = new XMLHttpRequest();

    xhttp.open("POST", "api/sync_content", true);
    xhttp.setRequestHeader("Content-type", "application/json");
    xhttp.send(JSON.stringify(State));

    setTimeout(SyncContent, 1000);
}

function RequestContent(){
    var inputVal = document.getElementById("textbox").value;
    
    var xhttp = new XMLHttpRequest();

    xhttp.open("POST", "api/request_content", true);
    xhttp.setRequestHeader("Content-type", "application/json");
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            console.log("Here");
            document.getElementById("textbox").value = JSON.parse(this.response).data;
        }
    };
    xhttp.send('{ "user": "Marco", "password": "Polo" }');

    setTimeout(SyncContent(), 0);
}

