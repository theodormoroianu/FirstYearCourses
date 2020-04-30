/// AUTHENTIFICATION CRUD -----------------------------------------------------------------------------------------------

var SYNC_SignIn = (obj, callback) => {
    fetch('API/login', {
        method: 'POST',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(obj)
    }).then(function (response) {
        response.json().then((resp) => {
            console.log("Received from login:");
            console.log(resp);
            callback(resp);
        });
    });
}

var SYNC_SignUp = (obj, callback) => {
    fetch('API/signup', {
        method: 'POST',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(obj)
    }).then(function (response) {
        response.json().then((resp) => {
            console.log("Received from signup:");
            console.log(resp);
            callback(resp);
        });
    });
}

var SYNC_SignOut = (obj, callback) => {
    fetch('API/signout', {
        method: 'DELETE',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(obj)
    }).then(function (response) {
        response.json().then((resp) => {
            console.log("Received from signout:");
            console.log(resp);
            callback(resp);
        });
    });
}



/// NOTES CRUD ------------------------------------------------------------------------------------------------------------------

var SYNC_CreateNote = (obj, callback) => {
    fetch('API/notes', {
        method: 'POST',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(obj)
    }).then(function (response) {
        response.json().then((resp) => {
            console.log("Received from createnote:");
            console.log(resp);
            callback(resp);
        });
    });
}

var SYNC_DeleteNote = (obj, callback) => {
    fetch('API/notes', {
        method: 'DELETE',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(obj)
    }).then(function (response) {
        response.json().then((resp) => {
            console.log("Received from deletenote:");
            console.log(resp);
            callback(resp);
        });
    });
}

var SYNC_GetNote = async (obj) => {
    var response = await fetch('API/notes?token=' + obj.token + '&note_id=' + obj.note_id);
    var response_json = await response.json();
    return response_json;
}

var SYNC_UpdateNote = (obj, callback) => {
    fetch('API/notes', {
        method: 'PUT',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(obj)
    }).then(function (response) {
        response.json().then((resp) => {
            console.log("Received from updatenote:");
            console.log(resp);
            callback(resp);
        });
    });
}



/// FUNCTION FOR UPDATING SETTINGS --------------------------------------------------------------------------------------------------

var SYNC_UpdateSettings = (obj, callback) => {
    fetch('API/settings', {
        method: 'PUT',
        headers: {
            "Content-type": "application/json"
        },
        body: JSON.stringify(obj)
    }).then(function (response) {
        response.json().then((resp) => {
            console.log("Received from updatesettings:");
            console.log(resp);
            callback(resp);
        });
    });
}

